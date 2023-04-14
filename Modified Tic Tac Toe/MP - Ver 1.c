#include <stdio.h>
#include <string.h>
#include<stdbool.h>

typedef char string[2];
typedef string board[4][4];


//Initializes the entire board to blanks at the start
void initializeBoard(board board){
    int i,j;
    for(i=0; i<4; i++){
        for(j=0; j<4; j++){
            strcpy(board[i][j], " ");
        }
    }
}

//Prints the game board
void printBoard(board board){	
    printf("| %s | %s | %s | %s |\n", board[0][0], board[0][1], board[0][2], board[0][3]);
    printf("| %s | %s | %s | %s |\n", board[1][0], board[1][1], board[1][2], board[1][3]);
    printf("| %s | %s | %s | %s |\n", board[2][0], board[2][1], board[2][2], board[2][3]);
    printf("| %s | %s | %s | %s |\n", board[3][0], board[3][1], board[3][2], board[3][3]);
}

//Gets the row from user input
int getRow(){
    int row;
    do{
        printf("Enter row of choice: ");
        scanf("%d", &row);
    }while(row<1 || row>4);

    return row-1;
}

//gets the column from user input
int getColumn(){
    int col;
    do{
        printf("Enter column of choice: ");
        scanf("%d", &col);
    }while(col<1 || col>4);

    return col-1;
}

//Verifies if the move is in a restricted tile or not
int verifyRestriction(int row, int col){

    if(row==0 && col==0 || row==0 && col==1 || row==0 && col==2
    || row==1 && col==0 || row==2 && col==0)
        return 0;
    else
        return 1;

}

//Verifies the move of Cha; checks if the tile is taken; returns 1 if tile is empty otherwise
int verifyMoveCha(board board, int row, int col){
    //If Cha: cannot put move on tiles occupied by Cha or Ord
    if(strcmp(board[row][col], " ")==0)//if the tile is empty then the player can put move there
        return 1;
    else
        return 0;
}

//Verifies the move of Ord; also checks if Ord reaches the move limit
int verifyMoveOrd(board board, int row, int col, int count){
    //If Ord: cannot put move on tiles occupied by Cha;

    //if tile has Ord move and Ord move count is 4
    if(strcmp(board[row][col], "X") ==0 && count==4){ //undo a move
        return 2; //undo the move in that tile
    }
    //if tile is taken by either Ord or Cha given that move count of Ord is not yet 4
    else if(strcmp(board[row][col], "O") == 0 || strcmp(board[row][col], "X")== 0){
        return 0;
    }
    else //tile is free
        return 1;
}


//Checks if someone wins the game; returns 1 if Cha wins; returns 2 if Ord wins; returns 0 if neither wins
int checkWin(board board){
    int i, j, count=0;//count is the number of occupied spaces; maximum occupied spaces is 11
    
    //Counts the number of filled tiles; 
    for(i=1; i<4; i++){
    	for(j=1; j<4; j++){
    		if(strcmp(board[i][j], " ") != 0)
    			count++;
		}
	}

    //Win condition of Cha
    if( strcmp(board[0][3], "O") == 0 && strcmp(board[1][3], "O") == 0 && strcmp(board[2][3], "O") == 0
     || strcmp(board[1][1], "O") == 0 && strcmp(board[2][2], "O") == 0 && strcmp(board[3][3], "O") == 0
     || strcmp(board[1][2], "O") == 0 && strcmp(board[2][1], "O") == 0 && strcmp(board[3][0], "O") == 0
     || strcmp(board[3][1], "O") == 0 && strcmp(board[3][2], "O") == 0 && strcmp(board[3][3], "O") == 0)
        return 1;

    //Win condition of Ord- if all the tiles excluding H are filled, regardless of H, Ord wins
    else if(count == 9 && strcmp(board[0][3], " ") != 0 && strcmp(board[3][0], " ") != 0) 
        return 2;

    //No winner
    else
        return 0;
}

//Game function
void playGame(board board){
    initializeBoard(board); //initialize the game board
    int row,col, count=0;


    //System initialization
    bool turn= true; //true for Cha ; false for Ord


    do{

       printBoard(board);

       //Cha's turn
       if(turn){
           printf("\n\n Player Cha's Turn\n");
           printf("\nNote: You cannot place your move on RESTRICTED tiles: (1, 1),(1, 2),(1, 3),(2, 1),(3, 1)}\n" );
           do{
               	row=getRow();
               	col=getColumn();
               	
               	if(verifyMoveCha(board, row, col) ==0)
               		printf("Choose another tile. Tile is taken\n\n");
               	if(verifyRestriction(row, col) ==0)
               		printf("Tile is restricted. Choose another tile\n\n");
               		
           }while(verifyMoveCha(board, row, col) ==0 || verifyRestriction(row, col) ==0);

           strcpy(board[row][col],"O" );
           turn= false;
       }
       //Ord's turn

       //Need to add restriction; only 4 moves
       else{
           printf("\n\n Player Ord's Turn\n\n");

           if(count==4){ //If move count of Ord is 4; he first undo a move, then place his move to a new tile
               do{
               		printf("Enter the move you want to undo \n");
                   	row=getRow();
                   	col=getColumn();
                   	
                   	if(verifyMoveOrd(board, row, col, count) != 2)
                   		printf("Make sure the tile you selected is your tile\n\n");
                   		
               }while(verifyMoveOrd(board, row, col, count) !=2 );

               count--;

               strcpy(board[row][col]," ");
               printBoard(board);
           }

           do{
               	row=getRow();
               	col=getColumn();
               	
               	if(verifyMoveOrd(board, row, col, count) ==0 )
               		printf("Tile is taken. Choose another tile\n\n");

           }while(verifyMoveOrd(board, row, col, count) ==0 );
           strcpy(board[row][col],"X" );
           count++;

           turn=true;
       }

    }while(checkWin(board)==0);


    if(checkWin(board) ==1 )
        printf("Player Cha Wins!!!!");
    else
        printf("Player Ord Wins!!!!");

}

int main() {

    board gameBoard;

    playGame(gameBoard);

    return 0;
}



