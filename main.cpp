#include <iostream> 
#include <string>
#include <ctime>
#include <vector>
#include <windows.h>
#include "Adams_cube.h"

#include <chrono>
using namespace std;

void testing(Cube cube){
	int counterscramblesolves;
	auto start = std::chrono::high_resolution_clock::now();
	while(true){
		cube.scramble();  // scrambles the cube
		cube.white_cross();
		counterscramblesolves++;
		if(counterscramblesolves%100==0){
			cout<< counterscramblesolves;
			auto finish = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> elapsed = finish - start;
			std::cout << ", Elapsed time: " << elapsed.count()/100 << " s on average per cube\n";
			start = std::chrono::high_resolution_clock::now();
		}
		
	}
	
}

void testing_with_printing(Cube cube){
	int counterscramblesolves;
	auto start = std::chrono::high_resolution_clock::now();
	while(true){
		cube.scramble();
		cube.print_cube();
		cube.white_cross();
		cube.print_cube();
		counterscramblesolves++;
		cube.print_cube();
		if(counterscramblesolves%100==0){
			cout<< counterscramblesolves;
			auto finish = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> elapsed = finish - start;
			std::cout << ", Elapsed time: " << elapsed.count()/100 << " s on average per cube\n";
			start = std::chrono::high_resolution_clock::now();
		}
		
	}
}

int main()
{
	srand((unsigned) time(0));
	Cube Rubiks;
	Rubiks.new_cube();
	//testing(Rubiks);
	start_program(Rubiks);
	

	
	
}
