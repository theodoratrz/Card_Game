#ifndef HOLDING_HPP
#define HOLDING_HPP

#include "Card.hpp"

enum class holding_type{PLAIN, MINE, GOLD_MINE, CRYSTAL_MINE, FARMS, SOLO, STRONGHOLD};         // Different Holding types

class Holding : public BlackCard
{
    holding_type type;
    int harvestValue;
    Holding* upperHolding;
    Holding* subHolding;

    public:
    Holding(const char* n, holding_type t);
    virtual ~Holding() = 0;
    card_type getType() const;                                          // Returns the type (card_type) of the Card.
    void connectSubHolding(Holding* other);                             // Connnects this Holding with the specified one (as a subholding), if possible
    void connectUpperHolding(Holding* other);                           // Connnects this Holding with the specified one (as an upperholding), if possible
    holding_type getHoldingType() const;
    void print() const;                                                 // Prints the Holding card details.
    Holding* getSubHolding() const;
    Holding* getUpperHolding() const;
    void setHarvest(int n);
    int getHarvest() const;
};

class Plain : public Holding
{
    public:
    Plain(const char* name);
};

class Mine : public Holding
{
    public:
    Mine(const char* name);
    void checkUpperBonus();                                             // Checks if the Mine has an upperholding and if so, activates the harvest value bonus

};

class GoldMine : public Holding
{
    public:
    GoldMine(const char* name);
    void checkUpperBonus();                                             // Checks if the Gold Mine has an upperholding and if so, activates the harvest value bonus
    void checkSubBonus();                                               // Checks if the Gold Mine has an subholding and if so, activates the harvest value bonus
    void checkChainBonus();                                             // Checks if there is a chain connection (if the Gold Mine has both a sub and an upperholding)
                                                                        // and if so, activates the chain harvest value bonus.
};

class CrystalMine : public Holding
{
    public:
    CrystalMine(const char* name);
    void checkSubBonus();                                               // Checks if the Crystal Mine has an subholding and if so, activates the harvest value bonus
};

class Farmland : public Holding
{
    public:
    Farmland(const char* name);
};

class GiftandFavour : public Holding
{
    public:
    GiftandFavour(const char* name);
};

class Stronghold : public Holding
{
    int honor;
    int money;
    int initialDefense;

    public:
    Stronghold(const char* name);    
    void setHonor(int value);
    void setMoney(int value);
    void setInitialDefense(int value);
    int getHonor() const;
    int getMoney() const;
    int getDefense() const;
    void print() const;                                                 // Prints the Stronghold card details.
}; 

#endif