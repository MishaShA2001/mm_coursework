#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <array>

using namespace sf;
using namespace std;

void melody_analysis(RenderWindow& window, array<Text, 10> texts, Text text_to_menu, array<Sound, 24> notes);
