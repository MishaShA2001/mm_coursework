#include "Mini_game.h"
#include "Get_and_draw_keyboard.h"
#include "Note_class.h"
#include "windows.h"

array<string, 12> notes_names_game = { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };

int level = 1;

bool isGame = 0;
bool isUser = 0;
bool game_result;

vector<int> played_by_game;
vector<int> played_by_user;

void mini_game(RenderWindow& window, array<Text, 5> texts, Text text_to_menu, array<Sound, 24> notes)
{
	vector<RectangleShape> all_keyboard = get_keyboard();

	Color background_color(255, 255, 200);

	window.clear(background_color);

	if (texts[3].getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))))
		texts[3].setStyle(Text::Underlined | Text::Italic);

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
			Note current_note(notes_names_game[i % 12], current_octave);
			texts[0].setString(notes_names_game[i % 12] + ", " + to_string(current_note.frequency()) + " Hz");
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
				if (isGame == 1 && isUser == 1)
					played_by_user.push_back(i);
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
				if (isGame == 1 && isUser == 1)
					played_by_user.push_back(i);
				notes[i].play();
				Sleep(1000);
			}
		}
	}

	if (texts[3].getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) &&
		Mouse::isButtonPressed(Mouse::Left))
	{
		isGame = 1;
		level = 1;
		played_by_game.clear();
		played_by_user.clear();

		Sleep(1000);
		for (int i = 0; i < level; i++)
		{
			int random_number = rand() % 24;
			played_by_game.push_back(random_number);
			notes[random_number].play();
			Sleep(1000);
		}
		isUser = 1;
	}

	if (text_to_menu.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) &&
		Mouse::isButtonPressed(Mouse::Left))
	{
		isGame = 0;
		level = 1;
		played_by_game.clear();
		played_by_user.clear();
	}

	if (isGame)
	{
		if (isUser == 0)
		{
			Sleep(1000);
			for (int i = 0; i < level; i++)
			{
				int random_number = rand() % 24;
				played_by_game.push_back(random_number);
				notes[random_number].play();
				Sleep(1000);
			}
			isUser = 1;
		}
		else
		{
			if (played_by_user.size() == level && played_by_user == played_by_game)
			{
				texts[4].setString("Correct!");
				texts[4].setFillColor(Color::Green);
				level += 1;
				isUser = 0;
				played_by_game.clear();
				played_by_user.clear();
			}
			
			if (played_by_user.size() == level && played_by_user != played_by_game)
			{
				texts[4].setString("Fail!");
				texts[4].setFillColor(Color::Red);
				isUser = 0;
				played_by_game.clear();
				played_by_user.clear();
			}
		}

	}

	draw_keyboard(window, all_keyboard);
	for (int i = 0; i < texts.size(); i++) window.draw(texts[i]);
	window.draw(text_to_menu);
	window.display();
}