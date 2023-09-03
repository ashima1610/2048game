#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//defining the size of the board:  (4*4)
#define SIZE 4

int board[SIZE][SIZE];


//firstly. we'll initialize the board to have all values as 0.
void initializeBoard(){
	for(int i=0; i<SIZE; i++){
		for(int j=0; j<SIZE; j++){
			board[i][j]=0;
		}
	}
}

//printing the initial board.
void printBoard(){
	for(int i=0; i<SIZE; i++){
		for(int j=0; j<SIZE; j++){
			printf("%-6d", board[i][j]);
		}

		printf("\n");
	}
}

//checking if the board is completely full or has some space left.
int isFull(){
	for(int i=0; i<SIZE; i++){
		for(int j=0; j<SIZE; j++){
			if(board[i][j]==0){
				return 0;  //means it is not full.
			}
		}
	}

	return 1; //means if full.
}

int getRandomNumber(int lower, int upper){
	//here, lower and upper denote the range of the generated no.
	return lower + (rand()%(upper-lower+1));

	//the above is the syntax to create a random integer between the range upper and lower using the rand() function.
}

void addInitialRandomTile(){

	int row, col;

	do{
         	//generating random row, col values.
	        row = getRandomNumber(0, SIZE-1);
	        col = getRandomNumber(0, SIZE-1);
	}
	while(board[row][col]!=0);

	board[row][col] = 2;

}



void addRandomTile(){
	if(isFull()){
		//means the board is already full.
		return;
	}

	int row, col;
	//generating a random value of 2 or 4 using the rand() function.
	int value = (getRandomNumber(0,1)+1)*2;  //generates either 2 or 4.
        
	do{
			//creating random values for row, col until an empty cell is obtained.
			row = getRandomNumber(0, SIZE-1);
			col = getRandomNumber(0, SIZE-1);
			}
	while(board[row][col]!=0);

	//assigning the randomly generated value to the empty random cell obtained.
	board[row][col] = value;

}


//the below function controls movement of cells in specified direction(top/bottom/left/right) and merging 2 adjacent and equal cells.

int movedTiles(int row[], int size){
       //here row[] represents a row or column of the board.
       //and size represents the size of that row or column.
       
       //this function keeps a track of any cells that were moved or merged during execution.
	int moved=0;

	for(int i=0; i<size-1; i++){
		if(row[i]==0){
			//means it is an empty cell.
			
			//if the current tile is zero, it is  moved towards the beginning of the row/column.
			for(int j=i+1; j<size; j++){
				//checking subsequent cells until a non-zero cell obtained.
				if(row[j]!=0){
					row[i]=row[j];
					row[j]=0;
					moved=1;
					break;
				}
			}
		}
		else if(row[i]==row[i+1]){
			//when we get two adjacent cells with same data:

			row[i]=row[i]*2;  //multiply the current cell data by 2.
			row[i+1]=0;   //empty the another cell.
	       	        moved=1;
			//skipping the i+1 th cell which has become zero.
			i++;
		}
	}
	return moved;
}

