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
#include "SW_strategy.h"
#include "SW_game_obs.h"

class player
{
private:
    std::string  player_name;

    bits* first_race_stack;
    bits* second_race_stack;
    culture* player_first_culture;
    culture* player_second_culture;
    dice* player_dice;
    loader* map;

    bank* player_central;
    wallet* player_wallet;

    aggressive_strategy aggr_strat;
    defensive_strategy def_strat;
    moderate_strategy mod_strat;
    random_strategy rand_strat;

    game_turn_token* marker;
//    undecorated_watcher* player_watcher;

//    behaviour ai = behaviour(nullptr);

    //include board bit vector
//    bits* player_tokens;
    void battle(int, tokens_info&);
    void take_over(int, int, bits*,tokens_info&);
    vector<int> show_edges(int);
    bool check_sea(int, int);
    void update_stats(int);
public:

    stats_observable* player_stats;

    behaviour ai = behaviour(nullptr);

    tokens_info* conquers(int );
    int scores(int, int);
    player();
    ~player();

    explicit player(std::string, loader*, bank*, int, game_turn_token*);
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
    double get_percent();


    tokens_info* ai_conquers(int); //always reinforcments, could change # units used
    int ai_region_conquers(int); //helper: calls get_region_adjacent_random
    int ai_owned(); //returns a random region id that the ai owns


};




#endif //SMALL_WORLD_SW_PLAYER_H
