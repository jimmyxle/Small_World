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

    cout<<"\n"
            "  _________              .__  .__     __      __            .__      .___\n"
            " /   _____/ _____ _____  |  | |  |   /  \\    /  \\___________|  |   __| _/\n"
            " \\_____  \\ /     \\\\__  \\ |  | |  |   \\   \\/\\/   /  _ \\_  __ \\  |  / __ | \n"
            " /        \\  Y Y  \\/ __ \\|  |_|  |__  \\        (  <_> )  | \\/  |_/ /_/ | \n"
            "/_______  /__|_|  (____  /____/____/   \\__/\\  / \\____/|__|  |____|____ | \n"
            "        \\/      \\/     \\/                   \\/                        \\/ "<<endl;

    cout<<"Too many people, not enough space."<<endl;
    cout<<"By JIMMY LE - 26546986"<<endl<<endl;cout<<"If you'd like to play with an AI, enter '1'. Enter anything else otherwise."<<endl;
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

    if(ai == 1)
    {
        game_manager* game1 = new game_manager(ai);
        game1->ai_game_loop();
    }
    else
    {
        game_manager* game1 = new game_manager(ai);
        game1->game_loop();
    }

    cout<<endl<<"============================ END ============================";
    return 0;
}