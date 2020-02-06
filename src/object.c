struct object {
    SDL_Rect rect;
    SDL_Texture *texture;

    float x, y;
    float speed_x, speed_y;
};

#define OBJECT_MAX 300
struct object objects[OBJECT_MAX];

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
