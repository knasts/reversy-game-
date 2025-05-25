#ifndef BOARD_H_DEFINED
#define BOARD_H_DEFINED
#include <SFML/Graphics.hpp>
#include <vector>
#include "MainMenu.h"
#define Max_playing_menu 9
using namespace std;

static const int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
static const int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

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
	sf::Text playing_menu[Max_playing_menu];
	sf::VideoMode video_mode;
	sf::RenderWindow* win;
	sf::Font font;
	sf::Clock game_end_clock;
	BoardChip board_info[8][8];
	int cell_size;
	int counter_pl1;
	int counter_pl2;

	bool player1_turn();
	void draw_chip(int i, int j);
	void flip_chips(int i, int j, int current_player);
	bool check_this_move(int row, int col, int current_player); //перевантажена версія
	bool check_this_move(int row, int col);
	bool player_can_make_move(int player);

	std::vector<sf::Vector2f> avaliable_positions();

public:
	Board(sf::RenderWindow& win, const sf::Color& col1, const sf::Color& col2, sf::Font& font);
	sf::Color color_pl1;
	sf::Color color_pl2;
	sf::Clock pass_clock;
	bool show_pass_move;
	int whos_turn;
	bool pause;
	bool game_over;
	bool hide_board;
	bool game_end_clock_started;

	void draw_play_texts();
	void draw_board_grid();

	bool restart_clicked(const sf::Vector2f& mouse_pos) const;
	bool end_clicked(const sf::Vector2f& mouse_pos) const;

	void update_button(const sf::Vector2f& mouse_pos);
	void place_chip(const sf::Vector2f& mouse_pos);
	void draw_all_chips();
	void place_dots();
	void curr_game_over();
	void check_turn();

};

#endif

