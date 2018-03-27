/*
 * Jimmy Le - 26546986
 * COMP 345 WINTER 2018 NORA H.
 * A1
 */

#ifndef SMALL_WORLD_SW_PIECES_H
#define SMALL_WORLD_SW_PIECES_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class game_turn_token
{
private:
    int turn_number;
    int MAX_TURNS;
public:
    game_turn_token();
    game_turn_token(int);
    ~game_turn_token();
    int get_turn_number();
    bool next_turn();
};

class coin
{
private:
    int coin_value;

public:
    coin();
    coin(int);
    ~coin();
    int get_coin();
};

class bank
{
//private:
private:
    vector<coin*> ones;
    vector<coin*> threes;
    vector<coin*> fives;
    vector<coin*> tens;
    const int BASE_SIZE = 25;

public:
    bank();
    ~bank();
    void initiate();
    coin* give_coins( int);
    void return_coin(coin*);
};

class wallet
{
private:
    vector<coin*> player_ones;
    vector<coin*> player_threes;
    vector<coin*> player_fives;
    vector<coin*> player_tens;
    bank* central;
public:
    wallet();
    ~wallet();
    void set_central(bank*);
    void first_coins();
    void init(bank*);
    void add_coin(int); //uses banks give_coin
    bool remove_coin(int);
    int get_wallet_total();
};

/*
 * Race Tokens. These are the pieces that the players move around the board. Each one depicts
one unit of the race in question on a little square chit. You know what race you (or anyone else)
is controlling by looking at the race banner sitting in front of them.
 */

class token
{
private:
    std::string name;
    bool mountain;
public:
    token();
    token(std::string, bool);
    virtual ~token();
    virtual void foo() = 0;
    std::string get_name();
    bool is_mountain();
    virtual void flip_token();
    virtual bool is_active();

};
class race_token : public token
{
private:
//    std::string name_of_race;
    bool active;
public:
    race_token();
    explicit race_token(std::string, bool, bool);
//    race_token( race_token&);
    ~race_token();
    void flip_token();
    bool is_active();
//    std::string get_name();
    void foo();
};

class terrain_token : public token
{
private:
//    std::string terrain;
public:
    terrain_token();
    explicit terrain_token(std::string, bool);
    ~terrain_token();
//    std::string getTerrain();
    void foo();
};

class bits {

private:
    vector<token*> pile;

public:
    bits();
    ~bits();
    void add_mountain_token();
    void add_race_tokens(std::string, int);
    void pop_race_tokens();
    int get_size();
    void print_pile();
    void clean();
    int number_race_tokens();
    void token_decline();
    bool get_decline();
//    bool check_if_decline();
};




/*
Cultural Identifiers. These determine the abilities of each race in the game. They're cleverly set
up as 14 race "banners" and 20 special power "badges". You link a badge with a banner and
        you have the cultural identity of a race. They work great any way you measure them. They're
attractive. The iconography on them is both consistent and easy to use, to the point where
        someone who's read the rules should be able to make out 80-90% of the powers at first glance.
Finally, they add great color to the game, as each special power lists an adjective and each race
        lists a noun, so you can have "Hill Elves", "Flying Ghouls", "Seafaring Giants", and "Heroic
Ratmen".

 */
class culture
{
    /*
     * my culture class is made of two inner classes: banners and badges
     */
private:
    typedef struct banners
    {
        std::string banner_name;
        int banner_value;
        banners();
        ~banners();
    }* bannerPtr;

    typedef struct badges
    {
        std::string badge_name;
        int badge_value;
        badges();
        ~badges();
    }* badgePtr;

    banners player_banner;
    badges player_badge;
    int culture_power;
public:
    culture();
    culture(std::string, int, std::string, int);
    culture(std::string, int);
    ~culture();
    void print_culture();
    const int get_culture_power();
    const std::string get_banner();
    const std::string get_badge();
    void give_badge(std::string, int);
};
//Hold information about valid races
const std::vector<std::string> banner_list{"Amazons","Dwarves", "Elves", "Ghouls","Giants", "Halflings",
                                           "Humans","Orcs", "Ratmen","Skeletons","Sorcerors","Tritons", "Trolls","Wizards"};
const std::vector<int> banner_power{6,3,6,5,6,6,5,5,8,6,5,6,5,5 };
const std::vector<std::string> badge_list{"Alchemist", "Berserk","Bivouacking","Commando","Diplomat",
                                          "Dragon master","Flying","Forest","Fortified","Heroic","Hill","Merhant","Mounted","Pillaging",
                                          "Seafaring","Spirit","Stout","Swamp","Underworld","Wealthy"};
const std::vector<int> badge_power{4,4,5,4,5,5,5,4,3,5,4,2,5,5,5,5,4,4,5,4 };

class culture_set
{
private:
    int DECK_SIZE; //may remove this later
    vector<culture> deck;
    vector<culture> visible;
    vector<std::string> race_list;
    vector<int>race_power;
    vector<std::string> ability_list;
    vector<int> ability_power;
public:
    culture_set();
    ~culture_set();
    void shuffle();
    void show_top(int);
    culture pick_race();
};

#endif //SMALL_WORLD_SW_PIECES_H
