# Artificial Intelligence Lab  

> **Practical 1:**  
> **AIM:** To solve the **8-puzzle problem** using **Breadth First Search (BFS)** and print the path from the initial state to the goal state.  

---

## WORKING:

- **Step 1:**  
  Input the initial 8-puzzle configuration (use **0** for the blank tile).  
  Example:  
1 2 3  
4 0 6  
7 5 8  

- **Step 2:**  
Define the goal state as:  
1 2 3  
4 5 6  
7 8 0  


- **Step 3:**  
The program applies the **Breadth First Search (BFS)** algorithm to explore all possible puzzle configurations level by level.  
- Each state represents a possible puzzle arrangement.  
- The **blank tile (0)** can move up, down, left, or right if within bounds.  
- BFS ensures the first time the goal is found, it is via the **minimum number of moves**.  

- **Step 4:**  
The parent of each state is stored to **reconstruct the path** once the goal is reached.  

- **Step 5:**  
The program then prints all intermediate puzzle configurations from the **initial state to the goal state**, along with the total number of moves.  

---

### Time & Space Complexity:
- **Time Complexity:** O(b<sup>d</sup>) — where *b* is the branching factor and *d* is the depth of the solution  
- **Space Complexity:** O(b<sup>d</sup>)  

---

## OUTPUT:

For the given initial state:  
1 2 3  
4 0 6  
7 5 8  


**Output:**
Goal state reached!  
Steps to reach goal:  
1 2 3  
4 0 6  
7 5 8  
1 2 3  
4 5 6  
7 0 8  
1 2 3  
4 5 6  
7 8 0  

Total Moves: 2  
 
---  
> **Practical 2:**  
> **AIM:** To solve the **8-Puzzle Problem** using **Depth First Search (DFS)** and print the path from the initial state to the goal state.  

---

## WORKING:

### 🔹 Step 1: Input
- The user enters the initial 8-puzzle configuration (use **0** to represent the blank space).  
  Example:  
1 2 3  
4 0 6  
7 5 8  


### 🔹 Step 2: Goal Definition
The **goal state** is defined as:  
1 2 3  
4 5 6  
7 8 0  

### 🔹 Step 3: Algorithm Overview
The program applies the **Depth First Search (DFS)** algorithm to explore possible puzzle configurations:

1. The **blank tile (0)** can move **up, down, left, or right**.
2. Each move generates a new puzzle configuration (state).
3. DFS explores one branch fully before backtracking.
4. A **stack** is used to manage states.
5. The **visited** map ensures that no state is revisited.
6. The **parent** map is used to trace back and print the final solution path.
7. The **search depth** is limited (e.g., 50) to prevent infinite loops for unsolvable cases.

---

### 🔹 Step 4: Important Functions

| Function | Description |
|-----------|--------------|
| `toString()` | Converts a 3x3 puzzle matrix to a single string for easy hashing. |
| `findZero()` | Locates the position of the blank tile (0). |
| `printPuzzle()` | Displays a 3x3 puzzle state neatly. |
| `solvePuzzleDFS()` | Performs Depth First Search and prints the steps to reach the goal. |

---

### 🔹 Step 5: Output
If the goal state is reached:
- All intermediate puzzle configurations are printed.
- The total number of moves is displayed.

If the goal state is **not reachable within the depth limit**, the program prints:  
No solution found within depth limit.


---

## Time & Space Complexity

| Measure | Complexity |
|----------|-------------|
| **Time Complexity** | O(b<sup>m</sup>), where *b* = branching factor and *m* = maximum depth |
| **Space Complexity** | O(b×m), since DFS stores only one path at a time |

---

## OUTPUT EXAMPLE

**Input:**  
1 2 3  
4 0 6  
7 5 8  

**Output:**
Goal state reached!
Steps to reach goal:
1 2 3  
4 0 6  
7 5 8  
 
1 2 3  
4 5 6  
7 0 8  

1 2 3  
4 5 6  
7 8 0  

Total Moves: 2

> **Practical 3:**  
> **AIM:** To solve the 8-puzzle problem using Best-First Search (Heuristic Search) and print the path from the initial state to the goal state.  

---

## WORKING:

- **Step 1:**  
  Input the initial 8-puzzle configuration (use 0 for the blank tile).
Example:  
2 8 3   
1 6 4  
7 0 5 

- **Step 2:**  
Define the goal state as:  
1 2 3  
4 5 6  
7 8 0  


- **Step 3:**  
The program applies the Best-First Search (BFS heuristic) algorithm, which uses a heuristic function to choose the next most promising node to explore.  
- The heuristic function (h) used here counts the number of misplaced tiles compared to the goal state.  
- A priority queue (min-heap) is used to always expand the node with the lowest heuristic value first.  
- Each move of the blank tile (0) generates a new possible puzzle configuration by swapping with its adjacent tiles (up, down, left, or right) within valid bounds.

