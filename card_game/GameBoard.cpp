#include "GameBoard.hpp"
#include <iostream>
#include "Card.hpp"
#include "DeckBuilder.hpp"
#include "Personality.hpp"
#include "Holding.hpp"
#include "Follower.hpp"
#include "Item.hpp"

using namespace std;

/**
 *  Creates a Player with name n
 *  @param n The Player's name
 */
Player :: Player(string n)
: name(n), deck(NULL), honor(-1), money(-1), initialDefense(-1), hand(NULL), dynastyDeck(NULL),
 fateDeck(NULL), numberOfProvinces(-1), provinces(NULL), holdings(NULL), army(NULL), stronghold(NULL)
{
    deck = new DeckBuilder();                                   // Creating the player's deck
    deck->createDynastyDeck();
    deck->createFateDeck();
    hand = new list<GreenCard*>();                              // Creating lists for the player's different cards
    holdings = new list<Holding*>();
    army = new list<Personality*>();
    provinces = new list<BlackCard*>();
}

Player :: ~Player()
{
    // Note: the player cards should be deleted first using discardCards()
    delete provinces;
    delete army;
    delete holdings;
    delete hand;
    delete deck;
}

string Player :: getName() const
{
    return name;
}

int Player :: getMoney() const
{
    return money;
}

int Player :: getHonor() const
{
    return honor;
}

void Player :: setHonor(int value)
{
    honor = value;
}

void Player :: setMoney(int value)
{
    money = value;
}

/**
 *  Does the Player preperation for the game.
 *  @param s The player's stronghold, which provides some of his stats
 */
void Player :: prepare(Stronghold* s)
{
    dynastyDeck = deck->getDynastyDeck();                               // "seperating" the player deck
    fateDeck = deck->getFateDeck();
    deck->deckShuffler(dynastyDeck);                                    // shuffling the 2 decks
    deck->deckShuffler(fateDeck);
    
    int i;
    GreenCard* hand_card;
    BlackCard* province_card;
    for( i = 0; i < STARTING_HAND; i++ )
    {
        hand_card = drawFateCard();                                     // Drawing the first fate cards
        addHand(hand_card);                                             // Adding them to the Player's hand
    }
    for ( i = 0; i < STARTING_PROVINCES; i++ )
    {
        province_card = drawDynastyCard();                              // Drawing the first Player's province cards
        addProvince(province_card);                                     // Adding them to the Province list
    }
    numberOfProvinces = STARTING_PROVINCES;
    stronghold = s;                                                     // Providing the Stronghold to player
    honor = stronghold->getHonor();                                     // Getting Player's stats
    money = stronghold->getMoney();
    initialDefense = stronghold->getDefense();
    addHolding(stronghold);                                             // The Stronghold is the first holding of the Player
}

/**
 *  Adds a Green Card to the player's hand.
 */
void Player :: addHand(GreenCard* card)
{
    hand->push_back(card);
}

/**
 *  Adds a Card to the Player's holdings.
 */
void Player :: addHolding(BlackCard* card)
{
    if (card->getType() != card_type :: HOLDING)
    {
        cout << "The selected card is not a Holding." << endl;
        return;
    }
    holdings->push_back( (Holding*)card );
}

/**
 *  Adds a Black Card to the Player's army (provided that it is a Personality).
 */
void Player :: addArmy(BlackCard* card)
{
    if (card->getType() != card_type :: PERSONALITY)
    {
        cout << "The selected card is not a Personality." << endl;
        return;
    }
    army->push_back( (Personality*)card );
}

/**
 *  Used in battles. Allows the player to choose the Army Personalities to use in a battle.
 *  Returns a list with the player's choices.
 */
list<Personality*> Player :: chooseArmy()
{
    list<Personality*> chosen_army;                                     // The chosen army personalitites are stored here
    list<Personality*> available_army;                                  // The available army personalitties are stored here
    list<Personality*> :: iterator itr;
    int a, counter;
    printArmy();
    available_army = *army;                                             // At first, all the army personalitties are available
    do {
        cout << "Choose army Personalities to use. Enter 0 if ready." << endl;
        cin >> a;                                                       // The number of Personality to include to the army
        if( a > 0 && a <= army->size() )
        {
            counter = 1;
            for ( itr = available_army.begin(); itr != available_army.end(); itr++ )
            {
                if ( counter == a )
                {
                    if (*itr == NULL )
                    {
                        cout << "Already chosen personality." << endl;
                    }
                    else if ( (*itr)->tapped() )
                    {
                        cout << "The selected personality has been tapped, therefore it can't be used." << endl;
                    }                    
                    else
                    {
                        chosen_army.push_back(*itr);                    // Including the chosen Personality to the chosen_army
                        *itr = NULL;                                    // Flag it in the available_army to avoid selecting it again
                        cout << "Personality included succesfully" << endl;
                    }
                    break;
                }
                counter++;
            }
        }
    } while (a != 0);
    return chosen_army;                                                 // Return the player's choices
}

/**
 *  Adds a Black Card to the Player's provinces.
 */
void Player :: addProvince(BlackCard* card)
{
    provinces->push_back(card);
    numberOfProvinces++;
}

/**
 *  Draws the card #i from the player's hand (1 == 1st card, 2 == 2nd etc.),
 *  and returns it.
 */
