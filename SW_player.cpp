/*
 * Jimmy Le - 26546986
 * COMP 345 WINTER 2018 NORA H.
 * A1
 */

#include "SW_player.h"
#include "SW_map_loader.h"
using namespace std;


player::player()
{
    player_name = "Dom";
    player_dice = new dice();
    player_wallet = new wallet(5);
    player_first_culture = new culture(banner_list[2],banner_power[2],badge_list[2],badge_power[2]);
    player_second_culture= nullptr;
    first_race_stack = new bits();
    first_race_stack->add_race_tokens(badge_list[2], player_first_culture->get_culture_power());
    give_tokens(1);
    second_race_stack = new bits();
    map = nullptr;
    cout<<player_name<<" has entered the game!"<<endl;

};
player::~player()
{
    delete player_dice;
    delete player_wallet;
    delete player_first_culture;
    delete player_second_culture;
    player_first_culture = nullptr;
    player_second_culture = nullptr;
    player_dice = nullptr;
    player_wallet = nullptr;
    cout<<player_name<<" has left the game!"<<endl;

}
player::player(std::string str, loader* map_loaded)
{
    player_name = std::move(str);
    player_dice = new dice();
    player_wallet = new wallet(5);
    player_first_culture = nullptr;
    player_second_culture= nullptr;
    first_race_stack = new bits();
    second_race_stack = new bits();
    map = map_loaded;
    cout<<player_name<<" has entered the game!"<<endl;
}
const std::string  player::get_name()
{
    return player_name;
}

void player::add_map(loader * map_loaded)
{
    map = map_loaded;
}
void player::picks_race()
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
        give_tokens(1);
    }
    else
    {
        if(player_second_culture == nullptr)
        {
            player_second_culture = new culture(banner_list[banner],banner_power[banner]
                    ,badge_list[badge],badge_power[badge]);
            give_tokens(2);
        }
        else
        {
            cout<<"Can't have two races in decline!!!";
        }
    }
}

void player::give_tokens(int index)
{
    if(index == 1)
    {
//        first_race_stack->add_race_tokens(player_first_culture->get_banner(),5);
        first_race_stack->add_race_tokens(player_first_culture->get_banner(),
                                          player_first_culture->get_culture_power());
//        cout<<"race one tokens: "<<first_race_stack->get_size()<<endl;
//        cout<<"race two tokens: "<<second_race_stack->get_size()<<endl;

    }

    else if(index == 2)
    {
        second_race_stack->add_race_tokens(player_second_culture->get_banner(),
                                           player_second_culture->get_culture_power());
        cout<<"race one tokens: "<<first_race_stack->get_size()<<endl;
        cout<<"race two tokens: "<<second_race_stack->get_size()<<endl;
    }

    else
    {
        cout<<"Invalid race choice"<<endl;
    }
}
void player::conquers()
{
    //start of turn
    cout<<"enter a region_ID(int) to conquer"<<endl;
    int region_ID;
    cin>>region_ID;
    if(!(map->l1->check_ownership(region_ID, player_name)))
    {
        cout<<"Eligible region. Are you using race (1) or (2)?"<<endl;
        int race_num;
        cin>> race_num;
        if(race_num == 1)
        {
            if(first_race_stack->get_size() >=2)
            {
                map->l1->control_region(region_ID, player_name);
                first_race_stack->pop_race_tokens();
                first_race_stack->pop_race_tokens();
//                first_race_stack.pop_back(); // go to node and put in an int member
                cout<<"Adding two tokens"<<endl;
                map->l1->add_region_tokens(region_ID, 2, player_first_culture->get_banner());
                cout<<"added two tokesn of "<<player_first_culture->get_banner()<<endl;

            }
            else
                cout<<"not enough first race tokens"<<endl;
        }

        else if(race_num == 2)
        {
            if(second_race_stack->get_size() >= 2)
            {
                map->l1->control_region(region_ID, player_name);
                second_race_stack->pop_race_tokens();
                second_race_stack->pop_race_tokens();
//                second_race_stack.pop_back();
            }
            else
                cout<<"not enough second race tokens"<<endl;
        }

        else
        {
            cout<<"invalid choice in conquest()"<<endl;
        }
    }
}
void player::scores()
{
    //problem with this is that it adds total # regions. gotta do it sequentially
//    player_wallet->add_coin( loader1->l1->num_regions_controlled(player_name) );
    int total = map->l1->num_regions_controlled(player_name);
    /*
    cout<<"you should score: "<<total<<endl;

    cout<<total/10<<endl;
    cout<<total/5<<endl;
    cout<<total/3<<endl;
    cout<<total/1<<endl;

    cout<<"here it is"<<endl;
    */

    while(total > 0) // ie: 28
    {
        if( total/ 10 != 0)
        {
            for(int i = 0; i < total/10; ++i )
            {
                player_wallet->add_coin(10);
//                cout<<"ten"<<endl;
            }
            total = total/10;

        }
        if( total/ 5 != 0)
        {
            for(int i = 0; i < total/5; ++i )
            {
                player_wallet->add_coin(5);
//                cout<<"five"<<endl;
            }
            total = total/5;
        }
        if( total/ 3 != 0)
        {
            for(int i = 0; i < total/3; ++i )
            {
                player_wallet->add_coin(3);
//                cout<<"three"<<endl;

            }
            total = total/3;
        }
        if(total >0)
        {
            for(int i = 0; i < total; ++i)
            {
                player_wallet->add_coin(1);
//                cout<<"one"<<endl;
            }
            total = 0;
        }
    }
    player_wallet->print_wallet();
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
    cout<<"Coins: ";player_wallet->print_wallet();

}



