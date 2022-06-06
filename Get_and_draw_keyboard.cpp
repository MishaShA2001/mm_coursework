#include "Get_and_draw_keyboard.h"

vector<RectangleShape> get_keyboard()
{
	vector<RectangleShape> our_vector;
	
	for (int i = 0; i < 27; i++)
	{
		if (i % 2 == 0)
		{
			RectangleShape rectangle_white(Vector2f(84, 252));
			rectangle_white.setFillColor(Color::White);
			rectangle_white.setOutlineThickness(1);
			rectangle_white.setOutlineColor(Color::Black);

			rectangle_white.setPosition(Vector2f(212 + i / 2 * 84, 547));

			our_vector.push_back(rectangle_white);
		}
		else
		{
			if (i != 5 && i != 13 && i != 19)
			{
				RectangleShape rectangle_black(Vector2f(42, 168));
				rectangle_black.setFillColor(Color::Black);
				rectangle_black.setOutlineThickness(1);
				rectangle_black.setOutlineColor(Color::Black);

				rectangle_black.setPosition(Vector2f(275 + (i - 1) / 2 * 84, 547));

				our_vector.push_back(rectangle_black);
			}
		}
	}
	
	return our_vector;
}

void draw_keyboard(RenderWindow& window, vector<RectangleShape> some_keyboard)
{
	array<int, 10> help_array = { 1, 3, 6, 8, 10, 13, 15, 18, 20, 22 };

	for (int i = 0; i < some_keyboard.size(); i++)
	{
		auto it = find(help_array.begin(), help_array.end(), i);
		if (it == help_array.end()) window.draw(some_keyboard[i]);
	}

	for (int i = 0; i < some_keyboard.size(); i++)
	{
		auto it = find(help_array.begin(), help_array.end(), i);
		if (it != help_array.end()) window.draw(some_keyboard[i]);
	}
}
