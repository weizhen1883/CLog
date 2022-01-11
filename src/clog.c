#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include "clog.h"

#ifndef CLOG_MAX_BUF_SIZE
#define CLOG_MAX_BUF_SIZE   255
#endif

#define CLOG_DEFAULT_LOG_LEVEL  DEBUG

typedef struct
{
    clog_level_t level;
    clog_print_t print;
} clog_t;

static void clog_default_print (clog_level_t level, char * str);

clog_t clog_cfg = { .level = CLOG_DEFAULT_LOG_LEVEL,
                .print = clog_default_print };

void clog_set_level (clog_level_t level)
{
    clog_cfg.level = level;
}

void clog_set_print (clog_print_t print)
{
    clog_cfg.print = print;
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

        clog_cfg.print(level, &buf[0]);
    }
}

static void clog_default_print (clog_level_t level, char * str)
{
    (void)level;
    printf("%s", str);
}
