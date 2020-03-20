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
        fscanf(map_file, "%s", buffer);
        cur_map.layers_texture[i] = loadTexture(buffer, NULL, NULL);
    }

    for (int y = 0; y < 34; y++) {
        for (int x = 0; x < 60; x++) {
            fscanf(map_file, "%d", (int *)(&cur_map.tiles[x][y]));
        }
    }

    fclose(map_file);
}
