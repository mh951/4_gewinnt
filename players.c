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


// turn of the player X
// return 0 in case of wrong input, or the columns is full
// return 1 in case of vaild input
int player_X(int input_value) {
    // check that the input is a number between 1 and 7
    if (!(input_value >= 1 && input_value <= COLUMNS)) {
        printf("please enter a number between 1 and %d\n", COLUMNS);
        // return 0, in case of wrong input
        return 0;
    }
    // we need it to check if there is 4-same symbols
    int current_line;
    // fill the lowest empty filed with X
    for (int i = LINES; i >= 0; i--) {
            // check if the field is empty
            if (isspace(matrix[i][input_value])) {
                matrix[i][input_value] = 'X';
                current_line = i;
                break;
            }
            // check if there is not any empty field in the column
            if (i == 0) {
                printf("All the fields in this column are already full\n");
                return 0;
            }
    }
    // check if there is a winner
    if (check_winner(input_value, current_line, 'X')) {
        winner = 'X';
        return 1;
    }
    // the other player's turn
    turn++;
    // return 1, in case the input is vaild
    return 1;
}

// turn of the player O
// return 0 in case of wrong input, or the columns is full
// return 1 in case of vaild input
int player_O(int input_value) {
    // check that the input is a number between 1 and 7
    if (!(input_value >= 1 && input_value <= COLUMNS)) {
        printf("please enter a number between 1 and %d\n", COLUMNS);
        // return 0 , in case of wrong input
        return 0;
    }
    // we need it to check if there is 4-same symbols
    int current_line;
    // fill the lowest empty filed with O
    for (int i = LINES; i >= 0; i--) {
            // check if the field is empty
            if (isspace(matrix[i][input_value])) {
                matrix[i][input_value] = 'O';
                current_line = i;
                break;
            }
            // check if there is not any empty field in the column
            if (i == 0) {
                printf("All the fields in this column are already full\n");
                return 0;
            }
    }
    // check if there is a winner
    if (check_winner(input_value, current_line, 'O')) {
        winner = 'O';
        return 1;
    }
    // the other player's turn
    turn++;
    // return 1, in case the input is vaild
    return 1;
}
