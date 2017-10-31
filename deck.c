//
//  cards.c
//  final_project
//
//  Created by RachelDi on 20/04/2017.
//  Copyright © 2017 RachelDi. All rights reserved.
//
//
#include "cards.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

suit suitArr[] = { hearts, diamonds, spades, clubs };
rank rankArr[] = {ace, two, three, four, five, six, seven, eight, nine, ten,
        jack, queen, king};
char* card_rank[] = {"two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "jack", "queen", "king",
    "ace"};
char *card_suit[] = {" of hearts", " of diamonds", " of spades", " of clubs"};

// create a standard 52-card deck
void* create_deck() {
    struct card **result = malloc(sizeof(struct card) * 52);
    for (int i = 0; i < 13; i++) {
        for(int j = 0; j < 4; j++) {
            struct card *current = malloc(sizeof(struct card));
            current->card_rank = rankArr[i];
            current->card_suit = suitArr[j];
            result[i * 4 + j] = current;
        }
    }
    *(result + 52) = NULL;
    // to shuffle the cards, otherwise the cards will always be in same order.
    srand((int)time(NULL));
    for(int i = 0; i < 52; i++){
        struct card * temp = malloc(sizeof(struct card));
        int ran = rand() % 52;
        temp = result[i];
        result[i] = result[ran];
        result[ran] = temp;
    }
    return result;
}

// free the deck memory
void destroy_deck(void* deck) {
    if (deck != NULL) {
        free(deck);
    }
}

// return a card, removing it from the deck
struct card* deal_card(void* deck) {
    int remove_index = number_of_cards_remaining_in_deck(deck) - 1;
    struct card* result = ((struct card **)deck)[remove_index];
    //the deck ends here
    ((struct card **)deck)[remove_index] = NULL;
    return result;
}

// return the number of cards indicated and remove them from the deck
struct card** deal_cards(void* deck, int num_cards) {
    int remove_index = number_of_cards_remaining_in_deck(deck) - num_cards;
    struct card **result = (malloc(sizeof(struct card*) * num_cards)) ;
    for (int i = 0; i < num_cards; i++) {
        result[i] = ((struct card **)deck)[remove_index + i];
    }
    ((struct card **)deck)[remove_index] = NULL;
    return result;
}

// Return the number of cards left in the deck
int number_of_cards_remaining_in_deck(void* deck) {
    //to avoid alter the deck
    struct card** temp = deck;
    int count = 0;
    while(*temp != NULL) {
        count++;
        temp++;
    }
    return count;
}

// This will return the remaining cards in the deck, in their current order, without removing any
struct card** peek_at_deck(void* deck) {
    return (struct card**)deck;
}

// Return a string describing a card e.g. "four of hearts" or "king of clubs"
char* to_string(struct card* my_card) {
    int r = my_card->card_rank;
    int s = my_card->card_suit;
    char* s1 = card_rank[r];
    char* s2 = card_suit[s];
    char* result = malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 1));
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}
