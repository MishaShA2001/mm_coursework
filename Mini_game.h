#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <array>

using namespace sf;
using namespace std;

void mini_game(RenderWindow& window, array<Text, 5> texts, Text text_to_menu, array<Sound, 24> notes);