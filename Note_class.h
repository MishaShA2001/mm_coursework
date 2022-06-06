#pragma once
#include <string>
#include <array>

using namespace std;

class Note
{
public:
	string name;
	int octave;
	
	Note(string str, int octave);
	
	int number();
	float frequency();
};
