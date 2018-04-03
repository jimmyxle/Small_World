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
//    cout<<"list created w/ default"<<endl;
    head = nullptr;
    temp = nullptr;
    world_nodes.reserve(50);
}
//List::List(std::string terrain)
//{
//    head = new region(counter, std::move(terrain));
//    temp = nullptr;
//    world_nodes.push_back(*head);
//    counter++;
//}
List::~List()
{
//    cout<<"List delete initiated."<<endl;
    world_nodes.clear();

//    for(auto iter = world_nodes.begin(); iter != world_nodes.end(); ++iter)
//    {
//        *temp = *iter;
//        delete temp;
//    }
//    temp = nullptr;
//    cout<<"List deleted succesfully."<<endl;
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
int List::get_region_strength(int ID)
{
    cout<<"This region has "<<world_nodes[ID].tokens_attached->get_size()<<" attached."<<endl;
    return world_nodes[ID].tokens_attached->get_size();
}
//void List::clean_region(int ID)
//{
//    world_nodes[ID].tokens_attached->clean();
//}

token* List::clear_region(const int ID)
{
    bits* temp = world_nodes[ID].tokens_attached;
    if(temp->get_size() > 0)
    {
        token* token_temp;
        token_temp = world_nodes[ID].tokens_attached->pop_one();
        return token_temp;
    }
    else
    {
        return nullptr;
    }


}
int List::get_number_race_tokens(int ID)
{
    return world_nodes[ID].tokens_attached->number_race_tokens();
}

//Change here
/*
void List::add_region_tokens(int ID, int number_of_tokens,const std::string& race)
{
//    world_nodes[ID].printAdj();
    bits* temp = world_nodes[ID].tokens_attached;

    world_nodes[ID].tokens_attached->add_race_tokens(race, number_of_tokens);
}
 */

void List::add_region_token(int ID,  token * token1)
{
    bits* temp = world_nodes[ID].tokens_attached;
//    for(int i = 0; i<number_of_tokens; ++i)
//    {
        temp->add_race_token(token1);
//    }

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
//        cout << "graph is connected!" << endl;
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
    controlled = "default";
//    std::vector<region> adjacent;
    adjacent.reserve(3);
    tokens_attached = new bits();
    edge = false;

}
List::region::region(int i, string n)
{
    ID = i;
    name =n;
//    vector<region> adjacent;
    adjacent.reserve(3);
    controlled = "default";
    tokens_attached = new bits();
    edge = false;
    if(n == "mountain")
        tokens_attached->add_mountain_token();
//    cout<<"\tregion "<<ID<<" created"<<endl;
}

List::region::~region()
{
    delete tokens_attached;
    adjacent.clear();
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
    int count = 0;
    for(auto iter = world_nodes.begin(); iter != world_nodes.end(); ++iter)
    {
        if((*iter).controlled == str)
            count++;
    }
//    cout<<"the count is "<<count<<endl;
    return count;
}
//used for player class
bool List::check_ownership(int target, std::string str)
{
    return (world_nodes[target].controlled == (str));
}
std::string List::get_owner(int ID)
{
    return world_nodes[ID].controlled;
}
void List::print_tokens()
{
    for(auto iter = world_nodes.begin(); iter!=world_nodes.end(); ++iter)
    {
        if(iter->tokens_attached->get_size() > 0)
        {
            cout<<iter->ID<<" ";
            iter->tokens_attached->print_pile();
        }
    }
}

void List::regions_in_decline(const std::string& player_name)
{
    for(auto iter = world_nodes.begin(); iter!= world_nodes.end(); ++iter)
    {
        if((*iter).controlled == player_name)
        {
            (*iter).tokens_attached->token_decline();
        }
    }
}
int List::check_region_is_active(int ID)
{
    return world_nodes[ID].tokens_attached->get_active();
}

tokens_info* List::abandon_region(int region_ID, tokens_info& remainder)
{
//    tokens_info* remainder = new tokens_info();

    bits* tokens_attached = world_nodes[region_ID].tokens_attached;
    token* temp1 = nullptr;
    do
    {
        temp1 = tokens_attached->token_withdraw(0);
        if(temp1 != nullptr)
            (&remainder)->returned_tokens.push_back(temp1);
    }while(temp1 != nullptr);

    world_nodes[region_ID].controlled = "default";
    cout<<"Number of tokens attached: "<<tokens_attached->get_size()<<endl;

    (&remainder)->number_of_tokens = (&remainder)->returned_tokens.size();
    if((&remainder)->number_of_tokens > 0)
        (&remainder)->exists = true;

    return (&remainder);
}

tokens_info* List::region_in_withdraw(const std::string& player_name)
{
    tokens_info* remainder = new tokens_info();
    for(auto iter = world_nodes.begin(); iter != world_nodes.end(); ++iter)
    {
        if(iter->controlled == player_name)
        {
            token* temp1 = nullptr;
            do
            {
                 temp1 =  iter->tokens_attached->token_withdraw(1);
                if(temp1 != nullptr)
                    remainder->returned_tokens.push_back(temp1);

            }while(temp1 != nullptr);
        }
    }
    remainder->prev_owner = player_name;
    remainder->number_of_tokens = remainder->returned_tokens.size();
    if(remainder->number_of_tokens > 0)
        remainder->exists = true;
//    cout<<"tokens "<<remainder->number_of_tokens<<endl;
    return remainder;
}
vector<int> List::get_region_array(const std::string& player_name)
{
    vector<int> region_list;

    for(auto iter = world_nodes.begin(); iter != world_nodes.end(); ++iter)
    {
        if(iter-> controlled == player_name)
        {
            region_list.push_back(iter->ID);
        }
    }
    return region_list;
}
void List::get_region_info(int region_ID)
{
    world_nodes[region_ID].display();
}

void List::region::display()
{
    cout<<"[ "<<ID<<" ]\t"<<"\'"<<name<<"\' : num_tokens: "<<tokens_attached->get_size()<<endl;
}

void List::region::set_edge()
{
    edge = true;
}
void List::declare_all_edges(int number_players)
{
    switch(number_players)
    {
        case 2:
            world_nodes[0].set_edge();
            world_nodes[1].set_edge();
            world_nodes[2].set_edge();
            world_nodes[3].set_edge();
            world_nodes[4].set_edge();
            world_nodes[5].set_edge();
            world_nodes[10].set_edge();
            world_nodes[11].set_edge();
            world_nodes[15].set_edge();
            world_nodes[16].set_edge();
            world_nodes[17].set_edge();
            world_nodes[18].set_edge();
            world_nodes[19].set_edge();
            world_nodes[20].set_edge();
            world_nodes[22].set_edge();
            break;
        case 3:
            world_nodes[0].set_edge();
            world_nodes[2].set_edge();
            world_nodes[3].set_edge();
            world_nodes[4].set_edge();
            world_nodes[5].set_edge();
            world_nodes[6].set_edge();
            world_nodes[7].set_edge();
            world_nodes[12].set_edge();
            world_nodes[17].set_edge();
            world_nodes[18].set_edge();
            world_nodes[24].set_edge();
            world_nodes[25].set_edge();
            world_nodes[26].set_edge();
            world_nodes[27].set_edge();
            world_nodes[28].set_edge();
            world_nodes[29].set_edge();

            break;
        case 4:
            world_nodes[0].set_edge();
            world_nodes[3].set_edge();
            world_nodes[4].set_edge();
            world_nodes[5].set_edge();
            world_nodes[11].set_edge();
            world_nodes[12].set_edge();
            world_nodes[18].set_edge();
            world_nodes[19].set_edge();
            world_nodes[24].set_edge();
            world_nodes[25].set_edge();
            world_nodes[29].set_edge();
            world_nodes[30].set_edge();
            world_nodes[31].set_edge();
            world_nodes[34].set_edge();
            world_nodes[35].set_edge();
            world_nodes[36].set_edge();
            world_nodes[37].set_edge();
            world_nodes[38].set_edge();

            break;
        case 5:
            world_nodes[0].set_edge();
            world_nodes[1].set_edge();
            world_nodes[2].set_edge();
            world_nodes[3].set_edge();
            world_nodes[4].set_edge();
            world_nodes[5].set_edge();
            world_nodes[6].set_edge();
            world_nodes[13].set_edge();
            world_nodes[18].set_edge();
            world_nodes[24].set_edge();
            world_nodes[29].set_edge();
            world_nodes[30].set_edge();
            world_nodes[35].set_edge();
            world_nodes[40].set_edge();
            world_nodes[41].set_edge();
            world_nodes[42].set_edge();
            world_nodes[43].set_edge();
            world_nodes[44].set_edge();
            world_nodes[45].set_edge();
            world_nodes[46].set_edge();
            world_nodes[47].set_edge();

            break;
        default:
            break;
    }
}

bool List::check_adjacency(int region_ID, std::string& player_name)
{
    vector<region*> *regions = &(world_nodes[region_ID].adjacent);
    for(auto iter = regions->begin(); iter != regions->end(); ++iter)
    {
        if((*iter)->controlled == player_name)
            return true;
    }
    return false;
}

double List::get_total_number_regions()
{
    return 0.0+world_nodes.size();
}

int List::ai_get_region_adjacent(int region_ID)
{
    vector<int> adjacent_regions;
    cout<<"ai choosing between regions: "<<endl;
    for(auto iter = world_nodes[region_ID].adjacent.begin();
        iter!=world_nodes[region_ID].adjacent.end(); ++iter)
    {
        cout<< (*iter)->ID<<" ";
        adjacent_regions.push_back( (*iter)->ID);
    }

    srand(time(0));
    int index = rand()%adjacent_regions.size();
    int reg = adjacent_regions[index];
    cout<<"ai chose "<<reg<<endl;
    return adjacent_regions[index];
}