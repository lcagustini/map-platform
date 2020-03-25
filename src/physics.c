bool colidedWithMap(int index) {
    int left_tile = objects[index].x / 8;
    int right_tile = (objects[index].x + objects[index].rect.w) / 8;
    int top_tile = objects[index].y / 8;
    int bottom_tile = (objects[index].y + objects[index].rect.h) / 8;

    if (left_tile < 0) {
        goto_left_bg();
        return false;
    }
    if (right_tile >= 60) {
        goto_right_bg();
        return false;
    }
    if (top_tile < 0) {
        goto_top_bg();
        return false;
    }
    if (bottom_tile >= 34) {
        goto_bottom_bg();
        return false;
    }

    for (int i = left_tile; i <= right_tile; i++) {
        for (int j = top_tile; j <= bottom_tile; j++) {
            if (cur_map.tiles[i][j]) return true;
        }
    }
    return false;
}

bool onSolidTile(int index, enum direction dir) {
    bool stopped = false;
    bool wall_on_dir = false;

    int left_tile = objects[index].x / 8;
    int right_tile = (objects[index].x + objects[index].rect.w) / 8;
    int top_tile = objects[index].y / 8;
    int bottom_tile = (objects[index].y + objects[index].rect.h) / 8;

    int offset_tile;
    switch (dir) {
        case D_UP:
            offset_tile = (objects[index].y - 1) / 8;
            for (int i = left_tile; i <= right_tile; i++) {
                wall_on_dir |= cur_map.tiles[i][offset_tile];
            }

            stopped = objects[index].speed_y == 0;
            break;
        case D_DOWN:
            offset_tile = (objects[index].y + objects[index].rect.h + 1) / 8;
            for (int i = left_tile; i <= right_tile; i++) {
                wall_on_dir |= cur_map.tiles[i][offset_tile];
            }

            stopped = objects[index].speed_y == 0;
            break;
        case D_LEFT:
            offset_tile = (objects[index].x - 1) / 8;
            for (int i = top_tile; i <= bottom_tile; i++) {
                wall_on_dir |= cur_map.tiles[offset_tile][i];
            }

            stopped = objects[index].speed_x == 0;
            break;
        case D_RIGHT:
            offset_tile = (objects[index].x + objects[index].rect.w + 1) / 8;
            for (int i = top_tile; i <= bottom_tile; i++) {
                wall_on_dir |= cur_map.tiles[offset_tile][i];
            }

            stopped = objects[index].speed_x == 0;
            break;
        default:
            stopped = wall_on_dir = false;
    }
    return stopped && wall_on_dir;
}

void do_player_physics() {
    objects[PLAYER_ID].speed_y += dt*GRAVITY;

    for (int i = 0; i < PHYSICS_STEPS; i++) {
        float old_pos = objects[PLAYER_ID].y;

        objects[PLAYER_ID].y += dt*objects[PLAYER_ID].speed_y/PHYSICS_STEPS;

        if (colidedWithMap(PLAYER_ID)) {
            objects[PLAYER_ID].speed_y = 0;
            objects[PLAYER_ID].y = old_pos;
            break;
        }
    }

    for (int i = 0; i < PHYSICS_STEPS; i++) {
        float old_pos = objects[PLAYER_ID].x;

        objects[PLAYER_ID].x += dt*objects[PLAYER_ID].speed_x/PHYSICS_STEPS;

        if (colidedWithMap(PLAYER_ID)) {
            objects[PLAYER_ID].speed_x = 0;
            objects[PLAYER_ID].x = old_pos;
            break;
        }
    }
}
