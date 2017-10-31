#include <stdio.h>
#include <stdlib.h>
#include "cards.h"
#include "blackjack.h"
#include "poker.h"

#define NUM_CARDS_IN_DECK 52
#define POKER 1

void
test_peek() {
  // Create a deck
  printf("\tcreating a blackjack_deck\n");
  int num_cards_to_request = 4;
  void *deck = create_deck();

  // request four cards
  struct card** blackjack_hand = deal_cards(deck, num_cards_to_request);
  char* blackjack_hand_string;

  blackjack_hand_string =  blackjack_to_string(blackjack_hand, num_cards_to_request);
  printf("\tblackjack hand: %s\n", blackjack_hand_string);
  free(blackjack_hand_string);
  // throw away the dealt cards
  for (int i=0; i<num_cards_to_request; i++) {
    free(blackjack_hand[i]);
  }
  free(blackjack_hand);

  int num_remaining_cards = number_of_cards_remaining_in_deck(deck);
  printf("Free cards %d (should be 48)\n", num_remaining_cards);

  // peek at the rest of the deck
  struct card** remaining_cards = peek_at_deck(deck);

  // request six cards
  num_cards_to_request = 6;
  blackjack_hand = deal_cards(deck, num_cards_to_request);
  char* peek_string;
  char* dealt_string;

  for(int i=0; i<num_cards_to_request; i++) {
    peek_string = to_string(remaining_cards[i]);
    dealt_string = to_string(blackjack_hand[i]);
    printf("peek: %s dealt: %s\n", peek_string, dealt_string);
    free(peek_string);
    free(dealt_string);
  }

  for (int i=0; i<num_remaining_cards; i++) {
    free(remaining_cards[i]);
  }
  free(remaining_cards);

  for (int i=0; i<num_cards_to_request; i++) {
    free(blackjack_hand[i]);
  }
  free(blackjack_hand);

  // Now destroy the deck
  destroy_deck(deck);
}

void
deal_one_hand_of_blackjack() {
  // Create a deck
  printf("\tcreating a blackjack_deck\n");
  int num_cards_to_request_hand_1 = 4;
  int num_cards_to_request_hand_2 = 3;
  void *deck = create_deck();

  // request four cards
  struct card** blackjack_hand_1 = deal_cards(deck, num_cards_to_request_hand_1);
  char* blackjack_hand_1_string;

  blackjack_hand_1_string =  blackjack_to_string(blackjack_hand_1, num_cards_to_request_hand_1);
  printf("\tblackjack hand 1: %s\n", blackjack_hand_1_string);

  // request three cards
  struct card** blackjack_hand_2 = deal_cards(deck, num_cards_to_request_hand_2);
  char* blackjack_hand_2_string;
  blackjack_hand_2_string =  blackjack_to_string(blackjack_hand_2, num_cards_to_request_hand_2);
  printf("\tblackjack hand 2: %s\n", blackjack_hand_2_string);

  // Compare the two hands to see who wins
  int hand_comparison = blackjack_compare(blackjack_hand_1, num_cards_to_request_hand_1,
                        blackjack_hand_2, num_cards_to_request_hand_2);
  if (hand_comparison < 0) {
    printf("\t\thand 1 wins\n");
  } else if (hand_comparison == 0) {
    printf("\t\tdraw\n");
  } else {
    printf("\t\thand 2 wins\n");
  }

  // free the hands and strings
  free(blackjack_hand_1_string);
  for (int i=0; i<num_cards_to_request_hand_1; i++) {
    free(blackjack_hand_1[i]);
  }
  free(blackjack_hand_1);
  free(blackjack_hand_2_string);
  for (int i=0; i<num_cards_to_request_hand_2; i++) {
    free(blackjack_hand_2[i]);
  }
  free(blackjack_hand_2);

  // Now destroy the deck
  destroy_deck(deck);
}

