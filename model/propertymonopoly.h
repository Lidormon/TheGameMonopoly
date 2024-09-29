#ifndef PROPERTYMONOPOLY_H
#define PROPERTYMONOPOLY_H

#include "model/propertycolor.h"
#include "model/propertytile.h"

namespace model {

class PropertyMonopoly {
public:
    using const_reference = PropertyTile *const &;
    using const_iterator = std::vector<PropertyTile*>::const_iterator;
private:
    PropertyColor color;
    std::vector<PropertyTile*> properties;

public:
    PropertyMonopoly(const PropertyColor &color, const std::vector<PropertyTile*> &properties);

public:
    PropertyColor getColor() const;
    int getHousePrice() const;
    int getHotelPrice() const;

public: // List:
    const_iterator begin() const;
    const_iterator end() const;

    const_reference operator[](int index) const;
};

} // namespace model

#endif // PROPERTYMONOPOLY_H
