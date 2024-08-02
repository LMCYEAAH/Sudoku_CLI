#include "SudokuGrid.h"



void SudokuGrid::Init(std::vector<std::vector<int>> vec)
{
    for(int i = 0; i < 9; i++) {
        _grid.push_back(std::vector<Block>());
        for(int j = 0; j < 9; j++) {
            _grid[i].push_back(Block(vec[i][j]));
        }
    }
}

SudokuGrid::SudokuGrid()
{
    Init(hardCodedPuzzle());
}

// Assumes new sudoku puzzle (all values predefined or empty (0))
SudokuGrid::SudokuGrid(std::vector<std::vector<int>> vec)
{
    Init(vec);
}

SudokuGrid::SudokuGrid(std::string filePath) {
    std::vector<std::vector<int>> vec(9,{0,0,0,0,0,0,0,0,0});
    std::ifstream file(filePath);
    int tempVal = -1;
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            while(!isdigit(tempVal)) {
                if(file.eof()) {
                    std::cout << "ERROR. End of File before grid filled\r\n";
                    return;
                }
                tempVal = file.get();
            }
            tempVal -= '0';
            vec[i][j] = tempVal;
        }
    }
    Init(vec);
}

int SudokuGrid::getValueAtBlock(int row, int col)
{
    return _grid[row][col].getValue();
}

int SudokuGrid::setValueAtBlock(int row, int col, int val)
{
    return _grid[row][col].setValue(val);
}

std::vector<int> SudokuGrid::getPossibleValuesAtBlock(int row, int col)
{
    return _grid[row][col].getPossibleValues();
}

void SudokuGrid::setPossibleValuesAtBlock(int row, int col, std::vector<int> vec)
{
    _grid[row][col].setPossibleValues(vec);
}

bool SudokuGrid::isBlockLocked(int row, int col)
{
    return _grid[row][col].isLocked();
}

bool SudokuGrid::validateRowAtBlock(int row, int col)
{
    return true;
}

bool SudokuGrid::validateColAtBlock(int row, int col)
{
    return true;
}

bool SudokuGrid::validateSquareAtBlock(int row, int col)
{
    return true;
}


bool SudokuGrid::isBlockValid(int row, int col)
{
    if(isBlockLocked(row, col) || getPossibleValuesAtBlock(row, col).size() == 1) return true;
    else return false;
}

bool SudokuGrid::isSolved()
{
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(!isBlockValid(i,j)) return false;
        }
    }
    return true;
}

int SudokuGrid::solvedBlockCount()
{
    int solvedCount = 0;
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(isBlockValid(i,j)) solvedCount++;
        }
    }
    return solvedCount;
}

void SudokuGrid::displaySolvedBlockCount()
{
    std::cout << "Number of Blocks Solved: " << solvedBlockCount() << std::endl;
}

void SudokuGrid::removeValuesFromBlock(int row, int col, std::vector<int> vec)
{
    int vecSize = vec.size();
    std::vector<int> possibleValues = getPossibleValuesAtBlock(row, col);
    if(possibleValues == vec) return;               // Do not want to accidentally erase entire possible block
    int possibleValuesSize = possibleValues.size();
    for(int i = 0; i < possibleValuesSize; i++) {
        for(int j = 0; j < vecSize; j++) {
            if(possibleValues[i] == vec[j]) {
                possibleValues.erase(possibleValues.begin() + i);
                possibleValuesSize = possibleValues.size();
                i = 0;
                break;
            }
        }
    }

    setPossibleValuesAtBlock(row, col, possibleValues);
}

