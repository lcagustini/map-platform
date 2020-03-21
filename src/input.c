void player_right() {
    objects[PLAYER_ID].speed_x += dt*PLAYER_SPEED;
}

void player_left() {
    objects[PLAYER_ID].speed_x -= dt*PLAYER_SPEED;
}

void player_up() {
    if (groundedObject(PLAYER_ID))
        objects[PLAYER_ID].speed_y = -GRAVITY;
}

void handle_constant_input() {
    const uint8_t *kb = SDL_GetKeyboardState(NULL);

    if (kb[SDL_SCANCODE_RIGHT]) player_right();
    if (kb[SDL_SCANCODE_LEFT]) player_left();
    if (kb[SDL_SCANCODE_SPACE]) player_up();

    if (controller) {
        if (SDL_JoystickGetAxis(controller, 0) > 10000)
            player_right();
        if (SDL_JoystickGetAxis(controller, 0) < -10000)
            player_left();
        if (SDL_JoystickGetButton(controller, 0))
            player_up();
    }
}
