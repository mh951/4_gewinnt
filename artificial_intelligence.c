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


// check the lines to see if the computer can win with one move
// return 1, when it finds a chance to win and play it.
// return 0, when it doesn't find a chance.
int find_line() {
    // check all lines
    for (int i = 1; i <= LINES; i++) {
        // split every line to 3 pieces, every piece is 4 fields.
        for (int piece = 1; piece <= 4; piece++) {
            // count how many spaces in same piece.
            int space_counter = 0;
            // count how many same symbols in same piece.
            int symbol_counter = 0;
            // save the coordinates of the empty field.
            int space_i, space_j;
            // check the next piece in same line.
            for (int j = piece; j <= piece + 3; j++) {
                if (matrix[i][j] == 'O') {
                    symbol_counter++;
                } else if (isspace(matrix[i][j])) {
                    space_counter++;
                    space_i = i;
                    space_j = j;
                    // if there was 2 or more spaces in same piece, break.
                    if (space_counter >= 2) {
                        break;
                    }
                // if there was another symbol in same piece, break.
                } else if (matrix[i][j] == 'X') {
                    break;
                }
                // if we have 3 same symbols and one empty field in same,
                // piece put a symbole in the empty field.
                if (symbol_counter == 3 && space_counter == 1) {
                    // if it was in the last line (line 6), put it directly.
                    if (i == 6) {
                        matrix[space_i][space_j] = 'O';
                        return 1;
                    // if it was not the last line, check if there was a
                    // non-empty field down of it, if yes, put the symbol
                    // there.
                    } else if (i < 6) {
                        if (isalpha(matrix[space_i+1][space_j])) {
                            matrix[space_i][space_j] = 'O';
                            return 1;
                        }
                    }
                }
            }
        }
    }
    // return 0, if did not find any direct win in same line.
    return 0;
}


// check the columns to see if the computer can win with one move.
// return 1, when it finds a chance to win and play it.
// return 0, when it doesn't find a chance.
int find_column() {
    // start counting from left down of battlefield
    for (int j = 1; j <= COLUMNS; j++) {
        // the number of the same symbol,
        // counter becomes 0 after every end of column.
        int counter = 0;
        for (int i = LINES; i >= 1; i--) {
            if (matrix[i][j] == 'O') {
                counter++;
                // if it found 3-symbols in order.
                if (counter == 3) {
                    // check that this is not the last line (so not line 1)
                    // (we can not put up that).
                    if (i != 1) {
                        // if it was empty, put the symbol in it.
                        if (isspace(matrix[i-1][j])) {
                            matrix[i-1][j] = 'O';
                            return 1;
                        }
                    }
                }
            // make the value of the counter to 0 back, if there was no same
            // 3-symbols in order.
            } else {
                counter = 0;
            }
        }
    }
    // return 0, if did not find any direct win in same column.
    return 0;
}


// check if there is a chance to win by checking the first type of diagonals
// (up left to down right).
// return 1, when it finds a chance to win and play it.
// return 0, when it doesn't find a chance.
int find_diagonal_left() {
    // in this function there is 6 possible diagonals, in which can
    // 4-same-symbols in order to be in..
    // we started with the first 3 of the 6 diagonals, which they start with:
    // matrix[3][1]
    // matrix[2][1]
    // matrix[1][1]
    // piece is the possible 4-symbole pieces in every diagonal
    for (int li = 3, piece = 1; li >= 1; li--, piece++) {
        // every diagonal has a specific number of pieces
        for (int times = 0; times < piece; times++) {
            // count how many spaces in same piece.
            int space_counter = 0;
            // count how many same symbols in same piece.
            int symbol_counter = 0;
            // save the coordinates of the empty field.
            int space_i, space_j;
            // check the next piece in same diagonal.
            for (int i = li + times, j = 1 + times; i <= li + times + 3;
                                                            i++, j++) {
                if (matrix[i][j] == 'O') {
                    symbol_counter++;
                // if there was another symbol in same piece, break.
                } else if (matrix[i][j] == 'X') {
                    break;
                // if there was 2 or more spaces in same piece, break.
                } else if (isspace(matrix[i][j])) {
                    space_counter++;
                    space_i = i;
                    space_j = j;
                    if (space_counter >= 2) {
                        break;
                    }
                }
                // if we have 3 same symbols and one empty field in same,
                // piece put a symbole in the empty field.
                if (symbol_counter == 3 && space_counter == 1) {
                    // if it was in the last line (line 6), put it directly.
                    if (space_i == LINES) {
                        matrix[space_i][space_j] = 'O';
                        return 1;
                    // if it was not the last line, check if there was a
                    // non-empty field down of it, if yes, put the symbol
                    // there.
                    } else if (space_i <= LINES) {
                        if (isalpha(matrix[space_i+1][space_j])) {
                            matrix[space_i][space_j] = 'O';
                            return 1;
                        }
                    }
                }
            }
        }
    }
    // now we continue with the last 3 daigonals, which they start with:
    // matrix[1][2]
    // matrix[1][3]
    // matrix[1][4]
    // piece is the possible 4-symbole pieces in every diagonal.
    for (int co = 2, piece = 3; co <= 4; co++, piece--) {
        // every diagonal has a specific number of pieces.
        for (int times = 0; times < piece; times++) {
            // count how many spaces in same piece.
            int space_counter = 0;
            // count how many same symbols in same piece.
            int symbol_counter = 0;
            // save the coordinates of the empty field.
            int space_i, space_j;
            // check the next piece in same diagonal.
            for (int i = 1 + times, j = co + times; j <= co + times + 3;
                                                            i++, j++) {
                if (matrix[i][j] == 'O') {
                    symbol_counter++;
                // if there was another symbol in same piece, break.
                } else if (matrix[i][j] == 'X') {
                    break;
                // if there was 2 or more spaces in same piece, break.
                } else if (isspace(matrix[i][j])) {
                    space_counter++;
                    space_i = i;
                    space_j = j;
                    if (space_counter >= 2) {
                        break;
                    }
                }
                // if we have 3 same symbols and one empty field in same,
                // piece put a symbole in the empty field.
                if (symbol_counter == 3 && space_counter == 1) {
                    // if it was in the last line (line 6), put it directly.
                    if (space_i == LINES) {
                        matrix[space_i][space_j] = 'O';
                        return 1;
                    // if it was not the last line, check if there was a
                    // non-empty field down of it, if yes, put the symbol
                    // there.
                    } else if (space_i <= LINES) {
                        if (isalpha(matrix[space_i+1][space_j])) {
                            matrix[space_i][space_j] = 'O';
                            return 1;
                        }
                    }
                }
            }
        }
    }
    // return 0, if there is no chance to win here.
    return 0;
}


