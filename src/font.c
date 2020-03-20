void initFont() {
    font = loadTexture("gfx/font.png", NULL, NULL);
}

void printFont(int x, int y, const char *format, ...) {
    va_list args;
    char buffer[50];

    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);

    for (char i = 0, *c = buffer; *c; i++, c++) {
        SDL_Rect src = {
            .x = FONT_CHAR_WIDTH*((*c - 32) % 19),
            .y = FONT_CHAR_HEIGHT*((*c - 32) / 19),
            .w = FONT_CHAR_WIDTH,
            .h = FONT_CHAR_HEIGHT
        };

        SDL_Rect dst = {
            .x = x + (FONT_CHAR_WIDTH + 1)*i,
            .y = y,
            .w = FONT_CHAR_WIDTH,
            .h = FONT_CHAR_HEIGHT
        };

        SDL_RenderCopy(renderer, font, &src, &dst);
    }
}
