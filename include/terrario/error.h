/**
 * @file log.h
 * @copyright Copyright (c) 2022
 * @date 2022-06-04
 * @author Niklas Seppälä
 * 
 * @brief Error handling and debugging/logging related functionality.
 */


#if !defined(GUARD_ERROR_H)
#define GUARD_ERROR_H
#include "terrario.h"
#include "debug/log.h"


// Definition of invalid count. Eg. when some function
// Should return count of something, checking INVALID_COUNT
// should be done.
#define INVALID_COUNT (-1)


// Prints error with information where it happened.
#define PRINTF_ERROR(format, ...) \
{ \
    log_printf(TR_LOG_ERROR, TERM_RED format COLOR_RESET, __VA_ARGS__); \
    log_printf(TR_LOG_ERROR, "\tat %s(), %s:%d", __func__, __FILE__, __LINE__); \
} \


// Logs fatal event and dumps core.
#define ABORT(reason) \
{ \
   log_printf(TR_LOG_FATAL, "ABORT:"); \
   log_printf(TR_LOG_FATAL, TERM_RED"\t%s"COLOR_RESET, reason); \
   abort();\
} \


#ifdef RT_NULL_KILLS
    // Process aborts on unexpected null pointer.
    // TODO: core dump settings.
    #define DIE_ON_NULL() ABORT("Unexpected NULL pointer!" )
#else 
    #define DIE_ON_NULL() UNDEFINED_MACRO
#endif


#ifdef RT_NULL_CHECKS
    // Assert that provided pointer is not NULL.
    // Process dies if NULLs are set fatal in compile
    // flags.
    #define NOT_NULL(ptr) \
    { \
        if ((void*)ptr == NULL)  \
        { \
            PRINTF_ERROR("%s", __func__, __FILE__, __LINE__, "Null Assertion Error: " #ptr); \
            DIE_ON_NULL(); \
        } \
    }
#else
    #define NOT_NULL(ptr) UNDEFINED_MACRO
#endif

#endif // GUARD_ERROR_H
