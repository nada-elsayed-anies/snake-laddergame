#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include <time.h>
#include <SFML/Audio.hpp>
#include<string>
#include<cstdlib>
#include<sstream>
#pragma warning(disable : 4996)

using namespace sf;
using namespace std;


struct player
{
	string name;
	int score = 0;
}players[14];

void minue_window(Font font,RenderWindow& window, player players[]);
void play_window(Font font, RenderWindow& window,  player players[]);
void producers_window(Font font, RenderWindow& window, player players[]);
void score_fn(RenderWindow& window, player players[] , int &turn , int number_of_players
	, int  f_s_h[5], int f_s_t[5], int f_l_u[5], int f_l_d[5] , Sprite  character[8]
	,bool& winner ,int& first_player , int&dice_score , int&first_player_index);
void snake_ladder(int  f_s_h[5], int f_s_t[5], int f_l_u[5], int f_l_d[5]);


int main()
{
	RenderWindow window(VideoMode(1026,669), "snake&ladder");

	Font font;
	font.loadFromFile("games.ttf");
	
	
	minue_window(font,window,players );
}
void minue_window(Font font, RenderWindow& window , player players[] )
{
	SoundBuffer buffer;
	buffer.loadFromFile("sound.wav");
	Sound click_sound;
	click_sound.setBuffer(buffer);

	int selectedItemIndex = 0;
	Text menu[3];
	menu[0].setFont(font);
	menu[0].setColor(Color::Yellow);
	menu[0].setString("Play");
	menu[0].setCharacterSize(45);
	menu[0].setPosition(Vector2f((window.getSize().x / 3) + 250, window.getSize().y / 4 * 2));

	menu[1].setFont(font);
	menu[1].setColor(Color::Black);
	menu[1].setString("producers");
	menu[1].setCharacterSize(45);
	menu[1].setPosition(Vector2f((window.getSize().x / 3) + 100, window.getSize().y / 4 * 2.5));

	menu[2].setFont(font);
	menu[2].setColor(sf::Color::Black);
	menu[2].setString("Exit");
	menu[2].setCharacterSize(45);
	menu[2].setPosition(Vector2f((window.getSize().x / 3)+30, window.getSize().y / 4 * 3));

	srand(time(NULL));
	Texture texture;
	texture.setRepeated(true);
	texture.setSmooth(true);
	texture.loadFromFile("background.png");
	Sprite m_background;
	m_background.setTexture(texture);

	Music music;
	music.openFromFile("music.ogg");
	music.play();
	music.setLoop(true);
	music.setVolume(50);

	Texture texture1;
	Texture texture2;
	texture1.loadFromFile("sound_off.png ");
	texture2.loadFromFile("sound_on.png ");
	
	Sprite sound_off;
	Sprite sound_on;
	sound_off.setTexture(texture1);
	sound_on.setTexture(texture2);
	sound_off.setScale(Vector2f(0.09, 0.09));
	sound_off.setPosition(Vector2f(20, 20));
	sound_on.setScale(Vector2f(0.09, 0.09));
	sound_on.setPosition(Vector2f(window.getSize().x-70, 20));

	Texture pluse;
	pluse.loadFromFile("sound_change.png");
	Sprite sound_up;
	sound_up.setTexture(pluse);
	sound_up.setPosition(Vector2f(20,window.getSize().y-110));
	sound_up.setScale(Vector2f(0.2, 0.2));
	
	Text right;
	right.setFont(font);
	right.setColor(Color::Red);
	right.setString("right");
	right.setCharacterSize(32);
	right.setPosition(Vector2f(window.getSize().x - 110, 70));

	Text left;
	left.setFont(font);
	left.setColor(Color::White);
	left.setString("left");
	left.setCharacterSize(32);
	left.setPosition(Vector2f(20, 70));

	while (window.isOpen())
	{
		Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::KeyReleased:
				switch (event.key.code)
				{
				case Keyboard::Up:
					if (selectedItemIndex - 1 >= 0)
					{
						menu[selectedItemIndex].setColor(Color::Black);
						selectedItemIndex--;
						menu[selectedItemIndex].setColor(Color::Yellow);
					}
					click_sound.play();
					break;
				case Keyboard::Down:
					if (selectedItemIndex + 1 < 3)
					{
						menu[selectedItemIndex].setColor(Color::Black);
						selectedItemIndex++;
						menu[selectedItemIndex].setColor(Color::Yellow);
					}
					click_sound.play();
					break;
				case Keyboard::Equal:
					music.setVolume(music.getVolume() + 10);
					break;
				case Keyboard::Subtract:
					music.setVolume(music.getVolume() - 10);
					break;
				case Keyboard::Right:
					right.setColor(Color::Red);
					left.setColor(Color::White);
					music.play();
					music.setLoop(true);
					break;
				case Keyboard::Left:
					left.setColor(Color::Red);
					right.setColor(Color::White);
					music.stop();
					break;
				case Keyboard::Enter:
					switch (selectedItemIndex)
					{
					case 0:
						click_sound.play();
						music.stop();
						play_window(font, window,players);
						break;
					case 1:
						producers_window(font, window, players);
						click_sound.play();
						break;
					case 2:
						window.close();
						break;
					}
					break;
				}
				break;
			case Event::Closed:
				window.close();
				break;
			}
		}
		window.clear();
		window.draw(m_background);
		for (int i = 0; i < 3; i++)
		{
			window.draw(menu[i]);
		}
		window.draw(sound_off);
		window.draw(sound_on);
		window.draw(sound_up);
		window.draw(left);
		window.draw(right);
		window.display();
	}
}

