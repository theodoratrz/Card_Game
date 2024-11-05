#include "Holding.hpp"
#include "stats.hpp"
#include <iostream>

using namespace std;

Holding :: Holding(const char* n, holding_type t)
: BlackCard(n, card_type :: HOLDING), type(t), harvestValue(-1), upperHolding(NULL), subHolding(NULL)
{
    switch(type)                                                  // Setting up attributes based on the Holding type
    {
        case (holding_type :: PLAIN):
            setCost(PLAIN_COST);
            harvestValue = PLAIN_HARVEST;
            break;
        case (holding_type :: MINE):
            setCost(MINE_COST);
            harvestValue = MINE_HARVEST;
            break;
        case (holding_type :: GOLD_MINE):
            setCost(GOLD_MINE_COST);
            harvestValue = GOLD_MINE_HARVEST;
            break;
        case (holding_type :: CRYSTAL_MINE):
            setCost(CRYSTAL_MINE_COST);
            harvestValue = CRYSTAL_MINE_HARVEST;
            break;
        case (holding_type :: FARMS):
            setCost(FARMS_COST);
            harvestValue = FARMS_HARVEST;
            break;
        case (holding_type :: SOLO):
            setCost(SOLO_COST);
            harvestValue = SOLO_HARVEST;
            break;
        case (holding_type :: STRONGHOLD):
            setCost(0);
            harvestValue = STRONGHOLD_HARVEST;      
            break;
        default:
            // problem
            break;
    }
}

Holding :: ~Holding() {}

card_type Holding :: getType() const
{
    return BlackCard :: getType();
}

holding_type Holding :: getHoldingType() const
{
    return type;
}

/**
 *  Connnects this Holding with the specified one (if possible)
 *  @param other becomes subholding of this and this becomes upperholding of other.
 */
void Holding :: connectSubHolding(Holding* other )
{
    switch (type)
    {
        case holding_type :: GOLD_MINE:
            if (other->type != holding_type :: MINE)            // This is a Gold Mine
            {
                return;                                         // If other is not a Mine, it cannot be the subholding of this
            }
            break;
        case holding_type :: CRYSTAL_MINE:                      
            if (other->type != holding_type :: GOLD_MINE)       // This is a Crystal Mine
            {
                return;                                         // If other is not a Gold Mine, it cannot be the subholding of this
            }
            break;
        default:
            return;
            break;
    }
    if (this->subHolding != NULL || other->upperHolding != NULL)        // If this already has a subholding or/and other has an upperholding,
    {
        return;                                                         // The connection cannot be made
    }    
    this->subHolding = other;                                           // other becomes subholding of this
    other->upperHolding = this;                                         // this becomes upperholding of other
}

/**
 *  Connnects this Holding with the specified one (if possible)
 *  @param other becomes upperholding of this and this becomes subholding of other.
 */
void Holding :: connectUpperHolding(Holding* other)
{
    switch (type)
    {
        case holding_type :: MINE:
            if (other->type != holding_type :: GOLD_MINE)       // This is a Mine
            {
                return;                                         // If other is not a Gold Mine, it cannot be the upperholding of this
            }
            break;
        case holding_type :: GOLD_MINE:                         // This is a Gold Mine
            if (other->type != holding_type :: CRYSTAL_MINE)    // If other is not a Crystal Mine, it cannot be the upperholding of this
            {
                return;
            }
            break;
        default:
            return;
            break;
    }
    if (this->upperHolding != NULL || other->subHolding != NULL)        // If this already has a upperholding or/and other has an subholding,
    {
        return;                                                         // The connection cannot be made
    }    
    this->upperHolding = other;                                         // other becomes upperholding of this
    other->subHolding = this;                                           // this becomes subholding of other
}

/**
 * Prints the Holding card details.
 */
void Holding :: print() const
{
    this -> BlackCard :: print();                                   // Printing the BlackCard :: part of the Holding

    switch(type)                                                    // Printing the specific Holding type
    {
        case(holding_type :: PLAIN):
            cout << "Holding Type: Plain" << endl;
            break;
        case(holding_type :: MINE):
            cout << "Holding Type: Mine" << endl;
            break;
        case(holding_type :: GOLD_MINE):
            cout << "Holding Type: Gold MIne" << endl;
            break;
        case(holding_type :: CRYSTAL_MINE):
            cout << "Holding Type: Crystal Mine" << endl;
            break;
        case(holding_type :: FARMS):
            cout << "Holding Type: Farmland" << endl;
            break;
        case(holding_type :: SOLO):
            cout << "Holding Type: Gift & Favour" << endl;
            break;
        case(holding_type :: STRONGHOLD):
            cout << "Holding Type: Stronghold" << endl;
            break;
        default:
            break;
    }
    // Printing the rest of the Item Attributes and Details
    cout << "Harvest: " << harvestValue << endl;
}

