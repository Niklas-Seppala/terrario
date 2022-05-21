#if !defined(LOGGER_H)
#define LOGGER_H
#include <stdarg.h>
#include <raylib.h>
#include "terminal.h"


/**
 * @brief Logs a statement to compile time defined
 *        output stream, using printf style.
 * 
 * @param level Logging level.
 * @param format Format string.
 * @param ... Values
 */
void log_printf(const TraceLogLevel level, const char *format, ...);

#define UNDEFINED

#ifdef DEBUG
    #define PRINTF_TRACE(format, ...) \
        log_printf(LOG_TRACE, format, __VA_ARGS__)
        
    #define PRINTF_DEBUG(format, ...) \
        log_printf(LOG_DEBUG, format, __VA_ARGS__)
#else
    #define PRINTF_TRACE(format, ...) UNDEFINED
    #define PRINTF_DEBUG(format, ...) UNDEFINED
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
