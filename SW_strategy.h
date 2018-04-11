//
// Created by Pierce on 4/3/2018.
//

#ifndef SMALL_WORLD_STRATEGY_H
#define SMALL_WORLD_STRATEGY_H
#include <iostream>
#include <ctime>
using namespace std;

class Istrategy
{
public:
    virtual int execute( int, int ) const = 0;
};

class aggressive_strategy : public Istrategy
{
public:
    int execute(int, int) const override;
};

class defensive_strategy : public Istrategy
{
public:
    int execute(int, int) const override;
};

class moderate_strategy : public Istrategy
{
public:
    int execute(int, int) const override;
};

class random_strategy : public Istrategy
{
public:
    int execute(int, int) const override;
};

class behaviour
{
private:
    Istrategy* strategy;
public:
    explicit behaviour(Istrategy* );
    void set_strategy(Istrategy*);
    int execute(int, int) const;
};



#endif //SMALL_WORLD_STRATEGY_H
