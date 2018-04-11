//
// Created by Pierce on 3/29/2018.
//

#include "SW_tokens_info.h"

tokens_info::tokens_info()
{
    number_of_tokens = 0;
    prev_owner = "";
    exists = false;
    returned_tokens.reserve(5);
}

tokens_info::~tokens_info()
{
    for (auto &returned_token : returned_tokens) {
        delete returned_token;
    }
}