#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "clog.h"

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
} clog_t;

static void clog_default_print (clog_level_t level, char * str);
static void clog_output (clog_level_t level, char * str);
static void clog_get_ansi_color_str (char * color_str,
                                     clog_color_type_t type,
                                     clog_color_code_t color_code);

clog_t clog_cfg = { .level = CLOG_DEFAULT_LOG_LEVEL,
                    .color_enable = COLOR_OFF,
                    .print = clog_default_print };

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
        va_list vl;
        va_start(vl, format);
        vsprintf(&buf[0], format, vl);
        va_end(vl);

        clog_output(level, &buf[0]);
    }
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

static void clog_output (clog_level_t level, char * str)
{
    if (COLOR_ON == clog_cfg.color_enable &&
        COLOR_TYPE_NONE != clog_cfg.color[level].type)
    {

        char color_str[CLOG_MAX_COLOR_STR_SIZE];
        if (FORECOLOR == clog_cfg.color[level].type ||
            BOTH == clog_cfg.color[level].type)
        {
            clog_get_ansi_color_str(&color_str[0],
                                    FORECOLOR,
                                    clog_cfg.color[level].forecolor);
            clog_cfg.print(level, &color_str[0]);
        }
        memset(color_str, 0, sizeof(color_str));
        if (BACKGROUND == clog_cfg.color[level].type ||
            BOTH == clog_cfg.color[level].type)
        {
            clog_get_ansi_color_str(&color_str[0],
                                    BACKGROUND,
                                    clog_cfg.color[level].background);
            clog_cfg.print(level, &color_str[0]);
        }

        clog_cfg.print(level, &str[0]);
        clog_cfg.print(level, ANSI_COLOR_RESET);
    }
    else
    {
        clog_cfg.print(level, &str[0]);
    }
}
