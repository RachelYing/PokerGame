//
//  poker.c
//  final_project
//
//  Created by RachelDi on 26/04/2017.
//  Copyright © 2017 RachelDi. All rights reserved.
//
#include "cards.h"
#include "poker.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// swap two cards
void swap(int i, int j, struct card** cards){
    struct card* card = cards[i];
    cards[i] = cards[j];
    cards[j] = card;
}

// get the numeric value of the ranks
int numericVal(rank rank){
    if(rank == ace){
        return 14;
    }else if(rank == two){
        return 2;
    }else if(rank == three){
        return 3;
    }else if(rank == four){
        return 4;
    }else if(rank == five){
        return 5;
    }else if(rank == six){
        return 6;
    }else if(rank == seven){
        return 7;
    }else if(rank == eight){
        return 8;
    }else if(rank == nine){
        return 9;
    }else if(rank == ten){
        return 10;
    }else if(rank == jack){
        return 11;
    }else if(rank == queen){
        return 12;
    }
    return 13;
}

// get the string value of the ranks
char* stringVal(rank rank){
    char* result=malloc(sizeof(char)*20);
    if(rank == ace){
        result= "ace";
    }else if(rank == two){
        result= "two";
    }else if(rank == three){
        result= "three";
    }else if(rank == four){
        result= "four";
    }else if(rank == five){
        result= "five";
    }else if(rank == six){
        result= "six";
    }else if(rank == seven){
        result= "seven";
    }else if(rank == eight){
        result= "eight";
    }else if(rank == nine){
        result= "nine";
    }else if(rank == ten){
        result= "ten";
    }else if(rank == jack){
        result= "jack";
    }else if(rank == queen){
        result= "queen";
    }else{
        result= "king";
    }
    return result;
}

// insert a card into the cards
void insert(int k, struct card** cards){
    while((k - 1) >= 0 && numericVal(cards[k - 1]->card_rank)
          > numericVal(cards[k]->card_rank)){
        swap(k - 1, k, cards);
        k--;
    }
}

// sort the cards
void sort(struct card** cards){
    int i;
    for(i = 1; i < 5; i++){
        insert(i, cards);
    }
}

// if the two cards are adjacent then return 1, else return 0;
int isAdjacent(struct card* card1, struct card* card2){
    if(numericVal(card2->card_rank) - numericVal(card1->card_rank) == 1){
        return 1;
    }
    return 0;
}

int isStraightFlush(struct card** cards){
    sort(cards);
    for(int i = 1; i < 5; i++){
        if (cards[i]->card_suit != cards[i - 1]->card_suit
            || isAdjacent(cards[i], cards[i-1]) == 0){
            return 0;
        }
    }
    return 1;
}

// is four of kind or better
int isFourKind(int arr[]){
    for(int i = 0; i < 4; i++){
        if(arr[i] == 4){
            return 1;
        }
    }
    return 0;
}

// is full house or better
int isFullHouse(int arr[]){
    int result1 = 0;
    int result2 = 0;
    for(int i = 0; i < 4; i++){
        if(arr[i] == 3){
            result1 = 1;
        }
        if(arr[i] == 2){
            result2 = 1;
        }
    }
    if(result1 == 1 && result2 == 1){
        return 1;
    }
    return 0;
}

//is flush or better
int isFlush(struct card** cards){
    sort(cards);
    for(int i = 1; i < 5; i++){
        if(cards[i]->card_suit != cards[i - 1]->card_suit){
            return 0;
        }
    }
    return 1;
}

// is straight or better
int isStraight(struct card** cards){
    sort(cards);
    for (int i = 1; i < 5; i++){
        if (isAdjacent(cards[i], cards[i - 1]) == 1){
            return 1;
        }
    }
    return 0;
}

// is three of kind or better
int isThreeKind(int arr[]){
    for(int i = 0; i < 4; i++){
        if(arr[i] == 3){
            return 1;
        }
    }
    return 0;
}

// is two pair or better
int isTwoPair(int arr[]){
    int count = 0;
    for(int i = 0; i < 4; i++){
        if(arr[i] == 2){
            count++;
        }
    }
    if(count == 2){
        return 1;
    }
    return 0;
}

// is pair or better
int isPair(int arr[]){
    int count = 0;
    for(int i = 0; i < 4; i++){
        if(arr[i] == 2){
            count++;
        }
    }
    if(count == 1){
        return 1;
    }
    return 0;
}

