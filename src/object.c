bool initObject(int index, float x, float y, const char *texture_path) {
    struct object *obj = &objects[index];

    if (obj->texture) SDL_DestroyTexture(obj->texture);

    obj->texture = loadTexture(texture_path, &obj->rect.w, &obj->rect.h);
    if (obj->texture) {
        obj->rect.x = obj->x = x;
        obj->rect.y = obj->y = y;
        obj->speed_x = obj->speed_y = 0;

        return true;
    }

    return false;
}

bool colidedWithMap(int index) {
    int left_tile = objects[index].x / 8;
    int right_tile = (objects[index].x + objects[index].rect.w) / 8;
    int top_tile = objects[index].y / 8;
    int bottom_tile = (objects[index].y + objects[index].rect.h) / 8;

    if(left_tile < 0) left_tile = 0;
    if(right_tile > 60) right_tile = 60;
    if(top_tile < 0) top_tile = 0;
    if(bottom_tile > 34) bottom_tile = 34;

    for (int i = left_tile; i <= right_tile; i++) {
        for (int j = top_tile; j <= bottom_tile; j++) {
            if (cur_map.tiles[i][j]) return true;
        }
    }
    return false;
}

inline bool groundedObject(int index) {
    return objects[index].speed_y == 0;
}
