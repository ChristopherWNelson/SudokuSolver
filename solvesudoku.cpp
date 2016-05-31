#include <iostream>
#include <cstdlib>
#include <string>
#include "SudokuGrid.h"

bool conflictingNumber(SudokuGrid& grid, int r,int c,int n){
  int startr = (r/3)*3;
  int startc = (c/3)*3;
  for(int row = 0; row < 9; row++) // check collumn
    if(grid.number(row,c) == n)
      return true;
  for(int col = 0; col < 9; col++) // check row
    if(grid.number(r,col) == n)
      return true;
  for(int i = 0; i < 3; i++){ // check 3x3 block
    int rowf = startr + i;
    for(int j = 0; j < 3; j++){
      int colf = startc + j;
      if(grid.number(rowf,colf) == n)
	return true;
    }
  }
  return false;
}

void autoPencil(SudokuGrid& grid){
  for (int r = 0; r < 9; r++)
    for (int c = 0; c < 9; c++)
      if (grid.number(r,c) == 0){
	grid.setAllPencils(r,c);
	for (int n = 1; n <= 9; n++)
	  if (conflictingNumber(grid,r,c,n))
	    grid.clearPencil(r,c,n);	
      }
}

int numPencilsInRow(SudokuGrid& grid, int row, int n){
  int count = 0;
  for (int c = 0; c < 9; c++)
    if(grid.isPencilSet(row, c, n))
      count++;
  return count;
}

int numPencilsInColumn(SudokuGrid& grid, int col, int n){
  int count = 0;
  for (int r = 0; r < 9; r++)
    if(grid.isPencilSet(r, col, n))
      count++;
  return count;
}

int numPencilsInBlock(SudokuGrid& grid, int row, int col, int n){
  int count = 0;
  int startr = (row/3)*3;
  int startc = (col/3)*3;
  for(int i = 0; i < 3; i++){
    int r = startr + i;
    for (int j = 0; j < 3; j++){
      int c = startc + j;
      if(grid.isPencilSet(r, c, n))
	count++;
    }
  }
  return count;
}
  
void deduce(SudokuGrid& grid){
  bool changed;
  do { // repeat until no changes made
    autoPencil(grid);
    changed = false;
    for (int row = 0; row < 9; row++)
      for (int col = 0; col < 9; col++)
	for (int n = 1; n <= 9; n++)
	  if (grid.isPencilSet(row, col, n) &&
	      !conflictingNumber(grid, row, col, n) &&
	      (numPencilsInRow(grid, row, n) == 1 ||
	       numPencilsInColumn(grid, col, n) == 1 ||
	       numPencilsInBlock(grid, row, col, n) == 1)){
	    grid.clearAllPencils(row, col);
	    grid.setNumber(row,col,n);
	    grid.setSolved(row,col);
	    changed = true;
	    break;
	  }
  } while(changed);
}

bool findUnassignedLocation(SudokuGrid& grid, int& row, int& col){
  for(int r = 0; r < 9; r++)
    for(int c = 0; c < 9; c++)
      if(grid.number(r,c) == 0){
	row = r;
	col = c;
	return true;
      }
  return false;
}

bool solveSudoku(SudokuGrid& grid){
  int row, col;
  if(!findUnassignedLocation(grid, row, col))
    return true; // puzzle filled, solution found!
  for (int num = 1; num <= 9; num++)
    if (!conflictingNumber(grid, row, col, num)){
      grid.setNumber(row, col, num); // try next number
      if (solveSudoku(grid))
	return true; // solved!
      grid.setNumber(row, col, 0); // not solved, clear number
    }
  return false; // not solved, back track
}

void printSudoku(SudokuGrid &grid){
  for (int i = 0; i < 9; i++){
    if (i % 3 == 0 && i != 0)
      std::cout << "---+---+---\n";
    for (int j = 0; j < 9; j++){
      if (j % 3 == 0 && j != 0)
	std::cout << '|';
      if (grid.number(i,j) == 0)
	std::cout << '.';
      if (grid.number(i,j) != 0)
	std::cout << grid.number(i,j);
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

int main(int argc, char *argv[]){
  std::string puzzle;
  std::cin >> puzzle;
  if((int)puzzle.length() != 81){
    std::cout << "Error: Invalid Puzzle Length.\n";
    std::exit(EXIT_FAILURE);
  }
  SudokuGrid grid(puzzle);
  printSudoku(grid);
  deduce(grid);
  printSudoku(grid);
  solveSudoku(grid);
  printSudoku(grid);
  return 0;
}
