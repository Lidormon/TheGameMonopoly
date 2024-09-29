#ifndef PROPERTYTILE_H
#define PROPERTYTILE_H

#include "model/propertycolor.h"
#include "ownabletile.h"

class Assets;

namespace model {

/** Represents a Monopoly board property tile/square. */
class PropertyTile : public OwnableTile {
public:
    /** The maximum amount of houses a player can build on a property. */
    static constexpr int MAX_HOUSE_COUNT = 4;
    /** How many houses are considered an hotel. */
    static constexpr int HOTEL_HOUSE_COUNT = MAX_HOUSE_COUNT + 1;

private:
    /**
     * A color group that the property is a part of. Owning all properties of
     * a color group allows a player to build houses on the color group's
     * properties.
     */
    PropertyColor color;
    /** The amount of rent a player pays the owner without houses. */
    int baseRent;
    /** The price of building a single house. */
    int housePrice;
    /**
     * The base rent each house adds(exponentially) to the rent.
     * The total rent equals to houseRent * 2^[number of houses-1].
     */
    int houseRent;
    /** The amount of rent a player pays the owner with a hotel. */
    int hotelRent;
    /**
     * The amount of houses built on the property. If the amount
     * equals `HOTEL_HOUSE_COUNT` then there's a hotel instead of houses.
     */
    int houseCount;

public:
    PropertyTile(int id, const std::string &name, int price,
    const PropertyColor& color, int baseRent, int housePrice, int houseRent,
    int hotelRent);

public: // Getters & Setters
    const PropertyColor& getColor() const;
    int getBaseRent() const;
    int getHousePrice() const;
    int getHotelPrice() const;
    int getHouseRent() const;
    int getHotelRent() const;
    int getHouseCount() const;

public:
    /** Increase the number of houses by one(Includs building hotel). */
    void buildHouse();
    /** Decrease the number of houses by one(Includs selling hotel). */
    void sellHouse();
    /** Checks whether the owner is able to build a house/hotel.*/
    bool canBuild() const;
    /** Checks whether a hotel is built on the property. */
    bool hasHotel() const;

public: // MonoTile interface
    void onStep(Player *player) const override;
    TileType getType() const override;

    friend class ::Assets;
};

} // namespace model

#endif // PROPERTYTILE_H
