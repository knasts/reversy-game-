#ifndef BOARD_H_DEFINED
#define BOARD_H_DEFINED
#include <SFML/Graphics.hpp>
#include "MainMenu.h"
#define Max_playing_menu 2
using namespace std;

struct BoardChip
{
	BoardChip();
	int status;
	sf::Color color;
	sf::Vector2f position;
};

class Board
{
private:; 
	BoardChip board_info[8][8]; 
	sf::Text playing_menu[Max_playing_menu];
	int cell_size;
	sf::VideoMode video_mode;
	sf::RenderWindow* win;
	sf::Font font;

	int counter_pl1;
	int counter_pl2;

	int whos_turn;
	bool player1_turn();

public:
	Board(sf::RenderWindow& win, const sf::Color& col1, const sf::Color& col2, sf::Font& font);
	sf::Color color_pl1;
	sf::Color color_pl2;

	void draw_board_grid();
	void draw_chip(int i, int j);
	void place_chip(const sf::Vector2f& mouse_pos);

	void draw_all_chips();

};

#endif

