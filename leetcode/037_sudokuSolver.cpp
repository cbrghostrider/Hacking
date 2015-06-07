// -------------------------------------------------------------------------------------
//         Author: Sourabh S Joshi (cbrghostrider); Copyright - All rights reserved.
//                       For email, run on linux (perl v5.8.5):
//   perl -e 'print pack "H*","736f75726162682e732e6a6f73686940676d61696c2e636f6d0a"'
// -------------------------------------------------------------------------------------
//posting full solution, so that I can use this to solve puzzles
//note that some refactoring can clean up the code a little (some repeated logic)
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <utility>

using std::pair;
using std::vector;

class Sudoku {
private:
    typedef pair<int, int> Coord;
    vector<char> SYMBOLS = {'1', '2', '3', '4', '5', '6', '7', '8', '9'}; 
    const int boardSize = 9;
    const int boxSize = 3;
    vector<vector<char> >& board;
private:
    bool validStart_() const;
    vector<char> evalCandidatesForCell_(int x, int y);
    bool visitCells_();
public:
    Sudoku(vector<vector<char> >& input) : board(input) {}
    void solveSudoku();
};

vector<char> Sudoku::evalCandidatesForCell_(int r, int c) 
{
    vector<char> retval;
    if (board[r][c] != '.') {
        assert(0);
        return retval;
    }

    vector<char> used;
    //get numbers already used in row
    for (int cc=0; cc<boardSize; cc++) {
        char check = board[r][cc];
        if (check != '.') {
            used.push_back(check);
        }
    }
    //get numbers already used in column
    for (int rr=0; rr<boardSize; rr++) {
        char check = board[rr][c];
        if (check != '.') {
            used.push_back(check);
        }
    }
    //get numbers already used in box
    int rrinit = (r/boxSize) * boxSize;
    int ccinit = (c/boxSize) * boxSize;
    for (int rr = rrinit; rr < rrinit+boxSize; rr++) {
        for (int cc = ccinit; cc < ccinit+boxSize; cc++) {
            char check = board[rr][cc];
            if (check != '.') {
                used.push_back(check);
            }
        }
    }
    std::sort(used.begin(), used.end());
    std::set_difference(SYMBOLS.begin(), SYMBOLS.end(), used.begin(), used.end(), back_inserter(retval));
    return retval;
}

bool Sudoku::validStart_() const 
{
    //check row consistency
    for (int rr=0; rr<boardSize; rr++) {
        vector<char> row;
        for (int cc=0; cc<boardSize; cc++) {
            if (board[rr][cc] != '.') row.push_back(board[rr][cc]);
        }
        std::sort(row.begin(), row.end());
        int sizeS = row.size();
        auto it = std::unique(row.begin(), row.end());
        row.erase(it, row.end());
        int sizeU = row.size();
        if (sizeS != sizeU) return false;
    }
    //check col consistency
    for (int cc=0; cc<boardSize; cc++) {
        vector<char> col;
        for (int rr=0; rr<boardSize; rr++) {
            if (board[rr][cc] != '.') col.push_back(board[rr][cc]);
        }
        std::sort(col.begin(), col.end());
        int sizeS = col.size();
        auto it = std::unique(col.begin(), col.end());
        col.erase(it, col.end());
        int sizeU = col.size();
        if (sizeS != sizeU) return false;
    }
    //check box consistency
    for (int rrinit=0; rrinit<boardSize; rrinit += boxSize) {
        for (int ccinit=0; ccinit < boardSize; ccinit += boxSize) {
            vector<char> box;
            for (int rr=rrinit; rr < rrinit+boxSize; rr++) {
                for (int cc=ccinit; cc<ccinit+boxSize; cc++) {
                    if (board[rr][cc] != '.') box.push_back(board[rr][cc]);
                }
            }
            std::sort(box.begin(), box.end());
            int sizeS = box.size();
            auto it = std::unique(box.begin(), box.end());
            box.erase(it, box.end());
            int sizeU = box.size();
            if (sizeS != sizeU) return false;
        }
    }

    //everything checked out!
    return true;
}

//return value indicates whether Sudoku is solvable w/ current choices
bool Sudoku::visitCells_()
{
    typedef pair<Coord, vector<char> > Result;
    Coord chosenCrd;
    vector<char> letterChoices;

    bool flag = false;

    for (int rr = 0; !flag && rr < boardSize; rr++) {
        for (int cc = 0; !flag && cc < boardSize; cc++) {
            if (board[rr][cc] != '.') continue; 
            chosenCrd = std::make_pair(rr, cc);
            letterChoices = evalCandidatesForCell_(rr, cc);
            if (letterChoices.empty()) return false;
            flag = true;
        }
    }

    //finished solving
    if (flag == false) return true;

    for (int i=0; i<letterChoices.size(); i++) {
        board[chosenCrd.first][chosenCrd.second] = letterChoices[i];
        bool trial = visitCells_();
        if (trial == true) return true;
    }

    //tried all letters for 0th index, none fit, so sudoku cannot be solved w/ current choices
    //i.e. at least one cell cannot be filled... backtrack!
    board[chosenCrd.first][chosenCrd.second] = '.';
    return false; 
}

void Sudoku::solveSudoku() 
{
    if (!validStart_()) {
        std::cout << "Sudoku start configuration is invalid!" << std::endl;
        return;
    }
    bool solvable = visitCells_();
    if (!solvable) {
        std::cout << "Sudoku puzzle is not solvable" << std::endl;
        return;
    }
    std::cout << "Solution is the following:" << std::endl;
    for (int rr=0; rr < boardSize; rr++) {
        for (int cc=0; cc<boardSize; cc++) {
            std::cout << board[rr][cc] << " ";
        }
        std::cout << std::endl;
    }
}

int main()
{
    /*vector<vector<char> > puzzle0 = {{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
                                    {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                                    {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                                    {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                                    {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                                    {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                                    {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                                    {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                                    {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};*/
    vector<vector<char> > puzzle1 = {{'.', '.', '9', '7', '4', '8', '.', '.', '.'},
                                    {'7', '.', '.', '.', '.', '.', '.', '.', '.'},
                                    {'.', '2', '.', '1', '.', '9', '.', '.', '.'},
                                    {'.', '.', '7', '.', '.', '.', '2', '4', '.'},
                                    {'.', '6', '4', '.', '1', '.', '5', '9', '.'},
                                    {'.', '9', '8', '.', '.', '.', '3', '.', '.'},
                                    {'.', '.', '.', '8', '.', '3', '.', '2', '.'},
                                    {'.', '.', '.', '.', '.', '.', '.', '.', '6'},
                                    {'.', '.', '.', '2', '7', '5', '9', '.', '.'}};

    Sudoku sudoku(puzzle1);
    sudoku.solveSudoku();
}

