#include<stdexcept>
#include "luckcard.h"

namespace model {

using LuckType = LuckCard::LuckType;
using std::out_of_range;

// ========================= Constructor =========================


LuckCard::LuckCard(LuckType type, std::string text, int argument) :
type(type), argument(argument), text(text) {
    if (argument < 0)
        throw out_of_range("LuckCard argument can't be negative.");
}

// ========================= Getters and Setters =========================

LuckType LuckCard::getType() const { return type; }

int LuckCard::getArgument() const { return argument; }

std::string LuckCard::getText() const { return text; }

} // namespace model
