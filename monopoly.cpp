#include "monopoly.h"
#include "model/gotile.h"
#include "model/jailtile.h"
#include "model/luckcardtile.h"
#include "monopolyerrors.h"
#include "view/gamewindow.h"
#include "view/mainmenuwindow.h"
#include "view/playerswindow.h"
#include "assets.h"
#include <QMessageBox>
#include <random>

using namespace model;
using namespace view;
using std::vector;
using std::string, std::to_string;
using std::runtime_error;
using Actions = Monopoly::Actions;

MainMenuWindow* Monopoly::menuWindow = nullptr;
PlayersWindow* Monopoly::playersWindow = nullptr;
GameWindow* Monopoly::gameWindow = nullptr;
int Monopoly::lastDiceThrow = 0;

// static because there's also `engine` in assets.cpp
static std::default_random_engine engine(time(NULL));
std::uniform_int_distribution<int> dice(1, 6);

Monopoly::Monopoly(const std::vector<Player> &players) :
    players(players), playerTurn(0), die1(6), die2(6), canThrowDice(true) {}

void Monopoly::fastStart() {
    if (players.size() > 4)
        MonoErrors::throwFastStart_tooManyPlayers(players.size());

    vector<PropertyMonopoly> monopolies = Assets::getAllMonopolies();
    std::shuffle(monopolies.begin(), monopolies.end(), engine);

    for (int i = 0; i < players.size(); i++) {
        for (auto prop : monopolies[i]) {
            players[i].getOwnedTiles().add(prop);
            prop->setOwner(&players[i]);
            prop->buildHouse();
        }
    }

    vector<MonoTile*> ownables = Assets::getAllTiles();
    // Delete all non OwnableTile tiles and tiles owned after last loop.
    for (int i = 0; i < ownables.size(); i++) {
        if (!ownables[i]->isOwnable() || ownables[i]->isOwned()) {
            ownables.erase(ownables.begin() + i);
            i--;
        }
    }

    std::shuffle(ownables.begin(), ownables.end(), engine);
    for (int i = 0; i < players.size(); i++) {
        OwnableTile *ownable = (OwnableTile*) ownables[i];
        players[i].getOwnedTiles().add(ownable);
        ownable->setOwner(&players[i]);
    }

    for (auto &player : players)
        player.addGetOutOfJailCard();
}

// ========================= Game Methods =========================

void Monopoly::rollDice() {
    die1 = dice(engine);
    die2 = dice(engine);
    lastDiceThrow = die1 + die2;

    Player &player = getCurrentPlayer();
    if (player.isInJail()) {
        canThrowDice = false;
        if (die1 == die2) {
            player.resetInJailTurs();
        } else {
            if (player.getJailTurns() <= JailTile::JAIL_TURNS)
                player.addInJailTurns();
            else {
                player.looseMoney(JailTile::JAIL_PRICE);
                player.resetInJailTurs();
            }
        }
        return;
    }

    if (die1 != die2) {
        canThrowDice = false;
        doubleCounter = 0;
    }
    else if (doubleCounter == 2) {
        int jailId = Assets::getTileCount() / 4;
        player.move(jailId - player.getLocation());
        player.addInJailTurns();
        canThrowDice = false;
    }
    else doubleCounter++;
}

void Monopoly::rollDiceForTest(int die1, int die2) {
    this->die1 = die1;
    this->die2 = die2;
    lastDiceThrow = die1 + die2;

    Player &player = getCurrentPlayer();
    if (player.isInJail()) {
        canThrowDice = false;
        if (die1 == die2) {
            player.resetInJailTurs();
        } else {
            if (player.getJailTurns() <= JailTile::JAIL_TURNS)
                player.addInJailTurns();
            else {
                player.looseMoney(JailTile::JAIL_PRICE);
                player.resetInJailTurs();
            }
        }
        return;
    }

    if (die1 != die2) {
        canThrowDice = false;
        doubleCounter = 0;
    }
    else if (doubleCounter == 2) {
        int jailId = Assets::getTileCount() / 4;
        player.move(jailId - player.getLocation());
        player.addInJailTurns();
        canThrowDice = false;
    }
    else doubleCounter++;
}

