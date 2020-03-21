#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define STB_TRUETYPE_IMPLEMENTATION
#include <stb_truetype.h>

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
//#define printf	pspDebugScreenPrintf
#endif

#include "common.h"
#include "render.c"
#include "font.c"
#include "bg.c"
#include "object.c"
#include "physics.c"
#include "input.c"

int main(void) {
    initRender();

    controller = SDL_JoystickOpen(0);

    initFont();
    loadWorldMap();
    loadBG(1);

    initObject(PLAYER_ID, 10, 10, "gfx/player.png");

    SDL_Event e;
    uint64_t last_frame_counter = SDL_GetPerformanceCounter();
    while (true) {
        uint64_t cur_frame_counter = SDL_GetPerformanceCounter();
        dt = (float)(cur_frame_counter - last_frame_counter) / SDL_GetPerformanceFrequency();
        last_frame_counter = cur_frame_counter;

        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) goto exit;
        }
        handle_constant_input();

        do_player_physics();

        draw();
    }

exit:
    if (controller) SDL_JoystickClose(controller);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
