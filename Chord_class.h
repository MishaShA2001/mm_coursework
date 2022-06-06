#pragma once
#include <string>
#include <array>
#include <vector>
#include "Key_class.h"

using namespace std;

int scalar_product(array<int, 12> array_1, array<int, 12> array_2);

class Chord_
{
public:
	string name, base_note, type;

	Chord_(string name_);

	array<int, 12> chord_vector();
	vector<int> chord_notes();

	bool is_in_key(Key some_key);
};

vector<Chord_> get_all_chords(array<string, 96> list_of_names);
