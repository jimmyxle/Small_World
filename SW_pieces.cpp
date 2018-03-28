/*
 * Jimmy Le - 26546986
 * COMP 345 WINTER 2018 NORA H.
 * A1
 */
#include <iostream>
#include <utility>
#include <memory>
#include <ctime>
#include <random>
//#include "SW_player.h"

using namespace std;
#include "SW_pieces.h"

/*
 * game_turn_token class
 */
game_turn_token::game_turn_token()
{
    turn_number =0;
}
game_turn_token::game_turn_token(int number_of_players)
{
    turn_number =0;
    switch(number_of_players)
    {
        case 2:
            MAX_TURNS = 10;
            break;
        case 3:
            MAX_TURNS = 10;
            break;
        case 4:
            MAX_TURNS = 9;
            break;
        case 5:
            MAX_TURNS = 8;
            break;
        default:
            cout<<"wrong input"<<endl;
            break;
    }
}

game_turn_token::~game_turn_token()
{

}
int game_turn_token::get_turn_number()
{
    return turn_number;
}

bool game_turn_token::next_turn()
{
    if(turn_number < MAX_TURNS)
    {
        turn_number++;
        cout<<"Turn advanced to turn: "<<turn_number<<endl;
        if(turn_number == MAX_TURNS)
            cout<<"It's the last turn!"<<endl;
        return true;
    }
    else
    {
        cout<<"Game has ended."<<endl;
        return false;
    }
}
/*
 * End of game_turn_token
 */

/*
 * Beginning of the Bank class
 */

coin::coin()
{
    coin_value = 1;
}
coin::~coin(){}
coin::coin(int value)
{
    coin_value = value;
}
int coin::get_coin()
{
    return coin_value;
}

bank::bank()
{

    ones.reserve(3*BASE_SIZE);
    threes.reserve(BASE_SIZE);
    fives.reserve(BASE_SIZE);
    tens.reserve(BASE_SIZE);

    initiate();
    cout<<"Bank created"<<endl;
}
bank::~bank()
{
    for(auto iter = ones.begin(); iter != ones.end(); ++iter)
    {
        delete (*iter);
    }
    ones.clear();

    for(auto iter = threes.begin(); iter != threes.end(); ++iter)
    {
        delete (*iter);
    }
    threes.clear();

    for(auto iter = fives.begin(); iter != fives.end(); ++iter)
    {
        delete (*iter);
    }

    fives.clear();

    for(auto iter = tens.begin(); iter != tens.end(); ++iter)
    {
        delete (*iter);
    }
    tens.clear();

    cout<<"Bank emptied"<<endl;
}

void bank::initiate()
{
    for(int iter = 0; iter < 3*BASE_SIZE; ++iter)
    {
        coin *temp= new coin(1);
        ones.push_back( temp );
}
    for(int iter = 0; iter < BASE_SIZE; ++iter)
    {
        coin *temp= new coin(3);
        threes.push_back( temp );

        temp = new coin(5);
        fives.push_back( temp );

        temp= new coin(10);
        tens.push_back( temp );
    }
//    cout<<"ones size: "<<ones.size()<<endl;
//    cout<<"threes size: "<<threes.size()<<endl;
//    cout<<"fives size: "<<fives.size()<<endl;
//    cout<<"tens size: "<<tens.size()<<endl;
//
//
//    cout<<"initiated"<<endl;
//    cout.flush();
}

coin* bank::give_coins( int value)
{
    //go to a vector according to value
    //assign a temp to the pointer
    //pop back that vector
    //return pointer
    coin* temp = nullptr;
    switch(value)
    {
        case 1:
            temp = ones.back();
            ones.pop_back();
            return temp;
        case 3:
            temp = threes.back();
            threes.pop_back();
//            cout<<threes.size()<<endl;
            return temp;
        case 5:
            temp = fives.back();
            fives.pop_back();
            return temp;
        case 10:
            temp = tens.back();
            tens.pop_back();
            return temp;
        default:
            cout<<"something went wrong"<<endl;
            return NULL;
    }
}

void bank::return_coin(coin * target)
{
    switch(target->get_coin())
    {
        case 1:
            ones.push_back(target);
            break;
        case 3:
            threes.push_back(target);
            break;
        case 5:
            fives.push_back(target);
            break;
        case 10:
            tens.push_back(target);
            break;
        default:
            cout<<"problem!"<<endl;
            break;
    }
}
/*
 * Beginning of wallet class
 */