// check if there is a chance to win by checking the second type of diagonals
// (up right to down left).
// return 1, when it finds a chance to win and play it.
// return 0, when it doesn't find a chance.
int find_diagonal_right() {
    // in this function there is 6 possible diagonals, in which can
    // 4-same-symbols in order to be in..
    // we started with the first 3 of the 6 diagonals, which they start with:
    // matrix[3][7]
    // matrix[2][7]
    // matrix[1][7]
    // piece is the possible 4-symbole pieces in every diagonal.
    for (int li = 3, piece = 1; li >= 1; li--, piece++) {
        // every diagonal has a specific number of pieces.
        for (int times = 0; times < piece; times++) {
            // count how many spaces in same piece.
            int space_counter = 0;
            // count how many same symbols in same piece.
            int symbol_counter = 0;
            // save the coordinates of the empty field.
            int space_i, space_j;
            // check the next piece in same diagonal.
            for (int i = li + times, j = 7 - times; i <= li + times + 3;
                                                            i++, j--) {
                if (matrix[i][j] == 'O') {
                    symbol_counter++;
                // if there was another symbol in same piece, break.
                } else if (matrix[i][j] == 'X') {
                    break;
                // if there was 2 or more spaces in same piece, break.
                } else if (isspace(matrix[i][j])) {
                    space_counter++;
                    space_i = i;
                    space_j = j;
                    if (space_counter >= 2) {
                        break;
                    }
                }
                // if we have 3 same symbols and one empty field in same,
                // piece put a symbole in the empty field.
                if (symbol_counter == 3 && space_counter == 1) {
                    // if it was in the last line (line 6), put it directly.
                    if (space_i == LINES) {
                        matrix[space_i][space_j] = 'O';
                        return 1;
                    // if it was not the last line, check if there was a
                    // non-empty field down of it, if yes, put the symbol
                    // there.
                    } else if (space_i <= LINES) {
                        if (isalpha(matrix[space_i+1][space_j])) {
                            matrix[space_i][space_j] = 'O';
                            return 1;
                        }
                    }
                }
            }
        }
    }
    // now we continue with the last 3 daigonals, which they start with:
    // matrix[1][6]
    // matrix[1][5]
    // matrix[1][4]
    // piece is the possible 4-symbole pieces in every diagonal
    for (int co = 6, piece = 3; co >= 4; co--, piece--) {
        // every diagonal has a specific number of pieces
        for (int times = 0; times < piece; times++) {
            // count how many spaces in same piece.
            int space_counter = 0;
            // count how many same symbols in same piece.
            int symbol_counter = 0;
            // save the coordinates of the empty field.
            int space_i, space_j;
            // check the next piece in same diagonal.
            for (int i = 1 + times, j = co - times; j >= co - times - 3;
                                                            i++, j--) {
                if (matrix[i][j] == 'O') {
                    symbol_counter++;
                // if there was another symbol in same piece, break.
                } else if (matrix[i][j] == 'X') {
                    break;
                // if there was 2 or more spaces in same piece, break.
                } else if (isspace(matrix[i][j])) {
                    space_counter++;
                    space_i = i;
                    space_j = j;
                    if (space_counter >= 2) {
                        break;
                    }
                }
                // if we have 3 same symbols and one empty field in same,
                // piece put a symbole in the empty field.
                if (symbol_counter == 3 && space_counter == 1) {
                    // if it was in the last line (line 6), put it directly.
                    if (space_i == LINES) {
                        matrix[space_i][space_j] = 'O';
                        return 1;
                    // if it was not the last line, check if there was a
                    // non-empty field down of it, if yes, put the symbol
                    // there.
                    } else if (space_i <= LINES) {
                        if (isalpha(matrix[space_i+1][space_j])) {
                            matrix[space_i][space_j] = 'O';
                            return 1;
                        }
                    }
                }
            }
        }
    }
    // return 0, if there is no chance to win here.
    return 0;
}


