//
// Created by Pierce on 3/10/2018.
//

#ifndef SMALL_WORLD_SW_GAME_START_H
#define SMALL_WORLD_SW_GAME_START_H

#include "SW_map_loader.h"
#include "SW_player.h"
#include "SW_game_obs.h"
#include "SW_strategy.h"

class game_manager
{
private:
    int num_players;
    loader* game_map;
    bank* game_bank;
    player* one;
    player* two;
    player* three;
    player* four;
    player* five;
    game_turn_token* marker;
    culture_set* culture_deck;
    phase_subject* subject;
    phase_watcher* phase;
    int map_size;
    stats_observable* game_stats;
    undecorated_watcher* watcher;
    aggressive_strategy aggr_strat;
    defensive_strategy def_strat;
    moderate_strategy mod_strat;
    random_strategy rand_strat;
    behaviour* ai;

    void create_players(int);
    void add_lost_tribes(int);
    void redistrib_tokens(player&,  tokens_info&, bool );

    void ai_continue_loop(player&);
    void continue_loop(player&);

    void distrib_tokens(player*);
    void abandon_phase(player& );
    void score_phase(player* );
    void one_play(player*);
    void ai_one_play(player*);

    int deco_menu(int);
    void update_stats(int);
    void decorate( int);
    double get_percent(player*);

public:
    game_manager(); //initiate map
    game_manager(int); //initiate map

    ~game_manager();
    void setup_observers();
    void initialize();

    void game_loop();

    int ai_turn(player*);
    int turn(player*);

    int ai_menu(player&);
    int menu(player&);
    void decline(player*);
    void redeploy(player*);


};



#endif //SMALL_WORLD_SW_GAME_START_H
