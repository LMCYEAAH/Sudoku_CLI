#include "StateMachine.h"


std::string toLower(std::string str);
std::string toUpper(std::string str);
bool contains(std::string str, std::string subStr);

StateMachine::StateMachine()
{
    setMessageBuffer("");
    setNewState(SUDOKU_START_SCREEN,false);
    setScreenSize(DEFAULT_SCREEN_SIZE);
    setCategory(EASY);
    setPuzzleNumber(1);
}


sudoku_state StateMachine::getCurrentState() {
    return _state;
}

void StateMachine::setNewState(sudoku_state state, bool setPreviousState)
{
    if(setPreviousState) _previousStates.push(_state);
    setMessageBuffer("");
    _state = state;
}

void StateMachine::pushPreviousState(sudoku_state state)
{
    if(_previousStates.size() < MAX_PREV_STATES) {
        _previousStates.push(state);
    } else {
        std::cout << "Error: _previousStates stack overflow..\r\n";
    }
}
sudoku_state StateMachine::popPreviousState()
{
    if(!_previousStates.empty()) {
        sudoku_state prevState = _previousStates.top();
        _previousStates.pop();
        return prevState;
    } else {
        //error, return back to start screen for now
        return SUDOKU_START_SCREEN;
    }
}

std::string StateMachine::getMessageBuffer()
{
    return _messageBuffer;
}

void StateMachine::setMessageBuffer(std::string str)
{
    _messageBuffer = str;
}

sudoku_category StateMachine::getCategory() {
    return _category;
}

void StateMachine::setCategory(sudoku_category category)
{
    _category = category;
}

std::string StateMachine::getCategoryString()
{
    switch(getCategory())
    {
        case EASY:
            return "Easy";
        case MEDIUM:
            return "Medium";
        case HARD:
            return "Hard";
        case EXPERT:
            return "Expert";
        case MASTER:
            return "Master";
        case EXTREME:
            return "Extreme";
        default:
            return "???";
    }
}

int StateMachine::getScreenSize()
{
    return _screenSize;
}

void StateMachine::setScreenSize(int screenSize)
{
    _screenSize = screenSize;
}

int StateMachine::getPuzzleNumber()
{
    return _puzzleNumber;
}

void StateMachine::setPuzzleNumber(int puzzleNumber)
{
    _puzzleNumber = puzzleNumber;
}

std::string StateMachine::getPuzzleString()
{
   return "puzzle" + std::to_string(getPuzzleNumber());
}

bool isInteger(std::string str)
{
    int strSize = str.size();
    if(strSize < 1) return false;
    for(int i = 0; i < str.size(); i++) {
        if(!isdigit(str[i])) return false;
    }
    return true;
}

