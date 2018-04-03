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



//    game_manager* game1 = new game_manager();
//    game1->game_loop();
//    delete game1;

    stats_observable* stats = new stats_observable();
    Iobserver* undec = new undecorated_watcher(*stats);
    stats->add(undec);
//    Iobserver* undec2 = new undecorated_watcher(*stats);
//    stats->add(undec2);

    stats->change_status(5,2.5,10,12);
//    undec->show();
    undec = new dom_decorator(undec);
    cout<<"split"<<endl;
    stats->change_status(6,3.0,11,11);
    undec->update(0,3.0,0,0);
//    undec ->show();

//    undec->show();
//    undec2->show();

    cout<<endl<<"============================ END ============================";
    return 0;
}