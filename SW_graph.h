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
#include "SW_tokens_info.h"
#include <ctime>

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
        string name;
        string controlled;
        vector<region*> adjacent;
        bits* tokens_attached;
        bool edge;
        //Constructors
        region();
        region(int, std::string);
//        region(const region &);
        ~region();
        //Class functions
        void addAdj(region*);
        void printAdj();
        void display();
        void set_edge();
        bool is_sea();
        string get_controlled();

    };
    //Some helper pointers
    region* head;
    region* temp;
    //Holds all the nodes
    std::vector<region>world_nodes;
    //Counter keeps track of the node index
    int counter = 0;
public:
    List();
    ~List();
    //Methods to create the graph
    void add_region( std::string);
    void print_region();
    void add_region_edge(int, int);
    bool traversal();
    //Used by other classes to manipulate data


    void control_region(int, std::string);
    int get_region_strength(int);
    int get_number_race_tokens(int);
    token* clear_region( int);
    void add_region_token(int, token*);
    bool is_region_adjacent(int, int);
    bool is_control_adjacent(int, int);
    int num_regions_controlled(std::string);
    bool check_ownership(int, string);
    std::string get_owner(int);
    void print_tokens();
    void regions_in_decline(const std::string&);

    int check_region_is_active(int);
    tokens_info* region_in_withdraw(const std::string&);
    vector<int> get_region_array(const std::string&);
    vector<int> get_region_array(const std::string&, string);

    void get_region_info(int);
    tokens_info * abandon_region(int, tokens_info&);
    void declare_all_edges(int);
    bool check_adjacency(int, std::string&);
    double get_total_number_regions();

    int ai_get_region_adjacent_random(int, string); //get a random region adjacent to target id
};
#endif //SMALL_WORLD_SW_GRAPH_H