// check the lines and find a chance to win the opponent with one move,
// and block it.
// return 1, when it blocks the opponent.
// return 0, when nothing to block.
int block_line() {
    // check all lines
    for (int i = 1; i <= LINES; i++) {
        // split every line to pieces, every piece is 4 fields.
        for (int piece = 1; piece <= 4; piece++) {
            // count how many spaces in same piece.
            int space_counter = 0;
            // count how many same symbols in same piece.
            int symbol_counter = 0;
            // save the coordinates of the empty field.
            int space_i, space_j;
            // check the next piece in same line.
            for (int j = piece; j <= piece + 3; j++) {
                if (matrix[i][j] == 'X') {
                    symbol_counter++;
                } else if (isspace(matrix[i][j])) {
                    space_counter++;
                    space_i = i;
                    space_j = j;
                    // if there was 2 or more spaces in same piece, break.
                    if (space_counter >= 2) {
                        break;
                    }
                // if there was another symbol in same piece, break.
                } else if (matrix[i][j] == 'O') {
                    break;
                }
                // if we have 3 same symbols and one empty field in same,
                // piece put a symbole in the empty field.
                if (symbol_counter == 3 && space_counter == 1) {
                    // if it was in the last line (line 6), put it directly.
                    if (i == 6) {
                        matrix[space_i][space_j] = 'O';
                        return 1;
                    // if it was not the last line, check if there was a
                    // non-empty field down of it, if yes, put the symbol
                    // there.
                    } else if (i < 6) {
                        if (isalpha(matrix[space_i+1][space_j])) {
                            matrix[space_i][space_j] = 'O';
                            return 1;
                        }
                    }
                }
            }
        }
    }
    // return 0, if did not find anything to block in same line.
    return 0;
}


// check the columns and find a chance to win the opponent with one move,
// and block it.
// return 1, when it blocks the opponent.
// return 0, when nothing to block.
int block_column() {
    // start counting from left down of battlefield.
    for (int j = 1; j <= COLUMNS; j++) {
        // the number of the same symbol.
        // counter becomes 0 after every end of column.
        int counter = 0;
        for (int i = LINES; i >= 1; i--) {
            if (matrix[i][j] == 'X') {
                counter++;
                // if it found 3-symbols in order.
                if (counter == 3) {
                    // check that this is not the last line (so not line 1)
                    // (we can not put up that).
                    if (i != 1) {
                        // if it was empty, put the symbol in it.
                        if (isspace(matrix[i-1][j])) {
                            matrix[i-1][j] = 'O';
                            return 1;
                        }
                    }
                }
            // make the value of the counter to 0 back, if there was no same
            // 3-symbols in order.
            } else {
                counter = 0;
            }
        }
    }
    // return 0, if did not find anything to block in same column.
    return 0;
}


// check the first type of diagonals (up left to down right), and find if
// there is a chance to win the opponent, and block it.
// return 1, when it blocks the opponent.
// return 0, when nothing to block.
int block_diagonal_left() {
    // in this function there is 6 possible diagonals, in which can
    // 4-same-symbols in order to be in..
    // we started with the first 3 of the 6 diagonals, which they start with:
    // matrix[3][1]
    // matrix[2][1]
    // matrix[1][1]
    // piece is the possible 4-symbole pieces in every diagonal.
    for (int li = 3, piece = 0; li >= 1; li--, piece++) {
        // every diagonal has a specific number of pieces
        for (int times = 0; times <= piece; times++) {
            // count how many spaces in same piece.
            int space_counter = 0;
            // count how many same symbols in same piece.
            int symbol_counter = 0;
            // save the coordinates of the empty field.
            int space_i, space_j;
            // check the next piece in same diagonal.
            for (int i = li + times, j = 1 + times; i <= li + times + 3;
                                                            i++, j++) {
                if (matrix[i][j] == 'X') {
                    symbol_counter++;
                // if there was another symbol in same piece, break.
                } else if (matrix[i][j] == 'O') {
                    break;
                // if there was 2 or more spaces in same piece, break.
                } else if (isspace(matrix[i][j])) {
                    space_counter++;
                    space_i = i;
                    space_j = j;
                    if (space_counter >= 2) {
                        break;
                    }
                }
                // if we have 3 same symbols and one empty field in same,
                // piece put a symbole in the empty field.
                if (symbol_counter == 3 && space_counter == 1) {
                    // if it was in the last line (line 6), put it directly.
                    if (space_i == LINES) {
                        matrix[space_i][space_j] = 'O';
                        return 1;
                    // if it was not the last line, check if there was a
                    // non-empty field down of it, if yes, put the symbol
                    // there.
                    } else if (space_i <= LINES) {
                        if (isalpha(matrix[space_i+1][space_j])) {
                            matrix[space_i][space_j] = 'O';
                            return 1;
                        }
                    }
                }
            }
        }
    }
    // now we continue with the last 3 daigonals, which they start with:
    // matrix[1][2]
    // matrix[1][3]
    // matrix[1][4]
    // piece is the possible 4-symbole pieces in every diagonal
    for (int co = 2, piece = 2; co <= 4; co++, piece--) {
        // every diagonal has a specific number of pieces
        for (int times = 0; times <= piece; times++) {
            // count how many spaces in same piece.
            int space_counter = 0;
            // count how many same symbols in same piece.
            int symbol_counter = 0;
            // save the coordinates of the empty field.
            int space_i, space_j;
            // check the next piece in same diagonal.
            for (int i = 1 + times, j = co + times; j <= co + times + 3;
                                                            i++, j++) {
                if (matrix[i][j] == 'X') {
                    symbol_counter++;
                // if there was another symbol in same piece, break.
                } else if (matrix[i][j] == 'O') {
                    break;
                // if there was 2 or more spaces in same piece, break.
                } else if (isspace(matrix[i][j])) {
                    space_counter++;
                    space_i = i;
                    space_j = j;
                    if (space_counter >= 2) {
                        break;
                    }
                }
                // if we have 3 same symbols and one empty field in same,
                // piece put a symbole in the empty field.
                if (symbol_counter == 3 && space_counter == 1) {
                    // if it was in the last line (line 6), put it directly.
                    if (space_i == LINES) {
                        matrix[space_i][space_j] = 'O';
                        return 1;
                    // if it was not the last line, check if there was a
                    // non-empty field down of it, if yes, put the symbol
                    // there.
                    } else if (space_i <= LINES) {
                        if (isalpha(matrix[space_i+1][space_j])) {
                            matrix[space_i][space_j] = 'O';
                            return 1;
                        }
                    }
                }
            }
        }
    }
    // return 0, if there is no chance for opponent to win here.
    return 0;
}


