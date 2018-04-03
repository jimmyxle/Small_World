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
    cout<<"Player "<<observed_name<<"\'s \""<<observed_phase<<"\" phase."<<endl;


    double percentage = 100*regions_watched/total_watched;
    cout<<"(=\tPlayer "<<observed_name<<" controls "<<regions_watched<<"/"<<total_watched
        <<"("<<percentage<<"%)";
    string bars = "\n\t\t\tControl: |\t";
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
void stats_observable::notify()
{
    for(auto iter = observer_list.begin(); iter != observer_list.end(); ++iter)
    {
       (*iter)->update(turn_number, percentage, hand, victory_coins);
    }
}
void stats_observable::change_status(int turn , double perc , int tokens, int coin)
{
    turn_number = turn;
    percentage = perc;
    hand = tokens;
    victory_coins = coin;
    notify();
}

undecorated_watcher::undecorated_watcher(Iobservable & subj)
{
    subject = &subj;
}
undecorated_watcher::undecorated_watcher() {}
undecorated_watcher::~undecorated_watcher()
{
    delete subject;
}

void undecorated_watcher::show()
{
    cout<<"Turn number: "<<w_turn_number<<endl;
}
void undecorated_watcher::update(int turn, double perc , int token, int coin )
{
    cout<<"undecorated watcher update"<<endl;
     w_turn_number = turn;
     w_percentage = perc;
     w_hand = token;
     w_victory_coins = coin;
    show();
}

dom_decorator::dom_decorator(Iobserver * observer1)
{
    obs = observer1;
}
void dom_decorator::show()
{
    this->obs->show();
    cout<<"perc: "<<w_percentage<<endl;
}

void dom_decorator::update(int, double perc, int, int)
{
    cout<<"call"<<endl;
    w_percentage = perc;
    show();
}