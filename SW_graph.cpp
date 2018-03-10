/*
 * Jimmy Le - 26546986
 * COMP 345 WINTER 2018 NORA H.
 * A1
 */
#include <vector>
#include <iostream>
#include "SW_graph.h"
#include <iterator>
using namespace std;

List::List()
{
    cout<<"list created w/ default"<<endl;
    head = nullptr;
    temp = nullptr;
    world_nodes.reserve(50);
}
List::List(std::string terrain)
{
    head = new region(counter, std::move(terrain));
    temp = nullptr;
    world_nodes.push_back(*head);
    counter++;
}
List::~List()
{
    cout<<"List delete initiated."<<endl;
//    world_nodes.clear();

    for(auto iter = world_nodes.begin(); iter != world_nodes.end(); ++iter)
    {
        *temp = *iter;
        delete temp;
    }

    cout<<"List deleted succesfully."<<endl;
}
//method takes in a string that describe the terrain. Creates region and gives it an ID
void List::add_region( std::string terrain)
{
    temp = new region(counter, std::move(terrain));
    world_nodes.push_back(  *temp );
    counter++;
}
//Adds node pointers to the vector of neighbouring pointers
void List::add_region_edge(int target, int edge)
{
    vector<region>::iterator iter;
    region* tempPtr = nullptr;
    for(iter = world_nodes.begin(); iter != world_nodes.end(); ++iter)
    {
        if(iter->ID == edge)
        {
            tempPtr = &(*iter);
            break;
        }
    }
    for(iter = world_nodes.begin(); iter != world_nodes.end(); ++iter)
    {
        if(iter->ID == target)
        {
            iter->addAdj(tempPtr);
            break;
        }
    }
}

/*
 * Helper functions
 */
//Changes the control of the region
void List::control_region(int ID, std::string str)
{
    if(ID < world_nodes.size() && ID >= 0)
    {
        world_nodes[ID].controlled= std::move(str);
    }
//    world_nodes[ID].printAdj();
}



//HEREE
void List::add_region_tokens(int ID, int number_of_tokens, std::string race)
{
//    world_nodes[ID].printAdj();
    world_nodes[ID].tokens_attached->add_race_tokens(race, number_of_tokens);
}
//Checks if the two regions are adjacent
bool List::is_region_adjacent(int target, int ID_check)
{
    vector<region*>::iterator iter;
    bool local_edge_exists = false;
    for(iter = world_nodes[target].adjacent.begin(); iter != world_nodes[target].adjacent.end();++iter )
    {
        if((*iter)->ID == (ID_check))
        {
            local_edge_exists = true;
        }
    }
    return local_edge_exists;
}
//checks if adjacent nodes are controlled by the same player
bool List::is_control_adjacent(int target,int ID_check) {
    if (is_region_adjacent(target, ID_check)) {
        if (world_nodes[ID_check].controlled == world_nodes[target].controlled)
        {
            cout << "These are controlled by the same player" << endl;
            return true;
        }
        else
            cout<<"not controlled by the same player"<<endl;
    }
    else
        cout<<"these regions are not adjacent"<<endl;
    return false;
}
//helper function to print out world_nodes, list of all nodes in the map.
void List::print_region()
{
    vector<region>::iterator iter;
    cout<<"here's the list of regions within this list!"<<endl;
    for(iter = world_nodes.begin(); iter != world_nodes.end(); ++iter)
    {
        cout<<iter->ID<<": "<<iter->name<<": [ ";
        for (auto &i : (iter->adjacent)) {
            cout<< i->ID<<" ";
        }
        cout<<"]"<<endl;
    }
    cout<<endl<<endl;
}
//helper function that shows if the map is connected
bool List::traversal() {
    //make boolean array and init all to false
    bool checked[world_nodes.size()];
    for (int i = 0; i < world_nodes.size(); ++i)
        checked[i] = false;

    vector<region>::iterator iter;
    for (iter = world_nodes.begin(); iter != world_nodes.end(); ++iter) {
//        if(iter->adjacent.size() == 0)
//            checked[iter->adjacent[inner_iter - (iter->adjacent.begin())]->ID]= false;
        vector<region *>::iterator inner_iter;
        for (inner_iter = iter->adjacent.begin(); inner_iter != iter->adjacent.end(); ++inner_iter) {
            checked[iter->adjacent[inner_iter - (iter->adjacent.begin())]->ID] = true;
        }
    }

    bool is_connected = true;
    for (int i = 0; i < world_nodes.size(); ++i) {
        if (!checked[i]) {
            is_connected = false;
        }
    }
    if (is_connected)
    {
        cout << "graph is connected!" << endl;
        return true;
    }
    else {
        cout << "graph is not connected" << endl;
        return false;
    }

}

/*
 * Region constructors and destructors
 */
List::region::region(){
    ID = 0;
    name = "firelands1";
    std::vector<region> adjacent;
    tokens_attached = new bits();

}
List::region::region(int i, string n)
{
    ID = i;
    name =n;
    vector<region> adjacent;
    tokens_attached = new bits();
//    cout<<tokens_attached->get_size()<<endl;

    if(n == "mountain")
        tokens_attached->add_mountain_token();

}
List::region::~region()
{
    delete tokens_attached;
//    adjacent.clear();
    adjacent.clear();

//    region* temp = nullptr;
//    for(auto iter = adjacent.begin(); iter!=adjacent.end();++iter)
//    {
//        temp  = *iter;
//        delete temp;
//    }

}

/*
 * Region functions
 */
//Add region pointers into the neighboring vector of the region node
void List::region::addAdj(region* r)
{
    adjacent.push_back(r);
}
//print out adjacent nodes of this region
void List::region::printAdj()
{
    cout<<"printing "<<adjacent.size()<<endl;

    for(auto iter = adjacent.begin(); iter != adjacent.end(); ++iter)
        cout<<adjacent[iter-adjacent.begin()]->ID<<endl;
}
//Used for score() method
int List::num_regions_controlled(std::string str)
{
    std::vector<region>::iterator iter;
    int count = 0;
    for(iter = world_nodes.begin(); iter != world_nodes.end(); ++iter)
    {
        if((*iter).controlled == str)
            count++;
    }
    return count;
}
//used for player class
bool List::check_ownership(int target, std::string str)
{
    return (world_nodes[target].controlled == std::move(str));
}



