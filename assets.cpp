#include<fstream>
#include<vector>
#include<map>
#include<stdexcept>
#include<random>
#include "model/gotile.h"
#include "assets.h"
#include "model/companytile.h"
#include "model/gotojailtile.h"
#include "model/jailtile.h"
#include "model/luckcardtile.h"
#include "model/parkingtile.h"
#include "model/railwaytile.h"
#include "model/taxtile.h"

/** ============================== Assumptions ==============================
 *  Game Board:
 *  - The amount of board tiles MUST be a multiple of 4 and the board is
 *  Square(Not Rectangular).
 *  - The 4 corners(Go, Jail, Parking, Go To Jail) are added after the
 *  loading of the board file.
 */

using namespace model;

using std::ifstream;
using std::string, std::getline, std::isspace, std::to_string;
using std::vector, std::map;
using std::runtime_error, std::exception;
using LuckType = LuckCard::LuckType;


string strTrim(const string &str);
bool strStartsWith(const string &str, const string &start, size_t pos=0);
vector<string> strSplit(const string &str, const string &delim);
int tryParseInt(string &line, const string &argName, const string &filePath, int lineCount);


vector<PropertyColor> Assets::colors;
vector<LuckCard> Assets::chanceCards;
vector<LuckCard> Assets::communityChestCards;
vector<MonoTile*> Assets::tiles;

constexpr char CARD_TYPE_PROFIT[] = "profit";
constexpr char CARD_TYPE_LOSS[] = "loss";
constexpr char CARD_TYPE_JAIL[] = "jail";
constexpr char CARD_TYPE_JAIL_FREE[] = "jail-free";
constexpr char CARD_TYPE_GOTO[] = "goto";

constexpr char SPACE_TYPE_PROPERTY[] = "property";
constexpr char SPACE_TYPE_RAILWAY[] = "railway";
constexpr char SPACE_TYPE_COMPANY[] = "company";
constexpr char SPACE_TYPE_TAX[] = "tax";
constexpr char SPACE_TYPE_CHANCE[] = "chance";
constexpr char SPACE_TYPE_COMMUNITY[] = "community";

// ============================== Init ==============================

void Assets::init() {
    loadAssets();
}

void Assets::release() {
    for(const auto &tile : Assets::tiles) {
        delete tile;
    }
}

// ============================== Load ==============================

void Assets::loadAssets() {
    loadColors(Assets::COLORS_PATH);
    loadMonopolySpaces(Assets::MONOPOLY_SPACES_PATH);
    loadChanceCards(Assets::CHANCE_CARDS_PATH);
    loadCommunityChestCards(Assets::COMMUNITY_CHEST_CARDS_PATH);
}

void Assets::loadColors(const string &filePath) {
    ifstream colorsFile(filePath);

    if (!colorsFile.is_open())
        throw runtime_error("Failed to open " + filePath);

    int lineCount = 0;
    string line;
    while (getline(colorsFile, line)) {
        lineCount++;
        line = strTrim(line);
        // Skip empty lines and comments
        if (line == "" || line[0] == '#') continue;

        size_t colon = line.find(':');
        string name = strTrim(line.substr(0, colon));

        string rgbStr = strTrim(line.substr(colon + 1));
        vector<string> rgb = strSplit(rgbStr, " ");

        if (rgb.size() != 3) throw runtime_error(
            "Error at '" + filePath + "' at line " + to_string(lineCount) + ":\n" +
            "Color must have 3 rgb values"
        );

        int red, green, blue;

        try {
            red = std::stoi(rgb[0]);
        } catch (const exception& ex) {
            throw runtime_error(
                "Error at '" + filePath + "' at line " + to_string(lineCount) + ":\n" +
                "Couldn't convert " + rgb[0] + " to a color"
            );
        }
        try {
            green = std::stoi(rgb[1]);
        } catch (const exception& ex) {
            throw runtime_error(
                "Error at '" + filePath + "' at line " + to_string(lineCount) + ":\n" +
                "Couldn't convert " + rgb[1] + " to a color"
            );
        }
        try {
            blue = std::stoi(rgb[2]);
        } catch (const exception& ex) {
            throw runtime_error(
                "Error at '" + filePath + "' at line " + to_string(lineCount) + ":\n" +
                "Couldn't convert " + rgb[2] + " to a color"
            );
        }

        if (red < 0 | green < 0 || blue < 0 || red > 255 || green > 255 || blue > 255)
            throw runtime_error(
                "Error at '" + filePath + "' at line " + to_string(lineCount) + ":\n" +
                "Color must be between 0-255"
            );

        QColor color(red, green, blue);

        Assets::colors.emplace_back(0, color, name);
    }

    colorsFile.close();
}

