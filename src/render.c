void printFont(int x, int y, const char *format, ...);

SDL_Texture *loadTexture(const char *path, int *t_width, int *t_height) {
    int width, height, channels;
    uint8_t *image = stbi_load(path, &width, &height, &channels, STBI_rgb_alpha);
    uint32_t rmask = 0x000000ff;
    uint32_t gmask = 0x0000ff00;
    uint32_t bmask = 0x00ff0000;
    uint32_t amask = 0xff000000;

    if (!image) return NULL;

    if (t_width) *t_width = width;
    if (t_height) *t_height = height;

    SDL_Surface *surf = SDL_CreateRGBSurfaceFrom(image, width, height, STBI_rgb_alpha*8, STBI_rgb_alpha*width, rmask, gmask, bmask, amask);
    if (!surf) {
        stbi_image_free(image);
        return NULL;
    }

    SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);
    stbi_image_free(image);
    return text;
}

void initRender() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER);
    window = SDL_CreateWindow("platform", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0xFF, 0xFF);

#ifndef PSP_BUILD
    SDL_SetHint(SDL_HINT_RENDER_BATCHING, "1");
    SDL_RenderSetScale(renderer, ZOOM, ZOOM);
#else
    PSPSetupCallbacks();
#endif
}

void draw() {
    SDL_RenderClear(renderer);

    for (int i = 0; i < 8; i++) {
        if (cur_map.layers_texture[i]) {
            SDL_RenderCopy(renderer, cur_map.layers_texture[i], NULL, NULL);
        }
    }

    for (int i = 0; i < OBJECT_MAX; i++) {
        if (!objects[i].texture) continue;
        objects[i].rect.x = objects[i].x;
        objects[i].rect.y = objects[i].y;
        SDL_RenderCopy(renderer, objects[i].texture, NULL, &objects[i].rect);
    }

    printFont(4, 4, "%d", (int)(1/dt));

    SDL_RenderPresent(renderer);
}
