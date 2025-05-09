#include "Board.h"
#include "MainMenu.h"
#include <iostream>

BoardChip::BoardChip()
{
	status = 0;
	color = sf::Color(255, 255, 255, 255);
}

Board::Board(sf::RenderWindow& win, const sf::Color& col1, const sf::Color& col2, sf::Font& font)
{
	this->win = &win;
	this->font = font;
	this->color_pl1 = col1; 
	this->color_pl2 = col2;
	this->cell_size = 60.f;

	float total_width = 8 * cell_size;
	float start_x = ((win.getSize().x - total_width) / 2.f) + 40.f;
	float start_y = ((win.getSize().y - total_width) / 2.f) + 70.f;

	counter_pl1 = 0;
	counter_pl2 = 0;

	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j)
		{
			board_info[i][j].status = 0;
			board_info[i][j].color = sf::Color::White;
			board_info[i][j].position = sf::Vector2f(start_x + j * cell_size, start_y + i * cell_size);

		}

	board_info[3][3].status = 1; //player 1
	board_info[3][3].color = this->color_pl1;
	board_info[4][4].status = 1;
	board_info[4][4].color = this->color_pl1;

	board_info[3][4].status = 2; // player 2
	board_info[3][4].color = this->color_pl2;
	board_info[4][3].status = 2;
	board_info[4][3].color = this->color_pl2;

	counter_pl1 += 2;
	counter_pl2 += 2;

	playing_menu[0].setFont(MainMenu::get_font());
	playing_menu[0].setFillColor(Main_color);
	playing_menu[0].setString("Turn:");
	playing_menu[0].setCharacterSize(58);
	playing_menu[0].setPosition(153, 7);

	whos_turn = 2;
}

bool Board::player1_turn()
{
	return (whos_turn % 2) == 0; // €кщо парне число, то черга першого гравц€
}

void Board::draw_board_grid()
{
	int rows = 8;
	int cols = 8;

	float total_width = cols * cell_size;

	float start_x = ((win->getSize().x - total_width) / 2.f) + 40.f - 7.f;
	float start_y = ((win->getSize().y - total_width) / 2.f) + 70.f - 7.f;

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			sf::RectangleShape cell;
			cell.setSize(sf::Vector2f(this->cell_size, this->cell_size));
			cell.setPosition(start_x + j * cell_size, start_y + i * cell_size);
			cell.setFillColor(sf::Color(196, 145, 100, 140)); //brown
			cell.setOutlineThickness(2.f);
			cell.setOutlineColor(sf::Color(162, 0, 81, 255));

			win->draw(cell);
		}
	}
}






void Board::draw_chip(int i, int j)
{
	if (board_info[i][j].status == 0) return;
	
	sf::Vector2f position = board_info[i][j].position;

	sf::CircleShape chip(23.f);
	chip.setPosition(position);

	chip.setFillColor(board_info[i][j].color);
	chip.setOutlineThickness(2.5);
	chip.setOutlineColor(sf::Color(162, 0, 81, 255));

	win->draw(chip);

}


void Board::place_chip(const sf::Vector2f& mouse_pos)
{
	for(int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			std::cout << "Clicked: " << mouse_pos.x << ", " << mouse_pos.y << std::endl;
			BoardChip& chip = board_info[i][j];
			sf::FloatRect bounds(chip.position, sf::Vector2f(cell_size, cell_size));

			if (chip.status == 0 && bounds.contains(mouse_pos))
			{
				if (player1_turn())
				{
					chip.status = 1;
					chip.color = this->color_pl1;
					counter_pl1++;
				}
				else
				{
					chip.status = 2;
					chip.color = this->color_pl2;
					counter_pl2++;
				}
				std::cout << "Placed chip for player " << (player1_turn() ? 1 : 2) << " at " << i << "," << j << std::endl;

				whos_turn++;
			}
		}
}

void Board::draw_all_chips()
{
	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j)
			draw_chip(i, j);
}
