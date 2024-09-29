#include<cmath>
#include <stdexcept>
#include "player.h"
#include "propertytile.h"

namespace model {

using std::pow;
using std::invalid_argument;

// ==================== Constructors ====================

PropertyTile::PropertyTile(int id, const std::string &name, int price,
const PropertyColor& color, int baseRent, int housePrice, int houseRent,
int hotelRent) :
    OwnableTile(id, name, 0, price),
    color(color), baseRent(baseRent), housePrice(housePrice),
    houseRent(houseRent), hotelRent(hotelRent), houseCount(0) {

    if (baseRent < 0) throw invalid_argument("Property rent cannot be negative.");
    if (housePrice < 0) throw invalid_argument("Property house price cannot be negative.");
    if (houseRent < 0) throw invalid_argument("Property rent cannot be negative.");
    if (hotelRent < 0) throw invalid_argument("Property rent cannot be negative.");
}


// ==================== Getters and Setters ====================

const PropertyColor& PropertyTile::getColor() const {
    return color;
}

int PropertyTile::getBaseRent() const {
    return baseRent;
}

int PropertyTile::getHousePrice() const {
    return housePrice;
}

int PropertyTile::getHotelPrice() const {
    return 4*housePrice + 100;
}

int PropertyTile::getHouseRent() const {
    return houseRent;
}

int PropertyTile::getHotelRent() const {
    return hotelRent;
}

int PropertyTile::getHouseCount() const {
    return houseCount;
}

// ==================== Methods ====================

void PropertyTile::buildHouse() {
    if (hasHotel())
        throw std::overflow_error("Cannot build houses when a hotel has "
            "already been built.");
    houseCount++;
}

void PropertyTile::sellHouse() {
    if (houseCount == 0)
        throw std::underflow_error("Cannot sell houses when there are no houses.");
    houseCount--;
}

bool PropertyTile::canBuild() const {
    if (!isOwned()) return false;
    if (houseCount >= HOTEL_HOUSE_COUNT) return false;
    // TODO: After implementing player: Check money.
}

bool PropertyTile::hasHotel() const {
    return houseCount == HOTEL_HOUSE_COUNT;
}

// ==================== MonoTile overrides ====================

void PropertyTile::onStep(Player *player) const {
    if (!isOwned() || owner == player) return;

    int rent;
    if (houseCount == 0) {
        rent = baseRent;
    } else if (houseCount < HOTEL_HOUSE_COUNT) {
        rent = houseRent * (int)pow(2, houseCount-1);
    } else {
        rent = hotelRent;
    }

    player->looseMoney(rent);
    owner->addMoney(rent);
}

MonoTile::TileType PropertyTile::getType() const {
    return MonoTile::TileType::TILE_PROPERTY;
}



} // namespace model
