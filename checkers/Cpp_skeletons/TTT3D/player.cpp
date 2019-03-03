#include "player.hpp"
#include <cstdlib>
#include <algorithm>
#include <iterator>
#include <math.h>
#include <limits>

namespace TICTACTOE3D
{

const int heuristics[5][5] = {
  {0,     -10, -100,  -1000, -10000},
  {10,     0,    0,    0,    0},
  {100,    0,    0,    0,    0},
  {1000,   0,    0,    0,    0},
  {10000,  0,    0,    0,    0}
};
int gamma_function(const GameState &pState)
{
    /*Needs to be changed with respect the 2D as that one was too time consuming*/

    if(pState.isEOG()){
      if(pState.isXWin() == true){
        return 10000;
      }else if(pState.isOWin() == true){
        return -10000;
      }else{
        return 0;
      }
    }

    uint8_t cell_value;
    int t = 0;
    int p, o, i, j, k, aux;

    /*columns in i axis*/
    for(i=0;i<4;i++){
      for(j=0;j<4;j++){
        p = o = 0;
        for (k=0; k<4; k++){
          cell_value = pState.at(i,j,k);
          if(cell_value == CELL_X){
            p++;
          }else if(cell_value == CELL_O){
            o++;
          }
        }
        t += heuristics[p][o];
      }
    }

    /*rows in i axis*/
    for(i=0; i<4; i++){
      for(k=0;k<4;k++){
        p = o = 0;
        for (j=0; j<4; j++){
          cell_value = pState.at(i,j,k);
          if(cell_value == CELL_X){
            p++;
          }else if(cell_value == CELL_O){
            o++;
          }
        }
        t += heuristics[p][o];
      }
    }

    /*columns in j axis*/
    for(j=0; j<4; j++){
      for(i=0;i<4;i++){
        p = o = 0;
        for (k=0; k<4; k++){
          cell_value = pState.at(i,j,k);
          if(cell_value == CELL_X){
            p++;
          }else if(cell_value == CELL_O){
            o++;
          }
        }
        t += heuristics[p][o];
      }
    }

    /*rows in j axis*/
    for(j=0; j<4; j++){
      for(k=0;k<4;k++){
        p = o = 0;
        for (i=0; i<4; i++){
          cell_value = pState.at(i,j,k);
          if(cell_value == CELL_X){
            p++;
          }else if(cell_value == CELL_O){
            o++;
          }
        }
        t += heuristics[p][o];
      }
    }

    /*rows in k axis*/
    for(k=0; k<4; k++){
      for(i=0;i<4;i++){
        p = o = 0;
        for (j=0; j<4; j++){
          cell_value = pState.at(i,j,k);
          if(cell_value == CELL_X){
            p++;
          }else if(cell_value == CELL_O){
            o++;
          }
        }
        t += heuristics[p][o];
      }
    }

    /*columns in k axis*/
    for(k=0; k<4; k++){
      for(j=0;j<4;j++){
        p = o = 0;
        for (i=0; i<4; i++){
          cell_value = pState.at(i,j,k);
          if(cell_value == CELL_X){
            p++;
          }else if(cell_value == CELL_O){
            o++;
          }
        }
        t += heuristics[p][o];
      }
    }
    //--------------------------------------------------------------------------
    /* 1st diagonal in i axis*/
    for(i=0;i<4;i++){
      p = o = 0;
      for(j=0;j<4;j++){
        cell_value = pState.at(i,j,j);
        if(cell_value == CELL_X){
          p++;
        }else if(cell_value == CELL_O){
          o++;
        }
      }
      t += heuristics[p][o];
    }
    /* 2n diagonal in i axis*/
    for(i=0;i<4;i++){
      p = o = 0;
      for(j=0;j<4;j++){
        cell_value = pState.at(i,j,3-j);
        if(cell_value == CELL_X){
          p++;
        }else if(cell_value == CELL_O){
          o++;
        }
      }
      t += heuristics[p][o];
    }
    /* 1st diagonal in j axis*/
    for(j=0;j<4;j++){
      p = o = 0;
      for(k=0;k<4;k++){
        cell_value = pState.at(k,j,k);
        if(cell_value == CELL_X){
          p++;
        }else if(cell_value == CELL_O){
          o++;
        }
      }
      t += heuristics[p][o];
    }
    /* 2n diagonal in j axis*/
    for(j=0;j<4;j++){
      p = o = 0;
      for(k=0;k<4;k++){
        cell_value = pState.at(3-k,j,k);
        if(cell_value == CELL_X){
          p++;
        }else if(cell_value == CELL_O){
          o++;
        }
      }
      t += heuristics[p][o];
    }
    /* 1st diagonal in k axis*/
    for(k=0;k<4;k++){
      p = o = 0;
      for(aux=0;aux<4;aux++){
        cell_value = pState.at(aux,aux,k);
        if(cell_value == CELL_X){
          p++;
        }else if(cell_value == CELL_O){
          o++;
        }
      }
      t += heuristics[p][o];
    }
    /* 2n diagonal in k axis*/
    for(k=0;k<4;k++){
      p = o = 0;
      for(aux=0;aux<4;aux++){
        cell_value = pState.at(3-aux,aux,k);
        if(cell_value == CELL_X){
          p++;
        }else if(cell_value == CELL_O){
          o++;
        }
      }
      t += heuristics[p][o];
    }

    /*3D Diagonals*/
    p = o = 0;
    for(i=0; i<4; i++){
      cell_value = pState.at(3-i,i,i);
      if(cell_value == CELL_X){
        p++;
      }else if(cell_value == CELL_O){
        o++;
      }
    }
    t += heuristics[p][o];

    p = o = 0;
    for(i=0; i<4; i++){
      cell_value = pState.at(i,i,i);
      if(cell_value == CELL_X){
        p++;
      }else if(cell_value == CELL_O){
        o++;
      }
    }
    t += heuristics[p][o];

    p = o = 0;
    for(i=0; i<4; i++){
      cell_value = pState.at(i,i,3-i);
      if(cell_value == CELL_X){
        p++;
      }else if(cell_value == CELL_O){
        o++;
      }
    }
    t += heuristics[p][o];

    p = o = 0;
    for(i=0; i<4; i++){
      cell_value = pState.at(i,3-i,i);
      if(cell_value == CELL_X){
        p++;
      }else if(cell_value == CELL_O){
        o++;
      }
    }
    t += heuristics[p][o];

    return t;
}

int Player::algorithm(const GameState &pState, int alpha, int beta, uint8_t player, int depth)
{
  int v = 0;
  std::vector<GameState> lNextStates;
  pState.findPossibleMoves(lNextStates); // returns a list of valid future states

  if (lNextStates.size()==0 || depth<=0) // TODO: Add another condition?
  {
    v = gamma_function(pState);
    return v;
  }

  if (lNextStates.size() > 1) {
      // order the next states of my player in order to evaluate them
      orderStates(lNextStates);
  }
  else{
    if (player == CELL_X) // TODO: Check real uint8 assigned to A
    {
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
      v = std::numeric_limits<int>::max();
      for (int i=lNextStates.size()-1; i>=0; i--){
        v = std::min(v, algorithm(lNextStates[i], alpha, beta, CELL_X, depth-1));
        beta = std::min(beta,v);
        if (alpha >= beta)
        {
          break;
        }
      }
    }
  }

  return v;
}

