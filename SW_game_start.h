//
// Created by Pierce on 3/10/2018.
//

#ifndef SMALL_WORLD_SW_GAME_START_H
#define SMALL_WORLD_SW_GAME_START_H

#include "SW_map_loader.h"
#include "SW_player.h"

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
    void create_players(int);
    void add_lost_tribes(int);

public:
    game_manager(); //initiate map
    ~game_manager();
    void initialize();
    void game_loop();
    int turn(player*);
    int menu(player*);
    void decline(player*);
};



#endif //SMALL_WORLD_SW_GAME_START_H
