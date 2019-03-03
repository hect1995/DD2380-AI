#include "player.hpp"

#include <cstdlib>
#include <algorithm>
#include <iterator>
#include <math.h>
#include <limits>

const int NUM_COLUMNS = 4;
const int NUM_ROWS = 4;
const int MAX_DEPTH = 3;

namespace TICTACTOE
{
  int sumCols(const GameState &state, uint8_t player){
    int sum = 0;
    int counter = 0;
    uint8_t opponent = (player == CELL_X) ? CELL_O : CELL_X;
    bool isopponent = false;
    bool me = false;
    int counter_en = 0;
    int counter_me = 0;
    for(int i=0; i<NUM_COLUMNS; i++){
      int tmp = 0;
      counter_en = 0;
      counter_me = 0;
      isopponent = false;
      me = false;
      for(int j=0; j<NUM_ROWS; j++){
        if(state.at(j,i) == opponent){ // there is already one opponent in the column
          counter_en = counter_en+1;
          tmp = -1*pow(10, counter_en);
          isopponent = true;
        }else if(state.at(j,i) == player){
          me = true;
          counter_me = counter_me+1;
          tmp = pow(10, counter_me);
        }
        if (isopponent == true && me == true){
          tmp = 0;
          break;
        }
      }
      sum += tmp;
    }
    return sum;
  }

  int sumRows(const GameState &state, uint8_t player){
    int sum = 0;


    uint8_t opponent = (player == CELL_X) ? CELL_O : CELL_X;
    bool isopponent = false;
    bool me = false;
    int counter_en = 0;
    int counter_me = 0;

    for(int i=0;i<NUM_ROWS;i++){
      int counter = 0;
      counter_en = 0;
      counter_me = 0;
      int tmp = 0;
      isopponent = false;
      me = false;
      for(int j=0;j<NUM_COLUMNS;j++){
        if(state.at(i,j) == opponent){
          counter_en = counter_en+1;
          tmp = -1*pow(10, counter_en);
          isopponent = true;
        }else if(state.at(i,j) == player){ //I have one mark in the column
          me = true;
          counter_me = counter_me+1;
          tmp = pow(10, counter_me);
        }
        if (isopponent == true && me == true){
          tmp = 0;
          break;
        }
      }
      sum += tmp;
    }
    return sum;
  }

