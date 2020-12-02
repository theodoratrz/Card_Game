#ifndef CARD_HPP
#define CARD_HPP

#include <string>

enum class card_type { PERSONALITY = 1, HOLDING, FOLLOWER, ITEM };      // Different Card types

using namespace std;

class Card
{
    string name;
    int cost;
    bool isTapped;
    card_type type;
    
    public:
    Card(const char* c, card_type t );                                  // Creates a Card with the specified name and the specified type.
    virtual ~Card() = 0;
    virtual card_type getType() const;                                  // Returns the type of the Card.
    void setCost(int c);
    virtual void print() const;                                         // Prints the Card details and type.
    void tap();                                                         // Taps the Card.
    void untap();                                                       // Untaps the Card.
    int getCost() const;
    bool tapped() const;                                                // Returns TRUE if tha card has been tapped, FALSE otherwise.
};

class BlackCard : public Card
{
    bool isRevealed;

    public:
    BlackCard(const char* c, card_type t);
    virtual ~BlackCard() = 0;
    card_type getType() const;                                          // Returns the type of the Card.
    bool Revealed();                                                    // Returns TRUE if the Black Card is revealed, FALSE otherwise.
    void setRevealed(bool value);                                       // Sets the Black Card as revealed/not reaveal.
    void print() const;                                                 // Prints the Black Card details.
};

class GreenCard : public Card
{
    int attackBonus;
    int defenseBonus;
    int minimumHonor;
    int effectBonus;
    int effectCost;
    string cardText;

    public:
    GreenCard (const char* c, card_type t );
    virtual ~GreenCard() = 0;
    card_type getType() const;                                          // Returns the type of the Card.
    void setAttackBonus(int s);
    void setDefenseBonus(int s);
    void setMinimumHonor(int s);
    void setEffectBonus(int s);
    void setEffectCost(int s);
    void setCardText(const char* txt);
    int getAttackBonus() const;
    int getDefenseBonus() const;
    int getMinimumHonor() const;
    int getEffectBonus() const;
    int getEffectCost() const;
    string getCardText() const;
    int getCost() const;
    void activateBonus();                                               // Activates the Bonus effect of the Green Card.
    void print() const;                                                 // Prints the Green Card details.
};

void discard(Card* card);                                               // Discards(Deletes) the specified Card.

#endif