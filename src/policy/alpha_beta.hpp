#pragma once
#include "../state/state.hpp"
#include <climits>
using namespace std;

/**
 * @brief Policy class for minimax policy, 
 * your policy class should have get_move method
 */
class Alpha_Beta{
public:
  static Move get_move(State *state, int depth, int alpha, int beta, int player);
  static int AB_Evaluate(State* next_state, int depth, int alpha, int beta, int player_is_black) ;
};
