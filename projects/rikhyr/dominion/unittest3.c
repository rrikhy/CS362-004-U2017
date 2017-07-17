/*
* RR
* CS 362
* handNumCards() Unit Test
*
* 1. Check correct player hand cards quantity processing.
*
* Check for occasional changes of game state inbetween testing runs.
* 
* 
*/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "compareStates.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main() 
{int randomSeed;
    SelectStream(1);
	PutSeed(-1);
    int i, r, j, locVal, zeros; // auxilliary  vars
    int numPlayer = 4; // setting maximal count of players
    int k[10] = {adventurer, gardens, smithy, village, sea_hag, treasure_map, outpost, cutpurse, tribute, salvager};
    struct gameState G, copyG;
    int seed = floor(Random() * 1000);

    srand(time(NULL));
    printf ("\nTESTING handNumCards():\n");
    
	
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    memcpy(&copyG, &G, sizeof(struct gameState)); // save the game state before we start checking isGameOver
	
	printf("Current player numHandCards should be 0 initially to see if whoseTurn() returns 0.\n");
    if (numHandCards(&G) != 5)
    {
        printf("Current turn player cards should be initially 5, but numHandCards() was not 5.\n");
    }
    printf("Running 1000 random tests for first player hand cards count to verify numHandCards is showing correct amount.\n");
    for (i = 0; i < 1000; i++)
    {
        int localDeck = rand() % MAX_HAND;
        G.handCount[0] = localDeck;
		zeros=numHandCards(&G);
        if ((zeros<0)||(zeros>MAX_HAND))
        {
			printf("Test %d. Amount should be %d, but numHandCards() returned value out of allowed range: %d.\n",i,localDeck,zeros);
		}
		
        if (zeros != localDeck)
        {
            printf("Test %d - numHandCards() failed to get correct amount: %d instead of %d.\n",i,zeros,localDeck);
        }
        
    }
    printf("Done with  random testing.\n");
	
	
	G.handCount[0]=5;
    
    for (j = 0; j < numPlayer; j++)
    {
        if (cmpDeckCount(&G, &copyG, j))
            printf("Deck Count has changed between copied and modified game state!\n");
        
		if (cmpDiscard(&G, &copyG, j))
            printf("Discard deck has changed between copied and modified game state!\n");
		
        if (cmpDiscardCount(&G, &copyG, j))
            printf("Discard count has been changed between copied and modified game state!\n");
        
		if (cmpDeck(&G, &copyG, j))
            printf("Deck has changed between copied and modified game state!\n");
	
    }
    printf("Testing general game state variables if they've been changed ...\n");
    printf("This will test to see if our copied game state before we performed numHandCards testing is equal to the modified game state.\n");
    
    if (cmpPlayedCards(&G, &copyG))
        printf("playedCards has changed between copied and modified game state!\n");
    if (cmpPlayedCardCount(&G, &copyG))
        printf("playedCardCount has changed between copied and modified game state!\n");
    if (cmpPhase(&G, &copyG))
        printf("phase has changed between copied and modified game state!\n");
    if (cmpWhoseTurn(&G, &copyG))
        printf("WhoseTurn has changed between copied and modified game state!\n"); 
    if (cmpNumActions(&G, &copyG))
        printf("numActions has changed between copied and modified game state!\n");
    if (cmpOutpostPlayed(&G, &copyG))
        printf("OutpostPlayed has changed between copied and modified game state!\n");
    if (cmpNumPlayers(&G, &copyG))
        printf("NumPlayers has changed between copied and modified game state!\n");
    if (cmpNumBuys(&G, &copyG))
        printf("NumBuys has changed between copied and modified game state!\n");
    if (cmpOutpostTurn(&G, &copyG))
        printf("OutpostTurn has changed between copied and modified game state!\n");
    printf("Done checking game states.\n");
    printf("\nAll tests done for numHandCards()!\n \n");
    return 0;
}