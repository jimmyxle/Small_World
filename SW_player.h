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
#include "SW_tokens_info.h"

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
    void battle(int, tokens_info&);
    void take_over(int, int, bits*,tokens_info&);
    vector<int> show_edges(int);
    bool check_sea(int, int);

public:
    tokens_info* ai_conquers(int);
    tokens_info* conquers(int );
    int scores(int, int);
    player();
    ~player();

    explicit player(std::string, loader*, bank*);
    const std::string get_name();
    void give_tokens();
    void redistribute_token(token *);
    void get_status();
    void set_first_culture(culture);
    int get_number_of_tokens_owned();
    void player_decline();
    bool first_culture_null();
    bool get_second_race_active(); //return true if second race == nullptr
    bool remove_tokens(int);

    tokens_info* redeploy();
    void redeploy_menu(); // make private later?
    int player_display(vector<int>&, List&);
    tokens_info* abandon_menu();

    int get_number_regions_owned();
    int get_victory_tokens();
    int ai_region_conquers(int);
    int ai_owned();


};




#endif //SMALL_WORLD_SW_PLAYER_H