- **Step 4:**  
The parent state of each configuration is stored using a hash map to reconstruct the path to the goal state once it is reached.  

- **Step 5:**  
After reaching the goal state, the program prints all intermediate puzzle configurations from the initial state to the goal state, along with:  
  - Total number of moves required  
  - Total nodes expanded during the search

---

### Time & Space Complexity:
- Time Complexity: O(b<sup>d</sup>) — depends on branching factor b and depth d of the optimal solution 
- Space Complexity: O(b<sup>d</sup>) — since all generated nodes are stored in memory  

---

## OUTPUT:

For the given initial state:  
2 8 3  
1 6 4  
7 0 5  


**Output:**
Goal state reached!
Steps to reach goal:

2 8 3  
1 6 4  
7 0 5    

2 8 3  
1 0 4  
7 6 5  

2 8 3  
1 4 0  
7 6 5  

1 8 3  
2 4 0  
7 6 5  

1 8 3  
2 4 5  
7 6 0  

1 8 3  
2 4 5  
7 0 6  

1 8 3  
2 0 5  
7 4 6  

1 8 3  
0 2 5  
7 4 6  

1 0 3  
8 2 5  
7 4 6  

1 2 3  
8 0 5  
7 4 6  

1 2 3  
8 4 5  
7 0 6  

1 2 3  
8 4 5  
7 6 0  

1 2 3  
8 4 0  
7 6 5  

1 2 3  
8 0 4  
7 6 5  

1 2 3  
0 8 4  
7 6 5  

1 2 3  
4 8 0  
7 6 5  

1 2 3  
4 0 8  
7 6 5  

1 2 3  
4 5 8  
7 6 0  

1 2 3  
4 5 6  
7 8 0  


Total Moves: 18  
Nodes Expanded: 134  

---  

> **Practical 4:**  
> **AIM:** To solve the 8-puzzle problem using the Hill Climbing Algorithm and display each intermediate step until the goal or a local minimum is reached.  

---

## WORKING:

- **Step 1:**  
  Input the initial 8-puzzle configuration (use 0 for the blank tile).
Example:  
2 8 3   
1 6 4  
7 0 5 

- **Step 2:**  
Define the goal state as:  
1 2 3  
4 5 6  
7 8 0  


- **Step 3:**  
The program uses the Hill Climbing algorithm, which starts with the given initial state and iteratively moves to the neighboring state with the best (lowest) heuristic value.  
  - The heuristic function (h) is the number of misplaced tiles compared to the goal state.  
  - The blank tile (0) can move up, down, left, or right to generate new neighboring states.
  - If multiple neighbors have the same heuristic value, one is chosen arbitrarily (using random tie-breaking).

- **Step 4:**  
The algorithm continues moving to better (lower h) states until:  
  - The goal state is reached (h = 0), or  
  - No neighbor has a lower heuristic (indicating a local minimum or plateau).  

- **Step 5:**  
The program prints each intermediate state along with its heuristic value and the step number, showing how the search progresses.
If it gets stuck in a local minimum, it reports the final state and stops.  

---

### Time & Space Complexity:
- Time Complexity: O(b<sup>d</sup>) — where b is the branching factor (possible moves) and d is the depth until a local optimum is reached 
- Space Complexity: O(1) — only the current and neighboring states are stored at a time 

---

## OUTPUT:

For the given initial state:  
2 8 3  
1 6 4  
7 0 5  


**Output:**
Initial State (Heuristic = 5):
2 8 3  
1 6 4  
7 0 5  

Step 1 (Heuristic = 4):
2 8 3  
1 0 4  
7 6 5  

Step 2 (Heuristic = 3):
2 8 3  
1 4 0  
7 6 5  

Step 3 (Heuristic = 2):
1 8 3  
2 4 0  
7 6 5  

Stuck in local minimum or plateau.
Final State (Heuristic = 2):
1 8 3  
2 4 0  
7 6 5  

---  

> **Practical 5:**  
> **AIM:** To implement the A* (A-star) algorithm for finding the shortest path in a grid, avoiding obstacles, and displaying the optimal path and cost.  

---

## WORKING:

- **Step 1:**  
  The user inputs the grid size (n × n), the start coordinates (S), and the destination coordinates (D).  
Example:  
Grid Size: 5  
Start: (0, 0)  
Destination: (4, 4)

- **Step 2:**  
The user specifies the number of obstacles and their positions in the grid.
Obstacles are represented by 1 and are impassable.
The start and destination cells cannot be obstacles.
Example:  
Number of obstacles: 3  
(1, 2)  
(2, 2)  
(3, 1)


