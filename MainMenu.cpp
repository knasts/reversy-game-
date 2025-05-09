#include "MainMenu.h"
#include "Board.h"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Network.hpp"
#include <iostream>
using namespace std;

sf::Font MainMenu::font;

void MainMenu::load_font()
{
	if (!font.loadFromFile("fonts/Wasted-Vindey.ttf")) //"Graphics/Milven-Regular.ttf"
	{
		throw runtime_error("can't load a font");
	}
}

sf::Font& MainMenu::get_font()
{  
   return font;  
}
  
MainMenu::MainMenu(float width, float height)
{
	this->load_font();
	main_menu[0].setFont(font);
	main_menu[0].setFillColor(Main_color);
	main_menu[0].setString("Welcome!");
	main_menu[0].setCharacterSize(58);
	main_menu[0].setPosition(153, 7);

	main_menu[4].setFont(font);
	main_menu[4].setFillColor(Main_darker);
	main_menu[4].setString("Choose colors & press the start!");
	main_menu[4].setCharacterSize(44);
	main_menu[4].setPosition(120, 62);

	main_menu[1].setFont(font);
	main_menu[1].setFillColor(Main_color);
	main_menu[1].setString("Player 1:");
	main_menu[1].setCharacterSize(50);
	main_menu[1].setPosition(150, 150);

	color_button[0].setRadius(40.f);
	color_button[0].setPosition(300, 250);
	color_button[0].setFillColor(Purple); //purple 

	color_button[1].setRadius(40.f);
	color_button[1].setPosition(450, 250);
	color_button[1].setFillColor(Pink); //pink

	main_menu[2].setFont(font);
	main_menu[2].setFillColor(Main_color);
	main_menu[2].setString("Player 2:");
	main_menu[2].setCharacterSize(50);
	main_menu[2].setPosition(150, 380);

	color_button[2].setRadius(40.f);
	color_button[2].setPosition(300, 480);
    color_button[2].setFillColor(Yellow); //yellow

	color_button[3].setRadius(40.f);
	color_button[3].setPosition(450, 480);
	color_button[3].setFillColor(Blue); //blue

	main_menu[3].setFont(font);
	main_menu[3].setFillColor(Main_color);
	main_menu[3].setString("Start");
	main_menu[3].setCharacterSize(80);
	main_menu[3].setPosition(340, 580);


	mainM_selected = -1;
}

void MainMenu::draw_m(sf::RenderWindow& window)
{
	for (int i = 0; i < Max_main_menu ; i++)
	{
		window.draw(main_menu[i]);
	}
	for (int i = 0; i < Max_main_buttons; i++)
	{
		window.draw(color_button[i]);
	}
}

bool MainMenu::start_clicked(const sf::Vector2f& mouse_pos) const
{
	sf::FloatRect bounds = main_menu[3].getGlobalBounds();
	return bounds.contains(mouse_pos);
}

void MainMenu::update_button(const sf::Vector2f& mouse_pos)
{
	sf::FloatRect bounds = main_menu[3].getGlobalBounds();

	if (bounds.contains(mouse_pos))
	{
		main_menu[3].setFillColor(Main_darker); //при наведенні
	}
	else main_menu[3].setFillColor(Main_color);

}

bool MainMenu::color_button_cl(const sf::Vector2f& mouse_pos)
{
	for (int i = 0; i < Max_main_buttons; ++i)
	{
		if (color_button[i].getGlobalBounds().contains(mouse_pos))
		{
			if (i < 2)
			{
 				selected_color_pl1 = i;
				if (i == 0) button_color_pl1 = Purple;
				else button_color_pl1 = Pink;
			}
			else selected_color_pl2 = i;
			{
				if (i == 2) button_color_pl2 =  Yellow;
				else button_color_pl2 = Blue;
			}
			update_color_buttons();
			return true;
		}
	}
	return false;
}

void MainMenu::update_color_buttons()
{
	for (int i = 0; i < Max_main_buttons; ++i)
	{
		bool selected = (i < 2 && i == selected_color_pl1) || (i >= 2 && i == selected_color_pl2);
		{
			color_button[i].setOutlineThickness(selected ? 3.f : 0.f);
			color_button[i].setOutlineColor(Main_darker);
		}
		
		
	}
}

bool MainMenu::both_buttons_selected()
{
	return selected_color_pl1 != -1 && selected_color_pl2 != -1;
}

MainMenu::~MainMenu()
{
}
