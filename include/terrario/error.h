#if !defined(ERROR_H)
#define ERROR_H
#include "debug/log.h"

#define PRINTF_ERROR(format, func, file, line, ...) \
{ \
    log_printf(LOG_ERROR, TERM_RED format COLOR_RESET, __VA_ARGS__); \
    log_printf(LOG_ERROR, "      at %s(), %s:%d", func, file, line); \
} \


typedef enum return_code {
    TERRARIO_ERROR = 0,
    TERRARIO_SUCCESS = 1
} RC;

#endif // ERROR_H
