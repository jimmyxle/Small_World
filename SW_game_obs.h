//
// Created by Pierce on 4/1/2018.
//

#ifndef SMALL_WORLD_SW_GAME_OBS_H
#define SMALL_WORLD_SW_GAME_OBS_H

#include <vector>
#include <string>
#include "SW_pieces.h"
#include <list>
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
    void add(observer*) override;
    void change_status(string, string,int,int);
    void notify() override;
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

    explicit phase_watcher(phase_subject&);
    ~phase_watcher();
    void update(string, string, int,int) override;

    void show() override ;
};

class Iobserver
{
public:
    virtual ~Iobserver();
    virtual void show() = 0;
    virtual void update(string, int,double, int, int) = 0;
};
class Iobservable
{
public:
    virtual ~Iobservable();
    virtual void add(Iobserver*)=0;
    virtual void notify() = 0;
    virtual void change_status(string, int,double,int,int)=0;
};


class stats_observable : public Iobservable
{
protected:
    string name;
    int turn_number;
    double uno_perc;
    int uno_hand;
    int victory_coins;
    list<Iobserver*> observer_list;
public:
    stats_observable();
    ~stats_observable() override;
    void add(Iobserver*) override;
    void remove(Iobserver*);
    void notify() override;
    void change_status(string, int,double, int, int) override;

};

class undecorated_watcher : public Iobserver
{
protected:
    string w_name;
    int w_turn_number;
    double w_uno;
    int w_uno_hand;
    int w_victory_coins;
    Iobservable* subject;

public:
    undecorated_watcher();
    ~undecorated_watcher();

    explicit undecorated_watcher(Iobservable&);
    void update(string, int,double, int, int) override;
    void show() override;
};
class watcher_decorator : public undecorated_watcher
{
public:
    ~watcher_decorator();

    void show() override = 0;

    void update(string,int,double, int,int) override = 0;
};

class dom_decorator : public watcher_decorator
{
protected:
    Iobserver* obs;
public:
    explicit dom_decorator(Iobserver*);
    ~dom_decorator() ;
    void show() override;
    void update(string ,int, double, int,int) override;
};

class hand_decorator : public watcher_decorator
{
protected:
    Iobserver* obs;
public:
    explicit hand_decorator(Iobserver*);
    ~hand_decorator();
    void show() override;
    void update(string,int, double, int, int) override;
};

class coin_decorator : public watcher_decorator
{
protected:
    Iobserver* obs;
public:
    explicit coin_decorator(Iobserver*);
    ~coin_decorator();
    void show() override;
    void update(string, int, double, int,int) override;
};

#endif //SMALL_WORLD_SW_GAME_OBS_H
