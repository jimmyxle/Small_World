//
// Created by Pierce on 3/10/2018.
//

#include <limits>
#include "SW_game_start.h"

game_manager::game_manager(int dummy_var)
{
    game_bank = new bank();

    one = nullptr;
    two = nullptr;
    three = nullptr;
    four = nullptr;
    five = nullptr;

    do
    {
        cout<<"Enter the number of players(2-5): "<<endl;
        try{
            cin >>num_players;
            if(!cin)
            {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                num_players = 0;
                throw "Not a number";
            }
            if(num_players < 1 || num_players > 5)
                throw "Number not in range.";
            else
                cout<<endl<<"Number of players is now: "<<num_players<<endl;
        }catch(const char* msg)
        {
            cerr<<"ERROR: "<<msg<<endl;
        }
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
    marker = new game_turn_token(num_players);
    game_map->l1->declare_all_edges(num_players);
    ai_create_players(num_players, dummy_var);
    map_size = game_map->l1->get_total_number_regions();
    setup_observers();
    initialize(); //culture decks

}
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
        try
        {
            cin >>num_players;

            if(!cin)
            {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                num_players = 0;
                throw "Not a number";
            }
            if(num_players < 1 || num_players > 5)
                throw "Number not in range.";
            else
                cout<<endl<<"Number of players is now: "<<num_players<<endl;
        }catch(const char* msg)
        {
            cerr<<"ERROR: "<<msg<<endl;
        }


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
    marker = new game_turn_token(num_players);

    game_map->l1->declare_all_edges(num_players);
    create_players(num_players);
    map_size = game_map->l1->get_total_number_regions();
    setup_observers();
    initialize(); //culture decks

}
void game_manager::setup_observers()
{
    subject = new phase_subject();
    phase = new phase_watcher(*subject);
    subject->add(phase);

//    game_stats = new stats_observable();
    watcher = new undecorated_watcher();
    one->player_stats->add(watcher);
    two->player_stats->add(watcher);
    if(three != nullptr)
        three->player_stats->add(watcher);
    if(four != nullptr)
        four->player_stats->add(watcher);
    if(five!=nullptr)
        five->player_stats->add(watcher);
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

    delete subject;
    delete phase;
//    delete game_stats;
//    delete watcher;
}
void game_manager::ai_create_players(int num_players, int setting)
{
    one = new player("uno", game_map, game_bank, 0, marker);
    two = new player("dos", game_map, game_bank, setting,marker );
    switch(num_players)
    {
        case 2:
            break;
        case 3:
            three = new player("tres", game_map, game_bank,2,marker); //defensive

            break;
        case 4:
            three = new player("tres", game_map,game_bank, 2,marker);
            four = new player("quatro", game_map,game_bank,1,marker); //aggressive
            break;
        case 5:
            three = new player("tres", game_map,game_bank,2,marker);
            four = new player("quatro", game_map,game_bank,1,marker);
            five = new player("cinqo", game_map,game_bank,4,marker); //random
            break;
        default:
            cout<<"Not possible"<<endl;
            break;


    }
}
void game_manager::create_players(int number)
{
    one = new player("uno", game_map, game_bank, 0,marker);
    two = new player("dos", game_map, game_bank,0 ,marker);
    switch(number)
    {
        case 2:
            break;
        case 3:
            three = new player("tres", game_map, game_bank,0,marker);
            break;
        case 4:
            three = new player("tres", game_map,game_bank, 0,marker);
            four = new player("quatro", game_map,game_bank,0,marker);
            break;
        case 5:
            three = new player("tres", game_map,game_bank,0,marker);
            four = new player("quatro", game_map,game_bank,0,marker);
            five = new player("cinqo", game_map,game_bank,0,marker);
            break;
        default:
            cout<<"Not possible"<<endl;
    }
}
void game_manager::ai_continue_loop(player &p)
{
    bool continue_turn = true;
    while (continue_turn)
    {
        subject->change_status(p.get_name(), "Conquer", p.get_number_regions_owned(), map_size);
//        update_stats();

        int empty_tokens = ai_turn( &p );
        if ( (&p) ->get_number_of_tokens_owned() > 0)
        {
            continue_turn = true;
        }
        else
            continue_turn = false;
        if (empty_tokens == 1)
            continue_turn = false;
    }
}
void game_manager::continue_loop(player& p)
{
    bool continue_turn = true;
    while (continue_turn)
    {
        subject->change_status(p.get_name(), "Conquer", p.get_number_regions_owned(), map_size);
//        update_stats();

        int empty_tokens = turn( &p );
        if ( (&p) ->get_number_of_tokens_owned() > 0)
        {
            continue_turn = true;
        }
        else
            continue_turn = false;
        if (empty_tokens == 1)
            continue_turn = false;
    }
}
void game_manager::ai_one_play(player * p)
{
    int menu_num = 0;
    menu_num = ai_menu(*p);
    //conquer phase
    if (menu_num == 1) {
        redeploy(p);
        ai_continue_loop(*p);
        subject->change_status((p)->get_name(), "Redeploy", p->get_number_regions_owned(), map_size );
        update_stats();


        cout<<endl<<"Redeploy troops? Enter '1' to redeploy. Enter '0' to skip ahead."<<endl;
        cout<<"ai never redeploys"<<endl;
    } else if (menu_num == 2) {
        //go in decline
        subject->change_status((p)->get_name(), "Decline", p->get_number_regions_owned(), map_size);
        decline(p);
    }
}
void game_manager::one_play(player * p)
{
    int menu_num = 0;
    menu_num = menu(*p);
    //conquer phase
    if (menu_num == 1) {
        redeploy(p);
        continue_loop(*p);
        subject->change_status((p)->get_name(), "Redeploy", p->get_number_regions_owned(), map_size );
        update_stats();


        cout<<endl<<"Redeploy troops? Enter '1' to redeploy. Enter '0' to skip ahead."<<endl;
        int redeploy_result = 0;


        try
        {
            cin>>redeploy_result;
            if(!cin)
            {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                redeploy_result = 0;
                throw "Not a number";
            }
        }catch(const char* msg)
        {
            cerr<<"ERROR: "<<msg<<endl;
        }


        if(redeploy_result == 1)
        {
            redeploy(p);
            distrib_tokens(p);
        }

    } else if (menu_num == 2) {
        //go in decline
        subject->change_status((p)->get_name(), "Decline", p->get_number_regions_owned(), map_size);
        decline(p);
    }
}
int game_manager::deco_menu(int choice)
{
    int decorator_choice = 0;


    bool deco_loop = true;
    do
    {
        if(choice > 0)
            decorator_choice = choice;
        else
        {
            cout<<"Would you like to add a new decorator?"<<endl;
            cout<<"Enter the index of the item. Enter a \'-1\' when you wish to continue"<<endl;
            cout<<"(2) Domination Decorator"<<endl<<"(3) Hand Decorator"<<endl
                <<"(4) Victory Coin Decorator" <<endl;
            try
            {
                cin>>decorator_choice;
                if(!cin)
                {
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    decorator_choice = -1;
                    throw "Not a number";
                }
            }catch(const char* msg)
            {
                cerr<<"ERROR: "<<msg<<endl;
            }



        }

        if(decorator_choice < 0)
        {
            cout<<"Won't bother you again"<<endl;
//            decorator_choice = -1;
            deco_loop = false;
        }
        else
        {
            if(decorator_choice > 1 && decorator_choice < 5)
            {
                deco_loop = false;
            }
            else
            {
//                cout<<"Enter "<<endl;
                decorator_choice = 0;
                choice = 0;
            }
        }




    }while(deco_loop);


    if(decorator_choice > 0)
    {
        cout<<"You chose "<<decorator_choice<<endl;

        decorate(decorator_choice);

        cout<<endl<<"Add another?\nEnter 2,3,4 to add another decorator.\n"
                "Enter -1 to skip ahead."<<endl;

        try
        {
            cin>>decorator_choice;
            if(!cin)
            {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                decorator_choice = -1;
                throw "Not a number";
            }
        }catch(const char* msg)
        {
            cerr<<"ERROR: "<<msg<<endl;
        }

        if(decorator_choice > 0)
            deco_menu(decorator_choice);

    }


    return decorator_choice;
}
void game_manager::update_stats()
{

    one->player_stats->change_status(one->get_name(),marker->get_turn_number(), one->get_percent(),
    one->get_number_of_tokens_owned(),0);
    watcher->show();

    two->player_stats->change_status(two->get_name(),marker->get_turn_number(), two->get_percent(),
    two->get_number_of_tokens_owned(),0);
    watcher->show();


    if(three != nullptr)
    {
        three->player_stats->change_status(three->get_name(),marker->get_turn_number(),
                                           three->get_percent(),
                                           three->get_number_of_tokens_owned(),0);
        watcher->show();

    }
    if(four!= nullptr)
    {
        four->player_stats->change_status(four->get_name(),marker->get_turn_number(),
                                          four->get_percent(),
                                         four->get_number_of_tokens_owned(),0);
        watcher->show();

    }
    if(five != nullptr)
    {
        five->player_stats->change_status(five->get_name(),marker->get_turn_number(),
                                          five->get_percent(),
                                         five->get_number_of_tokens_owned(),0);
        watcher->show();

    }
}

