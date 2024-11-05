#include "../include/Follower.hpp"
#include "../include/stats.hpp"
#include <iostream>

using namespace std;

Follower :: Follower(const char* n, follower_type t)
: GreenCard(n, card_type :: FOLLOWER), type(t)
{
    switch(type)                                                    // Setting up attributes based on the Follower type
    {
        case (follower_type :: FOOTSOLDIER):
            setCost(FOOTSOLDIER_COST);
            setAttackBonus(FOOTSOLDIER_ATTACK_BONUS);
            setDefenseBonus(FOOTSOLDIER_DEFENSE_BONUS);
            setMinimumHonor(FOOTSOLDIER_MIN_HONOR);
            setEffectBonus(FOOTSOLDIER_EFFECT_BONUS);
            setEffectCost(FOOTSOLDIER_EFFECT_COST);
            setCardText("Footsoldier Text");
            break;
        case (follower_type :: ARCHER):
            setCost(ARCHER_COST);
            setAttackBonus(ARCHER_ATTACK_BONUS);
            setDefenseBonus(ARCHER_DEFENSE_BONUS);
            setMinimumHonor(ARCHER_MIN_HONOR);
            setEffectBonus(ARCHER_EFFECT_BONUS);
            setEffectCost(ARCHER_EFFECT_COST);
            setCardText("Archer Text");
            break;
        case (follower_type :: SIEGER):
            setCost(SIEGER_COST);
            setAttackBonus(SIEGER_ATTACK_BONUS);
            setDefenseBonus(SIEGER_DEFENSE_BONUS);
            setMinimumHonor(SIEGER_MIN_HONOR);
            setEffectBonus(SIEGER_EFFECT_BONUS);
            setEffectCost(SIEGER_EFFECT_COST);
            setCardText("Sieger Text");
            break;
        case (follower_type :: CAVALRY):
            setCost(CAVALRY_COST);
            setAttackBonus(CAVALRY_ATTACK_BONUS);
            setDefenseBonus(CAVALRY_DEFENSE_BONUS);
            setMinimumHonor(CAVALRY_MIN_HONOR);
            setEffectBonus(CAVALRY_EFFECT_BONUS);
            setEffectCost(CAVALRY_EFFECT_COST);
            setCardText("Cavarly Text");
            break;
        case (follower_type :: NAVAL):
            setCost(NAVAL_COST);
            setAttackBonus(NAVAL_ATTACK_BONUS);
            setDefenseBonus(NAVAL_DEFENSE_BONUS);
            setMinimumHonor(NAVAL_MIN_HONOR);
            setEffectBonus(NAVAL_EFFECT_BONUS);
            setEffectCost(NAVAL_EFFECT_COST);
            setCardText("Attakebune Text");
            break;
        case (follower_type :: BUSHIDO):
            setCost(BUSHIDO_COST);
            setAttackBonus(BUSHIDO_ATTACK_BONUS);
            setDefenseBonus(BUSHIDO_DEFENSE_BONUS);
            setMinimumHonor(BUSHIDO_MIN_HONOR);
            setEffectBonus(BUSHIDO_EFFECT_BONUS);
            setEffectCost(BUSHIDO_EFFECT_COST);
            setCardText("Bushido Text");
            break;
        default :
            break;
    }
}

Follower :: ~Follower() {}

card_type Follower :: getType()
{
    return GreenCard :: getType();
}

/**
 * Prints the Item card details.
 */
void Follower :: print() const
{
    this -> GreenCard :: print();                                   // Printing the GreenCard :: part of the Follower

    switch(type)                                                    // Printing the specific Follower type
    {
        case(follower_type :: FOOTSOLDIER):
            cout << "Follower Type: Foot Soldier" << endl;
            break;
        case(follower_type :: ARCHER):
            cout << "Follower Type: Archer" << endl;
            break;
        case(follower_type :: SIEGER):
            cout << "Follower Type: Sieger" << endl;
            break;
        case(follower_type :: CAVALRY):
            cout << "Follower Type: Cavalry" << endl;
            break;
        case(follower_type :: NAVAL):
            cout << "Follower Type: Atakebune" << endl;
            break;
        case(follower_type :: BUSHIDO):
            cout << "Follower Type: Bushido" << endl;
            break;
        default:
            break;
    }
}

// Footsoldier methods

Footsoldier :: Footsoldier(const char* name)
: Follower(name, follower_type :: FOOTSOLDIER)
{

}

// Archer methods

Archer :: Archer(const char* name)
: Follower(name, follower_type :: ARCHER)
{

}

// Sieger methods

Sieger :: Sieger(const char* name)
: Follower(name, follower_type :: SIEGER)
{

}

// Cavalry methods

Cavalry :: Cavalry(const char* name)
: Follower(name, follower_type :: CAVALRY)
{

}

// Atakebune methods

Atakebune :: Atakebune(const char* name)
: Follower(name, follower_type :: NAVAL)
{

}

// Bushido methods

Bushido :: Bushido(const char* name)
: Follower(name, follower_type :: BUSHIDO)
{

}