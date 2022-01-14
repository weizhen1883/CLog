/////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2022, Zhen Wei                                                //
//                                                                             //
// Permission is hereby granted, free of charge, to any person obtaining a     //
// copy of this software and associated documentation files (the "Software"),  //
// to deal in the Software without restriction, including without limitation   //
// the rights to use, copy, modify, merge, publish, distribute, sublicense,    //
// and/or sell copies of the Software, and to permit persons to whom the       //
// Software is furnished to do so, subject to the following conditions:        //
//                                                                             //
// The above copyright notice and this permission notice shall be included     //
// in all copies or substantial portions of the Software.                      //
//                                                                             //
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS     //
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, //
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL     //
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER  //
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING     //
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER D       //
// EALINGS IN THE SOFTWARE.                                                    //
/////////////////////////////////////////////////////////////////////////////////

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "clog.h"

#define CLOG_VERSION_MAJOR      1
#define CLOG_VERSION_MINOR      1
#define CLOG_VERSION_BUILD      1

#define CLOG_VERSION_STR(X)     ('0' + X)

#ifndef CLOG_MAX_BUF_SIZE
#define CLOG_MAX_BUF_SIZE   255
#endif

#ifndef CLOG_LOG_LEVEL_SIZE
#define CLOG_LOG_LEVEL_SIZE     (TRACE + 1)
#endif

#define CLOG_DEFAULT_LOG_LEVEL  DEBUG

#define ANSI_COLOR_RESET        "\x1b[0m"
#define CLOG_MAX_COLOR_STR_SIZE 15

typedef struct
{
    clog_color_type_t type;
    clog_color_code_t forecolor;
    clog_color_code_t background;
} clog_color_t;

typedef struct
{
    clog_level_t level;
    clog_color_en_t color_enable;
    clog_color_t color[CLOG_LOG_LEVEL_SIZE];
    clog_print_t print;
    clog_mode_t mode;
} clog_t;

static void clog_default_print (clog_level_t level, char * str);
static void clog_output (clog_level_t level, char * str);
static void clog_output_add_color (clog_level_t level, char * str);
static void clog_get_ansi_color_str (char * color_str,
                                     clog_color_type_t type,
                                     clog_color_code_t color_code);

static clog_version_t clog_version = { .major = CLOG_VERSION_MAJOR,
                                       .minor = CLOG_VERSION_MINOR,
                                       .build = CLOG_VERSION_BUILD, };

static const uint8_t version_str_size = 6;
static char clog_version_str[version_str_size] = {
                CLOG_VERSION_STR(CLOG_VERSION_MAJOR), '.',
                CLOG_VERSION_STR(CLOG_VERSION_MINOR), '.',
                CLOG_VERSION_STR(CLOG_VERSION_BUILD), '\0' };

static clog_t clog_cfg = { .level = CLOG_DEFAULT_LOG_LEVEL,
                           .color_enable = COLOR_OFF,
                           .print = clog_default_print,
                           .mode = MODE_MSG_ONLY, };

static volatile clog_timestamp_t clog_timestamp = 0;

void clog_set_level (clog_level_t level)
{
    clog_cfg.level = level;
}

void clog_set_print (clog_print_t print)
{
    clog_cfg.print = print;
}

void clog_set_forecolor (clog_level_t level, clog_color_code_t color)
{
    clog_cfg.color[level].type = FORECOLOR;
    clog_cfg.color[level].forecolor = color;
}

void clog_set_background (clog_level_t level, clog_color_code_t color)
{
    clog_cfg.color[level].type = BACKGROUND;
    clog_cfg.color[level].background = color;
}

void clog_set_color (clog_level_t level, clog_color_type_t type,
                     clog_color_code_t forecolor, clog_color_code_t background)
{
    clog_cfg.color[level].type = type;
    clog_cfg.color[level].forecolor = forecolor;
    clog_cfg.color[level].background = background;
}

void clog_color_enable (clog_color_en_t en)
{
    if (COLOR_ON == en)
    {
        uint8_t index;
        for (index = 0; index < CLOG_LOG_LEVEL_SIZE; index++)
        {
            clog_cfg.color[index].type = FORECOLOR;
            clog_cfg.color[index].forecolor = index;
            clog_cfg.color[index].background = 0;
        }
    }

    clog_cfg.color_enable = en;
}

void clog_logging (clog_level_t level, const char * format, ...)
{
    if (level <= clog_cfg.level)
    {
        char buf[CLOG_MAX_BUF_SIZE];
        memset(buf, 0, sizeof(buf));
        
        va_list vl;
        va_start(vl, format);
        vsprintf(&buf[0], format, vl);
        va_end(vl);

        clog_output(level, &buf[0]);
    }
}

