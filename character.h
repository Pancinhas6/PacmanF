#ifndef CHARACTER_H
#define CHARACTER_H

class Character {
protected:
    int x, y;

public:
    Character(int startX, int startY);
    virtual ~Character() = default;

    virtual void move(int dx, int dy);
    int getX() const;
    int getY() const;
    void setPosition(int newX, int newY);
};

#endif

