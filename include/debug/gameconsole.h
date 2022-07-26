#if !defined(GUARD_GAME_CONSOLE_H)

#include <unistd.h>
#include <sys/mman.h>
#define GUARD_GAME_CONSOLE_H _SC_PAGE_SIZE

#if(TR_GC_SHARED_BUFFER)
#define TR_GCONSOLE_BUFFER_ACCESSIBILITY MAP_SHARED
#else
#define TR_GCONSOLE_BUFFER_ACCESSIBILITY MAP_PRIVATE
#endif

#if(TR_GC_FBACKED_BUFFER)
#define TR_GCONSOLE_BUFFER_FILE_BACKED 0
#else
#define TR_GCONSOLE_BUFFER_FILE_BACKED MAP_ANONYMOUS
#endif

#define BACKED_BY_FILE (TR_GCONSOLE_BUFFER_FILE_BACKED != MAP_ANONYMOUS)

void TR_gconsole_buffer_msg(const char *msg, int len);

void TR_gconsole_init(void);

void TR_gconsole_teardown(void);

void TR_gconsole_flush(void);

void TR_gconsole_render(void);

long TR_gconsole_get_buffer_size(void);


#endif // GUARD_GAME_CONSOLE_H
