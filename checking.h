// Copyright 2019 Mohamad Hamdo
// proglang.informatik.uni-freiburg.de/teaching/advanced-programming/2019/

#ifndef CHECKING_H_
#define CHECKING_H_

#define COLUMNS 7
#define LINES 6

char matrix[LINES + 1][COLUMNS + 1];
int check_line(int current_line, char symbole);
int check_column(int current_column, char symbole);
int check_first_diagonal(int current_line, int current_column, char symbole);
int check_second_diagonal(int current_line, int current_column, char symbole);
int check_winner(int current_column, int current_line, char symbole);
int check_tie();


#endif  // CHECKING_H_