void Assets::loadChanceCards(const string &filePath) {
    ifstream file(filePath);

    if (!file.is_open())
        throw runtime_error("Failed to open " + filePath);

    int lineCount = 0;
    string line;
    while (getline(file, line)) {
        lineCount++;
        line = strTrim(line);
        // Skip empty lines and comments
        if (line == "" || line[0] == '#') continue;

        size_t colon = line.find(':');
        if (colon == string::npos) throw runtime_error(
            "Error at '" + filePath + "' at line " + to_string(lineCount) + ":\n" +
            "Missing colon(:)"
        );

        string type = strTrim(line.substr(0, colon));
        line = strTrim(line.substr(colon + 1));

        // No argument types:
        if (type == CARD_TYPE_JAIL) {
            Assets::chanceCards.emplace_back(LuckType::LUCK_JAIL, line);
            continue;
        } else if (type == CARD_TYPE_JAIL_FREE) {
            Assets::chanceCards.emplace_back(LuckType::LUCK_OUT_OF_JAIL_FREE, line);
            continue;
        }

        // Parse argument
        size_t argLen = line.find(' ');
        string argStr = line.substr(0, argLen);
        string name = strTrim(line.substr(argLen + 1));
        int arg;

        // Try parse
        try {
            arg = std::stoi(argStr);
        } catch (const exception& ex) {
            throw runtime_error(
                "Error at '" + filePath + "' at line " + to_string(lineCount) + ":\n" +
                "Couldn't convert " + argStr + " to an integer"
            );
        }

        if (arg < 0)
            throw runtime_error(
                "Error at '" + filePath + "' at line " + to_string(lineCount) + ":\n" +
                type + " argument(=" + to_string(arg) + ") can't be negative"
            );

        // Profit/Loss cards
        if (type == CARD_TYPE_PROFIT) {
            Assets::chanceCards.emplace_back(LuckType::LUCK_PROFIT, name, arg);
            continue;
        } else if (type == CARD_TYPE_LOSS) {
            Assets::chanceCards.emplace_back(LuckType::LUCK_LOSS, name, arg);
            continue;
        }

        // Goto:
        int maxArg = Assets::tiles.size();
        if (arg >= maxArg) throw runtime_error(
            "Error at '" + filePath + "' at line " + to_string(lineCount) + ":\n" +
            "goto index(=" + to_string(arg) + ") must be less than " + to_string(maxArg)
        );

        if (type == CARD_TYPE_GOTO) {
            Assets::chanceCards.emplace_back(LuckType::LUCK_GOTO, name, arg);
            continue;
        }

        throw runtime_error(
            "Error at '" + filePath + "' at line " + to_string(lineCount) + ":\n" +
            "Unknown type: " + type
        );
    }

    file.close();
}

