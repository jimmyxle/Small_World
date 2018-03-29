//
// Created by Pierce on 3/10/2018.
//

#include <limits>
#include "SW_game_start.h"
#include "SW_player.h"

game_manager::game_manager(){
    //make game coins
    game_bank = new bank();


    one = nullptr;
    two = nullptr;
    three = nullptr;
    four = nullptr;
    five = nullptr;
    do
    {
        cout<<"Enter the number of players(2-5): "<<endl;
        cin >>num_players;
        if(!cin)
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            num_players = 1;
        }
        if(num_players < 1 || num_players > 5)
            cout<<"Invalid number, please choose between 2 & 5."<<endl;
        else
            cout<<endl<<"Number of players is now: "<<num_players<<endl;
    }while(num_players < 1 || num_players > 5);
    switch(num_players)
    {
        case 1:
            cout<<"bad map mode chosen"<<endl;
            game_map = new loader();
            game_map->read_file("bad_test_map.map");
            game_map->populate();
            break;
        case 2:
            game_map = new loader();
            game_map->read_file("2p.map");
            game_map->populate();
            cout<<"2p mode chosen."<<endl;
            add_lost_tribes(2);
            break;
        case 3:
            game_map = new loader();
            game_map->read_file("3p.map");
            game_map->populate();
            cout<<"3p mode chosen."<<endl;
            add_lost_tribes(3);
            break;
        case 4:
            game_map = new loader();
            game_map->read_file("4p.map");
            game_map->populate();
            cout<<"4p mode chosen."<<endl;
            add_lost_tribes(4);

            break;
        case 5:
            game_map = new loader();
            game_map->read_file("5p.map");
            game_map->populate();
            cout<<"5p mode chosen."<<endl;
            add_lost_tribes(5);

            break;
        default:
            cout<<"Invalid entry."<<endl;
    }
    create_players(num_players);
    marker = new game_turn_token(num_players);
    initialize();

}

void game_manager::initialize()
{
    culture_deck = new culture_set();
    culture_deck->shuffle(); //uncomment this later
}
game_manager::~game_manager()
{
    game_map = nullptr;
    if(one != nullptr)
        delete one;
    if(two != nullptr)
        delete two;
    if(three != nullptr)
        delete three;
    if(four != nullptr)
        delete four;
    if(five != nullptr)
        delete five;

    delete marker;
    delete culture_deck;
}
void game_manager::create_players(int number)
{
    one = new player("uno", game_map, game_bank);
    two = new player("dos", game_map, game_bank);
    switch(number)
    {
        case 2:
            break;
        case 3:
            three = new player("tres", game_map, game_bank);
            break;
        case 4:
            three = new player("tres", game_map,game_bank);
            four = new player("quatro", game_map,game_bank);
            break;
        case 5:
            three = new player("tres", game_map,game_bank);
            four = new player("quatro", game_map,game_bank);
            five = new player("cinqo", game_map,game_bank);
            break;
        default:
            cout<<"Not possible"<<endl;
    }
}

void game_manager::game_loop()
{
    cout<<endl<<"Game start!"<<endl;
    while(marker->next_turn()) {
        int menu_num = 0;
        menu_num = menu(one);
        //conquer phase
        if (menu_num == 1)
        {
            bool continue_turn = true;
            while (continue_turn) {
                int empty_tokens = turn(one);
                if(one->get_number_of_tokens_owned() > 0)
                {
                    continue_turn = true;
                }
                else
                {
                    continue_turn = false;
                }
                if(empty_tokens == 1)
                    continue_turn = false;
            }
        }
        else if(menu_num == 2)
        {
            //go in decline
            decline(one);
        }
        menu_num = menu(two);
        //conquer phase
        if(menu_num == 1)
            turn(two);
        else if(menu_num == 2)
        {
            decline(two);
        }

        if(three!= nullptr)
        {
            int menu_num = menu(three);
            //conquer phase
            if(menu_num == 1)
                turn(three);
            else if(menu_num == 2)
            {
                decline(three);
            }
        }
        if(four!= nullptr)
        {
            int menu_num = menu(four);
            //conquer phase
            if(menu_num == 1)
                turn(four);
            else if(menu_num == 2)
            {
                //go in decline
                decline(four);
            }
        }

        if(five!= nullptr)
        {
            int menu_num = menu(five);
            //conquer phase
            if(menu_num == 1)
                turn(five);
            else if(menu_num == 2)
            {
                //go in decline
                decline(five);
            }
        }

        //score phase
        one->scores();
        two->scores();
        if(three!= nullptr)
            three->scores();
        if(four!= nullptr)
            four->scores();
        if(five!= nullptr)
            five->scores();
    }
}