wallet::wallet()
{
    const int SIZE = 10;
    player_ones.reserve(SIZE);
    player_threes.reserve(SIZE);
    player_fives.reserve(SIZE);
    player_tens.reserve(SIZE);
};

wallet::~wallet()
{
    for(auto iter = player_ones.begin(); iter != player_ones.end(); ++iter)
    {
        delete (*iter);
    }
    player_ones.clear();

    for(auto iter = player_threes.begin(); iter != player_threes.end(); ++iter)
    {
        delete (*iter);
    }
    player_threes.clear();

    for(auto iter = player_fives.begin(); iter != player_fives.end(); ++iter)
    {
        delete (*iter);
    }

    player_fives.clear();

    for(auto iter = player_tens.begin(); iter != player_tens.end(); ++iter)
    {
        delete (*iter);
    }
    player_tens.clear();

    cout<<"Wallet emptied"<<endl;
}

void wallet::set_central(bank * bank1)
{
    central = bank1;
}

void wallet::first_coins()
{
    for(int i = 0; i < 5; ++i)
        player_ones.push_back( central->give_coins(1) );
}

void wallet::init(bank* bank1)
{
    set_central(bank1);
    first_coins();
}

void wallet::add_coin(int value)
{
    switch(value)
    {
        case 1:
            player_ones.push_back( central->give_coins(value) );
            break;
        case 3:
            player_threes.push_back( central->give_coins(value));
            break;
        case 5:
            player_fives.push_back( central->give_coins(value));
            break;
        case 10:
            player_tens.push_back( central->give_coins(value));
            break;
        default:
            cout<<"problem!"<<endl;
            break;
    }
}

bool wallet::remove_coin(int value)
{
    switch(value)
    {
        coin* temp;
        case 1:
            if(player_ones.size() > 0)
            {
                temp = player_ones.back();
                player_ones.pop_back();

                central->return_coin(temp);

                return true;
            }
            else
            {
                cout<<"don't have this coin in the wallet."<<endl;
                return false;
            }
        case 3:
            if(player_threes.size() > 0)
            {
                temp = player_threes.back();
                player_threes.pop_back();
                central->return_coin(temp);
                return true;
            }
            else
            {
                cout<<"don't have this coin in the wallet."<<endl;
                return false;
            }
        case 5:
            if(player_fives.size() > 0)
            {
                temp = player_fives.back();
                player_fives.pop_back();
                central->return_coin(temp);
                return true;
            }
            else
            {
                cout<<"don't have this coin in the wallet."<<endl;
                return false;
            }
        case 10:
            if(player_tens.size() > 0)
            {
                temp = player_tens.back();
                player_tens.pop_back();
                central->return_coin(temp);
                return true;
            }
            else
            {
                cout<<"don't have this coin in the wallet."<<endl;
                return false;
            }
        default:
            cout<<"problem!"<<endl;
            break;
    }
    return false;
};
int wallet::get_wallet_total()
{
    int sum = 0;
    sum += player_ones.size()*1;
    sum += player_threes.size()*3;
    sum += player_fives.size()*5;
    sum += player_tens.size()*10;
    return sum;
}

/*
 * End of Wallet class
 */

/*
 * Board Bits
 */
token::token()
{
    name = "";
    mountain = false;
}

token::token(std::string n , bool m)
{
    name = n;
    mountain = m;
}
token::~token(){}

std::string token::get_name()
{
    return name;
}

bool token::is_mountain()
{
    return mountain;
}
void token::flip_token()
{

}
bool token::is_active()
{

}
race_token::race_token() : token()
{
//    name = "toy token";
    cout<<"default token created"<<endl;
}
race_token::race_token(string name, bool status, bool mount) : token(name, mount)
{

}

//race_token::race_token( race_token& original)
//{
//    name_of_race = original.name_of_race;
//    active = original.active;
//}

race_token::~race_token()=default;


void race_token::flip_token()
{
    active = !active;
}
bool race_token::is_active()
{
   return active;
}
//std::string race_token::get_name()
//{
//    return get_name();
//}

void race_token::foo()
{

}

terrain_token::terrain_token()
{
//    terrain = "rain puddle";
    cout<<"default terrain created"<<endl;
}
terrain_token::terrain_token(std::string tera, bool mount) : token(tera, mount)
{
//    terrain = tera;
}
terrain_token::~terrain_token()=default;