// check the second type of diagonals (up right to down left), and find if
// there is a chance to win the opponent, and block it.
// return 1, when it blocks the opponent.
// return 0, when nothing to block.
int block_diagonal_right() {
    // in this function there is 6 possible diagonals, in which can
    // 4-same-symbols in order to be in..
    // we started with the first 3 of the 6 diagonals, which they start with:
    // matrix[3][7]
    // matrix[2][7]
    // matrix[1][7]
    // piece is the possible 4-symbole pieces in every diagonal.
    for (int li = 3, piece = 0; li >= 1; li--, piece++) {
        // every diagonal has a specific number of pieces.
        for (int times = 0; times <= piece; times++) {
            // count how many spaces in same piece.
            int space_counter = 0;
            // count how many same symbols in same piece.
            int symbol_counter = 0;
            // save the coordinates of the empty field.
            int space_i, space_j;
            // check the next piece in same diagonal.
            for (int i = li + times, j = 7 - times; i <= li + times + 3;
                                                            i++, j--) {
                if (matrix[i][j] == 'X') {
                    symbol_counter++;
                // if there was another symbol in same piece, break.
                } else if (matrix[i][j] == 'O') {
                    break;
                // if there was 2 or more spaces in same piece, break.
                } else if (isspace(matrix[i][j])) {
                    space_counter++;
                    space_i = i;
                    space_j = j;
                    if (space_counter >= 2) {
                        break;
                    }
                }
                // if we have 3 same symbols and one empty field in same,
                // piece put a symbole in the empty field.
                if (symbol_counter == 3 && space_counter == 1) {
                    // if it was in the last line (line 6), put it directly.
                    if (space_i == LINES) {
                        matrix[space_i][space_j] = 'O';
                        return 1;
                    // if it was not the last line, check if there was a
                    // non-empty field down of it, if yes, put the symbol
                    // there.
                    } else if (space_i <= LINES) {
                        if (isalpha(matrix[space_i+1][space_j])) {
                            matrix[space_i][space_j] = 'O';
                            return 1;
                        }
                    }
                }
            }
        }
    }
    // now we continue with the last 3 daigonals, which they start with:
    // matrix[1][6]
    // matrix[1][5]
    // matrix[1][4]
    // piece is the possible 4-symbole pieces in every diagonal
    for (int co = 6, piece = 2; co >= 4; co--, piece--) {
        // every diagonal has a specific number of pieces
        for (int times = 0; times <= piece; times++) {
            // count how many spaces in same piece.
            int space_counter = 0;
            // count how many same symbols in same piece.
            int symbol_counter = 0;
            // save the coordinates of the empty field.
            int space_i, space_j;
            // check the next piece in same diagonal.
            for (int i = 1 + times, j = co - times; j >= co - times - 3;
                                                            i++, j--) {
                if (matrix[i][j] == 'X') {
                    symbol_counter++;
                // if there was another symbol in same piece, break.
                } else if (matrix[i][j] == 'O') {
                    break;
                // if there was 2 or more spaces in same piece, break.
                } else if (isspace(matrix[i][j])) {
                    space_counter++;
                    space_i = i;
                    space_j = j;
                    if (space_counter >= 2) {
                        break;
                    }
                }
                // if we have 3 same symbols and one empty field in same,
                // piece put a symbole in the empty field.
                if (symbol_counter == 3 && space_counter == 1) {
                    // if it was in the last line (line 6), put it directly.
                    if (space_i == LINES) {
                        matrix[space_i][space_j] = 'O';
                        return 1;
                    // if it was not the last line, check if there was a
                    // non-empty field down of it, if yes, put the symbol
                    // there.
                    } else if (space_i <= LINES) {
                        if (isalpha(matrix[space_i+1][space_j])) {
                            matrix[space_i][space_j] = 'O';
                            return 1;
                        }
                    }
                }
            }
        }
    }
    // return 0, if there is no chance for opponent to win here.
    return 0;
}


// find if there is a chance to win with one move, if yes return 1.
// return 0, if no chance.
int find_chance() {
    if (find_line() ||
        find_column() ||
        find_diagonal_left() ||
        find_diagonal_right()) {
            return 1;
        }
    return 0;
}


// if the opponent will win in one move, block him.
// return 1 if blocked, return 0 in case nothing to block.
int block_opponent() {
    if (block_line() ||
       block_column() ||
       block_diagonal_left() ||
       block_diagonal_right()) {
           return 1;
       }
       return 0;
}


// check the lines, if there is 2-same O symbols and on empty field,
// fill the empty field with O symbol.
// return 1, when it finds and and played.
// return 0, when not found or not played.
int play_2_lines() {
    // check all lines
    for (int i = 1; i <= LINES; i++) {
        // split every line to 5 pieces, every piece is 3 fields.
        for (int piece = 1; piece <= 5; piece++) {
            // count how many spaces in same piece.
            int space_counter = 0;
            // count how many same symbols in same piece.
            int symbol_counter = 0;
            // save the coordinates of the empty field.
            int space_i, space_j;
            // check the next piece in same line.
            for (int j = piece; j <= piece + 2; j++) {
                if (matrix[i][j] == 'O') {
                    symbol_counter++;
                } else if (isspace(matrix[i][j])) {
                    space_counter++;
                    space_i = i;
                    space_j = j;
                    // if there was 2 or more spaces in same piece, break.
                    if (space_counter >= 2) {
                        break;
                    }
                // if there was another symbol in same piece, break.
                } else if (matrix[i][j] == 'X') {
                    break;
                }
                // if we have 3 same symbols and one empty field in same,
                // piece put a symbole in the empty field.
                if (symbol_counter == 2 && space_counter == 1) {
                    // if it was in the last line (line 6), put it directly.
                    if (i == 6) {
                        matrix[space_i][space_j] = 'O';
                        return 1;
                    // if it was not the last line, check if there was a
                    // non-empty field down of it, if yes, put the symbol
                    // there.
                    } else if (i < 6) {
                        if (isalpha(matrix[space_i+1][space_j])) {
                            matrix[space_i][space_j] = 'O';
                            return 1;
                        }
                    }
                }
            }
        }
    }
    // return 0, if did not find any 2-same O symbol in same line,
    // or not played the third.
    return 0;
}


