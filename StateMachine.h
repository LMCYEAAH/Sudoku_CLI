#ifndef STATEMACHINE_H
#define STATEMACHINE_H
#include <iostream>
#include <fstream>
#include "SudokuGrid.h"

#define DEFAULT_SCREEN_SIZE 16

enum sudoku_state {
    SUDOKU_START,
    SUDOKU_CATEGORY_SELECT,
    SUDOKU_PUZZLE_SELECT,
    SUDOKU_PUZZLE_INIT,
    SUDOKU_DISPLAY_UNSOLVED_PUZZLE,
    SUDOKU_PLAY_WAIT,
    SUDOKU_SET_BLOCK,
    SUDOKU_DISPLAY_SOLVED_PUZZLE,
    SUDOKU_OPTIONS,
    SUDOKU_RETRY_PROMPT,
    SUDOKU_END
};

enum sudoku_category {
    EASY,
    MEDIUM,
    HARD,
    EXPERT,
    MASTER,
    EXTREME
};

enum input_type {
    TYPE_INT,
    TYPE_STRING
};

void displayVector(std::vector<int> vec);

void displayMenu(sudoku_state state);

void promptForValidInput(std::string* inputStr, input_type inputType);

bool isInteger(std::string str);

void padScreen(int num);



class StateMachine {
    public:
        StateMachine();
        sudoku_state getState();
        void setNextState(sudoku_state state);
        sudoku_category getCategory();
        void setCategory(sudoku_category category);
        int getPuzzleNumber();
        void setPuzzleNumber(int puzzleNumber);
        std::string getPuzzleString();
        std::string getCategoryString();
        int getScreenSize();
        void setScreenSize(int screenSize);
        std::string getInput();
        void clearScreen();
        int getInputAsInt();
        SudokuGrid* getSudokuGrid();
        void setSodukuGrid(std::string filePath);
        void start();


    private:
        sudoku_state _state;
        sudoku_category _category;
        std::string _inputBuffer;
        int _screenSize;
        int _puzzleNumber;
        SudokuGrid* _grid;
};

#endif