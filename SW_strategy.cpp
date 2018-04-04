//
// Created by Pierce on 4/3/2018.
//

#include "SW_strategy.h"
int aggressive_strategy::execute(int min, int max) const
{
    cout<<"Aggression"<<endl;
    int aggr = min;
    return aggr;
}
int defensive_strategy::execute(int min, int max) const
{
    cout<<"Defensive"<<endl;
    int def = max;
    return def;
}
int moderate_strategy::execute(int min, int max) const
{
    cout<<"Moderate"<<endl;
    int moderate = (min+max)/2;
    return moderate;
}
int random_strategy::execute(int min, int max) const
{
    cout<<"Random"<<endl;
    srand(time(nullptr));
    int random_num = 0;

    random_num = rand()%(max-min+1)+min;
    return random_num;
}
behaviour::behaviour(Istrategy *strat)
{
    strategy = strat;
}
void behaviour::set_strategy(Istrategy *strat)
{
    strategy = strat;
}
int behaviour::execute(int min, int max) const
{
    strategy->execute(min, max);
}