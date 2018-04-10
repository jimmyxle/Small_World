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


    cout<<"Press 1-4 to play against ai.\n"
            "[1] Player 2 will be aggressive.\n"
            "[2] Player 2 will be defensive.\n"
            "[3] Player 2 will be moderate.\n"
            "[4] Player 2 will be random.\n"
            "Enter '-1' to play PVP"<<endl;
    int ai = 0;
    do
    {
        try
        {
            cin>>ai;
            if(!cin)
            {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                ai = 0;

                throw "Not a number.";
            }
            if(ai > 4 || ai < 1)
            {
                ai = 0;
                throw "Number not in range.";
            }
        }
        catch(const char* msg)
        {
            cerr<<"ERROR: "<<msg<<endl;
            cout<<"Enter a new number."<<endl;
        }
        catch(char x)
        {
            cout<<"ERROR "<<x<<": You did not enter a number within range."<<endl;
            cout<<"Enter a new number."<<endl;
        }
    }while(ai <1 || ai > 4);


    if(ai > 0)
    {
        game_manager* game1 = new game_manager(ai);
        game1->ai_game_loop();
    }
    else
    {
        game_manager* game1 = new game_manager();
        game1->game_loop();
    }

    cout<<endl<<"============================ END ============================";
    return 0;
}