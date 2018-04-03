//
// Created by Pierce on 4/1/2018.
//

#ifndef SMALL_WORLD_SW_GAME_OBS_H
#define SMALL_WORLD_SW_GAME_OBS_H

#include <vector>
#include <string>
#include "SW_pieces.h"

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
/*
 * part 4
 */

class Iobserver
{
public:
    virtual void show() = 0;
    virtual void update(int, double, int, int) = 0;
};
class Iobservable
{
public:
    virtual void add(Iobserver*)=0;
    //remove
    virtual void notify() = 0;
    virtual void change_status(int, double, int,int)=0;
};

class observer_decorator : public Iobserver
{
public:
    virtual void show() = 0;
    virtual void update(int,double, int, int) = 0;
};

class stats_observable : public Iobservable
{
protected:
    int turn_number;
    double percentage;
    int hand;
    int victory_coins;

    vector<Iobserver*> observer_list;
public:
    stats_observable();
    ~stats_observable();
    void add(Iobserver*);
    void notify();
    void change_status(int, double, int, int);

};

class undecorated_watcher : public Iobserver
{
private:
    int w_turn_number;
    double w_percentage;
    int w_hand;
    int w_victory_coins;

    Iobservable* subject;

public:
    undecorated_watcher();
    ~undecorated_watcher();
    undecorated_watcher(Iobservable&);
    void update(int, double, int, int);
    void show();

};

class dom_decorator : public observer_decorator
{
private:
    Iobserver* obs;
//    int w_turn_number;
    double w_percentage;
//    int w_hand;
//    int w_victory_coins;
public:
    dom_decorator(Iobserver*);
    void show();
    void update(int, double, int,int);
};

#endif //SMALL_WORLD_SW_GAME_OBS_H