// check the columns, if there is 2-same O symbols and one empty filed,
// fill the empty field with O symbol.
// return 1, when it finds and and played.
// return 0, when not found or not played.
int play_2_columns() {
    // start counting from left down of battlefield
    for (int j = 1; j <= COLUMNS; j++) {
        // the number of the same symbol,
        // counter becomes 0 after every end of column.
        int counter = 0;
        for (int i = LINES; i >= 1; i--) {
            if (matrix[i][j] == 'O') {
                counter++;
                // if it found 3-symbols in order.
                if (counter == 2) {
                    // check that this is not the last line (so not line 1)
                    // (we can not put up that).
                    if (i != 1) {
                        // if it was empty, put the symbol in it.
                        if (isspace(matrix[i-1][j])) {
                            matrix[i-1][j] = 'O';
                            return 1;
                        }
                    }
                }
            // make the value of the counter to 0 back, if there was no same
            // 2-symbols in order.
            } else {
                counter = 0;
            }
        }
    }
    // return 0, if did not find any 2-same O symbol in same column,
    // or not played the third.
    return 0;
}


// check the first type of diagonals (up left to down right), if there is
// 2-same O symbols and one empty field, fill the empty field with O symbol.
// return 1, when it finds and and played.
// return 0, when not found or not played.
int play_2_diagonal_left() {
    // in this function there is 6 possible diagonals, in which can
    // 4-same-symbols in order to be in..
    // we started with the first 3 of the 6 diagonals, which they start with:
    // matrix[3][1]
    // matrix[2][1]
    // matrix[1][1]
    // piece is the possible 4-symbole pieces in every diagonal
    for (int li = 3, piece = 2; li >= 1; li--, piece++) {
        // every diagonal has a specific number of pieces
        for (int times = 0; times < piece; times++) {
            // count how many spaces in same piece.
            int space_counter = 0;
            // count how many same symbols in same piece.
            int symbol_counter = 0;
            // save the coordinates of the empty field.
            int space_i, space_j;
            // check the next piece in same diagonal.
            for (int i = li + times, j = 1 + times; i <= li + times + 2;
                                                            i++, j++) {
                if (matrix[i][j] == 'O') {
                    symbol_counter++;
                // if there was another symbol in same piece, break.
                } else if (matrix[i][j] == 'X') {
                    break;
                // if there was 2 or more spaces in same piece, break.
                } else if (isspace(matrix[i][j])) {
                    space_counter++;
                    space_i = i;
                    space_j = j;
                    if (space_counter >= 2) {
                        break;
                    }
                }
                // if we have 2 same symbols and one empty field in same,
                // piece put a symbole in the empty field.
                if (symbol_counter == 2 && space_counter == 1) {
                    // if it was in the last line (line 6), put it directly.
                    if (space_i == LINES) {
                        matrix[space_i][space_j] = 'O';
                        return 1;
                    // if it was not the last line, check if there was a
                    // non-empty field down of it, if yes, put the symbol
                    // there.
                    } else if (space_i <= LINES) {
                        if (isalpha(matrix[space_i+1][space_j])) {
                            matrix[space_i][space_j] = 'O';
                            return 1;
                        }
                    }
                }
            }
        }
    }
    // now we continue with the last 3 daigonals, which they start with:
    // matrix[1][2]
    // matrix[1][3]
    // matrix[1][4]
    // piece is the possible 4-symbole pieces in every diagonal.
    for (int co = 2, piece = 4; co <= 4; co++, piece--) {
        // every diagonal has a specific number of pieces.
        for (int times = 0; times < piece; times++) {
            // count how many spaces in same piece.
            int space_counter = 0;
            // count how many same symbols in same piece.
            int symbol_counter = 0;
            // save the coordinates of the empty field.
            int space_i, space_j;
            // check the next piece in same diagonal.
            for (int i = 1 + times, j = co + times; j <= co + times + 2;
                                                            i++, j++) {
                if (matrix[i][j] == 'O') {
                    symbol_counter++;
                // if there was another symbol in same piece, break.
                } else if (matrix[i][j] == 'X') {
                    break;
                // if there was 2 or more spaces in same piece, break.
                } else if (isspace(matrix[i][j])) {
                    space_counter++;
                    space_i = i;
                    space_j = j;
                    if (space_counter >= 2) {
                        break;
                    }
                }
                // if we have 2 same symbols and one empty field in same,
                // piece put a symbole in the empty field.
                if (symbol_counter == 2 && space_counter == 1) {
                    // if it was in the last line (line 6), put it directly.
                    if (space_i == LINES) {
                        matrix[space_i][space_j] = 'O';
                        return 1;
                    // if it was not the last line, check if there was a
                    // non-empty field down of it, if yes, put the symbol
                    // there.
                    } else if (space_i <= LINES) {
                        if (isalpha(matrix[space_i+1][space_j])) {
                            matrix[space_i][space_j] = 'O';
                            return 1;
                        }
                    }
                }
            }
        }
    }
    // return 0, if didn't find 2-same O symbols with one empty field
    // or if found but didn't put the third O symbol.
    return 0;
}


