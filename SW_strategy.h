//
// Created by Pierce on 4/3/2018.
//

#ifndef SMALL_WORLD_STRATEGY_H
#define SMALL_WORLD_STRATEGY_H
#include <iostream>
using namespace std;

class Istrategy
{
public:
    virtual void execute() const = 0;
};

class aggressive_strategy : public Istrategy
{
public:
    void execute() const;
};

class defensive_strategy : public Istrategy
{
public:
    void execute() const;
};

class moderate_strategy : public Istrategy
{
public:
    void execute() const;
};

class random_strategy : public Istrategy
{
public:
    void execute() const;
};

class behaviour
{
private:
    Istrategy* strategy;
public:
    explicit behaviour(Istrategy* );
    void set_strategy(Istrategy*);
    void execute() const;
};



#endif //SMALL_WORLD_STRATEGY_H