    void Player::orderStates(std::vector<GameState> &states)
    {
        if (states.size() > 1)
        {
            std::vector<int> scoresStates(states.size());
            for (unsigned int i = 0; i < states.size(); i++)
                scoresStates[i] = gamma_function(states[i]);
            int low = 0;
            int high = states.size()-1;
            quickSort(states, scoresStates, low, high);
        }
    }

    void Player::quickSort(std::vector<GameState> &lNextStates, std::vector<int> &scoresStates, int low, int high)
    {
        if (low < high)
        {
            /* pi is partitioning index, arr[pi] is now
               at right place */
            int pi = partition(lNextStates, scoresStates, low, high);

            quickSort(lNextStates, scoresStates, low, pi - 1);  // Before pi
            quickSort(lNextStates, scoresStates, pi + 1, high); // After pi
        }
    }

    /* This function takes last element as pivot, places the pivot element at its correct position in sorted array, and
     * places all smaller (smaller than pivot) to left of pivot and all greater elements to right of pivot */
    int Player::partition (std::vector<GameState> &lNextStates, std::vector<int> &scoresStates, int low, int high)
    {
        int pivot = scoresStates[high];
        int i = low-1; // Index of smaller element (will start with index 1 as the 0 is already the pivot)
        for (int j = low; j <= high- 1; j++)
        {
            // If current element is bigger than or
            // equal to pivot
            if (scoresStates[j] >= pivot)
            {
                i++;
                swap(&scoresStates[i], &scoresStates[j]);
                swap_state(&lNextStates[i], &lNextStates[j]);
            }
        }
        swap(&scoresStates[i + 1], &scoresStates[high]);
        swap_state(&lNextStates[i + 1], &lNextStates[high]);

        return (i + 1);

    }

    // A utility function to swap two elements
    void Player::swap(int* a, int* b)
    {
        int t = *a;
        *a = *b;
        *b = t;
    }

    // A utility function to swap two elements
    void Player::swap_state(GameState* a, GameState* b)
    {
        GameState t = *a;
        *a = *b;
        *b = t;
    }

GameState Player::play(const GameState &pState,const Deadline &pDue)
{
    //std::cerr << "Processing " << pState.toMessage() << std::std::endl;
    //std::unordered_map<std::string, int> dict;

    std::vector<GameState> lNextStates;
    pState.findPossibleMoves(lNextStates); // returns a list of valid future states
    if (lNextStates.size() == 0) return GameState(pState, Move());
    if(lNextStates.size() == 1) return lNextStates[0];
    /*
     * Here you should write your clever algorithms to get the best next move, ie the best
     * next state. This skeleton returns a random move instead.
     */
     int values_childs = 0; // the evaluation of each of the childs, we will move to the one with the highest

     uint8_t next_player_id = (pState.getNextPlayer() == CELL_X) ? CELL_O : CELL_X;

     //std::cerr << "NEXT PLAYER: " << next_player_id << std::endl;

     int alpha = std::numeric_limits<int>::min();
     int beta = std::numeric_limits<int>::max();
     int max = std::numeric_limits<int>::min();
     int best_state = 0;
     int searchDepth = 3;
     int wanted_id = 0;

    if (lNextStates.size() > 1) {
        // order the next states of my player in order to evaluate them
        orderStates(lNextStates);
    }

     for (int iter=0;iter<lNextStates.size();iter++)  //Iterate over possible future states
     {
       if(pDue.now() > pDue-0.1){
        break;
      }
       //std::cerr << "CHILD of player "<< unsigned(pState.getNextPlayer()) << " has values: " << std::endl;
       values_childs = algorithm(lNextStates[iter], alpha, beta, next_player_id, searchDepth); // current depth of the childs is 1 (0 for the parent)
       if( values_childs > max){
         max = values_childs;
         wanted_id = iter;
       }
     }
    //return wantedState;
    return lNextStates[wanted_id];
}

/*namespace TICTACTOE3D*/ }
