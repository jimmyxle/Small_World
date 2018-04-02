/*
 * Jimmy Le - 26546986
 * COMP 345 WINTER 2018 NORA H.
 * A1
 */

#include "SW_player.h"
#include <limits>
using namespace std;


player::player()
{
    player_name = "Dom";
    player_dice = new dice();
//    player_wallet = new wallet();
    player_first_culture = new culture(banner_list[2],banner_power[2],badge_list[2],badge_power[2]);
    player_second_culture= nullptr;
    first_race_stack = new bits();
    int power = player_first_culture->get_culture_power();
    for(int i = 0 ; i <power; ++i)
    {
        race_token* temp = new race_token(badge_list[2], true, false);
        first_race_stack->add_race_token( (temp) );
    }
    give_tokens();
    second_race_stack = new bits();
    map = nullptr;
//    first_decline = false;
    cout<<player_name<<" has entered the game!"<<"\t";

};
player::~player()
{
    delete player_dice;
//    delete player_wallet;
//    delete player_first_culture;
//    delete player_second_culture;
    player_first_culture = nullptr;
    player_second_culture = nullptr;
    player_dice = nullptr;
//    player_wallet = nullptr;
    player_central = nullptr;
    delete player_wallet;

    cout<<player_name<<" has left the game!"<<"\t";


}
player::player(std::string str, loader* map_loaded, bank* bank1)
{
    player_name = std::move(str);
    player_dice = new dice();
    player_first_culture = nullptr;
    player_second_culture= nullptr;
    first_race_stack = new bits();
    second_race_stack = new bits();
    map = map_loaded;
//    first_decline = false;

    player_central = bank1;
    player_wallet = new wallet();
    player_wallet->init(bank1);


    cout<<player_name<<" has entered the game!"<<"\t";
}
const std::string  player::get_name()
{
    return player_name;
}



void player::give_tokens()
{
    if(player_second_culture == nullptr)
    {
//        first_race_stack->add_race_tokens(player_first_culture->get_banner(),
//                                          player_first_culture->get_culture_power());
        int power = player_first_culture->get_culture_power();
        string name = player_first_culture->get_banner();
        for(int i = 0 ; i <power; ++i)
        {
            race_token* temp = new race_token(name, true, false);
            first_race_stack->add_race_token( (temp) );
        }

    }

    else
    {
        int power = player_second_culture->get_culture_power();
        string name = player_second_culture->get_banner();
        for(int i = 0 ; i <power; ++i)
        {
            race_token* temp = new race_token(name, true, false);
            second_race_stack->add_race_token( (temp) );
        }
//        second_race_stack->add_race_tokens(player_second_culture->get_banner(),
//                                           player_second_culture->get_culture_power());
    }

}


void player::redistribute_token(token * token1)
{
    if(get_second_race_active())
    {
        first_race_stack->add_race_token( token1 );
    }
    else
    {
        second_race_stack->add_race_token(token1);
    }
}

//this gets tokesn to give back to players
void player::battle(int region_ID, tokens_info& remainder)
{
    {
        if(!(map->l1->check_ownership(region_ID, "default" )) )
        {
            if(  (map->l1->check_region_is_active(region_ID)) == 0 )//check if any tokens were in decline
            {
                cout<<"!!decline detected!!"<<endl;
                (&remainder)->number_of_tokens = 0;
            }
            else
            {
                cout<<"!!active!!"<<endl;
                int num_tokens = map->l1->get_number_race_tokens(region_ID);

                cout<<"num tokens given = "<<num_tokens-1 <<endl;
                (&remainder)->number_of_tokens= (num_tokens-1);
                token* temp = nullptr;
                do{ //gotta give back to original player
                    temp = map->l1->clear_region(region_ID);
                    if(temp != nullptr)
                        (&remainder)->returned_tokens.push_back(temp);
                }while(temp != nullptr);
            }
            if((&remainder)->number_of_tokens < 0)
                (&remainder)->number_of_tokens = 0;
            (&remainder)->prev_owner = map->l1->get_owner(region_ID);
            (&remainder)->exists = true;
        }
        else
        {//lost tribes
            token* temp = nullptr;
            vector<token*> delete_these;
            delete_these.reserve(2);
            do{
                temp = map->l1->clear_region(region_ID);
                if(temp != nullptr)
                    delete_these.push_back(temp);
            }while(temp != nullptr);
            for(auto iter = delete_these.begin(); iter != delete_these.end();++iter)
                delete (*iter);
            delete_these.clear();
        }
    }
}

