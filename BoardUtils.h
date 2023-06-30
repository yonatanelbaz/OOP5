//
// Created by ofir shapira on 29/06/2023.
//

#ifndef OOP5_BOARDUTILS_H
#define OOP5_BOARDUTILS_H

#include "Utilities.h"
#include "CellType.h"

constexpr int NOT_FOUND = -1;
template<typename X, typename Y>
struct IsSame
{
    static constexpr bool value = false;
};

template<typename X>
struct IsSame<X,X>
{
    static constexpr bool value = true;
};

template <int R,int C>
struct BoardIndex
{
    static constexpr int row =R;
    static constexpr int col =C;
};

template <typename Board,int R,int C>
struct GetCellAtIndex
{
private:
    typedef GetAtIndex<R,typename Board::board> row;
public:
    typedef GetAtIndex<C, row> cell;
};

template <typename Board,int R,int C,typename V>
struct SetCellAtIndex
{
private:
    typedef GetAtIndex<R,typename Board::board> oldRow;
    typedef SetAtIndex<C,V, oldRow> newCol;
public:
    typedef SetAtIndex<R,newCol, typename Board::board> board;

};
template<typename Board,int R,int l,int r,typename V>
struct MakeSwitch
{
private:
    typedef typename SetCellAtIndex<Board,R,l, V>::board afterSet;
public:
    typedef typename MakeSwitch<afterSet,R,l+1,r,V>::board board;
};

template<typename Board,int R,int x,typename V>
struct MakeSwitch<Board,R,x,x,V>
{
public:
    typedef typename SetCellAtIndex<Board,R,x,V>::board board;
};

template<typename L,CellType X>
struct FindCarInList
{
private:
    static constexpr bool cond =  L::head::type ==X;
    static constexpr int nextIndex = FindCarInList<typename L::next,X>::index;
    static constexpr int nextRes = ConditionalInteger<nextIndex == NOT_FOUND,NOT_FOUND,1+nextIndex>::value;

public:
    static constexpr int index = ConditionalInteger<cond,0,nextRes>::value;

};

template<CellType X>
struct FindCarInList<List<>,X>
{
private:
public:
    static constexpr int index = NOT_FOUND;
};

template<typename L,CellType X>
struct FindCarAux
{
private:
    static constexpr int checkRow = FindCarInList<typename L::head,X>::row;
    static constexpr int checkCol = FindCarInList<typename L::head,X>::col;
    static constexpr int nextRow = FindCarInList<typename L::next,X>::row;
    static constexpr int nextRowRes = ConditionalInteger<nextRow == NOT_FOUND,nextRow,nextRowRes+1>::value;

    static constexpr int nextCol = FindCarInList<typename L::next,X>::col;
    static constexpr int nextColRes = ConditionalInteger<nextCol == NOT_FOUND,nextCol,nextColRes+1>::value;

public:
    static constexpr int row = ConditionalInteger<checkRow == NOT_FOUND, checkRow,nextRowRes>::value ;
    static constexpr int col = ConditionalInteger<checkRow == NOT_FOUND, checkCol,nextColRes>::value ;
};

template<CellType X>
struct FindCarAux<List<>,X>
{
    static constexpr int row = -1;
    static constexpr int col = -1 ;
};

template<typename Board,CellType X>
struct FindCar
{
    static constexpr int row = FindCarAux<typename Board::board,X>::row;
    static constexpr int col =  FindCarAux<typename Board::board,X>::col;
public:
    typedef BoardIndex<row,col> res;
};

#endif //OOP5_BOARDUTILS_H
