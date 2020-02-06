SDL_Joystick *controller;

void player_right() {
    objects[0].speed_x += dt*2;
}

void player_left() {
    objects[0].speed_x -= dt*2;
}

void player_up() {
    if (groundedObject(0))
        objects[0].speed_y = -1;
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
