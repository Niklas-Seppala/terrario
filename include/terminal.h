#if !defined(TERMINAL_H)
#define TERMINAL_H

#define TERM_BLK "\e[0;30m"
#define TERM_RED "\e[0;31m"
#define TERM_REDHB "\e[0;101m"
#define TERM_GRN "\e[0;32m"
#define TERM_YEL "\e[0;33m"
#define TERM_BLU "\e[0;34m"
#define TERM_MAG "\e[0;35m"
#define TERM_CYN "\e[0;36m"
#define TERM_CYNHB "\e[0;106m"
#define TERM_WHT "\e[0;37m"
#define COLOR_RESET "\e[0m"

#define INFO  TERM_GRN"INFO"COLOR_RESET
#define TRACE TERM_CYNHB"TRACE"COLOR_RESET
#define WARN  TERM_YEL"WARN"COLOR_RESET
#define DEBG  TERM_MAG"DEBUG"COLOR_RESET
#define ERROR TERM_RED"ERROR"COLOR_RESET
#define FATAL TERM_REDHB"FATAL"COLOR_RESET

#endif // TERMINAL_H