  int sumDiags(const GameState &state, uint8_t player){
    int sum = 0;
    uint8_t opponent = (player == CELL_X) ? CELL_O : CELL_X;
    int counter_en = 0;
    int counter_me = 0;
    //1st diagonal
    bool isopponent = false;
    bool me = false;
    int tmp = 0;
    for(int i=0; i<NUM_COLUMNS; i++){
      if(state.at(i,i) == opponent){
        counter_en = counter_en+1;
        tmp = -1*pow(10, counter_en);
        isopponent = true;
      }else if(state.at(i,i) == player){
        me = true;
        counter_me = counter_me+1;
        tmp = pow(10, counter_me);
      }
      if (isopponent == true && me == true){
        tmp = 0;
        break;
      }

    }
    sum += tmp;

    //Second diagonal
    isopponent = false;
    counter_en = 0;
    counter_me = 0;
    me = false;
    tmp = 0;
    for(int i=0; i<NUM_COLUMNS; i++){
      if(state.at(i,3-i) == opponent){
        counter_en = counter_en+1;
        tmp = -1*pow(10, counter_en);
        isopponent = true;
      }else if(state.at(i,3-i) == player){
        me = true;
        counter_me = counter_me+1;
        tmp = pow(10, counter_me);
      }

      if (isopponent == true && me == true){
        tmp = 0;
        break;
      }

    }
    sum += tmp;

    return sum;
  }

int gamma_function(const GameState &pState, uint8_t player)
{
    //std::cerr << pState.toString(player) << std::endl;

    if( pState.isXWin() == true ){
      return 10000;
    }else if( pState.isOWin() == true ){
      return -10000;
    }else if( pState.isDraw() == true){
      return 0;
    }else{

      int value1 = sumDiags(pState, player);
      int value2 = sumRows(pState, player);
      int value3 = sumCols(pState, player);
      std::cerr << " for diag: " << value1 << " for col: " << value3 << " for row: " << value2 << std::endl << std::endl;
      return value1 + value2 + value3;
    }
}

int algorithm(const GameState &pState, int alpha, int beta, uint8_t player, int depth)
{
  int v = 0;
  std::vector<GameState> lNextStates;
  pState.findPossibleMoves(lNextStates); // returns a list of valid future states

  if (lNextStates.size()==0 || depth==0) // TODO: Add another condition?
  {
    v = gamma_function(pState, player);
    return v;
  }
  else{
    if (player == CELL_X) // TODO: Check real uint8 assigned to A
    {
      //std::cerr << "NEXT POSSIBLE STATES PLAYER: " << lNextStates.size() << std::endl;
      v = std::numeric_limits<int>::min();
      for (int i=0; i<lNextStates.size(); i++){
        v = std::max(v, algorithm(lNextStates[i], alpha, beta, CELL_O, depth-1));
        alpha = std::max(v, alpha);
        if (alpha >= beta)
        {
          break;
        }
      }
    }
    else { // Player B
      //std::cerr << "NEXT POSSIBLE STATES ENEMY: " << lNextStates.size() << std::endl;
      v = std::numeric_limits<int>::max();
      for (int i=0; i<lNextStates.size(); i++){
        v = std::min(v, algorithm(pState, alpha, beta, CELL_X, depth-1));
        beta = std::min(beta,v);
        if (alpha >= beta)
        {
          //std::cerr << "MIN B PLAYER: " << v << std::endl;
          break;
        }
      }
    }
  }

  return v;
}

GameState Player::play(const GameState &pState,const Deadline &pDue)
{
    //std::cerr << "Processing " << pState.toMessage() << std::std::endl;

    std::vector<GameState> lNextStates;
    pState.findPossibleMoves(lNextStates); // returns a list of valid future states
    //std::cerr << "NEXT POSSIBLE STATES: " << lNextStates.size() << std::endl;
    // The initial depth is 0 and we set a variable MAX_DEPTH to the leaves of the tree we want to consider
    if (lNextStates.size() == 0) return GameState(pState, Move());
    /*
     * Here you should write your clever algorithms to get the best next move, ie the best
     * next state. This skeleton returns a random move instead.
     */
     int values_childs = 0; // the evaluation of each of the childs, we will move to the one with the highest

     //std::cerr << "CURRENT PLAYER: " << pState.getNextPlayer() << std::endl;

     uint8_t next_player_id = (pState.getNextPlayer() == CELL_X) ? CELL_O : CELL_X;

     //std::cerr << "NEXT PLAYER: " << next_player_id << std::endl;

     int alpha = std::numeric_limits<int>::min();
     int beta = std::numeric_limits<int>::max();
     int max = std::numeric_limits<int>::min();
     //int depth = 0;
     int best_state = 0;
     GameState wantedState;
     for (GameState iter : lNextStates)  //Iterate over possible future states
     {
       //std::cerr << "CHILD " << i << " of player "<< unsigned(pState.getNextPlayer()) << " has values: " << std::endl;
       values_childs = algorithm(iter, alpha, beta, next_player_id, MAX_DEPTH); // current depth of the childs is 1 (0 for the parent)
       //std::cerr << "CHILD " << i << " of player "<< unsigned(pState.getNextPlayer()) << " has value " << values_childs << std::endl <<std::endl;
       if( values_childs > max){
         max = values_childs;
         wantedState = iter;
       }
     }
    //return lNextStates[rand() % lNextStates.size()];
    //std::cerr << "MOVE CHOOSEN: " << best_state.getMove() << std::endl;
    std::cerr << pState.toString(pState.getNextPlayer()) << std::endl;
    return wantedState;
}

/*namespace TICTACTOE*/ }
