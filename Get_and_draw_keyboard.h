#pragma once
#include <array>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

vector<RectangleShape> get_keyboard();
void draw_keyboard(RenderWindow& window, vector<RectangleShape> some_keyboard);
