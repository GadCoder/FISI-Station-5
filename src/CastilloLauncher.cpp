#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include "CastilloLauncher.h"

using namespace sf;

//WINDOW DIMENSIONS//
const int WIDTH = 800, HEIGHT = 600;

struct Images
{
	Texture bg, cloud1, cloud2, bg_over; //Background_Texture
	Texture hat, t1, t2, t3; //Player & enemy (Texture)
	Sprite spr_bg, spr_cloud1, spr_cloud2, spr_bg_over; //Background_Sprite
	Sprite spr_hat, players[2], enemy; //Player & enemy (Sprite)
	Font font;
	Text txt_points;

	void loadImages();
	void score();
	void position();
}image;

struct Position
{
	int x;
	int y;
}cloud1pos, cloud2pos, playerPos, hatPos, enemyPos;

struct Sounds
{
	SoundBuffer buffer;
	Music loseSound;
	Music gameMusic;
	Sound jumpSound;

	void loadSounds();
}sounds;

struct Player
{
	//Player variables
	//Step variables
	int index = 0;
	float step = 0.f;
	float stepSpeed = 0.4f;
	int changeCount = 5;

	//Jump variables
	int gravity = 7;
	bool isJumping = false;
	bool isBottom = true;
	int y_bottom;
	int hat_Y_bottom;

	//Enemy variables
	int enemyWidth = 0;
	int enemySpeed = 7;
	int enemy_Y_bottom;
	int enemy_X = WIDTH - 200;

	void steps();
	void jump();
}player;

struct Score
{
	bool gameLose = false;
	int points = 10;
	std::string str_score;

	void rule_of_the_game();
}score;

/// PROTOTYPE FUNCTIONS ///
void objectMove(Position&, int&, int&);
void initPos(Position&, int, int);
void replay();
void game_window(RenderWindow&);
void lose_window(RenderWindow&);
void windowEvents(RenderWindow&);

//Main
void CastilloLauncher::launchGame(int* p_score_ptr)
{
	//WINDOW VARIABLE
	RenderWindow window(VideoMode(WIDTH, HEIGHT), "Castillo Game");
	window.setFramerateLimit(60);

	//Loading images
	image.loadImages();
	image.score();

	//Loading sounds
	sounds.loadSounds();
	sounds.gameMusic.play();
	sounds.gameMusic.setLoop(true);

	//CLOUDS AND ENEMY SIZE
	int cloud1Width = image.cloud1.getSize().x;
	int cloud2Width = image.cloud2.getSize().x;
	int cloudSpeed = 1;

	//X_POSITIONS
	int cloud1_x = WIDTH - 700;
	int cloud2_x = WIDTH - 300;

	//Y_POSITIONS
	int cloud_y = HEIGHT - 400;
	player.y_bottom = HEIGHT - image.t1.getSize().y;
	player.hat_Y_bottom = player.y_bottom - image.hat.getSize().y;
	player.enemy_Y_bottom = HEIGHT - image.t3.getSize().y;


	//INITIAL POSITIONS X & Y
	initPos(cloud1pos, cloud1_x, cloud_y);
	initPos(cloud2pos, cloud2_x, cloud_y);
	initPos(playerPos, 50, player.y_bottom);
	initPos(hatPos, 26, player.hat_Y_bottom);
	initPos(enemyPos, player.enemy_X, player.enemy_Y_bottom);

	std::string highScore;

	//LOOP FOR WINDOW
	while (window.isOpen())
	{

		/// WINDOW EVENTS ///
		windowEvents(window);

		/// PLAYER JUMP ///
		player.jump();

		//Movement (player, enemy, objects)
		player.steps();
		objectMove(enemyPos, player.enemyWidth, player.enemySpeed);
		objectMove(cloud1pos, cloud1Width, cloudSpeed);
		objectMove(cloud2pos, cloud2Width, cloudSpeed);

		/// SCORE ///
		score.rule_of_the_game();

		/// REPLAY ///
		replay();

		// SETTING POSITIONS //
		image.position();

		/// DRAW WINDOW ///
		if (!score.gameLose)
		{
			game_window(window);
		}

		/// PLAYER INTERSECTS WITH ENEMY
		if (image.players[player.index].getGlobalBounds().intersects(image.enemy.getGlobalBounds()))
		{
			*p_score_ptr = score.points / 20;
			lose_window(window);
		}

	}
}

/// FUNCTIONS ///
/// LOADING IMAGES ///
void Images::loadImages()
{
	bg.loadFromFile("./content/Castillo/field.png");
	cloud1.loadFromFile("./content/Castillo/clouds1.png");
	cloud2.loadFromFile("./content/Castillo/clouds2.png");
	bg_over.loadFromFile("./content/Castillo/game_over.png");
	hat.loadFromFile("./content/Castillo/sombrero.png");
	t1.loadFromFile("./content/Castillo/castillo1.png");
	t2.loadFromFile("./content/Castillo/castillo2.png");
	t3.loadFromFile("./content/Castillo/cuysito.png");
	font.loadFromFile("./content/Fonts/Minecraftia-Regular.ttf");

	spr_bg.setTexture(bg);
	spr_cloud1.setTexture(cloud1);
	spr_cloud2.setTexture(cloud2);
	spr_bg_over.setTexture(bg_over);
	spr_hat.setTexture(hat);
	players[0].setTexture(t1);
	players[1].setTexture(t2);
	enemy.setTexture(t3);
}

