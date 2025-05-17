#pragma once

class Map;

//Class that handles the ghost's position and behavior
class Ghost {
public:
    Ghost(int x, int y);
    void move(const Map& map);
    int getX() const;
    int getY() const;
    bool isAlive() const;
    void setAlive(bool value);
private:
    int x, y;
    bool alive;
};