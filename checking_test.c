// Copyright 2019 Mohamad Hamdo
// proglang.informatik.uni-freiburg.de/teaching/advanced-programming/2019/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>

#include "players.h"
#include "checking.h"
#include "artificial_intelligence.h"
#include "main_4.h"

#define COLUMNS 7
#define LINES 6

// create an empty battlefield to test the functions.
char matrix[LINES + 1][COLUMNS + 1];

// make the matrix free after every test.
int make_free() {
    for (int i = 1; i <= LINES; i++) {
        for (int j = 1; j <= COLUMNS; j++) {
            matrix[i][j] = ' ';
        }
    }
}

int main() {
    make_free();

    // test check_line
    matrix[3][3] = 'X';
    matrix[3][4] = 'X';
    matrix[3][5] = 'X';
    matrix[3][6] = 'X';
    assert(check_line(3, 'X'));
    make_free();

/***************************************/

    // test check_column
    matrix[5][4] = 'O';
    matrix[4][4] = 'O';
    matrix[3][4] = 'O';
    matrix[2][4] = 'O';
    assert(check_column(4, 'O'));
    make_free();

/***************************************/

    // test check_first_diagonal
    matrix[1][1] = 'X';
    matrix[2][2] = 'X';
    matrix[3][3] = 'X';
    matrix[4][4] = 'X';
    assert(check_first_diagonal(1, 1, 'X'));
    make_free();

/***************************************/

    // test check_second_diagonal
    matrix[1][6] = 'O';
    matrix[2][5] = 'O';
    matrix[3][4] = 'O';
    matrix[4][3] = 'O';
    assert(check_second_diagonal(1, 6, 'O'));
    make_free();

/***************************************/

    // test check_winner
    matrix[1][5] = 'X';
    matrix[2][5] = 'X';
    matrix[3][5] = 'X';
    matrix[4][5] = 'X';
    check_column(5, 'X');
    assert(check_winner(5, 1, 'X'));
    make_free();

/***************************************/

    // test check_tie
    // fill the entire battlefield with X and O
    int turn = 0;
    for (int i = 1; i <= LINES; i++) {
        for (int j = 1; j <= COLUMNS; j++) {
            turn++;
            if (turn % 2 == 0) {
                matrix[i][j] = 'X';
            } else if (turn % 2 == 1) {
                matrix[i][j] = 'O';
            }
        }
    }
    assert(check_tie());
    make_free();
return 0;
}