#ifdef POKER
void
deal_one_hand_of_poker() {
  // Create a deck
  printf("\tcreating a poker_deck\n");
  int num_cards_to_request_hand_1 = 5;
  int num_cards_to_request_hand_2 = 5;
  void *deck = create_deck();

  // request five cards
  struct card** poker_hand_1 = deal_cards(deck, num_cards_to_request_hand_1);
  char* poker_hand_1_string;
  char* card_string;

  for(int i=0; i<5; i++) {
    card_string = to_string(poker_hand_1[i]);
    printf("\tdealt: %s\n", card_string);
    free(card_string);
  }

  poker_hand_1_string =  poker_to_string(poker_hand_1);
  printf("\t\tpoker hand 1: %s\n", poker_hand_1_string);


  // request five cards
  struct card** poker_hand_2 = deal_cards(deck, num_cards_to_request_hand_2);
  char* poker_hand_2_string;

  for(int i=0; i<5; i++) {
    card_string = to_string(poker_hand_2[i]);
    printf("\tdealt: %s\n", card_string);
    free(card_string);
  }

  poker_hand_2_string =  poker_to_string(poker_hand_2);
  printf("\t\tpoker hand 2: %s\n", poker_hand_2_string);

  // Compare the two hands to see who wins
  int hand_comparison = poker_compare(poker_hand_1, poker_hand_2);

  if (hand_comparison < 0) {
    printf("\t\thand 1 wins\n");
  } else if (hand_comparison == 0) {
    printf("\t\tdraw\n");
  } else {
    printf("\t\thand 2 wins\n");
  }

  // free the hands and strings
  free(poker_hand_1_string);
  for (int i=0; i<num_cards_to_request_hand_1; i++) {
    free(poker_hand_1[i]);
  }
  free(poker_hand_1);
  free(poker_hand_2_string);
  for (int i=0; i<num_cards_to_request_hand_2; i++) {
    free(poker_hand_2[i]);
  }
  free(poker_hand_2);

  // Now destroy the deck
  destroy_deck(deck);
}

void
compare_two_poker_hands(){
  // Create a deck
  printf("\tmanufacturing two poker hands\n");

  // request five cards
  struct card** poker_hand_1 = malloc(5*sizeof(struct card*));
  for( int i=0; i<5; i++) {
        poker_hand_1[i] = malloc(sizeof(struct card));
  }
  poker_hand_1[0]->card_suit = clubs;
  poker_hand_1[0]->card_rank = seven;
  poker_hand_1[1]->card_suit = hearts;
  poker_hand_1[1]->card_rank = seven;
  poker_hand_1[2]->card_suit = spades;
  poker_hand_1[2]->card_rank = jack;
  poker_hand_1[3]->card_suit = clubs;
  poker_hand_1[3]->card_rank = jack;
  poker_hand_1[4]->card_suit = hearts;
  poker_hand_1[4]->card_rank = jack;

  char* poker_hand_1_string;
  char* card_string;

  for(int i=0; i<5; i++) {
    card_string = to_string(poker_hand_1[i]);
    printf("\tdealt: %s\n", card_string);
    free(card_string);
  }

  poker_hand_1_string =  poker_to_string(poker_hand_1);
  printf("\t\tpoker hand 1 (should be full house, 7/jack): %s\n", poker_hand_1_string);

  // request five cards
  struct card** poker_hand_2 = malloc(5*sizeof(struct card*));
  for( int i=0; i<5; i++ ) {
        poker_hand_2[i] = malloc(sizeof(struct card));
  }
  poker_hand_2[0]->card_suit = clubs;
  poker_hand_2[0]->card_rank = seven;
  poker_hand_2[1]->card_suit = clubs;
  poker_hand_2[1]->card_rank = four;
  poker_hand_2[2]->card_suit = clubs;
  poker_hand_2[2]->card_rank = jack;
  poker_hand_2[3]->card_suit = clubs;
  poker_hand_2[3]->card_rank = king;
  poker_hand_2[4]->card_suit = clubs;
  poker_hand_2[4]->card_rank = two;

  char* poker_hand_2_string;

  for(int i=0; i<5; i++) {
    card_string = to_string(poker_hand_2[i]);
    printf("\tdealt: %s\n", card_string);
    free(card_string);
  }

  poker_hand_2_string =  poker_to_string(poker_hand_2);
  printf("\t\tpoker hand 2 (should be flush): %s\n", poker_hand_2_string);

  // Compare the two hands to see who wins
  int hand_comparison = poker_compare(poker_hand_1, poker_hand_2);

  if (hand_comparison < 0) {
    printf("\t\thand 1 wins\n");
  } else if (hand_comparison == 0) {
    printf("\t\tdraw\n");
  } else {
    printf("\t\thand 2 wins\n");
  }

  // free the hands and strings
  free(poker_hand_1_string);
  for (int i=0; i<5; i++) {
    free(poker_hand_1[i]);
  }

  free(poker_hand_1);
  free(poker_hand_2_string);
  for (int i=0; i<5; i++) {
    free(poker_hand_2[i]);
  }
  free(poker_hand_2);
}

