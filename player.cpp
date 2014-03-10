#include "player.h"
#include <vector>
#include <random>
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
	 int move = moves[rand() % moves.size()];
	 Move * output_move = new Move(move / 8, move % 8);
	 return output_move;	 
			  
}