void SudokuGrid::removeCommonPossibleValuesAtRow(int row)
{
    // Row investigate
    std::vector<int> commonIndexes;
    // Searching for duplicate
    for(int startingIndex = 0; startingIndex < GRID_COL_COUNT; startingIndex++) {
        if(getValueAtBlock(row, startingIndex) > 0) continue;
        commonIndexes.clear();
        for(int i = 0; i < GRID_COL_COUNT; i++) {
            // if(i == startingIndex) continue;
            if(getValueAtBlock(row,i) > 0) continue;
            if(getPossibleValuesAtBlock(row,i) == getPossibleValuesAtBlock(row, startingIndex)) {
                commonIndexes.push_back(i);
            }
        }
        int commonIndexSize = commonIndexes.size();
        bool isCommonIndex = false;
        #ifdef _DEBUG
        std::cout << "Common Indexes at startingIndex = " << startingIndex << ": ";
        for(int index_i = 0; index_i < commonIndexSize; index_i++) {
            std:: cout << commonIndexes[index_i] << " ";
        }
        std::cout << std::endl;
        #endif
        if(getPossibleValuesAtBlock(row,startingIndex).size() == commonIndexSize) {
            for(int j = 0; j < GRID_COL_COUNT; j++) {
                isCommonIndex = false;
                for(int k = 0; k < commonIndexSize; k++) {
                    if(j == commonIndexes[k]) {
                        isCommonIndex = true;
                        break;
                    }
                }
                if(isCommonIndex) continue;
                removeValuesFromBlock(row, j, getPossibleValuesAtBlock(row, startingIndex));
            }
        }
    }
}
void SudokuGrid::removeCommonPossibleValuesAtColumn(int col)
{
    // Column investigate
    std::vector<int> commonIndexes;
    // Searching for duplicate
    for(int startingIndex = 0; startingIndex < GRID_ROW_COUNT; startingIndex++) {
        if(getValueAtBlock(startingIndex, col) > 0) continue;
        commonIndexes.clear();
        for(int i = 0; i < GRID_ROW_COUNT; i++) {
            // if(i == startingIndex) continue;
            if(getValueAtBlock(i,col) > 0) continue;
            if(getPossibleValuesAtBlock(i,col) == getPossibleValuesAtBlock(startingIndex, col)) {
                commonIndexes.push_back(i);
            }
        }
        int commonIndexSize = commonIndexes.size();
        bool isCommonIndex = false;
        #ifdef _DEBUG
        std::cout << "Common Indexes at startingIndex = " << startingIndex << ": ";
        for(int index_i = 0; index_i < commonIndexSize; index_i++) {
            std:: cout << commonIndexes[index_i] << " ";
        }
        std::cout << std::endl;
        #endif
        if(getPossibleValuesAtBlock(startingIndex, col).size() == commonIndexSize) {
            for(int j = 0; j < GRID_ROW_COUNT; j++) {
                isCommonIndex = false;
                for(int k = 0; k < commonIndexSize; k++) {
                    if(j == commonIndexes[k]) {
                        isCommonIndex = true;
                        break;
                    }
                }
                if(isCommonIndex) continue;
                removeValuesFromBlock(j, col, getPossibleValuesAtBlock(startingIndex, col));
            }
        }
    }
}
void SudokuGrid::removeCommonPossibleValuesAtSquare(int square)
{
            // Check Square
        std::vector<std::vector<int>> commonPairs;
        int squareRow, squareCol, commonPairsSize;
        bool isCommonPair = false;

        if(square < 3) { squareRow = 0; }
        else if(square < 6) { squareRow = 3; }
        else { squareRow = 6; }

        if(square%3 == 0) { squareCol = 0; }
        else if(square%3 == 1) { squareCol = 3; }
        else { squareCol = 6; }

        for(int startingRow = squareRow; startingRow < squareRow + 3; startingRow++) {
            for(int startingCol = squareCol; startingCol < squareCol + 3; startingCol++) {
                commonPairs.clear();
                if(getValueAtBlock(startingRow, startingCol) > 0) continue;
                for(int i = squareRow; i < squareRow + 3; i++) {
                    for(int j = squareCol; j < squareCol + 3; j++) {
                        if(getValueAtBlock(i,j) > 0) continue;
                        if(getPossibleValuesAtBlock(i,j) == getPossibleValuesAtBlock(startingRow,startingCol)) {
                            commonPairs.push_back(std::vector({i,j}));
                        }
                    }
                    commonPairsSize = commonPairs.size();
                    if(getPossibleValuesAtBlock(startingRow, startingCol).size() == commonPairsSize) {
                        for(int k = squareRow; k < squareRow + 3; k++) {
                            for(int m = squareCol; m < squareCol + 3; m++) {
                                isCommonPair = false;
                                for(int n = 0; n < commonPairsSize; n++) {
                                    if(std::vector<int>({k,m}) == commonPairs[n]) {
                                    isCommonPair = true;
                                    break;
                                    }
                                }
                                if(isCommonPair) continue;
                                #ifdef _DEBUG
                                std::cout << "Uncommon pair for:";
                                displayPossibleValuesAtBlock(commonPairs[0][0],commonPairs[0][1]);
                                std::cout << "(" << k << "," << m << ")\r\n";
                                #endif
                                removeValuesFromBlock(k, m, getPossibleValuesAtBlock(commonPairs[0][0], commonPairs[0][1]));
                            }
                        }
                    }
                }
            }
        }
}

