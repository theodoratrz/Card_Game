#ifndef FOLLOWER_HPP
#define FOLLOWER_HPP

#include "Card.hpp"

enum class follower_type{FOOTSOLDIER, ARCHER, SIEGER, CAVALRY, NAVAL, BUSHIDO};

class Follower : public GreenCard
{
    follower_type type;

    public:
    Follower(const char* n, follower_type t);
    virtual ~Follower() = 0;
    card_type getType();                                                // Returns the type (card_type) of the Card.
    void print() const;                                                 // Prints the Follower card details.
};

class Footsoldier : public Follower
{
    public:
    Footsoldier(const char* name);
};

class Archer : public Follower
{
    public:
    Archer(const char* name);
};

class Sieger : public Follower
{
    public:
    Sieger(const char* name);
};

class Cavalry : public Follower
{
    public:
    Cavalry(const char* name);
};

class Atakebune : public Follower
{
    public:
    Atakebune(const char* name);
};

class Bushido : public Follower
{
    public:
    Bushido(const char* name);
};

#endif