- **Step 3:**  
The algorithm initializes the cost grid and uses a priority queue (min-heap) to store nodes in order of their f = g + h value, where:   
  - g → actual cost from start to the current node  
  - h → heuristic cost (estimated distance to goal)
  - f = g + h → total estimated cost

- **Step 4:**  
The heuristic function used is the Manhattan distance, calculated as:  
h(x,y)=∣x−xgoal​∣+∣y−ygoal​∣ 

- **Step 5:**  
The A* algorithm expands nodes with the lowest total cost (f) first, updating neighboring cells if a shorter path is found.
The parent of each cell is stored for path reconstruction once the goal is reached.

- Step 6:  
Once the destination is reached, the algorithm backtracks using parent nodes to reconstruct the optimal path from start (S) to destination (D).  

- Step 7:  
The program then displays:  
  - The total cost (number of steps)  
  - The path coordinates  
  - A visual representation of the grid with:  
    - S → Start  
    - D → Destination  
    - '#' → Obstacle
    - '*' → Path  
---

### Time & Space Complexity:
- Time Complexity: O(V + E) → approximately O(n²) for a grid of size n × n 
- Space Complexity: O(n²) → due to storage of cost, parent, and visited cells

---

## OUTPUT:

For the given initial state:  
Enter grid size (n): 5   
Enter start coordinates (sx sy): 0 0  
Enter destination coordinates (dx dy): 4 4  
How many obstacles? 4  
Obstacle 1 (x y): 1 2  
Obstacle 2 (x y): 2 2  
Obstacle 3 (x y): 3 1  
Obstacle 4 (x y): 3 3   


**Output:**
Path found!  
Total Cost (number of steps): 8  
Path: (0,0) (0,1) (0,2) (0,3) (1,3) (2,3) (3,4) (4,4)

=== Grid Visualization ===  
S * * * .   
. . # * .   
. . # * .   
. # . # *   
. . . . D  


---  

> **Practical 6:**  
> **AIM:** To implement the Water Jug Problem using Breadth-First Search (BFS) to determine the sequence of operations required to measure the desired quantity of water.  

---

## WORKING:

- **Step 1:**  
  The user inputs the following:   
  - Capacity of Jug A  
  - Capacity of Jug B  
  - Desired target amount of water  
Example:  
Jug A capacity: 4  
Jug B capacity: 3  
Target: 2  

- **Step 2:**  
The program first checks if the target amount is achievable using the given jug capacities by verifying:  
target % gcd(capA, capB) == 0  
   - If this condition fails, no solution exists.  
   - Otherwise, the BFS process begins.

- **Step 3:**  
The state space is represented as (x, y) where:    
  - x → amount of water in Jug A  
  - y → amount of water in Jug B  
The initial state is (0, 0) — both jugs empty.

- **Step 4:**  
The algorithm uses Breadth-First Search (BFS) with a queue to explore all possible states level by level.
Each operation generates a new state:  
  - Fill Jug A → (capA, y)  
  - Fill Jug B → (x, capB)  
  - Empty Jug A → (0, y)  
  - Empty Jug B → (x, 0)  
  - Pour A → B → (x - min(x, capB - y), y + min(x, capB - y))  
  - Pour B → A → (x + min(y, capA - x), y - min(y, capA - x))  

- **Step 5:**  
Each newly generated state is added to the queue only if it hasn’t been visited before (to avoid repetition).
The visited set keeps track of all explored states.  

- Step 6:  
The BFS continues until a state (x, y) is found where either x == target or y == target.
At that point, the path (sequence of states) from (0, 0) to the target is printed. 

- Step 7:  
If no sequence satisfies the condition, the algorithm displays:  
No solution found!

---

### Time & Space Complexity:
- Time Complexity: O(capA × capB) — Each possible state (x, y) can be visited once
- Space Complexity: O(capA × capB) — For storing visited states and queue elements
---

## OUTPUT:

For the given initial state:  
Enter Jug A capacity: 4  
Enter Jug B capacity: 3  
Enter target amount: 2    


**Output:**
Steps to achieve 2 liters:
(0,0)  
(4,0)  
(1,3)  
(1,0)  
(0,1)  
(4,1)  
(2,3)  

---  

> **Practical 7:**  
> **AIM:** To implement Tic Tac Toe game using the Minimax algorithm, enabling the computer to play an optimal game against a human player.

---

## WORKING:

- **Step 1:**  
  The program initializes a 3×3 board represented as a 2D vector of characters.
Each cell can hold:  
  - 'X' → Computer’s move  
  - 'O' → Player’s move  
  - ' ' → Empty cell  
The user always plays as ‘O’, and the computer plays as ‘X’.