Holding* Holding :: getUpperHolding() const
{
    return upperHolding;
}

Holding* Holding :: getSubHolding() const
{
    return subHolding;
}

void Holding :: setHarvest(int n)
{
    harvestValue = n;
}

int Holding :: getHarvest() const
{
    return harvestValue;
}

// Plain methods

Plain :: Plain(const char* name)
: Holding(name, holding_type :: PLAIN)
{

}

// Mine methods

Mine :: Mine(const char* name)
: Holding(name, holding_type :: MINE)
{

}

/**
 *  Checks if the Mine has an upperholding and if so, activates the harvest value bonus
 *  NOTE: to be called once after a connection is made.
 */
void Mine :: checkUpperBonus()
{
	if(this->getUpperHolding() != NULL)
	{
		setHarvest(getHarvest() + 2);
	}
}

// Gold Mine methods

GoldMine :: GoldMine(const char* name)
: Holding(name, holding_type :: GOLD_MINE)
{

}

/**
 *  Checks if the Gold Mine has an upperholding and if so, activates the harvest value bonus
 *  NOTE: to be called once after a connection is made.
 */
void GoldMine :: checkUpperBonus()
{
	if(this->getUpperHolding() != NULL)
	{
		setHarvest( getHarvest() + 5 );
	}
}

/**
 *  Checks if the Gold Mine has an subholding and if so, activates the harvest value bonus
 *  NOTE: to be called once after a connection is made.
 */
void GoldMine :: checkSubBonus()
{
	if(this->getSubHolding() != NULL)
	{
		setHarvest( getHarvest() + 4 );
	}
}

/**
 *  Checks if there is a chain connection (if the Gold Mine has both a sub and an upperholding)
 *  and if so, activates the chain harvest value bonus.
 * NOTE: to be called once after a chain connection is made
 */
void GoldMine :: checkChainBonus()
{
	if((this->getUpperHolding() != NULL) && (this->getSubHolding() != NULL))
	{
		this->setHarvest(GOLD_MINE_HARVEST*2);
		( getUpperHolding() )->setHarvest(CRYSTAL_MINE_HARVEST*3);
	}
}

// Crystal Mine methods

CrystalMine :: CrystalMine(const char* name)
: Holding(name, holding_type :: CRYSTAL_MINE)
{

}

/**
 *  Checks if the Crystal Mine has an subholding and if so, activates the harvest value bonus
 *  NOTE: to be called once after a connection is made.
 */
void CrystalMine :: checkSubBonus()
{
	if(this->getSubHolding() != NULL)
	{
		setHarvest(CRYSTAL_MINE_HARVEST);
        ( (GoldMine*)this->getSubHolding() )-> GoldMine :: checkChainBonus();
	}
}

// Farmland methods

Farmland :: Farmland(const char* name)
: Holding(name, holding_type :: FARMS)
{

}

// Gift & Favour methods

GiftandFavour :: GiftandFavour(const char* name)
: Holding(name, holding_type :: SOLO)
{

}

// Stronghold methods

Stronghold :: Stronghold(const char* name)
: Holding(name, holding_type :: STRONGHOLD), honor(-1), money(-1), initialDefense(STRONGHOLD_DEFENSE)
{}

void Stronghold :: setHonor(int value)
{
    honor = value;
}

void Stronghold :: setMoney(int value)
{
    money = value;
}

void Stronghold :: setInitialDefense(int value)
{
    initialDefense = value;
}

int Stronghold :: getHonor() const
{
    return honor;
}

int Stronghold :: getMoney() const
{
    return money;
}

int Stronghold :: getDefense() const
{
    return initialDefense ;
}

/**
 *  Prints the Stronghold card details.
 */
void Stronghold :: print() const
{
    this -> Holding :: print();                                 // Printing the Holding :: part of the Stronghold
    cout << "Honor: " << honor << endl;                         // And the rest of the Stronghold information
    cout << "Money: " << money << endl;
    cout << "Initial Defense: " << initialDefense << endl;
}
