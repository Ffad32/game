#ifdef ENTITY_H
#error entity.h is already included
#endif
#define ENTITY_H

enum Direction {
    NORTH,
    SOUTH,
    WEST,
    EAST
};

enum Status {
    HOLD,
    MOVING,
};

struct Entity {
    // state
    enum Status status;

    // position
    int x;
    int y;
    enum Direction direction;
    enum Direction nextStep;
};

void entity_move(struct Entity *entity, int dx, int dy) {
    entity->x += dx;
    entity->y += dy;
}
/*entity_render(struct Entity *entity, SDL_Renderer *renderer) {
    // render entity
}*/