#include <iostream> 
#include <string>
#include <ctime>
#include <vector>
#include <windows.h>
#include "Adams_cube.h"

#include <stdio.h>
#include <stdlib.h> 
#include <time.h> 

#include <chrono>


using namespace std;

	void Cube::print_moves(){
		/**
		 * This function prints out the moves used so far.
		 */
		string print_face;
		string rotation;
		for (unsigned int i = 0; i < moves.size(); i++){
		switch(moves[i][0]){
			case 0: print_face = "y";
					break;
			case 1: print_face = "b";
					break;
			case 2: print_face = "r"; 
					break;
			case 3: print_face = "g";
					break;
			case 4: print_face = "o";
					break;
			case 5: print_face = "w";
					break;
		}
		switch(moves[i][1]){
			case 0: rotation = "cc"; // counter clockwise
					break;
			case 1: rotation = "c"; //clockwise
					break;
		}
			cout << "[" << print_face << ", " << rotation << "] -> ";
		}
		cout << "done. \n";
	}


	void Cube::new_cube(){
		/**
		 * This function makes a new cube
		 */
		//makes a cube (in solved state)
		full_cube = {yellow, blue, red, green, orange, white};
		for(unsigned int i = 0; i < full_cube.size(); i++){
			for(unsigned int j = 0; j < 3; j++){
				vector<string> add_vec;
				for(unsigned int k = 0; k < 3; k++){
						add_vec.push_back(full_cube[i].name);
				}
				full_cube[i].matrix.push_back(add_vec);
			}
		}
		
		vector<vector<string>> table = {{"b", "o", "g", "r"},{"o", "y", "r", "w"},{"b", "y", "g", "w"},
										{"r", "y", "o", "w"},{"g", "y", "b", "w"},{"b", "r", "g", "o"}};
		for(unsigned int i = 0; i < full_cube.size(); i++){
			for(unsigned int j = 0; j < 3; j+=2){
				for(unsigned int k = 0; k < full_cube[i].matrix.size(); k++){
					full_cube[i].matrix[j][k]+= table[i][j+1];//horizontal
					full_cube[i].matrix[k][j]+= table[i][j];//vertical
				}
			}
		}
	}
	
	vector<vector<string>> Cube::get_array_cube(){
		/**
		 * This function returns a cube as an array
		 */
		//a version of the cube with each face as a single array (handy for some math)
		vector<vector<string>> cube_as_array;
		for (unsigned int i = 0; i < full_cube.size(); i++){
			vector<string> full_face;
			for (unsigned int j = 0; j < 3; j++){
				for (unsigned int k = 0; k < 3; k++){
					full_face.push_back(full_cube[i].matrix[j][k]);
				}
			}
			cube_as_array.push_back(full_face);
		}
		return cube_as_array;
	}
	
	void Cube::print_cube(){
		/**
		 * This function prints the current permutation of the cube
		 */
		vector<vector<string>> temp_mat = {{}, {}, {}};
		for(unsigned int i = 0; i < full_cube.size(); i++){
			if (i < 1 || i > 4){
				for(unsigned int j = 0; j < full_cube[i].matrix.size(); j++){
						cout << "               ";
						for(unsigned int k = 0; k < full_cube[i].matrix[j].size(); k++){
							texthandeler(full_cube[i].matrix[j][k]);
							cout << "|" <<full_cube[i].matrix[j][k] << "|";
						}
						cout << "\n";
				}
			}
			else{
				for(unsigned int j = 0; j < full_cube[i].matrix.size(); j++){
					for(unsigned int k = 0; k < full_cube[i].matrix[j].size(); k++){
						temp_mat[j].push_back(full_cube[i].matrix[j][k]);
					}

				}
				if (i == 4){
					for(unsigned int j = 0; j < temp_mat.size(); j++){
						for(unsigned int k = 0; k < temp_mat[j].size(); k++){
							texthandeler(temp_mat[j][k]);
							cout << "|" << temp_mat[j][k] << "|";
							
							HANDLE hConsole;// colors (for now)
							hConsole = GetStdHandle(STD_OUTPUT_HANDLE);//remove when colors remove
							SetConsoleTextAttribute(hConsole, 7);//remove when colors remove
						}
						cout << "\n";
					}
				}
			}
		}
		cout << "-------------------------------------------\n";
	}
	
	
	void Cube::texthandeler(string & cubiecolor){
		/**
		 * This function causes the print of each cubie to be with its correct color for a user friendly display when printing the cube.
		 */
		
		HANDLE hConsole;// colors (for now)
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		if (cubiecolor.size() == 1){
			cubiecolor += "  ";
		}
		else if (cubiecolor.size() == 2){
			cubiecolor += " ";
		}
		
		if (cubiecolor[0] == 'y' || cubiecolor[0] == 'Y'){
			SetConsoleTextAttribute(hConsole, 14);
		}
		if (cubiecolor[0] == 'b' || cubiecolor[0] == 'B'){
			SetConsoleTextAttribute(hConsole, 1);
		}
		if (cubiecolor[0] == 'r' || cubiecolor[0] == 'R'){
			SetConsoleTextAttribute(hConsole, 4);
		}
		if (cubiecolor[0] == 'g' || cubiecolor[0] == 'G'){
			SetConsoleTextAttribute(hConsole, 2);
		}
		if (cubiecolor[0] == 'o' || cubiecolor[0] == 'O'){
			SetConsoleTextAttribute(hConsole, 6);
		}
		if (cubiecolor[0] == 'w' || cubiecolor[0] == 'W'){
			SetConsoleTextAttribute(hConsole, 7);
			
		}
		
	}

	
	void Cube::rotate_red_orange(int face, bool c){
		//if the rotating face is either red or orange, here the sides of said face will be taken care of.
		vector<side> temp_full_cube = full_cube;
		vector<int> adjecents;

		switch(face+c){//the sides that are effected by the rotation
			case 2: adjecents = {3, 0, 1, 5, 3}; // red counterclockwise
					break;
			case 3: adjecents = {1, 0, 3, 5, 1}; // red clockwise
					break;
			case 4: adjecents = {3, 5, 1, 0, 3}; // orange counterclockwise
					break;
			case 5: adjecents = {1, 5, 3, 0, 1}; // orange clockwise
					break;
		}

		vector<int> tempC = {2, 1, 0};  //change to something clever
		if(face+c == 2 || face+c == 5){
			for (unsigned int j = 0; j < 3; j++){ //red cc and orange c
				full_cube[adjecents[1]].matrix[2][j] = temp_full_cube[adjecents[0]].matrix[j][0]; 
				full_cube[adjecents[2]].matrix[j][2] = temp_full_cube[adjecents[1]].matrix[2][tempC[j]]; 
				full_cube[adjecents[3]].matrix[0][j] = temp_full_cube[adjecents[2]].matrix[j][2]; 
				full_cube[adjecents[4]].matrix[tempC[j]][0] = temp_full_cube[adjecents[3]].matrix[0][j]; 
			}
		}
		else{
			for (unsigned int j = 0; j < 3; j++){  //red c and orange cc
				full_cube[adjecents[1]].matrix[2][tempC[j]] = temp_full_cube[adjecents[0]].matrix[j][2]; 
				full_cube[adjecents[2]].matrix[j][0] = temp_full_cube[adjecents[1]].matrix[2][j]; 
				full_cube[adjecents[3]].matrix[0][tempC[j]] = temp_full_cube[adjecents[2]].matrix[j][0]; 
				full_cube[adjecents[4]].matrix[j][2] = temp_full_cube[adjecents[3]].matrix[0][j]; 
			}
		}
	}
	
	
	void Cube::rotate(int face, bool c){
		moves.push_back({face, c});
		
		
		//c = true means clockwise rotation
		//transpose + mirror = rotate 90 degrees
		for (unsigned int i=0; i<full_cube[face].matrix.size(); i++){//transpose
			for(unsigned int j =0; j<full_cube[face].matrix[i].size(); j++){
				if(i < j){
					string TempA = full_cube[face].matrix[i][j];
					full_cube[face].matrix[i][j] = full_cube[face].matrix[j][i];
					full_cube[face].matrix[j][i] = TempA;
				}
			}
		}	
		if(c){
			for (unsigned int i=0; i<full_cube[face].matrix.size(); i++){//mirror
				string TempA = full_cube[face].matrix[i][0];
				full_cube[face].matrix[i][0] = full_cube[face].matrix[i][2];
				full_cube[face].matrix[i][2] = TempA;
			}
		}
		else{
			for (unsigned int i=0; i<full_cube[face].matrix.size(); i++){//mirror
				string TempA = full_cube[face].matrix[0][i];
				full_cube[face].matrix[0][i] = full_cube[face].matrix[2][i];
				full_cube[face].matrix[2][i] = TempA;
			}
		}
	
	
	
		if (face == 2 || face == 4){
			rotate_red_orange(face, c);
			return;
		}
		//turning the cubies adjecent to the face itself
		vector<side> temp_full_cube = full_cube;
		vector<int> adjecents = {0, 0, 0, 0, 0};
		
		switch(face){//the sides that are effected by the rotation
			case 0: adjecents = {1, 4, 3, 2, 1};
					break;
			case 1: adjecents = {0, 2, 5, 4, 0};
					break;
			case 3: adjecents = {2, 0, 4, 5, 2};
					break;
			case 5: adjecents = {1, 2, 3, 4, 1};
					break;
					
		}
		if (!c){//switch second and fourth nr in adjecents to make the turn counter clockwise
			int TempA = adjecents[1];
			adjecents[1] = adjecents[3];
			adjecents[3] = TempA;
		}
		if (face == 1 || face == 3){
			int coor = face-1;
			int coor2 = (7 % (face + 4));
			vector<int> tempC = {2, 1, 0};//change to something clever
			for (unsigned int i = 0; i < adjecents.size()-1; i++){
				for (unsigned int j = 0; j < 3; j++){
					if (adjecents[i+1] == 4){//orange problems
						full_cube[adjecents[i+1]].matrix[tempC[j]][coor2] = temp_full_cube[adjecents[i]].matrix[j][coor];
					}
					else if (adjecents[i] == 4){//orange problems
						full_cube[adjecents[i+1]].matrix[tempC[j]][coor] = temp_full_cube[adjecents[i]].matrix[j][coor2];
					}
					else{
						full_cube[adjecents[i+1]].matrix[j][coor] = temp_full_cube[adjecents[i]].matrix[j][coor];
					}
				}
			}
			return;
		}
		if (face == 0 || face == 5){
			int coor = (face % 3);//if face = 0 answer is 0, if face = 5 answer is 2. These are the correct coordinates to differ between top and bottom(yellow and white)
			for (unsigned int i = 0; i < adjecents.size()-1; i++){
				for (unsigned int j = 0; j < 3; j++){
					full_cube[adjecents[i+1]].matrix[coor][j] = temp_full_cube[adjecents[i]].matrix[coor][j];
				}
			}
		}
	}
	
	
	void Cube::scramble(){
		/**
		 * This function scrambles the cube
		 */
		
		moves = {}; //Reset moves list
		int randomnr;
		for (unsigned int i=0; i < 15; i++){
			randomnr = rand() % 6;
			rotate(randomnr, 1);
			//cout << randomnr;
		}
		//cout << "\n";
	}
	
	
	void Cube::give_perm(){
		/**
		 * This function is used to ask the user for the real cube permutation
		 */
		string cubiecolor;
		vector<string> face_names {"yellow", "blue", "red", "green", "orange", "white"};
		vector<int> middle_order = {4, 1, 2, 3, 4, 1, 2, 3, 4};
		full_cube = {yellow, blue, red, green, orange, white};
		for(unsigned int i = 0; i < full_cube.size(); i++){
			int cubienr = 0;
			cout << "input colors for "<< face_names[i] << " side;\n";
			for(unsigned int j = 0; j < 3; j++){
				vector<string> add_vec;
				for(unsigned int k = 0; k < 3; k++){
					cout << cubienr << ": ";
					cin >> cubiecolor;
					add_vec.push_back(cubiecolor);
					cubienr++;
				}
				full_cube[i].matrix.push_back(add_vec);
			}
		}
		
		
		vector<vector<vector<int>>> table = {{{0, 1, 2}, {0, 1, 2}, {2, 1, 0}, {2, 1, 0}}, 
											 {{2, 1, 0}, {2, 1, 0}, {0, 1, 2}, {0, 1, 2}}};
											 
		string temp;
											 
		for(unsigned int i = 0; i < table.size(); i++){
			for(unsigned int k = 0; k < 3; k++){
				temp = full_cube[i*5].matrix[k][0][0];
				full_cube[i*5].matrix[k][0] += full_cube[1].matrix[i*2][table[i][0][k]][0];
				//cout << full_cube[1].matrix[i*2][table[i][0][k]];
				full_cube[1].matrix[i*2][table[i][0][k]]+= temp;

				temp = full_cube[i*5].matrix[k][2][0];
				full_cube[i*5].matrix[k][2] += full_cube[3].matrix[i*2][table[i][2][k]][0];
				full_cube[3].matrix[i*2][table[i][2][k]] += temp;
				
				if(i == 0){
					temp = full_cube[i*5].matrix[0][k][0];
					full_cube[i*5].matrix[0][k] += full_cube[4].matrix[i*2][table[i][3][k]][0];
					full_cube[4].matrix[i*2][table[i][3][k]] += temp;
									
					temp = full_cube[i*5].matrix[2][k][0];
					full_cube[i*5].matrix[2][k] += full_cube[2].matrix[i*2][table[i][1][k]][0];
					full_cube[2].matrix[i*2][table[i][1][k]] += temp;
				}
				else{
					temp = full_cube[i*5].matrix[0][k][0];
					full_cube[i*5].matrix[0][k] += full_cube[2].matrix[i*2][table[i][3][k]][0];
					full_cube[4].matrix[i*2][table[i][3][k]] += temp;
									
					temp = full_cube[i*5].matrix[2][k][0];
					full_cube[i*5].matrix[2][k] += full_cube[4].matrix[i*2][table[i][1][k]][0];
					full_cube[2].matrix[i*2][table[i][1][k]] += temp;
				}
			}
		}
		for(unsigned int i = 1; i < 4; i+=2){
			for(unsigned int j = 0; j < 3; j++){
				temp = full_cube[i].matrix[j][0][0];
				full_cube[i].matrix[j][0] += full_cube[middle_order[i-1]].matrix[j][2][0];
				full_cube[middle_order[i-1]].matrix[j][2] += temp;
				
				temp = full_cube[i].matrix[j][2][0];
				full_cube[i].matrix[j][2] += full_cube[middle_order[i+1]].matrix[j][0][0];
				full_cube[middle_order[i+1]].matrix[j][0] += temp;
			}
		}
	}
	
	
	int Cube::get_algorithm1_amount(int wcubie_face, int ref_face, bool loc, bool down){
		int amount;
		
		if(wcubie_face == ref_face){
			amount = down+1;
		}
		else if(wcubie_face == 0 || wcubie_face == 5){
			amount = 27 % (wcubie_face+4);
		}
		else{
			amount = -1-down;
		}
		if (!loc && down){
			amount--;
		}
		return amount;
	}
	
	
	void Cube::algorithm1(int start_face, int y_or_w, int amount){
		/**
		 * This function is used as a series of moves often used in the CFOP algorithm.
		 */
		if(amount > 0){
			for (unsigned int i = 0; i < amount; i++){
				rotate(start_face, true);
				rotate(y_or_w, true);
				rotate(start_face, false);
				rotate(y_or_w, false);
			}
		}
		else{
			for (int i = amount; i < 0; i++){
				rotate(y_or_w, true);
				rotate(start_face, true);
				rotate(y_or_w, false);
				rotate(start_face, false);
				
			}
		}
	}
	
	
	void Cube::algorithm2(int start_face, bool mirror){
		/**
		 * This function is used as a series of moves often used in the CFOP algorithm.
		 */
		vector<int> middle_order = {4, 1, 2, 3, 4, 1};
		
		if (mirror){
			algorithm1(start_face, 0, 1);
			rotate(middle_order[start_face-mirror], false);
			rotate(0, false);
			rotate(middle_order[start_face-mirror], true);
			rotate(0, true);
		}
		else{
			rotate(middle_order[start_face-mirror], false);
			rotate(0, false);
			rotate(middle_order[start_face-mirror], true);
			rotate(0, true);
			algorithm1(middle_order[start_face+1], 0, 1);
		}
	}
	
	
	void Cube::algorithm3(int start_face, int amount){
		/**
		 * This function is used as a series of moves often used in the CFOP algorithm.
		 */
		vector<int> middle_order = {4, 1, 2, 3, 4, 1};
		rotate(start_face, true);
		
		algorithm1(middle_order[start_face+1], 0, amount);//alg
		
		rotate(start_face, false);
	}
	
	
	void Cube::algorithm4(int start_face){
		/**
		 * This function is used as a series of moves often used in the CFOP algorithm.
		 */
		rotate(start_face, true);
		rotate(0, true);
		rotate(start_face, false);
		rotate(0, true);
		rotate(start_face, true);
		rotate(0, true);
		rotate(0, true);
		rotate(start_face, false);
		rotate(0, true);
	}
	
	
	void Cube::algorithm5(int start_face){
		/**
		 * This function is used as a series of moves often used in the CFOP algorithm.
		 */
		vector<int> middle_order = {4, 1, 2, 3, 4, 1, 2, 3, 4};
		
		rotate(0, true);
		rotate(start_face, true);
		rotate(0, false);
		rotate(middle_order[start_face+2], false);
		rotate(0, true);
		rotate(start_face, false);
		rotate(0, false);
		rotate(middle_order[start_face+2], true);
	}
	
	
	void Cube::yellow_corners_or(){
		/**
		 * This function locates and calculates the moves needed to 
		 * get a orientation for the yellow croners correctly placed on the cube.
		 * 
		 * The end of this function gives a cube containing a yellow face with its corners oriented correctly,
		 * this completes the cube.
		 * The function is the last step for the algorithm.
		 */

		vector<int> middle_order = {4, 1, 2, 3, 4, 1, 2, 3, 4};
		vector<vector<string>> cube_as_array = get_array_cube();
		
		string tempcubie;
		string tempcubie2;
		int amount_correct = -5;//subtracting the yellow cross
		int yellow_sum = -20; //subtracting the yellow cross
		int amount_alg;
		int ref_face;
		
		bool par;
		
		for (unsigned int i = 0; i < 9; i ++){
			tempcubie = cube_as_array[0][i][0];
			if (tempcubie == "y"){
				amount_correct++;
				yellow_sum += i;
			}
		}
		
		if (amount_correct != 4){

			for (unsigned int i = 1; i < 5; i ++){
				tempcubie = cube_as_array[i][0][0];
				if (tempcubie == full_cube[i].name){
					ref_face = i;
					break;
				}
			}
			if (yellow_sum == 8){
				par = true;
			}
			if(amount_correct == 0){ 
				for (unsigned int i = 1; i < 5; i ++){
					tempcubie = cube_as_array[i][2][0];
					if (tempcubie == "y"){
						algorithm1(1, 5, 2);
					}
					else{
						algorithm1(1, 5, -2);
					}
					rotate(0, true);
				}
			}
			

			else if (amount_correct == 1){
				for (unsigned int i = 0; i < 3; i ++){
					tempcubie = cube_as_array[middle_order[ref_face+i]][2][0];
					if (tempcubie == "y"){
						algorithm1(ref_face, 5, 2);
					}
					else{
						algorithm1(ref_face, 5, -2);
					}
					rotate(0, true);
				}
				rotate(0, true);
			}
			else{
				if(par){
					for (unsigned int i = ref_face; i < 5; i += 2){
						tempcubie = cube_as_array[i][2][0];
						if (tempcubie == "y"){
							algorithm1(ref_face, 5, 2);
						}
						else{
							algorithm1(ref_face, 5, -2);
						}
						rotate(0, true);
						rotate(0, true);
					}
				}
				else{
					for (unsigned int i = 1; i < 5; i ++){
						tempcubie = cube_as_array[i][2][0];
						tempcubie2 = cube_as_array[middle_order[i+1]][2][0];
						if (tempcubie != full_cube[i].name && tempcubie2 != full_cube[middle_order[i+1]].name){
							ref_face = i;
							break;
						}
					}
					for (unsigned int i = ref_face; i < ref_face+2; i ++){
						tempcubie = cube_as_array[middle_order[i]][2][0];
						if (tempcubie == "y"){
							algorithm1(ref_face, 5, 2);
						}
						else{
							algorithm1(ref_face, 5, -2);
						}
						rotate(0, true);
					}
					rotate(0, true);
					rotate(0, true);
				}
			}
		}
		
		cube_as_array = get_array_cube();
		vector<string> all_faces= {"y", "b", "r", "g", "o", "w"};
		int amount_correct_face = 0;
		bool is_solved = true;
		for (unsigned int i = 0; i < all_faces.size(); i ++){
			for (unsigned int j = 0; j < 9; j ++){
				tempcubie = cube_as_array[i][j][0];
				if (tempcubie == all_faces[i]){
					amount_correct_face++;
				}
			}
			if(amount_correct_face < 9){
				is_solved = false;
			}
			amount_correct_face = 0;
		}
		
		if(is_solved){
			//cout << "SUCCESS\n";
		}
		else{
			
			cout << "FAIL\n";
			
		}
	}


	void Cube::yellow_corners_pos(){
		/**
		 * This function locates and calculates the moves needed to 
		 * get a position for the yellow croners correctly placed on the cube.
		 * 
		 * The end of this function gives a cube containing a yellow face with its corners placed correctly.
		 * The function then hops to yellow_corners_or() for the next step.
		 */

		vector<int> middle_order = {4, 1, 2, 3, 4, 1, 2, 3, 4};
		vector<vector<string>> cube_as_array = get_array_cube();
		string tempcubie;
		string ncubie1;
		string ncubie2;
		
		int counter;
		int ref_face;
		
		bool no_ref = true;
		
		while (true){
			counter = 0;
			for (unsigned int i = 1; i < 5; i ++){
				tempcubie = cube_as_array[i][0][0];
				if (tempcubie == "y"){
					ncubie1 = cube_as_array[i][0][1];
					ncubie2 = cube_as_array[i][0][2];
				}
				else{
					ncubie1 = tempcubie;
					ncubie2 = cube_as_array[i][0][1];
					if (ncubie2 == "y"){
						ncubie2 = cube_as_array[i][0][2];
					}
				}
				if((full_cube[i].name == ncubie1 || full_cube[i].name == ncubie2) && (full_cube[middle_order[i-1]].name == ncubie1 || full_cube[middle_order[i-1]].name == ncubie2)){
					counter++;
					if (no_ref){
						ref_face = i;
						no_ref = false;
					}
				}
			}
			if(counter == 4){
				break;
			}
			else if (counter == 0){
				algorithm5(2);
				//alg with red face
			}
			else{
				algorithm5(ref_face);
				//alg with ref_face
			}
			cube_as_array = get_array_cube();
		}
		yellow_corners_or();
	}


	void Cube::yellow_cross_edges(){
		/**
		 * This function locates and calculates the moves needed to 
		 * get a edges of the yellow cross correctly placed on the cube.
		 * 
		 * The end of this function gives a cube containing a completed yellow cross with the correct edges.
		 * The function then hops to yellow_corners_pos() for the next step.
		 */
		vector<int> middle_order = {4, 1, 2, 3, 4, 1, 2, 3, 4};
		vector<vector<string>> cube_as_array = get_array_cube();
		
		string tempcubie;
		
		int counter = 0;
		int face1;
		int face2;
		
		bool face_one_full;
		bool notcomplete = true;
		
		for (unsigned int i = 1; i < 5; i ++){
			tempcubie = cube_as_array[i][1][0];
			if(tempcubie == full_cube[i].name){
				counter ++;
			}
		}
		if (counter == 4){
			notcomplete = false;
		}
		else if (counter < 2){
			for (unsigned int j = 1; j < 4; j ++){
				counter = 0;
				for (unsigned int k = 1; k < 5; k ++){
					tempcubie = cube_as_array[k][1][0];
					if(tempcubie == full_cube[middle_order[k+j]].name){
						counter++;
					}
				}
				if (counter > 1 && counter < 4){// turn yellow j times
					switch(j){ // rotate yellow n times function?
					case 3: rotate(0, true);
							break;
					case 2: rotate(0, true);
							rotate(0, true);
							break;
					case 1: rotate(0, false);
							break;
					}
					break;
				}
				else if (counter == 4){
					for (unsigned int l = 0; l < j; l++){
						rotate(0, false);
					}
					notcomplete = false;
				}
			}
		}
		
		if(notcomplete){
			cube_as_array = get_array_cube(); // update the cube
			face_one_full = false;
			for (unsigned int i = 1; i < 5; i ++){
				tempcubie = cube_as_array[i][1][0];
				if(tempcubie == full_cube[i].name && !face_one_full){
					face1 = i;
					face_one_full = true;
				}
				else if(tempcubie == full_cube[i].name){
					face2 = i;
				}
			}
			
			if(face1+face2 == 6 || face1+face2 == 4){//paralel	
				rotate(0, true);
				algorithm4(face1+1);
				algorithm4(middle_order[face2+1]);
			}
			else{
				if(face1 == 1 && face2 == 4){
					algorithm4(face2);
				}
				else{
					algorithm4(face1);
				}
			}
		}
		yellow_corners_pos();
	}


	void Cube::yellow_cross(){
		/**
		 * This function locates and calculates the moves needed to 
		 * get a yellow cross correctly placed on the cube.
		 * 
		 * The end of this function gives a cube containing a completed yellow cross.
		 * The function then hops to yellow_cross_edges() for the next step.
		 */
		vector<vector<string>> cube_as_array = get_array_cube();
		string ref_cubie;
		int counter = 0;
		string tempcubie;

		for (unsigned int i = 1; i < cube_as_array[0].size(); i += 2){
			ref_cubie = cube_as_array[0][i][0];
			if(ref_cubie == "y"){
				counter += i;
			}
		}
		
		switch(counter){
			case 0: algorithm3(2, 1);
					algorithm3(4, 2);
					break;
			case 4: algorithm3(2, 2);
					break;
			case 6: algorithm3(1, 2);
					break;
			case 8: tempcubie = cube_as_array[0][1][0];
					if(tempcubie == "y"){
						algorithm3(3, 1);
						break;
					}
					algorithm3(2, 1);
					break;
			case 9: algorithm3(3, 1);
					break;
			case 10: algorithm3(3, 2);
					break;
			case 12: algorithm3(4, 2);
					break;
			
		}
		yellow_cross_edges();
	}
	
	
	void Cube::get_middle_row_edge_data(vector<vector<string>> & cube_as_array, string & ref_cubie, string & ncubie, int & ref_cubie_face, int & ref_cubie_loc, vector<string> solved_colors){
		/**
		 * This function locates the edges of the middle row and obtains its data
		 * the data is used to calculate the correct moves needed in the middle_row() function
		 */
		cube_as_array = get_array_cube();
		bool new_color;
		string tempcubie;
		
		for (unsigned int i = 1; i < cube_as_array.size()-1; i++){
			for (unsigned int j = 1; j < 5; j += 2){ // data cubie color. i = face, j = location on face
				ref_cubie = cube_as_array[i][j][0];
				ncubie = cube_as_array[i][j][1];
				if(ref_cubie != "y" && ncubie != "y"){
					new_color = true;
					
					for (unsigned int k = 0; k < solved_colors.size(); k++){
						if (solved_colors[k] == ref_cubie + ncubie){
							new_color = false;
						}
					}
					if(new_color){
						ref_cubie_face = i;
						ref_cubie_loc = j;
						return;
					}
				}
			}
		}
	}


	void Cube::middle_row(){
		/**
		 * This function locates and calculates the moves needed to 
		 * get a middle row (between white and yellow) correctly placed on the cube.
		 * 
		 * The end of this function gives a cube containing a completed middle row.
		 * The function then hops to yellow_cross() for the next step.
		 */
		vector<string> solved_colors;
		vector<int> middle_order = {4, 1, 2, 3, 4, 1, 2, 3, 4};
		vector<vector<string>> cube_as_array; 
		
		string ref_cubie;
		string ncubie;
		int ref_cubie_face;
		int ref_cubie_loc;
		int nr_yellow_turns;
		int dest_face;
		
		bool top;
		
		while(solved_colors.size() < 8){
			get_middle_row_edge_data(cube_as_array, ref_cubie, ncubie, ref_cubie_face, ref_cubie_loc, solved_colors);
			top = true;
			for (unsigned int i = 0; i < cube_as_array.size()-1; i++){
				if(ncubie == full_cube[middle_order[ref_cubie_face+i]].name){
					nr_yellow_turns = i-2;
					break;
				}
			}
			
			if(ref_cubie_loc == 3){
				top = false;
				if(ref_cubie != full_cube[ref_cubie_face].name || ncubie != full_cube[middle_order[ref_cubie_face-1]].name){
					top = true;
					algorithm2(ref_cubie_face, 1);
					// alg 1 w/ ref_face
				}
			}
			if (top){
				switch(nr_yellow_turns){ // rotate yellow n times function?
				case -1: rotate(0, true);
						break;
				case -2: rotate(0, true);
						rotate(0, true);
						break;
				case 1: rotate(0, false);
						break;
				}
				dest_face = middle_order[ref_cubie_face + nr_yellow_turns + 2];
				if (full_cube[middle_order[dest_face-1]].name == ref_cubie){
					algorithm2(dest_face, 1);
					//  alg1 w/ dest_face
				}
				else{
					//  alg2  w/ dest_face
					algorithm2(dest_face, 0);
				}
			}
			solved_colors.push_back(ref_cubie + ncubie);
			solved_colors.push_back(ncubie + ref_cubie);
		}
		yellow_cross();
	}


	void Cube::get_corner_data(vector<vector<string>> & cube_as_array, string & ncubie1, string & ncubie2, int & wcubie_face, int & wcubie_loc, int & ref_face, vector<string> solved_colors){
		/**
		 * This function locates the corners of the white face and obtains its data
		 * the data is used to calculate the correct moves needed in the white_corners() function
		 */
		vector<int> check_order = {0, 2, 6, 8};
		cube_as_array = get_array_cube();
		int ncubie1_face;
		int ncubie1_loc;
		int ncubie2_face; 
		int ncubie2_loc; 
		
		bool new_color;
		string tempcubie;
		string hcubie; 
		
		for (unsigned int i = 0; i < cube_as_array.size(); i++){
			for (unsigned int j = 0; j < check_order.size(); j ++){ // data cubie color. i = face, j = location on face
				hcubie = cube_as_array[i][check_order[j]][0];
				ncubie1 = cube_as_array[i][check_order[j]][1];
				ncubie2 = cube_as_array[i][check_order[j]][2];
				if(hcubie == "w"){
					new_color = true;
					
					for (unsigned int m = 0; m < solved_colors.size(); m++){
						if (solved_colors[m] == ncubie1 + ncubie2){
							new_color = false;
						}
					}
					if(new_color){
						wcubie_face = i;
						wcubie_loc = check_order[j];
						
						if (wcubie_face != 0 && wcubie_face != 5 && 7%(wcubie_loc+1) == 0){ //check if compatible as reference face
							ref_face = wcubie_face;
						}
						for (unsigned int k = 0; k < cube_as_array.size(); k++){ // data neighbouring cubie colors. k = face, l = location on face
							for (unsigned int l = 0; l < check_order.size(); l ++){ 
								
								if(ncubie1+"w"+ncubie2 == cube_as_array[k][check_order[l]] || ncubie1+ncubie2+"w" == cube_as_array[k][check_order[l]]){
									ncubie1_face = k;
									ncubie1_loc = check_order[l];
									// to do, better if statement (0)
									if (ncubie1_face != 0 && ncubie1_face != 5 && 7%(ncubie1_loc+1) == 0){ //check if compatible as reference face
										ref_face = ncubie1_face;
									}
								}
								if(ncubie2+"w"+ncubie1 == cube_as_array[k][check_order[l]] || ncubie2+ncubie1+"w" == cube_as_array[k][check_order[l]]){
									ncubie2_face = k;
									ncubie2_loc = check_order[l];
									
									if (ncubie2_face != 0 && ncubie2_face != 5 && 7%(ncubie2_loc+1) == 0){ //check if compatible as reference face
										ref_face = ncubie2_face;
									}
								}
							}
						}
						return;
					}
				}
			}
		}
	}


	void Cube::white_corners(){
		/**
		 * This function locates and calculates the moves needed to 
		 * get a white corners correctly placed on the cube.
		 * 
		 * The end of this function gives a cube containing a completed white side.
		 * The function then hops to middle_row() for the next step.
		 */
		vector<string> solved_colors;
		vector<int> middle_order = {4, 1, 2, 3, 4, 1, 2, 3, 4};
		vector<vector<string>> cube_as_array; 

		string ncubie1;
		string ncubie2;
		int wcubie_face;
		int wcubie_loc;
		
		
		int ref_face;//reference face (point of origin face for calculations)
		
		bool loc;
		bool down;
		
		int amount;

		while (solved_colors.size() < 4){
			get_corner_data(cube_as_array, ncubie1, ncubie2, wcubie_face, wcubie_loc, ref_face, solved_colors); // add what kind of corner(w or y)
			loc = false;
			down = true;

			if(wcubie_face == 0 || (wcubie_loc < 3 && wcubie_face != 5)){ // is the cubie up
				down = false;
			}
			if((full_cube[ref_face].name == ncubie1 || full_cube[ref_face].name == ncubie2) 
				&& (full_cube[middle_order[ref_face-1]].name == ncubie1 || full_cube[middle_order[ref_face-1]].name == ncubie2)){// is the location of the cubie correct?
				loc = true;
				amount = get_algorithm1_amount(wcubie_face, ref_face, loc, down);
				algorithm1(ref_face, 0, amount);
			}
			else{
				if(down){ // is the cubie up or down
					algorithm1(ref_face, 0, 1);
				}
				for (unsigned int i = 1; i < 4; i++){
					if((full_cube[middle_order[ref_face+i]].name == ncubie1 || full_cube[middle_order[ref_face+i]].name == ncubie2) 
						&& (full_cube[middle_order[ref_face-1+i]].name == ncubie1 || full_cube[middle_order[ref_face-1+i]].name == ncubie2)){
						switch(i){ // rotate yellow n times function?
						case 1: rotate(0, false);
								break;
						case 2: rotate(0, true);
								rotate(0, true);
								break;
						case 3: rotate(0, true);
								break;
						}
						amount = get_algorithm1_amount(wcubie_face, ref_face, loc, down);
						algorithm1(middle_order[ref_face+i], 0, amount);
						break;
					}
				}
			}
			solved_colors.push_back(ncubie1 + ncubie2);
		}
		middle_row();
	}


	void Cube::get_edge_data(vector<vector<string>> & cube_as_array, string & wcubie, string & ncubie, int & wcubie_face, int & wcubie_loc, int & ncubie_face, int & ncubie_loc, vector<string> solved_colors){
		cube_as_array = get_array_cube();
		bool new_color;
		string tempcubie;
		
		for (unsigned int i = 0; i < cube_as_array.size(); i++){
			for (unsigned int j = 1; j < cube_as_array[i].size(); j += 2){ // data cubie color. i = face, j = location on face
				wcubie = cube_as_array[i][j][0];
				ncubie = cube_as_array[i][j][1];
				if(wcubie == "w"){
					new_color = true;
					
					for (unsigned int m = 0; m < solved_colors.size(); m++){
						if (solved_colors[m] == ncubie){
							new_color = false;
						}
					}
					if(new_color){
						wcubie_face = i;
						wcubie_loc = j;
						
						for (unsigned int k = 0; k < cube_as_array.size(); k++){ // data neighbouring cubie color. k = face, l = location on face
							for (unsigned int l = 1; l < cube_as_array[k].size(); l += 2){ 
								if(ncubie+"w" == cube_as_array[k][l].substr(0,2)){
									ncubie_face = k;
									ncubie_loc = l;
									return;
								}
							}
						}
					}
				}
			}
		}
	}


	void Cube::white_cross(){
		/**
		 * The start of the algorithm. This function locates
		 * and calculates the moves needed to get a white cross correctly
		 * placed on the cube.
		 * 
		 * The end of this function gives a cube containing a white cross.
		 * The function then hops to white_corners() for the next step.
		 */
		vector<string> solved_colors;
		vector<int> middle_order = {4, 1, 2, 3, 4, 1, 2, 3, 4};
		vector<string> table = {"g", "o", "b", "r", "g", "o", "b", "r"};
		vector<vector<string>> cube_as_array; 
		string wcubie;
		string ncubie;
		int wcubie_face;
		int wcubie_loc;
		int ncubie_face;
		int ncubie_loc;
		bool eulerbool;
		
		moves = {}; //Reset moves list
		while(solved_colors.size() < 4){
			get_edge_data(cube_as_array, wcubie, ncubie, wcubie_face, wcubie_loc, ncubie_face, ncubie_loc, solved_colors);
			if(cube_as_array[wcubie_face][4] == ncubie || cube_as_array[ncubie_face][4] == ncubie){ //1
				if(cube_as_array[ncubie_face][4] == ncubie){//2euler
					
					if(ncubie_loc == 3 || ncubie_loc == 5 ){
						rotate( ncubie_face, (6%ncubie_loc));

					}
					else if (ncubie_loc == 1){
						rotate( ncubie_face, true);
						rotate( ncubie_face, true);

					}

						
				}
				else{
					if(wcubie_loc == 1 || wcubie_loc == 7 ){
						rotate( wcubie_face, true);						
					}
					if (wcubie_loc == 5 || wcubie_loc == 1){//R
						rotate( 5, true);
						rotate( middle_order[wcubie_face+1], false);
						rotate( 5, false);
					}
					else if (wcubie_loc == 7 || wcubie_loc == 3){//L
						rotate( 5, false);
						rotate( middle_order[wcubie_face-1], true);
						rotate( 5, true);
					}
				}
			}
			else{
				bool rewind = false;
				eulerbool = false;
				if ((ncubie_loc == 3 || ncubie_loc == 5) && (ncubie_face > 0 && ncubie_face < 5)){ //M
					eulerbool = true;
					rewind = true;
					rotate(ncubie_face, (10%ncubie_loc));
				}
				else if (ncubie_face > 0 && ncubie_face < 5){
					eulerbool = true;
					if (ncubie_loc == 7){
						rotate(ncubie_face, true);
						rotate(ncubie_face, true);
					}
				}
				else if (wcubie_loc == 1 || wcubie_loc == 7){
					if (wcubie_loc == 7){
						rotate(wcubie_face, true);
						rotate(wcubie_face, true);
					}
				}
				int counter;
				bool counterbool = true;
				if(ncubie_face > 0 && ncubie_face < 5){
					for (unsigned int i = 0; i < table.size(); i++){
						if(table[i] == ncubie && counterbool){
							counterbool = false;
							counter = i;
							
						}
						if (table[i] == cube_as_array[ncubie_face][4] && !counterbool){
							counter = i - counter;
							break;
							
						}
					}
				}
				else{
					for (unsigned int i = 0; i < table.size(); i++){
						if(table[i] == ncubie && counterbool){
							counterbool = false;
							counter = i;
						}
						if (table[i] == cube_as_array[wcubie_face][4] && !counterbool){
							counter = i - counter;
							break;
							
						}
					}
				}
				switch(counter){
					case 1: rotate(0, true);
							counter -= 2;
							break;
					case 2: rotate(0, true);
							rotate(0, true);
							break;
					case 3: rotate(0, false);
							counter -= 2;
							break;
				}
				if (rewind){
					rotate(ncubie_face, (6 % ncubie_loc));
				}
				if(eulerbool){
					rotate(middle_order[ncubie_face + counter], true);
					rotate(middle_order[ncubie_face + counter], true);
				}
				else{
					rotate(middle_order[wcubie_face + counter], true);
					rotate(5, true);
					rotate(middle_order[wcubie_face + counter+1], false);
					rotate(5, false);
				}
			}
			solved_colors.push_back(ncubie);
		}
		
		white_corners();
	}
	
	void start_program(Cube cube){
		/**
		* Starts the program, give you the option to solve a real cube
		* or let the app solve one for you as an example.
		* 
		* Each solve starts at the white_cross() function
		*/
		string first_ans;
		cout << "Would you like to solve a real cube (1) or get an example solve(2)?\n";
		cin >> first_ans;
		if (first_ans == "1"){
			cube.give_perm();
		}
		else{
			cout << "Scramble: \n";
			cube.scramble();
			cube.print_cube();
			cout << "Moves to scramble: ";
			cube.print_moves();
		}
		
		cout << "Solved: \n";
		cube.white_cross();
		cube.print_cube();
		cout << "Moves to solve: ";
		cube.print_moves();

	}