void SudokuGrid::setPossibleValuesBasedOnAdjacent(int row, int col)
{
        if(!isBlockLocked(row, col)) {
        std::vector<int> possibleValues = {1,2,3,4,5,6,7,8,9};

        // Check row
        for(int i = 0; i < 9; i++) {
            if(i == col) continue;
            int vecSize = possibleValues.size();
            for(int j = 0; j < vecSize; j++) {
                if(getValueAtBlock(row, i) == possibleValues[j]) {
                    possibleValues.erase(possibleValues.begin() + j);
                    break;
                }
            }
        }

        // Check column
        for(int i = 0; i < 9; i++) {
            if(i == row) continue;
            int vecSize = possibleValues.size();
            for(int j = 0; j < vecSize; j++) {
                if(getValueAtBlock(i, col) == possibleValues[j]) {
                    possibleValues.erase(possibleValues.begin() + j);
                    break;
                }
            }
        }

        // Check Square
        int squareRow, squareCol;
        if(row < 3) { squareRow = 0; }
        else if(row < 6) { squareRow = 3; }
        else { squareRow = 6; }

        if(col < 3) { squareCol = 0; }
        else if(col < 6) { squareCol = 3; }
        else { squareCol = 6; }

        for(int i = squareRow; i < squareRow + 3; i++) {
            for(int j = squareCol; j < squareCol + 3; j++) {
                if(i == row && j == col) continue;
                int vecSize = possibleValues.size();
                for(int k = 0; k < vecSize; k++) {
                    if(getValueAtBlock(i, j) == possibleValues[k]) {
                        possibleValues.erase(possibleValues.begin() + k);
                        break;
                    }
                }
            }
        }

        setPossibleValuesAtBlock(row, col, possibleValues);

        #ifdef _DEBUG
        std::cout << "Possible Values for (row=" << row << ",col=" << col << ",val=" << getValueAtBlock(row, col) << "): ";
        for(int i = 0; i < possibleValues.size(); i++) {
            std::cout << possibleValues[i] << " ";
        }
        // std::cout << std::endl;
        #endif

    } else {
        #ifdef _DEBUG
        std::cout << "Value is locked ";
        displayPossibleValuesAtBlock(row ,col);
        // std::cout << "(row=" << row << ",col=" << col << ",val=" << getValueAtBlock(row, col) << ")" << std::endl;
        #endif
    }
}

void SudokuGrid::displayPossibleValuesAtBlock(int row, int col)
{
    if(isBlockLocked(row, col)) {
        std::cout << "Value is locked for ";
        std::cout << "(row=" << row << ",col=" << col << ",val=" << getValueAtBlock(row, col) << ")" << std::endl;
    }
    else if(getValueAtBlock(row, col) > 0) {
        std::cout << "Value is defined for ";
        std::cout << "(row=" << row << ",col=" << col << ",val=" << getValueAtBlock(row, col) << ")" << std::endl;
    } else {
        std::vector<int> possibleValues = getPossibleValuesAtBlock(row, col);
        int possibleSize = possibleValues.size();
        std::cout << "Possible values for (row=" << row << ",col=" << col << "): ";
        for(int i = 0; i < possibleSize; i++) {
            std::cout << possibleValues[i];
            if(i < possibleSize - 1) std::cout << " ";
        }
        std::cout << std::endl;
    }
}

void SudokuGrid::displayAllPossibleValues(displayByEnum displayBy)
{
    int blockCount;
    switch(displayBy)
    {
        case ROW:
            for(int i = 0; i < GRID_ROW_COUNT; i++) {
                blockCount = 0;
                for(int j = 0; j < GRID_COL_COUNT; j++) {
                    if(getValueAtBlock(i,j) == 0) {
                        if(blockCount == 0) {
                            std::cout << "Row " << i + 1 << "\r\n";
                        }
                        blockCount++;
                        displayPossibleValuesAtBlock(i,j);
                    }
                }
            }
            break;
        case COLUMN:
            for(int j = 0; j < GRID_COL_COUNT; j++) {
                blockCount = 0;
                for(int i = 0; i < GRID_ROW_COUNT; i++) {
                    if(getValueAtBlock(i,j) == 0) {
                        if(blockCount == 0) {
                        std::cout << "Column " << j + 1 << "\r\n";
                        }
                        blockCount++;
                        displayPossibleValuesAtBlock(i,j);
                    }
                }
            }
            break;
        case SQUARE:
            int squareRow, squareCol;
            for(int square = 0; square < GRID_SQUARE_COUNT; square++) {
                blockCount = 0;

                if(square < 3) { squareRow = 0; }
                else if(square < 6) { squareRow = 3; }
                else { squareRow = 6; }

                if(square%3 == 0) { squareCol = 0; }
                else if(square%3 == 1) { squareCol = 3; }
                else { squareCol = 6; }

                for(int i = squareRow; i < squareRow + 3; i++) {
                    for(int j = squareCol; j < squareCol + 3; j++) {
                        if(getValueAtBlock(i,j) == 0) {
                            if(blockCount == 0) {
                                 std::cout << "Square " << square + 1 << "\r\n";
                            }
                            blockCount++;
                            displayPossibleValuesAtBlock(i,j);
                        }
                    }   
                }
                if(blockCount > 0) {

                }
            }
            break;
    }

}

