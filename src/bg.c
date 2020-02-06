enum tile_hit_type {
    THT_NONE,
    THT_WALL,
};

struct bg_map {
    uint8_t tiles[60][34];
    SDL_Texture *tile_textures[256];
    enum tile_hit_type tile_hit_types[256];
};

struct bg_map cur_map;

bool loadBG(int index) {
    cur_map.tile_textures[0] = loadTexture("gfx/brick.png", NULL, NULL);
    cur_map.tile_hit_types[0] = THT_WALL;

    cur_map.tile_textures[1] = loadTexture("gfx/wall.png", NULL, NULL);
    cur_map.tile_hit_types[1] = THT_NONE;

    for (int y = 0; y < 34; y++) {
        for (int x = 0; x < 60; x++) {
            if (y % 33 && x % 59) cur_map.tiles[x][y] = 1;
            else cur_map.tiles[x][y] = 0;
        }
    }

    return true;
}
