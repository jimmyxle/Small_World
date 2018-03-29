/*
 * Jimmy Le - 26546986
 * COMP 345 WINTER 2018 NORA H.
 * A1
 */

#include "SW_player.h"
#include "SW_map_loader.h"
#include <limits>
using namespace std;

tokens_info::tokens_info()
{
    number_of_tokens = 0;
    prev_owner = "";
    exists = false;
    returned_tokens.reserve(5);
}

tokens_info::~tokens_info()
{
    for(auto iter = returned_tokens.begin(); iter != returned_tokens.end(); ++iter)
    {
        delete (*iter);
    }
}
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

void player::add_map(loader * map_loaded)
{
    map = map_loaded;
}

void player::picks_race() // no longer used
{
    //have a list
    //prompt user to pick oned
    const int SIZE = banner_list.size();
    int banner;
    int badge;
    cout<<"Pick a race from the following list using the indexes [0-"<<SIZE-1<<"]"
        <<endl;
    for(int i =0; i<SIZE; ++i)
    {
        cout<<i<<": "<<banner_list[i]<<"["<<banner_power[i]<<"]"<<endl;
    }
    do {
        cout<<"Choose a race [0-"<<SIZE-1<<"]"<<endl;
        cin >> banner;
    }
    while(banner<0 || banner>SIZE);

    const int SIZE2 = badge_list.size();
    cout<<"Pick a power from the following list using the indexes [0-"<<SIZE2-1<<"]"
        <<endl;
    for(int i =0; i<SIZE2; ++i)
    {
        cout<<i<<": "<<badge_list[i]<<"["<<badge_power[i]<<"]"<<endl;
    }
    do {
        cout<<"Choose a power [0-"<<SIZE2-1<<"]"<<endl;
        cin >> badge;
    }
    while(badge<0 && badge>SIZE2);
    cout<<"you picked: "<<badge_list[badge]<<" ["<<badge_power[badge]<<"]"
        <<banner_list[banner]<<" ["<<banner_power[banner]<<"]"<<endl;

    if(player_first_culture == nullptr)
    { //culture::culture(std::string ban_name, int ban_power, std::string bad_name, int bad_power)
        player_first_culture = new culture(banner_list[banner],banner_power[banner]
                ,badge_list[badge],badge_power[badge]);
        give_tokens();
    }
    else
    {
        if(player_second_culture == nullptr)
        {
            player_second_culture = new culture(banner_list[banner],banner_power[banner]
                    ,badge_list[badge],badge_power[badge]);
            give_tokens();
        }
        else
        {
            cout<<"Can't have two races in decline!!!";
        }
    }
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
/*
void player::redistribute_tokens(int index, int number_of_tokens)
{
    if(get_second_race_active())
    {

        first_race_stack->add_race_tokens(player_first_culture->get_banner(),
                                          number_of_tokens);
        cout<<player_name<<" now has "<<first_race_stack->get_size()<<" (1)tokens."<<endl;

    }
    else
    {
        second_race_stack->add_race_tokens(player_second_culture->get_banner(),
                                           number_of_tokens);
        cout<<player_name<<" now has "<<second_race_stack->get_size()<<" (2)tokens."<<endl;

    }



}
 */
tokens_info* player::conquers()
{
    //start of turn
    cout<<endl;


    tokens_info* remainder = new tokens_info();
    (remainder)->number_of_tokens = 0;
    (remainder)->prev_owner = "";
    (remainder)->exists=false;
    remainder->returned_tokens.reserve(5);
    cout<<"enter a region_ID(int) to conquer"<<endl;
    int region_ID;
    cin>>region_ID;
    if(!(map->l1->check_ownership(region_ID, player_name)))
    {
        cout<<"Eligible region."<<endl;
        int race_num = 0;

        if(get_second_race_active())
            race_num = 1;
        else
            race_num = 2;


        if(race_num == 1)
        {
            int player_power = first_race_stack->get_size();
            if(player_power>=2)
            {
                //Check how many tokens there are, including mountain
                int strength = map->l1->get_region_strength(region_ID) + 2;

                int power = 0;
                do
                {
                    cout<<"You need to have "<<strength<<" to conquer this."<<endl;
                    cout<<"You currently have "<<player_power<<" tokens."<<endl;
                    cout<<"How many do you want to use to conquer ["<<region_ID<<"] ?"<<endl;
                    cin>>power;

                    if(power >= strength && power <= player_power)
                    {
                        //check for previous owner existence
                        {
                            if(!(map->l1->check_ownership(region_ID, "default" )) )
                            {
//                                cout<<endl<<endl<<"trouble?"<<endl;
                                if(  !(map->l1->check_region_is_decline(region_ID)) )//check if any tokens were in decline
                                {
                                    cout<<"decline detected"<<endl;
                                    remainder->number_of_tokens = 0;
                                }
                                else
                                {
                                    cout<<"decline not detected"<<endl;
                                    int num_tokens = map->l1->get_number_race_tokens(region_ID);
//                                    cout<<"num tokens detected = "<<num_tokens<<endl;
                                    cout<<"num tokens given = "<<num_tokens-1 <<endl;
                                    remainder->number_of_tokens= (num_tokens-1);
                                }
                                //this happens no matter what

                                cout<<"Tokens returned = "<<remainder->number_of_tokens<<endl;
                                if(remainder->number_of_tokens < 0)
                                    remainder->number_of_tokens = 0;
                                remainder->prev_owner = map->l1->get_owner(region_ID);
                                remainder->exists = true;
                                remainder->number_of_tokens = 0;
                                //note if first or second race
                            }
                        }
                        //go in region + remove race tokens but not mountain




                        token* temp = nullptr;
                        do{ //gotta give back to original player
//                            cout<<endl<<"this size: "<<map->l1->get_number_race_tokens(region_ID)<<endl;
                            temp = map->l1->clear_region(region_ID);
                            remainder->returned_tokens.push_back(temp);
                        }while(temp != nullptr);

                        cout<<"Success, region "<<region_ID<<" conquered!"<<endl;
                        map->l1->control_region(region_ID, player_name);


                        cout<<"Adding "<<power<<" tokens to region "<<region_ID<<endl;
                        for(int i = 0; i < power; ++i)
                            map->l1->add_region_token(region_ID, first_race_stack->pop_race_token());


                        /*
                         * here
                         */
                        map->l1->get_region_strength(region_ID);

//                        map->l1->add_region_tokens(region_ID, power, player_first_culture->get_banner());
                        cout<<player_name<<" has "<<first_race_stack->get_size()<<" tokens left"<<endl;

                        power = 0;
                    }
                    else
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout<<"Not strong enough"<<endl;
                        cout<<"Enter '0' if you wish to pass your turn. "
                                "Enter a negative number to try again."<<endl;
                        cin>>power;
                        if(power == 0)
                            break;
                    }
                }while(power<0 || power> player_power );
//                first_race_stack.pop_back(); // go to node and put in an int member
            }
            else
                cout<<"not enough first race tokens"<<endl;
            //have other option here
        }
        else if(race_num == 2)
        {
            int player_power = second_race_stack->get_size();
            if(player_power>=2)
            {
                //Check how many tokens there are, including mountain
                int strength = map->l1->get_region_strength(region_ID) + 2;
                int power = 0;
                do
                {
                    cout<<"You need to have more than "<<strength<<" to conquer this."<<endl;
                    cout<<"You currently have "<<player_power<<" tokens."<<endl;
                    cout<<"How many do you want to use to conquer ["<<region_ID<<"] ?"<<endl;
                    cin>>power;

                    if(power >= strength && power < player_power)
                    {
                        //check for previous owner existence
                        {
                            if(!(map->l1->check_ownership(region_ID, "default" )) )
                            {

                                remainder->number_of_tokens= map->l1->get_number_race_tokens(region_ID)-1;
                                cout<<"Tokens returned = "<<remainder->number_of_tokens<<endl;
                                if(remainder->number_of_tokens < 0)
                                    remainder->number_of_tokens = 0;
                                remainder->prev_owner = map->l1->get_owner(region_ID);
                                remainder->exists = true;
                                remainder->number_of_tokens =0;
                            }
                        }
                        //go in region + remove race tokens but not mountain

                        token* temp = nullptr;
                        do{ //gotta give back to original player
                            temp = map->l1->clear_region(region_ID);
                            remainder->returned_tokens.push_back(temp);
                        }while(temp != nullptr);


//                        map->l1->clean_region(region_ID); //
                        cout<<"success"<<endl;
                        map->l1->control_region(region_ID, player_name);
                        cout<<"Adding "<<power<<" tokens to region "<<region_ID<<endl;

                        for(int i = 0; i < power;++i )
                            map->l1->add_region_token(region_ID, second_race_stack->pop_race_token());


                        cout<<player_name<<" has "<<second_race_stack->get_size()<<" tokens left"<<endl;

//                        cout<<"added "<<power<<" tokens of "<<player_first_culture->get_banner()<<endl;
//                        cout<<"Region "<<region_ID<<" now has "<<map->l1->get_region_strength(region_ID)<<endl;
                        power = 0;
                    }
                    else
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout<<"Not strong enough"<<endl;
                        cout<<"Enter '0' if you wish to pass your turn. "
                                "Enter a negative number to try again."<<endl;
                        cin>>power;
                        if(power == 0)
                            break;

                    }
                }while(power<0 || power> player_power );

//                first_race_stack.pop_back(); // go to node and put in an int member
            }
            else
                cout<<"not enough second race tokens"<<endl;

        }

    }
    else
    {
        cout<<"You already control this!"<<endl;
        conquers();
    }
    return remainder;
}
void player::scores()
{
    int total = map->l1->num_regions_controlled(player_name);
    while(total > 0) // ie: 28
    {
        if( total/ 10 != 0)
        {
            for(int i = 0; i < total/10; ++i )
            {
                player_wallet->add_coin(10);
//                cout<<"add coin line 359"<<endl;
            }
            total = total/10;

        }
        if( total/ 5 != 0)
        {
            for(int i = 0; i < total/5; ++i )
            {
                player_wallet->add_coin(5);
//                cout<<"add coin line 368"<<endl;

            }
            total = total/5;
        }
        if( total/ 3 != 0)
        {
            for(int i = 0; i < total/3; ++i )
            {
                player_wallet->add_coin(3);
//                cout<<"add coin line 799"<<endl;

//                cout<<"three"<<endl;

            }
            total = total/3;
        }
        if(total >0)
        {
//            cout<<"Testing: total is "<<total<<endl;
            for(int i = 0; i < total; ++i)
            {
//                player_wallet->add_coin(1);
//                cout<<"add coin line 391"<<endl;
                player_wallet->add_coin(1);
//                cout<<"one"<<endl;
            }
            total = 0;
        }
    }
    cout<<"player "<<player_name<<" has: "<<player_wallet->get_wallet_total()<<" coins"<<endl;
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
}

bool player::first_culture_null()
{
    return player_first_culture == nullptr;
}
/*
void player::set_decline()
{
    first_decline = !first_decline;
}

bool player::get_decline()
{
    return first_decline;
}
 */
bool player::get_second_race_active()
{
    return player_second_culture == nullptr;
}