void
compare_two_more_poker_hands(){
  // Create a deck
  printf("\tmanufacturing two poker hands\n");

  // request five cards
  struct card** poker_hand_1 = malloc(5*sizeof(struct card*));
  for( int i=0; i<5; i++) {
        poker_hand_1[i] = malloc(sizeof(struct card));
  }
  poker_hand_1[0]->card_suit = clubs;
  poker_hand_1[0]->card_rank = seven;
  poker_hand_1[1]->card_suit = clubs;
  poker_hand_1[1]->card_rank = eight;
  poker_hand_1[2]->card_suit = clubs;
  poker_hand_1[2]->card_rank = nine;
  poker_hand_1[3]->card_suit = clubs;
  poker_hand_1[3]->card_rank = ten;
  poker_hand_1[4]->card_suit = clubs;
  poker_hand_1[4]->card_rank = jack;

  char* poker_hand_1_string;
  char* card_string;

  for(int i=0; i<5; i++) {
    card_string = to_string(poker_hand_1[i]);
    printf("\tdealt: %s\n", card_string);
    free(card_string);
  }

  poker_hand_1_string =  poker_to_string(poker_hand_1);
  printf("\t\tpoker hand 1 (should be straight-flush to the jack): %s\n", poker_hand_1_string);

  // request five cards
  struct card** poker_hand_2 = malloc(5*sizeof(struct card*));
  for( int i=0; i<5; i++ ) {
        poker_hand_2[i] = malloc(sizeof(struct card));
  }
  poker_hand_2[0]->card_suit = clubs;
  poker_hand_2[0]->card_rank = seven;
  poker_hand_2[1]->card_suit = clubs;
  poker_hand_2[1]->card_rank = four;
  poker_hand_2[2]->card_suit = clubs;
  poker_hand_2[2]->card_rank = jack;
  poker_hand_2[3]->card_suit = clubs;
  poker_hand_2[3]->card_rank = king;
  poker_hand_2[4]->card_suit = spades;
  poker_hand_2[4]->card_rank = two;

  char* poker_hand_2_string;

  for(int i=0; i<5; i++) {
    card_string = to_string(poker_hand_2[i]);
    printf("\tdealt: %s\n", card_string);
    free(card_string);
  }

  poker_hand_2_string =  poker_to_string(poker_hand_2);
  printf("\t\tpoker hand 2 (should be king-high): %s\n", poker_hand_2_string);

  // Compare the two hands to see who wins
  int hand_comparison = poker_compare(poker_hand_2, poker_hand_1);

  printf("hand two should win\n");
  if (hand_comparison < 0) {
    printf("\t\thand 1 wins\n");
  } else if (hand_comparison == 0) {
    printf("\t\tdraw\n");
  } else {
    printf("\t\thand 2 wins\n");
  }

  // free the hands and strings
  free(poker_hand_1_string);
  for (int i=0; i<5; i++) {
    free(poker_hand_1[i]);
  }

  free(poker_hand_1);
  free(poker_hand_2_string);
  for (int i=0; i<5; i++) {
    free(poker_hand_2[i]);
  }
  free(poker_hand_2);
}

#endif

void
create_and_destroy_deck() {
  // Create a deck
  void *deck = create_deck();

  // verify the deck size
  int cards_left = number_of_cards_remaining_in_deck(deck);
  printf("\tThere are %d cards left in the deck\n", cards_left);

  // Now destroy the deck
  destroy_deck(deck);
}

