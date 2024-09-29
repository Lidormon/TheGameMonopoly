#include<QApplication>
#include<cstdio>
#include<vector>
#include "doctest.h"
#include "assets.h"
#include "model/gotile.h"
#include "model/player.h"
#include "model/railwaytile.h"
#include "model/taxtile.h"
#include "monopoly.h"

using namespace model;
using std::vector;

TEST_CASE("Model Tests") {
    SUBCASE("Player Tests") {
        Player p("Lidor", Qt::black);

        // Before:
        CHECK(p.getName() == "Lidor");
        CHECK(p.getColor() == Qt::black);
        CHECK(p.getMoney() == Player::START_MONEY);
        CHECK(p.getJailTurns() == 0);
        CHECK(p.getOutOfJailCards() == 0);
        CHECK(!p.isInJail());
        CHECK(p.getLocation() == 0);

        //Changes:
        p.addMoney(300);
        p.addGetOutOfJailCard();
        p.addGetOutOfJailCard();
        p.addInJailTurns();
        p.move(12);
        p.move(6);
        p.move(10);

        CHECK(p.getMoney() == Player::START_MONEY + 300);
        CHECK(p.getOutOfJailCards() == 2);
        CHECK(p.isInJail());
        CHECK(p.getJailTurns() == 1);
        CHECK(p.getLocation() == 28);

        p.looseMoney(100);
        p.useGetOutOfJailCard();
        p.resetInJailTurs();
        p.move(10);
        // Wrap back to 8
        p.move(10);

        CHECK(p.getMoney() == Player::START_MONEY + 200);
        CHECK(p.getOutOfJailCards() == 1);
        CHECK(!p.isInJail());
        CHECK(p.getJailTurns() == 0);
        CHECK(p.getLocation() == 8);


        CHECK_NOTHROW(p.useGetOutOfJailCard());
        // Now there are 0 cards:
        CHECK_THROWS(p.useGetOutOfJailCard());
        CHECK_THROWS(p.addMoney(-100));
        CHECK_THROWS(p.looseMoney(-100));
    }

    SUBCASE("Tile Step Tests") {
        Player player("Lidor", Qt::black);
        Player enemy("Severus Snape", Qt::white);

        // Also polymorphism test on the way
        PropertyColor pink(3, QColorConstants::Svg::pink, "pink");
        MonoTile *go = new GoTile();
        MonoTile *prop1 = new PropertyTile(1, "Unclaimed", 100, pink, 6, 50, 20, 1000);
        MonoTile *prop2 = new PropertyTile(2, "Owned by Player", 101, pink, 7, 51, 21, 1001);
        MonoTile *prop3 = new PropertyTile(3, "Owned by enemy", 102, pink, 8, 52, 22, 1002);
        MonoTile *tax = new TaxTile(4, "Test Tax", 50);
        MonoTile *trains[] = {
            new RailwayTile(5, "Unclaimed Train"),
            new RailwayTile(6, "Player Train"),
            new RailwayTile(7, "Enemy Train"),
            new RailwayTile(8, "Enemy Train 2"),
        };

        player.getOwnedTiles().add((OwnableTile*)prop2);
        player.getOwnedTiles().add((OwnableTile*)trains[1]);
        ((OwnableTile*)prop2)->setOwner(&player);
        ((OwnableTile*)trains[1])->setOwner(&player);

        enemy.getOwnedTiles().add((OwnableTile*)prop3);
        enemy.getOwnedTiles().add((OwnableTile*)trains[2]);
        enemy.getOwnedTiles().add((OwnableTile*)trains[3]);
        ((OwnableTile*)prop3)->setOwner(&enemy);
        ((OwnableTile*)trains[2])->setOwner(&enemy);
        ((OwnableTile*)trains[3])->setOwner(&enemy);

        player.looseMoney(Player::START_MONEY - 100);
        enemy.looseMoney(Player::START_MONEY - 100);
        CHECK(player.getMoney() == 100);
        CHECK(enemy.getMoney() == 100);

        prop1->onStep(&player);
        CHECK(player.getMoney() == 100);
        prop2->onStep(&player);
        CHECK(player.getMoney() == 100);
        prop3->onStep(&player);
        CHECK(player.getMoney() == 92);
        CHECK(enemy.getMoney() == 108);

        go->onStep(&player);
        CHECK(player.getMoney() == 92 + 2*GoTile::PASS_REWARD);

        tax->onStep(&enemy);
        CHECK(enemy.getMoney() == 58);

        player.looseMoney(92 + 2*GoTile::PASS_REWARD);
        player.addMoney(300);

        CHECK(player.getMoney() == 300);
        trains[2]->onStep(&player);
        CHECK(player.getMoney() == 300 - 2*RailwayTile::BASE_PAY);

        delete go;
        delete prop1;
        delete prop2;
        delete prop3;
        delete trains[0];
        delete trains[1];
        delete trains[2];
        delete trains[3];
    }

    SUBCASE("House/Hotel Tests") {
        Player player("Lidor", Qt::black);
        Player enemy("Severus Snape", Qt::white);

        PropertyColor pink(2, QColorConstants::Svg::pink, "pink");
        PropertyColor purple(2, QColorConstants::Svg::purple, "purple");
        PropertyColor red(1, QColorConstants::Svg::red, "red");

        PropertyTile prop1(1, "pink 1", 100, pink, 10, 50, 60, 1000);
        PropertyTile prop2(2, "pink 2", 100, pink, 10, 50, 60, 1000);
        PropertyTile prop3(3, "purple 1", 120, purple, 12, 100, 70, 1300);
        PropertyTile prop4(4, "purple 2", 120, purple, 12, 100, 70, 1300);
        PropertyTile prop5(5, "red 1", 140, purple, 14, 100, 90, 1600);

        enemy.looseMoney(Player::START_MONEY);
        player.looseMoney(Player::START_MONEY);
        player.addMoney(10000);

        enemy.getOwnedTiles().add(&prop1);
        enemy.getOwnedTiles().add(&prop2);
        enemy.getOwnedTiles().add(&prop3);
        enemy.getOwnedTiles().add(&prop4);
        enemy.getOwnedTiles().add(&prop5);
        prop1.setOwner(&enemy);
        prop2.setOwner(&enemy);
        prop3.setOwner(&enemy);
        prop4.setOwner(&enemy);
        prop5.setOwner(&enemy);

        // Build Hotel:
        prop1.buildHouse(); prop1.buildHouse(); prop1.buildHouse();
        prop1.buildHouse(); prop1.buildHouse();
        // Build 4 houses:
        prop2.buildHouse(); prop2.buildHouse();
        prop2.buildHouse(); prop2.buildHouse();

        // Build 3 houses:
        prop3.buildHouse(); prop3.buildHouse(); prop3.buildHouse();
        // Build 2 houses:
        prop4.buildHouse(); prop4.buildHouse();

        // Build 1 house:
        prop5.buildHouse();

        CHECK(player.getMoney() == 10000);
        prop1.onStep(&player); // Rent: 1000
        CHECK(player.getMoney() == 9000);
        prop2.onStep(&player); // Rent: 60*2(4-1) = 480
        CHECK(player.getMoney() == 8520);
        prop3.onStep(&player); // Rent: 60*2(3-1) = 240
        CHECK(player.getMoney() == 8240);
        prop4.onStep(&player); // Rent: 70*2(2-1) = 140
        CHECK(player.getMoney() == 8100);
        prop5.onStep(&player); // Rent: 90*2(1-1) = 90
        CHECK(player.getMoney() == 8010);
    }
}

