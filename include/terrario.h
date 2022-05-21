#if !defined(TERRARIO_H)
#define TERRARIO_H

#define STRINGIFY(x) STRINGIFY_(x)
#define STRINGIFY_(x) #x

#ifndef GAME_NAME
    #define GAME_NAME "Terrario"
#endif

#ifndef TARGET_FPS
    #define TARGET_FPS 60
#endif

#ifndef SCREEN_DIMENSIONS
    #define SCREEN_START_WIDTH 650
    #define SCREEN_START_HEIGHT 650
#endif


#endif // TERRARIO_H
