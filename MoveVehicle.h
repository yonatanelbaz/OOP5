//
// Created by ofir shapira on 29/06/2023.
//

#ifndef OOP5_MOVEVEHICLE_H
#define OOP5_MOVEVEHICLE_H

#include "CellType.h"
#include "Direction.h"
#include "BoardCell.h"
#include "List.h"
#include "GameBoard.h"
#include "Utilities.h"
#include "BoardUtils.h"
#include "TransposeList.h"
template<CellType cell,Direction dir,int N>
struct Move
{
    static_assert(cell!=EMPTY,"Empty cell is not ok!\n");
    static constexpr CellType type = cell;
    static constexpr Direction direction = dir;
    static constexpr int amount = N;
};

template <typename Board,int R,int C,Direction D>
struct ValidIndexes
{
private:
    static_assert(R >=0 && R < Board::width, "Invalid Index");
    static_assert(C >=0 && C < Board::length, "Invalid Index");

    typedef GetAtIndex<R,typename Board::board> row;
    typedef GetAtIndex<C, row> cell;
    static_assert(cell::type == EMPTY, "Invalid Index");
    static_assert(cell::direction == LEFT && D != RIGHT && D != LEFT, "Invalid Direction");
    static_assert(cell::direction == RIGHT && D != RIGHT && D != LEFT, "Invalid Direction");
    static_assert(cell::direction == UP && D != UP && D != DOWN, "Invalid Direction");
    static_assert(cell::direction == DOWN && D != UP && D != DOWN, "Invalid Direction");
};

template <typename Board, int R,int C, typename Cell>
struct GetLeft
{
private:
    typedef typename GetAtIndex<R,typename Board::board>::value row;

    static constexpr int next = GetLeft<Board, R, C-1,Cell>::left;
    typedef typename GetAtIndex<C, row>::value cell;
    static constexpr int checkNext = ConditionalInteger<next != NOT_FOUND,next,C>::value;
public:
    static constexpr int left =  ConditionalInteger<IsSame<Cell,cell>::value, checkNext, NOT_FOUND>::value;

};


template <typename Board,int R, typename Cell>
struct GetLeft<Board,R,-1,Cell>
{
public:
    static constexpr int left =NOT_FOUND ;
};

template <typename Board,int width, int R,int C, typename Cell>
struct GetRight
{
private:
    typedef typename GetAtIndex<R,typename Board::board>::value row;

    static constexpr int next = GetRight<Board,width, R, C+1,Cell>::right;
    typedef typename GetAtIndex<C, row>::value cell;
    static constexpr int checkNext = ConditionalInteger<next != NOT_FOUND,next,C>::value;
public:
    static constexpr int right =  ConditionalInteger<IsSame<Cell,cell>::value, checkNext, NOT_FOUND>::value;

};


template <typename Board, int R,int C, typename Cell>
struct GetRight<Board,C,R,C,Cell>
{
public:
    static constexpr int right =  NOT_FOUND;

};

//struct get_Left ->
//struct get_right ->
//struct perform move
//struct valid index
//struct get cell


/*
template<typename ,int ,int,Direction,int > - Done
struct MoveVehicle
{
};*/


template <typename Board,int R,int C,Direction D>
struct PerformMove
{
private:
    typedef typename GetCellAtIndex<Board,R,C>::cell givenCell;

    static const int sideCol = ConditionalInteger<D==LEFT, GetRight<Board,Board::width,R,C,givenCell>::right, GetLeft<Board,R,C,givenCell>::left>::value;
    typedef typename GetCellAtIndex<Board,R,sideCol>::cell sourceCell;


    static constexpr int carLength = sourceCell::length;
    static constexpr int newCol = ConditionalInteger<D == RIGHT, sideCol +carLength,sideCol-carLength>::value;
    typedef typename GetCellAtIndex<Board,R,newCol>::cell destCell;
    static_assert(destCell::type == EMPTY,"The spot is taken bro\n");
    typedef typename SetCellAtIndex<Board,R,sideCol,BoardCell<EMPTY,UP,0>>::board eraseBoard;
public:
    typedef typename SetCellAtIndex<eraseBoard,R,newCol,sourceCell>::board board;
    static constexpr int nextCol = ConditionalInteger<D==RIGHT,C+1,sideCol-1>::value;
};


