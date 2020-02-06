SDL_Texture *loadTexture(const char *path, int *t_width, int *t_height) {
    int width, height, channels;
    uint8_t *image = stbi_load(path, &width, &height, &channels, STBI_rgb_alpha);
    uint32_t rmask = 0x000000ff;
    uint32_t gmask = 0x0000ff00;
    uint32_t bmask = 0x00ff0000;
    uint32_t amask = 0xff000000;

    if (t_width) *t_width = width;
    if (t_height) *t_height = height;

    SDL_Surface *surf = SDL_CreateRGBSurfaceFrom(image, width, height, STBI_rgb_alpha*8, STBI_rgb_alpha*width, rmask, gmask, bmask, amask);
    if (surf) {
        SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, surf);
        SDL_FreeSurface(surf);
        return text;
    }
    return NULL;
}
