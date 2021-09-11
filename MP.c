#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

/*
	CCDSTRU MP - Group []
		SY, MATTHEW JERICHO GO
		[]
		[]
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

void init_board(char M[5][5]) {
	int i, j;	
	
	for(i = 0; i < 5; i++)
		for(j = 0; j < 5; j++)
			M[i][j] = ' ';	// Initialize with blank space
}

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

int get_index(char cInput, char A[5]) {
	int i;
	int index = -1;
	
	for (i = 0; i < 5; i++) {
        if (cInput == A[i])
            index = i;
    }
    
    return index;
}

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

int find_in_set(char set[10][2], char two, char one) {
	int i, j;
	
	for ()
}

// TODO: calculate_score()
int calculate_score(char two, char one) {
	// set D
	char D[10][2] = { {'L', 'V'}, {'V', 'S'}  };
	
	// find in set D
	find_in_set(D, two, one)
}

// TODO:
int determine_winner() {
	// Print who won here instead of main
}


int main() {
	char M[5][5] = {};
	init_board(M);
	
    // Sys init
	char A[5] = {'R', 'P', 'S', 'L', 'V'};
    int over = 0;
    int pos = 0;
    int F = 0; 		// TODO: ctr?

    char Uno, one, Dos, two;

    // int turn = 1;
    int repeat;
	
	/* --- PRINT INSTRUCTIONS --- */
	printf("Game Instructions: \n");
    printf("- There are two players\n");
    printf("- In each turn, a player will choose a letter from set A = {R, P, S, L, V}");
    printf("\n\n");

	printf("Scoring: \n");
    printf("- If G exists in set D, pos (score) will decrease by 1.\n");
    printf("- If G exists in set E, pos (score) will increase by 1.\n");
    printf("- If G exists in set T, no points will be added.\n");

    printf("Scoring If |F| = 4 \n");
    printf("If G exists in set D, uno instantly wins.\n");
    printf("If G exists in set E, dos instantly wins.\n");
    

	/* --- GAME START --- */
	
	display_board(M, A);
	
	do
	{
		// turn = !turn;
        // printf("\n\nIt's %s turn.", turn ? "Dos" : "Uno");
        

		// if () | TODO: Instant win?
			
        if (F < 4) // TODO: Change F later
        {
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
            
            
			update_board(M, one, two, A);
			// TODO: pos = calculate_score(two, one);
			
			// system("cls");
			clear_screen();
        	display_board(M, A);
        	
        }
        else
        	over = TRUE;
        	
    	// TODO: over = determine_winner();
        	
        // END of loop
        F++;
	}while(!over);
	
	
	return 0;
}