void Assets::loadCommunityChestCards(const string &filePath) {
    ifstream file(filePath);

    if (!file.is_open())
        throw runtime_error("Failed to open " + filePath);

    int lineCount = 0;
    string line;
    while (getline(file, line)) {
        lineCount++;
        line = strTrim(line);
        // Skip empty lines and comments
        if (line == "" || line[0] == '#') continue;

        size_t colon = line.find(':');
        if (colon == string::npos) throw runtime_error(
                "Error at '" + filePath + "' at line " + to_string(lineCount) + ":\n" +
                "Missing colon(:)"
                );

        string type = strTrim(line.substr(0, colon));
        line = strTrim(line.substr(colon + 1));

        // No argument types:
        if (type == CARD_TYPE_JAIL) {
            throw runtime_error(
                "Error at '" + filePath + "' at line " + to_string(lineCount) + ":\n" +
                "No jail cards in community chest."
            );
        } else if (type == CARD_TYPE_JAIL_FREE) {
            Assets::communityChestCards.emplace_back(LuckType::LUCK_OUT_OF_JAIL_FREE, line);
            continue;
        }

        // Parse argument
        size_t argLen = line.find(' ');
        string argStr = line.substr(0, argLen);
        string name = strTrim(line.substr(argLen + 1));
        int arg;

        // Try parse
        try {
            arg = std::stoi(argStr);
        } catch (const exception& ex) {
            throw runtime_error(
                "Error at '" + filePath + "' at line " + to_string(lineCount) + ":\n" +
                "Couldn't convert " + argStr + " to an integer"
                );
        }

        if (arg < 0)
            throw runtime_error(
                "Error at '" + filePath + "' at line " + to_string(lineCount) + ":\n" +
                type + " argument(=" + to_string(arg) + ") can't be negative"
                );

        // Profit/Loss cards
        if (type == CARD_TYPE_PROFIT) {
            Assets::communityChestCards.emplace_back(LuckType::LUCK_PROFIT, name, arg);
            continue;
        } else if (type == CARD_TYPE_LOSS) {
            throw runtime_error(
                "Error at '" + filePath + "' at line " + to_string(lineCount) + ":\n" +
                "No loss cards in community chest."
            );
        }

        // Goto:
        int maxArg = Assets::tiles.size();
        if (arg >= maxArg) throw runtime_error(
                "Error at '" + filePath + "' at line " + to_string(lineCount) + ":\n" +
                "goto index(=" + to_string(arg) + ") must be less than " + to_string(maxArg)
                );

        if (type == CARD_TYPE_GOTO) {
            Assets::communityChestCards.emplace_back(LuckType::LUCK_GOTO, name, arg);
            continue;
        }

        throw runtime_error(
            "Error at '" + filePath + "' at line " + to_string(lineCount) + ":\n" +
            "Unknown type: " + type
            );
    }

    file.close();

}

