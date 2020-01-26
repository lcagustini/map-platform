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

struct object {
    SDL_Rect rect;
    SDL_Texture *texture;
};

struct input {
    SDL_Joystick *controllers[4];
    int controllers_count;
};

bool initObject(int x, int y, const char *texture_path, struct object *obj) {
    int width, height, channels;
    uint8_t *image = stbi_load(texture_path, &width, &height, &channels, STBI_rgb_alpha);
    uint32_t rmask = 0x000000ff;
    uint32_t gmask = 0x0000ff00;
    uint32_t bmask = 0x00ff0000;
    uint32_t amask = 0xff000000;

    SDL_Surface* loadedSurface = SDL_CreateRGBSurfaceFrom(image, width, height, STBI_rgb_alpha*8, STBI_rgb_alpha*width, rmask, gmask, bmask, amask);

    if (loadedSurface) {
        obj->texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        obj->rect.x = x;
        obj->rect.y = y;
        obj->rect.w = width;
        obj->rect.h = height;
        SDL_FreeSurface(loadedSurface);

        return true;
    }

    return false;
}

int main(void) {
#ifdef PSP_BUILD
    PSPSetupCallbacks();
#endif
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);

    window = SDL_CreateWindow("platform", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0xFF, 0xFF);

    struct input input = {0};
    input.controllers_count = SDL_NumJoysticks();
    for (int i = 0; i < input.controllers_count; i++) input.controllers[i] = SDL_JoystickOpen(i);

    struct object player;
    initObject(0, 0, "gfx/player.png", &player);

    SDL_Event e;
    while (true) {
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) goto exit;
        }

        if (input.controllers_count) {
            int16_t left_x = SDL_JoystickGetAxis(input.controllers[0], 0)/(INT16_MAX/2);
            int16_t left_y = SDL_JoystickGetAxis(input.controllers[0], 1)/(INT16_MAX/2);

            player.rect.x += left_x;
            player.rect.y += left_y;
        }

        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, player.texture, NULL, &player.rect);

        SDL_RenderPresent(renderer);
    }

exit:
    for (int i = 0; i < input.controllers_count; i++) SDL_JoystickClose(input.controllers[i]);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
