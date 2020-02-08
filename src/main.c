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
#define ZOOM 1
#else
#define ZOOM 3
#endif

#define REFERENCE_SCREEN_WIDTH 480
#define REFERENCE_SCREEN_HEIGHT 272
#define SCREEN_WIDTH ZOOM*480
#define SCREEN_HEIGHT ZOOM*272

SDL_Window *window;
SDL_Renderer *renderer;
float dt;

#include "render.c"
#include "object.c"
#include "bg.c"

bool groundedObject(int index) {
    return (cur_map.tile_hit_types[cur_map.tiles[(int)(objects[index].x + objects[index].rect.w/2)/8][(int)(objects[index].y + objects[index].rect.h)/8]]);
}

#include "input.c"

int main(void) {
#ifdef PSP_BUILD
    PSPSetupCallbacks();
#endif
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER);
    window = SDL_CreateWindow("platform", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

#if 0
#ifndef PSP_BUILD
    SDL_SetHint(SDL_HINT_RENDER_BATCHING, "1");
#endif
#endif
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0xFF, 0xFF);

#ifndef PSP_BUILD
    SDL_RenderSetScale(renderer, ZOOM, ZOOM);
#endif

    controller = SDL_JoystickOpen(0);

    loadBG(1);
    updateBGTexture();

    initObject(0, 10, 10, "gfx/player.png");

    SDL_Event e;
    uint64_t last_frame_counter = SDL_GetPerformanceCounter();
    while (true) {
        {
            uint64_t cur_frame_counter = SDL_GetPerformanceCounter();
            dt = (float)(cur_frame_counter - last_frame_counter) / SDL_GetPerformanceFrequency();
            last_frame_counter = cur_frame_counter;
        }

        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) goto exit;
        }
        handle_constant_input();

        objects[0].speed_y += dt*1;
        if (groundedObject(0) && objects[0].speed_y > 0)
            objects[0].speed_y = 0;
        objects[0].y += objects[0].speed_y;

        objects[0].speed_x *= (1-dt)*0.999;
        if (cur_map.tile_hit_types[cur_map.tiles[(int)objects[0].x/8][(int)objects[0].y/8]] && objects[0].speed_x < 0)
            objects[0].speed_x = 0;
        if (cur_map.tile_hit_types[cur_map.tiles[(int)(objects[0].x + objects[0].rect.w)/8][(int)objects[0].y/8]] && objects[0].speed_x > 0)
            objects[0].speed_x = 0;
        objects[0].x += objects[0].speed_x;

        SDL_RenderClear(renderer);

        SDL_RenderCopy(renderer, cur_map.screen_texture, NULL, NULL);

        for (int i = 0; i < OBJECT_MAX; i++) {
            if (!objects[i].texture) continue;
            objects[i].rect.x = objects[i].x;
            objects[i].rect.y = objects[i].y;
            SDL_RenderCopy(renderer, objects[i].texture, NULL, &objects[i].rect);
        }

        SDL_RenderPresent(renderer);
    }

exit:
    if (controller) SDL_JoystickClose(controller);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