//std::string terrain_token::getTerrain()
//{
//    return terrain;
//}
void terrain_token::foo()
{

}

bits::bits()
{
    pile.clear();
//    cout<<"bits created"<<endl;
//
//    race_token * r1 = new race_token( ) ;
//    pile.push_back(r1);
//    cout<<"Hey"<<endl;
//    pile.pop_back();
//    cout<<pile.size()<<endl;
//    pile->reserve(10);
}
bits::~bits()
{

//    token* pointer;
//    if(pile.size() > 0)
//    {
//        cout<<"HERE's the SIZE "<<pile.size()<<endl;
//        for(auto iter = pile.begin(); iter != pile.end(); ++iter)
//        {
//            pointer = *iter;
//            delete pointer;
//        }
//    }

}

void bits::add_race_tokens(std::string name , int num_tokens)
{
    for(int i =0; i < num_tokens; ++i)
    {
        race_token* temp = new race_token(name, true, false);
        pile.push_back(temp);
    }
//    cout<<"HEY"<<endl;
//    cout<<pile.size()<<endl;
}
void bits::pop_race_tokens()
{
    pile.pop_back();
}
int bits::get_size()
{
    return pile.size();
}

void bits::print_pile()
{
    for(auto iter = pile.begin(); iter != pile.end(); ++iter)
    {
        cout<<(*iter)->get_name()<<" ";
    }
    cout<<endl;
}
void bits::add_mountain_token()
{
    pile.push_back(new terrain_token("mountain", true));
}

void bits::clean()
{
//    cout<<"this has a size of "<<pile.size()<<endl;
    for(auto rev_iter = pile.rbegin(); rev_iter!= pile.rend(); ++rev_iter)
    {
        (*rev_iter)->get_name();
        if( (*rev_iter)->is_mountain() )
        {
           //skip
        }
        else
        {
            pile.pop_back();
        }
    }
//    cout<<"this now has a size of "<<pile.size()<<endl;

}
int bits::number_race_tokens()
{
    int count = 0;
    for(auto iter = pile.begin(); iter != pile.end(); ++iter)
    {
        if(!((*iter)->is_mountain()))
            count++;
    }
    return count;
}
void bits::token_decline()
{
    int count = 0;
    for(auto iter = pile.rbegin(); iter!= pile.rend(); ++iter)
    {
        if(!((*iter)->is_mountain()) )
        {
            if(count < 1){
                (*iter)->flip_token();
                count++;
            }
            else
            {
                pile.pop_back();
            }
        }
    }
    cout<<"finished declining"<<endl;
}

bool bits::get_decline()
{
    for(auto iter = pile.begin(); iter!=pile.end(); ++iter)
    {
        if(! ((*iter)->is_mountain()) )
        {
            return (*iter)->is_active();
        }
    }
}

/*
 * End of board bits
 */

/*
 * Culture
 */
culture::banners::banners()=default;
culture::banners::~banners()=default;

culture::badges::badges()=default;
culture::badges::~badges()=default;

culture::culture()
{
//    banner
    player_banner.banner_name= "frosty kittens";
    player_banner.banner_value= 6;
//    badge
    player_badge.badge_name="wretched";
    player_badge.badge_value = 4;
    culture_power = player_banner.banner_value + player_badge.badge_value;
    cout<<"["<<player_badge.badge_name<<"] "<<"["<<player_banner.banner_name
        <<"] created with a power of: [" <<culture_power<<"]"<<endl;
}

culture::culture(std::string ban_name, int ban_power, std::string bad_name, int bad_power)
{
//      banner
    player_banner.banner_name= std::move(ban_name);
    player_banner.banner_value= ban_power;

//    badge
    player_badge.badge_name= std::move(bad_name);
    player_badge.badge_value = bad_power;
    culture_power = player_banner.banner_value + player_badge.badge_value;
    cout<<"["<<player_badge.badge_name<<"] "<<"["<<player_banner.banner_name
        <<"] created with a power of: [" <<culture_power<<"]"<<endl;
}
culture::culture(std::string race_name, int race_power)
{
//    cout<<"race: "<<race_name<<" "<<race_power<<endl;
    player_banner.banner_name = race_name;
    player_banner.banner_value = race_power;

    player_badge.badge_name= "";
    player_badge.badge_value = 0;
    culture_power = player_banner.banner_value + player_badge.badge_value;

}

