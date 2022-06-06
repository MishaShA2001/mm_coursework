#include "Melody_analysis.h"
#include "Get_and_draw_keyboard.h"
#include "Note_class.h"
#include "Key_class.h"
#include "Chord_class.h"
#include "windows.h"
#include <string>

#include <iostream>
using namespace std;

string string_for_texts_8 = "Chords: ";

array<string, 12> notes_names_analysis = { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };

int counter = 0;
int general_len = 0;

bool isNewMelody = 0;

vector<int> played_notes;
array<int, 12> played_notes_array = { 0 };
array<int, 12> general_played_notes_array = { 0 };

vector<vector<int>> played_notes_set;
vector<array<int, 12>> played_notes_arrays_set;

array<array<int, 12>, 72> all_keys_arrays;
array<array<int, 12>, 96> all_chords_arrays;

Key possible_key("C-dur", "n");
vector<Chord_> possible_chords;

array<string, 24> for_keys = { "C-dur", "Cis-dur", "D-dur", "Dis-dur", "E-dur", "F-dur", "Fis-dur", "G-dur", "Gis-dur", "A-dur", "Ais-dur", "B-dur",
"c-moll", "cis-moll", "d-moll", "dis-moll", "e-moll", "f-moll", "fis-moll", "g-moll", "gis-moll", "a-moll", "ais-moll", "b-moll" };

array<string, 12> for_chords_notes = { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };
array<string, 8> for_chords_types = { "", "m", "aug", "dim", "sus4", "7", "m7", "maj7" };

