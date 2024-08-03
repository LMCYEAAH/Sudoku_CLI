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
    std::cout << std::string(40,'-') << std::endl;
    std::cout << "Output: " << getMessageBuffer() << std::endl;
    std::cout << std::string(40,'-') << std::endl;
}

void StateMachine::displayInfoBar()
{
    std::cout << std::string(40,'-') << std::endl;
    std::cout << "Difficulty: " << getCategoryString();
    std::cout << std::string(15 - getCategoryString().size(),' ') + "Puzzle: " << getPuzzleNumber() << "/10" << std::endl;
    std::cout << std::string(40,'-') << std::endl;
}
void StateMachine::displayMenu(sudoku_state state)
{

    clearScreen();
    switch(state)
    {
        case SUDOKU_START_SCREEN:
        {
            if(true) displayInfoBar();
            std::cout << "    Welcome to Sudoku for Terminal!\r\n";
            std::cout << "1) Play Sudoku\r\n"
                        << "2) Change Difficulty\r\n"
                        << "3) Select Puzzle or Randomize\r\n"
                        << "4) Options\r\n"
                        << "5) Exit\r\n";
            padScreen(2);
            break;
        }
        case SUDOKU_PLAY_SCREEN:
        {
            if(true) displayInfoBar();
            getSudokuGrid()->displayGrid();
            // padScreen(getScreenSize() >> 3);
            // std::cout << "1) Set Block   2) Load   3) Save\r\n";
            // std::cout << "4) Solve       5) Reset  6) Main Menu\r\n";
            // std::cout << "Output: " << getMessageBuffer() << std::endl;
            if(true) displayMessageBar();
            std::cout << "For a list of commands, enter 'list'.\r\n";
            std::cout << "For Sudoku Rules, enter 'help'.\r\n";
            std::cout << "To return to main menu, enter 'back'.\r\n";
            break; 
        }
        case SUDOKU_CATEGORY_SELECT_SCREEN:
        {
            if(true) displayInfoBar();
            std::cout << "1) Easy\r\n";
            std::cout << "2) Medium\r\n";
            std::cout << "3) Hard\r\n";
            std::cout << "4) Expert\r\n";
            std::cout << "5) Master\r\n";
            std::cout << "6) Extreme\r\n";
            padScreen(getScreenSize() >> 2);
            if(true) displayMessageBar();
            std::cout << "To choose difficulty, enter the corresponding number shown above (1-6).\r\n";
            std::cout << "To go back, enter 'back'\r\n";
            break;
        }
        case SUDOKU_PUZZLE_SELECT_SCREEN:
        {
            if(true) displayInfoBar();
            // List puzzles
            std::cout << "Placeholder puzzle list";
            padScreen(10);
            if(true) displayMessageBar();
            std::cout << "To return to main menu, enter 'back'.\r\n";
            break;
        }
        case SUDOKU_HELP_SCREEN:
        {
            if(true) displayInfoBar();
            std::cout << "In classic Sudoku, the objective is to fill a 9 × 9 grid with digits\r\n"
                        << "so that each column, each row, and each of the nine 3 × 3 subgrids\r\n"
                        << "that compose the grid contains all of the digits from 1 to 9. The\r\n"
                        << "puzzle setter provides a partially completed grid,\r\n"
                        << "which for a well-posed puzzle has a single solution.\r\n";
            padScreen(getScreenSize() >> 2);
            // std::cout << "Output: " << getMessageBuffer() << std::endl;
            if(true) displayMessageBar();
            std::cout << "To go back, enter 'back'.\r\n";
            break;
        }
        case SUDOKU_LIST_SCREEN:
        {
            if(true) displayInfoBar();
            std::cout << std::string(10,'-')
                        << "List of Commands"
                        << std::string(10,'-') << "\r\n";
            std::cout << "reset" + std::string(15 - 5,' ') + "resets puzzle to initial state";
            padScreen(getScreenSize() >> 2);
            if(true) displayMessageBar();
            break;
        }
        case SUDOKU_OPTIONS_SCREEN:
        {
            if(true) displayInfoBar();
            std::cout << "Options screen placeholder";
            padScreen(getScreenSize() >> 1);
            if(true) displayMessageBar();
            break;
        }
        case SUDOKU_END_SCREEN:
    {
        std::cout << "Thanks for Playing!";
        padScreen(getScreenSize() >> 1);
        break;
    }
    }
}


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

void StateMachine::commandInterpreter(sudoku_state state)
{
    switch(state)
    {
        case SUDOKU_START_SCREEN:
        {
            _commandBuffer = toUpper(getInput("Please select one of the following.\r\nEnter number (1-5): "));
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
                else {
                    setMessageBuffer("'" + _inputBuffer + "' is an invalid Command.");
                }
            break;
        }
        case SUDOKU_CATEGORY_SELECT_SCREEN:
        {
            _commandBuffer = toUpper(getInput("Enter command: "));

            if(_commandBuffer == "1") {
                setCategory(EASY);
                setMessageBuffer("Easy difficulty selected.");
            }
            else if(_commandBuffer == "2") {
                setCategory(MEDIUM);
                setMessageBuffer("Medium difficulty selected.");
            }
            else if(_commandBuffer == "3") {
                setCategory(HARD);
                setMessageBuffer("Hard difficulty selected.");
            }
            else if(_commandBuffer == "4") {
                setCategory(EXPERT);
                setMessageBuffer("Expert difficulty selected.");
            }
            else if(_commandBuffer == "5") {
                setCategory(MASTER);
                setMessageBuffer("Master difficulty selected.");
            }
            else if(_commandBuffer == "6") {
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
            _commandBuffer = toUpper(getInput("Enter Command: "));
            if(_commandBuffer == "BACK") {
                setNewState(popPreviousState(),false);
            }
            else {
                setMessageBuffer("'" + _inputBuffer + "' is an invalid Command.");
            }
            break;
        }
        case SUDOKU_OPTIONS_SCREEN:
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