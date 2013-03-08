------------------------------------------------------------------------
# Sudoku Puzzle Solver
------------------------------------------------------------------------
##Summary

A program which solve Sudoku puzzle. It also calculates difficulty
of the puzzle. It calculates depth, normal width, and average width.
Adopted algorithms are simple pencil marks and recursive backtracking.
Recursive call is performed on a cell which has the smallest number
of candidates (pencil marks).

Depth is the smallest number of recursive call to confirm that the
puzzle has unique solution.

Normal width is the number of recursive call to confirm that the
puzzle has a unique solution. If there are two ore more cells which
has the smallest number of candidates, pick up a cell with top-left
order.

Average width is the number of recursive call to confirm that the
puzzle has a unique solution. If there are two ore more cells which
has the smallest number of candidates, pick up a cell randomly.
100 independent tries are performed to calculate its width.
Since the average width is an estimated value, statistical error
is given.

------------------------------------------------------------------------
##Usage

    $ make
    $ ./solver sample01.dat
	Solved! Depth = 9
    This puzzle has 1 answer[s].
    5 4 8 9 1 6 3 2 7 
    1 9 7 2 4 3 5 8 6 
    6 2 3 5 8 7 1 4 9
    4 7 6 1 3 9 2 5 8 
    3 1 9 8 2 5 6 7 4 
    8 5 2 7 6 4 9 3 1 
    7 3 4 6 5 1 8 9 2 
    9 8 1 3 7 2 4 6 5 
    2 6 5 4 9 8 7 1 3 
    
    Depth = 5
    Normal Width 806
    Average Width 471.720000 +- 14.014093
------------------------------------------------------------------------
