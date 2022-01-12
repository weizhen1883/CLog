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

#ifdef TEST

#include <stdio.h>
#include <string.h>
#include "unity.h"

#include "clog.h"

char log_buf[255];
uint8_t buf_ptr = 0;

static void clog_print (clog_level_t level, char * str)
{
    uint8_t i = 0;
    while (str[i] != '\0')
    {
        log_buf[buf_ptr++] = str[i++];
    }
}

static void clear_log_buf (void)
{
    printf("%s", log_buf);
    memset(log_buf, 0, sizeof(log_buf));
    buf_ptr = 0;
}

void setUp(void)
{
    clog_version_t version = clog_get_version();
    printf("CLog Version %d.%d.%d\r\n", version.major, version.minor, version.build);
    clog_set_print(clog_print);
    clog_color_enable(COLOR_ON);
}

void tearDown(void)
{
}

void test_clog_colored_default(void)
{
    printf("test clog colored default\r\n");
    clog_set_level(ALL);

    clog_logging(FATAL, "logging in level fatal\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "\x1b[38;5;1mlogging in level fatal\r\n\x1B[0m");
    clear_log_buf();

    clog_logging(ERROR, "logging in level error\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "\x1b[38;5;2mlogging in level error\r\n\x1B[0m");
    clear_log_buf();

    clog_logging(WARN, "logging in level warn\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "\x1b[38;5;3mlogging in level warn\r\n\x1B[0m");
    clear_log_buf();

    clog_logging(INFO, "logging in level info\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "\x1b[38;5;4mlogging in level info\r\n\x1B[0m");
    clear_log_buf();

    clog_logging(DEBUG, "logging in level debug\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "\x1b[38;5;5mlogging in level debug\r\n\x1B[0m");
    clear_log_buf();

    clog_logging(TRACE, "logging in level trace\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "\x1b[38;5;6mlogging in level trace\r\n\x1B[0m");
    clear_log_buf();
}

void test_clog_set_forecolor(void)
{
    printf("test clog set forecolor\r\n");
    clog_set_level(ALL);
    clog_set_forecolor(INFO, 11);

    clog_logging(INFO, "logging in level info\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "\x1b[38;5;11mlogging in level info\r\n\x1B[0m");
    clear_log_buf();
}

void test_clog_set_background(void)
{
    printf("test clog set background\r\n");
    clog_set_level(ALL);
    clog_set_background(INFO, 11);

    clog_logging(INFO, "logging in level info\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "\x1b[48;5;11mlogging in level info\r\n\x1B[0m");
    clear_log_buf();
}

void test_clog_set_color(void)
{
    printf("test clog set color\r\n");
    clog_set_level(ALL);
    clog_set_color(INFO, BOTH, 10, 11);

    clog_logging(INFO, "logging in level info\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "\x1b[38;5;10m\x1b[48;5;11mlogging in level info\r\n\x1B[0m");
    clear_log_buf();
}

#endif // TEST
