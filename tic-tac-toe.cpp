#include<bits/stdc++.h>
using namespace std;

const int max_size = 4;
char Board[max_size+1][max_size+1];
char player = 'X';
char opponent = 'O';

//Function prototypes
pair<int,int> findBestMove();
int minimax(int,bool,int,int);
int evaluate();
void printBoard();
bool gameOver();
bool isMovesLeft();

int main(){
	
	//code to initialize the cells of the board
	//all the cells are empty when the game starts
	for(int i = 1; i <= max_size; ++i){
		
		for(int j = 1; j <= max_size; ++j){
			
			Board[i][j] = '_';
		}
	}
	
	printBoard();
	
	do{
		
		if(gameOver()){
			break;
		}
		
		cout<<"Enter the coordintes: ";
		
		int x,y;
		cin>>x>>y;
		
		Board[x][y] = opponent;
		
		//function to clear the screen
		system("CLS");
		
		printBoard();
		
		if(gameOver()){
			break;
		}
		
		pair<int,int> a = findBestMove();
		
		Board[a.first][a.second] = player;
		
		system("CLS");
		
		printBoard();
		
		if(gameOver()){
			break;
		}
		
	}while(true);
	
	return 0;
}

//finds the best move for the computer(O) among all the available moves
//this function evaluates all the available moves using minimax and returns the one with maximum value

pair<int, int> findBestMove(){
	
	pair<int,int> best = {0,0};
	int mx = -1000;
	
	for(int i = 1; i <= max_size; ++i){
		
		for(int j = 1; j <= max_size; ++j){
			
			if(Board[i][j] == '_'){
				
				Board[i][j] = player;
				
				int t = minimax(0,false, -1000, 1000);
				
				if(t > mx){
			    	best = {i,j};
			    	mx = t;
			    }
				
				Board[i][j] = '_';
			}
		}
	}
	
	return best;
}

//this function is the implementation of minimax algorithm to find the value of a move using bactracking
//this function also incorporates alpha-beta pruning to improve efficiency

int minimax(int depth, bool isMax,int alpha, int beta){
	
	int score = evaluate();
	
	if(score == 10 || score == -10) return score;
	
    if(!isMovesLeft()) return 0;
	
	if(isMax){
	
	   int best = -1000;
	   
	   for(int i = 1; i <= max_size; ++i){
	   
	       for(int j = 1; j <= max_size; ++j){
		   
		        if(Board[i][j] == '_'){
				
				     Board[i][j] = player;
					 
					 best = max(best, minimax(depth+1, false,alpha, beta));
					 
		             alpha = max(best, alpha);
					 
					 Board[i][j] = '_';
					 
					 if(beta <= alpha){
					 	
					 	   i = max_size+1;
					 	   break;
					 }
				}
			}
		}
		
		return best - depth;
	}
	
	else{
		
		int best = 1000;
		
		for(int i = 1; i <= max_size; ++i){
			
			for(int j = 1; j <= max_size; ++j){
				
				if(Board[i][j] == '_'){
					
					Board[i][j] = opponent;
					
					best = min(best, minimax(depth+1, true,alpha,beta));
					
					beta = min(beta, best);
					
					Board[i][j] = '_';
					
					if(beta <= alpha){
						
						i = max_size+1;
						break;
					}
				}
			}
		}
		
		return best + depth;
	}
}

//function to evaluate to board according to the rules of tic-tac-toe
//returns 10 if computer(O) is winning
//returns -10 if opponent(X) is winning
//returns 0 in case of a draw
				
				
int evaluate(){

    for(int row = 1; row <= max_size; ++row){
	
	     int cnt_x = 0;
	     int cnt_o = 0;
	     for(int i = 1; i <= max_size; ++i){
		 
		     	cnt_x += (Board[row][i] == 'X');
				cnt_o += (Board[row][i] == 'O');
		 }
		 
		 if(cnt_x == max_size) return 10;
		 if(cnt_o == max_size) return -10;
	}
	
	for(int col = 1; col <= max_size; ++col){
		
		int cnt_x = 0;
		int cnt_o = 0;
		for(int i = 1; i <= max_size; ++i){
			
			cnt_x += (Board[i][col] == 'X');
			cnt_o += (Board[i][col] == 'O');
		}
		
		if(cnt_x == max_size) return 10;
		if(cnt_o == max_size) return -10;
	}
	
	int cnt_x = 0;
	int cnt_o = 0;
	for(int i = 1; i <= max_size; ++i){
		
		cnt_x += (Board[i][i] == 'X');
		cnt_o += (Board[i][i] == 'O');
	}
	
	if(cnt_x == max_size) return 10;
	if(cnt_o == max_size) return -10;
	
	cnt_x = 0;
	cnt_o = 0;
	
	for(int i = 1; i <= max_size; ++i){
		
		cnt_x += (Board[i][max_size-i+1] == 'X');
		cnt_o += (Board[i][max_size-i+1] == 'O');
	}
	
	if(cnt_x == max_size) return 10;
	if(cnt_o == max_size) return -10;
	
	return 0;
}


void printBoard(){
	
	cout<<"\tComputer - X\n";
	cout<<"\tYou      - O\n\n";
	
	for(int row = 1; row <= max_size; ++row){
		
		cout<<"\t\t";
		
		for(int col = 1; col <= max_size; ++col){
			
			cout<<Board[row][col]<<"  ";
		}
		cout<<"\n\n";
	}
}


bool isMovesLeft(){
	
	for(int row = 1; row <= max_size; ++row){
		
		for(int col = 1; col <= max_size; ++col){
			
			if(Board[row][col] == '_') return true;
		}
	}
	
	return false;
}

bool gameOver(){
	
	int score = evaluate();
	
	if(score == 10){
		
		cout<<"Player X won\n";
		return true;
	}
	if(score == -10){
		
		cout<<"Player O won\n";
		return true;
	}
	if(!isMovesLeft()){
		
		cout<<"Draw\n";
		return true;
	}
	
	return false;
}
