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


    game_manager* game1 = new game_manager();
    game1->game_loop();
    delete game1;


/*
 *     int total = 29;
    int modulo = 10;
//    cout<<total/modulo<<endl;
//    if( total / modulo  >  0)
//    {
//        int times = total/modulo;
////        cout<<times<<endl;
//        cout<<total<<" - "<<times<<"*"<<modulo<<endl;
//        total = total - modulo;
//        cout<< total;
//    }
    while( total / 10 > 0)
    {
//        cout<<total<<"\t"<<endl;
        total = total - 10;
//        cout<<total;
        cout<<"kampai"<<endl;
        //update game when player gets a 10 coin token
    }while( total / 5 > 0)
    {
        cout<<total<<"\t"<<endl;

        total = total -5;
        cout<<total;

        cout<<"YO"<<endl;
        //update game when player gets a 10 coin token
    }while( total / 3 > 0)
    {
        cout<<total<<"\t"<<endl;

        total = total - 3;
        cout<<total;

        cout<<"drink!"<<endl;
        //update game when player gets a 10 coin token
    }while( total / 1 > 0)
    {
        cout<<total<<"\t"<<endl;

        total = total -1;
        cout<<total;

        cout<<"blargh"<<endl;
        //update game when player gets a 10 coin token
    }
    cout<<total;

////
 */
        stats_observable *stats = new stats_observable();

        Iobserver *undec = new undecorated_watcher(*stats);
        undec = new dom_decorator(undec);
        undec = new coin_decorator(undec);
        undec = new hand_decorator(undec);
        stats->add(undec);

        stats->change_status(5, 45,55,2,6,0);

        undec->show();

    /*
        stats->remove(undec);
        undec = new coin_decorator(new undecorated_watcher());
        stats->add(undec);

        stats->change_status(7, 5.0, 11, 20);

        undec->show();
        stats->remove(undec);

        undec = new undecorated_watcher();
        stats->add(undec);

        stats->change_status(10, 5.0, 11, 20);

        undec->show();

        delete undec;


    stats_observable* stats = new stats_observable();

    Iobserver* undec = new undecorated_watcher(*stats);
    undec = new dom_decorator(undec);
    stats->add(undec);

    Iobserver* undec2 = new undecorated_watcher(*stats);
    undec2 = new coin_decorator(undec2);
    stats->add(undec2);

    Iobserver* undec3 = new undecorated_watcher(*stats);
    undec3  = new dom_decorator(undec3);
    undec3 = new coin_decorator(undec3);
    stats->add(undec3);

    stats->change_status(6,3.0,11,10);

    undec->show();
    cout<<"----"<<endl;
    undec2->show();
    cout<<"----"<<endl;
    undec3->show();
    cout<<"=====split"<<endl;

    stats->change_status(7,20,11,15);

    undec->show();
    cout<<"----"<<endl;
    undec2->show();
    cout<<"----"<<endl;
    undec3->show();
    */

    cout<<endl<<"============================ END ============================";
    return 0;
}