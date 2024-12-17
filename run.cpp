#include "Run.h"
#include <curses.h>

Run::Run(const std::vector<std::string>& layout)
    : map(layout), Pacman(1, 1, map) {
    map.loadMap();
    ghosts.emplace_back(std::make_unique<Ghost>(10, 2, 'G', &map));
    ghosts.emplace_back(std::make_unique<Ghost>(5, 3, 'G', &map));
    ghosts.emplace_back(std::make_unique<Ghost>(3, 1, 'G', &map));
    ghosts.emplace_back(std::make_unique<Ghost>(7, 1, 'G', &map));
    ghosts.emplace_back(std::make_unique<Ghost>(9, 2, 'G', &map));
    lastCollisionTime = std::chrono::steady_clock::now() - std::chrono::milliseconds(500);
}

bool Run::isGameOver() const {
    return Pacman.getVidas() <= 0;
}

void Run::checkCollision() {
    for (const auto& ghost : ghosts) {
        if (Pacman.getX() == ghost->getX() && Pacman.getY() == ghost->getY()) {
            auto now = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastCollisionTime);
            if (elapsed.count() >= 500) {
                Pacman.perderVidas();
                lastCollisionTime = now;
                if (isGameOver()) {
                    return;
                }
            }
        }
    }
}

void Run::draw() const {
    clear();
    map.draw();
    map.drawPoints();

    attron(COLOR_PAIR(1));
    mvprintw(Pacman.getY(), Pacman.getX(), "@");
    attroff(COLOR_PAIR(1));

    for (const auto& ghost : ghosts) {
        ghost->draw();
    }
    attroff(COLOR_PAIR(2));

    mvprintw(map.getHeight() +1, 0, "Pontuacao: %d ", Pacman.getCell());
    mvprintw(map.getHeight()+2, 0, "Vidas: %d", Pacman.getVidas());
    refresh();
}

void Run::handleInput(int ch) {
    if (ch == 'q') {
        endwin();
        exit(0);
    }
    else {
        Pacman.handleInput(ch);
    }
}

void Run::start() {
    initscr();
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);

    bool running = true;
    int ghostMoveTimer = 0;
    const int ghostMoveDelay = 200;
    while (running) {
        draw();
        checkCollision();
        int ch = getch();

        if (ch != ERR) {
            Pacman.handleInput(ch);
            Pacman.movePacman();
        }

        if (Pacman.getVidas() == 0) {
            running == false;
        }

        if (ghostMoveTimer >= ghostMoveDelay) {
            for (auto& ghost : ghosts) {
                ghost->moveGhost();
            }
            ghostMoveTimer = 0;
        }

        ghostMoveTimer += 50;
        napms(50);

        if (isGameOver()) {
            clear();
            mvprintw(0, 0, "Morreste! Pontuacao: %d", Pacman.getCell());
            refresh();
            getch();
            break;
        }
        refresh();
    }
}