culture::~culture()= default;

void culture::give_badge(std::string name, int power)
{
//    cout<<"Gave "<<name<<" "<<power<<endl;
    player_badge.badge_name= name;
    player_badge.badge_value = power;
    culture_power = player_banner.banner_value + player_badge.badge_value;
}
void culture::print_culture()
{
    cout<<"["<<player_badge.badge_name<<"] "<<"["<<player_banner.banner_name
        <<"] : [" <<culture_power<<"]"<<endl;
}
const int culture::get_culture_power()
{
    return culture_power;
}
const std::string culture::get_banner()
{
    return player_banner.banner_name;
}
const std::string culture::get_badge()
{
    return player_badge.badge_name;
}
/*
 * End of culture
 */
culture_set::culture_set()
{
    DECK_SIZE = banner_list.size();
    for(int i = 0; i < banner_list.size(); ++i)
    {
        race_list.push_back(banner_list[i]);
        race_power.push_back(banner_power[i]);
    }
    for(int i = 0; i < badge_list.size(); ++i)
    {
        ability_list.push_back(badge_list[i]);
        ability_power.push_back(badge_power[i]);
    }

//    cout<<race_list.size()<<" AND "<<ability_power.size()<<endl;
}
culture_set::~culture_set()
{
    visible.clear();
    deck.clear();

}



void culture_set::shuffle()
{
    mt19937 randomGenerator(time(nullptr));

    string r_name = "";
    int r_power = 0;
    string a_name = "";
    int a_power = 0;
    int index;
    int r_size = race_list.size()-1;
    int p_size = ability_list.size()-1;

    do{
        uniform_int_distribution<int> race_roll(0, r_size);
        index = race_roll(randomGenerator); //cout<<"index chosen: "<<index<<endl;
        r_name = race_list[index]; //cout<<"chosen race: "<<r_name<<endl;
        r_power = race_power[index]; //cout<<"race power: "<<r_power<<endl;
        //swap to end + pop_back
        {
            race_list.erase(race_list.begin() + index);
            //swap to end + pop_back
            race_power.erase(race_power.begin() + index);
        }
        culture* temp = new culture(r_name, r_power);
        deck.push_back( *temp );
        r_size--;
    }while(r_size >= 0);
    r_size =  deck.size();
    int count = 0;
    do{
        uniform_int_distribution<int> race_roll(0, p_size);
        index = race_roll(randomGenerator); //cout<<"index chosen: "<<index<<endl;
        a_name = ability_list[index]; //cout<<"chosen ability: "<<a_name<<endl;
        a_power = ability_power[index]; //cout<<"ability power: "<<a_power<<endl;
        ability_list.erase(ability_list.begin()+index);
        ability_power.erase(ability_power.begin()+index);
        deck[count].give_badge(a_name, a_power);
        count++;
        p_size--;
        r_size--;
    }while(r_size >= 0 && count < deck.size());
}
void culture_set::show_top(int number) {
//    cout<<"deck size is now:"<<deck.size()<<" and visible is :"<<visible.size()<<endl;

    if(visible.size() < number)
    {
        int remain = number - visible.size();// cout<<"remain is: "<<remain<<endl;
        for (int i = 0; i < remain; ++i) {
//            cout<<i<<": ";
//            deck.back().print_culture();
            culture temp = deck.back();
            visible.push_back(temp);
            deck.pop_back();
        }
        for (int i = 0; i < number; ++i) {
            cout<<i<<": ";
            visible[i].print_culture();
        }
    }
    else
    {
//        cout<<"no need to draw more"<<endl;
        for (int i = 0; i < number; ++i) {
            cout<<i<<": ";
            visible[i].print_culture();
        }
    }
    cout.flush();
}

culture culture_set::pick_race()
{

    cout<<"Please choose an option from below:"<<endl;
    show_top(6);
    cout.flush();
    int choice = 0;
    do
    {
        cin>>choice;
        if(choice >= 0 || choice <6)
            cout<<"You chose "<<choice<<endl;

        else
            cout<<"invalid choice, please choose again."<<endl;
    }while(choice<0||choice>5);
    visible[choice].print_culture();
    culture temp = visible[choice];
    visible.erase( visible.begin()+choice );
    return temp;
}