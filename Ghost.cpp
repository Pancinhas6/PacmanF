#include "Ghost.h"

Ghost::Ghost(int startX, int startY, char appearance, Map* gameMap)
    : Character(startX, startY), appearance(appearance), map(gameMap) {
    srand(static_cast<unsigned>(time(0)));
}


bool Ghost::canMove(int dx, int dy) {
    char cell = map->getCell(dx, dy);
    return (cell != '#');
}

void Ghost::moveGhost() {
    for (int attempt = 0; attempt < 4; ++attempt) {
        int dx = 0, dy = 0;
        int direction = rand() % 4;

        if (direction == 0) {
            dx = 0; dy = -1;
        }
        else if (direction == 1) {
            dx = 0; dy = 1;
        }
        else if (direction == 2) {
            dx = -1; dy = 0;
        }
        else if (direction == 3) {
            dx = 1; dy = 0;
        }

        if (canMove(x + dx, y + dy)) {
            move(dx, dy);
            return;
        }
    }

}

void Ghost::draw() const {
    attron(COLOR_PAIR(2));
    mvprintw(y, x, "%c", appearance);
    attroff(COLOR_PAIR(2));
}
