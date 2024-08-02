#include <iostream>
#include <vector>

#include "SudokuGrid.h"
#include <fstream>


void displayVector(std::vector<int> vec);

int main() {
    // Hardcoding sudoku puzzle
    SudokuGrid newGrid;

    // By file
    SudokuGrid gridFile("puzzles/puzzle3(Hard).txt");



     gridFile.solveGrid();
    return 0;
}


void displayVector(std::vector<int> vec)
{
    int vecSize = vec.size();
    for(int i = 0; i < vecSize; i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}