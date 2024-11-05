#include "Personality.hpp"
#include "stats.hpp"
#include <iostream>
#include "Card.hpp"

using namespace std;

Personality :: Personality(const char* n, personality_type t)
: BlackCard(n, card_type :: PERSONALITY), type(t), Attack(-1), Defense(-1), Honor(-1),
 isDead(false), numberOfFollowers(0), numberOfItems(0)
{
    switch(type)                                                 // Setting up attributes based on the Personality type
    {
        case (personality_type :: ATTACKER):
            setCost(ATTACKER_COST);
            Attack = ATTACKER_ATTACK;
            Defense = ATTACKER_DEFENSE;
            Honor = ATTACKER_HONOR;
            break;
        case (personality_type :: DEFENDER):
            setCost(DEFENDER_COST);
            Attack = DEFNEDER_ATTACK;
            Defense = DEFNEDER_DEFENSE;
            Honor = DEFNEDER_HONOR;
            break;
        case (personality_type :: SHOGUN):
            setCost(SHOGUN_COST);
            Attack = SHOGUN_ATTACK;
            Defense = SHOGUN_DEFENSE;
            Honor = SHOGUN_HONOR;
            break;
        case (personality_type :: CHANCELLOR):
            setCost(CHANCELLOR_COST);
            Attack = CHANCELLOR_ATTACK;
            Defense = CHANCELLOR_DEFENSE;
            Honor = CHANCELLOR_HONOR;
            break;
        case (personality_type :: CHAMPION):
            setCost(CHAMPION_COST);
            Attack = CHAMPION_ATTACK;
            Defense = CHAMPION_DEFENSE;
            Honor = CHAMPION_HONOR;
            break;
        default :
            break;
    }
}

Personality :: ~Personality(){}

card_type Personality :: getType() const
{
    return BlackCard :: getType();
}

/**
 * Provides the specified follower to the Personality, to be attached to it.
 */
void Personality :: provideFollower(Follower* f)
{
    if (numberOfFollowers < MAX_PROV_FOLLOWERS)             // Checking if the maximum number of followers has been reached
    {
        followers.push_back(f);
        numberOfFollowers++;
    }
    else
    {
        cout << "Max number of Followers has been reached for this Personality" << endl;
    }    
}

/**
 * Provides the specified item to the Personality, to be attached to it.
 */
void Personality :: provideItem(Item* i)
{
    if (numberOfItems < MAX_PROV_ITEMS)                     // Checking if the maximum number of items has been reached
    {
        items.push_back(i);
        numberOfItems++;
    }
    else
    {
        cout << "Max number of Items has been reached for this Personality" << endl;
    }    
}

/**
 * Prints the Personality card details.
 */
void Personality :: print()  const
{
    this -> BlackCard :: print();                           // Printing the BlackCard :: part of the Personality

    switch(type)                                            // Printing the specific Personality type
    {
        case (personality_type :: ATTACKER):
            cout << "Personality Type: Attacker" << endl;
            break;
        case (personality_type :: DEFENDER):
            cout << "Personality Type: Defender" << endl;
            break;
        case (personality_type :: SHOGUN):
            cout << "Personality Type: Shogun" << endl;
            break;
        case (personality_type :: CHANCELLOR):
            cout << "Personality Type: Chancellor" << endl;
            break;
        case (personality_type :: CHAMPION):
            cout << "Personality Type: Champion" << endl;
            break;
        default:
            // problem
            break;
    }

    // Printing the rest of the Personality Attributes and Details
    cout << "Attack: " << Attack << endl << "Defense: " << Defense << endl << "Honor: " << Honor << endl;
    if(isDead)
    {
        cout << "Situation: Dead" << endl;
    }
    else
    {
        cout << "Situation: Alive" << endl;
    }
}

/**
 * Prints all the attached Followers of the Personality.
 */
void Personality :: printFollowers() const
{
    int counter = 1;
    list<Follower*> :: const_iterator itr;
    for ( itr = followers.begin(); itr != followers.end() ; itr++ )
    {
        cout << "Personality Follower: " << counter << endl;
        (*itr)->print();
        counter++;
    }
}

/**
 * Prints all the attached Items of the Personality.
 */
void Personality :: printItems() const
{
    int counter = 1;
    list<Item*> :: const_iterator itr;
    for ( itr = items.begin(); itr != items.end(); itr++ )
    {
        cout << "Personality Item: " << counter << endl;
        (*itr)->print();
        counter++;
    }
}

int Personality :: getHonor() const
{
    return Honor;
}

int Personality ::getAttack() const
{
    return Attack;
}

int Personality ::getDefense() const
{
    return Defense;
}

int Personality :: getNumberOfFollowers() const
{
    return numberOfFollowers;
}

void Personality :: setHonor(int value)
{
    Honor = value;
}

bool Personality ::dead() const
{
    return isDead;
}

/**
 *  Sets the Personality to be shown as dead.
 */
void Personality ::makeDead()
{
    isDead = true;
}

/**
 * Returns TRUE if the maximum number of attached Followers has been reached, FALSE otherwise.
 */
bool Personality :: maxFollowersReached() const
{
    if ( numberOfFollowers == MAX_PROV_FOLLOWERS )
    {
        return true;
    }
    else
    {
        return false;
    }    
}

/**
 * Returns TRUE if the maximum number of attached Items has been reached, FALSE otherwise.
 */
bool Personality :: maxItemsReached() const
{
    if ( numberOfItems == MAX_PROV_ITEMS )
    {
        return true;
    }
    else
    {
        return false;
    }    
}

void Personality :: performSeppuku()
{
    this->makeDead();
}

