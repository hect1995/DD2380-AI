#ifndef _TICTACTOE3D_PLAYER_HPP_
#define _TICTACTOE3D_PLAYER_HPP_

#include "constants.hpp"
#include "deadline.hpp"
#include "move.hpp"
#include "gamestate.hpp"
#include <vector>

namespace TICTACTOE3D
{

class Player
{
public:
    ///perform a move
    ///\param pState the current state of the board
    ///\param pDue time before which we must have returned
    ///\return the next state the board is in after our move

    void orderStates(std::vector<GameState> &states);
    int partition (std::vector<GameState> &lNextStates, std::vector<int> &scoresStates, int low, int high);
    void swap(int* a, int* b);
    void swap_state(GameState* a, GameState* b);
    void quickSort(std::vector<GameState> &lNextStates, std::vector<int> &scoresStates, int low, int high);
    int algorithm(const GameState &pState, int alpha, int beta, uint8_t player, int depth);
    GameState play(const GameState &pState, const Deadline &pDue);
};

/*namespace TICTACTOE3D*/ }

#endif
