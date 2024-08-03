#ifndef STATEMACHINE_H
#define STATEMACHINE_H
#include <iostream>
#include <fstream>
#include <stack>
#include "SudokuGrid.h"

#define DEFAULT_SCREEN_SIZE 16
#define MAX_PREV_STATES 50

enum sudoku_state {
    SUDOKU_START_SCREEN,
    SUDOKU_CATEGORY_SELECT_SCREEN,
    SUDOKU_PUZZLE_SELECT_SCREEN,
    SUDOKU_PUZZLE_INIT,
    SUDOKU_PLAY_SCREEN,
    SUDOKU_HELP_SCREEN,
    SUDOKU_LIST_SCREEN,
    SUDOKU_OPTIONS_SCREEN,
    SUDOKU_RETRY_PROMPT,
    SUDOKU_END_SCREEN
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



bool isInteger(std::string str);

void padScreen(int num);



class StateMachine {
    public:
        StateMachine();
        sudoku_state getCurrentState();
        void setNewState(sudoku_state state, bool setPreviousState);
        bool isColorEnabled();
        void setColorEnabled(bool value);
        void         pushPreviousState(sudoku_state state);
        sudoku_state popPreviousState();
        void         displayInfoBar();
        void         displayMessageBar();
        void         displayMenu(sudoku_state state);
        sudoku_category getCategory();
        void setCategory(sudoku_category category);
        int getPuzzleNumber();
        void setPuzzleNumber(int puzzleNumber);
        std::string getPuzzleString();
        std::string getCategoryString();
        std::string getMessageBuffer();
        void        setMessageBuffer(std::string str);
        int getScreenSize();
        void setScreenSize(int screenSize);
        std::string getInput(std::string strPrompt);
        void clearScreen();
        SudokuGrid* getSudokuGrid();
        void setSodukuGrid(std::string filePath);
        void start();
        void commandInterpreter(sudoku_state state);


    private:
        sudoku_state _state;
        std::stack<sudoku_state> _previousStates;
        sudoku_category _category;
        std::string _inputBuffer;
        std::string _messageBuffer;
        std::string _filePath;
        std::string _commandBuffer;
        int _screenSize;
        int _puzzleNumber;
        bool _colorEnabled;
        SudokuGrid* _grid;
};

#endif