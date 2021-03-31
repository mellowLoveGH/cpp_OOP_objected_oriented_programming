# cpp_bingo_game
c++, bingo game, the strategy in a Bingo game

Bingo Game
A bingo game is a board game using an N x N matrix board that is filled with numbers from 1 to N2. 
In this project, you and the opponent play the game according to the below sequence.
1) You and the opponent randomly distribute numbers on the matrix boards.
2) At each turn, you and the opponent pick a number to mark, and open them at the same time.
3) You and the opponent mark the picked numbers on the board. You will mark two numbers unless you and the opponent pick the same number.
4) The players repeat turns of 2) and 3) until one wins or the game is drawn.
5) One wins if one marks all numbers of in M rows, columns, diagonals, or in their combinations. 
In other words, when M=3, the winning condition includes marking all numbers in 3 rows as well as marking all numbers in 2 rows and 1 diagonal.
6) If you and the opponent reach the winning condition at the same time, the game is drawn.
You get 3 point for a win, 1 point for a draw, and 0 for a defeat.

By finding the hidden parameters from the calls of your opponent, you might be able to guess the bingo matrix of the opponent and use the information to win.

the bingo matrix size N is defined by BINGO_SIZE.
the winning condition M is defined by BINGO_CNT.
By default, N = 20 and M = 5.
The full league will be played for all possible pairs of players.
Two players will play 100 games. 

