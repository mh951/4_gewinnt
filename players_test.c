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

// set the name of the winner here.
// (we don't need it in tests).
char winner;

// check which player has the turn.
// (we don't need it in tests).
int turn = 0;

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

    // check player_X.
    player_X(4);
    assert(matrix[6][4] == 'X');
    assert(matrix[5][4] == ' ');
    player_X(4);
    assert(matrix[5][4] == 'X');
    player_X(4);
    player_X(4);
    player_X(4);
    player_X(4);
    assert(matrix[1][4] == 'X');
    assert(!player_X(4));
    make_free();

/**************************************/

    // check player_O.
    player_O(2);
    assert(matrix[6][2] == 'O');
    assert(matrix[5][2] == ' ');
    player_O(2);
    assert(matrix[5][2] == 'O');
    player_O(2);
    player_O(2);
    player_O(2);
    player_O(2);
    assert(matrix[1][2] == 'O');
    assert(!player_O(2));
    make_free();
return 0;
}
