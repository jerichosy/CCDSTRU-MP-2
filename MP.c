#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

/*
    CCDSTRU MP - Group 13
        SY, MATTHEW JERICHO GO
        COMLA, AYRTON RAPHAEL SANTOS
        TUANGCO, RALPH CHRISTIAN ARCIAGA
*/

typedef char Result[9];

/*
    Clears the console after every iteration of both players choosing their letters.
*/
void clear_screen() {
    #ifdef __WIN32__
        system("cls");
    #else
        system("clear");
    #endif
}

/*
    DISPLAYS THE 5x5 BOARD

    Preview:                    Coordinates:
       | R | P | S | L | V |
    ---+---+---+---+---+---+    
     R |   |   |   |   |   |    (R,R) | (R,P) | (R,S) | (R,L) | (R,V)
    ---+---+---+---+---+---+
     P |   |   |   |   |   |    (P,R) | (P,P) | (P,S) | (P,L) | (P,V)
    ---+---+---+---+---+---+
     S |   |   |   |   |   |    (S,R) | (S,P) | (S,S) | (S,L) | (S,V)
    ---+---+---+---+---+---+
     L |   |   |   |   |   |    (L,R) | (L,P) | (L,S) | (L,L) | (L,V)
    ---+---+---+---+---+---+
     V |   |   |   |   |   |    (V,R) | (V,P) | (V,S) | (V,L) | (V,V)
    ---+---+---+---+---+---+
*/
void display_board(char M[5][5], char A[5]) {
    int i, j;

    printf("\n   | R | P | S | L | V |\n");
    printf("---+---+---+---+---+---+");

    printf("\n");


    // char A[5] = {'R', 'P', 'S', 'L', 'V'};

    for (i = 0; i < 5; i++)
    {
        printf(" %c | ", A[i]);

        for (j = 0; j < 5; j++)
        {
            if (j < 4)
                printf("%c | ", M[i][j]);
            else
                printf("%c |", M[i][j]);
        }

        if (i < 5)
        {
            printf("\n");
            printf("---+---+---+---+---+---+\n");
        }
    }
}

/*
    Initializes the board with blank spaces.
*/
void init_board(char M[5][5]) {
    int i, j;	
    
    for(i = 0; i < 5; i++)
        for(j = 0; j < 5; j++)
            M[i][j] = ' ';	// Initialize with blank space
}

/*
    Check if the player's input is outside the range of the set A.
    Returns TRUE if yes (outside range), FALSE otherwise.
*/
int check_input_outside_range(char cInput, char A[5]) {
    int i;
    int outside = 1;
    
    for (i = 0; i < 5; i++) {
        // printf("%c %c\n", cInput, A[i]);
        if (cInput == A[i])
            outside = 0;
    }

    // printf("%d", outside);
    if (outside)
        return TRUE;
    else
        return FALSE;
}

/*
    Linear search through the array A / set A.
    Returns the index.
*/
int get_index(char cInput, char A[5]) {
    int i;
    int index = -1;
    
    for (i = 0; i < 5; i++) {
        if (cInput == A[i])
            index = i;
    }
    
    return index;
}

/*
    Updates the board based on the player's input.
*/
void update_board(char M[5][5], char one, char two, char A[5]) {
    int nRow, nCol;
    
    // Translate one and two to positions on the board
    nRow = get_index(one, A);
    nCol = get_index(two, A);
    
    /* debugging
    printf("%d", nRow);
    printf("%d", nCol);
    scanf(" %c", one);
    */
    
    M[nRow][nCol] = 'X';
}

/*
    Finds if both player's input constitute a set which exists in a given set (either D or E).
    Returns TRUE if it's found, FALSE otherwise.
*/
int find_in_set(char set[10][2], char two, char one) {
    int i;
    int found = FALSE;
    
    for (i = 0; i < 10; i++) {
        if (two == set[i][0])
            if (one == set[i][1])
                found = TRUE;
    }
    
    if (found)
        return TRUE;
    else
        return FALSE;
}

/*
    Takes the player's input then calls the find_in_set() function. 
        If it's found, determines the set and calculates the score (value of the pos variable) accordingly.
    Returns the score (pos value) for that particular turn/round.
*/
int calculate_score(char two, char one, int F, int pos) {
    // NOTE: Set T is not included as it has no bearing on pos (i.e. doesn't affect the points/score)
    
    // set D
    char D[10][2] = {"LV", "VS", "SP", "PR", "RL", "RS", "PV", "SL", "VR", "LP"};  // same as char D[10][2] = { {'L', 'V'}, {'V', 'S'}, ... };
    
    // set E
    char E[10][2] = {"RP", "LR", "RV", "PS", "PL", "SR", "SV", "LS", "VP", "VL"};
    
    if (F == 4) {
        if (find_in_set(D, two, one))  // find in set D
            return pos = -3;
        if (find_in_set(E, two, one))  // find in set E
            return pos = 3;
    }
    else {
        if (find_in_set(D, two, one))  // find in set D
            return pos += -1;
        if (find_in_set(E, two, one))  // find in set E
            return pos += 1;
    }
    
    return pos;  // return the same value again (no change) should it be a subset of T
}

