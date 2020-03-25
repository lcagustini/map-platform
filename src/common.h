#define FONT_CHAR_WIDTH 7
#define FONT_CHAR_HEIGHT 9

#define PLAYER_ID 0
#define PLAYER_SPEED 100
#define PLAYER_MAX_SPEED 120
#define PLAYER_JUMP_SPEED 0.5*GRAVITY
#define PLAYER_WALL_JUMP_SPEED_Y 0.7*GRAVITY
#define PLAYER_WALL_JUMP_SPEED_X 0.5*PLAYER_SPEED

#define OBJECT_MAX 300
#define MAPS_MAX 10

#define GRAVITY 150
#define PHYSICS_STEPS 5

#define ZOOM 3

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
    int id;
    enum tile_hit_type tiles[60][34];
    SDL_Texture *layers_texture[8];
};

struct world_map {
    int id;
    int top, bottom, left, right;
};

struct object {
    SDL_Rect rect;
    SDL_Texture *texture;

    float x, y;
    float speed_x, speed_y;
};

struct bg_map cur_map;
struct world_map map_array[MAPS_MAX];

SDL_Joystick *controller;

SDL_Texture *font;

struct object objects[OBJECT_MAX];

SDL_Window *window;
SDL_Renderer *renderer;
float dt;
