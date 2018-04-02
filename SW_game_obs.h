//
// Created by Pierce on 4/1/2018.
//

#ifndef SMALL_WORLD_SW_GAME_OBS_H
#define SMALL_WORLD_SW_GAME_OBS_H

#include <vector>
#include <string>
using namespace std;

class observer
{
private:
public:
    virtual void update(string, string, int, int) = 0;
};

class display
{
private:
public:
    virtual void show() =0;
};

class observable
{
private:
public:
    virtual void add(observer*) = 0;
//    virtual void rem(observer*) = 0;
    virtual void notify() = 0;
};


class phase_subject : public observable
{
private:
    string player_name;
    string phase;
    int turn_number;
    vector<observer*> watcher_list;

public:
    phase_subject();
    ~phase_subject();
    void add(observer*);
//    void rem(observer*);
    void change_status(string, string, int);
    void notify();
};


class objective_subject : public observable
{
private:
    string name;
    int number_regions_controlled;
    double total_number_regions;

    vector<observer*>watcher_list;
public:
    objective_subject();
    ~objective_subject();
    void add(observer*);
    void change_status(string, int, int);
    void notify();
};

class phase_watcher : public observer, public display
{
private:
    string observed_name;
    string observed_phase;
    int observed_turn;

    phase_subject* subject;
public:
    phase_watcher();
    phase_watcher(phase_subject&);
    ~phase_watcher();
    void update(string, string, int, int);
    void show();
};

class objective_watcher : public observer, public display
{
private:
    string name_watched;
    int regions_watched;
    int total_watched;

    objective_subject* subject;
public:
    objective_watcher();
    objective_watcher(objective_subject&);
    ~objective_watcher();
    void update(string,string, int, int);
    void show();
};

class observer_decorator : public observer
{
public:
    virtual void display() = 0;
};

#endif //SMALL_WORLD_SW_GAME_OBS_H
