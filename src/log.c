#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>

#include "debug/terminal.h"

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
    #define INFO  TERM_GRN"INFO"COLOR_RESET
    #define TRACE TERM_CYNHB"TRACE"COLOR_RESET
    #define WARN  TERM_YEL"WARN"COLOR_RESET
    #define DEBG  TERM_MAG"DEBUG"COLOR_RESET
    #define ERROR TERM_RED"ERROR"COLOR_RESET
    #define FATAL TERM_REDHB"FATAL"COLOR_RESET
#else
    #define INFO "INFO"
    #define TRACE "TRACE"
    #define WARN  "WARN"
    #define DEBG  "DEBUG"
    #define ERROR "ERROR"
    #define FATAL "FATAL"
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

void log_printf(const TraceLogLevel level, const char *format, ...)
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
        case LOG_INFO:    fprintf(OUT, "["INFO"]  "); break;
        case LOG_TRACE:   fprintf(OUT, "["TRACE"] "); break;
        case LOG_WARNING: fprintf(OUT, "["WARN"]  "); break;
        case LOG_DEBUG:   fprintf(OUT, "["DEBG"] ");  break;
        case LOG_ERROR:   fprintf(OUT, "["ERROR"] "); break;
        case LOG_FATAL:   fprintf(OUT, "["FATAL"] "); break;
        default:                                      break;
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