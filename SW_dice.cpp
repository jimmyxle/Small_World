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
mt19937 randomGenerator(time(nullptr));
uniform_int_distribution<int> dice_roll(1, 6);

/*
 * default constructors and deconstructors
 */
dice::dice(){}

dice::~dice(){
    history.clear();
}
/*
 * Function generates a number between 1 and 6. If 4,5,6 is rolled; then it is set to 4 and blank face is printed.
 * The value of the roll is pushed into the history vector of the class
 */
void dice::rollDice()
{
    cout<<"Dice rolled!"<<endl;
    int face = dice_roll(randomGenerator);
    if(face>3)
        face = 4;
    if(face==4)
        cout << "===>blank face!" << endl;
    else
        cout<<"===>"<<face<<endl;

    history.push_back(face);
}
/*
 * Prints out the history of rolls as a percentage
 */
void dice::getHistory(){
    vector<int>::iterator iter;
    cout<<endl<<"Here's the history of rolls."<<endl;
    int oneCount=0;
    int twoCount=0;
    int threeCount=0;
    int blankCount=0;
    int total = 0;
    for(iter = history.begin(); iter != history.end(); ++iter)
    {
        switch(*iter)
        {
            case 1:
                ++oneCount;
                ++total;
                break;
            case 2:

                ++twoCount;
                ++total;
                break;
            case 3:
                ++threeCount;
                ++total;
                break;
            default:
                ++blankCount;
                ++total;
                break;
        }
    }
    double onePercentage =  (oneCount*100.0 / total);
    double twoPercentage = (twoCount*100.0 / total);
    double threePercentage = (threeCount*100.0 / total);
    double blankPercentage = (blankCount*100.0 / total);

    cout<<"one's percentage: "<<onePercentage<<"%"<<endl;
    cout<<"twos's percentage: "<<twoPercentage<<"%"<<endl;
    cout<<"three's percentage: "<<threePercentage<<"%"<<endl;
    cout<<"blanks's percentage: "<<blankPercentage<<"%"<<endl;
}