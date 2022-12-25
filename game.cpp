#include "Player.h"
#include<set>
#include<iostream>
#include<algorithm>
#include<assert.h>
#include<vector>
#include<cstdlib>
#include<ctime>

using namespace std;

//This function sets each board position to '_' meaning empty
inline Game::Game() {
	
	for(int i = 0; i < 3; ++i) {
		
		for(int j = 0; j < 3; ++j) {
			
			Board[i][j] = '_';
		}
	}
}

inline void Game::print_board_nums() {
	
	for(int i = 0; i < 3; ++i) {
		cout << '|';
		for(int j = 0; j < 3; ++j) {
			
			cout << (i*3) + j << '|';
		}
		cout << endl;
	}
}

inline void Game::print_board() {

    for(int i = 0; i < 3; ++i) {
    	
    	cout<<'|';
    	
		for(int j = 0; j < 3; ++j) {
    		
    		cout << Board[i][j] << '|';
    	}
    	cout << endl;
    }
}
 
/* The function takes in the board position(0-8) and the letter(O/X)
   and makes the move at the given postion and returns true */ 
inline bool Game::make_move(int pos, char letter) {
	
	assert(pos >= 0 && pos <= 8);
	
	if(!is_moves_available())
	   return false;
	   
	int row = pos / 3;
	int col = pos % 3;
	
	Board[row][col] = letter;
	
	if(check_win(pos)) {
		
		current_winner = letter;
	}
	
	return true;
}

/*Return all the available moves on the board as vector of integers */
inline set<int> Game::get_available_moves() {
	
	set<int> temp;
	
	for(int i = 0; i < 3; ++i) {
		
		for(int j = 0; j < 3; ++j) {
			
			if(Board[i][j] == '_') {
				
				temp.insert((3*i)+j);
			}
		}
	}
	
	return temp;
}

/* Returns true if the last move was a winning move. Return false otherwise*/
inline bool Game::check_win(int pos) {
	
	assert(pos >= 0 && pos <= 8);
	
	int row = pos / 3;
	int col = pos % 3;
	
	if(Board[row][0] == Board[row][1] && Board[row][1] == Board[row][2])
	    return true;
	
	if(Board[0][col] == Board[1][col] && Board[1][col] == Board[2][col])
	    return true;
	    
	//if pos is a belongs to first diagonal
	if(pos == 0 || pos == 4 || pos == 8) {
		
		if(Board[0][0] == Board[1][1] && Board[1][1] == Board[2][2])
	        return true;
	}
	
	//if pos is a belongs to second diagonal
	if(pos == 2 || pos == 4 || pos == 6) {
		
		if(Board[0][2] == Board[1][1] && Board[1][1] == Board[2][0])
	        return true;
	}
	
	return false;
}
	
inline bool Game::is_moves_available() {
	
	for(int i = 0; i < 3; ++i) {
		
		for(int j = 0; j < 3; ++j) {
			
			if(Board[i][j] == '_') 
			    return true;
		}
	}
	
	return false;
}

inline bool Game::tie() {
	
	return is_moves_available();
}

inline char Game::get_current_winner() {
	
	return current_winner;
}

inline void Game::set_current_winner(char ch) {
	
	current_winner = ch;
}

int main(){
   
   Game game;
   HumanPlayer player1('X');
   OptimalComputerPlayer player2('O');
   
   game.print_board_nums();
   cout<<endl;
   game.print_board();
   
   char cur_player = player1.get_letter();
   
   while(true) {
		
		int pos;
		
		if(cur_player == player1.get_letter()) 
			pos = player1.get_move(game);
		else 
			pos = player2.get_move(game);
		
		game.make_move(pos, cur_player);
		game.print_board();
		cout<<endl;
		
		if(game.check_win(pos)) {
			
			cout<<cur_player<<" Won!\n";
			break;
		}
        
		if(cur_player == player1.get_letter()) {
			
			cur_player = player2.get_letter();
		}
		else {
			
			cur_player = player1.get_letter();
		}
    }
    
   return 0;
}


