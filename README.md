# Project Overview

This project is a card game implemented in C++, made for the Object Oriented course. The game involves players, decks of cards, and various game phases. Below is a high-level overview of the components and their roles:

## Project Structure

- **Card Classes:** Represent different types of cards in the game.
  - `Card.hpp` and `Card.cpp`
  - [Follower.hpp](card_game/include/Follower.hpp) and [Follower.cpp](card_game/src/Follower.cpp)
  - [Item.hpp](card_game/include/Item.hpp) and [Item.cpp](card_game/src/Item.cpp)
  - [Personality.hpp](card_game/include/Personality.hpp) and [Personality.cpp](card_game/src/Personality.cpp)
  - [Holding.hpp](card_game/include/Holding.hpp) and [Holding.cpp](card_game/src/Holding.cpp)

- **Deck Management:** Handles the creation and shuffling of decks.
  - [DeckBuilder.hpp](card_game/include/DeckBuilder.hpp) and [DeckBuilder.cpp](card_game/src/DeckBuilder.cpp)

- **Game Board:** Manages the overall game state, including players and game phases.
  - [GameBoard.hpp](card_game/include/GameBoard.hpp) and [GameBoard.cpp](card_game/src/GameBoard.cpp)

- **Player Class:** Represents a player in the game, including their deck, hand, and other attributes.
  - Defined in [GameBoard.hpp](card_game/include/GameBoard.hpp) and implemented in [GameBoard.cpp](card_game/src/GameBoard.cpp)

- **Type Conversion:** Utility to convert between different card types.
  - [TypeConverter.hpp](card_game/include/TypeConverter.hpp) and [TypeConverter.cpp](card_game/src/TypeConverter.cpp)

- **Main Entry Point:** The main function to start the game.
  - [main.cpp](card_game/src/main.cpp)

## Key Classes and Functions

### [GameBoard](card_game/include/GameBoard.hpp)

- **Attributes:**
  - `numberOfPlayers`: Number of players in the game.
  - `players`: A vector of pointers to `Player` objects.

- **Methods:**
  - `initializeGameBoard()`: Initializes the game board and players.
  - `gamePreparation()`: Prepares the game, including setting up players' strongholds.
  - `gameplay()`: Runs the main game loop, executing different phases until a winner is determined.
  - `checkWinningCondition()`: Checks if there is a winner.
  - `gameEnd()`: Performs cleanup actions after the game ends.
  - Various phase methods like `startingPhase()`, `equipPhase()`, `economyPhase()`, `battlePhase()`, and `finalPhase()`.

### [Player](card_game/include/GameBoard.hpp)

- **Attributes:**
  - `name`: Player's name.
  - `deck`: Pointer to the player's `DeckBuilder`.
  - `honor`, `money`, `initialDefense`: Player's attributes.
  - Various lists to manage cards in hand, deck, provinces, holdings, and army.

- **Methods:**
  - `prepare(Stronghold* s)`: Prepares the player for the game.
  - `getName()`, `getMoney()`, `getHonor()`, `setHonor(int value)`, `setMoney(int value)`: Getters and setters for player attributes.

### [DeckBuilder](card_game/include/DeckBuilder.hpp)

- **Attributes:**
  - `green`: List of `GreenCard` pointers (fate deck).
  - `black`: List of `BlackCard` pointers (dynasty deck).

- **Methods:**
  - `createFateDeck()`, `createDynastyDeck()`: Create the respective decks.
  - `deckShuffler(list<GreenCard*>* green)`, `deckShuffler(list<BlackCard*>* black)`: Shuffle the respective decks.
  - `getFateDeck()`, `getDynastyDeck()`: Get the respective decks.

## Game Flow

1. **Initialization**: The game board and players are initialized.
2. **Preparation**: Players' decks are prepared, and initial cards are drawn.
3. **Gameplay Loop**: The game phases are executed in a loop until a winning condition is met.
4. **End Game**: Cleanup actions are performed, and the winner is announced.