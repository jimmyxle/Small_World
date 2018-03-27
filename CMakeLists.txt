cmake_minimum_required(VERSION 3.9)
project(Small_World)

set(CMAKE_CXX_STANDARD 11)

add_executable(Small_World main.cpp SW_dice.cpp SW_dice.h SW_graph.cpp SW_graph.h SW_map_loader.cpp SW_map_loader.h SW_pieces.cpp SW_pieces.h SW_player.cpp SW_player.h SW_game_start.cpp SW_game_start.h)