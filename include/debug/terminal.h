/**
 * @file log.h
 * @copyright Copyright (c) 2022
 * @date 2022-06-04
 * @author Niklas Seppälä
 * 
 * @brief ANSI terminal color definitions.
 */


#if !defined(GUARD_TERMINAL_H)
#define GUARD_TERMINAL_H

#define TERM_BLK "\033[0;30m"
#define TERM_RED "\033[0;31m"
#define TERM_REDHB "\033[0;101m"
#define TERM_GRN "\033[0;32m"
#define TERM_YEL "\033[0;33m"
#define TERM_BLU "\033[0;34m"
#define TERM_MAG "\033[0;35m"
#define TERM_CYN "\033[0;36m"
#define TERM_CYNHB "\033[0;106m"
#define TERM_WHT "\033[0;37m"
#define COLOR_RESET "\033[0m"

#endif // GUARD_TERMINAL_H