void SudokuGrid::scanGridForPossibleValues(bool fillBlocks)
{
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            setPossibleValuesBasedOnAdjacent(i,j);
            if(fillBlocks) {
                if(getPossibleValuesAtBlock(i, j).size() == 1) {
                    setValueAtBlock(i, j, getPossibleValuesAtBlock(i,j)[0]);
                }
            }
        }
    }
}

void SudokuGrid::fillBlocksBasedOnPossibleValues()
{
    for(int i = 0; i < GRID_ROW_COUNT; i++) {
        for(int j = 0; j < GRID_COL_COUNT; j++) {
            if(getPossibleValuesAtBlock(i,j).size() == 1) {
                setValueAtBlock(i, j, getPossibleValuesAtBlock(i,j)[0]);
            }
        }
    }
}

void SudokuGrid::displayGrid()
{
    int row = 9;
    int col = 9;

    for(int i = 0; i < row; i++){ 
        for(int j = 0; j < col; j++) {
            if(getValueAtBlock(i,j) > 0) {
                std::cout << getValueAtBlock(i,j);
            } else {
                std::cout << "#";
            }
            if(j < row - 1){
                std::cout << " ";
                if(j%3 == 2) std::cout << " ";
            }
        }
        if( i!= 8) {
            std::cout << std::endl;
        }
        if(i%3 == 2) std::cout << std::endl;
    }
}

int SudokuGrid::solveGrid()
{
    int scanCount = 0;

    std::cout << "BEFORE\r\n";
    displaySolvedBlockCount();
    displayGrid();
    std::cout << std::endl;
    int prevSolvedCount = -1;
    while(scanCount < MAX_SCAN_COUNT) {
        if(prevSolvedCount == solvedBlockCount()) {
            break;
        }
        prevSolvedCount = solvedBlockCount();
        #ifdef _DEBUG
        std::cout << "SCAN #" << scanCount + 1 << std::endl;
        #endif
        scanGridForPossibleValues(true);
        scanCount++;
        if(isSolved()) break;
        #ifdef _DEBUG
        std::cout << "SCAN #" << scanCount << std::endl;
        displayGrid();
        std::cout << std::endl;
        #endif
    }

    if(isSolved()) {
        std::cout << "SOLVED AFTER " << scanCount << " SCANS!" << std::endl;
        displayGrid();
    } else {
        std::cout << "NOT SOLVED AFTER " << scanCount << " SCANS..." << std::endl;
        displaySolvedBlockCount();
        displayGrid();
        std::cout << "Attempting extra algorithms...\r\n";
        scanCount = 0;
        prevSolvedCount = -1;
        while(scanCount < MAX_SCAN_COUNT) {
            if(prevSolvedCount == solvedBlockCount()) {
            break;
            }
            prevSolvedCount = solvedBlockCount();
            for(int k = 0; k < GRID_SQUARE_COUNT; k++) {
                removeCommonPossibleValuesAtRow(k);
                removeCommonPossibleValuesAtColumn(k);
                removeCommonPossibleValuesAtSquare(k);
                fillBlocksBasedOnPossibleValues();
            }
            scanCount++;
            if(isSolved()) break;
        }
        if(isSolved()) {
            std::cout << "Solved!\r\n";
        } else {
            std::cout << "Not solved after " << scanCount << " attempts...\r\n";
        }
         std::cout << "Solved Blocks Count = " << solvedBlockCount() << std::endl;
         displayGrid();
         displayAllPossibleValues(SQUARE);
    }
    return 0;
}

std::vector<std::vector<int>> SudokuGrid::hardCodedPuzzle()
{
    std::vector<std::vector<int>> vect(9,{0,0,0,0,0,0,0,0,0});
    vect[0][0] = 5;
    vect[0][1] = 3;
    vect[0][4] = 7;
    
    vect[1][0] = 6;
    vect[1][3] = 1;
    vect[1][4] = 9;
    vect[1][5] = 5;
    
    vect[2][1] = 9;
    vect[2][2] = 8;
    vect[2][7] = 6;

    vect[3][0] = 8;
    vect[3][4] = 6;
    vect[3][8] = 3;

    vect[4][0] = 4;
    vect[4][3] = 8;
    vect[4][5] = 3;
    vect[4][8] = 1;
    
    vect[5][0] = 7;
    vect[5][4] = 2;
    vect[5][8] = 6;

    vect[6][1] = 6;
    vect[6][6] = 2;
    vect[6][7] = 8;

    vect[7][3] = 4;
    vect[7][4] = 1;
    vect[7][5] = 9;
    vect[7][8] = 5;

    vect[8][4] = 8;
    vect[8][7] = 7;
    vect[8][8] = 9;

    return vect;

}