// check the second type of diagonals (up right to down left), if there is
// 2-same O symbols and one empty field, fill the empty field with O symbol.
// return 1, when it finds and and played.
// return 0, when not found or not played.
int play_2_diagonal_right() {
    // in this function there is 6 possible diagonals, in which can
    // 4-same-symbols in order to be in..
    // we started with the first 3 of the 6 diagonals, which they start with:
    // matrix[3][7]
    // matrix[2][7]
    // matrix[1][7]
    // piece is the possible 4-symbole pieces in every diagonal.
    for (int li = 3, piece = 2; li >= 1; li--, piece++) {
        // every diagonal has a specific number of pieces.
        for (int times = 0; times < piece; times++) {
            // count how many spaces in same piece.
            int space_counter = 0;
            // count how many same symbols in same piece.
            int symbol_counter = 0;
            // save the coordinates of the empty field.
            int space_i, space_j;
            // check the next piece in same diagonal.
            for (int i = li + times, j = 7 - times; i <= li + times + 2;
                                                            i++, j--) {
                if (matrix[i][j] == 'O') {
                    symbol_counter++;
                // if there was another symbol in same piece, break.
                } else if (matrix[i][j] == 'X') {
                    break;
                // if there was 2 or more spaces in same piece, break.
                } else if (isspace(matrix[i][j])) {
                    space_counter++;
                    space_i = i;
                    space_j = j;
                    if (space_counter >= 2) {
                        break;
                    }
                }
                // if we have 2 same symbols and one empty field in same,
                // piece put a symbole in the empty field.
                if (symbol_counter == 2 && space_counter == 1) {
                    // if it was in the last line (line 6), put it directly.
                    if (space_i == LINES) {
                        matrix[space_i][space_j] = 'O';
                        return 1;
                    // if it was not the last line, check if there was a
                    // non-empty field down of it, if yes, put the symbol
                    // there.
                    } else if (space_i <= LINES) {
                        if (isalpha(matrix[space_i+1][space_j])) {
                            matrix[space_i][space_j] = 'O';
                            return 1;
                        }
                    }
                }
            }
        }
    }
    // now we continue with the last 3 daigonals, which they start with:
    // matrix[1][6]
    // matrix[1][5]
    // matrix[1][4]
    // piece is the possible 4-symbole pieces in every diagonal
    for (int co = 6, piece = 3; co >= 4; co--, piece--) {
        // every diagonal has a specific number of pieces
        for (int times = 0; times < piece; times++) {
            // count how many spaces in same piece.
            int space_counter = 0;
            // count how many same symbols in same piece.
            int symbol_counter = 0;
            // save the coordinates of the empty field.
            int space_i, space_j;
            // check the next piece in same diagonal.
            for (int i = 1 + times, j = co - times; j >= co - times - 2;
                                                            i++, j--) {
                if (matrix[i][j] == 'O') {
                    symbol_counter++;
                // if there was another symbol in same piece, break.
                } else if (matrix[i][j] == 'X') {
                    break;
                // if there was 2 or more spaces in same piece, break.
                } else if (isspace(matrix[i][j])) {
                    space_counter++;
                    space_i = i;
                    space_j = j;
                    if (space_counter >= 2) {
                        break;
                    }
                }
                // if we have 2 same symbols and one empty field in same,
                // piece put a symbole in the empty field.
                if (symbol_counter == 2 && space_counter == 1) {
                    // if it was in the last line (line 6), put it directly.
                    if (space_i == LINES) {
                        matrix[space_i][space_j] = 'O';
                        return 1;
                    // if it was not the last line, check if there was a
                    // non-empty field down of it, if yes, put the symbol
                    // there.
                    } else if (space_i <= LINES) {
                        if (isalpha(matrix[space_i+1][space_j])) {
                            matrix[space_i][space_j] = 'O';
                            return 1;
                        }
                    }
                }
            }
        }
    }
    // return 0, if didn't find 2-same O symbols with one empty field
    // or if found but didn't put the third O symbol.
    return 0;
}


// find 2 same O symobol and add the third one to them.
// return 1, if it found and added.
// return 0, if not found or not added.
int play_2() {
    if (play_2_lines() ||
        play_2_columns() ||
        play_2_diagonal_left() ||
        play_2_diagonal_right()) {
           return 1;
       }
       return 0;
}


// check the lines, if there is a 2-same X symbols in order, block them
// with O.
// return 1, when it finds and and played.
// return 0, when not found or not played.
int block_2_lines() {
    // check all lines
    for (int i = 1; i <= LINES; i++) {
        // split every line to 5 pieces, every piece is 3 fields.
        for (int piece = 1; piece <= 5; piece++) {
            // count how many spaces in same piece.
            int space_counter = 0;
            // count how many same symbols in same piece.
            int symbol_counter = 0;
            // save the coordinates of the empty field.
            int space_i, space_j;
            // check the next piece in same line.
            for (int j = piece; j <= piece + 2; j++) {
                if (matrix[i][j] == 'X') {
                    symbol_counter++;
                } else if (isspace(matrix[i][j])) {
                    space_counter++;
                    space_i = i;
                    space_j = j;
                    // if there was 2 or more spaces in same piece, break.
                    if (space_counter >= 2) {
                        break;
                    }
                // if there was another symbol in same piece, break.
                } else if (matrix[i][j] == 'O') {
                    break;
                }
                // if we have 2 same symbols and one empty field in same,
                // piece put a symbole in the empty field.
                if (symbol_counter == 2 && space_counter == 1) {
                    // if it was in the last line (line 6), put it directly.
                    if (i == 6) {
                        matrix[space_i][space_j] = 'O';
                        return 1;
                    // if it was not the last line, check if there was a
                    // non-empty field down of it, if yes, put the symbol
                    // there.
                    } else if (i < 6) {
                        if (isalpha(matrix[space_i+1][space_j])) {
                            matrix[space_i][space_j] = 'O';
                            return 1;
                        }
                    }
                }
            }
        }
    }
    // return 0, if did not find any 2-same O symbol in same line,
    // or not played O symbol.
    return 0;
}