/**
 * Returns the total sum of the Personality Attack and the Attack Bonuses of the attachments.
 */
int Personality :: attackPower()
{
    int sum = 0;
    list<Follower*> :: const_iterator f;
    list<Item*> :: const_iterator i;

    sum += Attack;                                          // Including the Personality Attack attribute in the sum
    for( f = followers.begin(); f != followers.end(); f++ )
    {
        sum += (*f)->getAttackBonus();                      // Including the Attack Bonuses of the attached Followers
    }
    for( i = items.begin(); i != items.end(); i++ )
    {
        sum += (*i)->getAttackBonus();                      // Including the Attack Bonuses of the attached Items
    }
    return sum;
}

/**
 * Returns the total sum of the Personality Defense and the Defense Bonuses of the attachments.
 */
int Personality :: defensePower()
{
    int sum = 0;
    list<Follower*> :: const_iterator f;
    list<Item*> :: const_iterator i;

    sum += Defense;                                         // Including the Personality Defense attribute in the sum
    for( f = followers.begin(); f != followers.end(); f++ )
    {
        sum += (*f)->getDefenseBonus();                     // Including the Defense Bonuses of the attached Followers
    }
    for( i = items.begin(); i != items.end(); i++ )
    {
        sum += (*i)->getDefenseBonus();                     // Including the Defense Bonuses of the attached Items
    }
    return sum;
}

/**
 * Discards all the Personality attachments (followers & items).
 */
void Personality :: detachDiscardAttachments()
{
    list<Follower*> :: iterator f;
    list<Item*> :: iterator i;
    for( f = followers.begin(); f != followers.end(); f++ )
    {
        discard(*f);
    }
    followers.clear();
    for( i = items.begin(); i != items.end(); f++ )
    {
        discard(*i);
    }
    items.clear();
}

/**
 * Discards #n follower (1 == 1st, 2 == 2nd etc.), and returns the attack and defense attributes of it.
 * @param n The number of the follower to be discarded
 * @param attack_power The Attack Bonus attribute of the Follower will be stored here
 * @param defense_power The Defense Bonus attribute of the Follower will be stored here
 * @return Returns 1 if the Follower is succesfully discarded, 0 otherwise.
 */
int Personality :: detachDiscardFollower(int n, int& attack_power, int& defense_power)
{
    if ( n > followers.size() || n < 1 )
    {
        cout << "Invalid number of follower to be detached" << endl;
        return 0;
    }
    else
    {
        int counter = 1;
        list<Follower*> :: iterator f;
        for ( f = followers.begin(); f != followers.end(); f++ )
        {
            if ( counter == n )                                     // Finding the specified follower
            {
                attack_power = (*f)->getAttackBonus();              // Storing Attack bonus in attack_power
                defense_power = (*f)->getDefenseBonus();            // Storing Defense bonus in defense_power
                discard(*f);                                        // Discarding the follower card
                followers.remove(*f);                               // Removing the address of it from the list
                break;
            }
            counter++;
        }
        return 1;
    }    
}

/**
 *  Scans the attached Items. If any of them has durability == 0, it is discarded.
 */
void Personality :: checkDiscardItems()
{
    list<Item*> :: iterator i;
    for ( i = items.begin(); i != items.end(); i++)
    {
        if ( (*i)->getDurability() == 0 )       // if this item has durability == 0
        {
            discard(*i);                        // discard it
            *i = NULL;                          // flag the corresponding node of the items list as NULL
        }
    }
    items.remove(NULL);                         // delete all the nodes with value == NULL (the nodes of the discarded items)
}

/**
 *  Scans the attached Followers. If any of them has minimum honor greater than the Personality honor, it is discarded.
 */
void Personality :: checkDiscardFollowers()
{
    list<Follower*> :: iterator f;
    for ( f = followers.begin(); f != followers.end(); f++)
    {
        if ( (*f)->getMinimumHonor() > this->Honor )        // if this follower has greater minimum honor than the Personality,
        {                                                   // it must be discarded
            discard(*f);                                    // discard it
            *f = NULL;                                      // flag the corresponding node of the followers list as NULL
        }
    }
    followers.remove(NULL);                                 // delete all the nodes with value == NULL (the nodes of the discarded followers)
}

/**
 *  Reduces all the Items durabilty by 1.
 */
void Personality :: reduceItemsDurability()
{
    list<Item*> :: iterator i;
    for ( i = items.begin(); i != items.end(); i++)
    {
        (*i)->reduceDurability();
    }    
}

/**
 * Taps all the Followers of the Personality.
 */
void Personality :: tapFollowers()
{
    list<Follower*> :: iterator f;
    for (f = followers.begin(); f != followers.end(); f++)
    {
        (*f)->tap();
    }    
}

/**
 * Untaps all the Followers of the Personality.
 */
void Personality :: untapFollowers()
{
    list<Follower*> :: iterator f;
    for (f = followers.begin(); f != followers.end(); f++)
    {
        (*f)->untap();
    }
}

// Attacker methods

Attacker :: Attacker(const char* name)
: Personality(name, personality_type :: ATTACKER)
{

}

// Defender methods

Defender :: Defender(const char* name)
: Personality(name, personality_type :: DEFENDER)
{

}

// Shogun methods

Shogun :: Shogun(const char* name)
: Personality(name, personality_type :: SHOGUN)
{

}

// Chancellor methods

Chancellor :: Chancellor(const char* name)
: Personality(name, personality_type :: CHANCELLOR)
{

}

// Champion methods

Champion :: Champion(const char* name)
: Personality(name, personality_type :: CHAMPION)
{

}