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



void Player::populate(node* tree, Side side, int depth){
	 //what are all moves this side can do
	 //for each of those boards, what are all moves other side can do
	 if (depth == 0) {
		 return;
	 }
	 for (int i = 0; i < 8; i ++){
		 for (int j = 0; j < 8; j ++){
			 //if (board->occupied(i, j)){
			 //	   continue;
			 //}
			 Move * move = new Move(i, j);
			 if (board->checkMove(move, side)){
				 Board * board2 = board->copy();
				 node *new_node = new node(board2, move);
				 //new_node->score = value(move); 
				 populate(new_node, (side == BLACK ? WHITE : BLACK), depth-1);
				 tree->add_child(new_node);
			 }
		 }
	 }
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
     //does opponent's 	move
     if (opponentsMove != NULL){
		 board->doMove(opponentsMove, (side == BLACK ? WHITE : BLACK));
	 }
     // if there are no available moves
     if (!board->hasMoves(side)){
		 return NULL;
	 }
	 node* tree = new node(board, opponentsMove);
	 populate(tree, side, 4);
	 std::vector<node *> list1, list2, list3, list4;
	 list1 = tree->children;
	 for (unsigned int i = 0; i <list1.size(); i++){
		 list2.insert(list2.end(), list1[i]->children.begin(), list1[i]->children.end());
	 }
	 for (unsigned int i = 0; i <list2.size(); i++){
		 list3.insert(list3.end(), list2[i]->children.begin(), list2[i]->children.end());
	 }
	 for (unsigned int i = 0; i < list3.size(); i++){
		 list4.insert(list4.end(), list3[i]->children.begin(), list3[i]->children.end());
	 }
	 int low3 = 1000000;
	 int low1 = 1000000000;
	 int high2 = -1000000;
	 int high = -1000000;
	 for (unsigned int i = 0; i < list4.size(); i++){
		 Move* x = list4[i]->move;
		 list4[i]->score = value(8*(x->getX()) + x->getY());
	 }
	 for (unsigned int i = 0; i < list3.size(); i++){
		 // for child in children of list3[i]:
		 // if child is the lowest score, set list3[i]'s score as child's score.
		 list3[i]->score = low3;
		 for (unsigned int child = 0; child < list3[i]->children.size(); child ++){
			 if (list3[i]->children[child]->score < list3[i]->score){
				list3[i]->score = list3[i]->children[child]->score;
			}
		 }
	 }
	 for (unsigned int i = 0; i < list2.size(); i++){
		 list2[i]->score = high2;
		 for (unsigned int j = 0; j < list2[i]->children.size(); j++){
			 if (list2[i]->children[j]->score > list2[i]->score){
				list2[i]->score = list2[i]->children[j]->score;
			}
		 }
	 }
	 for (unsigned int i = 0; i < list1.size(); i++){
		 list1[i]->score = low1;
		 for (unsigned int j = 0; j < list1[i]->children.size(); j++){
			 if (list1[i]->children[j]->score < list1[i]->score){
				list1[i]->score = list1[i]->children[j]->score;
			}
		 }
	 }
	 Move* final_move;
	  for (unsigned int i = 0; i < list1.size(); i++){
		  if (list1[i]->score > high){
			  high = list1[i]->score;
			  final_move = list1[i]->move;
		  }
	  }	 
	 /*
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
	 */
	 //randomly playing moves 
	 //int move = moves[rand() % moves.size()];
	 //Move * output_move = new Move(move / 8, move % 8);
	 //return output_move;
	 
	 //playing moves using heuristic 
	 /*
	 int final_move;
	 for(unsigned int i = 0; i != moves.size(); i++) {
		 int value_move = -300;
		 if (value(moves[i]) > value_move){
			 value_move = value(moves[i]);
			 final_move = moves[i];
		 }
	 }	
	 */ 	 
	 std::cerr << final_move->getX() << " " << final_move->getY() << std::endl;
	 board->doMove(final_move, side);
	 return final_move;
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
