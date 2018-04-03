/*
 * Jimmy Le - 26546986
 * COMP 345 WINTER 2018 NORA H.
 * A1
 */

#include <iostream>
#include <random>
#include "SW_dice.h"
#include "SW_graph.h"
#include "SW_map_loader.h"
#include "SW_pieces.h"
#include "SW_player.h"
#include "SW_game_start.h"
#include "SW_game_obs.h"
/*
 * Driver file that contains all test situations
 */
int main() {
    cout<<endl<<"Assignment 3 Testing"<<endl<<"============================================="<<endl;

    cout<<"Press 1 to play against ai. Press 0 to play PVP"<<endl;
    int ai = 0;
    cin>>ai;
    if(ai == 1)
    {
        game_manager* game1 = new game_manager(1);
        game1->game_loop();
    }
    else
    {
        game_manager* game1 = new game_manager();
        game1->game_loop();
    }



    cout<<endl<<"============================ END ============================";
    return 0;
}