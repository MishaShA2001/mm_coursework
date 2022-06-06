#include "Chord_class.h"
#include "Note_class.h"
#include "Key_class.h"

vector<int> rule_major = { 4, 3 };
vector<int> rule_m = { 3, 4 };
vector<int> rule_aug = { 4, 4 };
vector<int> rule_dim = { 3, 3 };
vector<int> rule_sus4 = { 5, 2 };

vector<int> rule_7 = { 4, 3, 3 };
vector<int> rule_m7 = { 3, 4, 3 };
vector<int> rule_maj7 = { 4, 3, 4 };

int scalar_product(array<int, 12> array_1, array<int, 12> array_2)
{
	int result = 0;
	for (int j = 0; j < 12; j++) result += array_1[j] * array_2[j];
	return result;
}

Chord_::Chord_(string name_)
{
	name = name_;
	if (name[1] == 'b' || name[1] == '#')
	{
		base_note = { name[0], name[1] };
		if (name.substr(2) != "") type = name.substr(2);
		else type = "major";
	}
	else
	{
		base_note = { name[0] };
		if (name.substr(1) != "") type = name.substr(1);
		else type = "major";
	}
}

array<int, 12> Chord_::chord_vector()
{
	Note my_note(base_note, 3);
	int start_note = my_note.number();
	
	if (type == "major") return vector_by_rule(start_note, rule_major);
	if (type == "m") return vector_by_rule(start_note, rule_m);
	if (type == "aug") return vector_by_rule(start_note, rule_aug);
	if (type == "dim") return vector_by_rule(start_note, rule_dim);
	if (type == "sus4") return vector_by_rule(start_note, rule_sus4);
	
	if (type == "7") return vector_by_rule(start_note, rule_7);
	if (type == "m7") return vector_by_rule(start_note, rule_m7);
	if (type == "maj7") return vector_by_rule(start_note, rule_maj7);
}

vector<int> Chord_::chord_notes()
{
	vector<int> our_array;
	array<int, 12> help_array = chord_vector();
	for (int i = 0; i < 12; i++) if (help_array[i] == 1) our_array.push_back(i);
	return our_array;
}

bool Chord_::is_in_key(Key some_key)
{
	array<int, 12> our_chord_vector = chord_vector();
	array<int, 12> our_key_vector = some_key.key_vector();
	int result = scalar_product(our_chord_vector, our_key_vector);
	if (result >= 3) return true;
	else return false;
}

vector<Chord_> get_all_chords(array<string, 96> list_of_names)
{
	vector<Chord_> all_chords;
	for (int i = 0; i < 96; i++)
	{
		Chord_ one_chord(list_of_names[i]);
		
		all_chords.push_back(one_chord);
	}

	return all_chords;
}