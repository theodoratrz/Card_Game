#ifndef PERSONALITY_HPP
#define PERSONALITY_HPP

#include "Card.hpp"
#include "Item.hpp"
#include "Follower.hpp"
#include <list>
#include "DeckBuilder.hpp"

using namespace std;

#define MAX_PROV_FOLLOWERS      NO_FOLLOWERS/7
#define MAX_PROV_ITEMS          NO_ITEMS/3


enum class personality_type {ATTACKER, DEFENDER, SHOGUN, CHANCELLOR, CHAMPION};     // Different Personality types

class Personality : public BlackCard
{
    personality_type type;                                                          // Specific Personality type
    int Attack;                                                                     // Attributes
    int Defense;
    int Honor;
    bool isDead;
    list<Follower*> followers;                                                      // Attached followers
    int numberOfFollowers;
    list<Item*> items;                                                              // Attached Items
    int numberOfItems;

    public:
    Personality(const char* n, personality_type t);
    virtual ~Personality() = 0;
    card_type getType() const;                                                      // Returns the type (card_type) of the Card.
    void provideFollower(Follower* f);                                              // Provides the specified follower to the Personality, to be attached to it.
    void provideItem(Item* i);                                                      // Provides the specified item to the Personality, to be attached to it.
    void print() const;                                                             // Prints the Personality card details.
    void printFollowers() const;                                                    // Prints all the attached Followers of the Personality.
    void printItems() const;                                                        // Prints all the attached Items of the Personality.
    int getHonor() const;
    int getAttack() const;
    int getDefense() const;
    int getNumberOfFollowers() const;
    void setHonor(int value);
    bool dead() const;                                                              // Returns TRUE if the Personality is dead, FALSE othewise.
    void makeDead();                                                                // Sets the Personality to be shown as dead.
    bool maxFollowersReached() const;                                               // Returns TRUE if the maximum number of attached Followers has been reached, FALSE otherwise.
    bool maxItemsReached() const;                                                   // Returns TRUE if the maximum number of attached Items has been reached, FALSE otherwise.
    void performSeppuku();
    int attackPower();                                                              // Returns the total sum of the Personality Attack and the Attack Bonuses of the attachments.
    int defensePower();                                                             // Returns the total sum of the Personality Defense and the Defense Bonuses of the attachments.
    void detachDiscardAttachments();                                                // Discards all the Personality attachments (followers & items).
    int detachDiscardFollower(int n, int& attack_power, int& defense_power);        // Discards #n follower (1 == 1st, 2 == 2nd etc.), and returns the attack and defense attributes of it.
    void checkDiscardItems();                                                       // Scans the attached Items. If any of them has durability == 0, it is discarded.
    void checkDiscardFollowers();                                                   // Scans the attached Followers. If any of them has minimum honor greater than the Personality honor, it is discarded.
    void reduceItemsDurability();                                                   // Reduces all the Items durabilty by 1.
    void tapFollowers();                                                            // Taps all the Followers of the Personality.
    void untapFollowers();                                                          // Untaps all the Followers of the Personality.
};

class Attacker : public Personality
{
    public:
    Attacker(const char* name);
};

class Defender : public Personality
{
    public:
    Defender(const char* name);
};

class Shogun : public Personality
{
    public:
    Shogun(const char* name);
};

class Chancellor : public Personality
{
    public:
    Chancellor(const char* name);
};

class Champion : public Personality
{
    public:
    Champion(const char* name);
};

#endif