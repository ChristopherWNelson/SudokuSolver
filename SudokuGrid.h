#ifndef SUDOKUGRID_H
#define SUDOKUGRID_H

#include <bitset>
#include <array>

class SudokuGrid {
 private:
  struct Cell{
    int value;
    std::bitset<9> pencils; // value 0..8 represents pencils 1..9
    bool isSolved;
    bool isFixed;
  };
  std::array<std::array<Cell,9>,9> grid; // sudoku grid
 public:
  SudokuGrid(std::string s){
    int n = 0;
    for(int i = 0; i < 9; i++){
      for (int j = 0; j < 9; j++){
	if(s[n] == '.'){
	  grid[i][j].value = 0;
	  grid[i][j].isSolved = false;
	  grid[i][j].isFixed = false;
	}
	else{
	  grid[i][j].value = (int)s[n]-'0';
	  grid[i][j].isSolved = true;
	  grid[i][j].isFixed = true;
	}
	n++;
      }
    }
  }
  int number(int row, int col) const{return grid[row][col].value;}
  void setNumber(int row, int col, int num){grid[row][col].value = num;}
  bool isFixed(int row, int col) const{return grid[row][col].isFixed;}
  bool isSolved(int row, int col) const{return grid[row][col].isSolved;}
  void setSolved(int row, int col){grid[row][col].isSolved = true;}
  bool isPencilSet(int row, int col, int n) const{
    int i = n-1;
    return grid[row][col].pencils[i];}
  bool anyPencilsSet(int row, int col) const{
    grid[row][col].pencils.any();
  }
  void setPencil(int row, int col, int n){
    int i = n-1;
    grid[row][col].pencils[i] = true;}
  void setAllPencils(int row, int col){
    for(int i = 0; i < 9; i++)
      grid[row][col].pencils[i] = true;
  }
  void clearPencil(int row, int col, int n){
    int i = n-1;
    grid[row][col].pencils[i] = false;}
  void clearAllPencils(int row, int col){
    grid[row][col].pencils.reset();
  }
};

#endif
