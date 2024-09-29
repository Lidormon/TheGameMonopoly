#include "playerlist.h"

using model::Player;
using iterator = PlayerList::iterator;
using const_iterator = PlayerList::const_iterator;

// ========================= Constructor =========================

PlayerList::PlayerList(const std::vector<Player> &players) : players(players) {}

// ========================= List methods =========================

Player& PlayerList::get(int i) {
    return players[i];
}

const Player& PlayerList::get(int i) const {
    return players[i];
}

void PlayerList::remove(size_t i) {
    players.erase(players.begin() + i);
}

size_t PlayerList::size() const {
    return players.size();
}

// ========================= Methods =========================


// ========================= Iterator =========================

iterator PlayerList::begin() {
    return players.begin();
}

const_iterator PlayerList::begin() const {
    return players.begin();
}

iterator PlayerList::end() {
    return players.end();
}

const_iterator PlayerList::end() const {
    return players.end();
}


// ========================= Operators =========================

Player& PlayerList::operator[](int i) {
    return players[i];
}

const Player& PlayerList::operator[](int i) const {
    return players[i];
}
