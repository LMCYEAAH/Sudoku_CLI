#include "StateMachine.h"


StateMachine::StateMachine()
{
    setNextState(SUDOKU_START);
    setScreenSize(DEFAULT_SCREEN_SIZE);
    setCategory(EASY);
    setPuzzleNumber(1);
}


sudoku_state StateMachine::getState() {
    return _state;
}

void StateMachine::setNextState(sudoku_state state)
{
    _state = state;
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

void displayMenu(sudoku_state state)
{

}

void promptForValidInput(sudoku_state state)
{
    std::string tempInput;
    switch(state)
    {
        case SUDOKU_START:
            break;
        case TYPE_STRING:
        default:
            break;
    }
}

std::string StateMachine::getInput()
{
    std::cin >> _inputBuffer;
    return _inputBuffer;
}

int StateMachine::getInputAsInt()
{
    std::string tempStr = getInput();
    int tempSize = tempStr.size();
    if(isInteger(tempStr)) {
        return std::stoi(tempStr);
    } else {
        return -1;
    }
}

SudokuGrid* StateMachine::getSudokuGrid()
{
    return _grid;
}

void StateMachine::setSodukuGrid(std::string filePath)
{
    _grid = new SudokuGrid(filePath);
}

void StateMachine::start()
{
    bool stateMachineExit = false;
    std::string filePath;
    while(!stateMachineExit)
    {
        switch(getState())
        {
            case SUDOKU_START:
                clearScreen();
                std::cout << "    Welcome to Sudoku for Terminal!\r\n";
                std::cout << std::string(40,'-') << std::endl;
                std::cout << "Difficulty: " << getCategoryString();
                std::cout << "         Puzzle: " << getPuzzleString() << std::endl;
                std::cout << std::string(40,'-') << std::endl;
                std::cout << "1) Play Sudoku\r\n"
                          << "2) Change Difficulty\r\n"
                          << "3) Select Puzzle or Randomize\r\n"
                          << "4) Options\r\n"
                          << "5) Exit\r\n";
                padScreen(2);
                std::cout << "Please select one of the following.\r\nEnter number (1-5): ";

                switch(getInputAsInt())
                {
                    case 1:
                        setNextState(SUDOKU_PUZZLE_INIT);
                        break;
                    case 2:
                        break;
                    case 3:
                        break;
                    case 4:
                        break;
                    case 5:
                        setNextState(SUDOKU_END);
                        break;
                    default:
                        break;
                }
                
                break;
            case SUDOKU_CATEGORY_SELECT:
                break;
            case SUDOKU_PUZZLE_INIT:
                filePath = "puzzles/" + getCategoryString() + "/" + getPuzzleString() + ".txt";
                setSodukuGrid(filePath);
                setNextState(SUDOKU_PLAY_WAIT);
                break;
            case SUDOKU_DISPLAY_UNSOLVED_PUZZLE:
                break;
            case SUDOKU_DISPLAY_SOLVED_PUZZLE:
                // clearScreen();
                // std::cout << "   " << getPuzzleString() << " (" << getCategoryString() << ")\r\n";
                getSudokuGrid()->solveGrid();
                // getSudokuGrid()->displayGrid();
                // padScreen(getScreenSize() >> 3);
                setNextState(SUDOKU_PLAY_WAIT);
                break;
            case SUDOKU_PLAY_WAIT:
                clearScreen();
                std::cout << "   " << getPuzzleString() << " (" << getCategoryString() << ")\r\n";
                getSudokuGrid()->displayGrid();
                padScreen(getScreenSize() >> 3);
                std::cout << "Choose one of the following.\r\n";
                std::cout << "1) Set Block   2) Load   3) Save\r\n";
                std::cout << "4) Solve       5) Reset  6) Main Menu\r\n";
                std::cout << "Enter Number: ";
                switch(getInputAsInt())
                {
                    case 1:
                        break;
                    case 2:
                        break;
                    case 3:
                        break;
                    case 4:
                        setNextState(SUDOKU_DISPLAY_SOLVED_PUZZLE);
                        break;
                    case 5:
                        setSodukuGrid(filePath);
                        break;
                    case 6:
                        setNextState(SUDOKU_START);
                        break;
                    default:
                        // setNextState(SUDOKU_PLAY_WAIT);
                        break;
                }
                break;
            case SUDOKU_END:
                clearScreen();
                std::cout << "Thanks for Playing!";
                padScreen(getScreenSize() >> 1);
                stateMachineExit = true;
            default:
                break;
        }
    }
}