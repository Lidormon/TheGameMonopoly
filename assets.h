#ifndef ASSETS_H
#define ASSETS_H

#include "model/luckcard.h"
#include "model/monotile.h"
#include "model/propertycolor.h"
#include "model/propertymonopoly.h"
#include "model/propertytile.h"
#include <string>
#include <vector>

class Assets {
public:
    static constexpr char COLORS_PATH[] = "assets/colors.txt";
    static constexpr char CHANCE_CARDS_PATH[] = "assets/chance.txt";
    static constexpr char COMMUNITY_CHEST_CARDS_PATH[] = "assets/community_chest.txt";
    static constexpr char MONOPOLY_SPACES_PATH[] = "assets/spaces.txt";


    static constexpr char IMAGE_COMMUNITY_CHEST_PATH[] = "assets/images/chest.png";
    static constexpr char IMAGE_DIE1_PATH[] = "assets/images/die1.png";
    static constexpr char IMAGE_DIE2_PATH[] = "assets/images/die2.png";
    static constexpr char IMAGE_DIE3_PATH[] = "assets/images/die3.png";
    static constexpr char IMAGE_DIE4_PATH[] = "assets/images/die4.png";
    static constexpr char IMAGE_DIE5_PATH[] = "assets/images/die5.png";
    static constexpr char IMAGE_DIE6_PATH[] = "assets/images/die6.png";
    static constexpr char IMAGE_ELECTRIC_PATH[] = "assets/images/electric.png";
    static constexpr char IMAGE_GO_PATH[] = "assets/images/go.png";
    static constexpr char IMAGE_GO_TO_JAIL_PATH[] = "assets/images/goto-jail.png";
    static constexpr char IMAGE_HOUSE_PATH[] = "assets/images/house.png";
    static constexpr char IMAGE_HOTEL_PATH[] = "assets/images/hotel.png";
    static constexpr char IMAGE_JAIL_PATH[] = "assets/images/jail.png";
    static constexpr char IMAGE_JAIL_ICON_PATH[] = "assets/images/jail-icon.png";
    static constexpr char IMAGE_FREE_PARIKING_PATH[] = "assets/images/parking.png";
    static constexpr char IMAGE_RAILWAY_PATH[] = "assets/images/railway.png";
    static constexpr char IMAGE_TAX_PATH[] = "assets/images/tax.png";
    static constexpr char IMAGE_WATER_PATH[] = "assets/images/water.png";

private:
    static std::vector<model::PropertyColor> colors;
    static std::vector<model::LuckCard> chanceCards;
    static std::vector<model::LuckCard> communityChestCards;
    static std::vector<model::MonoTile*> tiles;

public:
    static void init();
    static void release();

private:
    static void loadAssets();
    static void loadColors(const std::string &filePath);
    static void loadChanceCards(const std::string &filePath);
    static void loadCommunityChestCards(const std::string &filePath);
    static void loadMonopolySpaces(const std::string &filePath);

public: // Colors
    static const model::PropertyColor& getByColorId(int index);
    static const model::PropertyColor& getColorByName(const std::string &name);
    static bool isColorNameExist(const std::string &name);
    static size_t getColorCount();

public: // Cards
    static const model::LuckCard& getRandomChanceCard();
    static const model::LuckCard& getRandomCommunityChestCard();

public: // Tiles
    static model::MonoTile*const& getTileById(int index);
    static std::vector<model::MonoTile*> getAllTiles();
    static std::vector<model::PropertyMonopoly> getAllMonopolies();
    static std::vector<model::PropertyTile*> getByColor(const model::PropertyColor &color);
    static size_t getTileCount();
};


#endif // ASSETS_H
