#include <stdio.h>
#include <raylib.h>
#include <log.h>
#include <unistd.h>

int main(void)
{
    log_setup();

    log_printf(LOG_INFO, "Hello !");
    log_printf(LOG_WARNING, "Warn !");
    log_printf(LOG_ERROR, "ERR !");
    log_printf(LOG_FATAL, "FATAL !");

    PRINTF_TRACE("%s, %d","trace", 15);
    PRINTF_DEBUG("%s, %d","dbg", 15);

    log_teardown();
}
