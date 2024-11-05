#ifndef GAMEBOARD_HPP
#define GAMEBOARD_HPP

#include "Card.hpp"
#include "DeckBuilder.hpp"
#include "Personality.hpp"
#include "Holding.hpp"
#include "Follower.hpp"
#include "Item.hpp"
#include <string>
#include <list>
#include <vector>

#define NOF_PLAYERS 2
#define STARTING_PROVINCES 4
#define STARTING_HAND 4
#define MAX_HAND 12

using namespace std;

class Player
{
    string name;
    DeckBuilder* deck;                                                                      // The player's deck with all of his cards
    int honor;
    int money;
    int initialDefense;
    list <GreenCard*>* hand;                                                                // The cards in the player's hand
    list <BlackCard*>* dynastyDeck;                                                         // Player's dynasty deck (points to deck.black)
    list <GreenCard*>* fateDeck;                                                            // Player's fate deck (points to deck.green)
    int numberOfProvinces;
    list <BlackCard*>* provinces;                                                           // Province cards
    list <Holding*>* holdings;                                                              // Holding cards
    list <Personality*>* army;                                                              // Army Personalities
    Stronghold* stronghold;                                                                 // Player's stronghold
    
    public:
    Player(string n);                                                                       // Creates a Player with name n
    ~Player();
    string getName() const;
    int getMoney() const;
    int getHonor() const;
    void setHonor(int value);
    void setMoney(int value);
    void prepare(Stronghold* s);                                                            // Does the Player preperation for the game.
    void addHand(GreenCard* card);                                                          // Adds a Green Card to the player's hand.
    GreenCard* drawHand(int i);                                                             // Draws the card #i from the player's hand (1 == 1st card, 2 == 2nd etc.), and returns it.
    BlackCard* drawDynastyCard();                                                           // Draws a Card from the player's Dynasty Deck and returns it.
    GreenCard* drawFateCard();                                                              // Draws a Card from the player's Fate Deck and returns it.
    void addHolding(BlackCard* card);                                                       // Adds a Card to the Player's holdings.
    void addArmy(BlackCard* card);                                                          // Adds a Black Card to the Player's army (if it is a Personality card).
    void addProvince(BlackCard* card);                                                      // Adds a Black Card to the Player's provinces.
    list<Personality*> chooseArmy();                                                        // Used in battles. Allows the player to choose the Army Personalities to use in a battle.
    void printHand() const;                                                                 // Prints the Cards of the player's hand.
    void printProvinces() const;                                                            // Prints the player's provinces.
    void printHoldings() const;                                                             // Prints the player's Holdings.
    void printArmy() const;                                                                 // Prints the Personalities of the player's army, along with the attached followers and Items.
    void connectMines();                                                                    // Makes all the available connections between Mines of the player's holdings.
    void revealProvinces();                                                                 // Makes all the player's provinces revealed.
    void untapEverything();                                                                 // Makes all the player's holdings and army untapped.
    list <Personality*>* getArmy() const;
    list <GreenCard*>* getHand() const;
    int getNumberOfProvinces() const;
    int getInitialDefense() const;
    void setInitialDefense(int value);
    int tapCoverCost(int difference);                                                       // Used to make purchases by tapping Holding cards.
    void purchaseActivateBonus(GreenCard* card);                                            // Used to purchase and activate the bonus of the specified Green Card.
    void purchaseProvideGreenCard(GreenCard* card);                                         // Used to purchase the specified Green Card.
    void purchaseProvinces();                                                               // Used to purchase provinces.
    void sacrificeDefendingArmy(int difference, list<Personality*>& used_army);             // Used to make the required sacrifices out of the specified defending army.
    void sacrificeAttackingArmy(int difference, list<Personality*>& used_army);             // Used to make the required sacrifices out of the specified attacking army.
    void loseUsedArmy(list<Personality*>& used_army);                                       // Discards any used army Personalities (along with their attachments)
    void destroyProvince(int n);                                                            // Destroys the province pointed by the node n of the provinces list.
    void discardSurplusFateCards();                                                         // Forces the player to discard hand cards in case the limit is exceeded.
    void discardCards();                                                                    // Used to discard all of the player's cards.
    void checkUsedArmyAttachments(list<Personality*> used_army);                            // 
};

class GameBoard
{
    int numberOfPlayers;                                                                    // number of players that participate in the game
    vector<Player*>* players;                                                               // The game participants

    public:
    GameBoard();
    ~GameBoard();
    void initializeGameBoard();                                                             // Makes the required initializations before the start of the game.
    void printGameStatistics();                                                             // Prints the recorded game stats.
    void gameplay();
    void gamePreparation();                                                                 // Does the required game preperation actions.
    void startingPhase();
    void equipPhase();
    void economyPhase();
    void battlePhase();
    void finalPhase();
    bool checkWinningCondition();                                                            // Checks if there is a game winner.
    void gameEnd();                                                                          // Makes actions that must take place after the game ends (discarding cards etc.)
    void test();
};

void printUsedArmy(const list<Personality*> & army);                                         // Prints the specified army.
void battle( Player* attacker, Player* defender );                                           // Simulates the battle preparation and scenario between 2 players.
int attackPowerSum(const list<Personality*>& army);                                          // Returns the total Attack attribute of the specified army.
int defensePowerSum(const list<Personality*>& army);                                         // Returns the total Defense attribute of the specified army.
void reduceUsedItemsDurability(list<Personality*>& used_army);                               // Reduces the items durability for every used army Personality.
void reduceUsedPersonalitiesHonor(list<Personality*>& used_army);                            // Reduces the honor of every used army Personality.
void tapRemainingUsedArmy(list<Personality*> used_army);                                     // Used to tap all the remaining Personalities (and their attachments) of used_army.

#endif