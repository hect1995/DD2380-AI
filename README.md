# DD2380-AI
Artificial Intelligence course done in KTH during spring period of 2019. The repository contains two projects. The first one consists on developing a Duckhunt game where the model is trained to shoot birds based on their flying patterns. The latter is a checkers that is developed to perform best action possible after performing a tree search

Folder checkers contains 3 different games: TicTacToe in 2D and 3D in Cpp_skeletons folder and Checkers in checkers_skeleton_cpp.

TicTacToe is a zero-sum game where each player tries to be the first to mark 4 cells along a row, column or diagonal. The code is developed for a 2D TicTacToe (4 rows and 4 columns) and for a 3D TicTacToe (4x4x4). [Alfa beta prunning](https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning) is the method used to find efficiently the best next move. The ammount of computation for the 3D case is far higher due to the increase of winning combinations, so better heuristics as well as [Iterative Deepening Depth First Search](https://en.wikipedia.org/wiki/Iterative_deepening_depth-first_search) algorithm had to be implemented. Instructions to run the programs are provided in the README files in each subfolder.
For checkers the program receives a game state (certain distribution of cells for each player) and decides the best move based ont he algorithms explained before
![alt text](https://raw.githubusercontent.com/hect1995/DD2380-AI/master/images/result_moves.png)
