#include<stdexcept>
#include "monotile.h"
#include "player.h"

namespace model {

using std::invalid_argument, std::out_of_range;

// ==================== Constructors ====================

MonoTile::MonoTile() {}

MonoTile::MonoTile(int id, const std::string &name, int payOnStep) :
    id(id), name(name), payOnStep(payOnStep) {

    if (id < 0) throw out_of_range("Tile id cannot be negative.");
    if (payOnStep < 0) throw out_of_range("payOnStep cannot be negative.");
}

// ========================= Methods =========================


void MonoTile::onStep(Player *player) const {
    if (payOnStep > 0)
        player->looseMoney(payOnStep);
}

// ==================== Getters and Setters ====================

int MonoTile::getId() const {
    return id;
}

std::string MonoTile::getName() const {
    return name;
}

int MonoTile::getPayOnStep() const {
    return payOnStep;
}

void MonoTile::setPayOnStep(int newPayOnStep) {
    payOnStep = newPayOnStep;
}

} // namespace model