void game_manager::ai_game_loop()
{
    cout<<endl<<"Game start!"<<endl;
    int deco_choice = 1;
    while(marker->next_turn()) {
        update_stats();

        cout<<endl<<endl;
        if(deco_choice > 0)
        {
            deco_choice = deco_menu(deco_choice);
            deco_choice = -1;
        }


        game_loop_helper(one);
        ai_game_loop_helper(two);

        if(three != nullptr)
            ai_game_loop_helper(three);
        if(four != nullptr)
            ai_game_loop_helper(four);
        if(five != nullptr)
            ai_game_loop_helper(five);

    }
    declare_winner();
}
void game_manager::game_loop_helper(player* p)
{
    one_play(p);
    score_phase(p);
}
void game_manager::ai_game_loop_helper(player *p)
{
    ai_one_play(p);
    score_phase(p);
}
void game_manager::game_loop()
{
    cout<<endl<<"Game start!"<<endl;
    int deco_choice = 1;
    while(marker->next_turn()) {
        update_stats();

        cout<<endl<<endl;
        if(deco_choice > 0)
        {
            deco_choice = deco_menu(deco_choice);
            deco_choice = -1;
        }


        game_loop_helper(one);
        game_loop_helper(two);

        if(three != nullptr)
            game_loop_helper(three);
        if(four != nullptr)
            game_loop_helper(four);
        if(five != nullptr)
            game_loop_helper(five);

    }
    declare_winner();
}

