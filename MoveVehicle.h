//
// Created by ofir shapira on 29/06/2023.
//

#ifndef OOP5_MOVEVEHICLE_H
#define OOP5_MOVEVEHICLE_H

#include "CellType.h"
#include "Direction.h"


template<CellType cell,Direction dir,int N>
struct Move
{
    static_assert(cell==EMPTY,"Empty cell is not ok!\n");
    static constexpr CellType type = cell;
    static constexpr Direction direction = dir;
    static constexpr int amount = N;
};


//struct get_Left ->
//struct get_right ->
//struct perform move
//struct valid index
/*
template<typename ,int ,int,Direction,int >
struct MoveVehicle
{

};*/

template<typename board,int R ,int C,Direction D,int A>
struct MoveVehicle
{
    static_assert(board::);
};






#endif //OOP5_MOVEVEHICLE_H