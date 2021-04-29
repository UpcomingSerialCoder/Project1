#include "Game.h"
#include <iostream>;
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include<SFML/Window.hpp>
#include<vector>
//Private functions
void Game::initializeVariables()
{
	this->window = nullptr;
	this->points = 0;
	this->EnemySpawnTimerMax = 50.f;// spawn timer
	this->EnemySpawnTimer = this->EnemySpawnTimerMax;	
	this->maxEnemies = 100000;
	this->mouseHeld = false;
	this->health = 100;
	this->colours = { Color::Green,Color::Black,Color::Blue };
}





void Game::initializeEnemies()
{
	// middle is located in (600, 0 ) 
	this->enemy.setPosition(600,400); 
	this->enemy.setSize(Vector2f(100.f, 100.f));// the f makes the parameters as float type
	//this->enemy.setRadius(100); if u want it back to circle
	this->enemy.setScale(Vector2f(0.5f, 0.5f));
	this->enemy.setFillColor(Color::Cyan);
	this->enemy.setOutlineColor(Color::Green);
	this->enemy.setOutlineThickness(1.f);
	
}





void Game::initializeWindow()
{
	this->videoMode.width = 1200;
	this->videoMode.height = 800; 
	 this->window = new RenderWindow(this->videoMode, "My game", Style::Default);
	this->window->setFramerateLimit(60); 
}






//Constructors / destructors 
Game::Game()
{
	this->      initializeVariables();
	this->         initializeWindow();
	this->		initializeEnemies();
}

Game::~Game()
{
	delete this->window;
}
//Accessors 
const bool Game::GAMERUNNING() const
{
	return this->window->isOpen();
}

//Functions
 
void Game::UpdateEvents()
{
	while (this->window->pollEvent(this->eve))
	{
		switch (this->eve.type)
		{
		case Event::Closed:
			this->window->close();
			break;
		case Event::KeyPressed:
			if (this->eve.key.code == Keyboard::Escape)
			{
				this->window->close();
			}
			break;
		}
	}
}

void Game::updateMousePositions()
{
	/*
	Updates Mouse  positions relative to window(Vector2i) 
	*/
	this->MousePosWindow = Mouse::getPosition(*this->window); 
	this->MousePosView = this->window->mapPixelToCoords(this->MousePosWindow);
}

void Game::spawnenemy()
{
	/*
	Spawn enemy and set their colour and positions 
	-Sets a random position 
	-Sets a Random Colour 
	-Adds enemy to  the vector

	*/
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		0.f
			);
	this->enemy.setFillColor(colours[rand()%3]);
	this->enemies.push_back(this->enemy);


}
void Game::updateenemies()
{	
	//Updating the timer for enemy Spawning
	if (this->enemies.size() < this->maxEnemies)
	{
		bool deleted = false;
		if (this->EnemySpawnTimer >= this->EnemySpawnTimerMax)
		{
			this->spawnenemy();
			this->EnemySpawnTimer = 0.f;
		}
		else {
			this->EnemySpawnTimer += 1.f;
		}
	}
	for (int i = 0; i < this->enemies.size(); i++)
	{
		bool deleted = false;
		this->enemies[i].move(0.f, 10.f);
		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);
			this->health -= 5;
		}
	}
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (this->mouseHeld == false) {
				this->mouseHeld = true;
				bool deleted = false;

				for (size_t i = 0; i < this->enemies.size(); i++)
				{
					if (deleted == true)break;
					
					if (this->enemies[i].getGlobalBounds().contains(this->MousePosView))
					{
						deleted = true;
						this->enemies.erase(this->enemies.begin() + i);
						this->points += 10;
						std::cout << health << '\n';
					}
				}
			}
			else {
				mouseHeld = false;
			}

		}
}
void Game::update()
{
	this->UpdateEvents();//pollEvent
	this->updateMousePositions();
	this->updateenemies();
}

void Game::renderenemies()
{
	//Rendering the enemies

	for (auto& e : this->enemies)
	{
		this->window->draw(e); 
	}
}



void Game::render()
{
	/*
	@  return void
	* Clear old frame
	* render new objects
	* Display  frame in window
	Render the game objects
	*/



	this->window->clear(Color::Red);

	//Draw game objects

	this->renderenemies();


	this->window->display();
}