void displayVector(std::vector<int> vec)
{
    int vecSize = vec.size();
    for(int i = 0; i < vecSize; i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}

void padScreen(int num)
{
    if(num < 1) return;
    std::cout << std::string(num - 1,'\n');
    std::cout << std::endl;
}

void StateMachine::clearScreen()
{
    padScreen(_screenSize << 4);
}

void StateMachine::displayMessageBar()
{
    std::cout << std::string(80,'-') << std::endl;
    std::cout << "Output: " << getMessageBuffer() << std::endl;
    std::cout << std::string(80,'-') << std::endl;
}

void StateMachine::displayScreenBar(sudoku_state state)
{
    std::string screenStr;
    switch(state)
    {
        case SUDOKU_START_SCREEN:
        {
            screenStr = "Sudoku for Terminal! (LMC 2024)";
            break;
        }
        case SUDOKU_PLAY_SCREEN:
        {
            if(!getSudokuGrid()->isSolved()) {
                screenStr = "Solve the puzzle.";
            }
            else {
                screenStr = "Congratulations! Puzzle solved!";
            }
            break;
        }
        case SUDOKU_CATEGORY_SELECT_SCREEN:
        {
            screenStr = "Select Difficulty";
            break;
        }
        case SUDOKU_PUZZLE_SELECT_SCREEN:
        {
            screenStr = "Select Puzzle Number";
            break;
        }
        case SUDOKU_OPTIONS_SCREEN:
        {
            screenStr = "Configure Options";
            break;
        }
        case SUDOKU_LIST_SCREEN:
        {
            screenStr = "Command List";
            sudoku_state prevState = _previousStates.top();
            switch(prevState)
            {
                case SUDOKU_PLAY_SCREEN:
                {
                    screenStr = "Sudoku " + screenStr;
                    break;
                }
                case SUDOKU_OPTIONS_SCREEN:
                {
                    screenStr = "Options " + screenStr;
                    break;
                }
                case SUDOKU_PUZZLE_SELECT_SCREEN:
                {
                    screenStr = "Puzzle Select " + screenStr;
                    break;
                }
                case SUDOKU_CATEGORY_SELECT_SCREEN:
                {
                    screenStr = "Difficulty Select " + screenStr;
                    break;
                }
            }
            break;
        }
        case SUDOKU_HELP_SCREEN:
        {
            if(_previousStates.top() == SUDOKU_PLAY_SCREEN) {
                    screenStr = "Sudoku Rules";
            }
            break;
        }
        case SUDOKU_END_SCREEN:
        {
            screenStr = "See You Later";
            break;
        }
    }
    int screenStrSize = screenStr.size();
    std::cout << std::string(40 - (screenStrSize / 2) - (screenStrSize%2 == 1 ? 1 : 0),'-') << screenStr << std::string(40 - (screenStr.size() / 2),'-') << std::endl;

}

void StateMachine::displayInfoBar()
{
    std::cout << std::string(80,'-') << std::endl;
    std::cout << "Difficulty: " << getCategoryString();
    std::cout << std::string(23 - getCategoryString().size(),' ') + "[SUDOKU]" + std::string(27 - (getPuzzleNumber() > 9 ? 1 : 0) - (getPuzzleNumber() > 99 ? 1 : 0), ' ') + "Puzzle: " << getPuzzleNumber() << std::endl;
    std::cout << std::string(80,'-') << std::endl;
}
void StateMachine::displayMenu(sudoku_state state)
{

    clearScreen();
    switch(state)
    {
        case SUDOKU_START_SCREEN:
        {
            if(true) displayInfoBar();
            if(true) displayScreenBar(SUDOKU_START_SCREEN);
            std::cout << "1) Play Sudoku\r\n"
                        << "2) Change Difficulty\r\n"
                        << "3) Select Puzzle or Randomize\r\n"
                        << "4) Options\r\n"
                        << "5) Exit\r\n";
            padScreen(13);
            std::cout << "Please select one of the following.\r\n";
            if(true) displayMessageBar();
            break;
        }
        case SUDOKU_PLAY_SCREEN:
        {
            if(true) displayInfoBar();
            if(true) displayScreenBar(SUDOKU_PLAY_SCREEN);
            padScreen(1);
            getSudokuGrid()->displayGrid(20);
            padScreen(1);
            std::cout << "For a list of commands, enter 'list'. For Sudoku Rules, enter 'help'.\r\n";
            std::cout << "To return to main menu, enter 'back'.\r\n";
            if(true) displayMessageBar();
            break; 
        }
        case SUDOKU_CATEGORY_SELECT_SCREEN:
        {
            if(true) displayInfoBar();
            if(true) displayScreenBar(SUDOKU_CATEGORY_SELECT_SCREEN);
            std::cout << "1) Easy\r\n";
            std::cout << "2) Medium\r\n";
            std::cout << "3) Hard\r\n";
            std::cout << "4) Expert\r\n";
            std::cout << "5) Master\r\n";
            std::cout << "6) Extreme\r\n";
            padScreen(10);
            std::cout << "Enter a number between 1 and 6,\r\n";
            std::cout << "or enter the difficulty value (e.g., 'easy').\r\n";
            std::cout << "To go back, enter 'back'\r\n";
            if(true) displayMessageBar();
            break;
        }
        case SUDOKU_PUZZLE_SELECT_SCREEN:
        {
            if(true) displayInfoBar();
            if(true) displayScreenBar(SUDOKU_PUZZLE_SELECT_SCREEN);
            // List puzzles
            std::cout << "Enter value between 1 and 100.\r\n";
            padScreen(17);
            std::cout << "To return to main menu, enter 'back'.\r\n";
            if(true) displayMessageBar();
            break;
        }
        case SUDOKU_HELP_SCREEN:
        {
            if(true) displayInfoBar();
            if(true) displayScreenBar(SUDOKU_HELP_SCREEN);
            std::cout << "In classic Sudoku, the objective is to fill a 9 × 9 grid with digits\r\n"
                        << "so that each column, each row, and each of the nine 3 × 3 subgrids\r\n"
                        << "that compose the grid contains all of the digits from 1 to 9. The\r\n"
                        << "puzzle setter provides a partially completed grid,\r\n"
                        << "which for a well-posed puzzle has a single solution.\r\n";
            padScreen(13);
            std::cout << "To go back, enter 'back'.\r\n";
            if(true) displayMessageBar();
            break;
        }
        case SUDOKU_LIST_SCREEN:
        {
            if(true) displayInfoBar();
            if(true) displayScreenBar(SUDOKU_LIST_SCREEN);
            std::cout << "list" + std::string(30 - 4,' ') + "lists commands for interacting with Sudoku puzzle\r\n";
            std::cout << "fill  [row],[column] [value]" + std::string(30 - 28,' ') + "fills grid with [value] (1-9) at specified [row] and [column].\r\n";
            std::cout << "clear [row],[column]" + std::string(30 - 20,' ') + "erases grid value at specified [row] and [column].\r\n";
            std::cout << "note  [row],[column] [value]" + std::string(30 - 28,' ') + "adds/removes possible [value] to grid at specified [row] and [column].\r\n";
            std::cout << "show  [row],[column]" + std::string(30 - 20,' ') + "outputs user-noted possible values from grid at specified [row] and [column].\r\n";
            std::cout << "reset" + std::string(30 - 5,' ') + "resets puzzle to initial state\r\n";
            std::cout << "load" + std::string(30 - 4,' ') + "Loads save file from previous session.\r\n";
            std::cout << "save" + std::string(30 - 4,' ') + "Saves state of current Sudoku Grid.\r\n";
            padScreen(11);
            if(true) displayMessageBar();
            break;
        }
        case SUDOKU_OPTIONS_SCREEN:
        {
            if(true) displayInfoBar();
            if(true) displayScreenBar(SUDOKU_OPTIONS_SCREEN);
            std::cout << "Options screen placeholder\r\n";
            padScreen(18);
            if(true) displayMessageBar();
            break;
        }
        case SUDOKU_END_SCREEN:
    {
        if(true) displayInfoBar();
        if(true) displayScreenBar(SUDOKU_END_SCREEN);
        padScreen(10);
        std::cout << std::string(40 - 10,' ') << "Thanks for Playing!" << std::string(40 - 9,' ');
        padScreen(12);
        break;
    }
    }
}

// todo define terminal size (seems to be width: 80 characters, height: 26 lines)

void promptForValidInput(sudoku_state state)
{
    std::string tempInput;
    switch(state)
    {
        case SUDOKU_START_SCREEN:
            break;
        case TYPE_STRING:
        default:
            break;
    }
}

bool StateMachine::isColorEnabled()
{
    return _colorEnabled;
}

void StateMachine::setColorEnabled(bool value)
{
    _colorEnabled = value;
}

std::string StateMachine::getInput(std::string strPrompt)
{
    std::cout << strPrompt;
    std::getline(std::cin, _inputBuffer);
    return _inputBuffer;
}

SudokuGrid* StateMachine::getSudokuGrid()
{
    return _grid;
}

void StateMachine::setSodukuGrid(std::string filePath)
{
    _grid = new SudokuGrid(filePath);
}

//todo play command, list in main menu
void StateMachine::commandInterpreter(sudoku_state state)
{
    std::string msg;
    switch(state)
    {
        case SUDOKU_START_SCREEN:
        {
            _commandBuffer = toUpper(getInput("Enter number or command: "));
            if(_commandBuffer == "1") {
                setNewState(SUDOKU_PUZZLE_INIT,false);
            }
            else if(_commandBuffer == "2") {
                setNewState(SUDOKU_CATEGORY_SELECT_SCREEN,true);
            }
            else if(_commandBuffer == "3") {
                setNewState(SUDOKU_PUZZLE_SELECT_SCREEN,true);
            }
            else if(_commandBuffer == "4") {
                setNewState(SUDOKU_OPTIONS_SCREEN,true);
            }
            else if(_commandBuffer == "5") {
                setNewState(SUDOKU_END_SCREEN,true);
            }
            else if(_commandBuffer == "EXIT") {
                setNewState(SUDOKU_END_SCREEN,true);
            }
            break;
        }
        case SUDOKU_PLAY_SCREEN:
        {
            _commandBuffer = toUpper(getInput("Enter command: "));
                if(_commandBuffer == "SOLVE") {
                    if(getSudokuGrid()->solveGrid() == 0) {
                        setMessageBuffer("Puzzle suddenly solved!");
                    } else {
                        setMessageBuffer("Could not solve puzzle...");
                    }
                }
                else if(_commandBuffer == "RESET") {
                    setSodukuGrid(_filePath);
                    setMessageBuffer("Puzzle Reset.");
                }
                else if(_commandBuffer == "EXIT") {
                    setNewState(SUDOKU_END_SCREEN,true);
                }
                else if(_commandBuffer == "HELP") {
                    setNewState(SUDOKU_HELP_SCREEN,true);
                }
                else if(_commandBuffer == "LIST") {
                    setNewState(SUDOKU_LIST_SCREEN,true);
                }
                else if(_commandBuffer == "BACK") {
                    setMessageBuffer("");
                    setNewState(SUDOKU_START_SCREEN,false);
                }
                else if(_commandBuffer == "LOAD") {

                }
                else if(_commandBuffer == "SAVE") {

                }
                else if(_commandBuffer == "UNDO") {
                    setMessageBuffer("Undo Under Construction :)");
                }
                else if(contains(_commandBuffer,"FILL")) {
                    // set value on grid
                    setMessageBuffer(_inputBuffer);
                }
                else if(contains(_commandBuffer,"CLEAR")) {
                    // clear value on grid
                    setMessageBuffer(_inputBuffer);
                }
                else if(contains(_commandBuffer,"NOTE")) {
                    // set value on grid
                    setMessageBuffer(_inputBuffer);
                }
                else if(contains(_commandBuffer,"SHOW")) {
                    // set value on grid
                    setMessageBuffer(_inputBuffer);
                }
                else if(_commandBuffer[0] == 'F') {
                    if(_commandBuffer.size() == 4) {
                        for(int i = 0; i < 3; i++) {
                            if(!isdigit(_commandBuffer[1 + i])) {
                                setMessageBuffer("Invalid input");
                            }
                        }
                        int row = _commandBuffer[1] - '0';
                        int col = _commandBuffer[2] - '0';
                        int val = _commandBuffer[3] - '0';
                        if(row == 0 || col == 0 || val == 0) {
                            setMessageBuffer("Invalid input");
                            break;
                        }
                        row--;
                        col--;

                        getSudokuGrid()->setValueAtBlock(row,col,val);
                        row++;
                        col++;

                        setMessageBuffer(_inputBuffer);
                    }
                }
                else if(_commandBuffer[0] == 'C') {
                    if(_commandBuffer.size() == 3) {
                        for(int i = 0; i < 2; i++) {
                            if(!isdigit(_commandBuffer[1 + i])) {
                                setMessageBuffer("Invalid input");
                            }
                        }
                        int row = _commandBuffer[1] - '0';
                        int col = _commandBuffer[2] - '0';
                        if(row == 0 || col == 0) {
                            setMessageBuffer("Invalid input");
                            break;
                        }
                        row--;
                        col--;

                        getSudokuGrid()->setValueAtBlock(row,col,0);
                        row++;
                        col++;
                        // msg = "Value Cleared. (" + char(row + '0') + ',' + char(col + '0') + ')';
                        // msg += " is empty";
                        setMessageBuffer(_inputBuffer);
                    }
                }
                else {
                    setMessageBuffer("'" + _inputBuffer + "' is an invalid Command.");
                }
            break;
        }
        case SUDOKU_CATEGORY_SELECT_SCREEN:
        {
            _commandBuffer = toUpper(getInput("Enter command: "));

            if(_commandBuffer == "1" || _commandBuffer == "EASY") {
                setCategory(EASY);
                setMessageBuffer("Easy difficulty selected.");
            }
            else if(_commandBuffer == "2" || _commandBuffer == "MEDIUM") {
                setCategory(MEDIUM);
                setMessageBuffer("Medium difficulty selected.");
            }
            else if(_commandBuffer == "3" || _commandBuffer == "HARD") {
                setCategory(HARD);
                setMessageBuffer("Hard difficulty selected.");
            }
            else if(_commandBuffer == "4" || _commandBuffer == "EXPERT") {
                setCategory(EXPERT);
                setMessageBuffer("Expert difficulty selected.");
            }
            else if(_commandBuffer == "5" || _commandBuffer == "MASTER") {
                setCategory(MASTER);
                setMessageBuffer("Master difficulty selected.");
            }
            else if(_commandBuffer == "6" || _commandBuffer == "EXTREME") {
                setCategory(EXTREME);
                setMessageBuffer("Extreme difficulty selected.");
            }
            else if(_commandBuffer == "BACK") {
                setMessageBuffer("");
                setNewState(popPreviousState(),false);
            }
            else {
                setMessageBuffer("'" + _inputBuffer + "' is an invalid Command.");
            }
            break;
        }
        case SUDOKU_PUZZLE_SELECT_SCREEN:
        {
            
            _commandBuffer = toUpper(getInput("Enter number or command: "));
            if(_commandBuffer == "BACK") {
                setNewState(popPreviousState(),false);
            }
            else if(_commandBuffer == "EXIT") {
                setNewState(SUDOKU_END_SCREEN, true);
            }
            else if(isInteger(_commandBuffer)) {
                int num = std::stoi(_commandBuffer);
                if(num >= 1 && num <= 100) {
                    setPuzzleNumber(num);
                    setMessageBuffer("puzzle" + _commandBuffer + " (" + getCategoryString() + ") Selected.");
                } else {
                    setMessageBuffer("Invalid value. Enter a number between 1 and 100");
                }
            }
            else {
                setMessageBuffer("'" + _inputBuffer + "' is an invalid value.");
            }
            break;
        }
        case SUDOKU_OPTIONS_SCREEN:
        {
            _commandBuffer = toUpper(getInput("Enter command: "));
            if(_commandBuffer == "BACK") {
                setNewState(popPreviousState(),false);
            }
            else {
                setMessageBuffer("'" + _inputBuffer + "' is an invalid Command.");
            }
            break;
        }
        case SUDOKU_HELP_SCREEN:
        {
            _commandBuffer = toUpper(getInput("Enter command: "));
            if(_commandBuffer == "BACK") {
                setNewState(popPreviousState(),false);
            }
            else {
                setMessageBuffer("'" + _inputBuffer + "' is an invalid Command.");
            }
            break;
        }
        case SUDOKU_LIST_SCREEN:
        {
            _commandBuffer = toUpper(getInput("Enter Command: "));
            if(_commandBuffer == "BACK") {
                setNewState(popPreviousState(),false);
            }
            else {
                setMessageBuffer("'" + _inputBuffer + "' is an invalid Command.");
            }
            break;
        }
    }
}

void StateMachine::start()
{
    while(true)
    {
        switch(getCurrentState())
        {
            case SUDOKU_START_SCREEN:
            {
                displayMenu(SUDOKU_START_SCREEN);
                commandInterpreter(SUDOKU_START_SCREEN);
                break;
            }
            case SUDOKU_CATEGORY_SELECT_SCREEN:
            {
                displayMenu(SUDOKU_CATEGORY_SELECT_SCREEN);
                commandInterpreter(SUDOKU_CATEGORY_SELECT_SCREEN);
                break;
            }
            case SUDOKU_PUZZLE_SELECT_SCREEN:
            {
                displayMenu(SUDOKU_PUZZLE_SELECT_SCREEN);
                commandInterpreter(SUDOKU_PUZZLE_SELECT_SCREEN);
                break;
            }
            case SUDOKU_PUZZLE_INIT:
            {
                _filePath = "puzzles/" + getCategoryString() + "/" + getPuzzleString() + ".txt";
                setSodukuGrid(_filePath);
                setNewState(SUDOKU_PLAY_SCREEN,false);
                break;
            }
            case SUDOKU_PLAY_SCREEN:
            {
                displayMenu(SUDOKU_PLAY_SCREEN);
                commandInterpreter(SUDOKU_PLAY_SCREEN);
                break;
            }
            case SUDOKU_HELP_SCREEN:
            {
                displayMenu(SUDOKU_HELP_SCREEN);
                commandInterpreter(SUDOKU_HELP_SCREEN);
                break;
            }
            case SUDOKU_LIST_SCREEN:
            {
                displayMenu(SUDOKU_LIST_SCREEN);
                commandInterpreter(SUDOKU_LIST_SCREEN);
                break;
            }
            case SUDOKU_OPTIONS_SCREEN:
            {
                displayMenu(SUDOKU_OPTIONS_SCREEN);
                commandInterpreter(SUDOKU_OPTIONS_SCREEN);
                break;
            }
            case SUDOKU_END_SCREEN:
            {
                displayMenu(SUDOKU_END_SCREEN);
                return;
            }
        }
    }
}

std::string toLower(std::string str)
{
    int strSize = str.size();
    for(int i = 0; i < strSize; i++) {
        if(isalpha(str[i])) {
            if(isupper(str[i])) str[i] += 'a' - 'A';
        }
    }
    return str;
}

std::string toUpper(std::string str)
{
    int strSize = str.size();
    for(int i = 0; i < strSize; i++) {
        if(isalpha(str[i])) {
            if(islower(str[i])) str[i] += 'A' - 'a';
        }
    }
    return str;
}

bool contains(std::string str, std::string subStr)
{
    int strSize = str.size();
    int subStrSize = subStr.size();
    int matchCount = 0;

    for(int i = 0; i < strSize; i++) {
        if(str[i] == subStr[matchCount]) {
            matchCount++;
            if(matchCount == subStrSize - 1) return true;
        } else {
            matchCount = 0;
        }
    }
    return false;
}