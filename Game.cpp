#include "Game.h" 
#include "MainMenu.h"
#include "Board.h"
#include <vector>
using namespace std;

void Game::init_variables()
{
	this->window = nullptr;
	this->mainMenu = nullptr;
	this->currState = MAIN_MENU;
	this->board_created = false;
}

void Game::init_window()
{
	this->video_mode.height = 736;
	this->video_mode.width = 736;
	this->window = new sf::RenderWindow(this->video_mode, "my reversy game:)", sf::Style::Default);

	this->mainMenu = new MainMenu(this->video_mode.width, this->video_mode.height);
    sf::Vector2f mouse_pos = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));

	if (!this->main_texture.loadFromFile("backgrounds/my_backgroundd.jpg"))
	{
		throw std::runtime_error("background loading failed");
	}
	this->background.setSize(sf::Vector2f(this->video_mode.width, this->video_mode.height));
	this->background.setTexture(&this->main_texture);
}

sf::CircleShape Game::create_circle(int width)
{
	sf::CircleShape shape(width);
	shape.setFillColor(sf::Color::Cyan);
	return shape;
}

sf::RectangleShape Game::create_board()
{
	sf::RectangleShape shape(sf::Vector2f(480.f, 480.f));
	shape.setFillColor(sf::Color(180, 130, 80, 255));

	shape.setOrigin(shape.getSize().x / 2.f, shape.getSize().y / 2.f); //центр квадрата
	shape.setPosition((this->video_mode.width / 2.f) + 40, (this->video_mode.height / 2.f) + 70); //розташовуємо по центру
	return shape;
}

Game::Game() : video_mode(), event()
{
	this->init_variables();
	this->init_window();
}

Game::~Game()
{
	delete this->window;
	delete this->mainMenu;
	delete this->board;
}

const bool Game::window_is_open() const
{
	return this->window && this->window->isOpen();
}

void Game::pollevents() //check ivents
{
	while (this->window->pollEvent(this->event))
	{ 
		switch (this->event.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;

		case sf::Event::KeyPressed:
			if (this->event.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;

		case sf::Event::MouseButtonPressed:
			if (this->event.mouseButton.button == sf::Mouse::Left)
			{
				sf::Vector2f mouse_pos
				(
					static_cast<float>(this->event.mouseButton.x),
					static_cast<float>(this->event.mouseButton.y)
				);

				if (this->currState == MAIN_MENU && this->mainMenu)
				{
					this->mainMenu->color_button_cl(mouse_pos);

					if (this->mainMenu->start_clicked(mouse_pos))
					{
						if (this->mainMenu->both_buttons_selected())
						{
							this->currState = PLAYING;
						}
					}
				}
				else if (this->currState == PLAYING && this->board)
				{
					this->board->place_chip(mouse_pos);
				}
			}
			break;
		}

	}
}

void Game::update() //where game is
{
	this->pollevents();

	if (this->currState == MAIN_MENU && this->mainMenu && this->window)
	{
		sf::Vector2i pixel_pos = sf::Mouse::getPosition(*this->window);
		sf::Vector2f world_pos = this->window->mapPixelToCoords(pixel_pos);
		this->mainMenu->update_button(world_pos);
	}

	else if (this->currState == PLAYING)
	{
		if (!this->board_created)
		{
			const sf::Color col1 = this->mainMenu->button_color_pl1;
			const sf::Color col2 = this->mainMenu->button_color_pl2;
			this->board = new Board(*this->window, col1, col2, MainMenu::get_font());
			this->board_created = true;
		}
		else
		{
			if (this->board->show_pass_move && this->board->pass_clock.getElapsedTime().asSeconds() >= 2.0f
				&& this->board->pause)
			{
				this->board->whos_turn++;
				this->board->pause = false;
				this->board->show_pass_move = false;
			}
			else if (!this->board->pause) this->board->check_turn();
		}
	}
}

void Game::render() //visualisation where everything is
{
	this->window->clear();

	this->window->draw(this->background);

	if (this->currState == MAIN_MENU)
	{
		if (this->mainMenu)
		{
			this->mainMenu->draw_m(*this->window);
		}
	}
	else if (this->currState == PLAYING)
	{
		if (this->board)
		{
			this->board->draw_board_grid();
			this->board->draw_all_chips();
			this->board->place_dots();
			this->board->draw_play_texts();
		}
	}

	this->window->display();
}
