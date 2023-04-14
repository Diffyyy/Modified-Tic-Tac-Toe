## Modified Tic Tac Toe

### Run in your favorite C/C++ compiler / IDE

#### Rules:
##### 1. {(1, 1),(1, 2),(1, 3),(2, 1),(3, 1)} -> Coordinates where neither player can put a move on
##### 2. {(1, 4),(2, 4),(3, 4)}, {(2, 2),(3, 3),(4, 4)}, {(2, 3),(3, 2),(4, 1)}, {(4, 2),(4, 3),(4, 4)}	 -> Win Condition Player 1 (P1): If P1 successfully makes 1 of the 3 patterns listed, P1 wins. If there are no more available tiles for P1, P2 wins. 
##### 3. P2 needs to stop P1 from making one of the patterns. As long as P2 has marked less than 4 tiles, P2 can add mark to another tile given that the given tile is free (not marked/taken by either player). 
##### 4. If P2 chose a tile marked by P2, the mark is undone. Example: P2 has a move on coordinates (1,4) and P2 selected the tile again. The move of P2 is cleared. 