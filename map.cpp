#include "Map.h"
#include <curses.h>
#include <iostream>

Map::Map(const std::vector<std::string>& layout) : layout(layout) {
    height = layout.size();
    width = height > 0 ? layout[0].size() : 0;
    loadMap();
}

void Map::removePoint(int x, int y) {
    for (auto it = Cell.begin(); it != Cell.end(); ++it) {
        if (it->x == x && it->y == y) {
            Cell.erase(it);
            break;
        }
    }
}

bool Map::collectPoint(int x, int y) {
    for (auto it = Cell.begin(); it != Cell.end(); ++it) {
        if (it->x == x && it->y == y) {
            Cell.erase(it);
            layout[y][x] = ' ';
            return true;
        }
    }
    return false;
}
void Map::loadMap() {
    Cell.clear();
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (layout[y][x] == '.') {
                Cell.emplace_back(x, y);
            }
        }
    }
}


void Map::draw() const {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (layout[y][x] == '#') {
                mvprintw(y, x, "#");
            }
            else {
                mvprintw(y, x, " ");
            }
        }
    }
}

void Map::drawPoints() const {
    for (const auto& point : Cell) {
        mvprintw(point.y, point.x, ".");
    }
}
char Map::getCell(int x, int y) const {
    if (y >= 0 && y < height && x >= 0 && x < width) {
        return layout[y][x];
    }
    return '#';
}

void Map::setCell(int x, int y, char value) {
    if (y >= 0 && y < height && x >= 0 && x < width) {
        layout[y][x] = value;
    }
}

int Map::getWidth() const {
    return width;
}

int Map::getHeight() const {
    return height;
}