void
test_card_exists_after_deck_destruction() {
  // Create a deck
  void *deck = create_deck();

  // verify the deck size
  int cards_left = number_of_cards_remaining_in_deck(deck);
  printf("\tThere are %d cards left in the deck\n", cards_left);

  // Deal a card
  struct card* one_card = deal_card(deck);
  printf("\tCard is the %d of %d\n", one_card->card_rank, one_card->card_suit);

  char* card_string;
  card_string = to_string(one_card);
  printf("\t%s\n", card_string);

  // free the string that was returned
  // Now destroy the deck
  destroy_deck(deck);

  printf("\tPost-destroy, card is %s\n", card_string);
  printf("\t%s\n", card_string);

  // free the card that we were dealt
  free(one_card);
  // free the string that was returned
  free(card_string);
}

void
deal_one_card() {
  // Create a deck
  void *deck = create_deck();

  // Deal a card
  struct card* one_card = deal_card(deck);
  printf("\tCard is the %d of %d\n", one_card->card_rank, one_card->card_suit);

  char* card_string;
  card_string = to_string(one_card);
  printf("\t%s\n", card_string);

  // free the string that was returned
  free(card_string);

  int cards_left = number_of_cards_remaining_in_deck(deck);
  printf("\tThere are %d cards left in the deck\n", cards_left);

  // free the card that we were dealt
  free(one_card);

  // Now destroy the deck
  destroy_deck(deck);
}

void
two_decks_should_not_match() {
  // Create a deck
  void *deck1 = create_deck();
  void *deck2 = create_deck();

  // Deal a card
  struct card* one_card = deal_card(deck1);
  printf("\tCard is the %d of %d\n", one_card->card_rank, one_card->card_suit);

  struct card* another_card = deal_card(deck2);
  printf("\tCard is the %d of %d\n", another_card->card_rank, another_card->card_suit);

  char* card_string1;
  char* card_string2;
  card_string1 = to_string(one_card);
  card_string2 = to_string(another_card);
  printf("\t%s should not equal %s\n", card_string1, card_string2);

  // free the string that was returned
  free(card_string1);
  free(card_string2);

  int cards_left = number_of_cards_remaining_in_deck(deck1);
  printf("\tThere are %d cards left in the deck\n", cards_left);

  // free the card that we were dealt
  free(one_card);
  free(another_card);

  // Now destroy the deck
  destroy_deck(deck1);
  destroy_deck(deck2);
}

void
deal_fifty_two_cards() {
  // Create a deck
  void *deck = create_deck();

  struct card* one_card;
  char* card_string;
  int cards_left;

  for (int i=0; i<NUM_CARDS_IN_DECK; i++) {
    // Deal a card
    one_card = deal_card(deck);

    card_string = to_string(one_card);
    printf("\t%s\n", card_string);

    // free the string that was returned
    free(card_string);

    int cards_left = number_of_cards_remaining_in_deck(deck);
    printf("\tThere are %d cards left in the deck\n", cards_left);

    // free the card that we were dealt
    free(one_card);
  }

  // Now destroy the deck
  destroy_deck(deck);
}

void
deal_one_hand() {
  // Create a deck
  void *deck = create_deck();

  // request two cards
  struct card** my_hand = deal_cards(deck, 5);

  char* card_string;
  // print and then free free each card
  for (int i=0; i<5; i++) {
    card_string = to_string(my_hand[i]);
    printf("\t%s\n", card_string);

    // free the card string and then the card
    free(card_string);
    free(my_hand[i]);
  }

  // How many cards are left in the deck?
  int cards_left = number_of_cards_remaining_in_deck(deck);
  printf("\tThere are %d cards left in the deck\n", cards_left);

  // free the point to the pointers
  free(my_hand);

  // Now destroy the deck
  destroy_deck(deck);
}

