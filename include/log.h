#if !defined(LOGGER_H)
#define LOGGER_H
#include <stdarg.h>
#include <raylib.h>

/**
 * @brief 
 * 
 * @param level 
 * @param format 
 * @param ... 
 */
void log_any(const TraceLogLevel level, const char *format, ...);

/**
 * @brief 
 * 
 */
void log_setup(void);

/**
 * @brief 
 * 
 */
void log_teardown(void);

#endif // LOGGER_H
