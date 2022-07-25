/**
 * @file log.h
 * @copyright Copyright (c) 2022
 * @date 2022-06-04
 * @author Niklas Seppälä
 * 
 * @brief Logging API for variety of different levels.
 *        Most common log functions also come with compilation
 *        dependent macros.
 * 
 *        Functionality can be customized with compilation flags. 
 *              TODO: list flags here.
 */


#if !defined(GUARD_LOGGER_H)
#define GUARD_LOGGER_H
#include <stdarg.h>

#include "terminal.h"
#include "terrario.h"
#include "terrario/error.h"

typedef enum TR_LOG {
    TR_LOG_INFO,
    TR_LOG_TRACE,
    TR_LOG_WARNING,
    TR_LOG_DEBUG,  
    TR_LOG_ERROR,  
    TR_LOG_FATAL,  
    TR_LOG_TEST,   
} TR_LogLevel;

/**
 * @brief Logs a statement to compile time defined
 *        output stream, using printf style.
 * 
 * @param level Logging level.
 * @param format Format string.
 * @param ... Values
 */
void log_printf(const TR_LogLevel level, const char *format, ...);

#ifdef DEBUG
    #define PRINTF_TRACE(format, ...) \
        log_printf(TR_LOG_TRACE, format, __VA_ARGS__)
        
    #define PRINTF_DEBUG(format, ...) \
        log_printf(TR_LOG_DEBUG, format, __VA_ARGS__)
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

#endif // GUARD_LOGGER_H
