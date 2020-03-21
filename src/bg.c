void loadWorldMap() {
    FILE *map_file = fopen("resources/worldmap", "r");

    char dir;
    int src, dst;
    while (fscanf(map_file, "%d %c %d", &src, &dir, &dst) != EOF) {
        switch (dir) {
            case 'r':
                map_array[src].right = dst;
                break;
            case 'l':
                map_array[src].left = dst;
                break;
            case 't':
                map_array[src].top = dst;
                break;
            case 'b':
                map_array[src].bottom = dst;
                break;
        }
    }
}

void loadBG(int index) {
    char buffer[50];

    sprintf(buffer, "resources/%02d.map", index);
    FILE *map_file = fopen(buffer, "r");

    int layer_amount;
    fscanf(map_file, "%d", &layer_amount);

    for (int i = 0; i < 8; i++) {
        if (cur_map.layers_texture[i]) SDL_DestroyTexture(cur_map.layers_texture[i]);
        cur_map.layers_texture[i] = NULL;
    }

    for (int i = 0; i < layer_amount; i++) {
        sprintf(buffer, "gfx/%02d_layer%1d.png", index, i);
        cur_map.layers_texture[i] = loadTexture(buffer, NULL, NULL);
    }

    for (int y = 0; y < 34; y++) {
        for (int x = 0; x < 60; x++) {
            fscanf(map_file, "%d", (int *)(&cur_map.tiles[x][y]));
        }
    }
    cur_map.id = index;

    fclose(map_file);
}

void goto_left_bg() {
    objects[PLAYER_ID].x = 456;
    loadBG(map_array[cur_map.id].left);
}

void goto_right_bg() {
    objects[PLAYER_ID].x = 8;
    loadBG(map_array[cur_map.id].right);
}

void goto_bottom_bg() {
    objects[PLAYER_ID].y = 8;
    loadBG(map_array[cur_map.id].bottom);
}

void goto_top_bg() {
    objects[PLAYER_ID].y = 232;
    loadBG(map_array[cur_map.id].top);
}
