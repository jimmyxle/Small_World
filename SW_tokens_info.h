//
// Created by Pierce on 3/29/2018.
//

#ifndef SMALL_WORLD_SW_TOKENS_INFO_H
#define SMALL_WORLD_SW_TOKENS_INFO_H
#include "SW_pieces.h"

struct tokens_info
{
public:
    int number_of_tokens;
    std::string prev_owner;
    bool exists;
    vector<token*> returned_tokens;
    int turn_finish;

    tokens_info();
    ~tokens_info();
};

#endif //SMALL_WORLD_SW_TOKENS_INFO_H