void Assets::loadMonopolySpaces(const string &filePath) {
    ifstream file(filePath);

    if (!file.is_open())
        throw runtime_error("Failed to open " + filePath);

    // Count non empty lines to find how many spaces are on the board.
    int edgeLength;
    int count = 0;
    string line;
    while (getline(file, line)) {
        line = strTrim(line);
        // Skip empty lines and comments
        if (line == "" || line[0] == '#') continue;
        count++;
    }
    count += 4;
    edgeLength = count / 4;

    file.clear();
    file.seekg(0);

    int boardIndex = -1;
    int lineCount = 0;
    while (getline(file, line)) {
        lineCount++;
        line = strTrim(line);
        // Skip empty lines and comments
        if (line == "" || line[0] == '#') continue;

        boardIndex++;
        if (boardIndex % edgeLength == 0) boardIndex++;

        size_t colon = line.find(':');
        if (colon == string::npos) throw runtime_error(
            "Error at '" + filePath + "' at line " + to_string(lineCount) + ":\n" +
            "Missing colon(:)"
        );

        string type = strTrim(line.substr(0, colon));
        line = strTrim(line.substr(colon + 1));

        if (type != SPACE_TYPE_PROPERTY && type != SPACE_TYPE_RAILWAY &&
            type != SPACE_TYPE_COMPANY && type != SPACE_TYPE_TAX &&
            type != SPACE_TYPE_CHANCE && type != SPACE_TYPE_COMMUNITY) {

            throw runtime_error(
                "Error at '" + filePath + "' at line " + to_string(lineCount) + ":\n" +
                "Unknown type " + type
            );
        }


        // No argument types:
        if (type == SPACE_TYPE_CHANCE) {
            Assets::tiles.push_back(new LuckCardTile(boardIndex, LuckCardTile::CHANCE_TILE));
            continue;
        } else if (type == SPACE_TYPE_COMMUNITY) {
            Assets::tiles.push_back(new LuckCardTile(boardIndex, LuckCardTile::COMMUNITY_CHEST_TILE));
            continue;
        } else if (type == SPACE_TYPE_COMPANY) {
            string name = line;
            Assets::tiles.push_back(new CompanyTile(boardIndex, name));
            continue;
        } else if (type == SPACE_TYPE_RAILWAY) {
            string name = line;
            Assets::tiles.push_back(new RailwayTile(boardIndex, name));
            continue;
        } else if (type == SPACE_TYPE_TAX) {
            int tax = tryParseInt(line, "Tax", filePath, lineCount);
            string name = line;
            Assets::tiles.push_back(new TaxTile(boardIndex, name, tax));
            continue;
        }

        // type = SPACE_TYPE_PROPERTY

        // get color group
        size_t colorLen = line.find(' ');
        string colorStr = line.substr(0, colorLen);

        if (!isColorNameExist(colorStr)) throw runtime_error(
            "Error at '" + filePath + "' at line " + to_string(lineCount) + ":\n" +
            "Color " + colorStr + " is not a valid color"
        );

        PropertyColor color = getColorByName(colorStr);
        line = strTrim(line.substr(colorLen));

        // Get rest of the args:
        int price = tryParseInt(line, "Rent", filePath, lineCount);
        int rent = tryParseInt(line, "Rent", filePath, lineCount);
        int housePrice = tryParseInt(line, "House price", filePath, lineCount);
        int houseRent = tryParseInt(line, "House rent", filePath, lineCount);
        int hotelRent = tryParseInt(line, "Hotel rent", filePath, lineCount);
        string name = line;

        Assets::tiles.push_back(new PropertyTile(boardIndex, name, price,
            color, rent, housePrice, houseRent, hotelRent));
    }

    if (count % 4 != 0) throw runtime_error(
        "Error at '" + filePath + "':\n" +
        "The amount of spaces in the file(="+to_string(count)+") is not a multiple of 4"
    );

    GoTile *go = new GoTile();
    JailTile *jail = new JailTile(edgeLength*1);
    ParkingTile *free_parking = new ParkingTile(edgeLength*2);
    GotoJailTile *goto_jail = new GotoJailTile(edgeLength*3);

    auto pos = Assets::tiles.begin();
    Assets::tiles.insert(pos, go);
    Assets::tiles.insert(pos += edgeLength, jail);
    Assets::tiles.insert(pos += edgeLength, free_parking);
    Assets::tiles.insert(pos += edgeLength, goto_jail);

    file.close();

    // Count colors:
    map<PropertyColor, vector<PropertyTile*>> colorMap;
    for (auto &color : colors)
        colorMap[color] = vector<PropertyTile*>();

    for (auto tile : tiles) {
        if (tile->getType() != MonoTile::TILE_PROPERTY) continue;
        PropertyTile *property = (PropertyTile*) tile;
        PropertyColor color = property->getColor();
        colorMap[color].push_back(property);
    }

    for (auto &color : colors) {
        color.propertyCount = colorMap[color].size();
        for (auto tile : colorMap[color])
            tile->color = color;
    }
}

// ============================== Colors ==============================

const PropertyColor &Assets::getByColorId(int index) {
    return Assets::colors[index];
}

const PropertyColor &Assets::getColorByName(const string &name) {
    for (const auto &color : Assets::colors) {
        if (color.getName() == name) return color;
    }
    throw runtime_error("No color named " + name);
}

bool Assets::isColorNameExist(const std::string &name) {
    for (const auto &color : Assets::colors) {
        if (color.getName() == name) return true;
    }
    return false;
}

