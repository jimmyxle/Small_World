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


class player
{
private:
    std::string  player_name;

    bits* first_race_stack;
    bits* second_race_stack;
    culture* player_first_culture;
    culture* player_second_culture;
    wallet* player_wallet;
    dice* player_dice;
    loader* map;
    //include board bit vector
//    bits* player_tokens;
public:
    void add_map(loader*);
    void picks_race();
    void conquers();
    void scores();
    player();
    ~player();

    explicit player(std::string, loader*);
    const std::string get_name();
    void give_tokens(int);
    void get_status();

};




#endif //SMALL_WORLD_SW_PLAYER_H
