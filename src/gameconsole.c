#include "debug/gameconsole.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include "terrario/error.h"

#define LOG_MODULE "[GAMECONSOLE]"

#define BACKED_FILE_PATH "GConsole"

extern int errno;

char *CONSOLE;

long BUFFER_SIZE;


long TR_gconsole_get_buffer_size(void)
{
    return BUFFER_SIZE;
}

/**
 * @brief 
 * 
 * @return int 
 */
static int open_buffer_file();

static void set_buffer_size();

void TR_gconsole_init(void)
{
    const int ACCESS_FLAGS = PROT_READ | PROT_WRITE;
    const int FLAGS = TR_GCONSOLE_BUFFER_ACCESSIBILITY |
                      TR_GCONSOLE_BUFFER_FILE_BACKED;

    int file = open_buffer_file();

    set_buffer_size();

    CONSOLE = mmap(NULL, BUFFER_SIZE, ACCESS_FLAGS, FLAGS, file, 0);
    if (CONSOLE == MAP_FAILED)
    {
        log_printf(TR_LOG_FATAL, LOG_MODULE " %s",
            strerror(errno));
        ABORT("Could not mmap() game console buffer.");
    }
    log_printf(TR_LOG_INFO, LOG_MODULE " Buffer mapped to address %p.", CONSOLE);

    if (file) close(file);
}

void TR_gconsole_teardown(void)
{
    munmap(CONSOLE, BUFFER_SIZE);
    log_printf(TR_LOG_INFO, LOG_MODULE " Buffer un-mapped.");
}

static void set_buffer_size()
{
    BUFFER_SIZE = sysconf(_SC_PAGESIZE);
    log_printf(TR_LOG_INFO, LOG_MODULE " Buffer size is: %d bytes.", BUFFER_SIZE);
}

static int open_buffer_file()
{
    int fd = -1;
    const int OWNER_FLAGS = S_IRWXU | S_IRWXG;
    const int ACCESS_FLAGS = O_CREAT | O_RDWR;

    if (BACKED_BY_FILE) {
        if ((fd = open(BACKED_FILE_PATH, ACCESS_FLAGS | OWNER_FLAGS)) == -1)
        {
            log_printf(TR_LOG_FATAL, LOG_MODULE " %s",
                strerror(errno));
            ABORT("Could not open a backing file for console buffer.");
        }
        else
        {
            // Allocate enough space to file.
            posix_fallocate(fd, 0, BUFFER_SIZE);
            log_printf(TR_LOG_INFO, LOG_MODULE " Buffer is backed by file %s",
                 BACKED_FILE_PATH);
        }

    }
    // Default to no file.
    else fd = 0;
    return fd;
}