void Monopoly::moveCurrentPlayerBy(int steps) {
    Player &player = getCurrentPlayer();
    checkPassGo(player.getLocation(), player.getLocation() + steps);
    player.move(steps);

    MonoTile *tile = Assets::getTileById(player.getLocation());
    tile->onStep(&player);

    switch(tile->getType()) {
    case MonoTile::TILE_PROPERTY: break;
    case MonoTile::TILE_RAILWAY: break;
    case MonoTile::TILE_COMPANY: break;
    case MonoTile::TILE_TAX: break;
    case MonoTile::TILE_LUCK_CARD:
        stepOnLuckCardTile();
        break;
    case MonoTile::TILE_GO: break; // On step handles go.
    case MonoTile::TILE_JAIL: break;
    case MonoTile::TILE_FREE_PARKING: {
        QMessageBox msg;
        msg.setWindowTitle("Free Parking");
        msg.setIcon(QMessageBox::Information);
        msg.setText(
            "You stepped on the free parking tile.\n"
            "Stay a while and relax, your turn has been skipped."
        );
        msg.exec();
        finishTurn();
    } break;
    case MonoTile::TILE_GOTO_JAIL: {
        int jailId = Assets::getTileCount() / 4;
        player.move(jailId - player.getLocation());
        player.addInJailTurns();

        QMessageBox msg;
        msg.setWindowTitle("Go To Jail!");
        msg.setIcon(QMessageBox::Warning);
        msg.setText(
            "You stepped on the go to jail tile.\n"
            "Go to strait to Jail, do not pass Go, do not collect $200."
        );
        msg.exec();
        finishTurn();
    } break;
    }
}

void Monopoly::moveCurrentPlayerTo(size_t boardId) {
    MonoErrors::checkBoardSpaceId(boardId);

    int delta = boardId - getCurrentPlayer().getLocation();
    // newLoc = loc + delta = loc + boardId - loc = boardId
    moveCurrentPlayerBy(delta);
}

void Monopoly::finishTurn() {
    if (getCurrentPlayer().getMoney() < 0)
        MonoErrors::throwFinishTurnWithNegativeMoney(getCurrentPlayer());

    playerTurn = (playerTurn + 1) % players.size();
    canThrowDice = true;
    doubleCounter = 0;
}

Actions Monopoly::getAvailableActions() {
    Actions actions = ActionNone;
    Player &player = getCurrentPlayer();

    if (canThrowDice) actions |= ActionRollDice;

    if (!canThrowDice && player.getMoney() >= 0) actions |= ActionFinishTurn;

    // Check if can buy property;
    MonoTile *tile = Assets::getTileById(player.getLocation());
    if (tile->isOwnable() && !tile->isOwned()) {
        OwnableTile *ownable = (OwnableTile*)tile;
        if (player.getMoney() >= ownable->getPrice())
            actions |= ActionBuyProperty;
    }

    OwnedMonopolies monopolies = player.getOwnedTiles().getOwnedMonopolies();
    // Check if can buy a house
    for (auto &monopoly : monopolies) {
        for (auto &prop : monopoly) {
            if (player.getMoney() >= prop->getHousePrice() && prop->getHouseCount() < 4) {
                actions |= ActionBuyHouse;
                break;
            }
        }
        // No need to continue checking.
        if (actions & ActionBuyHouse) break;
    }

    // Check if can sell a house
    for (auto &monopoly : monopolies) {
        bool hasHotels = false;
        bool hasHouses = false;
        for (auto &prop : monopoly) {
            if (prop->hasHotel()) {
                hasHotels = true;
                break;
            }
            if (prop->getHouseCount() > 0) {
                hasHouses = true;
                break;
            }
        }
        if (hasHouses && !hasHotels) {
            actions |= ActionSellHouse;
            break;
        }
    }

    // Check if can buy Hotel
    for (auto &monopoly : monopolies) {
        bool all4Houses = true;
        bool notAllHotels = false;
        for (auto &prop : monopoly) {
            if (!prop->hasHotel()) notAllHotels = true;
            if (prop->getHouseCount() < 4) all4Houses = false;
        }
        if (all4Houses && notAllHotels){
            actions |= ActionBuyHotel;
            break;
        }
    }

    // Check if can sell a hotel
    for (auto &monopoly : monopolies) {
        for (auto &prop : monopoly) {
            if (prop->hasHotel()) {
                actions |= ActionSellHotel;
                break;
            }
        }
        // No need to continue checking.
        if (actions & ActionSellHotel) break;
    }

    if (player.getOutOfJailCards() > 0 && player.isInJail())
        actions |= ActionUseOutOfJailCard;

    return actions;
}

