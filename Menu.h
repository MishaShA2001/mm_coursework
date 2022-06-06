#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <array>

using namespace sf;
using namespace std;

void menu(RenderWindow& window, array<Text, 4> texts, array<Sound, 24> notes);
