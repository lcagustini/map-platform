#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#ifdef PSP_BUILD
#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspdebug.h>
#include <pspctrl.h>

#include <pspgu.h>
#include <pspgum.h>

#include "pspcallback.c"
#endif

#ifdef PSP_BUILD
#include <SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#ifdef PSP_BUILD
PSP_MODULE_INFO("platform", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);
PSP_HEAP_SIZE_MAX();
#define printf	pspDebugScreenPrintf
#endif

#ifdef PSP_BUILD
#define SCREEN_WIDTH 480
#define SCREEN_HEIGHT 272
#else
#define SCREEN_WIDTH 3*480
#define SCREEN_HEIGHT 3*272
#endif

SDL_Window *window;
SDL_Renderer *renderer;

SDL_Texture* loadTexture(const char *path) {
    SDL_Texture *newTexture = NULL;

    int width, height, channels;
    uint8_t *image = stbi_load(path, &width, &height, &channels, STBI_rgb);
    uint32_t rmask = 0x000000ff;
    uint32_t gmask = 0x0000ff00;
    uint32_t bmask = 0x00ff0000;
    uint32_t amask = 0;

    SDL_Surface* loadedSurface = SDL_CreateRGBSurfaceFrom(image, width, height, STBI_rgb*8, STBI_rgb*width, rmask, gmask, bmask, amask);

    if (loadedSurface) {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

int main(void) {
#ifdef PSP_BUILD
    PSPSetupCallbacks();
#endif
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("platform", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0xFF, 0xFF);

    SDL_Event e;
    while (true) {
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) goto exit;
        }

        SDL_RenderClear(renderer );
        //SDL_RenderCopy(renderer, gTexture, NULL, NULL );
        SDL_RenderPresent(renderer);
    }

exit:
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
