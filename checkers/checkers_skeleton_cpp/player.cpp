#include "player.hpp"
#include <cstdlib>

namespace checkers
{

    GameState Player::play(const GameState &pState,const Deadline &pDue)
    {
        std::vector<GameState> lNextStates;
        pState.findPossibleMoves(lNextStates);

        if (lNextStates.size() == 0) return GameState(pState, Move());
        if (lNextStates.size() == 1) return lNextStates[0];
        /*
         * Here you should write your clever algorithms to get the best next move, ie the best
         * next state. This skeleton returns a random move instead.
         */
         int searchDepth = std::numeric_limits<int>::max();

         return iDeepSearch(pState.getNextPlayer(), lNextStates, searchDepth, pDue); //send current player and all the
         // next states for this player

    }

    /*A state space/graph search strategy in which a depth-limited version of depth-first search is run repeatedly with
     * increasing depth limits until the goal is found.*/
    GameState Player::iDeepSearch(uint8_t myPlayer, std::vector<GameState> lNextStates,
                                               int searchDepth, const Deadline &pDue)
    {
        GameState bestState = lNextStates[0]; // In case of timeout by default the returned state will be the first one
        std::vector<int> scoresStates(lNextStates.size(), 0); // initialize the scores to 0
        try
        {
            // For each depth run the alfa-beta algorithm, and for each depth the lNextStates order is changed as well
            // as its scores
            for (int depth = 1; depth < searchDepth; depth++)
            {
                bestState = moveBasedOnDepth(myPlayer, lNextStates, scoresStates, depth, pDue);
            }
        }
        catch (std::exception e)
        {
            /* Exception returned from the function alpha-beta in order to provide an answer*/
        }

        return bestState;
    }

    GameState Player::moveBasedOnDepth(uint8_t myPlayer, std::vector<GameState> &lNextStates, std::vector<int> &scoresStates,
            int depth, const Deadline &pDue)
    {
        // First of all the states need to be ordered based on previous scoresStates using quicksort (algorithm copied
        // from https://www.geeksforgeeks.org/quick-sort/)
        if (lNextStates.size() > 1) {
            // order the next states of my player in order to evaluate them
            orderStates(lNextStates);
        }
        int alpha = std::numeric_limits<int>::min();
        int beta = std::numeric_limits<int>::max();

        if (myPlayer == CELL_WHITE)
        {
            GameState bestState; // objective is to maximize
            int v;// = std::numeric_limits<int>::min();
            int maxValue = std::numeric_limits<int>::min();

            for (int i=0; i<lNextStates.size(); i++){
                v = algorithm(lNextStates[i], alpha, beta, CELL_RED, depth, pDue);
                if(v > maxValue) // save the maximum heuristic child
                {
                    maxValue = v;
                    bestState = lNextStates[i];
                }
            }
            return bestState;
        }
        else { // Player B
            GameState bestState; // objective is to minimize
            int v;
            int maxValue = std::numeric_limits<int>::max();

            for (int i=lNextStates.size()-1; i>=0; i--){
                v = algorithm(lNextStates[i], alpha, beta, CELL_WHITE, depth, pDue);
                if(v < maxValue) // save the minimum heuristic child for the minimizer
                {
                    maxValue = v;
                    bestState = lNextStates[i];
                }
            }
            return bestState;
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

    // A utility function to swap two integers
    void Player::swap(int* a, int* b)
    {
        int t = *a;
        *a = *b;
        *b = t;
    }

    // A utility function to swap two Gamestate objects
    void Player::swap_state(GameState* a, GameState* b)
    {
        GameState t = *a;
        *a = *b;
        *b = t;
    }

    int Player::algorithm(const GameState &pState, int alpha,
                          int beta, int myPlayer, int depth, const Deadline &pDue)
    {
        // As in A1,A2, where a final node is reached or we cannot continue evaluate
        if(pState.isEOG() || (depth <= 0 && !pState.getMove().isJump()))
        {
            return gamma_function(pState);
        }

        // If no time left
        if(pDue.getSeconds() < pDue.now().getSeconds() + 1e-4){
            throw std::exception();
        }

        std::vector<GameState> newStates; // child states of the state Im interested in
        pState.findPossibleMoves(newStates);

        orderStates(newStates); //order new movements based on the evaluation function of them if they were

        if (myPlayer == CELL_WHITE)
        {
            int v = std::numeric_limits<int>::min();
            for (int i=0; i<newStates.size(); i++){
                v = std::max(v, algorithm(newStates[i], alpha, beta, CELL_RED, depth-1, pDue));
                alpha = std::max(v, alpha);
                if (alpha >= beta)
                {
                    break;
                }
            }
            return v;
        }
        else { // Player B
            int v = std::numeric_limits<int>::max();
            for (int i=newStates.size()-1; i>=0; i--){
                v = std::min(v, algorithm(newStates[i], alpha, beta, CELL_WHITE, depth-1, pDue));
                beta = std::min(beta,v);
                if (alpha >= beta)
                {
                    break;
                }
            }
            return v;
        }
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

    /*The evaluate function*/
    int Player::gamma_function(const GameState &pState)
    {

        if (pState.isRedWin()) // the minimizer wins
        {
            return std::numeric_limits<int>::min();
        }
        else if (pState.isWhiteWin()) // The maximizer wins
        {
            return std::numeric_limits<int>::max();
        }
        else if (pState.isDraw())
        {
            return 0; // As draw doesnt work to pass the assigment we could give negative value as well
        }
        else
        {
            int valueRed = 0;
            int valueWhite = 0;
            for(unsigned int i = 0; i < 32; i++)
            {
                int piece = pState.at(i);
                if(piece == CELL_RED)
                {
                    if(piece == CELL_KING)
                        valueRed += 75 * heuristicRed[i];
                    else
                        valueRed += 50 * heuristicRed[i];
                }
                else if(piece == CELL_WHITE)
                {
                    if(piece == CELL_KING)
                        valueWhite += 75 * heuristicWhite[i];
                    else
                        valueWhite += 50 * heuristicWhite[i];
                }
            }
            return (valueWhite - valueRed);


        }

    }

/*namespace checkers*/ }
