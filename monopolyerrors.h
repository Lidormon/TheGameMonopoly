#ifndef MONOPOLYERRORS_H
#define MONOPOLYERRORS_H

#include <cstddef>
#include <string>

namespace model {
    class Player;
    class MonoTile;
    class OwnableTile;
    class PropertyTile;
}

namespace MonoErrors{

void checkPlayerId(size_t id);
void checkBoardSpaceId(size_t id);

// Game Errors
void throwFinishTurnWithNegativeMoney(const model::Player &player);

void throwCantBuyProperty(
    const model::Player &player, const model::MonoTile *tile,
    const std::string &reason
);
void throwProperty_notOwnable(
    const model::Player &player, const model::MonoTile *tile
);
void throwProperty_cantAfford(
    const model::Player &player, const model::OwnableTile *tile
);
void throwProperty_dontOwn(
    const model::Player &player, const model::OwnableTile *tile
);

void throwFastStart_tooManyPlayers(size_t players);

void throwCantBuySellHouse_dontOwn(
    const model::Player &player, const model::PropertyTile *property
);
void throwCantSellHotel_none(const model::PropertyTile *property);
void throwCantSellHouse_none(const model::PropertyTile *property);

}

#endif // MONOPOLYERRORS_H
