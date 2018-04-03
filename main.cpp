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


//
    game_manager* game1 = new game_manager();
    game1->game_loop();
    delete game1;
//    phase_subject* subj = new phase_subject();
//    observer* watch1 = new phase_watcher(*subj);
//    subj->add(watch1);
//
//    subj->change_status("jimmy", "start", 1, 5, 23, 10,3);
//
//    observer*watch2 = new phase_watcher(*subj);
//
//    subj->change_status("Denise", "end", 2, 3, 23, 10,3);
//
//    watch2 = new domination_decorator(watch2);
//
//    watch2->show();



    cout<<endl<<"============================ END ============================";
    return 0;
}