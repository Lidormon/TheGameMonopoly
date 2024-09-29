#include "propertymonopoly.h"

namespace model {

using const_iterator = PropertyMonopoly::const_iterator;
using const_reference = PropertyMonopoly::const_reference;

PropertyMonopoly::PropertyMonopoly(const PropertyColor &color,
const std::vector<PropertyTile*> &properties) :
    color(color), properties(properties) {}

PropertyColor PropertyMonopoly::getColor() const {
    return color;
}

int PropertyMonopoly::getHousePrice() const {
    return properties[0]->getHousePrice();
}

int PropertyMonopoly::getHotelPrice() const {
    return 4 * getHousePrice() + 100;
}

const_iterator PropertyMonopoly::begin() const {
    return properties.begin();
}

const_iterator PropertyMonopoly::end() const {
    return properties.end();
}

const_reference PropertyMonopoly::operator[](int index) const {
    return properties[index];
}

} // namespace model
