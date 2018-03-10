/*
 * Jimmy Le - 26546986
 * COMP 345 WINTER 2018 NORA H.
 * A1
 */

#ifndef SMALL_WORLD_SW_GRAPH_H
#define SMALL_WORLD_SW_GRAPH_H

#include <vector>
#include <string>
#include "SW_pieces.h"
/*
 * Graph is made as a vector of region nodes. Each region node have a vector of pointers to its neightbours
 */
class List
{
private:
    /*
     * Inner class node called region. Typedef allows me to refer region* as regionPTR if need be
     */
    struct region
    {
        //Parameters
        int ID;
        std::string name;
        std::string controlled;
        std::vector<region*> adjacent;
        bits* tokens_attached;
        //Constructors
        region();
        region(int, std::string);
        ~region();
        //Class functions
        void addAdj(region*);
        void printAdj();
    };
    //Some helper pointers
    region* head;
    region* temp;
    //Holds all the nodes
    std::vector<region>world_nodes;
    //Counter keeps track of the node index
    int counter = 0;
public:
    //Constructors
    List();
    explicit List( std::string);
    ~List();
    //Methods to create the graph
    void add_region( std::string);
    void print_region();
    void add_region_edge(int, int);
    bool traversal();
    //Used by other classes to manipulate data
    void control_region(int, std::string);
    void add_region_tokens(int, int, std::string);
    bool is_region_adjacent(int, int);
    bool is_control_adjacent(int, int);
    int num_regions_controlled(std::string);
    bool check_ownership(int, std::string);
};
#endif //SMALL_WORLD_SW_GRAPH_H