void play_window(Font font , RenderWindow& window , player players[] ) {
	int number_of_players;
	cin >> number_of_players;
	if (number_of_players <= 1) 
	{
		cout << "                error!!! number of players must be 2 or more" << endl;
		cin >> number_of_players;
	}
	for (int i = 0; i < number_of_players; i++) 
	{
		cout << "enter the name of player " << i + 1 << " : ";
		cin >> players[i].name;
	}
	srand(time(NULL));

	Texture play_b;
	play_b.loadFromFile("play background.png");
	Sprite play_background;
	play_background.setTexture(play_b);

	int  f_s_h[5], f_s_t[5], f_l_u[5], f_l_d[5];
	snake_ladder( f_s_h,  f_s_t,  f_l_u,  f_l_d);

	Texture escape;
	escape.loadFromFile("icon.png");
	Sprite escape_arrow;
	escape_arrow.setTexture(escape);
	escape_arrow.setPosition(Vector2f(20, window.getSize().y - 70));
	escape_arrow.setScale(Vector2f(0.3, 0.3));

	int x=0, y=0;
	Texture characters;
	characters.loadFromFile("players.png");
	Sprite character[16];
	Vector2u character_size = characters.getSize();
	character_size.x /= 4;
	character_size.y /= 4;
	for (int i = 0; i < number_of_players; i++) 
	{	
		character[i].setTexture(characters);
		character[i].setTextureRect(IntRect(character_size.x*x, character_size.y*y, character_size.x, character_size.y));
		character[i].setPosition(20, 470);
		if (i < 3) 
			x++;
		if (i >= 3 && i<7)
		{
			if (i == 3)
			{
				y++;
				x++;
			}
			x--;
		}
		if (i >= 7 && i < 11)
		{
			if (i == 7)
			{
				y++;
				x--;
			}
			x++;
		}
		if (i >= 11 && i < 15)
		{
			if (i == 11)
			{
				y++;
				x++;
			}
			x--;
		}

	}

	Text dice ;
	dice.setFont(font);
	dice.setColor(Color::White);
	dice.setString("press enter to roll dice");
	dice.setCharacterSize(32);
	dice.setPosition(sf::Vector2f((window.getSize().x - 450), window.getSize().y - 150));

	Texture board_t;
	Sprite board[10][10];
	int x_board = 20, y_board = 20, line;
	int x_nums = 30, y_nums = 40;
	Text numbers[10][10];
	board_t.loadFromFile("board.png");
	int n[100];
	int num = 100;
	ostringstream nums[100];
	for (int i = 0; i < 100; i++)
	{
		n[i] = num;
		num--;
		nums[i] << n[i];
	}
	int n_a = 0;
	for (int a = 0; a < 10; a++)
	{
		line = a + 1;
		for (int b = 0; b < 10; b++)
		{
			numbers[a][b].setFont(font);
			numbers[a][b].setString(nums[n_a].str());
			numbers[a][b].setColor(Color::Black);
			numbers[a][b].setPosition(x_nums, y_nums);
			numbers[a][b].setCharacterSize(25);
			n_a++;
			if (line % 2 != 0)
			{
				if (x_nums == 480)
					break;
				x_nums += 50;
			}
			else
			{
				if (x_nums == 30)
					break;
				x_nums -= 50;
			}
		}
		y_nums += 50;
	}
	for (int i = 0; i < 10; i++)
	{
		line = i + 1;
		for (int j = 0; j < 10; j++)
		{
			board[i][j].setTexture(board_t);
			board[i][j].setPosition(x_board, y_board);
			if (line % 2 != 0)
			{
				if (x_board == 470)
					break;
				x_board += 50;
			}
			else
			{
				if (x_board == 20)
					break;
				x_board -= 50;
			}
		}
		y_board += 50;
	}

	Texture sn[5];
	if (!sn[0].loadFromFile("purple_snake.png"));
	if (!sn[1].loadFromFile("yellow_snake.png"));
	if (!sn[2].loadFromFile("blue_snake.png"));
	if (!sn[3].loadFromFile("red_snake.png"));
	if (!sn[4].loadFromFile("green_snake.png"));
	Sprite snakes_h[5];
	int x_sn_header = 500, y_sn_header = 230;
	int line_sn_h = 1, count_sn_h = 0;
	int sn_sprite_array = 0;
	for (int initial = 51; initial <= 99; initial++)
	{
		count_sn_h++;
		for (int s_h = 0; s_h < 5; s_h++)
		{
			if (initial == f_s_h[s_h])
			{
				snakes_h[sn_sprite_array].setTexture(sn[s_h]);
				snakes_h[sn_sprite_array].setPosition(x_sn_header, y_sn_header);
				sn_sprite_array++;
			}
		}

		if (line_sn_h % 2 != 0)
		{
			if (x_sn_header == 550)
				x_sn_header = 500;
			x_sn_header -= 50;
		}
		else if (line_sn_h % 2 == 0)
		{
			if (x_sn_header == 0)
				x_sn_header = 50;
			x_sn_header += 50;
		}
		if (count_sn_h == 10)
		{
			line_sn_h = line_sn_h + 1;
			count_sn_h = 0;
			y_sn_header -= 50;
		}
	}

	Sprite snakes_t[5];
	int x_sn_tail = 50, y_sn_tail = 480;
	int line_sn_t = 1, count_sn_t = 0;
	sn_sprite_array = 0;
	for (int initial = 1; initial <= 50; initial++)
	{
		count_sn_t++;
		for (int s_t = 0; s_t < 5; s_t++)
		{
			if (initial == f_s_t[s_t])
			{
				snakes_t[sn_sprite_array].setTexture(sn[s_t]);
				snakes_t[sn_sprite_array].setPosition(x_sn_tail, y_sn_tail);
				sn_sprite_array++;
			}
		}
		if (line_sn_t % 2 != 0)
		{
			if (x_sn_tail == 0)
				x_sn_tail = 50;
			x_sn_tail += 50;
		}
		else if (line_sn_t % 2 == 0)
		{
			if (x_sn_tail == 550)
				x_sn_tail = 500;
			x_sn_tail -= 50;
		}
		if (count_sn_t == 10)
		{
			line_sn_t = line_sn_t + 1;
			count_sn_t = 0;
			y_sn_tail -= 50;
		}
	}

	Texture ladder[5];
	if (!ladder[0].loadFromFile("purple_ladder.png"));
	if (!ladder[1].loadFromFile("yellow_ladder.png"));
	if (!ladder[2].loadFromFile("blue_ladder.png"));
	if (!ladder[3].loadFromFile("red_ladder.png"));
	if (!ladder[4].loadFromFile("green_ladder.png"));
	Sprite ladder_h[5];
	int x_ld_header = 500, y_ld_header = 230;
	int line_ld_h = 1, count_ld_h = 0;
	int ld_sprite_array = 0;
	for (int initial = 51; initial <= 100; initial++)
	{
		count_ld_h++;
		for (int l_h = 0; l_h < 5; l_h++)
		{
			if (initial == f_l_u[l_h])
			{
				ladder_h[ld_sprite_array].setTexture(ladder[l_h]);
				ladder_h[ld_sprite_array].setPosition(x_ld_header, y_ld_header);
				ld_sprite_array++;
			}
		}
		if (line_ld_h % 2 != 0)
		{

			x_ld_header -= 50;
		}
		else if (line_ld_h % 2 == 0)
		{

			x_ld_header += 50;
		}
		if (count_ld_h == 10)
		{
			line_ld_h = line_ld_h + 1;
			count_ld_h = 0;
			y_ld_header -= 50;
			if (x_ld_header == 550)
				x_ld_header = 500;
			if (x_ld_header == 0)
				x_ld_header = 50;
		}
	}

	Sprite ladder_t[5];
	int x_ld_tail = 50, y_ld_tail = 480;
	int line_ld_t = 1, count_ld_t = 0;
	ld_sprite_array = 0;
	for (int initial = 1; initial <= 50; initial++)
	{
		count_ld_t++;
		for (int l_t = 0; l_t < 5; l_t++)
		{
			if (initial == f_l_d[l_t])
			{
				ladder_t[ld_sprite_array].setTexture(ladder[l_t]);
				ladder_t[ld_sprite_array].setPosition(x_ld_tail, y_ld_tail);
				ld_sprite_array++;
			}
		}

		if (line_ld_t % 2 != 0)
		{

			x_ld_tail += 50;
		}
		else if (line_ld_t % 2 == 0)
		{
			x_ld_tail -= 50;
		}
		if (count_ld_t == 10)
		{
			line_ld_t = line_ld_t + 1;
			count_ld_t = 0;
			y_ld_tail -= 50;
			if (x_ld_tail == 0)
				x_ld_tail = 50;
			if (x_ld_tail == 550)
				x_ld_tail = 500;
		}

	}
	Text win;
	win.setFont(font);
	win.setColor(Color::Yellow);
	win.setString("we got a winner!!!");
	win.setCharacterSize(80);
	win.setPosition(Vector2f(200, window.getSize().y/2));

	SoundBuffer dice_;
	dice_.loadFromFile("dice.wav");
	Sound dice_audio;
	dice_audio.setBuffer(dice_);

	SoundBuffer snake;
	snake.loadFromFile("losing.wav");
	Sound snake_sound ;
	snake_sound.setBuffer(dice_);

	int first_player = 0;
	bool winner = false;
	int turn = 1;
	bool got_snake = false;
	int dice_score;
	int first_player_index=0;

	Texture dice_n;
	dice_n.loadFromFile("dice_number.png");
	Sprite dice_number;
	Vector2u dice_size = dice_n.getSize();
	dice_size.x /=2;
	dice_size.y /= 3;
	int x_ofdice = 0 ,y_ofdice=0;
		dice_number.setTexture(dice_n);
		dice_number.setTextureRect(IntRect(dice_size.x*x_ofdice, dice_size.y*y_ofdice, dice_size.x, dice_size.y));
		dice_number.setPosition(sf::Vector2f((window.getSize().x - 260), window.getSize().y - 110));
	
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;
			case Event::KeyReleased:
				switch (event.key.code)
				{
				case Keyboard::Enter:
					if (winner == false) 
					{
	                    dice_score = rand() % 6 + 1;
						dice_audio.play();
						if (dice_score > 3)
						{
							x_ofdice++;
							y_ofdice = dice_score - 3;
						}
						else
						{
							y_ofdice = dice_score;
						}
						dice_number.setTextureRect(IntRect(dice_size.x*x_ofdice, dice_size.y*(y_ofdice-1), dice_size.x, dice_size.y));
						x_ofdice = 0;
						score_fn(window, players, turn, number_of_players,
							f_s_h, f_s_t, f_l_u, f_l_d, character, winner, first_player, dice_score , first_player_index);
						
					}
					break;
				case Keyboard::Escape:
					for (int i = 0; i < number_of_players; i++)
						players[i].score = 0;
					minue_window(font, window, players);


				}
			}
			window.clear();
			window.draw( play_background);
			window.draw(dice);
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					window.draw(board[i][j]);
					window.draw(numbers[i][j]);
				}
			}
			for (int i = 0; i < 5; i++) 
			{
				window.draw(snakes_h[i]);
				window.draw(ladder_t[i]);
				window.draw(ladder_h[i]);
				window.draw(snakes_t[i]);
			}
			for (int i = 0; i < number_of_players; i++) 
				window.draw(character[i]);
			window.draw(escape_arrow);
			window.draw(dice_number);
			if (winner == true) {
				window.clear();
				window.draw(win);
			}
			window.display();
		}
	}

}

