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
}

void tearDown(void)
{
}

void test_clog_msg_only(void)
{
    printf("test clog msg only without colored\r\n");
    clog_color_enable(COLOR_OFF);
    clog_mode_set(MODE_MSG_ONLY);

    clog_logging(INFO, "logging in level info\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "logging in level info\r\n");
    clear_log_buf();
}

void test_clog_msg_only_colored(void)
{
    printf("test clog msg only with colored\r\n");
    clog_color_enable(COLOR_ON);
    clog_mode_set(MODE_MSG_ONLY);

    clog_logging(INFO, "logging in level info\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "\x1b[38;5;4mlogging in level info\r\n\x1B[0m");
    clear_log_buf();
}

void test_clog_w_log_info(void)
{
    printf("test clog with log info without colored\r\n");
    clog_color_enable(COLOR_OFF);
    clog_mode_set(MODE_W_LOG_INFO);

    clog_logging(INFO, "logging in level info\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "(0)[4]logging in level info\r\n");
    clear_log_buf();
}

void test_clog_w_log_info_colored(void)
{
    printf("test clog with log info with colored\r\n");
    clog_color_enable(COLOR_ON);
    clog_mode_set(MODE_W_LOG_INFO);

    clog_logging(INFO, "logging in level info\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "\x1b[38;5;4m(0)[4]logging in level info\r\n\x1B[0m");
    clear_log_buf();
}

void test_clog_timestamp_tick_update(void)
{
    printf("test clog with log info without colored\r\n");
    clog_color_enable(COLOR_OFF);
    clog_mode_set(MODE_W_LOG_INFO);

    clog_timestamp_reset();

    uint8_t index = 0;
    for (index = 0; index < 10; index++)
    {
        clog_timestamp_tick_update();
    }

    clog_logging(INFO, "logging in level info\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "(10)[4]logging in level info\r\n");
    clear_log_buf();
}

#endif // TEST
