#pragma once
/*
	 Class that acts as the game engine
	 Wrapper class.
*/
#include <iostream>;
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include<SFML/Window.hpp>
#include <ctime>
using namespace sf;
class Game
{
private:		
	//Variables 
	//Window 
	RenderWindow* window;
	Event eve;
	VideoMode videoMode;

	//Mouse position
	Vector2i MousePosWindow;// Vector2i because it holds 2 integer , if it should hold 2 floats , make it 2f
	Vector2f MousePosView;

	//Game Logic
	float EnemySpawnTimer;
	float EnemySpawnTimerMax;
	int maxEnemies;
	int health;
	unsigned points;
	bool mouseHeld;
	//Game Objects 
	std::vector<sf::RectangleShape>enemies;
	std::vector<sf::Color>colours;
	RectangleShape enemy;
	//sf::CircleShape enemy;


	//Private functions
	void initializeVariables(), initializeWindow(), initializeEnemies();



public:
	//Constructors /Destructors 
	Game();
	virtual ~Game();
	//Accessors
	const bool GAMERUNNING() const;
	//Functions
	void update(), render(), UpdateEvents(), updateMousePositions(), spawnenemy(), updateenemies(),
		 renderenemies();
};
