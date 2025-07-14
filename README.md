LAN Party Tournament Automation 🎮🏆
Overview 🎯
This project is designed to automate the management of a LAN Party tournament organized by the Faculty of Automation and Computers. It involves handling teams and players, simulating matches, and generating rankings using fundamental data structures like lists, queues, stacks, binary search trees, and AVL trees.

Objectives 🚀
Understand and implement core data structures: lists, stacks, queues, binary search trees (BST), and AVL trees.

Manipulate these data structures effectively.

Build a practical application that simulates a tournament, handling teams and their match results.

Features & Requirements 📝
1. Load Teams into a List 📋
Teams are loaded from the input file d.in into a list.

Teams are inserted at the beginning of the list (O(1) complexity).

2. Filter Teams Based on Scores 🎯
Remove teams with the lowest team score until only n teams remain.

Here, n is the largest power of 2 less than or equal to the initial number of teams.

If multiple teams share the lowest score, remove the first found team.

After each removal, re-scan the list from the start.

3. Match Simulation Using Data Structures ⚔️
Create a queue of matches, pairing teams consecutively from the list.

Use two stacks:

One for winners

One for losers

Teams winning a match get their score increased by 1.

In case of a tie, the first team added to the match wins.

After each round, delete the teams in the losers’ stack.

Move winners from the winners’ stack back to the queue for the next round.

Repeat until the top 8 teams are determined.

Continue matches until the ultimate winner is decided.

4. Rankings with BST 🌳
Store the final 8 teams in a Binary Search Tree (BST).

BST is ordered by team score descending; if scores tie, order by team name descending.

Output the BST content in descending order.

5. AVL Tree and Level Display ⚖️
Build an AVL tree using the same 8 teams sorted as above.

Display the teams on level 2 of the AVL tree.

Technical Details ⚙️
Player structure example:

c

struct Player {
  char* firstName;
  char* secondName;
  int points;  // experience points
};
Team score = arithmetic mean of all players’ points.

After a win, increase all players’ points in the team by 1.

Input/Output Files 📂
c.in: Contains which requirements to execute (e.g. "1 0 0 0 0" means only requirement 1).

d.in: Contains teams and players data.

r.out: Output file with results.

Running the Program ▶️
After compiling, run the executable lanParty as follows:

bash
./lanParty c.in d.in r.out
Example Use Case 🎲
Initially, 146 teams.

Largest power of 2 ≤ 146 is 128 (2^7).

Remove 18 teams with lowest scores until 128 remain