// get the score of the hands
int score(struct card** cards){
    int arr[4] = {0,0,0,0};
    for(int i = 0; i < 4; i++){
        if(cards[i]->card_suit == hearts){
            arr[0] = arr[0] + 1;
        }else if(cards[i]->card_suit == diamonds){
            arr[1] = arr[1] + 1;
        }else if(cards[i]->card_suit == spades){
            arr[2] = arr[2] + 1;
        }else{
            arr[2] = arr[3] + 1;
        }
    }
    int result = 0;
    if(isStraightFlush(cards) == 1){
        for(int i = 0; i < 5; i++){
            result += 50000000 * numericVal(cards[i]->card_rank);
        }
    }else if(isFourKind(arr) == 1){
        for(int i = 0; i < 5; i++){
            result += 5000000 * numericVal(cards[i]->card_rank);
        }
    }else if(isFullHouse(arr) == 1){
        for(int i = 0; i < 5; i++){
            result += 500000 * numericVal(cards[i]->card_rank);
        }
    }else if(isFlush(cards) == 1){
        for(int i = 0; i < 5; i++){
            result += 50000 * numericVal(cards[i]->card_rank);
        }
    }else if(isStraight(cards) == 1){
        for(int i = 0; i < 5; i++){
            result += 5000 * numericVal(cards[i]->card_rank);
        }
    }else if(isThreeKind(arr) == 1){
        for(int i = 0; i < 5; i++){
            result += 500 * numericVal(cards[i]->card_rank);
        }
    }else if(isTwoPair(arr) == 1){
        for(int i = 0; i < 5; i++){
            result += 50 * numericVal(cards[i]->card_rank);
        }
    }else if(isPair(arr) == 1){
        for(int i = 0; i < 5; i++){
            result += 9 * numericVal(cards[i]->card_rank);
        }
    }else{
        for(int i = 0; i < 5; i++){
            result += numericVal(cards[i]->card_rank);
        }
    }
      return result;
}

// Compare two poker hands. Return a value < 0 if hand_one wins, a value of 0
// if the hands are equal and a value > 0 if hand_two wins.
// Poker hands are always 5 cards, so no need to pass that in as an argument.
int poker_compare(struct card** hand_one, struct card** hand_two){
    int score1 = score(hand_one);
    int score2 = score(hand_two);
    if(score1 == score2){
        return 0;
    }else if(score1 > score2){
        return -1;
    }
    return 1;
}

// poker to_string. See the wikipedia page for hand definitions. Poker hands are always
// five cards, no need to specify the hand length.
//Examples include:
// Ace high
// Pair of jacks
// Two pairs, nines and fives
// Three queens
// Straight, eight high
// Flush, ten high
// Full house, sixes over threes
// four sevens
// straight flush, eight high
// royal flush
char* poker_to_string(struct card** my_hand){
    sort(my_hand);
    int arr[4] = {0,0,0,0};
    for(int i = 0; i < 5; i++){
        if(my_hand[i]->card_suit == hearts){
            arr[0] = arr[0] + 1;
        }else if(my_hand[i]->card_suit == diamonds){
            arr[1] = arr[1] + 1;
        }else if(my_hand[i]->card_suit == spades){
            arr[2] = arr[2] + 1;
        }else{
            arr[2] = arr[3] + 1;
        }
    }
    char* result = malloc(sizeof(char)*60);
    if(isStraightFlush(my_hand) == 1){
        strcpy(result,"straight flush, ");
        strcat(result, stringVal(my_hand[4]->card_rank));
        strcat(result,"high");
    }else if(isFourKind(arr) == 1){
        strcpy(result,"four");
        strcat(result, stringVal(my_hand[1]->card_rank));
        strcat(result,"s");
    }else if(isFullHouse(arr) == 1){
        strcpy(result,"full house, ");
        strcat(result, stringVal(my_hand[2]->card_rank));
        strcpy(result,"s over ");
        if(my_hand[4]->card_rank != my_hand[2]->card_rank){
            strcat(result, stringVal(my_hand[4]->card_rank));
        }else{
            strcat(result, stringVal(my_hand[0]->card_rank));
        }
    }else if(isFlush(my_hand) == 1){
        strcpy(result,"flush, ");
        strcat(result, stringVal(my_hand[4]->card_rank));
        strcat(result,"high");
    }else if(isStraight(my_hand) == 1){
        strcpy(result,"straight, ");
        strcat(result, stringVal(my_hand[4]->card_rank));
        strcat(result,"high");
    }else if(isThreeKind(arr) == 1){
        strcpy(result,"three");
        strcat(result, stringVal(my_hand[2]->card_rank));
        strcat(result,"s");
    }else if(isTwoPair(arr) == 1){
        rank rank1=-1;
        rank rank2=-1;
        for(int i = 1; i < 5; i++){
            for(int j = 0; j < i; j++){
                if(my_hand[i]->card_rank == my_hand[j]->card_rank){
                    rank1 = my_hand[i]->card_rank;
                }
            }
        }
        for(int i = 1; i < 5; i++){
            for(int j = 0; j < i; j++){
                if(my_hand[i]->card_rank == my_hand[j]->card_rank
                   && my_hand[i]->card_rank != rank1){
                    rank2 = my_hand[i]->card_rank;
                }
            }
        }
        strcpy(result,"two pairs, ");
        strcpy(result,stringVal(rank1));
        strcpy(result,"s and ");
        strcpy(result,stringVal(rank2));
        strcpy(result,"s");
    }else if(isPair(arr) == 1){
        rank rank=-1;
        for(int i = 1; i < 5; i++){
            for(int j = 0; j < i; j++){
                if(my_hand[i]->card_rank == my_hand[j]->card_rank){
                    rank = my_hand[i]->card_rank;
                }
            }
        }
        strcpy(result,"pairs of ");
        strcpy(result,stringVal(rank));
        strcpy(result,"s");
    }else{
        strcat(result, stringVal(my_hand[4]->card_rank));
        strcpy(result," high");
    }
    return result;
}



