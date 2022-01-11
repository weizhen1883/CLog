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

typedef uint8_t clog_level_t;
typedef void (*clog_print_t) (clog_level_t level, char * str);

void clog_set_level (clog_level_t level);
void clog_set_print (clog_print_t print);
void clog_logging (clog_level_t level, const char * format, ...);

#ifdef __cplusplus
extern }
#endif

#endif /* __CLOG_H__ */
