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

inline bool groundedObject(int index) {
    return objects[index].speed_y == 0;
}

void do_player_physics() {
    objects[PLAYER_ID].speed_x *= (1-dt)*0.99;
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
