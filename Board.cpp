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
	this->whos_turn = 0;
	this->game_over = false;
	this->show_pass_move = false;
	this->pause = false;
	this->hide_board = false;
	this->game_end_clock_started = false;

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
	playing_menu[0].setCharacterSize(55);
	playing_menu[0].setPosition(183, 11);

	playing_menu[1].setFont(MainMenu::get_font());
	playing_menu[1].setFillColor(col1);
	playing_menu[1].setString("PLAYER 1");
	playing_menu[1].setCharacterSize(60);
	playing_menu[1].setPosition(350, 8);
	playing_menu[1].setOutlineThickness(1.2);
	playing_menu[1].setOutlineColor(Main_darker);

	playing_menu[2].setFont(MainMenu::get_font());
	playing_menu[2].setFillColor(col2);
	playing_menu[2].setString("PLAYER 2");
	playing_menu[2].setCharacterSize(60);
	playing_menu[2].setPosition(350, 8);
	playing_menu[2].setOutlineThickness(1.2);
	playing_menu[2].setOutlineColor(Main_darker);

	playing_menu[5].setFont(MainMenu::get_font());
	playing_menu[5].setFillColor(Main_color);
	playing_menu[5].setString("DRAW!");
	playing_menu[5].setCharacterSize(60);
	playing_menu[5].setPosition(350, 8);
	playing_menu[5].setOutlineThickness(1.2);
	playing_menu[5].setOutlineColor(Main_darker);

	playing_menu[4].setFont(MainMenu::get_font());
	playing_menu[4].setFillColor(Main_color);
	playing_menu[4].setString("Winner: ");
	playing_menu[4].setCharacterSize(55);
	playing_menu[4].setPosition(163, 7);

	playing_menu[3].setFont(MainMenu::get_font());
	playing_menu[3].setFillColor(Main_color);
	playing_menu[3].setString("GAME OVER!");
	playing_menu[3].setCharacterSize(80);
	playing_menu[3].setPosition(170, 63);

	playing_menu[6].setFont(MainMenu::get_font());
	playing_menu[6].setFillColor(Main_color);
	playing_menu[6].setString("Passing turn~~");
	playing_menu[6].setCharacterSize(55);
	playing_menu[6].setPosition(183, 67);

	playing_menu[7].setFont(MainMenu::get_font());
	playing_menu[7].setFillColor(Main_darker);
	playing_menu[7].setString("New game");
	playing_menu[7].setCharacterSize(70);
	playing_menu[7].setPosition(160, 280);

	playing_menu[8].setFont(MainMenu::get_font());
	playing_menu[8].setFillColor(Main_darker);
	playing_menu[8].setString("Exit");
	playing_menu[8].setCharacterSize(70);
	playing_menu[8].setPosition(515, 280);

	whos_turn = 2;
}

bool Board::player1_turn()
{
	return (whos_turn % 2) == 0; 
}

void Board::draw_play_texts()
{
	if (!game_over)
	{
		win->draw(playing_menu[0]);
		if (player1_turn()) win->draw(playing_menu[1]);
		else win->draw(playing_menu[2]);

		if (show_pass_move && pass_clock.getElapsedTime().asSeconds() < 1.3)
		{
			win->draw(playing_menu[6]);
		}
	}
	else
	{
		win->draw(playing_menu[3]);
		win->draw(playing_menu[4]);
		if(counter_pl1 > counter_pl2) win->draw(playing_menu[1]);
		else if(counter_pl1 < counter_pl2) win->draw(playing_menu[2]);
		else win->draw(playing_menu[5]);

		float end_seconds = game_end_clock.getElapsedTime().asSeconds();

		if(end_seconds >= 3.0f)
		{
			if(!hide_board) hide_board = true;

			win->draw(playing_menu[7]);
			win->draw(playing_menu[8]);
		}
	}
}

