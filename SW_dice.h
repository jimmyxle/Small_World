/*
 * Jimmy Le - 26546986
 * COMP 345 WINTER 2018 NORA H.
 * A1
 */
#ifndef DICE_DICE_GENERATE_H
#define DICE_DICE_GENERATE_H
#include <vector>
/*
 * DICE CLASS
 *
 * Small class that instantiates a dice.
 * Members:
 * It only has a vector<int> that holds the history of rolls.
 * Functions:
 * Has two functions: one to roll the dice and get the history of rolls.
 */
class dice
{
private:
    std::vector<int> history;
public:
    dice();
    ~dice();
    void rollDice();
    void getHistory();
};

#endif //DICE_DICE_GENERATE_H
