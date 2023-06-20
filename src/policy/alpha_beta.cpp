#include <cstdlib>
#include <map>
#include <climits>
#include "../state/state.hpp"
#include "./alpha_beta.hpp"
using namespace std;

/**
 * @brief Get a legal action with minimax
 * 
 * @param state Now state
 * @param depth Now depth
 * @return Move 
 */

Move Alpha_Beta::get_move(State *state, int depth, int alpha, int beta, int player){

  state -> get_legal_actions();

  Move move;
  int val;
  if (state->player) 
    val = INT_MAX;
  else
    val = INT_MIN;
  for (Move item : state->legal_actions) {
    State* next = state->next_state(item);
    int evaluate = AB_Evaluate(next, depth - 1, alpha, beta, 1 - state->player);
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
  }

 return move;
}


int Alpha_Beta::AB_Evaluate(State* next_state, int depth, int alpha, int beta, int player_is_black) {
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
      int HEU = AB_Evaluate(NEXT, depth - 1, alpha, beta, 1 - player_is_black);
      delete NEXT;
      H = max(H, HEU);
      alpha = max(alpha, H);
      if (alpha >= beta)
        break; 
    }

  }
  else {
    H = INT_MAX;
    for (auto next : next_state->legal_actions) {
      State* NEXT = next_state->next_state(next);
      int HEU = AB_Evaluate(NEXT, depth - 1, alpha, beta, 1 - player_is_black);
      delete NEXT;
      H = min(H, HEU); 
      beta = min(beta, H);
      if (alpha >= beta)
        break;
    }
  }
  return H;
}