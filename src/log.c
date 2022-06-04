#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>

#include "debug/terminal.h"
#include "debug/log.h"

#define TIME_STR_LEN (72)
#define MILLIS_STR_LEN 8

#ifdef LOG_FILE
    // Determinel log file path. 
    #ifndef LOG_FILE_PATH
        #define LOG_FILE_PATH "game.log"
    #endif

    // Is file read with terminal (include colors).
    #ifdef LOG_EXT_TERMINAL
        #define COLORS 1
    #else
        #define COLORS 0
    #endif
#else
    // Log with color to stdout.
    #define COLORS 1
#endif

#if COLORS
    #define PRETTY_INFO  TERM_GRN"INFO"COLOR_RESET
    #define PRETTY_TRACE TERM_CYNHB"TRACE"COLOR_RESET
    #define PRETTY_WARN  TERM_YEL"WARN"COLOR_RESET
    #define PRETTY_DEBUG  TERM_MAG"DEBUG"COLOR_RESET
    #define PRETTY_ERROR TERM_RED"ERROR"COLOR_RESET
    #define PRETTY_FATAL TERM_REDHB"FATAL"COLOR_RESET
    #define PRETTY_TEST  TERM_YEL"TEST"COLOR_RESET
#else
    #define PRETTY_INFO  "INFO"
    #define PRETTY_TRACE "TRACE"
    #define PRETTY_WARN  "WARN"
    #define PRETTY_DEBG  "DEBUG"
    #define PRETTY_ERROR "ERROR"
    #define PRETTY_FATAL "FATAL"
    #define PRETTY_TEST  "TEST"
#endif


static FILE *OUT = NULL;

static char *timestr(char *str)
{
    // Date and time of day
    time_t now = time(NULL);
    struct tm *time_info = localtime(&now);
    strftime(str, TIME_STR_LEN, "%H:%M:%S:", time_info);

    // Append millis
    char millis[MILLIS_STR_LEN] = { 0 };
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    sprintf(millis, "%.3lf", (float) current_time.tv_usec/1000);
    strncat(str, millis, MILLIS_STR_LEN);

    return str;
}

void log_printf(const TR_LogLevel level, const char *format, ...)
{
    if (OUT == NULL) 
    {
        fprintf(stderr, "LOGGER IS NOT INITIALIZED!\n");
        return;
    }

    va_list args;
    va_start(args, format);

    switch (level)
    {
        case TR_LOG_INFO:    fprintf(OUT, "["PRETTY_INFO"]  "); break;
        case TR_LOG_TRACE:   fprintf(OUT, "["PRETTY_TRACE"] "); break;
        case TR_LOG_WARNING: fprintf(OUT, "["PRETTY_WARN"]  "); break;
        case TR_LOG_DEBUG:   fprintf(OUT, "["PRETTY_DEBUG"] "); break;
        case TR_LOG_ERROR:   fprintf(OUT, "["PRETTY_ERROR"] "); break;
        case TR_LOG_FATAL:   fprintf(OUT, "["PRETTY_FATAL"] "); break;
        case TR_LOG_TEST:    fprintf(OUT, "["PRETTY_TEST"]  "); break;
        default:                                                break;
    }

    // Time
    char str[TIME_STR_LEN] = { 0 };
    timestr(str);
#if COLORS
    fprintf(OUT, "["TERM_CYN"%s"COLOR_RESET"] ", str);
#else
    fprintf(OUT, "[%s] ", str);
#endif

    // message
    vfprintf(OUT, format, args);
    fprintf(OUT, "\n");

#ifdef LOG_FILE
    fflush(OUT);
#endif

    va_end(args);
}

void log_teardown(void)
{
    #ifdef LOG_FILE
        fclose(OUT);
        #if !LOG_PERSIST
            remove(LOG_FILE_PATH);
        #endif
    #endif
}

void log_setup(void)
{
    #ifdef LOG_FILE
        FILE *stream = fopen(LOG_FILE_PATH, "a");
        if (stream == NULL)
        {
            perror(LOG_FILE_PATH);
            exit(EXIT_FAILURE);
        }
        OUT = stream;
    #else
        OUT = stdout;
    #endif
}