size_t Assets::getColorCount() {
    return Assets::colors.size();
}

// ============================== Cards ==============================

// static because there's also `engine` in monopoly.cpp
static std::default_random_engine engine(time(NULL));

const LuckCard &Assets::getRandomChanceCard() {
    std::uniform_int_distribution<size_t> rand(0, Assets::chanceCards.size()-1);
    size_t index = rand(engine);

    return Assets::chanceCards[index];
}

const LuckCard &Assets::getRandomCommunityChestCard() {
    std::uniform_int_distribution<size_t> rand(0, Assets::communityChestCards.size()-1);
    size_t index = rand(engine);

    return Assets::communityChestCards[index];
}


// ============================== Tiles ==============================

MonoTile*const& Assets::getTileById(int index) {
    return Assets::tiles[index];
}

vector<MonoTile *> Assets::getAllTiles() {
    return Assets::tiles;
}

vector<PropertyMonopoly> Assets::getAllMonopolies() {
    map<PropertyColor, vector<PropertyTile*>> map;
    vector<PropertyMonopoly> monopolies;

    for (const auto tile : tiles) {
        if (tile->getType() != MonoTile::TILE_PROPERTY) continue;
        PropertyTile *prop = (PropertyTile*) tile;
        const PropertyColor &color = prop->getColor();

        if (map.find(color) == map.end())
            map[color] = vector<PropertyTile*>();

        map[color].push_back(prop);
    }

    for (const auto &pair : map) {
        PropertyColor color = pair.first;
        vector<PropertyTile*> props = pair.second;
        monopolies.emplace_back(color, props);
    }

    return monopolies;
}

vector<PropertyTile *> Assets::getByColor(const PropertyColor &color) {
    vector<PropertyTile *> list;

    for (auto &tile : Assets::tiles) {
        if (tile->getType() != MonoTile::TILE_PROPERTY) continue;
        PropertyTile* property = (PropertyTile*)tile;
        if (property->getColor() == color)
            list.push_back(property);
    }

    return list;
}

size_t Assets::getTileCount() { return tiles.size(); }

// ============================== Helpers ==============================

string strTrim(const string &str) {
    size_t start = 0, end = str.size() - 1;

    while (start < end && isspace(str[start])) {
        start++;
    }
    if (start == end) return "";

    while (isspace(str[end])) {
        end--;
    }

    return str.substr(start, end - start + 1);
}

bool strStartsWith(const string &str, const string &start, size_t pos) {
    for (size_t i = 0; i < start.size(); i++) {
        if (str[pos + i] != start[i]) return false;
    }
    return true;
}

vector<string> strSplit(const string &str, const string &delim) {
    vector<string> strings;

    size_t prev_pos = 0;
    size_t pos = str.find(delim);
    while(pos != string::npos) {
        strings.push_back(str.substr(prev_pos, pos - prev_pos));

        // Skip extra delimiters
        while (strStartsWith(str, delim, pos))
            pos += delim.size();

        prev_pos = pos;
        pos = str.find(delim, pos);
    }

    if (prev_pos < str.size())
        strings.push_back(str.substr(prev_pos));

    return strings;
}

int tryParseInt(string &line, const string &argName, const string &filePath, int lineCount) {
    // Parse house rent:
    size_t argLen = line.find(' ');
    string argStr = line.substr(0, argLen);
    int arg;

    // Try parse
    try {
        arg = std::stoi(argStr);
    } catch (const exception& ex) {
        throw runtime_error(
            "Error at '" + filePath + "' at line " + to_string(lineCount) + ":\n" +
            "Couldn't convert " + argStr + " to an integer"
        );
    }

    if (arg < 0) throw runtime_error(
        "Error at '" + filePath + "' at line " + to_string(lineCount) + ":\n" +
        argName + " can't be negative"
    );

    line = strTrim(line.substr(argLen));
    return arg;
}