void game_manager::score_phase(player * p)
{
    subject->change_status((p)->get_name(), "Score", p->get_number_regions_owned(), map_size );

    int total = game_map->l1->num_regions_controlled(p->get_name());
    int total_display = total;

    while(total > 0) // ie: 28
    {
        while( total / 10 > 0)
        {
            int temp = p->scores(total, 10); //return 18
            total = temp;
//            update_stats(10);
            //update game when player gets a 10 coin token
        }while( total / 5 > 0)
        {
            int temp = p->scores(total, 5); //return 18
            total = temp;
//            update_stats(5);
        }while( total / 3 > 0)
        {
            int temp = p->scores(total, 3); //return 18
            total = temp;
//            update_stats(3);
        }while( total / 1 > 0)
        {
            int temp = p->scores(total, 1); //return 18
            total = temp;
//            update_stats(1);
        }
    }


    cout<<"------------------------"<<endl;
    cout<<"Player "<<p->get_name()<<endl;
    cout<<"------------------------"<<endl;

    cout<<"\tNumber of regions controlled: "<<total_display<<" region(s)!"<<endl;
    cout<<"\tNumber of Victory Coins: "<<p->get_victory_tokens()<<endl<<endl;

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

void game_manager::redistrib_tokens(player& p, tokens_info & return_token, bool withdraw)
{

    vector<token *> *temp = &(&return_token)->returned_tokens;
    int SIZE = temp->size();

    if(!withdraw)
    {
        if (temp->size() > 0)
            SIZE--;
    }

    for (int i = 0; i < SIZE; i++) {
        token *token1 = temp->back();
        (&p)->redistribute_token(token1);
        temp->pop_back();
    }


    cout << "player " << (&p)->get_name() << " new token total : " << (&p)->get_number_of_tokens_owned()
         << endl;
    update_stats();

}
int game_manager::ai_turn(player *p)
{

    tokens_info *return_token = ( p->ai_conquers( num_players) );
    if(return_token->exists)
    {
        if(return_token->prev_owner == one->get_name())
        {
            redistrib_tokens(*(one), *return_token, false);
        }
        else if(return_token->prev_owner == two->get_name())
        {
            redistrib_tokens(*(two), *return_token, false);
        }
        else if(three!= nullptr && return_token->prev_owner == three->get_name())
        {
            redistrib_tokens(*three, *return_token, false);
        }
        else if(four != nullptr && return_token->prev_owner == four->get_name())
        {
            redistrib_tokens(*four, *return_token, false);

        }
        else if(five != nullptr && return_token->prev_owner == five->get_name())
        {
            redistrib_tokens(*five, *return_token, false);
        }
        else if(return_token->prev_owner == "default")
        {
            cout<<"Lost tribes slain"<<endl;
        }
        else
        {
            cout<<"Redistribute token has no owner."<<endl;
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
int game_manager::turn(player* p)
{
    tokens_info *return_token = ( p->conquers( num_players) );
    if(return_token->exists)
    {
        if(return_token->prev_owner == one->get_name())
        {
            redistrib_tokens(*(one), *return_token, false);
        }
        else if(return_token->prev_owner == two->get_name())
        {
           redistrib_tokens(*(two), *return_token, false);
        }
        else if(three!= nullptr && return_token->prev_owner == three->get_name())
        {
            redistrib_tokens(*three, *return_token, false);
        }
        else if(four != nullptr && return_token->prev_owner == four->get_name())
        {
           redistrib_tokens(*four, *return_token, false);

        }
        else if(five != nullptr && return_token->prev_owner == five->get_name())
        {
            redistrib_tokens(*five, *return_token, false);
        }
        else if(return_token->prev_owner == "default")
        {
            cout<<"Lost tribes slain"<<endl;
        }
        else
        {
            cout<<"Redistribute token has no owner."<<endl;
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

int game_manager::ai_menu(player &p)
{
    if((&p)->first_culture_null())
    {
        subject->change_status((&p)->get_name(), "Pick", (&p)->get_number_regions_owned(), map_size );
        int ai_pick = (&p)->ai.execute(1,3);
        (&p)->set_first_culture(culture_deck->ai_pick_race( ));
        (&p)->give_tokens();
        update_stats();
    }
    else
    {
        List* list_ptr = game_map->l1;
        vector<int> regions_list = list_ptr -> get_region_array((&p)->get_name());
        subject->change_status((&p)->get_name(), "Abandon", (&p)->get_number_regions_owned(), map_size);
        update_stats();

        (&p)->player_display(regions_list, *list_ptr);

        cout<<"Ai won't abandon any regions"<<endl;

    }


    cout<<endl;
    int ai_choice = 0;
    if((&p)->get_second_race_active())
    {
        subject->change_status((&p)->get_name(), "Conquer", (&p)->get_number_regions_owned(), map_size);
//        update_stats();
        cout<<"Will you conquer(1) or go in decline(2)?"<<endl;
        cout<<"ai will conquer"<<endl;
        ai_choice =1;
    }
    else
    {
        cout<<"You have 2 races, so can only conquer, abandon regions or redeploy!"<<endl;
        ai_choice = 1;
    }

    return ai_choice;
}
int game_manager::menu(player& p)
{
    if((&p)->first_culture_null())
    {
        subject->change_status((&p)->get_name(), "Pick", (&p)->get_number_regions_owned(), map_size );
        (&p)->set_first_culture(culture_deck->pick_race());
        (&p)->give_tokens();

        update_stats();
    }
    else
    {
        List* list_ptr = game_map->l1;
        vector<int> regions_list = list_ptr -> get_region_array((&p)->get_name());
        subject->change_status((&p)->get_name(), "Abandon", (&p)->get_number_regions_owned(), map_size);
        update_stats();

        (&p)->player_display(regions_list, *list_ptr);

        cout<<"Enter [1] if you want to abandon any regions"<<endl;

        int choice = 0;
        try
        {
            cin>>choice;
            if(!cin)
            {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                choice = -1;
                throw "Not a number";
            }
        }catch(const char* msg)
        {
            cerr<<"ERROR: "<<msg<<endl;
        }

        if(choice == 1)
        {
            abandon_phase(p);
        }
    }


    cout<<endl;
    int p_choice = 0;

    if((&p)->get_second_race_active())
    {
        subject->change_status((&p)->get_name(), "Conquer", (&p)->get_number_regions_owned(), map_size);
//        update_stats();
        cout<<"Will you conquer(1) or go in decline(2)?"<<endl;
        do
        {

            try
            {
                cin>>p_choice;
                if(!cin)
                {
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    p_choice = -1;
                    throw "Not a number";
                }
            }catch(const char* msg)
            {
                cerr<<"ERROR: "<<msg<<endl;
            }

            if( p_choice <1 || p_choice >2)
            {
                cout<<"Did not choose 1 or 2, pick again."<<endl;
                p_choice = 0;
            }
        }while(p_choice <1 || p_choice > 2);
    }
    else
    {
        cout<<"You have 2 races, so can only conquer, abandon regions or redeploy!"<<endl;
        p_choice = 1;
    }

    return p_choice;
}

void game_manager::decline(player* p)
{
    cout<<p->get_name()<<" chose to go in decline."<<endl;
    game_map->l1->regions_in_decline(p->get_name());
    p->player_decline();

}

void game_manager::redeploy(player * p)
{
    cout<<"Redeploy initiated"<<endl;
    tokens_info* return_token = p->redeploy();
    if(return_token->exists)
    {
        if(return_token->prev_owner == one->get_name())
        {
            redistrib_tokens(*(one), *return_token, true);
        }
        else if(return_token->prev_owner == two->get_name())
        {
            redistrib_tokens(*(two), *return_token, true);
        }
        else if(three!= nullptr && return_token->prev_owner == three->get_name())
        {
            redistrib_tokens(*three, *return_token, true);
        }
        else if(four != nullptr && return_token->prev_owner == four->get_name())
        {
            redistrib_tokens(*four, *return_token, true);

        }
        else if(five != nullptr && return_token->prev_owner == five->get_name())
        {
            redistrib_tokens(*five, *return_token, true);
        }
        else
        {
            cout<<"something wrong has happened."<<endl;
        }
    }
    if(return_token->turn_finish == true)
        delete return_token;
    else
        delete return_token;

}
void game_manager::distrib_tokens(player* p)
{
    p->redeploy_menu();
}

void game_manager::abandon_phase(player& p)
{
    subject->change_status((&p)->get_name(), "Abandon",(&p)->get_number_regions_owned(), map_size);
    update_stats();

    tokens_info* return_token = (&p)->abandon_menu();
    if(return_token->exists)
    {
        if(return_token->prev_owner == one->get_name())
        {
            redistrib_tokens(*(one), *return_token, true);
        }
        else if(return_token->prev_owner == two->get_name())
        {
            redistrib_tokens(*(two), *return_token, true);
        }
        else if(three!= nullptr && return_token->prev_owner == three->get_name())
        {
            redistrib_tokens(*three, *return_token, true);
        }
        else if(four != nullptr && return_token->prev_owner == four->get_name())
        {
            redistrib_tokens(*four, *return_token, true);

        }
        else if(five != nullptr && return_token->prev_owner == five->get_name())
        {
            redistrib_tokens(*five, *return_token, true);
        }
        else
        {
            cout<<"something wrong has happened."<<endl;
        }
    }
    if(return_token->turn_finish == true)
        delete return_token;
    else
        delete return_token;
}


void game_manager::decorate( int deco_number)
{
    one->player_stats->remove(watcher);
    two->player_stats->remove(watcher);
    if(three != nullptr)
        three->player_stats->remove(watcher);
    if(four!=nullptr)
        four->player_stats->remove(watcher);
    if(five!=nullptr)
        five->player_stats->remove(watcher);

    switch (deco_number)
    {
        case 2:
            watcher = new dom_decorator(watcher);
            break;
        case 3:
            watcher = new hand_decorator(watcher);
            break;
        case 4:
            watcher = new coin_decorator(watcher);
            break;
        default:
            break;
    }
    one->player_stats->add(watcher);
    two->player_stats->add(watcher);
    if(three != nullptr)
        three->player_stats->add(watcher);
    if(four!=nullptr)
        four->player_stats->add(watcher);
    if(five!=nullptr)
        five->player_stats->add(watcher);
    update_stats();    //
}



void game_manager::declare_winner()
{

    update_stats(); //string p_name, string p_phase, int regions, int total
    subject->change_status(one->get_name(), "END", one->get_number_regions_owned(), map_size);
    subject->change_status(two->get_name(), "END", two->get_number_regions_owned(), map_size);
    int one_score = one->get_victory_tokens();
    int two_score = two->get_victory_tokens();
    int three_score = 0;
    int four_score = 0;
    int five_score = 0;

    if(three != nullptr)
    {
        subject->change_status(three->get_name(), "END", three->get_number_regions_owned(), map_size);
        three_score = three->get_victory_tokens();
    }
    if(four != nullptr)
    {
        subject->change_status(four->get_name(), "END", four->get_number_regions_owned(), map_size);
        four_score = four -> get_victory_tokens();
    }
    if(five != nullptr)
    {
        subject->change_status(five->get_name(), "END", five->get_number_regions_owned(), map_size);
        five_score = five -> get_victory_tokens();
    }

    int score_arr[] = {one_score, two_score, three_score, four_score, five_score};
    int max = 0;
    for(int i =0; i < 5; ++i)
    {
        if(score_arr[i] > max)
        {
            max = score_arr[i];
        }
    }
    string winner = "";
    if(max == one_score)
        winner = one->get_name();
    else if(max == two_score)
        winner = two->get_name();
    else if(max == three_score)
        winner = three->get_name();
    else if(max == four_score)
        winner = four->get_name();
    else
        winner = five->get_name();

    cout<<winner<<" has won!"<<endl;
}