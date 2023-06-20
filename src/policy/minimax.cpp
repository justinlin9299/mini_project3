#include <cstdlib>
#include <map>
#include <climits>
#include "../state/state.hpp"
#include "./minimax.hpp"
using namespace std;;

/**
 * @brief Get a legal action with minimax
 * 
 * @param state Now state
 * @param depth Now depth
 * @return Move 
 */

Move Minimax::get_move(State *state, int depth, int player){

  state -> get_legal_actions();
 

  //map<int, Move> heu_and_move;
  Move move;
  int val;
  if (state->player) 
    val = INT_MAX;
  else
    val = INT_MIN;
  int eval;
  for (Move item : state->legal_actions) {
    State* next = state->next_state(item);
    int evaluate = Minimax_Evaluate(next, depth - 1, 1 - state->player);
    if(state->player){
      if(evaluate < val){
        move = item;
        val = evaluate;
      }
    }
    else{
      if(evaluate > val){
        move = item;
        val = evaluate;
      }
    }
    //heu_and_move[heu] = item;
  }
  return move;
  // if (!player)
  //   return ((*heu_and_move.rbegin()).second);
  // else
  //   return ((*heu_and_move.begin()).second);
}

int Minimax::Minimax_Evaluate(State* next_state, int depth, int player_is_black) {
  int H = 0;
  
  if (depth == 0 || !next_state->legal_actions.size()) {
    return next_state->evaluate();
  }
  if (!next_state->legal_actions.size()) {
    next_state->get_legal_actions();
  }

  if (player_is_black == 0) {
    H = INT_MIN;
    for (auto next : next_state->legal_actions) {
      State* NEXT = next_state->next_state(next);
      int HEU = Minimax_Evaluate(NEXT, depth - 1, 1-player_is_black);
      delete NEXT;
      H = max(H, HEU); 
    }
  }
  else {
    H = INT_MAX;
    for (auto next : next_state->legal_actions) {
      State* NEXT = next_state->next_state(next);
      int HEU = Minimax_Evaluate(NEXT, depth - 1, 1-player_is_black);
      delete NEXT;
      H = min(H, HEU); 
    }
  }
  return H;
}