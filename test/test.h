#if !defined(GUARD_TEST_H)
#define GUARD_TEST_H

// #include <raylib.h>
#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include "../include/debug/log.h"

typedef void (*TestCase)(int);

#define PRINTF_TEST(format, ...) \
    log_printf(TR_LOG_TEST, format, __VA_ARGS__)

Suite *test_add_case(Suite *suite, TestCase tc);

#endif // GUARD_TEST_H
