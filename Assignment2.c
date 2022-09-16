/**Thando Tsebedu
   R00221555
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define MINBOARD 32
#define MAXBOARD 64
#define MIN_SL_SIZE 1
#define MAX_SL_SIZE 10
#define FILE_NAME "S&L Game Report.txt"

static int boardSize = 0;
int playerPosition = 0;

// structure snake and ladder
typedef struct Node
{
    int isSnake, isLadder;
    int nodeIndex, lengthSL;
    struct Node *next;
} slBoard;

slBoard *head = NULL;
slBoard *tail = NULL;

// structure for player position
typedef struct player
{
    int currentPosition, newPosition, randStrDice;
    struct player *next;
    struct Node *node;
} playerMoves;

playerMoves *headPlayer = NULL;
playerMoves *tailPlayer = NULL;

// functions to print create and reverse board
void printBoard(slBoard *node);
void createGameBoard();
void reverse(struct Node **head);
struct Node *searchNode(int i);
int randomNumbers(int min, int max);

// functions to create random numbers passing the min and max numbers
int randomNumbers(int min, int max)
{
    int randNum = (rand() % (max - min + 1)) + min;
    return randNum;
}

// create the board for the game
void createGameBoard()
{

    int boardNode = 1;
    boardSize = randomNumbers(MINBOARD, MAXBOARD);
    int i, counter = 0;
    slBoard *newNode;

    // set the size of the board
    for (i = 0; i < boardSize; i++)
    {
        newNode = (slBoard *)malloc(sizeof(slBoard));
        newNode->nodeIndex = boardNode++;
        newNode->next = NULL;

        // check if the list is empty
        if (head == tail && tail == NULL)
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }
    // reverse the board/
     reverse(&head);
     //print board
    printBoard(head);
}

// Linked list of player moves
void playerMovesList(int randDice)
{

    playerMoves *pMove = (playerMoves *)malloc(sizeof(playerMoves));

    pMove->currentPosition = playerPosition;
    printf("\nPlayer current position: %d", pMove->currentPosition);
    pMove->newPosition = pMove->currentPosition + randDice;
    playerPosition = pMove->newPosition;
    pMove->randStrDice = randDice;
    pMove->next = NULL;
    slBoard *temp = searchNode(pMove->newPosition);

    // check if we are in a snake or ladder
    if (temp->isLadder == 1)
    {
        printf("\n\tLadder has been reached");
        printf("\n\tladder length = %d", temp->lengthSL);
        // add to player position
        playerPosition += temp->lengthSL;
        printf("\n\tNow player is at position = %d", playerPosition);
    }
    if (temp->isSnake == 1)
    {
        printf("\n\tSnake has been reached");
        printf("\n\tSnake length = %d", temp->lengthSL);
        // subtract from player position
        playerPosition -= temp->lengthSL;
        printf("\n\tNow player is at position = %d", playerPosition);
    }

    pMove->node = searchNode(pMove->newPosition);

    if (headPlayer == tailPlayer && tailPlayer == NULL)
    {
        headPlayer = tailPlayer = pMove;
    }
    else
    {
        // add newnode after tail, then point to new node
        tailPlayer->next = pMove;
        // set tail to become new node
        tailPlayer = pMove;
    }
    printf("\nPlayer is at position: %d", playerPosition);
}

// Reverse the board
void reverse(struct Node **head)
{
    struct Node *temp = NULL;
    struct Node *prev = NULL;
    struct Node *current = (*head);
    while (current != NULL){
        temp = current->next;
        current->next = prev;
        prev = current;
        current = temp;
    }
    (*head) = prev;
}

// Print the board
void printBoard(slBoard *node)
{
    int i, counter = 0;

    while (node != NULL)
    {
        counter++;

        printf("%d  ", node->nodeIndex);
        if (counter % 8 == 0)
        {
            printf("\n");
        }
        node = node->next;
    }
}

// Search for the node with index = i
slBoard *searchNode(int i)
{

    if (head == NULL)
    {
        return NULL;
    }
    else
    {
        slBoard *cursor = head;
        while (cursor != NULL)
        {
            if (cursor->nodeIndex == i)
            {
                return cursor;
            }
            else
            {
                cursor = cursor->next;
            }
        }
    }
}

void main()
{
    srand(time(NULL));
    // create game board
    printf("\n\n=========== Gameboard =============\n");
    createGameBoard();
    // hold num snakes and ladders
    int numSnakes = 0, numLadders = 0;
    // Enter number of snakes and ladders from user
    printf("\n\nEnter number of snakes: ");
    scanf("%d", &numSnakes);
    printf("Enter number of ladders: ");
    scanf("%d", &numLadders);

    // initialise snake and ladder size
    int snakeSize = 0, ladderSize = 0;

    // used to check if is in bounds of game board
    int resultSnake = 0;
    int resultLadder = 0;

    // SNAKE INSERTION IMPLEMENTATION
    printf("\n=========== Snake Insertion =============\n");
    for (int i = 0; i < numSnakes; i++)
    {
        // generate rand num in bounds of board size
        int randNumPointer = randomNumbers(2, boardSize - 1);
        // get node that's equal to this rand num
        slBoard *temp = searchNode(randNumPointer);
        // check out of bounds resultSnake
        do
        {
            snakeSize = randomNumbers(MIN_SL_SIZE, MAX_SL_SIZE);
            resultSnake = temp->nodeIndex - snakeSize;
            printf("\nResult snake %d\n", resultSnake);
        } while (resultSnake < 1);
        temp->isSnake = 1;
        temp->lengthSL = snakeSize;
        printf("Inserted at %d\n", temp->nodeIndex);
        printf("Snake length = %d\n", temp->lengthSL);
    }

    // LADDER INSERTION IMPLEMENTATION
    printf("\n=========== Ladder Insertion =============\n");
    for (int i = 0; i < numLadders; i++)
    {
        // generate rand num in bounds of board size
        int randNumPointer = randomNumbers(2, boardSize - 1);
        // get node that's equal to this rand num
        struct Node *temp = searchNode(randNumPointer);
        // check out of bounds resultLadder
        do
        {
            ladderSize = randomNumbers(MIN_SL_SIZE, MAX_SL_SIZE);
            resultLadder = temp->nodeIndex + ladderSize;

            printf("\nResult ladder %d\n", resultLadder);
        } while (resultLadder < 1 && temp->isSnake == 1);
        temp->isLadder = 1;
        temp->lengthSL = ladderSize;
        printf("Inserted at %d\n", temp->nodeIndex);
        printf("Ladder length = %d\n", temp->lengthSL);
    }
    // GAMEPLAY IMPLEMENTATION
    printf("\n=========== Gameplay =============\n");
    printf("\nBoard Size = %d\n", boardSize);
    // Continue playing while player hasn't won
    do
    {
        getchar();
        //  roll dice
        int randDice = randomNumbers(1, 6);
        // check if rolled dice doesn't lead to out of bounds
        // temp player position to check if its out of bounds
        int tempPlayerPos = playerPosition + randDice;
        if (tempPlayerPos > boardSize)
            printf("\n\nDice Roll: %d Move Invalid", randDice);
        else
        {
            printf("\nRolled dice = %d", randDice);
            // slBoard *temp = searchNode(playerPosition);

            // add player path node to linked list
            playerMovesList(randDice);
        }
    } while (playerPosition != boardSize);
    printf("\nPlayer has won\n");

    // FILE IMPLEMENTATION
    printf("\n=========== SAVING PLAYER PATH TO FILE =============\n");
    FILE *file = fopen(FILE_NAME, "w");
    // check if file was created
    if (file == NULL)
    {
        printf("\nError!!! File not created. \n");
    }
    else
    {
        playerMoves *cursor = headPlayer;
        while (cursor->next != NULL)
        {
            //print to file
            fprintf(file,
                    "%s, currPosition = %d\n, newPosition = %d\n, rolledDice = %d\n, isLadder = %d\n, isSnake = %d\n, length = %d\n\n",
               "path_", cursor->currentPosition, cursor->newPosition, cursor->randStrDice,
               cursor->node->isLadder, cursor->node->isSnake, cursor->node->lengthSL);

            cursor = cursor->next;
        }
    }
    fclose(file);

    printf("\nFile created and saved successfully. \n");
}
