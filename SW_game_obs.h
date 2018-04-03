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

public:
    virtual void update(string, string, int,int) = 0;
    virtual void show() =0;
};


class observable
{
public:
    virtual void add(observer*) = 0;
//    virtual void rem(observer*) = 0;
    virtual void notify() = 0;
};


class phase_subject : public observable
{
protected:
    string player_name;
    string phase;
    int number_regions_controlled;
    int total_number_regions;

    vector<observer*> watcher_list;

public:
    phase_subject();
    ~phase_subject();
    void add(observer*);
//    void rem(observer*);
    void change_status(string, string,int,int);
    void notify();
};


class phase_watcher : public observer
{
protected:
    string observed_name;
    string observed_phase;
    int regions_watched;
    int total_watched;

    phase_subject* subject;
public:
    phase_watcher();
    phase_watcher(phase_subject&);
    ~phase_watcher();
//    void update(string, string, int, int, int, int, int);
    void update(string, string, int,int);

    void show() override ;
};


class observer_decorator : public observer
{
public:
    virtual void show() = 0;
    void update(string, string, int, int);
};

class stats_subject : public observable
{
public:

};
class stats_watcher : public observer{
public:

};

#endif //SMALL_WORLD_SW_GAME_OBS_H
