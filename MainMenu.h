#ifndef MAINMENU_H_INCLUDED
#define MAINMENU_H_INCLUDED
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Network.hpp"
#define Max_main_menu 5
#define Max_main_buttons 4

static const sf::Color Purple(228, 162, 255, 255);
static const sf::Color Pink(255, 153, 204, 255);
static const sf::Color Yellow(241, 255, 123, 255);
static const sf::Color Blue(153, 204, 255, 255);
static const sf::Color Main_color(204, 0, 102, 255);
static const sf::Color Main_darker(162, 0, 81, 255);

class MainMenu
{
public:
	MainMenu(float width, float height);
	
	static sf::Font& get_font();

	void draw_m(sf::RenderWindow& window);
	int MainMenu_pressed()
	{
		return mainM_selected;
	};
	bool start_clicked(const sf::Vector2f& mouse_pos) const;
	void update_button(const sf::Vector2f& mouse_pos);

	sf::CircleShape color_button[4];
	int selected_color_pl1 = -1;
	int selected_color_pl2 = -1;
	sf::Color button_color_pl1;
	sf::Color button_color_pl2;

	bool color_button_cl(const sf::Vector2f& mouse_pos);
	void update_color_buttons();
	bool both_buttons_selected();
	~MainMenu();
private:
	int mainM_selected;
	sf::Text main_menu[Max_main_menu];
	static sf::Font font;
	static void load_font();
};

#endif 

