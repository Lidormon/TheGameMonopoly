#include<stdexcept>
#include<string>
#include "monopolyerrors.h"
#include "assets.h"
#include "monopoly.h"

using std::out_of_range, std::runtime_error;
using std::string, std::to_string;

namespace MonoErrors {

void checkPlayerId(size_t id) {
    if (id < 0 || id >= MAX_PLAYERS) {
        throw out_of_range("Player id must be 0-7. Got: " + to_string(id));
    }
}

void checkBoardSpaceId(size_t id) {
    size_t max = Assets::getTileCount() - 1;
    if (id < 0 || id > max) {
        throw out_of_range(
            "Board space id must be 0-" + to_string(max) +
            ". Got: " + to_string(id)
        );
    }
}

void throwFinishTurnWithNegativeMoney(const model::Player &player) {
    string error =
        "Player can't finish turn with negative money.\n"
        "\tPlayer '" + player.getName() + "' has " +
        to_string(player.getMoney()) + " money!";
    throw runtime_error(error);
}

void throwCantBuyProperty(const model::Player &player,
const model::MonoTile *tile, const std::string &reason) {
    string pName = player.getName(), tName = tile->getName();
    string error =
        "Player '" + pName + "' can't buy '" + tName + "'.\n"
        "Reason: " + reason;
    throw runtime_error(error);
}

void throwProperty_notOwnable(
const model::Player &player, const model::MonoTile *tile) {
    throwCantBuyProperty(player, tile, "Not buyable.");
}

void throwProperty_cantAfford(
const model::Player &player, const model::OwnableTile *tile) {
    string cost = to_string(tile->getPrice());
    string money = to_string(player.getMoney());
    string reason = "Not enough money. Needed: " + cost + ", has: " + money;
    throwCantBuyProperty(player, tile, reason);
}

void throwProperty_dontOwn(
const model::Player &player, const model::OwnableTile *tile) {
    string owner = tile->getOwner()->getName();
    string reason = "Already owned by '" + owner + "'.";
    throwCantBuyProperty(player, tile, reason);
}

void throwFastStart_tooManyPlayers(size_t players) {
    string err = "Can't play a 'Fast Start' with " + to_string(players) +
                 " players. Max 4 players.";
    throw runtime_error(err);
}

void throwCantBuySellHouse_dontOwn(
const model::Player &player, const model::PropertyTile *property) {
    string pName = player.getName(), tName = property->getName();
    string err = "Player '" + pName + "' doesn't own '" + tName + "'.";
    throw runtime_error(err);
}

void throwCantSellHotel_none(const model::PropertyTile *property) {
    string name = property->getName();
    string err = "Can't sell hotel on '" + name + "' because it has no hotels.";
    throw runtime_error(err);
}

void throwCantSellHouse_none(const model::PropertyTile *property) {
    string name = property->getName();
    string err = "Can't sell house on '" + name + "' because it has no houses.";
    throw runtime_error(err);
}

} // namespace MonoErrors

