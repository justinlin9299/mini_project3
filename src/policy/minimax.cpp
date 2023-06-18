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
  if (!state->legal_actions.size()) {
    state -> get_legal_actions();
  }

  map<int, Move> heu_and_move;

  for (Move item : state->legal_actions) {
    State* next = state->next_state(item);
    int heu = Minimax_Evaluate(next, depth, (state->player ^ 1));
    heu_and_move[heu] = item;
  }

  if (!player)
    return ((*heu_and_move.rbegin()).second);
  else
    return ((*heu_and_move.begin()).second);
}

int Minimax::Minimax_Evaluate(State* next_state, int depth, int player_is_black) {
  int H = 0;
  if (!next_state->legal_actions.size()) {
    next_state->get_legal_actions();
  }
  if (depth == 0 || next_state->game_state == WIN || next_state->game_state == DRAW) {
    return next_state->evaluate();
  }

  if (!player_is_black) {
    H = -INT_MAX;
    for (Move next : next_state->legal_actions) {
      State* NEXT = next_state->next_state(next);
      int HEU = Minimax_Evaluate(NEXT, depth - 1, 1);
      H = max(H, HEU); 
    }
  }
  else {
    H = INT_MAX;
    for (Move next : next_state->legal_actions) {
      State* NEXT = next_state->next_state(next);
      int HEU = Minimax_Evaluate(NEXT, depth - 1, 1);
      H = min(H, HEU); 
    }
  }
  return H;
}