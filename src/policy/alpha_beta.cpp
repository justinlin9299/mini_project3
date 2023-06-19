#include <cstdlib>
#include <map>
#include <climits>
#include "../state/state.hpp"
#include "./alpha_beta.hpp"
using namespace std;;

/**
 * @brief Get a legal action with minimax
 * 
 * @param state Now state
 * @param depth Now depth
 * @return Move 
 */

Move Alpha_Beta::get_move(State *state, int depth, int alpha, int beta, int player){
  if (!state->legal_actions.size()) {
    state -> get_legal_actions();
  }

  map<int, Move> heu_and_move;

  for (auto item : state->legal_actions) {
    State* next = state->next_state(item);
    int heu = AB_Evaluate(next, depth, alpha, beta, (state->player ^ 1));
    heu_and_move[heu] = item;
  }

  if (!player)
    return ((*heu_and_move.rbegin()).second);
  else
    return ((*heu_and_move.begin()).second);
}

int Alpha_Beta::AB_Evaluate(State* next_state, int depth, int alpha, int beta, int player_is_black) {
  int H = 0;
  if (!next_state->legal_actions.size()) {
    next_state->get_legal_actions();
  }
  if (!depth) {
    return next_state->evaluate();
  }

  if (!player_is_black) {
    H = -INT_MAX;
    for (auto next : next_state->legal_actions) {
      State* NEXT = next_state->next_state(next);
      int HEU = AB_Evaluate(NEXT, depth - 1, alpha, beta, 1);
      H = max(H, HEU);
      alpha = max(alpha, H);
      if (beta <= alpha)
        break; 
    }
  }
  else {
    H = INT_MAX;
    for (auto next : next_state->legal_actions) {
      State* NEXT = next_state->next_state(next);
      int HEU = AB_Evaluate(NEXT, depth - 1, alpha, beta, 0);
      H = min(H, HEU); 
      beta = min(beta, H);
      if (beta <= alpha)
        break;
    }
  }
  return H;
}