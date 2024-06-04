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

void moving(enum Direction direction, SDL_Rect *rect, int stepSize)
{
    if (direction & NORTH)
    {
        rect->y -= stepSize;
    }
    if (direction & SOUTH)
    {
        rect->y += stepSize;
    }
    if (direction & WEST)
    {
        rect->x -= stepSize;
    }
    if (direction & EAST)
    {
        rect->x += stepSize;
    }
}

bool intersect(SDL_Rect rect1, SDL_Rect rect2)
{
    bool inter = SDL_HasIntersection(&rect1, &rect2) == SDL_TRUE;
    return inter;
}

SDL_Rect rangeToRect(Range range)
{
    SDL_Rect target;
    target.h = 50;
    target.w = 50;
    target.x = range.x_start;
    target.y = range.y_start;
    return target;
}

void testRange(SDL_Rect rect, Range range, Range *lastCode)
{
    if (range.info != 1)
    {
        if (intersect(rect, rangeToRect(range)) == true)
        {
            if (lastCode->info == 1 || (range.info > lastCode->info))
                *lastCode = range;
        }
    }
}

void canMove(SDL_Rect rect, enum Direction direction, Range *lastCode)
{
    int i = rect.x / 51.2;
    int j = rect.y / 51.2;

    // printf("ranges: %d, %d\n",i,j);
    lastCode->info = 1;

    if (direction & NORTH)
    {
        testRange(rect, ranges[i][j], lastCode);
        testRange(rect, ranges[i - 1][j], lastCode);
        testRange(rect, ranges[i + 1][j], lastCode);
    }
    if (direction & SOUTH)
    {
        testRange(rect, ranges[i][j + 1], lastCode);
        testRange(rect, ranges[i - 1][j + 1], lastCode);
        testRange(rect, ranges[i + 1][j + 1], lastCode);
    }
    if (direction & WEST)
    {
        testRange(rect, ranges[i][j], lastCode);
        testRange(rect, ranges[i][j - 1], lastCode);
        testRange(rect, ranges[i][j + 1], lastCode);
    }
    if (direction & EAST)
    {
        testRange(rect, ranges[i + 1][j], lastCode);
        testRange(rect, ranges[i + 1][j - 1], lastCode);
        testRange(rect, ranges[i + 1][j + 1], lastCode);
    }
}

#endif //ENTITY_H