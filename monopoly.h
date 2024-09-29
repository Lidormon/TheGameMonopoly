#ifndef MONOPOLY_H
#define MONOPOLY_H

#include "model/luckcard.h"
#include "playerlist.h"

namespace view {
class MainMenuWindow;
class PlayersWindow;
class GameWindow;
}

constexpr size_t MAX_PLAYERS = 8;

class Monopoly {
public:
    enum Actions {
        ActionNone = 0,
        ActionRollDice = 1 << 0,
        ActionFinishTurn = 1 << 1,
        ActionBuyProperty = 1 << 2,
        ActionBuyHouse = 1 << 3,
        ActionSellHouse = 1 << 4,
        ActionBuyHotel = 1 << 5,
        ActionSellHotel = 1 << 6,
        ActionUseOutOfJailCard = 1 << 7
    };
private:
    PlayerList players;
    /**The index of the player who's turn it currently is.*/
    int playerTurn;
    int die1, die2;
    bool canThrowDice;
    int doubleCounter;
    static int lastDiceThrow;

public:
    static view::MainMenuWindow *menuWindow;
    static view::PlayersWindow *playersWindow;
    static view::GameWindow *gameWindow;

public:
    Monopoly(const std::vector<model::Player> &players);

public: // Game methods.
    void fastStart();

    void rollDice();
    // Only for tests:
    void rollDiceForTest(int die1, int die2);
    void moveCurrentPlayerBy(int steps);
    void moveCurrentPlayerTo(size_t boardId);
    void finishTurn();
    Actions getAvailableActions();
    void buyProperty();
    void buyHouse(model::PropertyTile *property);
    void sellHouse(model::PropertyTile *property);
    void buyHotel(model::PropertyTile *property);
    void sellHotel(model::PropertyTile *property);
    void useOutOfJailCard();
    void playerLooseGame();

    const std::vector<model::PropertyTile*> getBuyableHouseProperties() const;
    const std::vector<model::PropertyTile*> getSellableHouseProperties() const;
    const std::vector<model::PropertyTile*> getBuyableHotelProperties() const;
    const std::vector<model::PropertyTile*> getSellableHotelProperties() const;

private:
    void checkPassGo(size_t boardId, size_t newBoardId);
    // void extracted(model::LuckCard &card); - ???
    void stepOnLuckCardTile();

public:
    const PlayerList& getPlayers() const;
    int getPlayerTurn() const;
    const model::Player& getCurrentPlayer() const;
    model::Player& getCurrentPlayer();
    int getDie1() const;
    int getDie2() const;
    int getLastRoll() const;
    static int getLastDiceRoll();
};

#endif // MONOPOLY_H

Monopoly::Actions operator| (Monopoly::Actions lhs, Monopoly::Actions rhs);
Monopoly::Actions operator|= (Monopoly::Actions &lhs, Monopoly::Actions rhs);
Monopoly::Actions operator& (Monopoly::Actions lhs, Monopoly::Actions rhs);
