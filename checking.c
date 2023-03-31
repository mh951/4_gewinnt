// Copyright 2019 Mohamad Hamdo
// proglang.informatik.uni-freiburg.de/teaching/advanced-programming/2019/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include "players.h"
#include "checking.h"
#include "artificial_intelligence.h"
#include "main_4.h"


// check if there are 4 same symbols in order in the same line
// return 1, if there is 4-same symbols in any line.
// return 0, if not.
int check_line(int current_line, char symbol) {
    // the number of the same symbol
    int counter = 0;
    for (int i = 1; i <= COLUMNS; i++) {
        if (matrix[current_line][i] == symbol) {
            counter++;
            if (counter == 4) {
                return 1;
            }
        } else {
            counter = 0;
        }
    }
    return 0;
}


// check if there are 4 same symbols in order in the same column.
// return 1, if there is 4-same symbols in any column.
// return 0, if not.
int check_column(int current_column, char symbol) {
    // the number of the same symbol
    int counter = 0;
    for (int i = 1; i <= LINES; i++) {
        if (matrix[i][current_column] == symbol) {
            counter++;
            if (counter == 4) {
                return 1;
            }
        } else {
            counter = 0;
        }
    }
    return 0;
}


// check if there is 4-same symbols in order in
// first type of diagonals (up left) to (down right).
// return 1, if there is 4-same symbols in any diagonal.
// return 0, if not.
int check_first_diagonal(int current_line, int current_column, char symbol) {
    int lowest_line;
    int lowest_column;
    // go to the start of the diagonal (lowest line and lowest column).
    for (int i = current_line, j = current_column; i >= 1, j >= 1; i--, j--) {
        lowest_line = i;
        lowest_column = j;
    }
    // check the diagonal
    int counter = 0;
    for (int i = lowest_line, j = lowest_column; i <= LINES, j <= COLUMNS;
                                                                i++, j++) {
        if (matrix[i][j] == symbol) {
            counter++;
            if (counter == 4) {
                return 1;
            }
        } else {
            counter = 0;
        }
    }
    return 0;
}


// check if there is 4-same symbols in order in
// first type of diagonals (up right) to (down left).
// return 1, if there is 4-same symbols in any diagonal.
// return 0, if not.
int check_second_diagonal(int current_line, int current_column, char symbol) {
    int lowest_line;
    int heighest_column;
    // go to the start of the diagonal (lowest line and heighest column).
    for (int i = current_line, j = current_column;
                i >= 1, j <= COLUMNS; i--, j++) {
        lowest_line = i;
        heighest_column = j;
    }
    // check the diagonal
    int counter = 0;
    for (int i = lowest_line, j = heighest_column;
                    i <= LINES, j >= 1; i++, j--) {
        if (matrix[i][j] == symbol) {
            counter++;
            if (counter == 4) {
                return 1;
            }
        } else {
            counter = 0;
        }
    }
    return 0;
}


// check if there is a winner
// return 1, if there is a winner.
// return 0, if not.
int check_winner(int current_column, int current_line, char symbol) {
    // check every function which check if there is a winner
    if ((check_line(current_line, symbol)) ||
       (check_column(current_column, symbol)) ||
        check_first_diagonal(current_line, current_column, symbol) ||
        check_second_diagonal(current_line, current_column, symbol)) {
           return 1;
       } else {
        return 0;
    }
}


// check if the matrix is full, so it is tie.
// return 1, if it is tie.
// return 0, if not.
int check_tie() {
    for (int i = 1; i <= LINES; i++) {
        for (int j = 1; j<= COLUMNS; j++) {
            if (isspace(matrix[i][j])) {
                return 0;
            }
        }
    }
    return 1;
}
