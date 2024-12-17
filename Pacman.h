#ifndef PACMAN_H
#define PACMAN_H
#include "Map.h"
#include "Character.h"

class Pacman : public Character {
private:
    int dx, dy;
    int Cell;
    Map map;
    int vidas;
    bool canMove(int dx, int dy);

public:
    Pacman(int startX, int startY, Map& Map);
    int getCell() const;
    int getVidas() const;
    void movePacman();
    void perderVidas();
    void handleInput(int input);
};

#endif 