TEST_CASE("Monopoly Tests") {
    int argc = 1;
    char *argv[] = {"argv"};
    QApplication app(argc, argv);
    vector<Player> players = {
        Player("Lidor", Qt::red),
        Player("Eli Kopter", Qt::green),
        Player("Amit Nakesh", Qt::blue),
    };
    for (auto &player : players) {
        player.looseMoney(player.getMoney());
        player.addMoney(2000);
    }

    SUBCASE("Simulation") {
        Monopoly game(players);

        // ==================== Simulate Game ====================
        // Lidor's Turn
        game.rollDiceForTest(2, 4); // Move to Oriental Avenue.
        game.moveCurrentPlayerBy(6);
        game.buyProperty(); // Cost: -$100.
        game.finishTurn();

        // Eli's Turn
        game.rollDiceForTest(1, 3); // Move to Income Tax, -$200
        game.moveCurrentPlayerBy(4);
        CHECK_THROWS(game.buyProperty()); // Can't buy Tax space.
        game.finishTurn();

        // Amit's Turn
        game.rollDiceForTest(1, 2); // Move to Baltic Avenue.
        game.moveCurrentPlayerBy(3);
        game.buyProperty(); // Cost: -$60.
        game.finishTurn();


        // Lidor's Turn
        game.rollDiceForTest(1, 2);
        game.moveCurrentPlayerBy(2); // Move to Vermont.
        game.buyProperty(); // Const: -$100.
        game.moveCurrentPlayerBy(1); // Move to Connecticut.
        game.buyProperty(); // Const: -$120.
        // Now Lidor has monopoly over light-blue color.
        game.finishTurn();

        // Eli's Turn
        game.rollDiceForTest(6, 6); // Move to St. James Palace.
        game.moveCurrentPlayerBy(12);
        game.buyProperty(); // Cost: -$180
        game.rollDiceForTest(6, 6); // Move to Water Works.
        game.moveCurrentPlayerBy(12);
        game.buyProperty(); // Cost: -$150
        game.rollDiceForTest(3, 4); // Move to Short Line Railway.
        game.moveCurrentPlayerBy(7);
        game.finishTurn();

        // Amit's Turn
        CHECK(!game.getCurrentPlayer().isInJail());
        game.rollDiceForTest(3, 3); // Move to Connecticut.
        game.moveCurrentPlayerBy(6); // (Lidor's, -$8)
        game.rollDiceForTest(3, 3); // Move to Pennsylvania Railroad.
        game.moveCurrentPlayerBy(6);
        game.buyProperty(); // Cost: -$200.
        game.rollDiceForTest(3, 3); // Move to Jail. (3 doubles)
        CHECK(game.getCurrentPlayer().isInJail());
        game.finishTurn();

        // Lidor's Turn
        game.rollDiceForTest(6, 6); // Move to Kentucky.
        game.moveCurrentPlayerBy(12);
        game.buyProperty(); // Cost: -$220
        game.rollDiceForTest(5, 5); // Move to Pacific Ave.
        game.moveCurrentPlayerBy(10);
        game.rollDiceForTest(4, 6); // Move to Mediterranean.
        game.moveCurrentPlayerBy(10); // Pass Go, +$200
        game.buyProperty(); // Cose: -$60.
        // Buy houses in light-blue monopoly:
        game.buyHouse((PropertyTile*)Assets::getTileById(6)); // -$50
        game.buyHouse((PropertyTile*)Assets::getTileById(8)); // -$50
        game.buyHouse((PropertyTile*)Assets::getTileById(9)); // -$50
        game.buyHouse((PropertyTile*)Assets::getTileById(6)); // -$50
        game.buyHouse((PropertyTile*)Assets::getTileById(8)); // -$50
        game.buyHouse((PropertyTile*)Assets::getTileById(9)); // -$50
        CHECK_THROWS(game.buyHouse((PropertyTile*)Assets::getTileById(11))); // Owned by nobody
        CHECK_THROWS(game.buyHouse((PropertyTile*)Assets::getTileById(3))); // Owned by Amit
        game.finishTurn();

        // Eli's Turn
        game.rollDiceForTest(2, 3); // Move to Go.
        game.moveCurrentPlayerBy(5); // +$400
        game.finishTurn();

        // Amit's Turn
        CHECK(game.getCurrentPlayer().isInJail());
        game.rollDiceForTest(3, 3);
        CHECK(!game.getCurrentPlayer().isInJail());
        game.moveCurrentPlayerBy(6); // Move to St James Palace. (Eli's, -$14)
        game.finishTurn();


        // ==================== Check state ====================
        OwnableTileList tiles;
        PropertyColor brown = Assets::getColorByName("brown");
        PropertyColor lightBlue = Assets::getColorByName("light-blue");

        // Lidor:
        const Player& lidor = game.getPlayers()[0];
        tiles = lidor.getOwnedTiles();
        CHECK(lidor.getMoney() == 1308); // 2000 - 2*100 - 120 + 8(rent) - 220 + 200 - 60 - 6*50
        CHECK(lidor.getLocation() == 1); // Mediterranean.
        CHECK(lidor.getJailTurns() == 0);
        CHECK(!lidor.isInJail());
        CHECK(tiles.countRailways() == 0);
        CHECK(!tiles.hasMonopoly(brown));
        CHECK(tiles.hasMonopoly(lightBlue));
        CHECK(tiles.size() == 5);
        CHECK(tiles[0]->getName() == "Oriental Avenue");
        CHECK(((PropertyTile*)tiles[0])->getHouseCount() == 2);
        CHECK(tiles[1]->getName() == "Vermont Avenue");
        CHECK(((PropertyTile*)tiles[1])->getHouseCount() == 2);
        CHECK(tiles[2]->getName() == "Connecticut Avenue");
        CHECK(((PropertyTile*)tiles[2])->getHouseCount() == 2);
        CHECK(tiles[3]->getName() == "Kentucky Avenue");
        CHECK(((PropertyTile*)tiles[3])->getHouseCount() == 0);
        CHECK(tiles[4]->getName() == "Mediter-ranean Avenue");
        CHECK(((PropertyTile*)tiles[4])->getHouseCount() == 0);

        // Eli:
        const Player& eli = game.getPlayers()[1];
        tiles = eli.getOwnedTiles();
        CHECK(eli.getMoney() == 1884); // 2000 - 200 - 180 - 150 + 400 + 14(rent)
        CHECK(eli.getLocation() == 0); // Go.
        CHECK(eli.getJailTurns() == 0);
        CHECK(!eli.isInJail());
        CHECK(tiles.countRailways() == 0);
        CHECK(!tiles.hasMonopoly(brown));
        CHECK(!tiles.hasMonopoly(lightBlue));
        CHECK(tiles.size() == 2);
        CHECK(tiles[0]->getName() == "St. James Place");
        CHECK(((PropertyTile*)tiles[0])->getHouseCount() == 0);
        CHECK(tiles[1]->getName() == "Water Works");
        CHECK(tiles[1]->getType() == MonoTile::TILE_COMPANY);

        // Amit:
        const Player& amit = game.getPlayers()[2];
        tiles = amit.getOwnedTiles();
        CHECK(amit.getMoney() == 1718); // 2000 - 60 - 8 - 200 - 14
        CHECK(amit.getLocation() == 16); // St. James Place.
        CHECK(amit.getJailTurns() == 0);
        CHECK(!amit.isInJail());
        CHECK(tiles.countRailways() == 1);
        CHECK(!tiles.hasMonopoly(brown));
        CHECK(!tiles.hasMonopoly(lightBlue));
        CHECK(tiles.size() == 2);
        CHECK(tiles[0]->getName() == "Baltic Avenue");
        CHECK(((PropertyTile*)tiles[0])->getHouseCount() == 0);
        CHECK(tiles[1]->getName() == "Pennsylvania Railroad");
        CHECK(tiles[1]->getType() == MonoTile::TILE_RAILWAY);
    }
}

