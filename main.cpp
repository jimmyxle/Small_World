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
/*
 * Driver file that contains all test situations
 */
int main() {

    cout<<endl<<"Assignment 2 Testing"<<endl<<"============================================="<<endl;

    /*
    game_manager* game1 = new game_manager();
    game1->game_loop();
    delete game1;
*/
    bank * b1 = new bank();
    wallet * w1 = new wallet();


    w1->init(b1);
//    w1->set_central(b1);
//    w1->first_coins();
    cout<<"The value of the wallet is: "<<w1->get_wallet_total()<<endl;

    w1->add_coin(1);
    w1->add_coin(3);
    w1->add_coin(10);

//    w1->add_coin(1);
//    w1->add_coin(1)

    cout<<"The value of the wallet is: "<<w1->get_wallet_total()<<endl;
    w1->remove_coin(3);
    w1->remove_coin(10);

    cout<<"The value of the wallet is: "<<w1->get_wallet_total()<<endl;


    cout<<endl<<"============================ END ============================";
    return 0;
}