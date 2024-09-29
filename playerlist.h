#ifndef PLAYERLIST_H
#define PLAYERLIST_H

#include "model/player.h"

class PlayerList {
public:
    using Player = model::Player;

    using iterator = std::vector<Player>::iterator;
    using const_iterator = std::vector<Player>::const_iterator;

private:
    std::vector<Player> players;

public:
    PlayerList(const std::vector<Player> &players);

public: // List methods
    Player& get(int i);
    const Player& get(int i) const;
    void remove(size_t i);

    size_t size() const;

public: // Methods

public: // Iterator
    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

public: // Operators
    Player& operator[](int i);
    const Player& operator[](int i) const;
};

#endif // PLAYERLIST_H
