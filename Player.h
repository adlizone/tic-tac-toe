#include "game.h"
#include<set>
#include<iostream>
#include<algorithm>
#include<assert.h>
#include<vector>
#include<cstdlib>
#include<ctime>

const int inf = 1e9 + 7;

using namespace std;

class Player {
	
	private:
		char letter;
		
	public:
		Player(char ch) { letter = ch; };
		char get_letter(){
		    return letter;
		};
};


class HumanPlayer : public Player {
	
	public:
		HumanPlayer(char ch): Player(ch) {};
		int get_move(Game);
};

//Gets a number from 0 to 8 from the console		
inline int HumanPlayer::get_move(Game game) {
	
	cout<<"Available moves are: ";
	
	set<int> moves = game.get_available_moves();
	
	for(auto move : moves) {
		
		cout<<move<<" ";
	}
	
	cout<<"\nEnter a valid move: ";
    
	int pos;
	cin>>pos;
	
	try {
		
		if(pos < 0 || pos > 8 || !moves.count(pos))
			throw pos;
	}
	catch(int pos) {
		
		bool condition = true;
		while(condition) {
			
			cout<<"Enter a valid number! ";
			cin>>pos;
			
			if(pos >= 0 && pos <= 8 && moves.count(pos))
				condition = false;
		}
		return pos;
	}
	
	return pos;
}

/* RandomComputerPlayer plays randomly using rand() and srand() */
class RandomComputerPlayer : public Player {
	
	public:
		RandomComputerPlayer(char ch) : Player(ch){};
		int get_move(Game);
};

/* Returns a random move among the available moves */
inline int RandomComputerPlayer::get_move(Game game) {
	
	set<int> moves = game.get_available_moves();
	
    srand(time(0));
	int pos;
	
	bool condition = true;
	while(condition) {
		
		pos = rand() % 9;
		if(moves.count(pos)) {
			
			condition = false;
		}
	}
	
	return pos;
}

/* OptimalComputerPlayer plays optimally using minimax algorithm */
class OptimalComputerPlayer : public Player {
	
	public:
		OptimalComputerPlayer(char ch) : Player(ch) {};
		int get_move(Game);
		int minimax(Game,char);
};

/* Returns the most optimal move among the available moves */
inline int OptimalComputerPlayer::get_move(Game game) {

	int pos;
	int best = -inf;
	
	set<int> moves = game.get_available_moves();
	
	for(auto move : moves) {
		
		game.make_move(move, get_letter());
		
		char other_player = (get_letter() == 'X' ? 'O' : 'X');
		
		int value = minimax(game, other_player);
		
		if(value > best) {
			
			pos = move;
			best = value;
		}
		
		game.make_move(move, '_');
	}
	
	return pos;
}

inline int OptimalComputerPlayer::minimax(Game game, char player) {
	
	char maximizer = get_letter();
	char minimiser = (get_letter() == 'O' ? 'X' : 'O');
	
	char other_player = (player == 'X' ? 'O' : 'X');
	
	if(game.get_current_winner() == other_player) {
		
		set<int> moves = game.get_available_moves();
		
		if(other_player == maximizer) {
			
			return (game.get_available_moves().size() + 1) * 1;
		}
		else {
			
			return (game.get_available_moves().size() + 1) * -1;
		}
	}
	
	int best;
	
	if(player == maximizer) best = -inf;
	else best = inf;
	
	for(auto move : game.get_available_moves()) {
		
		game.make_move(move, player);
		
		int value = minimax(game, other_player);
		
		game.make_move(move, '_');
		
		game.set_current_winner('_');
		
		if(player == maximizer) {
			
			best = max(best, value);
		}
		else {
			
			best = min(best, value);
		}
	}
	
	return best;
}
			
			
		
	
	