void game_manager::add_lost_tribes(int number_of_players)
{
    List* temp_list = game_map->l1;

    switch(number_of_players)
    {
        case 2:
            temp_list->add_region_token(3,new race_token("lost_tribes", true, false));
            temp_list->add_region_token(3,new race_token("lost_tribes", true, false));
            temp_list->add_region_token(6, new race_token("lost_tribes", true, false));
            temp_list->add_region_token(6, new race_token("lost_tribes", true, false));
            temp_list->add_region_token(10, new race_token("lost_tribes", true, false));
            temp_list->add_region_token(10, new race_token("lost_tribes", true, false));
            temp_list->add_region_token(11, new race_token("lost_tribes", true, false));
            temp_list->add_region_token(11, new race_token("lost_tribes", true, false));
            temp_list->add_region_token(12,  new race_token("lost_tribes", true, false));
            temp_list->add_region_token(12,  new race_token("lost_tribes", true, false));
            temp_list->add_region_token(13,  new race_token("lost_tribes", true, false));
            temp_list->add_region_token(13,  new race_token("lost_tribes", true, false));
            temp_list->add_region_token(14, new race_token("lost_tribes", true, false));
            temp_list->add_region_token(14, new race_token("lost_tribes", true, false));
            temp_list->add_region_token(18, new race_token("lost_tribes", true, false));
            temp_list->add_region_token(18, new race_token("lost_tribes", true, false));
            temp_list->add_region_token(20, new race_token("lost_tribes", true, false) );
            temp_list->add_region_token(20, new race_token("lost_tribes", true, false) );
//            game_map->l1->print_tokens();
            cout<<"added Lost_Tribe tokess"<<endl;
            break;


        case 3:
            temp_list->add_region_token(1, new race_token("lost_tribes", true, false));
            temp_list->add_region_token(1, new race_token("lost_tribes", true, false));
            temp_list->add_region_token(6, new race_token("lost_tribes", true, false));
            temp_list->add_region_token(6, new race_token("lost_tribes", true, false));
            temp_list->add_region_token(9, new race_token("lost_tribes", true, false));
            temp_list->add_region_token(9, new race_token("lost_tribes", true, false));
            temp_list->add_region_token(11,  new race_token("lost_tribes", true, false));
            temp_list->add_region_token(11,  new race_token("lost_tribes", true, false));
            temp_list->add_region_token(13,  new race_token("lost_tribes", true, false));
            temp_list->add_region_token(13,  new race_token("lost_tribes", true, false));
            temp_list->add_region_token(19,  new race_token("lost_tribes", true, false));
            temp_list->add_region_token(19,  new race_token("lost_tribes", true, false));
            temp_list->add_region_token(21,  new race_token("lost_tribes", true, false));
            temp_list->add_region_token(21,  new race_token("lost_tribes", true, false));
            temp_list->add_region_token(22, new race_token("lost_tribes", true, false));
            temp_list->add_region_token(22, new race_token("lost_tribes", true, false));
            temp_list->add_region_token(23,  new race_token("lost_tribes", true, false));
            temp_list->add_region_token(23,  new race_token("lost_tribes", true, false));
            temp_list->add_region_token(29,  new race_token("lost_tribes", true, false));
            temp_list->add_region_token(29,  new race_token("lost_tribes", true, false));
//            game_map->l1->print_tokens();
            cout<<"added Lost_Tribe tokess"<<endl;
            break;
        case 4:
            temp_list->add_region_token(2,  new race_token("lost_tribes", true, false));
            temp_list->add_region_token(2,  new race_token("lost_tribes", true, false));
            temp_list->add_region_token(3,  new race_token("lost_tribes", true, false));
            temp_list->add_region_token(3,  new race_token("lost_tribes", true, false));
            temp_list->add_region_token(4,  new race_token("lost_tribes", true, false));
            temp_list->add_region_token(4,  new race_token("lost_tribes", true, false));
            temp_list->add_region_token(6,  new race_token("lost_tribes", true, false));
            temp_list->add_region_token(6,  new race_token("lost_tribes", true, false));
            temp_list->add_region_token(7,  new race_token("lost_tribes", true, false));
            temp_list->add_region_token(7,  new race_token("lost_tribes", true, false));
            temp_list->add_region_token(10, new race_token("lost_tribes", true, false));
            temp_list->add_region_token(10, new race_token("lost_tribes", true, false));
            temp_list->add_region_token(14, new race_token("lost_tribes", true, false));
            temp_list->add_region_token(14, new race_token("lost_tribes", true, false));
            temp_list->add_region_token(22, new race_token("lost_tribes", true, false));
            temp_list->add_region_token(22, new race_token("lost_tribes", true, false));
            temp_list->add_region_token(23, new race_token("lost_tribes", true, false));
            temp_list->add_region_token(23, new race_token("lost_tribes", true, false));
            temp_list->add_region_token(24, new race_token("lost_tribes", true, false));
            temp_list->add_region_token(24, new race_token("lost_tribes", true, false));
            temp_list->add_region_token(25, new race_token("lost_tribes", true, false));
            temp_list->add_region_token(25, new race_token("lost_tribes", true, false));
            temp_list->add_region_token(26, new race_token("lost_tribes", true, false));
            temp_list->add_region_token(26, new race_token("lost_tribes", true, false));
            temp_list->add_region_token(32, new race_token("lost_tribes", true, false));
            temp_list->add_region_token(32, new race_token("lost_tribes", true, false));
            temp_list->add_region_token(33, new race_token("lost_tribes", true, false));
            temp_list->add_region_token(33, new race_token("lost_tribes", true, false));
//            game_map->l1->print_tokens();
            cout<<"added Lost_Tribe tokess"<<endl;
            break;
        case 5:
            temp_list->add_region_token(5,  new race_token("lost_tribes", true, false));
            temp_list->add_region_token(5,  new race_token("lost_tribes", true, false));
            temp_list->add_region_token(8, new race_token("lost_tribes", true, false));
            temp_list->add_region_token(8, new race_token("lost_tribes", true, false));
            temp_list->add_region_token(12,  new race_token("lost_tribes", true, false));
            temp_list->add_region_token(12,  new race_token("lost_tribes", true, false));
            temp_list->add_region_token(14,  new race_token("lost_tribes", true, false));
            temp_list->add_region_token(14,  new race_token("lost_tribes", true, false));
            temp_list->add_region_token(15,  new race_token("lost_tribes", true, false));
            temp_list->add_region_token(15,  new race_token("lost_tribes", true, false));
            temp_list->add_region_token(19,  new race_token("lost_tribes", true, false));
            temp_list->add_region_token(19,  new race_token("lost_tribes", true, false));
            temp_list->add_region_token(21,  new race_token("lost_tribes", true, false));
            temp_list->add_region_token(21,  new race_token("lost_tribes", true, false));
            temp_list->add_region_token(23,  new race_token("lost_tribes", true, false));
            temp_list->add_region_token(23,  new race_token("lost_tribes", true, false));
            temp_list->add_region_token(25, new race_token("lost_tribes", true, false));
            temp_list->add_region_token(25, new race_token("lost_tribes", true, false));
            temp_list->add_region_token(27,  new race_token("lost_tribes", true, false));
            temp_list->add_region_token(27,  new race_token("lost_tribes", true, false));
            temp_list->add_region_token(29,  new race_token("lost_tribes", true, false));
            temp_list->add_region_token(29,  new race_token("lost_tribes", true, false));
            temp_list->add_region_token(32, new race_token("lost_tribes", true, false));
            temp_list->add_region_token(32, new race_token("lost_tribes", true, false));
            temp_list->add_region_token(35, new race_token("lost_tribes", true, false));
            temp_list->add_region_token(35, new race_token("lost_tribes", true, false));
            temp_list->add_region_token(36, new race_token("lost_tribes", true, false));
            temp_list->add_region_token(36, new race_token("lost_tribes", true, false));
            temp_list->add_region_token(38, new race_token("lost_tribes", true, false));
            temp_list->add_region_token(38, new race_token("lost_tribes", true, false));
            temp_list->add_region_token(43,  new race_token("lost_tribes", true, false));
            temp_list->add_region_token(43,  new race_token("lost_tribes", true, false));
            temp_list->add_region_token(44,  new race_token("lost_tribes", true, false));
            temp_list->add_region_token(44,  new race_token("lost_tribes", true, false));
//            game_map->l1->print_tokens();
            cout<<"added Lost_Tribe tokess"<<endl;
            break;

        default:
            cout<<"MAP DISABLED."<<endl;
            break;
    }
}
int game_manager::turn(player* p)
{
    cout.flush();
    cout<<"player "<<p->get_name()<<"'s turn"<<endl;
    tokens_info *return_token = ( p->conquers() );
    if(return_token->exists)
    {
        if(return_token->prev_owner == one->get_name())
        {
            cout<<"player"<<one->get_name()<<" current token total : "
                <<one->get_number_of_tokens_owned()<<endl;
            vector<token*> *temp = &return_token->returned_tokens;
            int SIZE = temp->size();

            if(temp->size() > 0)
                SIZE--;

            for(int i = 0; i < SIZE; i++)
            {
                token* token1 = temp->back();
                one->redistribute_token(token1);
                temp->pop_back();
            }
            cout<<"player "<<one->get_name()<<" new token total : "<<one->get_number_of_tokens_owned()<<endl;
        }
        else if(return_token->prev_owner == two->get_name())
        {
            cout<<"player"<<two->get_name()<<" current token total : "
                <<two->get_number_of_tokens_owned()<<endl;
            vector<token*> *temp = &return_token->returned_tokens;
            int SIZE = temp->size();

            if(temp->size() > 0)
                SIZE--;

            for(int i = 0; i < SIZE; i++)
            {
                token* token1 = temp->back();
                two->redistribute_token(token1);
                temp->pop_back();
            }
            cout<<"player "<<two->get_name()<<" new token total : "
                <<two->get_number_of_tokens_owned()<<endl;
        }
        else if(three!= nullptr && return_token->prev_owner == three->get_name())
        {
            //conditional to check for first race or second race in decline
            if(three->get_second_race_active())
            {
                cout<<"player tokens: "<<three->get_number_of_tokens_owned()<<endl;
                cout<<"tokens added: "<<return_token->number_of_tokens<<endl;
//                three->redistribute_tokens(1, return_token.number_of_tokens);
                cout<<"PLAYER REDISTRIBUTE DISABLED"<<endl;
            }
            else
            {
                cout<<"player tokens: "<<three->get_number_of_tokens_owned()<<endl;
                cout<<"tokens added: "<<return_token->number_of_tokens<<endl;
//                three->redistribute_tokens(2, return_token.number_of_tokens);
                cout<<"PLAYER REDISTRIBUTE DISABLED"<<endl;

            }
        }
        else if(four != nullptr && return_token->prev_owner == four->get_name())
        {
            //conditional to check for first race or second race in decline
            if(four->get_second_race_active())
            {
                cout<<"player tokens: "<<four->get_number_of_tokens_owned()<<endl;
                cout<<"tokens added: "<<return_token->number_of_tokens<<endl;
//                four->redistribute_tokens(1, return_token.number_of_tokens);
                cout<<"PLAYER REDISTRIBUTE DISABLED"<<endl;

            }
            else
            {
                cout<<"player tokens: "<<four->get_number_of_tokens_owned()<<endl;
                cout<<"tokens added: "<<return_token->number_of_tokens<<endl;
//                four->redistribute_tokens(2, return_token.number_of_tokens);
                cout<<"PLAYER REDISTRIBUTE DISABLED"<<endl;

            }

        }
        else if(five != nullptr && return_token->prev_owner == five->get_name())
        {
            //conditional to check for first race or second race in decline
            if( five->get_second_race_active() )
            {
                cout<<"player tokens: "<<five->get_number_of_tokens_owned()<<endl;
                cout<<"tokens added: "<<return_token->number_of_tokens<<endl;
//                five->redistribute_tokens(1, return_token.number_of_tokens);
                cout<<"PLAYER REDISTRIBUTE DISABLED"<<endl;

            }
            else
            {
                cout<<"player tokens: "<<five->get_number_of_tokens_owned()<<endl;
                cout<<"tokens added: "<<return_token->number_of_tokens<<endl;
//                five->redistribute_tokens(2, return_token.number_of_tokens);
                cout<<"PLAYER REDISTRIBUTE DISABLED"<<endl;
            }
        }
        else
        {
            cout<<"something wrong has happened."<<endl;
        }
    }
    if(return_token->turn_finish == true)
    {
        delete return_token;
        return 1;
    }
    else
    {
        delete return_token;
        return 0;
    }
}
int game_manager::menu(player* p)
{
    if(p->first_culture_null())
    {
        p->set_first_culture(culture_deck->pick_race());
        p->give_tokens();
    }
    cout<<p->get_name()<<"'s turn. Will you conquer(1) or go in decline(2)?"<<endl;
    int p_choice = 0;
    do
    {
        cin>>p_choice;
        if(!cin || p_choice <1 || p_choice >2)
        {
            cout<<"Did not choose 1 or 2, pick again."<<endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            p_choice = 0;
        }
    }while(p_choice <1 || p_choice > 2);
    return p_choice;
}

void game_manager::decline(player* p)
{
    cout<<p->get_name()<<" chose to go in decline."<<endl;
    game_map->l1->regions_in_decline(p->get_name());
    p->player_decline();

}