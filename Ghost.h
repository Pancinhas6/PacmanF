#ifndef GHOST_H
#define GHOST_H

#include "Map.h"
#include "Character.h"
#include <cstdlib>
#include <ctime>
#include <curses.h>

class Ghost : public Character {
private:
    char appearance;
    Map* map;
    bool canMove(int dx, int dy);

public:
    Ghost(int startX, int startY, char appearance, Map* gameMap);
    void moveGhost();
    void draw() const;
};

#endif


