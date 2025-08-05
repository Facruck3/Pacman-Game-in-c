#ifndef PACMAN_RANK_H
#define PACMAN_RANK_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define MAX_NAME_LEN 8
#define MAX_SCORES 10
#define SCORE_FILE "scores.bin"

typedef struct {
    char name[MAX_NAME_LEN+1];
    uint16_t score;
} PlayerScore;

typedef struct {
    PlayerScore scores[MAX_SCORES];
    uint8_t count;
} ScoreBoard;

void add_score(ScoreBoard* board, const char name[MAX_NAME_LEN+1] , uint16_t score);
void save_scores(const ScoreBoard* board);
void load_scores(ScoreBoard* board);

#endif