//
// Created by Héctor Esteban Cabezos on 2019-02-18.
//

#ifndef A2_STATESMEMORY_HPP
#define A2_STATESMEMORY_HPP

#include <string>
#include "constants.hpp"
#include "gamestate.hpp"

#define SIZE 4


namespace checkers
{

    struct stateData
    {
        int score;
        int depth;
        int maxDepth;
        uint8_t myPlayer;

        stateData(int _score, int _depth, uint8_t _player, int _maxdepth)
        {
            this->score = _score;
            this->depth = _depth;
            this->myPlayer = _player;
            this->maxDepth = _maxdepth;
        }

        std::string idString(const GameState &pState)
        {
            char id[SIZE * (SIZE * 2) + 1];
            for (unsigned int i = 0; i < SIZE * (SIZE * 2); i++)
            {
                uint8_t piece = pState.at(i);
                if (piece & CELL_WHITE)
                {
                    if (piece & CELL_KING)
                        id[i] = 'w';
                    else
                        id[i] = 'W';
                }
                else if (piece & CELL_RED)
                {
                    if (piece & CELL_KING)
                        id[i] = 'r';
                    else
                        id[i] = 'R';
                }
                else
                    id[i] = 'n';
            }

            id[SIZE * (SIZE * 2)] = '\0'; //return the end of line

            return std::string(id);
        };

        std::string IdMirrorString(const GameState &pState)
        {
            char id[SIZE * (SIZE * 2) + 1];
            for (unsigned int i = 0; i < SIZE * (SIZE * 2); i += 4)
            {
                uint8_t piece1 = pState.at(i);
                uint8_t piece2 = pState.at(i + 3);
                if (piece1 & CELL_WHITE)
                {
                    if (piece1 & CELL_KING)
                        id[i + 3] = 'w';
                    else
                        id[i + 3] = 'W';
                }
                else if (piece1 & CELL_RED)
                {
                    if (piece1 & CELL_KING)
                        id[i + 3] = 'r';
                    else
                        id[i + 3] = 'R';
                }
                else
                    id[i + 3] = 'n';
                if (piece2 & CELL_WHITE)
                {
                    if (piece2 & CELL_KING)
                        id[i] = 'w';
                    else
                        id[i] = 'W';
                }
                else if (piece2 & CELL_RED)
                {
                    if (piece2 & CELL_KING)
                        id[i] = 'r';
                    else
                        id[i] = 'R';
                }
                else
                    id[i] = 'n';
            }

            for (unsigned int i = 1; i < SIZE * (SIZE * 2); i += 4)
            {
                uint8_t piece1 = pState.at(i);
                uint8_t piece2 = pState.at(i + 1);
                if (piece1 & CELL_WHITE)
                {
                    if (piece1 & CELL_KING)
                        id[i + 1] = 'w';
                    else
                        id[i + 1] = 'W';
                }
                else if (piece1 & CELL_RED)
                {
                    if (piece1 & CELL_KING)
                        id[i + 1] = 'r';
                    else
                        id[i + 1] = 'R';
                }
                else
                    id[i + 1] = 'n';
                if (piece2 & CELL_WHITE)
                {
                    if (piece2 & CELL_KING)
                        id[i] = 'w';
                    else
                        id[i] = 'W';
                }
                else if (piece2 & CELL_RED)
                {
                    if (piece2 & CELL_KING)
                        id[i] = 'r';
                    else
                        id[i] = 'R';
                }
                else
                    id[i] = 'n';
            }

            id[SIZE * (SIZE * 2)] = '\0';

            return std::string(id);
        }



    };


} /* Namespace checkers*/

#endif //A2_STATESMEMORY_H
