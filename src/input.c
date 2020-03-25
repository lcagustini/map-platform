void player_right() {
    if (objects[PLAYER_ID].speed_x < PLAYER_MAX_SPEED) {
        objects[PLAYER_ID].speed_x += dt*PLAYER_SPEED;
    }
}

void player_left() {
    if (objects[PLAYER_ID].speed_x > -PLAYER_MAX_SPEED) {
        objects[PLAYER_ID].speed_x -= dt*PLAYER_SPEED;
    }
}

void player_jump() {
    if (onSolidTile(PLAYER_ID, D_DOWN)) {
        objects[PLAYER_ID].speed_y = -PLAYER_JUMP_SPEED;
        return;
    }
    if (onSolidTile(PLAYER_ID, D_RIGHT)) {
        objects[PLAYER_ID].speed_y = -PLAYER_WALL_JUMP_SPEED_Y;
        objects[PLAYER_ID].speed_x = -PLAYER_WALL_JUMP_SPEED_X;
    }
    if (onSolidTile(PLAYER_ID, D_LEFT)) {
        objects[PLAYER_ID].speed_y = -PLAYER_WALL_JUMP_SPEED_Y;
        objects[PLAYER_ID].speed_x = PLAYER_WALL_JUMP_SPEED_X;
    }
}

void handle_constant_input() {
    const uint8_t *kb = SDL_GetKeyboardState(NULL);

    if (kb[SDL_SCANCODE_SPACE]) player_jump();
    if (kb[SDL_SCANCODE_RIGHT] || kb[SDL_SCANCODE_LEFT]) {
        if (kb[SDL_SCANCODE_RIGHT]) player_right();
        else player_left();
    }
    else {
        objects[PLAYER_ID].speed_x *= (1-dt)*0.9;
    }

    if (controller) {
        if (SDL_JoystickGetAxis(controller, 0) > 10000)
            player_right();
        if (SDL_JoystickGetAxis(controller, 0) < -10000)
            player_left();
        if (SDL_JoystickGetButton(controller, 0))
            player_jump();
    }
}
