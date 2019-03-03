#ifndef _CHECKERS_PLAYER_HPP_
#define _CHECKERS_PLAYER_HPP_

#include "constants.hpp"
#include "deadline.hpp"
#include "move.hpp"
#include "gamestate.hpp"
//#include "statesMemory.hpp"
#include <vector>
#include <unordered_map>
#include <limits>



namespace checkers
{

class Player
{
public:
    ///perform a move
    ///\param pState the current state of the board
    ///\param pDue time before which we must have returned
    ///\return the next state the board is in after our move
    GameState play(const GameState &pState, const Deadline &pDue);
    GameState iDeepSearch(uint8_t player, std::vector<GameState> lNextStates, int searchDepth, const Deadline &pDue);
    GameState moveBasedOnDepth(uint8_t myPlayer, std::vector<GameState> &lNextStates, std::vector<int> &scoresStates,
                                       int depth, const Deadline &pDue);
    void quickSort(std::vector<GameState> &lNextStates, std::vector<int> &scoresStates, int low, int high);
    int partition (std::vector<GameState> &lNextStates, std::vector<int> &scoresStates, int low, int high);
    int algorithm(const GameState &pState, int alpha, int beta, int myPlayer, int depth, const Deadline &pDue);
    bool improvedState(std::string stringId, int depth, int maxDepth);
    void orderStates(std::vector<GameState> &states);
    int gamma_function(const GameState &pState);
    void addState(const std::string stringId, const int depth,
                          const int score, const int player, int maxdepth);
    void swap(int* a, int* b);
    void swap_state(GameState* a, GameState* b);

    // Obtained from https://github.com/burklight/Checkers/blob/master/src/player.cpp
    const int heuristicWhite[32] = {
      2520, 2520, 2268, 2520,
      2016, 2016, 1764, 1764,
      1512, 1512, 1260, 1512,
      1512, 1512, 1260, 1008,
      1260, 1008, 1260, 1512,
      1008,  756, 1260,  756,
       504,  756,  504, 1008,
       756,  504,  756, 1008
    };

    const int heuristicRed[32] = {
      1008,  756,  504,  756,
      1008,  504,  756,  504,
       756, 1260,  756,  1008,
      1512, 1260, 1008, 1260,
      1008, 1260, 1512, 1512,
      1512, 1260, 1512, 1512,
      1764, 1764, 2016, 2016,
      2520, 2268, 2520, 2520
    };


};

/*namespace checkers*/ }

#endif
