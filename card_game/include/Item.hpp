#ifndef ITEM_HPP
#define ITEM_HPP

#include "Card.hpp"

enum class item_type {KATANA, SPEAR, BOW, NINJATO, WAKIZASHI};

class Item : public GreenCard
{
    item_type type;
    int durability;

    public:
    Item(const char* n, item_type t);
    virtual ~Item() = 0;
    card_type getType();                                                // Returns the type (card_type) of the Card.
    void print() const;                                                 // Prints the Item card details.
    int getDurability() const;
    void reduceDurability();                                            // Reduces the Item's durability by 1.
};

class Katana : public Item
{
    public:
    Katana(const char* name);
};

class Spear : public Item
{
    public:
    Spear(const char* name);
};

class Bow : public Item
{
    public:
    Bow(const char* name);
};

class Ninjato : public Item
{
    public:
    Ninjato(const char* name);
};

class Wakizashi : public Item
{
    public:
    Wakizashi(const char* name);
};

#endif