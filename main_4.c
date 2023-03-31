// Copyright 2019 Mohamad Hamdo
// proglang.informatik.uni-freiburg.de/teaching/advanced-programming/2019/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#include "main_4.h"
#include "players.h"
#include "checking.h"
#include "artificial_intelligence.h"

#define COLUMNS 7
#define LINES 6


// matrix is the battlefield, I used +1 to start from 1, not from 0
char matrix[LINES + 1][COLUMNS + 1];

// check which player has the turn
extern int turn = 0;

// set the name of the winner here
char winner;

// if computer is 0, play with friend
// if computer is 1, play with computer.
int computer;

// is 1, when the computer win
extern int computer_won = 0;



int main(int argc, char *argv[]) {
    // check that the user inputed a vaild inputs
    if (argc >2) {
        printf("sorry, worng input\n");
        exit(1);
    }
    if (argc == 2) {
        // give informations about the game bye useing:
        // ./4 --help
        int help = strcmp(argv[1], "--help");
        // play against computer bye useing:
        // ./4 --ai
        int comp = strcmp(argv[1], "--ai");
        // if input was ./4 --help  -> the argv[1] == "--help" -> help = 0
        if (!help) {
            printf("Connect Four (also known as Captain's Mistress, Four Up,"
            " Plot Four, Find Four, Four in a Row, Four in a Line, Drop Four,"
            " and Gravitrips (in Soviet Union))\n"
            "is a two-player connection game in which the players "
            " first choose a color and then take turns dropping one colored"
            " disc from the top into a seven-column,"
            " six-row vertically suspended grid.\n The pieces fall straight"
            " down, occupying the lowest available space within the column."
            "The objective of the game is to be the first to form a"
            " horizontal, vertical, or diagonal line of four of "
            "Connect Four is a solved game. The first player can always"
            " win by one's own discs.\n playing the right moves.\n"
            "************************************************\n"
            "if you want to play against computer use:\n"
            "./4 --ai\n"
            "if you want to play against your firendf use:\n"
            "./4\n");
            return 0;
        // if the inputs was ./4 --ai  -> the argv[1] == "--comp" -> comp = 0
        } else if (!comp) {
            computer = 1;
        }
    }
    // draw the empty matrix, and fill the fields with spaces
    printf("===============================\n ");
    for (int i = 1; i <= COLUMNS; i++) {
        printf("   %d", i);
    }
    printf("\n\n");
    for (int i = 1; i <= LINES; i++) {
        printf("%d   ", i);
        for (int j = 1; j <= COLUMNS; j++) {
            matrix[i][j] = ' ';
            printf("%c   ", matrix[i][j]);
        }
        printf("\n\n");
    }
    // play against friend.
    if (!computer) {
        while (true) {
            printf("===============================\n");
            // first check if there is a place to play in the battlefield.
            if (check_tie()) {
                printf("the matrix is already full, TIE!\n");
                return 0;
            }
            // check which player has the turn.
            if (turn % 2 == 0) {
                // recive the input as string and then convert it to int
                char get[100];
                printf("player X: ");
                scanf("%s", &get);
                // convert the the string to int
                int input_value = strtol(get, 0, 10);
                if (!player_X(input_value)) {
                    continue;
                }
            } else {
                // recive the input as string and then convert it to int
                char get[100];
                printf("player O: ");
                scanf("%s", &get);
                // convert the the string to int
                int input_value = strtol(get, 0, 10);
                if (!player_O(input_value)) {
                    continue;
                }
            }
            // redraw the battlefiel after every turn.
            printf("\n\n\n\n\n\n\n\n\n\n ");
            for (int i = 0; i < COLUMNS; i++) {
            printf("   %d", i + 1);
            }
            printf("\n\n");
            for (int i = 1; i <= LINES; i++) {
                printf("%d   ", i);
                for (int j = 1; j <= COLUMNS; j++) {
                    printf("%c   ", matrix[i][j]);
                }
                printf("\n\n");
            }
            // end the game if a winner has been found.
            if (winner) {
                printf("==============================================\n");
                printf("Congratiolations!! "
                       "player %c won the game...\n", winner);
                printf("==============================================\n");
                return 0;
            }
        }
    // if computer is 1, so play against computer.
    } else {
        while (true) {
            printf("===============================\n");
            // first check if there is a place to play in the battlefield.
            if (check_tie()) {
                printf("the matrix is already full, TIE!\n");
                return 0;
            }
            // check which player has the turn.
            if (turn % 2 == 0) {
                // recive the input as string and then convert it to int
                char get[100];
                printf("player X: ");
                scanf("%s", &get);
                // convert the the string to int
                int input_value = strtol(get, 0, 10);
                if (!player_X(input_value)) {
                    continue;
                }
            } else {
                // player_COM has no "continue", because the computer
                // doesn't give worng inputs.
                player_COM();
            }
            // redraw the battlefiel after every turn.
            printf("\n\n\n\n\n\n\n\n\n\n ");
            for (int i = 0; i < COLUMNS; i++) {
            printf("   %d", i + 1);
            }
            printf("\n\n");
            for (int i = 1; i <= LINES; i++) {
                printf("%d   ", i);
                for (int j = 1; j <= COLUMNS; j++) {
                    printf("%c   ", matrix[i][j]);
                }
                printf("\n\n");
            }
            // end the game if a winner has been found.
            if (winner) {
                printf("==============================================\n");
                printf("Congratiolations!! "
                       "player %c won the game...\n", winner);
                printf("==============================================\n");
                return 0;
            }
            if (computer_won) {
                printf("==============================================\n");
                printf("Sorry, the computer defeated you :(\n");
                printf("==============================================\n");
                return 0;
            }
        }
    }
}
