#include "Card.hpp"
#include <iostream>

using namespace std;

/**
 *  Creates a Card with the specified name and the specified type.
 *  @param c The name of the Card
 *  @param t The Card type
 */
Card :: Card( const char* c, card_type t )
:name(c), cost(-1), isTapped(false), type(t)
{

}

Card :: ~Card() {}

/**
 * Prints the Card details and type.
 */
void Card :: print() const
{
    // Printing Card details
    cout << "Name: " << name << endl << "Cost: " << cost << endl;
    if(isTapped)
    {
        cout << "Situation: Tapped" << endl;
    }
    else
    {
        cout << "Situation: Untapped" << endl;
    }

    // Printing Card type 
    switch(type)
    {
        case card_type :: PERSONALITY:
            cout << "Card Type: Personality" << endl;
            break;
        case card_type :: HOLDING:
            cout << "Card Type: Holding" << endl;
            break;
        case card_type :: FOLLOWER:
            cout << "Card Type: Follower" << endl;
            break;
        case card_type :: ITEM:
            cout << "Card Type: Item" << endl;
            break;
        default:
            break;
    }
}

/**
 * Returns the type of the Card.
 */
card_type Card :: getType() const
{
    return type;
}

void Card :: setCost(int c)
{
    cost = c;
}

int Card :: getCost() const
{
    return cost;
}

void Card :: tap()
{
	isTapped = true;
}

void Card :: untap()
{
	isTapped = false;
}

bool Card :: tapped() const
{
    return isTapped;
}

// BlackCard methods

BlackCard :: BlackCard ( const char* c, card_type t )
: Card(c,t), isRevealed(false)
{

}

BlackCard :: ~BlackCard() {}

card_type BlackCard :: getType() const
{
    return Card :: getType();
}

bool BlackCard :: Revealed ()
{
    return isRevealed;
}

/**
 * Sets the Black Card as revealed/not reaveal.
 */
void BlackCard :: setRevealed(bool value)
{
    isRevealed = value;
}

/**
 * Prints the Black Card details.
 */
void BlackCard :: print() const
{
    this -> Card :: print();                            // Print the Card :: part of the Black Card
    cout << "Color: Black" << endl;                     // And the rest of the Black Card details
    if(isRevealed)
    {
        cout << "Visibility: Revealed" << endl;
    }
    else
    {
        cout << "Visibility: Not Revealed" << endl;
    }
}

// Green Card methods

GreenCard :: GreenCard ( const char* c, card_type t )
: Card(c,t), attackBonus(-1), defenseBonus(-1), minimumHonor(-1), effectBonus(-1),
effectCost(0), cardText("Text")
{

}

GreenCard :: ~GreenCard() {}

card_type GreenCard :: getType() const
{
    return Card :: getType();
}

void GreenCard :: setAttackBonus (int s)
{
    attackBonus = s;
}

void GreenCard :: setDefenseBonus (int s)
{
    defenseBonus = s;
}

void GreenCard :: setMinimumHonor (int s)
{
    minimumHonor = s;
}

void GreenCard :: setEffectBonus (int s)
{
    effectBonus = s;
}

void GreenCard :: setEffectCost (int s)
{
    effectCost = s;
}

void GreenCard :: setCardText (const char* txt)
{
    cardText.assign(txt);
}

int GreenCard :: getAttackBonus() const
{
    return attackBonus;
}

int GreenCard :: getDefenseBonus() const
{
    return defenseBonus;
}

int GreenCard :: getMinimumHonor() const
{
    return minimumHonor;
}

int GreenCard :: getEffectBonus() const
{
    return effectBonus;
}

int GreenCard :: getEffectCost() const
{
    return effectCost;
}

string GreenCard :: getCardText() const
{
    return cardText;
}

int GreenCard :: getCost() const
{
    return Card :: getCost();
}

/**
 * Activates the Bonus effect of the Green Card.
 */
void GreenCard :: activateBonus()
{
    attackBonus += effectBonus;
    defenseBonus += effectBonus;
}

/**
 * Prints the Green Card details.
 */
void GreenCard :: print() const
{
    this -> Card :: print();                            // Print the Card :: part ot the Green Card
                                                        // // And the rest of the Green Card details
    cout << "Color: Green" << endl;
    cout << "Attack Bonus: " << attackBonus << endl << "Defense Bonus: " << defenseBonus << endl;
    cout << "Minimum Honor: " << minimumHonor << endl ;
    cout << "Effect Bonus: " << effectBonus << endl << "Effect Cost: " << effectCost << endl;
    cout << "Text: " << endl << cardText << endl ;
}

// Other non-class methods

/**
 * Deletes the specified Card.
 */
void discard(Card* card)
{
    delete card;
}