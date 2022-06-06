#include "Menu.h"
#include "Get_and_draw_keyboard.h"
#include "Note_class.h"
#include "windows.h"

array<string, 12> notes_names_menu = { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };

void menu(RenderWindow& window, array<Text, 4> texts, array<Sound, 24> notes)
{
	vector<RectangleShape> all_keyboard = get_keyboard();

	Color background_color(255, 255, 200);

	window.clear(background_color);

	for (int i = 2; i < 4; i++)
	{
		if (texts[i].getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
			texts[i].setStyle(Text::Underlined);
	}

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
			Note current_note(notes_names_menu[i % 12], current_octave);
			texts[0].setString(notes_names_menu[i % 12] + ", " + to_string(current_note.frequency()) + " Hz");
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
				notes[i].play();
				Sleep(1000);
			}
		}
	}

	draw_keyboard(window, all_keyboard);
	for (int i = 0; i < 4; i++) window.draw(texts[i]);
	window.display();
}