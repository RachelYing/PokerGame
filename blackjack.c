//
//  blackjack.c
//  final_project
//
//  Created by RachelDi on 20/04/2017.
//  Copyright © 2017 RachelDi. All rights reserved.
//
#include "cards.h"
#include "blackjack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// get the total score first and then we can compare two hands
int totalScore(struct card** cards, int size);

// Compare two blackjack hands. Return a value < 0 if hand_one wins, a value of 0
// if the hands are equal and a value > 0 if hand_two wins
int blackjack_compare(struct card **hand_one, int num_cards_hand_one,
                      struct card **hand_two, int num_cards_hand_two) {
    int score1 = totalScore(hand_one, num_cards_hand_one);
    int score2 = totalScore(hand_two, num_cards_hand_two);
    int result = 0;
    if((score1 > 21 && score2 > 21)||score1 == score2){
        result = 0;
    }else if(score1 > score2){
        if(score1 > 21){
            result = 1;
        }else{
            result = -1;
        }
    }else{
        if(score2 > 21){
            result = -1;
        }else{
            result = 1;
        }
    }
    return result;
}

// Blackjack to_string, should return the value of the hand or "BUST" if the total
// is over 21
char *blackjack_to_string(struct card **my_hand, int num_cards_in_hand) {
    char* bust = malloc(sizeof(char) * 20);
    strcpy(bust,"BUST");
    int win = totalScore(my_hand, num_cards_in_hand);
    if (win > 21){
        return bust;
    }
    char str[20];
    sprintf(str, "%d", win);
    char* other_result = malloc(sizeof(char) * 20);
    strcpy(other_result, str);
    return other_result;
}

int containAce(struct card** cards, int size){
    struct card** temp = (malloc(sizeof(struct card*) * size)) ;
    temp = cards;
    for (int i = 0; i < size; i++){
        if (temp[i]->card_rank == ace){
            return 1;
        }
    }
    return 0;
}

// get the total score first and then we can compare two hands
int totalScore(struct card** cards, int size) {
    int result = 0;
    int numeric_value = 0;
    for (int i = 0; i < size; i++) {
        rank card_rank = cards[i]->card_rank;
        if(card_rank == ace){
            numeric_value = 1;
        }else if(card_rank == two){
            numeric_value = 2;
        }else if(card_rank == three){
            numeric_value = 3;
        }else if(card_rank == four){
            numeric_value = 4;
        }else if(card_rank == five){
            numeric_value = 5;
        }else if(card_rank == six){
            numeric_value = 6;
        }else if(card_rank == seven){
            numeric_value = 7;
        }else if(card_rank == eight){
            numeric_value = 8;
        }else if(card_rank == nine){
            numeric_value = 9;
        }else{
            numeric_value = 10;
        }
        result += numeric_value;
        int contain = containAce(cards, size);
        // if current result is less than 11, then if we replace the ace
        // value with 11, the total score will not exceed 21. 11-1+11=21.
        if (contain == 1 && result <= 11){
            result += 10;
        }
    }
    return result;
}