void
test_specific_blackjack_hands() {
  int cards_in_hand_1 = 2;
  int cards_in_hand_2 = 3;

  // Create a hand that is 21
  struct card** twenty_one = malloc(2*sizeof(struct card*));
  for (int i=0; i<cards_in_hand_1; i++) {
    twenty_one[i] = malloc(sizeof(struct card));
  }
  twenty_one[0]->card_suit = diamonds;
  twenty_one[0]->card_rank = king;
  twenty_one[1]->card_suit = spades;
  twenty_one[1]->card_rank = ace;
  char* hand_string = blackjack_to_string(twenty_one, 2);
  printf("\tblackjack hand 1: %s\n", hand_string);
  free(hand_string);

  struct card** twenty = malloc(3*sizeof(struct card*));
  for (int i=0; i<cards_in_hand_2; i++) {
    twenty[i] = malloc(sizeof(struct card));
  }
  twenty[0]->card_suit = hearts;
  twenty[0]->card_rank = six;
  twenty[1]->card_suit = clubs;
  twenty[1]->card_rank = seven;
  twenty[2]->card_suit = spades;
  twenty[2]->card_rank = seven;
  hand_string = blackjack_to_string(twenty, 3);
  printf("\tblackjack hand 2: %s\n", hand_string);
  free(hand_string);

  int hand_comparison = blackjack_compare(twenty_one, 2, twenty, 3);

  // free the hands
  for (int i=0; i<cards_in_hand_1; i++) {
    free(twenty_one[i]);
  }
  for (int i=0; i<cards_in_hand_2; i++) {
    free(twenty[i]);
  }
  free(twenty_one);
  free(twenty);

  printf("\thand 1 should win\n");
  if (hand_comparison < 0) {
    printf("\t\thand 1 wins\n");
  } else if (hand_comparison == 0) {
    printf("\t\tdraw\n");
  } else {
    printf("\t\thand 2 wins\n");
  }
}

void
test_bust_blackjack_hand() {
  int cards_in_hand_1 = 2;
  int cards_in_hand_2 = 3;

  struct card** ten = malloc(cards_in_hand_1 * sizeof(struct card*));
  for (int i=0; i<cards_in_hand_1; i++) {
    ten[i] = malloc(sizeof(struct card));
  }
  ten[0]->card_suit = diamonds;
  ten[0]->card_rank = two;
  ten[1]->card_suit = spades;
  ten[1]->card_rank = eight;
  char* hand_string = blackjack_to_string(ten, 2);
  printf("\tblackjack hand 1: %s\n", hand_string);
  free(hand_string);

  struct card** bust = malloc(cards_in_hand_2 * sizeof(struct card*));
  for (int i=0; i<cards_in_hand_2; i++) {
    bust[i] = malloc(sizeof(struct card));
  }
  bust[0]->card_suit = hearts;
  bust[0]->card_rank = queen;
  bust[1]->card_suit = clubs;
  bust[1]->card_rank = three;
  bust[2]->card_suit = spades;
  bust[2]->card_rank = king;
  hand_string = blackjack_to_string(bust, 3);
  printf("\tblackjack hand 2: %s\n", hand_string);
  free(hand_string);

  int hand_comparison = blackjack_compare(bust, 3, ten, 2);

  // free the hands
  for (int i=0; i<cards_in_hand_1; i++) {
    free(ten[i]);
  }
  for (int i=0; i<cards_in_hand_2; i++) {
    free(bust[i]);
  }
  free(bust);
  free(ten);

  printf("\thand 2 should win\n");
  if (hand_comparison < 0) {
    printf("\t\thand 1 wins\n");
  } else if (hand_comparison == 0) {
    printf("\t\tdraw\n");
  } else {
    printf("\t\thand 2 wins\n");
  }
}

