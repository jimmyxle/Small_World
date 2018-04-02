//
// Created by Pierce on 3/10/2018.
//

#ifndef SMALL_WORLD_SW_GAME_START_H
#define SMALL_WORLD_SW_GAME_START_H

#include "SW_map_loader.h"
#include "SW_player.h"
#include "SW_game_obs.h"

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
    objective_subject* obj_sub;
    objective_watcher* obj_watch;
    double map_size;

    void create_players(int);
    void add_lost_tribes(int);
    void redistrib_tokens(player&,  tokens_info&, bool );
    void continue_loop(player&);
    void distrib_tokens(player*);
    void abandon_phase(player* p);
    void score_phase();
    void one_play(player*);
    void update_objective_observer();
public:
    game_manager(); //initiate map
    ~game_manager();
    void setup_observers();
    void initialize();
    void game_loop();
    int turn(player*);
    int menu(player&);
    void decline(player*);
    void redeploy(player*);


};



#endif //SMALL_WORLD_SW_GAME_START_H