// check the columns, if there is a 2-same X symbols in order, block them
// with O.
// return 1, when it finds and and played.
// return 0, when not found or not played.
int block_2_columns() {
    // start counting from left down of battlefield
    for (int j = 1; j <= COLUMNS; j++) {
        // the number of the same symbol,
        // counter becomes 0 after every end of column.
        int counter = 0;
        for (int i = LINES; i >= 1; i--) {
            if (matrix[i][j] == 'X') {
                counter++;
                // if it found 2-symbols in order.
                if (counter == 2) {
                    // check that this is not the last line (so not line 1)
                    // (we can not put up that).
                    if (i > 1) {
                        // if it was empty, put the symbol in it.
                        if (isspace(matrix[i-1][j])) {
                            matrix[i-1][j] = 'O';
                            return 1;
                        }
                    }
                }
            // make the value of the counter to 0 back, if there was no same
            // 2-symbols in order.
            } else {
                counter = 0;
            }
        }
    }
    // return 0, if did not find any 2-same O symbol in same column,
    // or not played O symbol.
    return 0;
}


// check the first type of diagonals (up left to down right), if there is
// 2-same X symbols and one empty field, fill the empty field with O symbol.
// return 1, when it finds and and played.
// return 0, when not found or not played.
int block_2_diagonal_left() {
    // in this function there is 6 possible diagonals, in which can
    // 4-same-symbols in order to be in..
    // we started with the first 3 of the 6 diagonals, which they start with:
    // matrix[3][1]
    // matrix[2][1]
    // matrix[1][1]
    // piece is the possible 4-symbole pieces in every diagonal
    for (int li = 3, piece = 2; li >= 1; li--, piece++) {
        // every diagonal has a specific number of pieces
        for (int times = 0; times < piece; times++) {
            // count how many spaces in same piece.
            int space_counter = 0;
            // count how many same symbols in same piece.
            int symbol_counter = 0;
            // save the coordinates of the empty field.
            int space_i, space_j;
            // check the next piece in same diagonal.
            for (int i = li + times, j = 1 + times; i <= li + times + 2;
                                                            i++, j++) {
                if (matrix[i][j] == 'X') {
                    symbol_counter++;
                // if there was another symbol in same piece, break.
                } else if (matrix[i][j] == 'O') {
                    break;
                // if there was 2 or more spaces in same piece, break.
                } else if (isspace(matrix[i][j])) {
                    space_counter++;
                    space_i = i;
                    space_j = j;
                    if (space_counter >= 2) {
                        break;
                    }
                }
                // if we have 2 same symbols and one empty field in same,
                // piece put a symbole in the empty field.
                if (symbol_counter == 2 && space_counter == 1) {
                    // if it was in the last line (line 6), put it directly.
                    if (space_i == LINES) {
                        matrix[space_i][space_j] = 'O';
                        return 1;
                    // if it was not the last line, check if there was a
                    // non-empty field down of it, if yes, put the symbol
                    // there.
                    } else if (space_i <= LINES) {
                        if (isalpha(matrix[space_i+1][space_j])) {
                            matrix[space_i][space_j] = 'O';
                            return 1;
                        }
                    }
                }
            }
        }
    }
    // now we continue with the last 3 daigonals, which they start with:
    // matrix[1][2]
    // matrix[1][3]
    // matrix[1][4]
    // piece is the possible 4-symbole pieces in every diagonal.
    for (int co = 2, piece = 4; co <= 4; co++, piece--) {
        // every diagonal has a specific number of pieces.
        for (int times = 0; times < piece; times++) {
            // count how many spaces in same piece.
            int space_counter = 0;
            // count how many same symbols in same piece.
            int symbol_counter = 0;
            // save the coordinates of the empty field.
            int space_i, space_j;
            // check the next piece in same diagonal.
            for (int i = 1 + times, j = co + times; j <= co + times + 2;
                                                            i++, j++) {
                if (matrix[i][j] == 'X') {
                    symbol_counter++;
                // if there was another symbol in same piece, break.
                } else if (matrix[i][j] == 'O') {
                    break;
                // if there was 2 or more spaces in same piece, break.
                } else if (isspace(matrix[i][j])) {
                    space_counter++;
                    space_i = i;
                    space_j = j;
                    if (space_counter >= 2) {
                        break;
                    }
                }
                // if we have 2 same symbols and one empty field in same,
                // piece put a symbole in the empty field.
                if (symbol_counter == 2 && space_counter == 1) {
                    // if it was in the last line (line 6), put it directly.
                    if (space_i == LINES) {
                        matrix[space_i][space_j] = 'O';
                        return 1;
                    // if it was not the last line, check if there was a
                    // non-empty field down of it, if yes, put the symbol
                    // there.
                    } else if (space_i <= LINES) {
                        if (isalpha(matrix[space_i+1][space_j])) {
                            matrix[space_i][space_j] = 'O';
                            return 1;
                        }
                    }
                }
            }
        }
    }
    // return 0, if didn't find 2-same X symbols with one empty field
    // or if found but didn't put the third O symbol.
    return 0;
}


