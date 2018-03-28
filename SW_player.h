/*
 * Jimmy Le - 26546986
 * COMP 345 WINTER 2018 NORA H.
 * A1
 */

#ifndef SMALL_WORLD_SW_PLAYER_H
#define SMALL_WORLD_SW_PLAYER_H

#include <string>
#include "SW_pieces.h"
#include "SW_dice.h"
#include "SW_map_loader.h"

struct tokens_info
{
    int number_of_tokens;
    string prev_owner;
    bool exists;
//    bool second;
};
class player
{
private:
    std::string  player_name;

    bits* first_race_stack;
    bits* second_race_stack;
    culture* player_first_culture;
    culture* player_second_culture;
//    bool first_decline;
    dice* player_dice;
    loader* map;

    bank* player_central;
    wallet* player_wallet;

    //include board bit vector
//    bits* player_tokens;

public:
    void add_map(loader*);
    void picks_race();
    tokens_info conquers();
    void scores();
    player();
    ~player();

    explicit player(std::string, loader*, bank*);
    const std::string get_name();
    void give_tokens();
    void redistribute_tokens(int, int);
    void get_status();
    void set_first_culture(culture);
//    void set_second_culture(culture);
    int get_number_of_tokens_owned(int);
//    void set_decline();
//    bool get_decline();
    void player_decline();
    bool first_culture_null();
    bool get_second_race_active(); //return true if second race == nullptr
    bool remove_tokens(int);
};




#endif //SMALL_WORLD_SW_PLAYER_H