void Images::score()
{
	txt_points.setFont(font);
	txt_points.setPosition(10, 25);
	txt_points.setCharacterSize(20);
	txt_points.setFillColor(Color::Yellow);
}

/// SOUNDS ///
void Sounds::loadSounds()
{
	if (!sounds.gameMusic.openFromFile("./content/Sounds/gameMusic.wav"))
	{
		std::cout << "Error, sound not found" << std::endl;
	}

	if (!sounds.loseSound.openFromFile("./content/Sounds/castilloo.ogg"))
	{
		std::cout << "Error, sound not found" << std::endl;
	}
	sounds.loseSound.setVolume(10.f);

	if (!sounds.buffer.loadFromFile("./content/Sounds/jump.wav"))
	{
		std::cout << "Error, sound not found" << std::endl;
	}

	sounds.jumpSound.setBuffer(buffer);
	sounds.gameMusic.setVolume(5.f);
	sounds.loseSound.setVolume(5.f);
	sounds.jumpSound.setVolume(10.f);
}

void initPos(Position& obj, int pos_x, int pos_y)
{
	obj.x = pos_x;
	obj.y = pos_y;
}

void Images::position()
{
	spr_cloud1.setPosition(cloud1pos.x, cloud1pos.y);
	spr_cloud2.setPosition(cloud2pos.x, cloud2pos.y);
	players[player.index].setPosition(playerPos.x, playerPos.y);
	spr_hat.setPosition(hatPos.x, hatPos.y);
	enemy.setPosition(enemyPos.x, enemyPos.y);
}

void Player::jump()
{
	if (Keyboard::isKeyPressed(Keyboard::Space) or Keyboard::isKeyPressed(Keyboard::Up))
	{
		if (player.isBottom && !player.isJumping)
		{
			//make jumping stage;
			player.isJumping = true;
			player.isBottom = false;
		}
	}

	//player jump(up and down)
	if (player.isJumping)
	{
		playerPos.y -= player.gravity;
		hatPos.y -= player.gravity;
	}
	else
	{
		playerPos.y += player.gravity;
		hatPos.y += player.gravity;
	}

	//player jump limit / player bottom limit
	if ((playerPos.y >= player.y_bottom) && (hatPos.y >= player.hat_Y_bottom))
	{
		playerPos.y = player.y_bottom;
		hatPos.y = player.hat_Y_bottom;
		player.isBottom = true;
	}
	if ((playerPos.y <= player.y_bottom - 160) && (hatPos.y <= player.hat_Y_bottom - 160))
	{
		player.isJumping = false;
	}
}

void objectMove(Position& obj, int& width, int& speed)
{
	if (obj.x <= -width)
	{
		obj.x = WIDTH;
	}
	else
	{
		obj.x -= speed;
	}
}

void Player::steps()
{
	step += stepSpeed;
	if (step > changeCount)
	{
		step -= changeCount;
		++index;
		if (index >= 2)
		{
			index = 0;
		}
	}
}

void Score::rule_of_the_game()
{
	if (!score.gameLose)
	{
		score.points++;
		//Score logic
		if (score.points > 1 && score.points % 10 == 0)
		{
			std::string score_aux = std::to_string(score.points / 20);
			score.str_score = "Points : " + score_aux;
			image.txt_points.setString(score.str_score);
		}

		//Difficulty limit
		if (score.points % 1000 == 0)
		{
			if ((player.enemySpeed < 15) && (player.gravity < 15))
			{
				player.enemySpeed++;
				player.gravity++;
				if (player.changeCount > 3)
				{
					player.changeCount--;
				}
			}
		}
	}
}

void replay()
{
	if (Keyboard::isKeyPressed(Keyboard::Enter))
	{
		if (score.gameLose)
		{
			//Restart values
			sounds.loseSound.stop();
			score.gameLose = false;
			score.points = 10;
			enemyPos.x = WIDTH - 200;
			player.enemySpeed = 7;
			player.gravity = 7;
		}
	}
}

void game_window(RenderWindow& window)
{
	window.clear(Color::White);
	window.draw(image.spr_bg);
	window.draw(image.txt_points);
	window.draw(image.spr_cloud1);
	window.draw(image.spr_cloud2);
	window.draw(image.players[player.index]);
	window.draw(image.spr_hat);
	window.draw(image.enemy);
	window.display();
}

void lose_window(RenderWindow& window)
{
	while (!score.gameLose)
	{
		score.gameLose = true;
		Text game_over, retry;

		sounds.gameMusic.stop();
		sounds.loseSound.play();

		game_over.setFont(image.font);
		game_over.setString("GAME OVER!!!!!!");
		game_over.setCharacterSize(40);
		game_over.setFillColor(Color::Red);
		game_over.setPosition(240, 280);

		retry.setFont(image.font);
		retry.setString("Pulsa  Enter para continuar \n\t\tPulsa  Esc para salir");
		retry.setCharacterSize(20);
		retry.setPosition(220, 540);

		window.clear();
		window.draw(image.spr_bg_over);
		window.draw(game_over);
		window.draw(retry);
		window.draw(image.txt_points);
		window.display();
	}
}

void windowEvents(RenderWindow& window)
{
	Event ev;
	while (window.pollEvent(ev))
	{
		if (ev.type == Event::Closed)
		{
			window.close();
		}
		if (ev.type == Event::KeyPressed)
		{
			if (ev.key.code == Keyboard::Space or ev.key.code == Keyboard::Up)
			{
				sounds.jumpSound.play();
			}
			if (ev.key.code == Keyboard::Escape)
			{
				exit(1);
			}
		}
	}
}
