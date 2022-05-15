#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>

#include "terminal.h"

static FILE *OUT = NULL;

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
    va_list args;
    va_start(args, format);

    switch (level)
    {
        case LOG_INFO:
        #if COLORS
            fprintf(OUT, "["INFO"]  ");
        #else
            fprintf(OUT, "[INFO]  ");
        #endif
            break;
        
        case LOG_TRACE:
        #if COLORS
            fprintf(OUT, "["TRACE"] ");
        #else
            fprintf(OUT, "[TRACE] ");
        #endif
            break;

        case LOG_WARNING: 
        #if COLORS
            fprintf(OUT, "["WARN"]  ");
        #else
            fprintf(OUT, "[WARN]  ");
        #endif
            break;

        case LOG_DEBUG: 
        #if COLORS
            fprintf(OUT, "["DEBG"] ");
        #else
            fprintf(OUT, "[DEBUG] ");
        #endif
            break;
        
        case LOG_ERROR: 
        #if COLORS
            fprintf(OUT, "["ERROR"] ");
        #else
            fprintf(OUT, "[ERROR] ");
        #endif
            break;

        case LOG_FATAL: 
        #if COLORS
            fprintf(OUT, "["FATAL"] ");
        #else
            fprintf(OUT, "[FATAL] ");
        #endif
            break;

        default: 
            break;
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

#ifdef DEBUG
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