------------------------------------------------------------------------
# Sudoku Puzzle Maker
------------------------------------------------------------------------
## Summary

A program which creates Sudoku puzzles using Replica-Exchange Monte
Carlo method. It requires MPI library to build. But it is easy to
remove MPI, since MPI is used only for the trivial parallelization.

------------------------------------------------------------------------
## Usage

    $ make
    $ mpirun -np 1 ./maker

-----------------------------------------------------------------------
