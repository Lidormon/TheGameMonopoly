#ifndef MONOTILE_H
#define MONOTILE_H

#include<string>

namespace model {

class Player;

/** Represents a Monopoly board tile/square. */
class MonoTile {
public:
    enum TileType {
        TILE_PROPERTY, TILE_RAILWAY, TILE_COMPANY, TILE_TAX, TILE_LUCK_CARD,
        TILE_GO, TILE_JAIL, TILE_FREE_PARKING, TILE_GOTO_JAIL
    };
protected:
    /** The position of the tile on the board. */
    int id;
    /** The name of the tile. E.g. "New York Ave." */
    std::string name;
    /** The amount of money a player must pay when stepping on the tile. */
    int payOnStep;

protected:
    MonoTile();

public:
    MonoTile(int id, const std::string &name, int payOnStep);
    virtual ~MonoTile() {};

public:
    int getId() const;
    std::string getName() const;
    int getPayOnStep() const;
    void setPayOnStep(int newPayOnStep);

public:
    // TODO: Maybe not const.
    /** Event of a player stepping on the tile. */
    virtual void onStep(Player *player) const;

    virtual TileType getType() const = 0;

    virtual bool isOwnable() const = 0;
    virtual bool isOwned() const = 0;
    virtual Player* getOwner() const = 0;
};

} // namespace model

#endif // MONOTILE_H