int main(){

	srand(time(NULL));   //ensures that a different sequence of random numbers is generated everytime the program is executed.
	initializeBoard();

	//adding two random tiles to the board.
	addInitialRandomTile();
	addInitialRandomTile();
	printf("\n\t WELCOME TO 2048 GAME!!\t\n\n");
	printBoard();
        
	printf("\nRULES:\n");
	printf("\n1. Move the tiles in such a way that you get a 2048 valued-tile.\n");
	printf("2. You can move top, down, left, right using the (T/D/L/R) characters respectively.\n");
        printf("3. When two tiles with same values become adjacent, they merge into one.\n\n");

        while(1){
		//this loop will execute until there's a win or a lose.


		//flags tracking win or lose.
		int gameWon = 0;
		int gameLost = 1;

		for(int i=0; i<SIZE; i++){
			for(int j=0; j<SIZE; j++){
				if(board[i][j]==2048){
					//2048 tile found.
					//game won.
					gameWon = 1;
					break;
				}
				if(board[i][j]==0){
					//means an empty cell found.
					//therefore, continue game.
					gameLost = 0;
				}
			}

			if(gameWon==1){
				break;
			}
		}

                if(gameWon==1){
			printf("\n\t CONGRATULATIONS!! YOU WON. \t\n");
			break;
		}

		if(gameLost==1){
			printf("\n\t GAME OVER!! YOU LOST! \t\n");
			break;
		}

                //taking user-input.
		//if its neither a win nor a lose.
		char move;
		printf("Enter move(T/D/L/R): ");
		scanf(" %c", &move);

                //saving the current state of the board.
		int previousBoard[SIZE][SIZE];

		for(int i=0; i<SIZE; i++){
			for(int j=0; j<SIZE; j++){
				previousBoard[i][j]=board[i][j];
			}
		};
                 
	         int wrongMove = 0;
	         //updating the board according to user input.
	         switch(move){
	         	case 'T':
	         	case 't':
	         	      //on top move
                              //traversing column-wise
			      for(int j=0; j<SIZE; j++){
				      int row[SIZE];
				      for(int i=0; i<SIZE; i++){
					      row[i]=board[i][j];
				      }
				      if(movedTiles(row, SIZE)){
					      //means some tiles have been moved.
					      //update board accordingly.
					      for(int i=0; i<SIZE; i++){
						      board[i][j]=row[i];
					      }
				      }
			      }
			      break;

			case 'D':
			case 'd':
			      //on down move
			      //again traversing column-wise
			      for(int j=0; j<SIZE; j++){
				      int row[SIZE];
				      for(int i=0; i<SIZE; i++){
					      //storing row values for the particular column in reverse order
					      row[i] = board[SIZE-1-i][j];
				      }

				      if(movedTiles(row, SIZE)){
						      //i.e some tiles have been moved.
						      //upadte board accordinly.
						      for(int i=0; i<SIZE; i++){
						           board[SIZE-1-i][j]=row[i];
						       }
						       
				       }
			      }
		                 break;

			 case 'L':
			 case 'l':
			      //on left move
			      //traversing row-wise first.
			      for(int i=0; i<SIZE; i++){
				      int col[SIZE];
				      for(int j=0; j<SIZE; j++){
					      //storing col values for the particular row.
					      col[j] = board[i][j];
				      }

				      if(movedTiles(col, SIZE)){
						      //i,e some tiles have been moved.
						      //update board accordingly.
						      for(int j=0; j<SIZE; j++){
						          board[i][j]=col[j];
						      }
				      }
			      }
			        break;

			 case 'R':
                         case 'r':
			      //on right move
			      //traversing row- wise first.
                              for(int i=0; i<SIZE; i++){
				      int col[SIZE];
				      for(int j=0; j<SIZE; j++){
					      //storing col values for the particular row in reverse order.
					      col[j] = board[i][SIZE-j-1];
				      }

				      if(movedTiles(col, SIZE)){
					      //i.e some tiles have been moved.
					      //update board accordingly.
					      for(int j=0; j<SIZE; j++){
						      board[i][SIZE-j-1]=col[j];
					      }
				      }
			      }
			        break;

		       default:
			      printf("Invalid move. Use (T/D/L/R)\n");
			      continue;
                             
                       }
                 

		//check if the board has changed.
		int boardChanged = 0;
		for(int i=0; i<SIZE; i++){
			for(int j=0; j<SIZE; j++){
				if(board[i][j]!=previousBoard[i][j]){
					boardChanged=1;
					break;
				}
			}
			if(boardChanged){
				break;
			}
		}

		if(boardChanged){
			//i.e there was some movement in the tiles.
			addRandomTile();
			printBoard();
		}
		else{
			printf("No movement possible in this direction.\n");
		}

	}

	return 0;

}


