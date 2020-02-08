enum tile_hit_type {
    THT_NONE,
    THT_WALL,
};

struct bg_map {
    uint8_t tiles[60][34];
    SDL_Texture *tile_textures[256];
    enum tile_hit_type tile_hit_types[256];
    SDL_Texture *screen_texture;
};

struct bg_map cur_map;

void loadBG(int index) {
    char buffer[50];

    sprintf(buffer, "resources/maps/%02d.map", index);
    FILE *map_file = fopen(buffer, "r");

    int texture_amount;
    fscanf(map_file, "%d", &texture_amount);

    for (int i = 0; i < texture_amount; i++) {
        fscanf(map_file, "%s", buffer);
        cur_map.tile_textures[i] = loadTexture(buffer, NULL, NULL);
        fscanf(map_file, "%d", &cur_map.tile_hit_types[i]);
    }

    for (int y = 0; y < 34; y++) {
        for (int x = 0; x < 60; x++) {
            fscanf(map_file, "%hhd", &cur_map.tiles[x][y]);
        }
    }

    if (!cur_map.screen_texture) {
        cur_map.screen_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, REFERENCE_SCREEN_WIDTH, REFERENCE_SCREEN_HEIGHT);
    }
}

void updateBGTexture() {
    SDL_SetRenderTarget(renderer, cur_map.screen_texture);
    for (int y = 0; y < 34; y++) {
        for (int x = 0; x < 60; x++) {
            SDL_Rect target = {.x = x*8, .y = y*8, .w = 8, .h = 8};
            SDL_RenderCopy(renderer, cur_map.tile_textures[cur_map.tiles[x][y]], NULL, &target);
        }
    }
    SDL_SetRenderTarget(renderer, NULL);
}
