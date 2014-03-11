#include "player.h"
#include <vector>
#include <cstdlib>

//Hi! I really hope this works. Okay bye. :)

//Your comments worked! 

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish 
 * within 30 seconds.
 */
 
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    /* 
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
     this->side = side;
     board = new Board();  
}

/*
 * Destructor for the player.
 */
Player::~Player() {
	delete board;
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be NULL.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return NULL.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /* 
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */ 
     //does opponent's move
     if (opponentsMove != NULL){
		 board->doMove(opponentsMove, (side == BLACK ? WHITE : BLACK));
	 }
     // if there are no available moves
     if (!board->hasMoves(side)){
		 return NULL;
	 }
	 std::vector<int> moves;
	 for (int i = 0; i < 8; i ++){
		 for (int j = 0; j < 8; j ++){
			 //if (board->occupied(i, j)){
			 //	   continue;
			 //}
			 Move * move = new Move(i, j);
			 if (board->checkMove(move, side)){
				 moves.push_back(8*i + j);
			 }
		 //delete move;
		 }
	 } 
	 //randomly playing moves 
	 //int move = moves[rand() % moves.size()];
	 //Move * output_move = new Move(move / 8, move % 8);
	 //return output_move;
	 
	 //playing moves using heuristic 
	 int final_move;
	 for(unsigned int i = 0; i != moves.size(); i++) {
		 int value_move = -300;
		 if (value(moves[i]) > value_move){
			 value_move = value(moves[i]);
			 final_move = moves[i];
		 }
	 }	 
	 Move * final = new Move(final_move / 8, final_move % 8);	 
	 board->doMove(final, side);
	 return final;
}

int Player::value(int move) {
	Board * board = this->board->copy();
	int value = board->count(side) - board->count((side == BLACK ? WHITE : BLACK));
	//assigning higher value to corner pieces
	if (move == 0 || move == 63 || move == 56 || move == 7) {
		value *= 3;
	}
	//assigning lower value to pieces adjacent to corner
	else if (move == 9 || move == 8 || move == 1 || move == 6 || move == 14 || move == 15){
		value *= -3;
	}
	else if (move == 54 || move == 55 || move == 62 || move == 48 || move == 49 || move == 57){
		value *= -3;
	}
	//else if (move == 2 || move == 3 || move == 4 || move == 5 || move == 16 || move == 24 || move == 32 || move == 40){
	//	value *= 1.5;
	//}
	//else if (move == 23 || move == 31 || move == 39 || move == 47 || move == 58 || move == 59 || move == 60 || move == 61){
	//	value *= 1.5;
	//}
	delete board;
	return value;
}
