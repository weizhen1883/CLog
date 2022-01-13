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

#ifndef __CLOG_H__
#define __CLOG_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

enum
{
    OFF = 0,
    FATAL,
    ERROR,
    WARN,
    INFO,
    DEBUG,
    TRACE,

    ALL = 255,
};

enum
{
    COLOR_OFF = 0,
    COLOR_ON,
};

enum
{
    COLOR_TYPE_NONE = 0,
    FORECOLOR       = 38,
    BACKGROUND      = 48,
    BOTH            = 255,
};

enum
{
    MODE_MSG_ONLY = 0,
    MODE_W_LOG_INFO,
};

typedef struct
{
    uint8_t major;
    uint8_t minor;
    uint8_t build;
} clog_version_t;

typedef uint8_t clog_level_t;
typedef uint8_t clog_color_en_t;
typedef uint8_t clog_color_type_t;
typedef uint8_t clog_color_code_t;
typedef uint32_t clog_timestamp_t;
typedef uint8_t clog_mode_t;
typedef void (*clog_print_t) (clog_level_t level, char * str);

void clog_set_level (clog_level_t level);
void clog_set_print (clog_print_t print);
void clog_set_forecolor (clog_level_t level, clog_color_code_t color);
void clog_set_background (clog_level_t level, clog_color_code_t color);
void clog_set_color (clog_level_t level, clog_color_type_t type,
                     clog_color_code_t forecolor, clog_color_code_t background);
void clog_color_enable (clog_color_en_t en);
void clog_logging (clog_level_t level, const char * format, ...);

clog_version_t clog_get_version (void);
char *  clog_get_version_str (void);

void clog_timestamp_tick_update (void);
void clog_timestamp_reset (void);

void clog_mode_set (clog_mode_t mode);

#ifdef __cplusplus
extern }
#endif

#endif /* __CLOG_H__ */
