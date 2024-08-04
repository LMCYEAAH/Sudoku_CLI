#ifndef SUDOKUGRID_H
#define SUDOKUGRID_H
#include <iostream>
#include <fstream>
#include <vector>
#include "Block.h"

// #define _DEBUG
#define MAX_SCAN_COUNT 10
#define GRID_ROW_COUNT 9
#define GRID_COL_COUNT 9
#define GRID_SQUARE_COUNT 9
#define DEFAULT_EMPTY_BLOCK_CHAR '-'

enum displayByEnum {
    ROW,
    COLUMN,
    SQUARE
};

class SudokuGrid {
    public:
        void                Init(std::vector<std::vector<int>> vec);
                            SudokuGrid();
                            SudokuGrid(std::vector<std::vector<int>> vec);
                            SudokuGrid(std::string filePath);
        void                displayPossibleValuesAtBlock(int row, int col);
        void                displayAllPossibleValues(displayByEnum displayBy);
        char                getEmptyBlockCharacter();
        void                setEmptyBlockCharacter(char emptyBlockCharacter);
        void                displayGrid(int indent);      //todo add indentation argument
        int                 solveGrid();
        bool                isSolved();
        bool                isBlockLocked(int row, int col);
        bool                isBlockValid(int row, int col);
        int                 solvedBlockCount();
        void                displaySolvedBlockCount();
        int                 getValueAtBlock(int row, int col);
        int                 setValueAtBlock(int row, int col, int val);
        bool                validateRowAtBlock(int row, int col);
        bool                validateColAtBlock(int row, int col);
        bool                validateSquareAtBlock(int row, int col);
        std::vector<int>    getPossibleValuesAtBlock(int row, int col);
        void                setPossibleValuesAtBlock(int row, int col, std::vector<int> vec);
    private:
        std::vector<std::vector<Block>> _grid;
        char                _emptyBlockCharacter;
        void                setPossibleValuesBasedOnAdjacent(int row, int col);
        void                isolateUncommonPossibleValueAtRow(int row);
        void                isolateUncommonPossibleValueAtColumn(int col);
        void                isolateUncommonPossibleValueAtSquare(int square);
        void                removeCommonPossibleValuesAtRow(int row, bool checkForSubsets);
        void                removeCommonPossibleValuesAtColumn(int col, bool checkForSubsets);
        void                removeCommonPossibleValuesAtSquare(int square, bool checkForSubsets);
        void                removeValuesFromBlock(int row, int col, std::vector<int> vec);
        void                scanGridForPossibleValues(bool fillBlocks);
        void                fillBlocksBasedOnPossibleValues();
        std::vector<std::vector<int>> hardCodedPuzzle();
};

#endif