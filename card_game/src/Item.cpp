#include "../include/Item.hpp"
#include "../include/stats.hpp"
#include <iostream>

using namespace std;

Item :: Item(const char* n, item_type t)
: GreenCard(n, card_type :: ITEM), type(t)
{
    switch (type)                                                   // Setting up attributes based on the Item type
    {
        case (item_type :: KATANA):
            setCost(KATANA_COST);
            setAttackBonus(KATANA_ATTACK_BONUS);
            setDefenseBonus(KATANA_DEFENSE_BONUS);
            setMinimumHonor(KATANA_MIN_HONOR);
            setEffectBonus(KATANA_EFFECT_BONUS);
            setEffectCost(KATANA_EFFECT_COST);
            setCardText("Katana Text");
            durability = KATANA_DURABILITY;
            break;
        case (item_type :: SPEAR):
            setCost(SPEAR_COST);
            setAttackBonus(SPEAR_ATTACK_BONUS);
            setDefenseBonus(SPEAR_DEFENSE_BONUS);
            setMinimumHonor(SPEAR_MIN_HONOR);
            setEffectBonus(SPEAR_EFFECT_BONUS);
            setEffectCost(SPEAR_EFFECT_COST);
            setCardText("Spear Text");
            durability = SPEAR_DURABILITY;
            break;
        case (item_type :: BOW):
            setCost(BOW_COST);
            setAttackBonus(BOW_ATTACK_BONUS);
            setDefenseBonus(BOW_DEFENSE_BONUS);
            setMinimumHonor(BOW_MIN_HONOR);
            setEffectBonus(BOW_EFFECT_BONUS);
            setEffectCost(BOW_EFFECT_COST);
            setCardText("Bow Text");
            durability = BOW_DURABILITY;
            break;
        case (item_type :: NINJATO):
            setCost(NINJATO_COST);
            setAttackBonus(NINJATO_ATTACK_BONUS);
            setDefenseBonus(NINJATO_DEFENSE_BONUS);
            setMinimumHonor(NINJATO_MIN_HONOR);
            setEffectBonus(NINJATO_EFFECT_BONUS);
            setEffectCost(NINJATO_EFFECT_COST);
            setCardText("Ninjato Text");
            durability = NINJATO_DURABILITY;
            break;
        case (item_type :: WAKIZASHI):
            setCost(WAKIZASHI_COST);
            setAttackBonus(WAKIZASHI_ATTACK_BONUS);
            setDefenseBonus(WAKIZASHI_DEFENSE_BONUS);
            setMinimumHonor(WAKIZASHI_MIN_HONOR);
            setEffectBonus(WAKIZASHI_EFFECT_BONUS);
            setEffectCost(WAKIZASHI_EFFECT_COST);
            setCardText("Wakizashi Text");
            durability = WAKIZASHI_DURABILITY;
            break;
        default:
            // problem
            break;    
    }
}

Item :: ~Item() {}

card_type Item :: getType()
{
    return GreenCard :: getType();
}

/**
 * Prints the Item card details.
 */
void Item :: print() const
{
    this -> GreenCard :: print();                                   // Printing the GreenCard :: part of the Item

    switch(type)                                                    // Printing the specific Item type
    {
        case(item_type :: KATANA):
            cout << "Item Type: Katana" << endl;
            break;
        case(item_type :: SPEAR):
            cout << "Item Type: Spear" << endl;
            break;
        case(item_type :: BOW):
            cout << "Item Type: Bow" << endl;
            break;
        case(item_type :: NINJATO):
            cout << "Item Type: Ninjato" << endl;
            break;
        case(item_type :: WAKIZASHI):
            cout << "Item Type: Wakizashi" << endl;
            break;
        default:
            break;    
    }
    // Printing the rest of the Item Attributes and Details
    cout << "Durability: " << durability << endl;
}

int Item :: getDurability() const
{
    return durability;
}

/**
 *   Reduces the Item's durability by 1.
 */
void Item :: reduceDurability()
{
    durability--;
}

// Katana methods

Katana :: Katana(const char* name)
: Item(name, item_type :: KATANA)
{

}

// Spear methods

Spear :: Spear(const char* name)
: Item(name, item_type :: SPEAR)
{

}

// Bow methods

Bow :: Bow(const char* name)
: Item(name, item_type :: BOW)
{

}

// Ninjato methods

Ninjato :: Ninjato(const char* name)
: Item(name, item_type :: NINJATO)
{

}

// Wakizashi methods

Wakizashi :: Wakizashi(const char* name)
: Item(name, item_type :: WAKIZASHI)
{

}