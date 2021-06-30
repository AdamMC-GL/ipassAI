#ifndef ADAMSCUBE_H
#define ADAMSCUBE_H
using namespace std;

struct side{
	string name;
	vector<vector<string>> matrix;
};



class Cube{
private:

	side white =  {"w", {}};
	side green =  {"g", {}};
	side red =  {"r", {}};
	side blue =  {"b", {}};
	side orange =  {"o", {}};
	side yellow =  {"y", {}};
	
	vector<side> full_cube = {yellow, blue, red, green, orange, white};
	
	
	void texthandeler(string & cubiecolor);
	void algorithm1(int start_face, int y_or_w, int amount);
	void algorithm2(int start_face, bool mirror);
	void algorithm3(int start_face, int amount);
	void algorithm4(int start_face);
	void algorithm5(int start_face);
public:
	void print_cube();
	void new_cube();
	vector<vector<string>> get_array_cube();
	vector<vector<int>> moves;
	
	void print_moves();
	void scramble();
	void give_perm();
	void rotate_red_orange(int face, bool c);
	void rotate(int face, bool c);
	int get_algorithm1_amount(int wcubie_face, int ref_face, bool loc, bool down);
	void yellow_corners_or();
	void yellow_corners_pos();
	void yellow_cross_edges();
	void yellow_cross();
	void get_middle_row_edge_data(vector<vector<string>> & cube_as_array, string & ref_cubie, string & ncubie, int & ref_cubie_face, int & ref_cubie_loc, vector<string> solved_colors);
	void middle_row();
	void get_corner_data(vector<vector<string>> & cube_as_array, string & ncubie1, string & ncubie2, int & wcubie_face, int & wcubie_loc, int & ref_face, vector<string> solved_colors);
	void white_corners();
	void get_edge_data(vector<vector<string>> & cube_as_array, string & wcubie, string & ncubie, int & wcubie_face, int & wcubie_loc, int & ncubie_face, int & ncubie_loc, vector<string> solved_colors);
	void white_cross();
	
};
void start_program(Cube cube);

#endif