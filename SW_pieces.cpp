/*
 * Jimmy Le - 26546986
 * COMP 345 WINTER 2018 NORA H.
 * A1
 */
#include <iostream>
#include <utility>
#include <memory>

using namespace std;
#include "SW_pieces.h"

/*
 * Beginning of wallet class
 */
wallet::coin::coin()
{
    coin_value = 0;
}
wallet::coin::coin(int value)
{
    if(value == 1 || value == 3 || value == 5 || value == 10)
    {
        coin_value = value;
    } else {
        cout <<"Invalid value"<<endl;
    }
}
wallet::coin::~coin() {};

wallet::wallet(const int SIZE)
{
    for(int i = 0; i < SIZE; ++i)
    {
        coin* temp = new coin(1);
        coin_wallet.push_back(temp);
        wallet_total++;
    }
}

wallet::~wallet()
{
    coin_wallet.clear();
}
void wallet::print_wallet()
{
    cout<<"This wallet contains:"<<endl;
    int one = 0;
    int three = 0;
    int five = 0;
    int ten = 0;
    for(auto iter = coin_wallet.begin() ; iter!= coin_wallet.end(); ++iter)
    {
        switch((*iter)->get_coin())
        {
            case 1 :
                one++;
                break;
            case 3:
                three++;
                break;
            case 5:
                five++;
                break;
            case 10:
                ten++;
                break;
            default:
                cout<<"something went real wrong."<<endl;
                break;
        }
    }
    cout<<"Number of 1's: "<<one<<endl;
    cout<<"Number of 3's: "<<three<<endl;
    cout<<"Number of 5's: "<<five<<endl;
    cout<<"Number of 10's: "<<ten<<endl;
    cout<<"Total value is: "<<one*1 + three*3 + five*5 + ten*10<<endl;
}


void wallet::add_coin(const int amount)
{
    coin* temp = new coin(amount);
    coin_wallet.push_back(temp);
    wallet_total += amount;
}


void wallet::rem_coin(const int amount)
{
    int index = find(amount);
    if( index >= 0) {
        if(index != coin_wallet.size())
        {
            std::swap(*coin_wallet[index], *coin_wallet.back());
            coin_wallet.back()= nullptr;
            coin_wallet.pop_back();
        }
        else
        {
            coin_wallet.pop_back();
        }
        wallet_total-=amount;
//        cout<<"Removed: "<<index<<" succesfully."<<endl;
    }
    else
        cout<<"Can't remove this coin"<<endl;
}

int wallet::find(const int amount)
{
//    cout<<"The size of the wallet is: "<<coin_wallet.size()<<endl;
    for(auto iter = coin_wallet.begin(); iter != coin_wallet.end(); ++iter )
    {
//        cout<<(*iter)->get_coin()<<endl;
        if( (*iter)->get_coin() == amount)
        {
//            cout<<"Here's the value: "<<iter-coin_wallet.begin()<<endl;
            return iter - coin_wallet.begin();
        }
    }
    return -1;
}


inline int wallet::coin::get_coin()
{
    return coin_value;
}

int wallet::get_wallet_total()
{
    return wallet_total;
}
/*
 * End of Wallet class
 */

/*
 * Board Bits
 */

bool terrain_token::is_mountain()
{
    return mountain;
}

race_token::race_token()
{
    name_of_race = "toy token";
    cout<<"default token created"<<endl;
}
race_token::race_token(string name, bool status)
{
    name_of_race = name;
}

race_token::race_token( race_token& original)
{
    name_of_race = original.name_of_race;
    active = original.active;
}

race_token::~race_token()=default;

void race_token::flip_token()
{
    active = !active;
}
bool race_token::is_active()
{
   return active;
}
std::string race_token::get_name()
{
    return name_of_race;
}

void race_token::foo()
{

}

terrain_token::terrain_token()
{
    terrain = "rain puddle";
    mountain = false;
    cout<<"default terrain created"<<endl;
}
terrain_token::terrain_token(std::string tera, bool mount)
{
    terrain = tera;
    mountain = mount;
}
terrain_token::~terrain_token()=default;


std::string terrain_token::getTerrain()
{
    return terrain;
}
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
        race_token* temp = new race_token(name, true);
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

void bits::add_mountain_token()
{
    pile.push_back(new terrain_token("mountain", true));
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

culture::~culture()=default;

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
