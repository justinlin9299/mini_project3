#pragma once
#include "../state/state.hpp"


/**
 * @brief Policy class for minimax policy, 
 * your policy class should have get_move method
 */
class Minimax{
public:
  static Move get_move(State *state, int depth, int player);
  static int Minimax_Evaluate(State *state, int depth, int player_is_black);
};
