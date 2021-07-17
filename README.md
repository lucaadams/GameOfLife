# GameOfLife
C++ remake of Conway's Game of Life using SFML

<p align="center"><img src="res/gameOfLifePreview.gif"></p>

## rules
The universe of the Game of Life is an infinite two-dimensional orthogonal grid of square cells, 
each of which is in one of two possible states, alive or dead, or "populated" or "unpopulated". 
Every cell interacts with its eight neighbours, which are the cells that are horizontally, vertically, or 
diagonally adjacent. At each step in time, the following transitions occur:
- Any live cell with fewer than two live neighbours dies, as if caused by underpopulation.
- Any live cell with two or three live neighbours lives on to the next generation.
- Any live cell with more than three live neighbours dies, as if by overpopulation.
- Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

## controls
### all modes
- `C` - clear grid
- `I` - invert colours
- `\+` - increase frame rate cap
- `\-` - lower frame rate cap
- `Esc` - exit
### `prep` mode
This is when you set up the grid
- `LMB` - place cell
- `RMB` - remove cell
- `R` - randomise grid
- `Enter` - set to `play` mode
### `play` mode
This is when the automation begins 
- `P` - pause (sets the game back to `prep` mode)
