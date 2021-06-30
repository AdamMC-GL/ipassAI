# ipassAI

To use the application simply run the main script with all the other files in the same folder. 
This will prompt you with asking wether you want a real cube to be solved or be given an example of a solve.

If chosen to get an example, the user shall be given a scramble and the moves required to get to this scramble. 
Then the algorithm will solve the cube and give the moves required to solve it from the scrambled position.

If chosen to solve a real cube the application will ask you to enter the permutation of your cube, starting
from the yellow face, then blue, red, green, orange and at last white.
After this the algorithm will solve the cube an the user will be given a series of moves that was used to solve it.

Note:
- When asked for the yellow face, have the face towards yourself and have the orange face on top for the correct orientation.
- When asked for the blue, red, green, and orange face, have the face towards yourself and have the yellow face on top for the correct orientation.
- When asked for the white face, have the face towards yourself and have the red face on top for the correct orientation.

# syntax
In rubix solving there is a special syntax used. To make this application accessible this syntax is not used. Instead
each move will be written as which face needs to be turned, and which direction. With C meaning clockwise, and CC meaning counter clockwise.

# tests
The tests for the algorithm is written in the main function as well. If these functions are used the a rubiks cube will be solved repeatedly and 
the average speed of each solve will be measured.

# functions
The whole application has a series of functions used for the product.
For the application:
- start_program(Cube) starts the application
- print_cube(); prints the current permutation of the cube 
- print_moves(); prints the moves used so far
- scramble(); Scrambles the cube
- give_perm(); Used to ask the user for the real cube permutation
- texthandeler(string); Causes the print of each cubie to be with its correct color for a user friendly display when printing the cube.

For the algorithm:
- rotate_red_orange() and rotate(); used to rotate the cube
- algorithm1, 2, 3, 4, 5; 5 functions, each used as a series of moves often used in the CFOP algorithm.
- get_middle_row_edge_data(vector<vector<string>>, string, string, int, int, vector<string>);
- get_corner_data(vector<vector<string>>, string, string, int, int, int, vector<string>);
- get_edge_data(vector<vector<string>> & cube_as_array, string, string, int, int, int, int, vector<string>);
  
The CFOP algorithm:
- yellow_corners_or();
- yellow_corners_pos();
- yellow_cross_edges();
- yellow_cross();
- middle_row();
- white_corners();
- white_cross(); Start

