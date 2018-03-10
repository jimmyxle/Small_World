/*
 * Jimmy Le - 26546986
 * COMP 345 WINTER 2018 NORA H.
 * A1
 */
/*
 * map loader class
 *
 * This class store two vectors with information about adjacent nodes.
 * Used to build the game map
 */

#ifndef SMALL_WORLD_SW_MAP_LOADER_H
#define SMALL_WORLD_SW_MAP_LOADER_H


#include <string>
#include <vector>
#include "SW_graph.h"



class loader
{
private:
    std::vector<std::string> region_nodes;
    std::vector<std::vector<int>> region_adj;
public:
    loader();
    ~loader();
    List *l1;
    std::vector<std::string> explode(std::string const &, char);
    void write_file(std::string, std::string);
    void read_file(std::string);
    void separate(std::string);
    bool populate();
};
//extern loader* loader1;


#endif //SMALL_WORLD_SW_MAP_LOADER_H
