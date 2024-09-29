#include <assets.h>
#include<stdexcept>
#include "player.h"

namespace model {

using std::out_of_range;


// ============================== Constructor ==============================

Player::Player(const std::string &name, const QColor &color) :
    name(name), color(color),
    money(START_MONEY), location(0), ownedTiles(), outOfJailCards(0),
    jailTurns(0) {
}

// ========================= Getters and Setters =========================

std::string Player::getName() const { return name; }

QColor Player::getColor() const { return color; }

int Player::getMoney() const { return money; }

int Player::getLocation() const { return location; }

OwnableTileList& Player::getOwnedTiles() { return ownedTiles; }

const OwnableTileList& Player::getOwnedTiles() const { return ownedTiles; }

int Player::getOutOfJailCards() const { return outOfJailCards; }

int Player::getJailTurns() const { return jailTurns; }

bool Player::isInJail() const {
    return jailTurns != 0;
}

// ============================== Methods ==============================

void Player::addMoney(int money) {
    if (money < 0)
        throw out_of_range("Money can't be negative.");

    this->money += money;
}

void Player::looseMoney(int money) {
    if (money < 0)
        throw out_of_range("Money can't be negative.");

    this->money -= money;
}

void Player::useGetOutOfJailCard() {
    if (outOfJailCards == 0)
        throw out_of_range("No more 'Get Out of Jail Free' cards left!");
    outOfJailCards--;
}

void Player::addGetOutOfJailCard() {
    outOfJailCards++;
}

void Player::addInJailTurns() {
    jailTurns++;
}

void Player::resetInJailTurs() {
    jailTurns = 0;
}

void Player::move(int steps) {
    location = (location + steps) % Assets::getTileCount();
}

} // namespace model
