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

//        dynamic_cast<phase_watcher*>(*iter)->update(player_name, phase, turn_number,
//                                                    number_regions_controlled, total_number_regions);
    }
}
