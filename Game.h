#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Network.hpp"
#include "MainMenu.h"
#include "Board.h"

enum GameState
{
	MAIN_MENU,
	PLAYING
};

class Game
{
private:
	sf::RenderWindow* window;
	sf::VideoMode video_mode;
	sf::Event event;

	void init_variables();
	void init_window();
	sf::RectangleShape create_board();
	GameState currState;
	MainMenu* mainMenu;
	Board* board;
	sf::RectangleShape background;
	sf::Texture main_texture;
	bool board_created;

public:
	Game();
	virtual ~Game();

	const bool window_is_open() const;
	void pollevents();
	void update();
	void render();
};

#endif 