/*
    Determines the winner based on the score (value of pos).
*/
void determine_winner(Result result, int pos) {
    if (pos == -3)
        strcpy(result, "Dos Wins");
    else if (pos == 3)
        strcpy(result, "Uno Wins");
    else
        strcpy(result, "Tie");
}


int main() {
    char M[5][5] = {};
    init_board(M);
    
    // Sys init
    char A[5] = {'R', 'P', 'S', 'L', 'V'};
    int over = 0;
    int pos = 0;  // score
    int F = 0; 

    char Uno, one, Dos, two;
    Result result;
    
    int repeat;
    
    /* --- PRINT INFO --- */
    printf("CCDSTRU MP\n");
    printf("- SY, MATTHEW JERICHO GO\n");
    printf("- COMLA, AYRTON RAPHAEL SANTOS\n");
    printf("- TUANGCO, RALPH CHRISTIAN ARCIAGA\n");
    printf("-----------------------------------\n");
    printf("\n");
    
    printf("Game Instructions: \n");
    printf("- There are two players\n");
    printf("- In each turn, both players will choose a letter from set A = {R, P, S, L, V}.\n");
    printf("- Together, both players' choices will be used to form a cartesian product G\n");
    printf("      based on Player 2's and Player 1's choices. See scoring section for more info.\n");
    printf("- There is a maximum of 5 turns. It's possible to win in 3 turns.\n");
    printf("- Should the game reach the 5th turn, the result of that turn overrules all\n");
    printf("      scores gained from all previous turns.\n");
    printf("\n");

    printf("Scoring: \n");
    printf("- G is the cartesian product of Player 2's and Player 1's choices.\n");
    printf("- If G is a subset of D, the score will DECREASE by 1.\n");
    printf("- If G is a subset of E, the score will INCREASE by 1.\n");
    printf("- If G is a subset of T (both players' choices are the same), there is no effect on the score.\n");
    printf("- If the score reaches either -3 or +3, the game stops and a winner is determined based on the ff:\n");
    printf("    - If the score is -3, Player 2 wins.\n");  // Dos wins
    printf("    - If the score is +3, Player 1 wins.\n");  // Uno wins
    printf("\n");

    printf("Scoring for the final (5th) turn: \n");  // (if |F| = 4)
    printf("- If G is a subset of D, Player 2 instantly wins.\n");  // Dos instantly wins
    printf("- If G is a subset of E, Player 1 instantly wins.\n");  // Uno instantly wins
    printf("\n");
    
    printf("Sets: \n");
    printf("  D = { {L, V}, {V, S}, {S, P}, {P, R}, {R, L}, {R, S}, {P, V}, {S, L}, {V, R}, {L, P} }\n");
    printf("  E = { {R, P}, {L, R}, {R, V}, {P, S}, {P, L}, {S, R}, {S, V}, {L, S}, {V, P}, {V, L} }\n");
    

    /* --- GAME START --- */
    
    display_board(M, A);
    
    do
    {	
        if (F < 5 && pos != -3 && pos != 3)
        {
            printf("\nTurn: %d", F + 1);
            
            printf("\n\nIt's %s turn.", "Uno");
            do
            {
                repeat = FALSE;
                printf("\nInput: ");
                scanf(" %c", &one);
                
                if (check_input_outside_range(one, A))
                    printf("    INVALID INPUT! Input a character that's within the set A.");
                else if (one == Uno) {
                    printf("    INVALID INPUT! You cannot input a character that you entered in your previous turn.");
                    repeat = TRUE;;
                }
                else
                    Uno = one;

            }while(check_input_outside_range(one, A) || repeat);
            
            printf("\nIt's %s turn.", "Dos");
            do
            {
                repeat = FALSE;
                printf("\nInput: ");
                scanf(" %c", &two);
                
                if (check_input_outside_range(two, A))
                    printf("    INVALID INPUT! Input a character that's within the set A.");
                else if (two == Dos) {
                    printf("    INVALID INPUT! You cannot input a character that you entered in your previous turn.");
                    repeat = TRUE;
                }
                else
                    Dos = two;

            }while(check_input_outside_range(two, A) || repeat);
            
            
            /* --- UPDATE STUFF --- */
            update_board(M, one, two, A);
            pos = calculate_score(two, one, F, pos);
            
            
            /* --- VIEW THE CHANGES --- */
            clear_screen();  // system("cls");
            
            printf("Sets: \n");
            printf("  D = { {L, V}, {V, S}, {S, P}, {P, R}, {R, L}, {R, S}, {P, V}, {S, L}, {V, R}, {L, P} }\n");
            printf("  E = { {R, P}, {L, R}, {R, V}, {P, S}, {P, L}, {S, R}, {S, V}, {L, S}, {V, P}, {V, L} }\n");
    
            display_board(M, A);
            
            printf("\npos (Score): %d\n\n", pos);
            
        }
        else {
            /* --- GAME END --- */
            over = TRUE;
            determine_winner(result, pos);
            printf("%s", result);
        }
            
        // END of loop
        F++;
    }while(!over);
    
    
    return 0;
}
