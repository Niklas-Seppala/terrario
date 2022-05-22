#if !defined(TEST_H)
#define TEST_H

#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

// Test case function implementation.
typedef void (*TestCase)(int);

/**
 * @brief 
 * 
 * @param suite 
 * @param tc 
 * @return Suite* 
 */
Suite *test_add_case(Suite *suite, TestCase tc);

#endif // TEST_H
