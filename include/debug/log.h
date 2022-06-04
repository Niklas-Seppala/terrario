/**
 * @file log.h
 * @copyright Copyright (c) 2022
 * @date 2022-06-04
 * @author Niklas Seppälä
 * 
 * @brief 
 */

#if !defined(LOGGER_H)
#define LOGGER_H
#include <stdarg.h>
#include <raylib.h>

#include "terminal.h"
#include "terrario.h"
#include "terrario/error.h"


/**
 * @brief Logs a statement to compile time defined
 *        output stream, using printf style.
 * 
 * @param level Logging level.
 * @param format Format string.
 * @param ... Values
 */
void log_printf(const TraceLogLevel level, const char *format, ...);

#ifdef DEBUG
    #define PRINTF_TRACE(format, ...) \
        log_printf(LOG_TRACE, format, __VA_ARGS__)
        
    #define PRINTF_DEBUG(format, ...) \
        log_printf(LOG_DEBUG, format, __VA_ARGS__)
#else
    #define PRINTF_TRACE(format, ...) UNDEFINED_MACRO
    #define PRINTF_DEBUG(format, ...) UNDEFINED_MACRO
#endif

/**
 * @brief Setup logging.
 */
void log_setup(void);

/**
 * @brief Clear logging resources.
 */
void log_teardown(void);

#endif // LOGGER_H
