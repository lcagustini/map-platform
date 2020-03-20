#define FONT_CHAR_WIDTH 7
#define FONT_CHAR_HEIGHT 9

#define OBJECT_MAX 300

#ifdef PSP_BUILD
#define ZOOM 1
#else
#define ZOOM 3
#endif

#define REFERENCE_SCREEN_WIDTH 480
#define REFERENCE_SCREEN_HEIGHT 272
#define SCREEN_WIDTH ZOOM*480
#define SCREEN_HEIGHT ZOOM*272

enum direction {
    D_NONE,
    D_UP,
    D_DOWN,
    D_LEFT,
    D_RIGHT,
};

enum tile_hit_type {
    THT_NONE,
    THT_WALL,
};

struct bg_map {
    enum tile_hit_type tiles[60][34];
    SDL_Texture *layers_texture[8];
};

struct object {
    SDL_Rect rect;
    SDL_Texture *texture;

    float x, y;
    float speed_x, speed_y;
};

struct bg_map cur_map;

SDL_Joystick *controller;

SDL_Texture *font;

struct object objects[OBJECT_MAX];

SDL_Window *window;
SDL_Renderer *renderer;
float dt;
