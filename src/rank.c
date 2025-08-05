#include "rank.h"

void add_score(ScoreBoard* board, const char name[MAX_NAME_LEN+1] , uint16_t score) {
    // Si el tablero no está lleno o el nuevo score es mayor que el menor existente
    if (board->count < MAX_SCORES || score > board->scores[MAX_SCORES-1].score) {
        if (board->count < MAX_SCORES) {
            board->count++;
        }
        
        int i = board->count - 1;
        while (i > 0 && score > board->scores[i-1].score) {
            board->scores[i] = board->scores[i-1];
            i--;
        }   
        strncpy(board->scores[i].name, name, MAX_NAME_LEN);
        board->scores[i].name[MAX_NAME_LEN] = '\0';
        board->scores[i].score = score;
        //printf("Added succesfully: %d. %s - %d\n",i+1,board->scores[i].name,board->scores[i].score);
    }
}

void save_scores(const ScoreBoard* board) {
    FILE* f = fopen(SCORE_FILE, "wb");
    if (f) {
        fwrite(&board->count, sizeof(uint8_t), 1, f);
        fwrite(board->scores, sizeof(PlayerScore), board->count, f);
        fclose(f);
    }
}

void load_scores(ScoreBoard* board) {
    FILE* f = fopen("scores.bin", "rb");
    if (!f) {
        board->count = 0;
        return;
    }
    
    fread(&board->count, sizeof(uint8_t), 1, f);
    if (board->count > MAX_SCORES) board->count = MAX_SCORES;
    fread(board->scores, sizeof(PlayerScore), board->count, f);
    fclose(f);
}