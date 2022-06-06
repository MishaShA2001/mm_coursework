#include "Key_class.h"
#include "Note_class.h"

vector<int> rule_dur_n = { 2, 2, 1, 2, 2, 2 };
vector<int> rule_dur_g = { 2, 2, 1, 2, 1, 3 };
vector<int> rule_dur_m = { 2, 2, 1, 2, 1, 2 };

vector<int> rule_moll_n = { 2, 1, 2, 2, 1, 2 };
vector<int> rule_moll_g = { 2, 1, 2, 2, 1, 3 };
vector<int> rule_moll_m = { 2, 1, 2, 2, 2, 2 };

array<int, 12> vector_by_rule(int start_note, vector<int> rule)
{
	array<int, 12> our_vector = { 0 };
	int counter = start_note;
	our_vector[counter] = 1;
	for (int i = 0; i < rule.size(); i++)
	{
		counter += rule[i];
		if (counter > 11) counter -= 12;
		our_vector[counter] = 1;
	}
	return our_vector;
}

Key::Key(string str, string lad_)
{
	string base_note_from_str = str.substr(0, str.find("-"));
	if (base_note_from_str.length() != 1)
	{
		char help_char_1 = toupper(base_note_from_str[0]);
		char help_char_2;
		if (base_note_from_str.substr(1, 2) == "es") help_char_2 = 'b';
		if (base_note_from_str.substr(1, 2) == "is") help_char_2 = '#';
		base_note = { help_char_1, help_char_2 };
	}
	else
	{
		char help_char = toupper(base_note_from_str[0]);
		base_note = { help_char };
	}
	type = str.substr(str.find("-") + 1);
	lad = lad_;
}

array<int, 12> Key::key_vector()
{
	Note my_note(base_note, 3);
	int start_note = my_note.number();
	if (type == "dur")
	{
		if (lad == "n") return vector_by_rule(start_note, rule_dur_n);
		if (lad == "g") return vector_by_rule(start_note, rule_dur_g);
		if (lad == "m") return vector_by_rule(start_note, rule_dur_m);
	}
	if (type == "moll")
	{
		if (lad == "n") return vector_by_rule(start_note, rule_moll_n);
		if (lad == "g") return vector_by_rule(start_note, rule_moll_g);
		if (lad == "m") return vector_by_rule(start_note, rule_moll_m);
	}
}

array<int, 7> Key::key_notes()
{
	array<int, 7> our_array = { 0 };
	array<int, 12> help_array = key_vector();
	int counter = 0;
	for (int i = 0; i < 12; i++)
	{
		if (help_array[i] == 1)
		{
			our_array[counter] = i;
			counter += 1;
		}
	}
	return our_array;
}

vector<Key> get_all_keys(array<string, 24> list_of_names)
{
	vector<Key> all_keys;
	for (int i = 0; i < 24; i++)
	{
		Key key_n(list_of_names[i], "n");
		Key key_g(list_of_names[i], "g");
		Key key_m(list_of_names[i], "m");

		all_keys.push_back(key_n);
		all_keys.push_back(key_g);
		all_keys.push_back(key_m);
	}

	return all_keys;
}