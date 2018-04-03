//
// Created by Pierce on 4/3/2018.
//

#include "SW_strategy.h"
void aggressive_strategy::execute() const
{
    cout<<"Aggression"<<endl;
}
void defensive_strategy::execute() const
{
    cout<<"Defensive"<<endl;
}
void moderate_strategy::execute() const
{
    cout<<"Moderate"<<endl;
}
void random_strategy::execute() const
{
    cout<<"Random"<<endl;
}
behaviour::behaviour(Istrategy *strat)
{
    strategy = strat;
}
void behaviour::set_strategy(Istrategy *strat)
{
    strategy = strat;
}
void behaviour::execute() const
{
    strategy->execute();
}