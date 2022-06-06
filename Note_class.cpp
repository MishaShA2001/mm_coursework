#include "Note_class.h"
#include <cmath>
#include <array>

int A3_frequency = 440;

array<string, 12> notes_names_var_1 = { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };
array<string, 12> notes_names_var_2 = { "C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B" };

Note::Note(string str, int oct)
{
	name = str;
	octave = oct;
}

int Note::number()
{
	auto it_1 = find(notes_names_var_1.begin(), notes_names_var_1.end(), name);
	if (it_1 != notes_names_var_1.end()) return it_1 - notes_names_var_1.begin();
	else
	{
		auto it_2 = find(notes_names_var_2.begin(), notes_names_var_2.end(), name);
		return it_2 - notes_names_var_2.begin();
	}
}

float Note::frequency()
{
	int diff_in_octave = number() - 9;
	int diff_between_octaves = octave - 3;
	return A3_frequency * pow(pow(2, 1./12.), diff_in_octave) * pow(2, diff_between_octaves);
}