template <typename Board,int R,int C,Direction D,int A>
struct PerformMoves
{
private:
    typedef typename PerformMove<Board,R,C,D>::board boardAfterMove;
    static constexpr int nextColNew= PerformMove<Board,R,C,D>::nextCol;
public:
    typedef typename PerformMoves<boardAfterMove,R,nextColNew,D,A-1>::board board;
};

template <typename Board,int R,int C,Direction D>
struct PerformMoves<Board,R,C,D,0>
{
    typedef Board board;
};



template<typename Board,int R ,int C,Direction D,int A>
struct MoveVehicle{};

template<typename Board ,int R ,int C, int A>
struct MoveVehicle<Board, R , C, LEFT,A>
{
    typedef ValidIndexes<Board,R,C,LEFT> check;
public:
    typedef typename PerformMoves<Board,R,C,LEFT,A>::board board;

};
template<typename Board ,int R ,int C, int A>
struct MoveVehicle<Board, R , C,RIGHT,A>
{
    typedef ValidIndexes<Board,R,C,RIGHT> check;
public:
    typedef typename PerformMoves<Board,R,C,RIGHT,A>::board board;

};
template<typename Board ,int R ,int C, int A>
struct MoveVehicle<Board, R , C,UP,A>
{
private:

    typedef typename Transpose<typename Board::board>::matrix boardAsList;
    typedef typename GetAtIndex<C,boardAsList>::value row;
    typedef typename GetCellAtIndex<Board,R,C>::cell cellUp;
    typedef  BoardCell<cellUp::type,LEFT,cellUp::length> cellLeft;

    static constexpr int dSide = GetLeft<GameBoard<boardAsList>,C,R,cellUp>::left;
    static constexpr int uSide = GetRight<GameBoard<boardAsList>,Board::length,C,R,cellUp>::right;



    static constexpr int dSideAfter = dSide -A;
    static constexpr int uSideAfter = uSide -A;


    typedef typename MakeSwitch<GameBoard<boardAsList>,C,dSide,uSide,cellLeft>::board boardAfterSwitchPre;


    typedef typename MoveVehicle<boardAfterSwitchPre, C,R, LEFT,A>::board boardAfterMove;

    typedef typename MakeSwitch<boardAfterMove,C,dSideAfter,uSideAfter,cellUp>::board boardAfterSwitchPost;


    typedef typename Transpose<typename boardAfterSwitchPost::board>::matrix finalTranspose;

public:
    typedef GameBoard<finalTranspose> board;

};



template<typename Board ,int R ,int C, int A>
struct MoveVehicle<Board, R , C,DOWN,A>
{
private:

    typedef typename Transpose<typename Board::board>::matrix boardAsList;
    typedef typename GetAtIndex<C,boardAsList>::value row;
    typedef typename GetCellAtIndex<Board,R,C>::cell cellDown;
    typedef BoardCell<cellDown::type,RIGHT,cellDown::length> cellRight;

    static constexpr int dSide = GetLeft<GameBoard<boardAsList>,C,R,cellDown>::left;
    static constexpr int uSide = GetRight<GameBoard<boardAsList>,Board::length,C,R,cellDown>::right;
    static constexpr int dSideAfter = dSide + A;
    static constexpr int USideAfter = uSide + A;


    typedef typename MakeSwitch<GameBoard<boardAsList>,C,dSide,uSide,cellRight>::board boardAfterSwitchPre;

    typedef typename MoveVehicle<boardAfterSwitchPre,C,R,RIGHT,A>::board boardAfterMove;

    typedef typename MakeSwitch<boardAfterMove,C,dSideAfter,USideAfter,cellDown>::board boardAfterSwitchPost;


    typedef typename Transpose<typename boardAfterSwitchPost::board>::matrix finalTranspose;

public:
    typedef GameBoard<finalTranspose> board;

};




#endif //OOP5_MOVEVEHICLE_H