void melody_analysis(RenderWindow& window, array<Text, 10> texts, Text text_to_menu, array<Sound, 24> notes)
{
	vector<RectangleShape> all_keyboard = get_keyboard();

	Color background_color(255, 255, 200);

	window.clear(background_color);

	for (int i = 2; i < 6; i++)
	{
		if (i == 2 || i == 4 || i == 5)
			if (texts[i].getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
				texts[i].setStyle(Text::Underlined);
	}

	if (texts[9].getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
		texts[9].setStyle(Text::Underlined | Text::Italic);

	if (text_to_menu.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
		text_to_menu.setStyle(Text::Underlined | Text::Italic);

	array<int, 10> help_array = { 1, 3, 6, 8, 10, 13, 15, 18, 20, 22 };
	for (int i = 0; i < all_keyboard.size(); i++)
	{
		if (all_keyboard[i].getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
		{
			auto it = find(help_array.begin(), help_array.end(), i);
			all_keyboard[i].setFillColor(Color::Green);
			int current_octave;
			if (i / 12 == 1) current_octave = 3;
			else current_octave = 2;
			Note current_note(notes_names_analysis[i % 12], current_octave);
			texts[0].setString(notes_names_analysis[i % 12] + ", " + to_string(current_note.frequency()) + " Hz");
			if (it != help_array.end())
			{
				all_keyboard[i - 1].setFillColor(Color::White);
				all_keyboard[i + 1].setFillColor(Color::White);
				break;
			}
		}
	}

	for (int i = 0; i < 24; i++)
	{
		auto it = find(help_array.begin(), help_array.end(), i);
		if (it != help_array.end() || i == 23)
		{
			if (all_keyboard[i].getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) &&
				Mouse::isButtonPressed(Mouse::Left))
			{
				if (isNewMelody)
				{
					played_notes.push_back(i);
					played_notes_array[i % 12] = 1;
				}
				notes[i].play();
				Sleep(1000);
			}
		}
		else
		{
			if (all_keyboard[i].getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) &&
				all_keyboard[i + 1].getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) == 0 &&
				Mouse::isButtonPressed(Mouse::Left))
			{
				if (isNewMelody)
				{
					played_notes.push_back(i);
					played_notes_array[i % 12] = 1;
				}
				notes[i].play();
				Sleep(1000);
			}
		}
	}

	if (texts[2].getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) &&
		Mouse::isButtonPressed(Mouse::Left))
	{
		isNewMelody = 1;
		played_notes_set.clear();
		played_notes_arrays_set.clear();
		played_notes.clear();
		for (int i = 0; i < 12; i++)
			played_notes_array[i] = 0;
		counter = 0;
		general_len = 0;
		string_for_texts_8 = "Chords: ";
		possible_chords.clear();
	}

	if (texts[4].getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) &&
		Mouse::isButtonPressed(Mouse::Left))
	{
		played_notes_set.push_back(played_notes);
		played_notes_arrays_set.push_back(played_notes_array);

		played_notes.clear();
		for (int i = 0; i < 12; i++)
			played_notes_array[i] = 0;

		counter += 1;
		string_for_texts_8 = "Chords: ";
		Sleep(500);
	}

	if (texts[5].getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) &&
		Mouse::isButtonPressed(Mouse::Left))
	{
		isNewMelody = 0;
		counter = 0;
		general_played_notes_array = { 0 };
		general_len = 0;
		possible_chords.clear();

		for (int i = 0; i < played_notes_arrays_set.size(); i++)
			for (int j = 0; j < 12; j++)
				general_played_notes_array[j] += played_notes_arrays_set[i][j];

		for (int i = 0; i < 12; i++)
			if (general_played_notes_array[i] != 0)
			{
				general_played_notes_array[i] /= general_played_notes_array[i];
				general_len += 1;
			}

		if (general_len >= 3)
		{
			vector<Key> all_keys = get_all_keys(for_keys);
			for (int i = 0; i < 72; i++)
				all_keys_arrays[i] = all_keys[i].key_vector();

			int max_scalar_product = 2;
			for (int i = 0; i < 72; i++)
				if (scalar_product(all_keys_arrays[i], general_played_notes_array) > max_scalar_product)
				{
					max_scalar_product = scalar_product(all_keys_arrays[i], general_played_notes_array);
					possible_key = all_keys[i];
					if (max_scalar_product == 7) break;
				}

			array<string, 96> for_chords;
			int counter_for_chords = 0;
			for (int i = 0; i < 8; i++)
				for (int j = 0; j < 12; j++)
				{
					for_chords[counter_for_chords] = for_chords_notes[j] + for_chords_types[i];
					counter_for_chords += 1;
				}
			
			vector<Chord_> all_chords = get_all_chords(for_chords);
			for (int i = 0; i < 96; i++)
				all_chords_arrays[i] = all_chords[i].chord_vector();

			array<int, 12> ones = { 1 };
			for (int i = 0; i < played_notes_arrays_set.size(); i++)
			{
				if (scalar_product(ones, played_notes_arrays_set[i]) < 3)
				{
					max_scalar_product = 0;
					Chord_ possible_chord("C");

					for (int j = 0; j < 96; j++)
						if (all_chords[j].is_in_key(possible_key))
						{
							possible_chord = all_chords[j];
							break;
						}

					for (int j = 0; j < 96; j++)
					{
						if (scalar_product(played_notes_arrays_set[i], all_chords_arrays[j]) > max_scalar_product &&
							all_chords[j].is_in_key(possible_key))
						{
							possible_chord = all_chords[j];
							max_scalar_product = scalar_product(played_notes_arrays_set[i], all_chords_arrays[j]);
						}
					}
					possible_chords.push_back(possible_chord);
				}

				else
				{
					max_scalar_product = 1;
					Chord_ possible_chord("C");

					for (int j = 0; j < 96; j++)
						if (scalar_product(played_notes_arrays_set[i], all_chords_arrays[j]) > max_scalar_product)
						{
							max_scalar_product = scalar_product(played_notes_arrays_set[i], all_chords_arrays[j]);
							possible_chord = all_chords[j];
						}
					
					possible_chords.push_back(possible_chord);
				}
			}
		}

		string_for_texts_8 = "Chords: ";
		for (int k = 0; k < possible_chords.size(); k++)
		{
			if (k != possible_chords.size() - 1)
				string_for_texts_8 += possible_chords[k].name + ", ";
			else
				string_for_texts_8 += possible_chords[k].name;
		}

		Sleep(500);
	}

	if (texts[9].getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) &&
		Mouse::isButtonPressed(Mouse::Left))
	{
		if (general_len >= 3)
		{
			for (int i = 0; i < played_notes_set.size(); i++)
			{
				vector<int> current_chord_notes = possible_chords[i].chord_notes();
				for (int j = 0; j < current_chord_notes.size(); j++)
					notes[current_chord_notes[j]].play();
				for (int j = 0; j < played_notes_set[i].size(); j++)
				{
					notes[played_notes_set[i][j]].play();
					if (j == played_notes_set[i].size() - 1)
						Sleep(1000);
					else Sleep(500);
				}
			}
		}
	}

	if (isNewMelody)
	{
		texts[3].setString("Play tact " + to_string(counter + 1) + ", then press The next tact");
	}

	if (isNewMelody == 0)
	{
		texts[3].setString("");

		if (general_len < 3)
		{
			texts[7].setString("Key: there aren't any tacts or there aren't enough notes to define");
			texts[8].setString("Chords: there aren't any tacts or there aren't enough notes to define");
		}

		else
		{
			texts[7].setString("Key: " + possible_key.base_note + ", " + possible_key.type + ", " + possible_key.lad);
			texts[8].setString(string_for_texts_8);
		}
	}

	draw_keyboard(window, all_keyboard);
	for (int i = 0; i < 10; i++) window.draw(texts[i]);
	window.draw(text_to_menu);
	window.display();
}
