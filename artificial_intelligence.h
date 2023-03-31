// Copyright 2019 Mohamad Hamdo
// proglang.informatik.uni-freiburg.de/teaching/advanced-programming/2019/

#ifndef ARTIFICIAL_INTELLIGENCE_H_
#define ARTIFICIAL_INTELLIGENCE_H_

extern int turn;
extern int computer_won;
char winner;


int find_chance();
int find_line();
int find_column();
int find_diagonal_left();
int find_diagonal_right();

int block_opponent();
int block_line();
int block_column();
int block_diagonal_left();
int block_diagonal_right();

int play_2();
int play_2_lines();
int play_2_columns();
int play_2_diagonal_left();
int play_2_diagonal_right();

int block_2();
int block_2_lines();
int block_2_columns();
int block_2_diagonal_left();
int block_2_diagonal_right();

int player_COM();
int play_somthing();
int play_anything();


#endif  // ARTIFICIAL_INTELLIGENCE_H_
