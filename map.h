#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>

struct Point {
    int x, y;
    bool active;
    Point(int x, int y) : x(x), y(y) {}
};

class Map {
private:
    std::vector<std::string> layout;
    std::vector<Point> Cell;
    int width;
    int height;

public:
    Map(const std::vector<std::string>& layout); 
    void loadMap();
    void removePoint(int x, int y);
    void draw() const;
    char getCell(int x, int y) const;
    void setCell(int x, int y, char value);
    bool collectPoint(int x, int y);
    void drawPoints() const;
    int getWidth() const;
    int getHeight() const;
};
#endif


