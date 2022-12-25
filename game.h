#include<set>
#include<iostream>
#include<algorithm>
#include<assert.h>
#include<vector>
#include<cstdlib>
#include<ctime>

using namespace std;

class Game {
	
	private:
		char Board[3][3];
		char current_winner = '_'; //Underscore means no current winner
		
	public:
		
		Game();
		void print_board_nums();
		void print_board();
		bool make_move(int,char);
		bool is_moves_available();
		set<int> get_available_moves();
		bool check_win(int);
		bool tie();
		char get_current_winner();
		void set_current_winner(char);
};

