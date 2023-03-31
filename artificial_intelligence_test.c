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

// check which player has the turn.
// (we don't need it in tests).
extern int turn = 0;

// if computer is 0, play with friend
// if computer is 1, play with computer.
// (we don't need it in tests).
extern int computer_won = 0;

// set the name of the winner here
// (we don't need it in tests).
char winner;

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

    // test find_chance.
    matrix[6][2] = 'O';
    matrix[6][3] = 'O';
    matrix[6][4] = 'O';
    assert(matrix[6][1] == ' ');
    assert(find_chance());
    assert(matrix[6][1] == 'O');
    make_free();

/****************************************/

    // test fine_line.
    matrix[5][1] = 'O';
    matrix[5][3] = 'O';
    matrix[5][4] = 'O';
    matrix[6][2] = 'X';
    assert(matrix[5][2] == ' ');
    find_line();
    assert(matrix[5][2] == 'O');
    make_free();

/****************************************/

    // test find_column.
    matrix[2][4] = 'O';
    matrix[3][4] = 'O';
    matrix[4][4] = 'O';
    assert(matrix[1][4] == ' ');
    find_column();
    assert(matrix[1][4] == 'O');
    make_free();

/****************************************/

    // test find_diagonal_left.
    matrix[3][2] = 'O';
    matrix[4][3] = 'O';
    matrix[5][4] = 'O';
    assert(matrix[6][5] == ' ');
    find_diagonal_left();
    assert(matrix[6][5] == 'O');
    make_free();

/****************************************/

    // test find_diagonal_right.
    matrix[3][5] = 'O';
    matrix[4][4] = 'O';
    matrix[5][3] = 'O';
    assert(matrix[6][2] == ' ');
    find_diagonal_right();
    assert(matrix[6][2] == 'O');
    make_free();


/****************************************/
/****************************************/
/****************************************/
/****************************************/

    // test block_opponent.
    matrix[6][4] = 'X';
    matrix[6][5] = 'X';
    matrix[6][6] = 'X';
    assert(matrix[6][3] == ' ');
    block_opponent();
    assert(matrix[6][3] == 'O');
    make_free();

/****************************************/

    // test block_line.
    matrix[3][5] = 'X';
    matrix[3][4] = 'X';
    matrix[3][2] = 'X';
    matrix[4][3] = 'X';
    assert(matrix[3][3] == ' ');
    block_line();
    assert(matrix[3][3] == 'O');
    make_free();

/****************************************/

    // test block_column.
    matrix[6][7] = 'X';
    matrix[5][7] = 'X';
    matrix[4][7] = 'X';
    assert(matrix[3][7] == ' ');
    block_column();
    assert(matrix[3][7] == 'O');
    make_free();

/****************************************/

    // test block_diagonal_left.
    matrix[3][3] = 'X';
    matrix[4][4] = 'X';
    matrix[5][5] = 'X';
    assert(matrix[6][6] == ' ');
    block_diagonal_left();
    assert(matrix[6][6] == 'O');
    make_free();

/****************************************/

    // test block_diagonal_right.
    matrix[1][5] = 'X';
    matrix[2][4] = 'X';
    matrix[3][3] = 'X';
    matrix[5][2] = 'X';
    assert(matrix[4][2] == ' ');
    block_2_diagonal_right();
    assert(matrix[4][2] == 'O');
    make_free();

/****************************************/
/****************************************/
/****************************************/
/****************************************/

    // test play_somthing.
    matrix[6][1] = 'O';
    matrix[6][2] = 'O';
    assert(matrix[6][3] == ' ');
    play_somthing();
    assert(matrix[6][3] == 'O');
    make_free();

/****************************************/

    // test play_2.
    matrix[6][2] = 'O';
    matrix[6][3] = 'O';
    assert(matrix[6][1] == ' ');
    play_2();
    assert(matrix[6][1] == 'O');
    make_free();

/****************************************/

    // test play_2_lines.
    matrix[2][2] = 'O';
    matrix[2][3] = 'O';
    matrix[3][1] = 'X';
    assert(matrix[2][1] == ' ');
    play_2_lines();
    assert(matrix[2][1] == 'O');
    make_free();

/****************************************/

    // test play_2_columns.
    matrix[6][3] = 'O';
    matrix[5][3] = 'O';
    assert(matrix[4][3] == ' ');
    play_2_columns();
    assert(matrix[4][3] == 'O');
    make_free();

/****************************************/

    // test play_2_diagonal_left.
    matrix[4][4] = 'O';
    matrix[5][5] = 'O';
    assert(matrix[6][6] == ' ');
    play_2_diagonal_left();
    assert(matrix[6][6] == 'O');
    make_free();

/****************************************/

    // test play_2_diagonal_right.
    matrix[2][4] = 'O';
    matrix[3][3] = 'O';
    matrix[5][2] = 'X';
    assert(matrix[4][2] == ' ');
    play_2_diagonal_right();
    assert(matrix[4][2] == 'O');
    make_free();

/****************************************/
/****************************************/
/****************************************/
/****************************************/

    // test block_2().
    matrix[6][2] = 'X';
    matrix[6][3] = 'X';
    assert(matrix[6][1] == ' ');
    block_2();
    assert(matrix[6][1] == 'O');
    make_free();

/****************************************/

    // test block_2_lines.
    matrix[2][2] = 'X';
    matrix[2][3] = 'X';
    matrix[3][1] = 'O';
    assert(matrix[2][1] == ' ');
    block_2_lines();
    assert(matrix[2][1] == 'O');
    make_free();

/****************************************/

    // test block_2_columns.
    matrix[6][3] = 'X';
    matrix[5][3] = 'X';
    assert(matrix[4][3] == ' ');
    block_2_columns();
    assert(matrix[4][3] == 'O');
    make_free();


/****************************************/

    // test block_2_diagonal_left.
    matrix[4][4] = 'X';
    matrix[5][5] = 'X';
    assert(matrix[6][6] == ' ');
    block_2_diagonal_left();
    assert(matrix[6][6] == 'O');
    make_free();

/****************************************/

    // test block_2_diagonal_right.
    matrix[2][4] = 'X';
    matrix[3][3] = 'X';
    matrix[5][2] = 'O';
    assert(matrix[4][2] == ' ');
    block_2_diagonal_right();
    assert(matrix[4][2] == 'O');
    make_free();

/****************************************/
/****************************************/
/****************************************/
/****************************************/

    // test player_COM.
    matrix[6][7] = 'O';
    matrix[6][6] = 'O';
    matrix[6][5] = 'O';
    assert(matrix[6][4] = ' ');
    player_COM();
    assert(matrix[6][4] = 'O');
    make_free();

/****************************************/

    // test play_anything.
    assert(matrix[6][4] == ' ');
    play_anything();
    assert(matrix[6][4] == 'O');
    assert(matrix[6][3] == ' ');
    play_anything();
    assert(matrix[6][3] == 'O');
    assert(matrix[6][5] == ' ');
    play_anything();
    assert(matrix[6][5] == 'O');
    make_free();

return 0;
}
