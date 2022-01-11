#ifdef TEST

#include <stdio.h>
#include "unity.h"

#include "clog.h"

#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

char log_buf[255];

static void clog_print (clog_level_t level, char * str)
{
    printf("level - %d: %s", level, str);
    sprintf(log_buf, "%s", str);
}

static void clear_log_buf (void)
{
    uint16_t i;
    for (i = 0; i < 255; i++)
    {
        log_buf[i] = 0;
    }
}

void setUp(void)
{
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
