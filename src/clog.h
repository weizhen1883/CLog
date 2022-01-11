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

typedef uint8_t clog_level_t;
typedef uint8_t clog_color_en_t;
typedef uint8_t clog_color_type_t;
typedef uint8_t clog_color_code_t;
typedef void (*clog_print_t) (clog_level_t level, char * str);

void clog_set_level (clog_level_t level);
void clog_set_print (clog_print_t print);
void clog_set_forecolor (clog_level_t level, clog_color_code_t color);
void clog_set_background (clog_level_t level, clog_color_code_t color);
void clog_set_color (clog_level_t level, clog_color_type_t type,
                     clog_color_code_t forecolor, clog_color_code_t background);
void clog_color_enable (clog_color_en_t en);
void clog_logging (clog_level_t level, const char * format, ...);

#ifdef __cplusplus
extern }
#endif

#endif /* __CLOG_H__ */