// check the second type of diagonals (up right to down left), if there is
// 2-same X symbols and one empty field, fill the empty field with O symbol.
// return 1, when it finds and and played.
// return 0, when not found or not played.
int block_2_diagonal_right() {
    // in this function there is 6 possible diagonals, in which can
    // 4-same-symbols in order to be in..
    // we started with the first 3 of the 6 diagonals, which they start with:
    // matrix[3][7]
    // matrix[2][7]
    // matrix[1][7]
    // piece is the possible 4-symbole pieces in every diagonal.
    for (int li = 3, piece = 2; li >= 1; li--, piece++) {
        // every diagonal has a specific number of pieces.
        for (int times = 0; times < piece; times++) {
            // count how many spaces in same piece.
            int space_counter = 0;
            // count how many same symbols in same piece.
            int symbol_counter = 0;
            // save the coordinates of the empty field.
            int space_i, space_j;
            // check the next piece in same diagonal.
            for (int i = li + times, j = 7 - times; i <= li + times + 2;
                                                            i++, j--) {
                if (matrix[i][j] == 'X') {
                    symbol_counter++;
                // if there was another symbol in same piece, break.
                } else if (matrix[i][j] == 'O') {
                    break;
                // if there was 2 or more spaces in same piece, break.
                } else if (isspace(matrix[i][j])) {
                    space_counter++;
                    space_i = i;
                    space_j = j;
                    if (space_counter >= 2) {
                        break;
                    }
                }
                // if we have 2 same symbols and one empty field in same,
                // piece put a symbole in the empty field.
                if (symbol_counter == 2 && space_counter == 1) {
                    // if it was in the last line (line 6), put it directly.
                    if (space_i == LINES) {
                        matrix[space_i][space_j] = 'O';
                        return 1;
                    // if it was not the last line, check if there was a
                    // non-empty field down of it, if yes, put the symbol
                    // there.
                    } else if (space_i <= LINES) {
                        if (isalpha(matrix[space_i+1][space_j])) {
                            matrix[space_i][space_j] = 'O';
                            return 1;
                        }
                    }
                }
            }
        }
    }
    // now we continue with the last 3 daigonals, which they start with:
    // matrix[1][6]
    // matrix[1][5]
    // matrix[1][4]
    // piece is the possible 4-symbole pieces in every diagonal
    for (int co = 6, piece = 4; co >= 4; co--, piece--) {
        // every diagonal has a specific number of pieces
        for (int times = 0; times < piece; times++) {
            // count how many spaces in same piece.
            int space_counter = 0;
            // count how many same symbols in same piece.
            int symbol_counter = 0;
            // save the coordinates of the empty field.
            int space_i, space_j;
            // check the next piece in same diagonal.
            for (int i = 1 + times, j = co - times; j >= co - times - 2;
                                                            i++, j--) {
                if (matrix[i][j] == 'X') {
                    symbol_counter++;
                // if there was another symbol in same piece, break.
                } else if (matrix[i][j] == 'O') {
                    break;
                // if there was 2 or more spaces in same piece, break.
                } else if (isspace(matrix[i][j])) {
                    space_counter++;
                    space_i = i;
                    space_j = j;
                    if (space_counter >= 2) {
                        break;
                    }
                }
                // if we have 2 same symbols and one empty field in same,
                // piece put a symbole in the empty field.
                if (symbol_counter == 2 && space_counter == 1) {
                    // if it was in the last line (line 6), put it directly.
                    if (space_i == LINES) {
                        matrix[space_i][space_j] = 'O';
                        return 1;
                    // if it was not the last line, check if there was a
                    // non-empty field down of it, if yes, put the symbol
                    // there.
                    } else if (space_i <= LINES) {
                        if (isalpha(matrix[space_i+1][space_j])) {
                            matrix[space_i][space_j] = 'O';
                            return 1;
                        }
                    }
                }
            }
        }
    }
    // return 0, if didn't find 2-same X symbols with one empty field
    // or if found but didn't put the third O symbol.
    return 0;
}


// check the battlefield to find 2-same X symbol in order and try to block
// them with O.
// return 1, if it found and added.
// return 0, if not.
int block_2() {
    if (block_2_lines() ||
       block_2_columns() ||
       block_2_diagonal_left() ||
       block_2_diagonal_right()) {
        return 1;
    }
    return 0;
}


// try to to put the O symbol in the middle as far as possible.
// returns 1, if it played.
int play_anything() {
    for (int i = LINES; i >= 1; i--) {
        // change between right and left sides of the middle
        int change = 0;
        for (int j1 = 4, j2 = 4; j1 >= 1; j1--, j2++) {
            if (change % 2 == 0) {
                if (isspace(matrix[i][j1])) {
                    matrix[i][j1] = 'O';
                    return 1;
                } else {
                    change++;
                }
            }
            if (change % 2 == 1) {
                if (isspace(matrix[i][j2])) {
                    matrix[i][j2] = 'O';
                    return 1;
                } else {
                    change++;
                }
            }
        }
    }
}


// if no chance to win with one move, or no chance to opponent to win with one
// move, play somthing usfull.
// return 1, if played
int play_somthing() {
    if (play_2() ||
       block_2() ||
       play_anything())
        return 1;
}


// computer takes O symbol.
// player taked X symbol.
//
// computer's turn, first check if there is a chance to win by using
// (find_chacne), if yes, put the symbol in the correct place and make
// coputer_won = 1. if not, try to block the opponent of winning in one
// move by using (block_opponent), if there were no danger of that, put the
// symbol in some good place.
// return 1, if it played.
int player_COM() {
    if (find_chance()) {
        computer_won = 1;
        return 1;
    }
    if (block_opponent()) {
        turn++;
        return 1;
    }
    play_somthing();
    turn++;
    return 1;
}
