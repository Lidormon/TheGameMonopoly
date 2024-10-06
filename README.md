# TheGameMonopoly

Project Instructions:

1. Download and open QT Creator
2. Go to File -> Open File or Project
3. Select the project you downloaded from my Git
4. Open the file "monopoly.pro"
5. Click on the "Configure Project" button
6. Click on "Project" on the left side of the screen and then on "Run"
7. Go to "Working Directory" and change the folder location to the folder of the project where you opened it from
8. In the bottom left, click the green triangle to start the game

This project implements a simplified version of the classic board game Monopoly using QT GUI. The game includes all key components such as players, assets (properties), and game tiles, as well as handling rules and interactions between players. It is designed to simulate a competitive Monopoly game experience with a focus on properties, player management, and error handling.

Project Structure

model: Contains the core classes and logic related to the game model.

view: Handles the user interface or graphical representation of the game (though this depends on the specific contents of the folder).

Files

assets.cpp / assets.h: I am loading the game data from the 'assets' folder, which contains the text files (spaces.txt, colors.txt, chance.txt, community_chest.txt) with the information. In addition these files manage the game’s assets, such as properties and utilities, including their ownership, purchase price, and rent calculation. Note: if I change the number of tiles on the board (by adding or removing rows in spaces.txt, the 'go to' rows in chance.txt also need to be adjusted.

main.cpp: This is the entry point for the game, responsible for initializing the game components, handling game flow, and managing player turns. monopoly.cpp / monopoly.h: These files contain the core logic of the game, including rules for buying properties, handling special tiles (e.g., Chance, Go to Jail), and interactions between players.

monopolyerrors.cpp / monopolyerrors.h: These handle potential errors or exceptions that may arise during gameplay, ensuring the game runs smoothly without crashing.

ownabletilelist.cpp / ownabletilelist.h: These files manage the list of tiles that can be owned by players, such as properties, and utilities.

playerlist.cpp / playerlist.h: These manage the list of players, keeping track of their financial status, properties, and position on the board.

Game Features

Player Management: Handles multiple players, including their movement across the board, financial transactions, and asset ownership.

Property Ownership: Implements the core concept of buying, selling, and renting properties.

Game Flow: Enforces the rules of Monopoly, ensuring proper turn-based gameplay, and interaction with special tiles such as "Go to Jail" or "Chance" cards.

Error Handling: Robust error handling to prevent crashes during gameplay, particularly around property transactions and player status.
