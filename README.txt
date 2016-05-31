Sudoku Solver
CS 355
Christopher Nelson
christopher.w.nelso@email.wsu.edu

Description:
  A Sudoku puzzle solver that uses backtracking.
  Before backtracking, the program attempts to 
  reduce the search space by solving for some 
  of the numbers by located "naked singles".
  The program should be able to solve each of
  the provided puzzles.

Building:
  The source is written in C++11 and requires
  a C++ compiler of recent vintage.

  make	# builds 'solvesudoku' app
  make clean # deletes build riffraff

Running:
  The program reads a 81 character string from stdin
  that describes the input puzzle in row-major order.
  Each character in the string is either a dot '.' or
  a digit for an empty space or initial number respectively.
  'simple.txt' and 'hard.txt' contain a list of puzzles.
  To run the program using the 13th puzzle from "hard.txt",
  do the following:

        sed -n "13p" hard.txt | ./solvesudoku 

  The program will print the  original puzzle, the
  puzzle with deduced numbers, and then the final
  solved puzzle.

Files in archive:

README.txt ........... This file
Makefile ............. make builds solvesudoku app
SudokuGrid.h ......... SudokuGrid class definition
simple.txt ........... Some "simple" sudoku puzzles
hard.txt ............. Some "hard" sudoku puzzles
solvesudoku.cpp ...... solver source file

