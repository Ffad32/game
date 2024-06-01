#ifndef ENTITY_H
#define ENTITY_H

enum Direction {
    NONE = 0b0000,
    NORTH = 0b001,
    SOUTH = 0b010,
    WEST = 0b100,
    EAST = 0b1000,

    NORTH_WEST = NORTH | WEST,
    NORTH_EAST = NORTH | EAST,
    SOUTH_WEST = SOUTH | WEST,
    SOUTH_EAST = SOUTH | EAST
};

enum Status {
    HOLD,
    MOVING,
    DIALOGUE,
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

#endif //ENTITY_H