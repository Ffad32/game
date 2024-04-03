
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

entity_move(struct Entity *entity, int dx, int dy) {
    entity->x += dx;
    entity->y += dy;
}
/*entity_render(struct Entity *entity, SDL_Renderer *renderer) {
    // render entity
}*/