void Monopoly::buyProperty() {
    Player &player = getCurrentPlayer();
    MonoTile *tile = Assets::getTileById(player.getLocation());
    if (!tile->isOwnable())
        MonoErrors::throwProperty_notOwnable(player, tile);
    OwnableTile *prop = (OwnableTile*) tile;
    if (player.getMoney() < prop->getPrice())
        MonoErrors::throwProperty_cantAfford(player, prop);
    if (prop->isOwned())
        MonoErrors::throwProperty_dontOwn(player, prop);

    player.looseMoney(prop->getPrice());
    prop->setOwner(&player);
    player.getOwnedTiles().add(prop);
}

void Monopoly::buyHouse(model::PropertyTile *property) {
    Player &player = getCurrentPlayer();
    if (property->getOwner() != &player)
        MonoErrors::throwCantBuySellHouse_dontOwn(player, property);

    player.looseMoney(property->getHousePrice());
    property->buildHouse();
}

void Monopoly::sellHouse(model::PropertyTile *property) {
    Player &player = getCurrentPlayer();
    if (property->getOwner() != &player)
        MonoErrors::throwCantBuySellHouse_dontOwn(player, property);
    if (property->getHouseCount() == 0)
        MonoErrors::throwCantSellHouse_none(property);

    player.addMoney(property->getHousePrice() / 2);
    property->sellHouse();
}

void Monopoly::buyHotel(model::PropertyTile *property) {
    Player &player = getCurrentPlayer();
    if (property->getOwner() != &player)
        MonoErrors::throwCantBuySellHouse_dontOwn(player, property);

    player.looseMoney(property->getHotelPrice());
    property->buildHouse();
}

void Monopoly::sellHotel(model::PropertyTile *property) {
    Player &player = getCurrentPlayer();
    if (property->getOwner() != &player)
        MonoErrors::throwCantBuySellHouse_dontOwn(player, property);
    if (!property->hasHotel())
        MonoErrors::throwCantSellHotel_none(property);

    player.addMoney(property->getHotelPrice() / 2);
    property->sellHouse();
}

void Monopoly::useOutOfJailCard() {
    Player &player = getCurrentPlayer();
    if (!player.isInJail()) throw "Not in Jail";
    if (player.getOutOfJailCards() == 0) throw "No cards";

    player.useGetOutOfJailCard();
    player.resetInJailTurs();
}

void Monopoly::playerLooseGame() {
    Player &player = getCurrentPlayer();
    MonoTile *tile = Assets::getTileById(player.getLocation());

    if (tile->isOwned()) {
        Player *owner = tile->getOwner();
        for (auto ownable : player.getOwnedTiles()) {
            ownable->setOwner(owner);
            owner->getOwnedTiles().add(ownable);
        }
    } else {
        for (auto ownable : player.getOwnedTiles())
            ownable->setOwner(nullptr);
    }

    int i = playerTurn;
    players.remove(i);

    playerTurn--;
}

const vector<PropertyTile *> Monopoly::getBuyableHouseProperties() const {
    const Player &player = getCurrentPlayer();
    OwnedMonopolies monopolies = player.getOwnedTiles().getOwnedMonopolies();
    vector<PropertyTile*> props;

    for (auto &monopoly : monopolies) {
        vector<PropertyTile*> temp;
        int houseCount = monopoly[0]->getHouseCount();
        for (auto &prop : monopoly) {
            if (prop->getHouseCount() == houseCount) {
                temp.push_back(prop);
            } else if (prop->getHouseCount() < houseCount) {
                temp.clear();
                houseCount = prop->getHouseCount();
                temp.push_back(prop);
            }
        }
        for (auto prop : temp) props.push_back(prop);
    }

    return props;
}