void player::take_over(int region_ID, int power, bits* stack)
{
    cout << "Success, region " << region_ID << " conquered!" << endl;
    map->l1->control_region(region_ID, player_name);
    cout << "Adding " << power << " tokens to region " << region_ID << endl;

    for (int i = 0; i < power; ++i)
        map->l1->add_region_token(region_ID, stack->pop_race_token());

    cout << player_name << " has " << stack->get_size() << " tokens left" << endl;
}

vector<int> player::show_edges(int number_players)
{
    vector<int> arr;
    switch(number_players) {
        case 2:
            arr = { 1, 2, 3, 4,
                   5, 10, 11, 15, 16,
                   17, 18, 19, 20};
            break;
        case 3:
            arr = { 2, 3, 4, 5,
                   6, 7, 12, 17, 18,
                   24, 25, 26, 27, 28};
            break;
        case 4:
            arr = { 3, 4, 5, 11,
                   12, 18, 19, 24, 25,
                   29, 30, 31, 34, 35,
                    37, 38};
            break;
        case 5:
            arr = {1, 2, 3, 4,
                   5, 6, 13, 18, 24,
                   29, 30, 35, 40, 41,
                   43, 44, 45, 46, 47};
            break;
        default:
            break;
    }
    for(int i =0; i<arr.size(); ++i)
    {
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    return arr;
}

bool player::check_sea(int region_ID, int number_players)
{
    vector<int> arr;
    switch(number_players)
    {
        case 2:
            arr = {0, 7, 22};
            break;
        case 3:
            arr={0,14,29};
            break;

        case 4:
            arr={0,16, 36};

        case 5:
            arr={0,16,42};

        default:
            break;
    }
    for(int i = 0; i < arr.size(); ++i)
    {
        if(region_ID == arr[i])
            return true;
    }

    return false;
}
tokens_info* player::conquers(int map_number)
{
    tokens_info* remainder = new tokens_info();
    (remainder)->number_of_tokens = 0;
    (remainder)->prev_owner = "";
    (remainder)->exists=false;
    remainder->returned_tokens.reserve(13);
    remainder->turn_finish = 0;

    //start of turn
    cout<<endl;

    List* list_ptr = map->l1;


    bool keep_conquering = true;
    do
    {
        int region_ID = 0;
        vector<int> regions_list = list_ptr -> get_region_array(player_name);
        int first_conquer = player_display(regions_list, *list_ptr);

        if(first_conquer == 0)
        {
            //must conquer from the following list:
            cout<<"This is your first conquer, "
                    "so you must choose a region found at the edge:"<<endl;
            vector<int> edge_list = show_edges(map_number);
            bool not_edge = true;
            do
            {
                cin>>region_ID;

                for(int i = 0; i < edge_list.size(); ++i)
                {
                    if(region_ID == edge_list[i])
                    {
                        not_edge = false;
                        break;
                    }
                }
                if(not_edge)
                    cout<<"choose again!"<<endl;

            }while(not_edge);
        }
        else
        {
            bool is_sea = true;
            do
            {
                cout << "Enter a region_ID(int) to conquer. Enter a -1 to skip the rest of the turn." << endl;
                cin >> region_ID;

                if(region_ID < 0)
                {
                    is_sea = false;
                }
                else
                {
                    if (check_sea(region_ID, map_number))
                        cout << "You cannot conquer the sea. Choose again!" << endl;
                    else
                        is_sea = false;
                }
            }while(is_sea);


            if(region_ID > 0)
            {
                bool adjacent_okay = false;
                do {
                    bool acceptable = list_ptr->check_adjacency(region_ID, player_name);

                    if (acceptable == false) {
                        cout << "This node is not adjacent to any of your regions. Choose again." << endl;
                        cin >> region_ID;
                    } else
                        adjacent_okay = true;

                } while (adjacent_okay == false);
            }
        }


        if (region_ID < 0) {
            cout << "Turn skipped" << endl;
            keep_conquering = false;
            remainder->turn_finish = 1;
        }
        else
        {
            if (!(map->l1->check_ownership(region_ID, player_name)))
            {
                cout << "Eligible region." << endl;
                int SIZE = 0;

                if (get_second_race_active())
                {
                    SIZE = first_race_stack->get_size();
                }
                else
                {
                    SIZE = second_race_stack->get_size();
                }

                {
                    int player_power = SIZE;
                    if (player_power >= 0)
                    {
                        //Check how many tokens there are, including mountain
                        int strength = map->l1->get_region_strength(region_ID) + 2;

                        int power = 0;
                        int dice_affirm = 0;
                        int roll_result = 0;

                        cout << "You need to have " << strength << " to conquer this." << endl;

                        if (player_power >= 1 && strength > player_power &&
                            (player_power + 3) >= strength) {
                            cout << "You must use the reinforcement die to conquer this" << endl;
                            cout << "Enter: '1' to roll the die." << endl;
                            cin >> dice_affirm;
                            if (dice_affirm == 1) {
                                roll_result = player_dice->rollDice();
                            }
                            else
                            {
                                roll_result = 0;
                            }
                            player_power += roll_result;
                            if (player_power >= strength) {
                                cout << "Comquered!" << endl;
                                //slap on units
                                if(get_second_race_active()){
                                    take_over(region_ID, SIZE, first_race_stack);
                                }
                                else
                                {
                                    take_over(region_ID, SIZE, second_race_stack);

                                }
                                keep_conquering = false;
                            } else {
                                cout << "too weak" << endl;
                                keep_conquering = false;
                                remainder->turn_finish = 1;
                            }
                        } else {
                            cout << "You currently have " << player_power << " tokens." << endl;
                            cout << "How many do you want to use to conquer [" << region_ID << "] ?" << endl;
                            cin >> power;
                            if (power >= strength && power <= player_power) {
                                cout << endl;
                                battle(region_ID, *remainder);
                                if(get_second_race_active())
                                {
                                    take_over(region_ID, power, first_race_stack);
                                }
                                else
                                {
                                    take_over(region_ID, power, second_race_stack);
                                }

                                power = 0;
                            } else {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << "Not strong enough" << endl;
                                remainder->turn_finish = 1;
                            }
                        }
                    }
                    else
                    {
                        keep_conquering = false;
                        cout << "not enough first race tokens" << endl;
                    }
                }
            } else {
                cout << "You already control this!" << endl;
                conquers(map_number);
            }
        }
        if(get_second_race_active())
        {
            if(first_race_stack->get_size() == 0)
                keep_conquering = false;

        }
        else
        {
            if(second_race_stack->get_size() == 0)
                keep_conquering = false;
        }
    }
    while(keep_conquering);

    return remainder;
}
void player::scores()
{
    int total = map->l1->num_regions_controlled(player_name);
    int total_display = total;
    while(total > 0) // ie: 28
    {
        if( total/ 10 != 0)
        {
            for(int i = 0; i < total/10; ++i )
                player_wallet->add_coin(10);

            total = total/10;

        }
        if( total/ 5 != 0)
        {
            for(int i = 0; i < total/5; ++i )
                player_wallet->add_coin(5);

            total = total/5;
        }
        if( total/ 3 != 0)
        {
            for(int i = 0; i < total/3; ++i )
                player_wallet->add_coin(3);
            total = total/3;
        }
        if(total >0)
        {
            for(int i = 0; i < total; ++i)
                player_wallet->add_coin(1);
            total = 0;
        }
    }
    cout<<"------------------------"<<endl;
    cout<<"Player "<<player_name<<endl;
    cout<<"------------------------"<<endl;

    cout<<"\tNumber of regions controlled: "<<total_display<<" region(s)!"<<endl;
    cout<<"\tNumber of Victory Coins: "<<player_wallet->get_wallet_total()<<endl;
}
void player::get_status()
{
    cout<<"Name: "<<player_name<<endl;
    int num_tokens = player_first_culture->get_culture_power();
    cout<<"1st Race: "<<player_first_culture->get_badge()<<" "
        <<player_first_culture->get_banner()<<endl;
    if(player_second_culture != nullptr)
    {
        cout<<"2nd Race: "<<player_second_culture->get_badge()<<" "
            <<player_second_culture->get_banner()<<endl;
        num_tokens += player_second_culture->get_culture_power();
    }

    cout<<"Player has: "<<num_tokens<<" tokens"<<endl;
//    cout<<"Coins: ";player_wallet->print_wallet();

}
void player::set_first_culture(culture first)
{
    player_first_culture = &(first);
}

int player::get_number_of_tokens_owned() {
    if (get_second_race_active()) {
        return first_race_stack->get_size();
    } else {
        return second_race_stack->get_size();
    }
}

void player::player_decline()
{
    player_second_culture = player_first_culture;
    player_first_culture = nullptr;
    first_race_stack->clean();
    first_race_stack = nullptr;
}


bool player::first_culture_null()
{
    return player_first_culture == nullptr;
}

bool player::get_second_race_active()
{
    return player_second_culture == nullptr;
}

tokens_info* player::redeploy()
{
    tokens_info* temp =  map->l1->region_in_withdraw(player_name);
    return temp;
}

int player::player_display(vector<int>& regions_list, List& list_ptr)
{
    if(regions_list.size() > 0) {
        cout << "Here's the list of regions you control: " << endl;
        for (int i = 0; i < regions_list.size(); ++i)
            (&list_ptr)->get_region_info(regions_list[i]);
        return 1;
    }
    else
    {
        return 0;
    }
}

void player::redeploy_menu()
{
    List* list_ptr = map->l1;
    vector<int> regions_list = list_ptr -> get_region_array(player_name);
    int remaining_tokens = 0;
    if(get_second_race_active())
        remaining_tokens = first_race_stack->get_size();
    else
        remaining_tokens = second_race_stack->get_size();
    bool continue_token = true;
    do
    {
        player_display(regions_list, *list_ptr);

        cout<<"Choose which regions to reinforce!"<<endl;
        int ID_choice = 0;
        bool exists = false;

        do
        {
            cin>> ID_choice;
            for(int i = 0; i < regions_list.size(); ++i)
            {
                if(ID_choice == regions_list[i])
                    exists = true;
            }

            if(exists == false)
                cout<<"Wrong region ID, choose again!"<<endl;
        }while(exists == false);
//
        int token_choice = 0;
        do
        {
            cout<<"Current number of tokens: "<<remaining_tokens<<endl;
            cout<<"You can place any number of tokens from [1 - "<<remaining_tokens<<"]"<<endl;
            cin>>token_choice;

            if(token_choice<0 || token_choice > remaining_tokens)
                cout<<"invalid entry. Please enter another entry"<<endl;
        }while(token_choice < 0 || token_choice > remaining_tokens);

        for(int i = 0; i < token_choice; ++i)
        {
            if(get_second_race_active())
            {
                token* temp = first_race_stack->pop_one();
                list_ptr->add_region_token(ID_choice, temp);
            }
            else
            {
                token* temp = second_race_stack->pop_one();
                list_ptr -> add_region_token(ID_choice, temp);
            }
        }

        if(get_second_race_active())
            remaining_tokens = first_race_stack->get_size();
        else
            remaining_tokens = second_race_stack->get_size();

        if(remaining_tokens == 0)
            continue_token = false;

    }while(continue_token);


}


tokens_info* player::abandon_menu()
{

    List* list_ptr = map->l1;
    int remaining_tokens = 0;
    tokens_info* return_token = new tokens_info();

    bool continue_token = true;
    do {
        if(get_second_race_active())
            remaining_tokens = first_race_stack->get_size();
        else
            remaining_tokens = second_race_stack->get_size();

        vector<int> regions_list = list_ptr -> get_region_array(player_name);

        player_display(regions_list, *list_ptr);
//        cout<<endl<<"Here's the current number of tokens: "<<remaining_tokens<<endl;
        cout << "Choose which regions to abandon!"<< endl;
        cout<<"Enter -1 to skip ahead"<<endl;
        int ID_choice = 0;
        bool exists = false;

        do {
            cin >> ID_choice;
            if(ID_choice < 0)
            {
                continue_token = false;
                break;
            }


            for(int i = 0; i < regions_list.size(); ++i)
            {
                if(ID_choice == regions_list[i])
                    exists = true;
            }
            if(exists == false)
                cout<<"Wrong region ID, choose again!"<<endl;

        } while (exists == false);

        //take user choice and go to that region and clear it out
        //ID_choice
        if(exists)
            return_token = list_ptr -> abandon_region(ID_choice, *return_token);



    }while(continue_token);

    return_token->prev_owner = player_name;
    return return_token;
}

int player::get_number_regions_owned()
{
    List* list_ptr = map->l1;
    int number = list_ptr->num_regions_controlled(player_name);
//    cout<<number<<endl;
    return number;
}
