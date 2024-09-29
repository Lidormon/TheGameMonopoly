#include<stdexcept>
#include "ownabletile.h"

namespace model {

using std::string;
using std::invalid_argument;

// ==================== Constructors ====================

OwnableTile::OwnableTile() : MonoTile() {}

OwnableTile::OwnableTile(int id, const string &name, int payOnStep, int price) :
    MonoTile(id, name, payOnStep), owner(nullptr), price(price) {

    if (price < 0) throw invalid_argument("Tile price cannot be negative.");
}

// ==================== Getters and Setters ====================

Player *OwnableTile::getOwner() const {
    return owner;
}

void OwnableTile::setOwner(Player *newOwner) {
    owner = newOwner;
}

int OwnableTile::getPrice() const {
    return price;
}

// ==================== MonoTile implementation ====================

bool OwnableTile::isOwnable() const {
    return true;
}

bool OwnableTile::isOwned() const {
    return owner != nullptr;
}

} // namespace model