const vector<PropertyTile *> Monopoly::getSellableHouseProperties() const {
    const Player &player = getCurrentPlayer();
    OwnedMonopolies monopolies = player.getOwnedTiles().getOwnedMonopolies();
    vector<PropertyTile*> props;

    for (auto &monopoly : monopolies) {
        vector<PropertyTile*> temp;
        int houseCount = monopoly[0]->getHouseCount();
        for (auto &prop : monopoly) {
            if (prop->getHouseCount() == houseCount) {
                temp.push_back(prop);
            } else if (prop->getHouseCount() > houseCount) {
                temp.clear();
                houseCount = prop->getHouseCount();
                temp.push_back(prop);
            }
        }
        if (houseCount == PropertyTile::HOTEL_HOUSE_COUNT) continue;
        for (auto prop : temp) props.push_back(prop);
    }

    return props;
}

const vector<PropertyTile *> Monopoly::getBuyableHotelProperties() const {
    const Player &player = getCurrentPlayer();
    OwnedMonopolies monopolies = player.getOwnedTiles().getOwnedMonopolies();
    vector<PropertyTile*> props;

    for (auto &monopoly : monopolies) {
        bool all4Houses = true;
        for (auto &prop : monopoly) {
            if (!prop->hasHotel() && prop->getHouseCount() < 4) {
                all4Houses = false;
                break;
            }
        }
        if (!all4Houses) continue;
        for (auto &prop : monopoly)
            if (!prop->hasHotel())
                props.push_back(prop);
    }

    return props;
}

const vector<PropertyTile *> Monopoly::getSellableHotelProperties() const {
    const Player &player = getCurrentPlayer();
    OwnedMonopolies monopolies = player.getOwnedTiles().getOwnedMonopolies();
    vector<PropertyTile*> props;

    for (auto &monopoly : monopolies) {
        for (auto &prop : monopoly)
            if (prop->hasHotel())
                props.push_back(prop);
    }

    return props;
}

void Monopoly::checkPassGo(size_t boardId, size_t newBoardId) {
    MonoErrors::checkBoardSpaceId(boardId);

    // If ON go.
    if (newBoardId == 0) return;
    // 37 + 10
    // Opt1: 7
    // Opt2: 47
    if (newBoardId < boardId || newBoardId > Assets::getTileCount())
        getCurrentPlayer().addMoney(GoTile::PASS_REWARD);
}

void Monopoly::stepOnLuckCardTile() {
    Player &player = getCurrentPlayer();
    LuckCardTile *tile = (LuckCardTile*) Assets::getTileById(player.getLocation());

    bool isChance = tile->getName() == LuckCardTile::CHANCE;
    LuckCard card = (isChance) ?
        Assets::getRandomChanceCard() :
        Assets::getRandomCommunityChestCard();
    gameWindow->displayLuckCard(card, isChance);

    switch(card.getType()) {
    case LuckCard::LUCK_PROFIT:
        player.addMoney(card.getArgument());
        break;
    case LuckCard::LUCK_LOSS:
        player.looseMoney(card.getArgument());
        break;
    case LuckCard::LUCK_JAIL: {
        int jailId = Assets::getTileCount() / 4;
        player.move(jailId - player.getLocation());
        player.addInJailTurns();
        finishTurn();
    } break;
    case LuckCard::LUCK_OUT_OF_JAIL_FREE:
        player.addGetOutOfJailCard();
        break;
    case LuckCard::LUCK_GOTO:
        moveCurrentPlayerTo(card.getArgument());
    }
}

// ========================= Getters and Setters =========================

const PlayerList &Monopoly::getPlayers() const {
    return players;
}

int Monopoly::getPlayerTurn() const { return playerTurn; }

const Player &Monopoly::getCurrentPlayer() const {
    return players[playerTurn];
}

Player &Monopoly::getCurrentPlayer() {
    return players[playerTurn];
}

int Monopoly::getDie1() const { return die1; }

int Monopoly::getDie2() const { return die2; }

int Monopoly::getLastRoll() const { return die1+die2; }

int Monopoly::getLastDiceRoll() { return lastDiceThrow; }

// ========================= Action Operators =========================

Actions operator| (Actions lhs, Actions rhs) {
    return (Actions) ((unsigned)lhs | (unsigned)rhs);
}
Actions operator|= (Actions &lhs, Actions rhs) {
    return lhs = lhs | rhs;
}
Actions operator& (Actions lhs, Actions rhs) {
    return (Actions) ((unsigned)lhs & (unsigned)rhs);
}
