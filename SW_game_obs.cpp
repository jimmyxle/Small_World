//
// Created by Pierce on 4/1/2018.
//
#include "SW_game_obs.h"
#include <iostream>
using namespace std;

phase_watcher::phase_watcher()
{
    observed_name = "";
    observed_phase = "";


    regions_watched = 0;
    total_watched = 0;


    subject  = nullptr;
}

phase_watcher::~phase_watcher()
{
    delete subject;
}
phase_watcher::phase_watcher(phase_subject & p_status)
{
    subject = &p_status;
}

void phase_watcher::update(string p_name, string p_phase, int regions, int total)
{
    observed_name = p_name;
    observed_phase = p_phase;

    regions_watched = regions;
    total_watched = total;

    show();
}

void phase_watcher::show()
{
    cout<<endl;
    cout<<"\t\tPlayer ["<<observed_name<<"] \""<<observed_phase<<"\" phase."<<endl;


    double percentage = 100*regions_watched/total_watched;
    cout<<"(=\t\t\tPlayer "<<observed_name<<" controls "<<regions_watched<<"/"<<total_watched
        <<"("<<percentage<<"%)";
    string bars = "\n\tControl: |\t";
    for(int i =0; i < regions_watched; ++i)
    {
        bars += "[X]";
    }
    int leftover = total_watched - regions_watched;
    for(int i =0; i < leftover; ++i)
    {
        bars += "[ ]";
    }
    bars += "\t|";
    cout<<bars<<endl;



}


phase_subject::phase_subject()
{
    player_name = "";
    phase = "";


    number_regions_controlled = 0;
    total_number_regions = 0;


}
phase_subject::~phase_subject()
{
    for(auto iter = watcher_list.begin(); iter != watcher_list.end(); ++iter)
        delete *iter;
}
void phase_subject::add(observer * p_watcher)
{
    watcher_list.push_back(p_watcher);
}

void phase_subject::change_status(string p_name, string p_phase,int regions, int total)
{

    player_name = p_name;
    phase = p_phase;
    number_regions_controlled = regions;
    total_number_regions = total;


    notify();
}

void phase_subject::notify()
{
    for(auto iter = watcher_list.begin(); iter != watcher_list.end(); ++iter)
    {
           dynamic_cast<phase_watcher*>(*iter)->update(player_name, phase, number_regions_controlled, total_number_regions);

    }
}
Iobserver::~Iobserver()= default;
Iobservable::~Iobservable() = default;
watcher_decorator::~watcher_decorator() = default;

stats_observable::stats_observable() {}
stats_observable::~stats_observable()
{
    for(auto iter = observer_list.begin(); iter != observer_list.end(); ++iter)
        delete (*iter);
}
void stats_observable::add(Iobserver *obs)
{
    observer_list.push_back(obs);
}
void stats_observable::remove(Iobserver * obs)
{
    observer_list.remove(obs);
}
void stats_observable::notify()
{
    for(auto iter = observer_list.begin(); iter != observer_list.end(); ++iter)
    {
       (*iter)->update(turn_number, uno_perc, dos_perc, uno_hand, dos_hand, victory_coins);
    }
}
void stats_observable::change_status(int turn ,double uno, double dos , int uno_tokens,int dos_tokens, int coin)
{
    turn_number = turn;
    uno_perc = uno;
    dos_perc = dos;

    uno_hand = uno_tokens;
    dos_hand = dos_tokens;

    victory_coins = coin;
    notify();
}

undecorated_watcher::undecorated_watcher(Iobservable & subj)
{
    subject = &subj;
}
undecorated_watcher::undecorated_watcher()
{
    w_turn_number =0;
    w_uno = 0;
    w_dos;
//    w_hand = 0;
    w_uno_hand = 0;
    w_dos_hand = 0;
    w_victory_coins = 5;
}
undecorated_watcher::~undecorated_watcher()
{
    delete subject;
}

void undecorated_watcher::show()
{
    cout<<endl<<"====================="<<endl;
    cout<<"Turn number:\t["<<w_turn_number<<"]"<<endl;
}
void undecorated_watcher::update(int turn,double uno, double dos , int uno_token,int dos_token, int coin )
{
     w_turn_number = turn;

    w_uno = uno;
    w_dos = dos;

    w_uno_hand = uno_token;
    w_dos_hand = dos_token;

     w_victory_coins = coin;
}

dom_decorator::dom_decorator(Iobserver * observer1)
{
    obs = observer1;
}
dom_decorator::~dom_decorator()
{
    delete obs;
}
void dom_decorator::show()
{
    this->obs->show();
    cout<<"uno controlled: "<<w_uno<<"%"<<endl;
    cout<<"dos controlled: "<<w_dos<<"%"<<endl;

}

void dom_decorator::update(int turn, double uno ,double dos, int uno_token,int dos_token, int coin)
{
    this->obs->update(turn,uno,dos,uno_token,dos_token, coin );
    w_uno = uno;
    w_dos = dos;
//    show();
}

coin_decorator::coin_decorator(Iobserver *observer)
{
    obs=observer;
}
coin_decorator::~coin_decorator()
{
    delete obs;
}
void coin_decorator::show()
{
    this->obs->show();
    cout<<"Coin value: "<<w_victory_coins<<endl;
}
void coin_decorator::update(int turn, double uno, double dos, int uno_token,int dos_token, int coin)
{
    this->obs->update(turn, uno, dos, uno_token, dos_token, coin);
    w_victory_coins = coin;
}

hand_decorator::hand_decorator(Iobserver * obs1)
{
    obs = obs1;
}
hand_decorator::~hand_decorator()
{
    delete obs;
}
void hand_decorator::show()
{
    this->obs->show();
    cout<<"Player 1's number of tokens in hand: "<<w_uno_hand<<endl;
    cout<<"Player 2's number of tokens in hand: "<<w_dos_hand<<endl;
}

void hand_decorator::update(int turn, double uno, double dos, int uno_token,int dos_token, int coin)
{
    this->obs->update(turn, uno, dos, uno_token, dos_token, coin);
    w_uno_hand = uno_token;
    w_dos_hand = dos_token;
}