GreenCard* Player :: drawHand(int i)
{
    int counter = 1;
    list<GreenCard*> :: iterator it;
    for ( it = hand->begin(); it != hand->end(); it++ )
    {
        if ( counter == i )                                 // Finding the asked card in the player's hand
        {
            GreenCard* temp = *it;
            hand->remove(*it);                              // Remove it from the hand
            return temp;                                    // And return it
        }
        counter++;
    }
    cout << "No card with the asked index exists." << endl;
    return NULL;
}

/**
 *  Draws a Card from the player's Dynasty Deck and returns it.
 */
BlackCard* Player :: drawDynastyCard()
{
    BlackCard* card;
    card = dynastyDeck->front();                            // Draw the first card of the deck (take the address of it and remove it from the deck)
    dynastyDeck->pop_front();
    return card;
}

/**
 *  Draws a Card from the player's Fate Deck and returns it.
 */
GreenCard* Player :: drawFateCard()
{
    GreenCard* card;
    card = fateDeck->front();                               // Draw the first card of the deck (take the address of it and remove it from the deck)
    fateDeck->pop_front();
    return card;
}

/**
 *  Prints the Cards of the player's hand.
 */
void Player :: printHand() const
{
    int counter = 1;
    list<GreenCard *> :: const_iterator h;
    cout << "Player's Hand:" << endl;
	for (h = hand->begin(); h != hand->end(); h++)
    {
        cout << counter << ". ";                            // Output will look like: 1. <Card info> \n 2.<Card info> \n etc.
        (*h)->print();
        cout << endl;
        counter++;
    }
}

/**
 *  Prints the player's Holdings.
 */
void Player :: printHoldings() const
{
    int counter = 1;
    list<Holding *> :: const_iterator h;
    cout << "Player's Holdings:" << endl;
	for (h = holdings->begin(); h != holdings->end(); h++)
    {
        cout << counter << ". ";
        (*h)->print();
        cout << endl;
        counter++;
    }
}

/**
 *  Prints the player's provinces.
 */
void Player :: printProvinces() const
{
    int counter = 1;
    list<BlackCard *>::iterator p;
    cout << "Player's Provinces:" << endl;
	for (p = provinces->begin(); p != provinces->end(); p++)
    {
        cout << counter << ". ";
        if ( (*p)->Revealed() )
        {
            (*p)->print();
        }
        else
        {
            cout << "Unrevealed Province" << endl;                              // If the Province card has not been revealed, the details of it are not printed.
        }        
        cout << endl;
        counter++;
    }
}

/**
 *  Prints the Personalities of the player's army, along with the attached followers and Items.
 */