clog_version_t clog_get_version (void)
{
     return clog_version;
}

char * clog_get_version_str (void)
{
    return &clog_version_str[0];
}

void clog_timestamp_tick_update (void)
{
    clog_timestamp++;
}

void clog_timestamp_reset (void)
{
    clog_timestamp = 0;
}

void clog_mode_set (clog_mode_t mode)
{
    clog_cfg.mode = mode;
}

static void clog_default_print (clog_level_t level, char * str)
{
    (void)level;
    printf("%s", str);
}

static void clog_get_ansi_color_str (char * color_str,
                                     clog_color_type_t type,
                                     clog_color_code_t color_code)
{
    sprintf(color_str, "\x1b[%d;5;%dm", type, color_code);
}

static char log_msg_buf[CLOG_MAX_BUF_SIZE];
static uint16_t log_msg_ptr = 0;
static void clog_output (clog_level_t level, char * str)
{
    switch (clog_cfg.mode)
    {
        case MODE_W_LOG_INFO:
        {
            uint16_t i;
            for (i = 0; i < CLOG_MAX_BUF_SIZE && str[i] != '\0'; i++)
            {
                if (0 == log_msg_ptr)
                {
                    const uint8_t buf_size = 15;
                    char buf[buf_size];
                    memset(buf, 0, sizeof(buf));
                    sprintf(buf, "(%d)[%d]", clog_timestamp, level);

                    uint8_t j;
                    for (j = 0; j < buf_size && buf[j] != '\0'; j++)
                    {
                        log_msg_buf[log_msg_ptr++] = buf[j];
                    }
                }

                log_msg_buf[log_msg_ptr++] = str[i];
                if (str[i] == '\n')
                {
                    log_msg_buf[log_msg_ptr++] = '\0';
                    clog_output_add_color(level, &log_msg_buf[0]);
                    log_msg_ptr = 0;
                    memset(log_msg_buf, 0, sizeof(log_msg_buf));
                }
            }
            break;
        }
        case MODE_MSG_ONLY:
        default:
            clog_output_add_color(level, &str[0]);
            break;
    }
}

static void clog_output_add_color (clog_level_t level, char * str)
{
    if (COLOR_ON == clog_cfg.color_enable &&
        COLOR_TYPE_NONE != clog_cfg.color[level].type)
    {
        uint8_t is_new_line = 0;
        uint16_t i = 0;
        uint16_t buf_ptr = 0;
        char buf[CLOG_MAX_BUF_SIZE];
        char color_str[CLOG_MAX_COLOR_STR_SIZE];

        memset(buf, 0, sizeof(buf));
        memset(color_str, 0, sizeof(color_str));

        if (FORECOLOR == clog_cfg.color[level].type ||
            BOTH == clog_cfg.color[level].type)
        {
            clog_get_ansi_color_str(&color_str[0],
                                    FORECOLOR,
                                    clog_cfg.color[level].forecolor);

            for (i = 0; i < CLOG_MAX_COLOR_STR_SIZE && color_str[i] != '\0'; i++)
            {
                buf[buf_ptr++] = color_str[i];
            }
        }
        memset(color_str, 0, sizeof(color_str));
        if (BACKGROUND == clog_cfg.color[level].type ||
            BOTH == clog_cfg.color[level].type)
        {
            clog_get_ansi_color_str(&color_str[0],
                                    BACKGROUND,
                                    clog_cfg.color[level].background);
            for (i = 0; i < CLOG_MAX_COLOR_STR_SIZE && color_str[i] != '\0'; i++)
            {
                buf[buf_ptr++] = color_str[i];
            }
        }

        for (i = 0; i < CLOG_MAX_BUF_SIZE && str[i] != '\0'; i++)
        {
            buf[buf_ptr++] = str[i];
        }

        // ignore the new line, if there is new line there
        if (buf[buf_ptr - 1] == '\n')
        {
            buf_ptr -= 1;

            if (buf[buf_ptr - 1] == '\r')
            {
                buf_ptr -= 1;
            }

            is_new_line = 1;
        }

        memcpy(color_str, ANSI_COLOR_RESET, sizeof(ANSI_COLOR_RESET));
        for (i = 0; i < CLOG_MAX_COLOR_STR_SIZE && color_str[i] != '\0'; i++)
        {
            buf[buf_ptr++] = color_str[i];
        }

        if (is_new_line == 1)
        {
            buf[buf_ptr++] = '\r';
            buf[buf_ptr++] = '\n';
        }

        clog_cfg.print(level, &buf[0]);
    }
    else
    {
        clog_cfg.print(level, &str[0]);
    }
}
