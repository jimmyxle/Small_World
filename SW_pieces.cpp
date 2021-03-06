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

game_turn_token::~game_turn_token()=default;
int game_turn_token::get_turn_number()
{
    return turn_number;
}

bool game_turn_token::next_turn()
{
    if(turn_number < MAX_TURNS)
    {
        turn_number++;
        cout<<endl<<endl<<"====================="<<endl;
        cout<<"Turn advanced to turn: "<<turn_number<<endl;
        cout<<"====================="<<endl;

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
coin::~coin()=default;
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

    ones.reserve((3 * BASE_SIZE));
    threes.reserve(BASE_SIZE);
    fives.reserve(BASE_SIZE);
    tens.reserve(BASE_SIZE);

    initiate();
}
bank::~bank()
{
    for (auto &one : ones) {
        delete one;
    }
    ones.clear();

    for (auto &three : threes) {
        delete three;
    }
    threes.clear();

    for (auto &five : fives) {
        delete five;
    }

    fives.clear();

    for (auto &ten : tens) {
        delete ten;
    }
    tens.clear();

    cout<<"Bank emptied"<<endl;
}

void bank::initiate()
{
    for(int iter = 0; iter < 3*BASE_SIZE; ++iter)
    {
        auto *temp= new coin(1);
        ones.push_back( temp );
    }
    for(int iter = 0; iter < BASE_SIZE; ++iter)
    {
        auto *temp= new coin(3);
        threes.push_back( temp );

        temp = new coin(5);
        fives.push_back( temp );

        temp= new coin(10);
        tens.push_back( temp );
    }

}

coin* bank::give_coins( int value)
{

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
            return nullptr;
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
    for (auto &player_one : player_ones) {
        delete player_one;
    }
    player_ones.clear();

    for (auto &player_three : player_threes) {
        delete player_three;
    }
    player_threes.clear();

    for (auto &player_five : player_fives) {
        delete player_five;
    }

    player_fives.clear();

    for (auto &player_ten : player_tens) {
        delete player_ten;
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
    coin* temp;
    switch(value)
    {
        case 1:
            if(!player_ones.empty())
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
            if(!player_threes.empty())
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
            if(!player_fives.empty())
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
            if(!player_tens.empty())
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
    name = std::move(n);
    mountain = m;
}
token::~token() = default;

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
int token::is_active()
{
}
race_token::race_token() : token(){}
race_token::race_token(string name, bool status, bool mount) : token(std::move(name), mount)
{
    active = status;
}


race_token::~race_token() = default;

bool race_token::is_mountain()
{
    return false;
}
void race_token::flip_token()
{
    active = !active;
}
int race_token::is_active()
{
    if(active)
        return 1;
    else
        return 0;
}



terrain_token::terrain_token()
{
    cout<<"default terrain created"<<endl;
}
terrain_token::terrain_token(std::string tera, bool mount) : token(std::move(tera), mount) {}
terrain_token::~terrain_token()=default;


void terrain_token::flip_token()
{
    cout<<"wrong call "<<endl;
}
int terrain_token::is_active()
{
    return 0;
}

bits::bits()
{
    pile.clear();
}
bits::~bits()
= default;

void bits::add_race_token(token *token1)
{
    pile.push_back( (token1) );
}
token* bits::pop_race_token()
{
    token* temp = (pile.back());
    pile.pop_back();
    return temp;
}
int bits::get_size()
{
    return pile.size();
}

void bits::print_pile()
{
    for (auto &iter : pile) {
        cout<< iter->get_name()<<" ";
    }
    cout<<endl;
}
void bits::add_mountain_token()
{
    pile.push_back(new terrain_token("mountain", true));
}

void bits::clean()
{
    for(auto rev_iter = pile.rbegin(); rev_iter!= pile.rend(); ++rev_iter)
    {
        delete (*rev_iter);
    }

}
token* bits::pop_one()
{
    token* temp = pile.back();
    if(  !((temp)->is_mountain() ))
    {
        pile.pop_back();
        return temp;
    } else{
        return nullptr;
    }
}
int bits::number_race_tokens()
{
    int count = 0;
    for (auto &iter : pile) {
        if(!(iter->is_mountain()))
            count++;
    }
    return count;
}
void bits::token_decline()
{
    int count = 0;
    for(auto iter = pile.rbegin(); iter!= pile.rend(); ++iter)
    {
        (*iter)->flip_token();
        if(!((*iter)->is_mountain()) )
        {
            if(count < 1)
                count++;
            else
                pile.pop_back();
        }
    }
}

int bits::get_active()
{
    if(pile.empty())
        return 0;
    for (auto &iter : pile) {

        if(! (iter->is_mountain()) )
        {
            return iter->is_active();
        }
    }
}
string bits::get_token_race()
{
    return (*pile.end())->get_name();
}


token* bits::token_withdraw( int code )
{
    if(code == 1 ) {
//        int SIZE = pile.size();
        for (auto iter = pile.begin() + 1; iter != pile.end(); ++iter) {
            if (!(*iter)->is_mountain()) {
                if (*iter != nullptr) {
//                    cout << "pop!" << endl;
                    token *temp = *iter;
                    pile.pop_back();
                    return temp;
                }
                else
                    return nullptr;

            }
        }
    }
    else if(code == 0)
    {
        for (auto iter = pile.begin(); iter != pile.end(); ++iter) {
            if (!(*iter)->is_mountain()) {
                if (*iter != nullptr) {
//                    cout << "pop!" << endl;
                    token *temp = *iter;
                    pile.pop_back();
                    return temp;
                }
                else
                    return nullptr;

            }
        }

    }
    else
        cout<<"Something went wrong in token_withdraw()"<<endl;
    return nullptr;
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
    player_banner.banner_name = std::move(race_name);
    player_banner.banner_value = race_power;

    player_badge.badge_name= "";
    player_badge.badge_value = 0;
    culture_power = player_banner.banner_value + player_badge.badge_value;

}

culture::~culture()= default;

void culture::give_badge(std::string name, int power)
{
//    cout<<"Gave "<<name<<" "<<power<<endl;
    player_badge.badge_name= std::move(name);
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

}
culture_set::~culture_set()
{
    visible.clear();
    deck.clear();

}



void culture_set::shuffle()
{
    mt19937 randomGenerator(static_cast<unsigned int>(time(nullptr)));

    string r_name;
    int r_power = 0;
    string a_name;
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
    if(visible.size() < number)
    {
        int remain = number - visible.size();
        for (int i = 0; i < remain; ++i) {
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
        for (int i = 0; i < number; ++i) {
            cout<<i<<": ";
            visible[i].print_culture();
        }
    }
    cout.flush();
}


culture culture_set::ai_pick_race(int ai)
{

    cout<<endl;
    cout<<"-----------------------------------"<<endl;
    cout<<"Please choose an option from below:"<<endl;
    show_top(6);
    cout<<"-----------------------------------"<<endl;

//    cout.flush();
    int choice = 0;
    int SIZE = 6;
    int top[SIZE];
    for(int i = 0; i < SIZE; ++i)
    {
        top[i] = visible[i].get_culture_power();
    }
    if(ai == 1)
    {
        //return max
        int max = top[0];
        int index = 0;
        for(int i = 1; i <SIZE; ++i )
        {
            if(top[i] > max)
            {
                max = top[i];
                index = i;
            }
        }
        choice = index;
    }
    else if(ai == 2)
    {
        //return mod
        choice = 2;
    }
    else
    {
        //return def
        //return max
        int min = top[0];
        int index = 0;
        for(int i = 1; i <SIZE; ++i )
        {
            if(top[i] < min)
            {
                min = top[i];
                index = i;
            }
        }
        choice = index;

    }
    cout<<"Ai chose "<<choice<<endl;

    visible[choice].print_culture();
    cout<<"Would you agree with this? Choose a race (0-5) "<<endl;
    int attempt =0;

    do{
        try
        {
            cin>>attempt;
            if(!cin)
            {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw "Not a number";
            }

        }catch(const char* msg)
        {
            cerr<<"ERROR: "<<msg<<endl;
            cout<<"Enter a new number"<<endl;
        }
        if(attempt >= 0 || attempt <6) {


            cout << "You chose (" << attempt << ")\t";
            choice = attempt;
        }
        else
            cout<<"invalid choice, please choose again."<<endl;
    }while(attempt< 0 || attempt >5);




    culture temp = visible[choice];
    visible.erase( visible.begin()+choice );
    return temp;

}
culture culture_set::pick_race()
{
    cout<<endl;
    cout<<"-----------------------------------"<<endl;
    cout<<"Please choose an option from below:"<<endl;
    show_top(6);
    cout<<"-----------------------------------"<<endl;

//    cout.flush();
    int choice = 0;
    do
    {

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
            cout<<"Enter a new number"<<endl;
        }
        if(choice >= 0 || choice <6)
            cout<<"You chose ("<<choice<<")\t";

        else
            cout<<"invalid choice, please choose again."<<endl;
    }while(choice<0||choice>5);
    visible[choice].print_culture();
    culture temp = visible[choice];
    visible.erase( visible.begin()+choice );
    return temp;
}