void
test_double_bust_blackjack_hand() {
  int cards_in_hand_1 = 4;
  int cards_in_hand_2 = 3;

  struct card** hand1 = malloc(cards_in_hand_1 * sizeof(struct card*));
  for (int i=0; i<cards_in_hand_1; i++) {
    hand1[i] = malloc(sizeof(struct card));
  }
  hand1[0]->card_suit = diamonds;
  hand1[0]->card_rank = two;
  hand1[1]->card_suit = spades;
  hand1[1]->card_rank = eight;
  hand1[2]->card_suit = diamonds;
  hand1[2]->card_rank = four;
  hand1[3]->card_suit = spades;
  hand1[3]->card_rank = king;
  char* hand_string = blackjack_to_string(hand1, cards_in_hand_1);
  printf("\tblackjack hand 1: %s\n", hand_string);
  free(hand_string);

  struct card** bust = malloc(cards_in_hand_2 * sizeof(struct card*));
  for (int i=0; i<cards_in_hand_2; i++) {
    bust[i] = malloc(sizeof(struct card));
  }
  bust[0]->card_suit = hearts;
  bust[0]->card_rank = queen;
  bust[1]->card_suit = clubs;
  bust[1]->card_rank = three;
  bust[2]->card_suit = spades;
  bust[2]->card_rank = king;
  hand_string = blackjack_to_string(bust, 3);
  printf("\tblackjack hand 2: %s\n", hand_string);
  free(hand_string);

  int hand_comparison = blackjack_compare(bust, 3, hand1, 4);

  // free the hands
  for (int i=0; i<cards_in_hand_1; i++) {
    free(hand1[i]);
  }
  for (int i=0; i<cards_in_hand_2; i++) {
    free(bust[i]);
  }
  free(hand1);
  free(bust);


  printf("\thands should tie\n");
  if (hand_comparison < 0) {
    printf("\t\thand 1 wins\n");
  } else if (hand_comparison == 0) {
    printf("\t\tdraw\n");
  } else {
    printf("\t\thand 2 wins\n");
  }
}

void
test_blackjack_hand_draw() {
  int cards_in_hand_1 = 2;
  int cards_in_hand_2 = 3;

  struct card** hand1 = malloc(cards_in_hand_1 * sizeof(struct card*));
  for (int i=0; i<cards_in_hand_1; i++) {
    hand1[i] = malloc(sizeof(struct card));
  }
  hand1[0]->card_suit = spades;
  hand1[0]->card_rank = nine;
  hand1[1]->card_suit = spades;
  hand1[1]->card_rank = ten;
  char* hand_string = blackjack_to_string(hand1, cards_in_hand_1);
  printf("\tblackjack hand 1: %s\n", hand_string);
  free(hand_string);

  struct card** hand2= malloc(cards_in_hand_2 * sizeof(struct card*));
  for (int i=0; i<cards_in_hand_2; i++) {
    hand2[i] = malloc(sizeof(struct card));
  }
  hand2[0]->card_suit = clubs;
  hand2[0]->card_rank = seven;
  hand2[1]->card_suit = hearts;
  hand2[1]->card_rank = two;
  hand2[2]->card_suit = spades;
  hand2[2]->card_rank = king;
  hand_string = blackjack_to_string(hand2, 3);
  printf("\tblackjack hand 2: %s\n", hand_string);
  free(hand_string);

  int hand_comparison = blackjack_compare(hand1, 2, hand2, 3);

  // free the hands
  for (int i=0; i<cards_in_hand_1; i++) {
    free(hand1[i]);
  }
  for (int i=0; i<cards_in_hand_2; i++) {
    free(hand2[i]);
  }
  free(hand1);
  free(hand2);


  printf("\thands should tie\n");
  if (hand_comparison < 0) {
    printf("\t\thand 1 wins\n");
  } else if (hand_comparison == 0) {
    printf("\t\tdraw\n");
  } else {
    printf("\t\thand 2 wins\n");
  }
}

int
main() {
  printf("Cards time\n");

  printf("test 1\n");
  create_and_destroy_deck();

  printf("test 2\n");
  deal_one_card();

  printf("test 3\n");
  deal_one_hand();

  printf("test 4\n");
  deal_one_hand_of_blackjack();

  printf("test 5\n");
  test_card_exists_after_deck_destruction();

  printf("test 6\n");
  deal_fifty_two_cards();

  printf("test 7\n");
  test_specific_blackjack_hands();

  printf("test 8\n");
  test_bust_blackjack_hand();

  printf("test 9\n");
  test_double_bust_blackjack_hand();

  printf("test 10\n");
  test_blackjack_hand_draw();

//  printf("test 11\n");
//  test_peek();

#ifdef POKER
  printf("test 12\n");
  deal_one_hand_of_poker();

  printf("test 13\n");
  compare_two_poker_hands();

  printf("test 14\n");
  compare_two_more_poker_hands();
#endif

  printf("test 15\n");
  two_decks_should_not_match();

  return 0;
}