void Board::draw_board_grid()
{
	if (hide_board) return;

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

bool Board::restart_clicked(const sf::Vector2f& mouse_pos) const
{
	sf::FloatRect bounds = playing_menu[7].getGlobalBounds();
	return bounds.contains(mouse_pos);
}

bool Board::end_clicked(const sf::Vector2f& mouse_pos) const
{
	sf::FloatRect bounds = playing_menu[8].getGlobalBounds();
	return bounds.contains(mouse_pos);
}

void Board::update_button(const sf::Vector2f& mouse_pos)
{
	sf::FloatRect bounds = playing_menu[7].getGlobalBounds();
	sf::FloatRect boundss = playing_menu[8].getGlobalBounds();

	if (bounds.contains(mouse_pos))
	{
		playing_menu[7].setFillColor(Main_color); //при наведенні
	}
	else playing_menu[7].setFillColor(Main_darker);

	if (boundss.contains(mouse_pos))
	{
		playing_menu[8].setFillColor(Main_color); //при наведенні
	}
	else playing_menu[8].setFillColor(Main_darker);
}

void Board::check_turn()
{
	//перевіряємо чи гра зікінчилася
	bool pl1_move = player_can_make_move(1);
	bool pl2_move = player_can_make_move(2);

	if (!pl1_move && !pl2_move)
	{
		curr_game_over();
		if (!game_end_clock_started)
		{
			game_end_clock.restart();
			game_end_clock_started = true;
		}
		return;
	}
	else if ((player1_turn() && !pl1_move && pl2_move) || (!player1_turn() && pl1_move && !pl2_move))
	{
		std::cout << "no moves, skipping turn" << std::endl;
		show_pass_move = true;
		pass_clock.restart();
		pause = true;
	}
	else
	{
		show_pass_move = false;
	}
}


void Board::place_chip(const sf::Vector2f& mouse_pos)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			BoardChip& chip = board_info[i][j];
			sf::FloatRect bounds(chip.position, sf::Vector2f(cell_size, cell_size));

			if (chip.status == 0 && bounds.contains(mouse_pos) && check_this_move(i, j))
			{
				int current_player = 0;
				if (player1_turn())
				{
					chip.status = 1;
					chip.color = this->color_pl1;
					current_player = 1;
					counter_pl1++;
				}
				else
				{
					chip.status = 2;
					chip.color = this->color_pl2;
					current_player = 2;
					counter_pl2++;
				}
				flip_chips(i, j, current_player);
				show_pass_move = false;
				whos_turn++;
				check_turn();
				break;
			}
		}
	}
}


void Board::flip_chips(int row, int col, int current_player)
{
	int opp = (current_player == 1) ? 2 : 1;

	sf::Color player_color = (current_player == 1) ? color_pl1 : color_pl2;

	for (int k = 0; k < 8; ++k)
	{
		int x = row + dx[k];
		int y = col + dy[k];

		std::vector<std::pair<int, int>> to_flip;

		while (x >= 0 && x < 8 && y >= 0 && y < 8)
		{
			if (board_info[x][y].status == opp) to_flip.push_back({ x, y });
			else if (board_info[x][y].status == current_player)
			{
				for (auto& p : to_flip)
				{
					board_info[p.first][p.second].status = current_player;
					board_info[p.first][p.second].color = player_color;
					if (current_player == 1)
					{
						counter_pl1++;
						counter_pl2--;
					}
					else
					{
						counter_pl1--;
						counter_pl2++;
					}
				}
				break;
			}
			else break;
			
			x += dx[k];
			y += dy[k];
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

void Board::draw_all_chips()
{
	if (hide_board) return;
	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j)
			draw_chip(i, j);
}

bool Board::check_this_move(int row, int col, int current_player)
{
	if (board_info[row][col].status != 0) return false;

	int opp = (current_player == 1) ? 2 : 1;

	for (int k = 0; k < 8; k++)
	{
		int x = row + dx[k];
		int y = col + dy[k];
		bool opp_found = false;

		while (x >= 0 && x < 8 && y >= 0 && y < 8)
		{
			if (board_info[x][y].status == opp) opp_found = true;
			else if (board_info[x][y].status == current_player)
			{
				if (opp_found) return true;
				else break;
			}
			else break;

			x += dx[k];
			y += dy[k];
		}
	}
	return false;
}

bool Board::check_this_move(int row, int col)
{
	if (board_info[row][col].status != 0) return false;

	int current_player = player1_turn() ? 1 : 2;
	int opp = (current_player == 1) ? 2 : 1;

	for (int k = 0; k < 8; k++)
	{
		int x = row + dx[k];
		int y = col + dy[k];
		bool opp_found = false;

		while (x >= 0 && x < 8 && y >= 0 && y < 8)
		{
			if (board_info[x][y].status == opp) opp_found = true;
			else if (board_info[x][y].status == current_player)
			{
				if (opp_found) return true;
				else break;
			}
			else break;

			x += dx[k];
			y += dy[k];
		}
	}
	return false;
}

std::vector<sf::Vector2f> Board::avaliable_positions()
{
	std::vector<sf::Vector2f> moves_positions;

	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j)
		{
			if (check_this_move(i, j))
				moves_positions.push_back(board_info[i][j].position);

		}
	return moves_positions;
}

void Board::place_dots() 
{
	std::vector<sf::Vector2f> moves = avaliable_positions();

	for (const auto& pos: moves)
	{
		sf::CircleShape dot(5.f);
		dot.setFillColor(sf::Color(162, 0, 81, 255));
		dot.setOrigin(5.f, 5.f);
		dot.setPosition(pos.x + cell_size / 2 - 4.f, pos.y + cell_size / 2 - 4.f); 

		win->draw(dot);
	}
}

bool Board::player_can_make_move(int player)
{
	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j)
			if (check_this_move(i, j, player)) return true;
	return false;
}


void Board::curr_game_over()
{
	game_over = true;	
}

