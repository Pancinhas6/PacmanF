#ifndef RUN_H
#define RUN_H

#include "Map.h"
#include "PacMan.h"
#include "Ghost.h"
#include <vector>
#include <memory>
#include <chrono>

class Run {
private:
    Map map;
    Pacman Pacman;
    std::vector<std::unique_ptr<Ghost>> ghosts;
    void handleInput(int ch);
    std::chrono::steady_clock::time_point lastCollisionTime;

public:
    Run(const std::vector<std::string>& layout);
    void checkCollision();
    bool isGameOver() const;
    void start();
    void draw() const;
};

#endif
