#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <array>
#include "Menu.h"
#include "Melody_analysis.h"
#include "Mini_game.h"

#include <iostream>

using namespace sf;
using namespace std;

int main()
{
	RenderWindow window(VideoMode(1600, 800), "Our_piano");

	Font font_arial;
	font_arial.loadFromFile("arial.ttf");

	array<Text, 4> texts_menu;

	Text notes_text("", font_arial, 35);
	notes_text.setFillColor(Color::Black);
	notes_text.setStyle(Text::Italic);
	notes_text.setPosition(Vector2f(212, 500));
	texts_menu[0] = notes_text;

	Text hello_text("Welcome!", font_arial, 55);
	hello_text.setFillColor(Color::Magenta);
	hello_text.setStyle(Text::Bold);
	hello_text.setPosition(Vector2f(212, 0));
	texts_menu[1] = hello_text;

	Text text_melody_analysis("- Melody analysis", font_arial, 45);
	text_melody_analysis.setFillColor(Color::Black);
	text_melody_analysis.setPosition(Vector2f(212, 120));
	texts_menu[2] = text_melody_analysis;

	Text text_mini_game("- Mini-game", font_arial, 45);
	text_mini_game.setFillColor(Color::Black);
	text_mini_game.setPosition(Vector2f(212, 180));
	texts_menu[3] = text_mini_game;

	Text text_to_menu("To the menu", font_arial, 35);
	text_to_menu.setFillColor(Color::Magenta);
	text_to_menu.setStyle(Text::Italic);
	text_to_menu.setPosition(Vector2f(212, 50));

	array<Text, 10> texts_analysis;

	texts_analysis[0] = notes_text;

	Text text_top("Melody analysis", font_arial, 45);
	text_top.setFillColor(Color::Magenta);
	text_top.setStyle(Text::Bold);
	text_top.setPosition(Vector2f(212, 0));
	texts_analysis[1] = text_top;

	Text text_process("New melody", font_arial, 35);
	text_process.setFillColor(Color::Black);
	text_process.setPosition(Vector2f(212, 100));
	texts_analysis[2] = text_process;

	Text text_notes("", font_arial, 30);
	text_notes.setFillColor(Color::Black);
	text_notes.setStyle(Text::Italic);
	text_notes.setPosition(Vector2f(212, 150));
	texts_analysis[3] = text_notes;

	Text text_next("The next tact", font_arial, 35);
	text_next.setFillColor(Color::Black);
	text_next.setPosition(Vector2f(212, 200));
	texts_analysis[4] = text_next;

	Text text_stop("Stop", font_arial, 35);
	text_stop.setFillColor(Color::Black);
	text_stop.setPosition(Vector2f(212, 240));
	texts_analysis[5] = text_stop;

	Text text_results("Supposed results", font_arial, 40);
	text_results.setFillColor(Color::Blue);
	text_results.setStyle(Text::Italic);
	text_results.setPosition(Vector2f(212, 310));
	texts_analysis[6] = text_results;

	Text text_key("Key: ", font_arial, 30);
	text_key.setFillColor(Color::Blue);
	text_key.setPosition(Vector2f(212, 370));
	texts_analysis[7] = text_key;

	Text text_chords("Chords: ", font_arial, 30);
	text_chords.setFillColor(Color::Blue);
	text_chords.setPosition(Vector2f(212, 405));
	texts_analysis[8] = text_chords;

	Text text_play_result("Play result!", font_arial, 40);
	text_play_result.setFillColor(Color::Blue);
	text_play_result.setStyle(Text::Italic);
	text_play_result.setPosition(Vector2f(212, 450));
	texts_analysis[9] = text_play_result;


	array<Text, 5> texts_mini_game;

	texts_mini_game[0] = notes_text;

	Text text_top_game("Mini-game", font_arial, 45);
	text_top_game.setFillColor(Color::Magenta);
	text_top_game.setStyle(Text::Bold);
	text_top_game.setPosition(Vector2f(212, 0));
	texts_mini_game[1] = text_top_game;

	Text text_rules("Try to repeat our melody! The higher your level is, the more notes are played for you!", font_arial, 35);
	text_rules.setFillColor(Color::Black);
	text_rules.setPosition(Vector2f(212, 150));
	texts_mini_game[2] = text_rules;

	Text text_begin("Press to begin!", font_arial, 40);
	text_begin.setFillColor(Color::Black);
	text_begin.setStyle(Text::Italic);
	text_begin.setPosition(Vector2f(212, 310));
	texts_mini_game[3] = text_begin;

	Text text_game_result("", font_arial, 60);
	text_game_result.setFillColor(Color::Black);
	text_game_result.setPosition(Vector2f(212, 370));
	texts_mini_game[4] = text_game_result;


	array<Sound, 24> notes_sounds;
	array<SoundBuffer, 24> notes_buffers;

	for (int i = 0; i < 24; i++)
	{
		SoundBuffer notes_buffer;
		notes_buffers[i] = notes_buffer;
		notes_buffers[i].loadFromFile(to_string(i) + ".wav");
	}

	for (int i = 0; i < 24; i++)
	{
		Sound notes_sound(notes_buffers[i]);
		notes_sounds[i] = notes_sound;
	}

	bool isMenu = 1;
	string section;

	while (window.isOpen())
	{
		while (isMenu)
		{
			menu(window, texts_menu, notes_sounds);

			if (texts_menu[2].getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) &&
				Mouse::isButtonPressed(Mouse::Left))
			{
				isMenu = 0;
				section = "Melody analysis";
			}

			if (texts_menu[3].getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) &&
				Mouse::isButtonPressed(Mouse::Left))
			{
				isMenu = 0;
				section = "Mini-game";
			}

			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();
			}
		}

		while (isMenu == 0)
		{
			if (text_to_menu.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window))) &&
				Mouse::isButtonPressed(Mouse::Left))
				isMenu = 1;

			if (section == "Melody analysis")
				melody_analysis(window, texts_analysis, text_to_menu, notes_sounds);

			if (section == "Mini-game")
				mini_game(window, texts_mini_game, text_to_menu, notes_sounds);

			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();
			}
		}
	}

}