void Player :: printArmy() const
{
    int counter = 1;
    list<Personality *>::iterator p;
    cout << "Player's Army:" << endl;
	for (p = army->begin(); p != army->end(); p++)
    {
        cout << "Persnonality " << counter << ":";
        (*p)->print();
        cout << "Personality Followers:" << endl;
        (*p)->printFollowers();
        cout << "Personality Items:" << endl;
        (*p)->printItems();
        cout << endl;
        counter++;
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

/**
 *  Makes all the available connections between Mines of the player's holdings.
 */
void Player :: connectMines()
{
	list <Holding*> mines;
	list<Holding*> :: iterator ptr;
	list<Holding*> :: iterator temp;

	for(ptr = holdings->begin(); ptr != holdings->end(); ptr++)
	{
		if( (*ptr) -> getHoldingType() == holding_type :: MINE )
		{
			mines.push_back((*ptr));
			continue;
		}
		if( (*ptr)-> getHoldingType() == holding_type :: GOLD_MINE )
		{
			mines.push_back((*ptr));
			continue;
		}
		if( (*ptr)-> getHoldingType() == holding_type :: CRYSTAL_MINE )
		{
			mines.push_back((*ptr));
			continue;
		}
	}
	for(ptr = mines.begin(); ptr != mines.end(); ptr++)
	{
		switch( (*ptr)-> getHoldingType() )
		{
			case holding_type :: MINE:
				for(temp = mines.begin(); temp != mines.end(); temp++)
				{
					(*ptr)->connectUpperHolding(*temp);                    
				}
                ( (Mine*)(*ptr) )->checkUpperBonus();
			    break;
			case holding_type :: GOLD_MINE:
				for(temp = mines.begin(); temp != mines.end(); temp++)
				{
					(*ptr)->connectUpperHolding(*temp);                    
					(*ptr)->connectSubHolding(*temp);
				}
                ( (GoldMine*)(*ptr) )->checkUpperBonus();
                ( (GoldMine*)(*ptr) )->checkSubBonus();
                ( (GoldMine*)(*ptr) )->checkChainBonus();
			    break;
			case holding_type :: CRYSTAL_MINE:
				for(temp = mines.begin(); temp != mines.end(); temp++)
				{
					(*ptr)->connectSubHolding(*temp);
				}
                ( (CrystalMine*)(*ptr) )->checkSubBonus();
			    break;
			default:
				break;
		}
	}
}

/**
 *  Makes all the player's provinces revealed.
 */
void Player :: revealProvinces()
{
	list<BlackCard *> :: iterator ptr;
	int counter = 1;

	for(ptr = provinces->begin(); ptr != provinces->end(); ptr++)
	{
		(*ptr)->setRevealed(true);
	}

	cout << "All available provinces are revealed" << endl;
}

/**
 *  Makes all the player's holdings and army untapped.
 */
void Player :: untapEverything()
{
	list<Holding*> :: iterator h;

    // Untapping the player's holding cards.
	for(h = holdings->begin(); h != holdings->end(); h++)
	{
		(*h)->untap();
	}
    // Untapping the player's army Personalities, along with any tapped followers.
    list<Personality*> :: iterator p;
	for(p = army->begin(); p != army->end(); p++)
	{
		(*p)->untap();
        (*p)->untapFollowers();
	}

	cout << "All cards have been untapped" << endl;
}

list <Personality*>* Player :: getArmy() const
{
    return army;
}

list <GreenCard*>* Player :: getHand() const
{
    return hand;
}

int Player :: getNumberOfProvinces() const
{
    return numberOfProvinces;
}

int Player :: getInitialDefense() const
{
    return initialDefense;
}

void Player :: setInitialDefense(int value)
{
    initialDefense = value;
}

/**
 *  Used to make purchases by tapping Holding cards.
 *  @param difference Amount of money that must be balanced through tapping.
 */
int Player :: tapCoverCost(int difference)
{
    if ( holdings->empty() )
    {
        cout << "This player has no holdings. Unable to make the selected purchase." << endl;
        return 0;
    }

    printHoldings();
    int dif_left = difference;
    int i;
    list<Holding*> :: iterator itr;
    int counter = 1;
    bool break_loop = false;
    do {
        cout << "Enter the number of a holding you wish to tap in order to make the purchase. Enter 0 to cancel" << endl;
        cin >> i;
        if (i == 0)
        {
            cout << "Purchase cancelled." << endl;
            return 0;
        }
        else if ( i > holdings->size() || i < 0 )
        {
            cout << "Invalid number given." << endl;
        }
        else
        {
            for( itr = holdings->begin(); itr != holdings->end(); itr++ )
            {
                if (counter == i)
                {
                    if ( (*itr)->tapped() )
                    {
                        cout << "This Holding has already been tapped." << endl;
                        break;
                    }
                    else
                    {
                        difference = difference - (*itr)->getHarvest();
                        (*itr)->tap();
                        cout << "Holding: " << i << " has been tapped." << endl;
                        if (difference <= 0)
                        {
                            cout << "Now able to make pruchase." << endl;
                            return 1;
                        }
                        else
                        {
                            cout << "More Holdings need to be tapped" << endl;
                            break;
                        }
                    }     
                }
                counter ++;
            }
        }
    } while (!break_loop);
    return 0;
}

/**
 *  Used to purchase and activate the bonus of the specified Green Card.
 */
void Player :: purchaseActivateBonus(GreenCard* card)
{
	int purchase_made = false;
    char ch;
	if ( money < card->getEffectCost() )
	{
        cout << "Player money not enough to purchase bonus for the selected card."
        << "Would you like to tap any Holding cards to be able to buy it? [y/n]" << endl;
        cin >> ch;
        if ( ch == 'y' )
        {
            if ( tapCoverCost(card->getEffectCost() - money) == 0)
            {
                return;
            }
            else
            {
                money = 0;
                purchase_made = true;
            }
        }
        else
        {
        	cout << "Cancelling bonus purchase" << endl;
            return;
        }
	}
	else
	{
		money = money - card->getEffectCost();
		purchase_made = true;
	}
	if ( purchase_made )
	{
		card->activateBonus();
		cout << "Bonus activated" << endl;
	}
}

/**
 *  Used to purchase the specified Green Card.
 *  @param card The Green Card to be purchased.
 */
void Player :: purchaseProvideGreenCard(GreenCard* card)
{
	if(army->empty())
	{
		cout << "This player has no army." << endl;
	}
	else
	{
        printArmy();
        bool purchase_made;
        int i;
        list<Personality*> :: iterator ptr;
        char ch;
        bool break_loop = false;
        int counter;
	    do {
		    cout << "Choose a Personality from the army to provide the selected green card. Press 0 to exit." << endl;
		    cin >> i;
		    if ( i == 0)
		    {
		    	cout << "Cancelling purchase" << endl;
		    	return;
		    }
			else if ( i > army->size() || i < 0)
			{
				cout << "Invalid number given." << endl;
			}
			else
			{
				counter = 1;	            
				for(ptr = army->begin(); ptr != army->end(); ptr++)
				{
					if(i == counter)
					{
						if ( card->getMinimumHonor() > (*ptr)->getHonor() )
	                    {
	                        cout << "The selected green card requires a greater honor than the one of the chosen personality." << endl;
	                        break;
	                    }
	                    if( card->getType() == card_type :: FOLLOWER )
						{
							if ( (*ptr)->maxFollowersReached() )
							{
								cout << "Max number of followers reached for this Personality" << endl;
								break;
							}
						}
						else if( card->getType() == card_type :: ITEM )
						{
							if ( (*ptr)->maxItemsReached() )
							{
								cout << "Max number of items reached for this Personality" << endl;
								break;
							}
						}
						if ( money < card->getCost() )
						{
	                        cout << "Player money not enough to buy the selected card."
	                        << "Would you like to tap any Holding cards to be able to buy it? [y/n]" << endl;
	                        cin >> ch;
	                        if ( ch == 'y' )
	                        {
	                            if ( tapCoverCost(card->getCost() - money) == 0)
	                            {
	                                return;
	                            }
	                            else
	                            {
	                                money = 0;
	                                purchase_made = true;
                                    break_loop = true;
	                            }
	                        }
	                        else
	                        {
                                cout << "Purchase Cancelled" << endl;
	                            return;
	                        }
						}
						else
						{
							money = money - card->getCost();
							purchase_made = true;
                            break_loop = true;
						}                        
						break;
					}
                    counter++;
				}
			}
		} while(!break_loop);

		if ( purchase_made )
		{
			if(card->getType() == card_type :: FOLLOWER)
			{
				(*ptr)->provideFollower( (Follower*)card );
			}
			else if(card->getType() == card_type :: ITEM)
			{
				(*ptr)->provideItem( (Item*)card );
			}
            hand->remove(card);
            cout << "Purchase Made!" << endl;
			cout << "Do you want to activate bonus for the selected green card? (Cost: " << card->getEffectCost() << ") [y/n]" << endl;
            cin >> ch;
			if(ch == 'y')
			{
				purchaseActivateBonus(card);
			}
		}
	}
}

/**
 *  Used to purchase provinces.
 */
void Player :: purchaseProvinces()
{
    int n;
    char c;
    BlackCard* new_province;
    int counter;
    list<BlackCard*> :: iterator itr;
    bool purchase_made;
    bool exit_loop = false;
    do 
    {
        purchase_made = false;
        cout << "Player money: " << money << endl;
        cout << "Do you want to buy any available provinces? [y/n]" << endl;
        cin >> c;
        if ( c == 'n')
        {
            return;
        }
        else if(c == 'y')
        {
            cout << "The available provinces are: " << endl;
            printProvinces();
            cout << "Which one would you like to purchase?" << endl;
            cin >> n;
            if ( n <= 0 || n > provinces->size() )
            {
                cout << "Invalid number." << endl;
                continue;
            }
            counter = 1;
            for(itr = provinces->begin(); itr != provinces->end(); itr++)
            {
                if(n == counter)
                {
                    if( (*itr)->Revealed() )
                    {
                        cout << "Province cost: " << (*itr)->getCost() << endl;
                        cout << "Proceed? [y/n]" << endl;
                        cin >> c;
                        if(c == 'y')
                        {
                            if(money < (*itr)->getCost())
                            {
                                cout << "Player money not enough to buy the selected card."
	                            << "Would you like to tap any Holding cards to be able to buy it? [y/n]" << endl;
                                cin >> c;
                                if ( c == 'y' )
                                {
                                    if ( tapCoverCost( (*itr)->getCost() - money ) == 0)
                                    {
                                        return;
                                    }
                                    else
                                    {
                                        money = 0;
                                        purchase_made = true;
                                    }
                                }
                                else
                                {
                                    cout << "Purchase cancelled." << endl;
                                }                                
                            }
                            else
                            {
                                money = money - (*itr)->getCost();
                                purchase_made = true;
                            }                            
                        }
                    }
                    else
                    {
                        cout << "The selected province is not revealed." << endl;
                    }                    
                    break;
                }
                counter++;
            }
        }
        if (purchase_made)
        {
            cout << "Purchase completed!" << endl;
            if((*itr)->getType() == card_type :: HOLDING)
            {
                addHolding(*itr);
            }
            else if((*itr)->getType() == card_type :: PERSONALITY)
            {
                addArmy(*itr);
            }
            provinces->remove(*itr);
            new_province = drawDynastyCard();
            provinces->push_back(new_province);
        }
    } while (!exit_loop);
}

/**
 *  Used to make the required sacrifices out of the specified defending army.
 *  @param difference The defense points that must be balanced through sacrificing.
 *  @param used_army The player's used army Personalities.
 */
void Player :: sacrificeDefendingArmy(int difference, list <Personality*>& used_army)
{
    int i, counter, follower_attack, follower_defense;
    list<Personality*> :: iterator p;
    list<Follower*> :: iterator f;
    bool break_loop = false;

    cout << "Defender must sacrifice used Persnonality/Followers with total defense bonus: " << difference << endl;
    do
    {
        cout << "Defender used army to sacrifice:" << endl;
        printUsedArmy(used_army);
        cout << "Enter the number of a used Personality: " << endl;
        cin >> i;
        if ( i > used_army.size() || i <= 0 )
        {
            cout << "Invalid number given." << endl;
        }
        else
        {
            counter = 1;
            for ( p = used_army.begin(); p != used_army.end(); p++ )
            {
                if (counter == i)
                {
                    cout << "Enter 0 to sacrifice the chosen personality, along with the attached followers/items." 
                    << endl << "Enter 1 to sacrifice a Follower attached to this Personality." << endl;
                    cin >> i;
                    if (i == 0)
                    {
                        difference = difference - (*p)->defensePower();
                        (*p)->detachDiscardAttachments();
                        army->remove(*p);
                        discard(*p);
                        used_army.remove(*p);
                        cout << "Personality: " << i << " has been sacrificed along with its attachments." << endl;
                    }
                    else if (i == 1)
                    {
                        (*p)->printFollowers();
                        cout << "Enter number of follower to sacrifice:" << endl;
                        cin >> i;
                        if ( i > ( (*p)->getNumberOfFollowers() || i < 1) )
                        {
                            cout << "Invalid input." << endl;
                            break;
                        }
                        else
                        {
                            if ( (*p)->detachDiscardFollower(i, follower_attack, follower_defense) )
                            {
                                difference = difference - follower_defense;
                                cout << "Follower " << i << " has been sacrificed succesfully." << endl;
                            }                            
                        }                        
                    }
                    else
                    {
                        cout << "Wrong input." << endl;
                        break;
                    }
                    if (difference <= 0)
                    {
                        cout << "No more army is needed to be sacrificed." << endl;
                        return;
                    }
                    else
                    {
                        cout << "More Holdings need to be tapped" << endl;
                        break;
                    }
                }
                counter++;
            }            
        }
    } while (!break_loop);    
}

/**
 *  Used to make the required sacrifices out of the specified attacking army.
 *  @param difference The attack points that must be balanced through sacrificing.
 *  @param used_army The player's used army Personalities.
 */
void Player :: sacrificeAttackingArmy(int difference, list<Personality*>& used_army)
{
    int i, counter, follower_attack, follower_defense;
    list<Personality*> :: iterator p;
    list<Follower*> :: iterator f;
    bool break_loop = false;

    cout << "Attacker must sacrifice used Persnonality/Followers with total attack bonus: " << difference << endl;
    do
    {
        cout << "Attacker used army to sacrifice:" << endl;
        printUsedArmy(used_army);
        cout << "Enter the number of a used Personality: " << endl;
        cin >> i;
        if ( i > used_army.size() || i <= 0 )
        {
            cout << "Invalid number given." << endl;
        }
        else
        {
            counter = 1;
            for ( p = used_army.begin(); p != used_army.end(); p++ )
            {
                if (counter == i)
                {
                    cout << "Enter 0 to sacrifice the chosen personality, along with the attached followers/items." 
                    << endl << "Enter 1 to sacrifice a Follower attached to this Personality." << endl;
                    cin >> i;
                    if (i == 0)
                    {
                        difference = difference - (*p)->attackPower();
                        (*p)->detachDiscardAttachments();
                        army->remove(*p);
                        discard(*p);
                        used_army.remove(*p);
                        cout << "Personality: " << i << " has been sacrificed along with its attachments." << endl;
                    }
                    else if (i == 1)
                    {
                        (*p)->printFollowers();
                        cout << "Enter number of follower to sacrifice:" << endl;
                        cin >> i;
                        if ( i > ( (*p)->getNumberOfFollowers() || i < 1) )
                        {
                            cout << "Invalid input." << endl;
                            break;
                        }
                        else
                        {
                            if ( (*p)->detachDiscardFollower(i, follower_attack, follower_defense) )
                            {
                                difference = difference - follower_attack;
                                cout << "Follower " << i << " has been sacrificed succesfully." << endl;
                            }                            
                        }                        
                    }
                    else
                    {
                        cout << "Wrong input." << endl;
                        break;
                    }
                    if (difference <= 0)
                    {
                        cout << "No more army is needed to be sacrificed." << endl;
                        return;
                    }
                    else
                    {
                        cout << "More Holdings need to be tapped" << endl;
                        break;
                    }
                }
                counter++;
            }            
        }
    } while (!break_loop);
}

/**
 * Discards any used army Personalities (along with their attachments)
 * @param used_army List of the used army Personalities.
 */
void Player :: loseUsedArmy(list<Personality*>& used_army)
{
    list<Personality*> :: iterator p;
    for ( p = used_army.begin(); p != used_army.end(); p++)
    {
        (*p)->detachDiscardAttachments();           // Discarding the Personality attachments
        discard(*p);                                // Discarding the Personality
        army->remove(*p);                           // Removing the Personality address from the Army List
    }
    used_army.clear();
}

/**
 *  Destroys the province pointed by the node n of the provinces list.
 *  (n == 0 => 1st node, n == 1 => 2nd node etc)
 */
void Player :: destroyProvince(int n)
{
    if ( n > numberOfProvinces )
    {
        return;
    }
    int counter = 0;
    list<BlackCard*> :: iterator b;
    for ( b = provinces->begin(); b != provinces->end(); b++)
    {
        if( counter == n )
        {
            discard(*b);
            provinces->remove(*b);
            numberOfProvinces--;
            break;
        }
        counter++;
    }    
}

/**
 *  Forces the player to discard hand cards in case the limit is exceeded.
 */
void Player :: discardSurplusFateCards()
{
	list<GreenCard*> :: iterator ptr;
	int n;
	int counter = 1;

    while(hand->size() > MAX_HAND)
    {
        cout << hand->size() - MAX_HAND << "cards from this player's hand need to be discarded." << endl;
		printHand();
		cout << "Choose which one to discard:" << endl;
		cin >> n;
		for(ptr = hand->begin(); ptr != hand->end(); ptr++)
		{
			if(counter == n)
			{
				discard(*ptr);
				hand->remove( (*ptr) );
				break;
			}
			counter++;
		}
    }
    cout << "No more cards from the player's hand need to be discarded." << endl;
}

/**
 *  Used to discard all of the player's cards.
 */
void Player :: discardCards()
{
    list<GreenCard*> :: iterator g;
    list<BlackCard*> :: iterator b;
    list<Holding*> :: iterator h;
    list<Personality*> :: iterator p;
    for( g = hand->begin(); g != hand->end(); g++ )
    {
        discard(*g);
    }
    hand->clear();
    for( h = holdings->begin(); h != holdings->end(); h++ )
    {
        discard(*h);
    }
    holdings->clear();
    for( p = army->begin(); p != army->end(); p++ )
    {
        (*p)->detachDiscardAttachments();
        discard(*p);
    }
    army->clear();
    for( b = provinces->begin(); b != provinces->end(); b++ )
    {
        discard(*b);
    }
    provinces->clear();    
}

/**
 * 
 */
void Player :: checkUsedArmyAttachments(list<Personality*> used_army)
{
    list<Personality*> :: iterator itr;
    for( itr = used_army.begin(); itr != used_army.end(); itr++ )
    {
        (*itr)->checkDiscardFollowers();
        (*itr)->checkDiscardItems();
        if( (*itr)->getHonor() == 0 )
        {
            (*itr)->performSeppuku();
            (*itr)->detachDiscardAttachments();
            discard(*itr);
            army->remove(*itr);
            *itr = NULL;
        }
    }
}

// Game Board methods

GameBoard :: GameBoard()
: numberOfPlayers(NOF_PLAYERS), players(NULL) {}

GameBoard :: ~GameBoard()
{
    if (players != NULL)
    {
        for ( int i = 0; i < numberOfPlayers; i++ )
        {
            delete (*players)[i];
        }
        players->clear();
        delete players;
    }
}

/**
 *  Makes the required initializations before the start of the game.
 *  NOTE: It is required to be called before gameplay().
 */
void GameBoard :: initializeGameBoard()
{
    players = new vector<Player*>();
    string temp("Player");
    for ( int i = 0; i < numberOfPlayers; i++ )
    {
        players->push_back( new Player( temp + to_string(i) ) );
    }
}

/**
 *  Prints the recorded game stats.
 */
void GameBoard :: printGameStatistics()
{
    for( int i = 0; i < numberOfPlayers; i++ )
    {
        cout << "Player: " << i << " : Provinces Left: " << (*players)[i]->getNumberOfProvinces() << endl;
    }
    // ...............
}

/**
 *  Does the required game preperation actions.
 *  NOTE: to be called after initializeGameBoard(), before gameplay()
 */
void GameBoard :: gamePreparation()
{
    int i;
    int money = 3;
    int defense;
    int honor = 7;
    Stronghold** strongholds;
    strongholds = new Stronghold* [NOF_PLAYERS];
    string name;
    
    for ( i = 0; i < numberOfPlayers; i++ )
    {
        name.assign("Stronghold");
        name.append( to_string(i) );
        strongholds[i] = new Stronghold( name.c_str() );
        strongholds[i]->setCost(0);
        strongholds[i]->setMoney(money++);
        strongholds[i]->setHonor(honor--);
        strongholds[i]->setRevealed(true);
    }
    for ( i = 0; i < numberOfPlayers; i++ )
    {
        (*players)[i]->prepare(strongholds[i]);
    }
}

void GameBoard :: startingPhase()
{
    GreenCard* drawn_card;
    int i;
    cout << "Starting phase begins" << endl;
	for(i = 0; i < NOF_PLAYERS; i++)
	{
        cout << "Starting phase for player: " << i << endl;
		(*players)[i]->untapEverything();
        drawn_card = (*players)[i]->drawFateCard();
		(*players)[i]->addHand( drawn_card );
        cout << "New fate card drawn and added in hand" << endl;
		(*players)[i]->revealProvinces();
		(*players)[i]->printHand();
		(*players)[i]->printProvinces();
    }
}

void GameBoard :: equipPhase()
{
    int n,i, counter;
    char ch;
    list<Personality*> :: iterator ptr;
    GreenCard* gr = NULL;                                           // Every chosen Green Card address is stored here

    cout << "Equip Phase Starting" << endl;
    for(n = 0; n < NOF_PLAYERS; n++)
    {
        cout << "Equip Phase for player: " << n << endl;

       	if( ((*players)[n]->getArmy())->empty() )   			    // if the list of army is not empty
       	{
       	    cout << "There is no army." << endl;
            continue;
        }
                                                                    // Then the player may purchase Green Cards from his hand to equip his army
   	    (*players)[n]->printArmy();
   	    (*players)[n]->printHand();
        cout<< "Do you wish to buy new green cards in order to equip your personalities? [y/n]" << endl;
        cin >> ch;
        while(ch == 'y')
        {
            (*players)[n]->printHand();
            cout << "Player money: " << (*players)[n]->getMoney() << endl;
           	cout << "Which green card from your hand would you like to buy?" <<endl;
           	cin >> i;
            
            if (i > ( (*players)[n]->getHand() )->size() )
            {
                cout << "Wrong green card number" << endl;
            }
            else
            {   
                gr = (*players)[n]->drawHand(i);
                if( gr != NULL )
                {
                    (*players)[n]->purchaseProvideGreenCard(gr);
                }
                else
                {
                    cout << "Invalid hand card number given." << endl;
                }                
            }
            cout << "Would like to buy any other card? [y/n]" <<endl;
            cin >> ch;
        }
    }
}

void GameBoard :: economyPhase()
{
    int i,n;
    char ch;
    BlackCard* b;
    int counter;
    list<BlackCard*> :: iterator itr;
    bool purchase_made;
    bool exit_loop = false;
    for(i = 0; i < NOF_PLAYERS; i++)
    {
        cout << "Economy Phase for player: " << i << endl;
        (*players)[i]->revealProvinces();
        (*players)[i]->printProvinces();
        (*players)[i]->purchaseProvinces();
        (*players)[i]->connectMines(); 
    }
    cout << "End of Economy Phase" << endl;
}

void GameBoard :: battlePhase()
{
    char c;
    int n;
    cout << "Battle Phase starting" << endl;
    for( int i = 0; i < numberOfPlayers; i++ )
    {
        cout << "Player " << i << ": Do you want to attack another player? [y/n]" << endl;
        cin >> c;
        if ( c == 'y' )
        {
            do 
            {
                cout << "Which player do you want to attack? Enter -1 to cancel attacking" << endl;
                cin >> n;
                if ( n < -1 || n > numberOfPlayers - 1 || n == i )
                {
                    cout << "Invalid Input" << endl;
                }
                else if ( n != -1 )
                {
                    cout << "Battle between players: " << i << " and " << n << " begins!" << endl;
                    battle( (*players)[i], (*players)[n] );
                    if( (*players)[n]->getNumberOfProvinces() == 0 )            // If the defending player has no more provinces
                    {
                        (*players)[n]->discardCards();
                        delete (*players)[n];                                   // He has lost the game and he is deleted
                        players->erase( players->begin() + n );                 // and removed from the players vector
                        numberOfPlayers--;
                        cout << "Player: " << n << " has lost the game." << endl;
                    }
                    break;
                }
                else
                {
                    cout << "Attack cancelled" << endl;
                }
            } while(n != -1);
        }
    }
}

void GameBoard :: finalPhase()
{
	int n;	
    for(n = 0; n < NOF_PLAYERS; n++)
    {
        if ( (*players)[n]->getHand()->size() > MAX_HAND )
        {
            cout << "Player " << n << " has too many cards in his hand" << endl;
            (*players)[n]->discardSurplusFateCards();
        }    	
    	(*players)[n]->printHand();
    	(*players)[n]->printProvinces();
    	(*players)[n]->printHoldings();
    	(*players)[n]->printArmy();
        (*players)[n]->setMoney(0);
    }
    printGameStatistics();
}

void GameBoard :: gameplay()
{
    while( !( checkWinningCondition() ) )                                           // Until we have a winner,
	{                                                                               // all the game phases are excecuted
		startingPhase();
		equipPhase();
		battlePhase();
		economyPhase();
		finalPhase();
	}
    cout << "Game is over. Winner: "<< (*players)[0]->getName() << endl;            // There is one player left, who is the winner of the game.
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------

/**
 *  Checks if there is a game winner.
 */
bool GameBoard :: checkWinningCondition()
{
	if(numberOfPlayers > 1)
	{
		return false;           // If there more than one players, the game has not finished yet
	}
	else                        // (numberOfPlayers should be 1)
	{
		return true;            // we have a winner!
	}
}

/**
 *  Makes actions that must take place after the game ends (discarding cards etc.)
 */
void GameBoard :: gameEnd()
{
    for ( int i = 0; i < numberOfPlayers; i++ )
    {
        (*players)[i]->discardCards();                  // Discarding the cards of the remaining players
    }
}

void GameBoard :: test()
{
    BlackCard* a1 = new Shogun("Isawa Shi en");
    BlackCard* a2 = new Champion("Mirimuto Enishi");
    BlackCard* a3 = new Defender("Footsoldiers");    
    (*players)[0]->addArmy(a1);
    (*players)[0]->printArmy();
    (*players)[1]->addArmy(a2);
    (*players)[1]->addArmy(a3);
    (*players)[1]->printArmy();
    (*players)[0]->revealProvinces();
    (*players)[1]->revealProvinces();
    (*players)[0]->destroyProvince(3);
    (*players)[0]->destroyProvince(2);
    (*players)[1]->setInitialDefense(100);
    (*players)[0]->setMoney(50);
    (*players)[1]->setMoney(50);
    equipPhase();
    list<Personality*> :: iterator itr;
    for ( itr = (*players)[0]->getArmy()->begin(); itr != (*players)[0]->getArmy()->end(); itr++ )
    {
        (*itr)->setHonor(1);
    }  

    battlePhase();
    if ( checkWinningCondition() )
    {
        cout << "Game is over. Winner: "<< (*players)[0]->getName() << endl;
    }
}

// Other non-object methods

/**
 *  Simulates the battle preparation and scenario between 2 players.
 *  @param attacker The attacking player
 *  @param defender The defending player
 */
void battle(Player* attacker, Player* defender)
{
    list<Personality*> attacker_chosen_army;                                    // The army Personalities that are chosen by the attacker
    list<Personality*> defender_chosen_army;                                    // The army Personalities that are chosen by the defender 
    list<Personality*> :: iterator itr;
    int attack_power;                                                           // The total power of the attacker's army
    int defense_power;                                                          // The total power of the defender's army
    int prov;                                                                   // The number of province that will be attacked

    cout << "Defender's provinces:" << endl;
    defender->printProvinces();
    cout << "Attacker: choose province to attack" << endl;                      // The attacking player chooses the Province to attack
    cin >> prov;
    while( prov > defender->getNumberOfProvinces() || prov < 1)                 // Valid input check
    {
        cout << "Invalid input." << endl;
        cout << "Attacker: choose province to attack:" << endl;
        cin >> prov;
    }

    cout << "Defender province: " << prov << " is under Attack" << endl;
    prov--;                                                                     // valid input: [1,number of provinces], valid index: [0, number of provinces -1]
    cout << "Attacker: choose army Personalities to use:" << endl;
    attacker_chosen_army = attacker->chooseArmy();                              // Attacker chooses army for the battle 
    cout << "Defender: choose army Personalities to use:" << endl;
    defender_chosen_army = defender->chooseArmy();                              // Defender chooses army for the battle
    cout << "----------------------------------------------------------" << endl;
    attack_power = attackPowerSum(attacker_chosen_army);                        // Calculating total Attack power
    defense_power = defensePowerSum(defender_chosen_army);                      // Calculating total Defense power
    cout << "----------------------------------------------------------" << endl;
    cout << "Attack: " << attack_power << endl;
    cout << "Defense: " << defense_power << endl;
    cout << "Province Defense: " << defender->getInitialDefense() << endl;
                                                                                // Now the battle scenario can be decided
    if ( attack_power - defense_power >= defender->getInitialDefense() )
    {                                                                           // The attacker won in points and managed to destroy the province
        cout << "Attacker wins!" << endl;
        defender->destroyProvince(prov);                                        // The province is destroyed
        cout << "Defender Province Destroyed." << endl;
        defender->loseUsedArmy(defender_chosen_army);                           // The defender loses all of his used army personalitites
        cout << "Defender used army has been lost." << endl;
    }
    else
    {
        cout << "Province could not be destroyed." << endl;
        if ( attack_power > defense_power )                                     // The attacker won in points but the province could not be destroyed
        {
            cout << "Attacker could not win the battle, but survived." << endl;
            defender->loseUsedArmy(defender_chosen_army);                       // The defender loses all of his used army personalitites
            cout << "Defender used army has been lost. Usable Green Cards return to hand." << endl;
            reduceUsedItemsDurability(attacker_chosen_army);                    // The attacker's items durability is reduced
            cout << "Attacker used items durability has been reduced by 1." << endl;
            reduceUsedPersonalitiesHonor(attacker_chosen_army);                 // The attacker's personalities honor is reduced
            cout << "Attacker used Personalities honor has been reduced by 1." << endl;
            attacker->sacrificeAttackingArmy(attack_power - defense_power, attacker_chosen_army);        // The attacker makes the needed sacrifices from his used army
            attacker->checkUsedArmyAttachments(attacker_chosen_army);           // The attacker's Personalities' attachments are checked
                                                                                // in case any of them must be discarded
            tapRemainingUsedArmy(attacker_chosen_army);                         // The rest of the attacker's used army is Tapped
        }
        else if ( attack_power == defense_power )
        {
            cout << "It's a draw!" << endl;                                     // Neither of the two players won
            defender->loseUsedArmy(defender_chosen_army);                       // Both players lose their used army Personalitites
            cout << "Defender used army has been lost. Usable Green Cards return to hand." << endl;
            attacker->loseUsedArmy(attacker_chosen_army);
            cout << "Attacker used army has been lost. Usable Green Cards return to hand." << endl;
        }        
        else
        {
            cout << "Defender wins!" << endl;                                   // Defender won the battle
            attacker->loseUsedArmy(attacker_chosen_army);                       // The attacker loses all of his used army personalitites
            cout << "Attacker used army has been lost. Usable Green Cards return to hand." << endl;
            defender->sacrificeDefendingArmy(defense_power - attack_power, defender_chosen_army);       // The defender makes the needed sacrifices from his used army
        }        
    }    
}

/**
 *  Returns the total Attack attribute of the specified army.
 */
int attackPowerSum(const list<Personality*>& army)
{
    int attack_points = 0;
    list<Personality*> :: const_iterator itr;
    for ( itr = army.begin(); itr != army.end(); itr++ )
    {
        attack_points += (*itr)->attackPower();
    }
    return attack_points;
}

/**
 *  Returns the total Defense attribute of the specified army.
 */
int defensePowerSum(const list<Personality*>& army)
{
    int defense_points = 0;
    list<Personality*> :: const_iterator itr;
    for ( itr = army.begin(); itr != army.end(); itr++ )
    {
        defense_points += (*itr)->defensePower();
    }
    return defense_points;
}

/**
 *  Prints the specified army.
 */
void printUsedArmy(const list<Personality*> & used_army)
{
    int counter = 1;
    list<Personality *>:: const_iterator p;
    cout << "Player Used Army:" << endl;
	for (p = used_army.begin(); p != used_army.end(); p++)
    {
        cout << "Personality " << counter << ". ";
        (*p)->print();
        cout << "Personality Folllowers:" << endl;
        (*p)->printFollowers();
        cout << "Personality Items:" << endl;
        (*p)->printItems();
        cout << endl;
        counter++;
    }
}

/**
 *  Reduces the items durability for every used army Personality.
 */
void reduceUsedItemsDurability(list<Personality*>& used_army)
{
    list<Personality*> :: iterator p;
    for ( p = used_army.begin(); p != used_army.end(); p++)
    {
        (*p)->reduceItemsDurability();
    }    
}

/**
 *  Reduces the honor of every used army Personality.
 */
void reduceUsedPersonalitiesHonor(list<Personality*>& used_army)
{
    list<Personality*> :: iterator p;
    for ( p = used_army.begin(); p != used_army.end(); p++)
    {
        (*p)->setHonor( (*p)->getHonor() - 1 );
    }
}

/**
 *  Used to tap all the remaining Personalities (and their attachments) of used_army.
 *  @note It is supposed to be called after checkUsedArmyAttachments, 
 *  so it handles the case some used_army nodes point to NULL.
 */
void tapRemainingUsedArmy(list<Personality*> used_army)
{
    list<Personality*> :: iterator p;
    for ( p = used_army.begin(); p != used_army.end(); p++)
    {
        if ( *p != NULL )                               // If this Personality was used and not discarded
        {
            (*p)->tapFollowers();                       // Tap it along with the attached cards
            (*p)->tap();
        }
    }
}