- **Step 2:**  
The player is prompted to input their move by specifying a row (1–3) and column (1–3).
The program checks whether the move is valid (i.e., within bounds and on an empty cell).  

- **Step 3:**  
After each move, the evaluation function checks the board to determine if a player has won or if the board is full (draw).
The evaluate() function returns:  
  - +10 → if Computer (X) wins   
  - -10 → if Player (O) wins 
  - 0 → if the game is still undecided

- **Step 4:**  
When it’s the computer’s turn, the Minimax algorithm recursively simulates all possible moves and their outcomes to select the optimal move. 
  - Minimax Principle: 
    - The Maximizer (Computer/X) tries to maximize the score (+10).  
    - The Minimizer (Human/O) tries to minimize the score (–10). 

- **Step 5:**  
The minimax() function explores every possible move:
  - Base Case:
    - Returns +10 / –10 / 0 depending on board evaluation.  
  - Recursive Case:  
    - For the Maximizer, it selects the move with the maximum value.  
    - For the Minimizer, it selects the move with the minimum value.  
  - A depth adjustment ensures faster wins and slower losses are prioritized.

- Step 6:  
The findBestMove() function iterates over all empty cells, calls minimax() for each, and picks the move with the best score for the computer.

- Step 7:  
The game continues alternately between user and computer moves until:  
  - One of them wins
  - Or the board becomes full (Draw)

---

### Time & Space Complexity:
- Time Complexity: O(b^m)
- Space Complexity: O(m)
---

## OUTPUT:

TIC TAC TOE using MINIMAX
You are O, Computer is X

Enter your move (row[1-3] col[1-3]): 2 2


Computer is thinking...


Enter your move (row[1-3] col[1-3]): 1 1

Computer is thinking...


Computer wins!

---  

> **Practical 8:**  
> **AIM:** To implement the Block World Problem in Prolog, demonstrating how state-space search and reasoning can be applied to achieve a goal configuration from an initial setup.

---

## WORKING:

- **Step 1:**  
  The program defines the initial state and goal state as lists of predicates describing relationships such as: 
  - on(a, b) → block a is on block b 
  - ontable(c) → block c is on the table  
  - clear(a) → top of block a is empty  
  - handempty → the robot’s hand is free

- **Step 2:**  
The program defines possible actions that can change the world:
  - pickup(X) → pick up block X from the table
  - putdown(X) → put down block X on the table
  - unstack(X, Y) → pick up block X from block Y
  - stack(X, Y) → place block X onto block Y

- **Step 3:**  
Each move is represented as a state transition rule, showing what preconditions must hold and how the world changes after performing the move.

- **Step 4:**  
The planner recursively searches for a sequence of valid actions that transform the initial state into the goal state.
  - It avoids revisiting previously explored states (Visited list). 
  - Once the goal condition is met (subset(Goal, State)), recursion stops.

- **Step 5:**  
The final output displays:
  - The initial and goal states  
  - The ordered sequence of actions to reach the goal

---

## OUTPUT:

Initial State: [on(a,b),on(b,c),ontable(c),clear(a),handempty]  
Goal State: [on(b,a),on(c,b),ontable(a),clear(c),handempty]  

Sequence of Moves to reach the Goal:
 -> unstack(a,b)  
 -> putdown(a)  
 -> unstack(b,c)  
 -> stack(b,a)  
 -> pickup(c)  
 -> stack(c,b)  

---  

> **Practical 9:**  
> **AIM:** To implement the Monkey and Banana Problem in Prolog — modeling the intelligent agent’s planning behavior to reach a goal using logical reasoning and state-space search.

---

## WORKING:

- **Step 1:**  
  Represent the environment using a state:  
  state(Monkey_H, Monkey_V, Chair_Pos, Stick_Pos, Carry_Stick?, Carry_Chair?, Banana_V, Banana_H)

- **Step 2:**  
Define all possible actions (move/3) such as:

  - walk  
  - carry_stick  
  - carry_chair
  - walk_with_stick
  - walk_with_chair
  - climb
  - put_chair_down
  - knock

Each move changes the current state to a new state.

- **Step 3:**  
Define the goal condition:  
state(_, _, _, _, _, _, banadown, _)  


- **Step 4:**  
Use recursion with:  
canget(State)  
to explore all possible moves until the goal state is reached.


- **Step 5:**  
Run in Prolog:  
?- canget(state(door, onfloor, window, middle, notcarrystick, notcarrychair, banaup, middle)).  
If banana can be obtained → Output: true.

---

## OUTPUT:

Monkey walks from door to middle.  
Monkey carries stick.  
Monkey carries chair.  
Monkey walks with chair and stick to middle.  
Monkey puts chair down.  
Monkey climbs on chair.  
Monkey knocks the banana down.  

true.

--- 