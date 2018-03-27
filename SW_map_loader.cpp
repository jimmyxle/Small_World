/*
 * Jimmy Le - 26546986
 * COMP 345 WINTER 2018 NORA H.
 * A1
 */

#include "SW_map_loader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
using namespace std;
//constructors and destructors
loader::loader()
{
    l1 = new List();
    loader_ID++;
}

loader::~loader()
{
//    cout<<loader_ID<<" loader delete initiated"<<endl;
    region_adj.clear();
    region_adj.clear();
    delete l1;
}

//explode string into a vector
std::vector<std::string> loader::explode(std::string const &s, char delim)
{
    std::vector<std::string> result;
    std::istringstream iss(s);
    for(std::string token; std::getline(iss, token, delim);)
        result.push_back(std::move(token));

    return result;
}

//helper function to initiate .map file
void loader::write_file(std::string str, std::string file)
{
    ofstream myfile(file, ios::app);
    if(myfile.is_open())
    {
        myfile <<str<<'\n';
        myfile.close();
    }
    else cout <<"Unable to open file";
}
//read file line by line and call populate on each line
void loader::read_file(std::string file)
{
    string line;
    ifstream myfile(file);
    if(myfile.is_open())
    {
        while(getline(myfile, line))
            separate(line);

        myfile.close();
    }
    else
    {
        cout <<"unable to open file"<<endl;
        exit(0);
    }
}
//fill region_nods and region adj
void loader::separate(std::string str)
{
    std::vector<std::string>::iterator iter;
    std::vector<std::string> temp;
    temp = explode(str, ' ');
    iter = temp.begin();
    region_nodes.push_back(*iter);
    std::vector<int> rest;
    for(iter = temp.begin()+1; iter!=temp.end(); ++iter){
        rest.push_back( std::stoi(*iter) );
    }
    region_adj.push_back(rest);
}
//populate list w/ nodes from region_nodes
bool loader::populate()
{
    int count = 0;
    std::vector<std::string>::iterator iter;
    for(iter = region_nodes.begin(); iter != region_nodes.end(); ++iter)
    {
        l1->add_region( *iter );
    }

//    cout <<"All the nodes have been created."<<endl;
    for(int i = 0; i < region_adj.size(); ++i)
    {
        for(int j =0;j < region_adj[i].size(); j++) {
            l1->add_region_edge(i, region_adj[i][j]); //HERE
        }
    }
    return l1->traversal();
}

