//
// Created by Pierce on 4/1/2018.
//
#include "SW_game_obs.h"
#include <iostream>
using namespace std;

phase_watcher::phase_watcher()
{
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
void phase_watcher::update(string p_name, string p_phase, int turn, int)
{
//    subject
    observed_name = p_name;
    observed_phase = p_phase;
    observed_turn = turn;
    show();
}

void phase_watcher::show()
{
    cout<<endl;
    cout<<"Player "<<observed_name<<"\'s \""<<observed_phase<<"\" phase."<<endl;
    cout<<"________________________________"<<endl;
}


phase_subject::phase_subject()
{
    player_name = "";
    phase = "";
    turn_number = 0;
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
void phase_subject::change_status(string current_name, string current_phase, int turn)
{
    player_name = current_name;
    phase = current_phase;
    turn_number = turn;
    notify();
}
void phase_subject::notify()
{
    for(auto iter = watcher_list.begin(); iter != watcher_list.end(); ++iter)
    {
        dynamic_cast<phase_watcher*>(*iter)->update(player_name, phase,turn_number,0);
    }
}

objective_watcher::objective_watcher() {}
objective_watcher::objective_watcher(objective_subject & obj_sub)
{
    subject = &obj_sub;
}
objective_watcher::~objective_watcher() {}
void objective_watcher::update(string, string w_name, int w_regions,int w_total)
{
    name_watched = w_name;
    regions_watched = w_regions;
    total_watched = w_total;
    show();
}
void objective_watcher::show()
{
    double percentage = 100*regions_watched/total_watched;
    cout<<"(=\tPlayer "<<name_watched<<" controls "<<regions_watched<<"/"<<total_watched
        <<"("<<percentage<<"%)";
    string bars = "\t\t\tControl: |\t";
    for(int i =0; i < regions_watched; ++i)
    {
        bars += "[]";
    }
    bars += "\t|";
    cout<<bars<<endl;

}

objective_subject::objective_subject()
{
    name = "";
    number_regions_controlled = 0;
    total_number_regions = 0;
}
objective_subject::~objective_subject() {}
void objective_subject::add(observer * obj_watcher)
{
    watcher_list.push_back(obj_watcher);
}
void objective_subject::change_status(string obj_name, int obj_watched, int tot_watched)
{
    name = obj_name;
    number_regions_controlled = obj_watched;
    total_number_regions = tot_watched;
    notify();
}

void objective_subject::notify()
{
    for(auto iter = watcher_list.begin(); iter != watcher_list.end(); ++iter)
    {
        dynamic_cast<objective_watcher*>(*iter)->update("",name, number_regions_controlled, total_number_regions);
    }
}

