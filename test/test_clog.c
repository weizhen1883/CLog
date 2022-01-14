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

static void clog_print (clog_level_t level, char * str)
{
    printf("level - %d: %s", level, str);
    sprintf(log_buf, "%s", str);
}

static void clear_log_buf (void)
{
    memset(log_buf, 0, sizeof(log_buf));
}

void setUp(void)
{
    printf("CLog Version %s\r\n", clog_get_version_str());
    clog_set_print(clog_print);
}

void tearDown(void)
{
}

void test_clog_off(void)
{
    printf("set clog level OFF\r\n");
    clog_set_level(OFF);

    clog_logging(FATAL, "logging in level fatal\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "");
    clear_log_buf();

    clog_logging(ERROR, "logging in level error\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "");
    clear_log_buf();

    clog_logging(WARN, "logging in level warn\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "");
    clear_log_buf();

    clog_logging(INFO, "logging in level info\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "");
    clear_log_buf();

    clog_logging(DEBUG, "logging in level debug\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "");
    clear_log_buf();

    clog_logging(TRACE, "logging in level trace\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "");
    clear_log_buf();
}

void test_clog_fatal(void)
{
    printf("set clog level FATAL\r\n");
    clog_set_level(FATAL);

    clog_logging(FATAL, "logging in level fatal\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "logging in level fatal\r\n");
    clear_log_buf();

    clog_logging(ERROR, "logging in level error\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "");
    clear_log_buf();

    clog_logging(WARN, "logging in level warn\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "");
    clear_log_buf();

    clog_logging(INFO, "logging in level info\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "");
    clear_log_buf();

    clog_logging(DEBUG, "logging in level debug\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "");
    clear_log_buf();

    clog_logging(TRACE, "logging in level trace\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "");
    clear_log_buf();
}

void test_clog_error(void)
{
    printf("set clog level ERROR\r\n");
    clog_set_level(ERROR);

    clog_logging(FATAL, "logging in level fatal\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "logging in level fatal\r\n");
    clear_log_buf();

    clog_logging(ERROR, "logging in level error\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "logging in level error\r\n");
    clear_log_buf();

    clog_logging(WARN, "logging in level warn\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "");
    clear_log_buf();

    clog_logging(INFO, "logging in level info\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "");
    clear_log_buf();

    clog_logging(DEBUG, "logging in level debug\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "");
    clear_log_buf();

    clog_logging(TRACE, "logging in level trace\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "");
    clear_log_buf();
}

void test_clog_warn(void)
{
    printf("set clog level WARN\r\n");
    clog_set_level(WARN);

    clog_logging(FATAL, "logging in level fatal\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "logging in level fatal\r\n");
    clear_log_buf();

    clog_logging(ERROR, "logging in level error\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "logging in level error\r\n");
    clear_log_buf();

    clog_logging(WARN, "logging in level warn\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "logging in level warn\r\n");
    clear_log_buf();

    clog_logging(INFO, "logging in level info\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "");
    clear_log_buf();

    clog_logging(DEBUG, "logging in level debug\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "");
    clear_log_buf();

    clog_logging(TRACE, "logging in level trace\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "");
    clear_log_buf();
}

void test_clog_info(void)
{
    printf("set clog level INFO\r\n");
    clog_set_level(INFO);

    clog_logging(FATAL, "logging in level fatal\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "logging in level fatal\r\n");
    clear_log_buf();

    clog_logging(ERROR, "logging in level error\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "logging in level error\r\n");
    clear_log_buf();

    clog_logging(WARN, "logging in level warn\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "logging in level warn\r\n");
    clear_log_buf();

    clog_logging(INFO, "logging in level info\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "logging in level info\r\n");
    clear_log_buf();

    clog_logging(DEBUG, "logging in level debug\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "");
    clear_log_buf();

    clog_logging(TRACE, "logging in level trace\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "");
    clear_log_buf();
}

void test_clog_debug(void)
{
    printf("set clog level DEBUG\r\n");
    clog_set_level(DEBUG);

    clog_logging(FATAL, "logging in level fatal\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "logging in level fatal\r\n");
    clear_log_buf();

    clog_logging(ERROR, "logging in level error\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "logging in level error\r\n");
    clear_log_buf();

    clog_logging(WARN, "logging in level warn\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "logging in level warn\r\n");
    clear_log_buf();

    clog_logging(INFO, "logging in level info\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "logging in level info\r\n");
    clear_log_buf();

    clog_logging(DEBUG, "logging in level debug\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "logging in level debug\r\n");
    clear_log_buf();

    clog_logging(TRACE, "logging in level trace\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "");
    clear_log_buf();
}

void test_clog_trace(void)
{
    printf("set clog level TRACE\r\n");
    clog_set_level(TRACE);

    clog_logging(FATAL, "logging in level fatal\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "logging in level fatal\r\n");
    clear_log_buf();

    clog_logging(ERROR, "logging in level error\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "logging in level error\r\n");
    clear_log_buf();

    clog_logging(WARN, "logging in level warn\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "logging in level warn\r\n");
    clear_log_buf();

    clog_logging(INFO, "logging in level info\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "logging in level info\r\n");
    clear_log_buf();

    clog_logging(DEBUG, "logging in level debug\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "logging in level debug\r\n");
    clear_log_buf();

    clog_logging(TRACE, "logging in level trace\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "logging in level trace\r\n");
    clear_log_buf();
}

void test_clog_all(void)
{
    printf("set clog level ALL\r\n");
    clog_set_level(ALL);

    clog_logging(FATAL, "logging in level fatal\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "logging in level fatal\r\n");
    clear_log_buf();

    clog_logging(ERROR, "logging in level error\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "logging in level error\r\n");
    clear_log_buf();

    clog_logging(WARN, "logging in level warn\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "logging in level warn\r\n");
    clear_log_buf();

    clog_logging(INFO, "logging in level info\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "logging in level info\r\n");
    clear_log_buf();

    clog_logging(DEBUG, "logging in level debug\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "logging in level debug\r\n");
    clear_log_buf();

    clog_logging(TRACE, "logging in level trace\r\n");
    TEST_ASSERT_EQUAL_STRING(log_buf, "logging in level trace\r\n");
    clear_log_buf();
}

#endif // TEST
