/*
 * Jimmy Le - 26546986
 * COMP 345 WINTER 2018 NORA H.
 * A1
 */
#include <iostream>
#include <random>
#include <ctime>
#include "SW_dice.h"
#include <iterator>
using namespace std;


/*
 * Seed the random number generator
 */
mt19937 randomGenerator((time(nullptr)));
uniform_int_distribution<int> dice_roll(1, 6);

/*
 * default constructors and deconstructors
 */
dice::dice() = default;

dice::~dice(){
    history.clear();
}
/*
 * Function generates a number between 1 and 6. If 4,5,6 is rolled; then it is set to 4 and blank face is printed.
 * The value of the roll is pushed into the history vector of the class
 */
int dice::rollDice()
{
    cout<<"Dice rolled";
    int face = dice_roll(randomGenerator);
    if(face>3)
        face = 0;
    if(face==0)
        cout << "  ===>blank face!" << endl;
    else
        cout<<"  ===>"<<face<<endl;
    history.push_back(face);
    return face;

}