void score_fn(RenderWindow& window, player players[],int&turn , int number_of_players 
	, int  f_s_h[5], int f_s_t[5], int f_l_u[5],int f_l_d[5], Sprite  character[8],
	bool&winner  ,int& first_player , int&dice_score , int&first_player_index)
{

	srand(time(NULL));
	int y_axis, y_axis_d;
			players[turn-1].score += dice_score;

			cout << "     _____________________________________________________" << endl;
			for (int i = 0; i < number_of_players; i++) {
				cout << "     | the score of " << players[i].name << " is " << players[i].score << "                                 | " << endl;
			}
			cout << "     |          player " << turn  << " got " << dice_score << " from dice " << "                  |" << endl;

			for (int i = 0; i < 5; i++) 
			{
				if (players[turn - 1].score == f_s_h[i])
				{
					players[turn - 1].score = f_s_t[i];
					
					cout << "     | oops!! player " <<turn << " got a snake to " << players[turn - 1].score <<"            |" << endl;
				}
				if (players[turn - 1].score == f_l_d[i])
				{
					players[turn - 1].score = f_l_u[i];
					
					cout << "     | woow player " << turn << " got a leader to " << players[turn - 1].score << "            |"<< endl;
				}
			}
			if (players[turn - 1].score > first_player)
			{
				first_player = players[turn-1].score;
				first_player_index = turn - 1;
			}
			cout << "     |       and " << players[first_player_index].name << " is the first player with score of "
				<< players[first_player_index].score << "     |" << endl;
			cout << "     ______________________________________________________" << endl;
			y_axis = players[turn - 1].score;
			y_axis_d = y_axis % 10;
			y_axis -= y_axis_d;
			y_axis /= 10;
			if (y_axis % 2 == 0)
			{
				if (y_axis_d == 1)
					character[turn-1].setPosition(20 , 470 - 50 * y_axis);
				else if (y_axis_d == 0)
				{
					character[turn].setPosition(20, 470 - 50 * (y_axis - 1));
				}
				else {
					y_axis_d--;
					character[turn-1].setPosition(20 + y_axis_d * 50, 470 - 50 * y_axis);
					y_axis_d++;

				}
			}
			else if (y_axis % 2 != 0)
			{
				if (y_axis_d == 1)
					character[turn - 1].setPosition(470, 470 - 50 * y_axis);
				else if (y_axis_d == 0) 
					character[turn - 1].setPosition(470, 470 - 50 * (y_axis - 1));
				else 
					character[turn - 1].setPosition(20 + (10 - y_axis_d) * 50, 470 - 50 * y_axis);
				
			}
			if (players[turn-1].score >= 100) 
			{
				winner = true;
				cout << endl;
				cout << "         player " << turn << " is the winner !!! " << endl;
			}
			turn++;
					
		if (turn == number_of_players+1)
			turn -= number_of_players;

}
void snake_ladder(int  f_s_h[5], int f_s_t[5], int f_l_u[5], int f_l_d[5])
{
	const int size = 50;
	int s_h[size], s_t[size], l_u[size], l_d[size];
	bool check1 = true, check2 = true, check3 = true, check4 = true;
	int count = 0;
	int m = 0;
	for (int i = 0; i < size; i++)
	{
		s_h[i] = 51 + rand() % 49; 
		s_t[i] = 1 + rand() % 50; 
		l_u[i] = 51 + rand() % 50; 
		l_d[i] = 2 + rand() % 49;
	}
	for (int i = 0; i < size; i++)
	{
		if (s_h[i] % 2 == 0)
		{
			for (int j = size - 1; j > i; j--)
			{
				if (s_h[i] == s_h[j])
				{
					check1 = true;
					break;
				}
				else
					check1 = false;
			}
			if (!check1)
			{
				if (count == 5)
					break;
				f_s_h[m] = s_h[i];
				m++;
				count++;
			}
		}
	} 
	cout << endl << "snakes header : " ;
	for (int i = 0; i < 5; i++) {
		cout << f_s_h[i] << " " ;
	}
	count = 0;
	m = 0;

	for (int i = 0; i < size; i++)
	{
		if (l_u[i] % 2 != 0)
		{
			for (int j = size - 1; j > i; j--)
			{
				if (l_u[i] == l_u[j])
				{
					check2 = true;
					break;
				}
				else
					check2 = false;

			}
			if (!check2)
			{
				if (count == 5)
					break;
				f_l_u[m] = l_u[i];
				m++;
				count++;
			}
		}
	}
	cout << endl << "ladders up : ";
	for (int i = 0; i < 5; i++) {
		cout << f_l_u[i] << " " ;
	}
	count = 0;
	m = 0;
	for (int i = 0; i < size; i++)
	{
		if (s_t[i] % 2 == 0)
		{
			for (int j = size - 1; j > i; j--)
			{
				if (s_t[i] == s_t[j])
				{
					check3 = true;
					break;
				}
				else
					check3 = false;
			}
			if (!check3)
			{
				if (count == 5)
					break;
				f_s_t[m] = s_t[i];
				m++;
				count++;
			}
		}
	}
	cout << endl<< "snakes tail : ";
	for (int i = 0; i < 5; i++) {
		cout << f_s_t[i] << " " ;
	}
	count = 0;
	m = 0;
	for (int i = 0; i < size; i++)
	{
		if (l_d[i] % 2 != 0)
		{
			for (int j = size - 1; j > i; j--)
			{
				if (l_d[i] == l_d[j])
				{
					check4 = true;
					break;
				}
				else
					check4 = false;
			}
			if (!check4)
			{
				if (count == 5)
					break;
				f_l_d[m] = l_d[i];
				m++;
				count++;
			}
		}
	}
	cout << endl << "ladders down " ;
	for (int i = 0; i < 5; i++) {
		cout << f_l_d[i] << " " ;
	}
	cout << endl;
}

void producers_window(Font font, RenderWindow& window, player players[])
{
	Texture producer;
	producer.loadFromFile("produce_bg.png");
	Sprite pr;
	pr.setTexture(producer);

	while (window.isOpen())
	{
		Event event;

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::KeyReleased:
				if (event.key.code == Keyboard::Escape)
					minue_window(font, window, players);
					break;
			case Event::Closed:
				window.close();
				break;
			}
		}
		window.clear();
		window.draw(pr);
		window.display();
	}


}