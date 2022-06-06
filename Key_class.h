#pragma once
#include <string>
#include <array>
#include <vector>

using namespace std;

array<int, 12> vector_by_rule(int start_note, vector<int> rule);

class Key
{
public:
	string base_note, type, lad;
	
	Key(string str, string lad_);

	array<int, 12> key_vector();
	array<int, 7> key_notes();
};

vector<Key> get_all_keys(array<string, 24> list_of_names);