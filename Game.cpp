#include <iostream>

class Game
{
	private:
	Board board;
	LetterBag letter_bag;
	unsigned int num_players;
	std::unordered_map<char, Player*> players;
	
	static Game *instance;
	Game() {}

	public:
	static void getInstance()
	{
		if (instance == nullptr)
			instance = new Game();
		return instance;
	}

	void init()
	{
		while (true)
		{
			std::cout << "enter number of players: ";
			std::cin >> num_players;
			if (num_players >= 2 && num_players <= 4)
				break;
			std::cout << "there must be between 2 and 4 players\n";	
		}

		for (int i = 1; i <= num_players; i++)
		{
			Player *player = new Player();

			std::cout << "enter name: \n";
			std::cin >> player->name; 	

			while (true)
			{
				char letter;
				std::cout << "enter letter: \n";
				// if hashmap <<players>> has no entry with <<letter>>
				if (players[letter = getchar()] == nullptr)
				{
					// add new entry with key <<letter>> and value <<player>>
					players[letter] = player;	
					break;
				}
				std::cout << "someone already picked this letter\n";	
			}
		}

		// sort hashmap <<players>> by keys' alphabetical order
		std::sort(players.begin(), players.end());

		for (auto it = players.begin(); it <= players.end(); i++) 
		{
			auto player = it.second;
			std::cout << player->name + ", enter the letters representing the tiles you wish to choose: ";

			while (int i = 1; i <= 7)
				player->addTile(getchar());
		}

		board.draw();	
	}	

	void loop()
	{
		for (auto it = players.begin();; it++)
		{
			auto player = it.second;
			unsigned int tiles_played = 0;
			//player->playTile();
			//...	
			//loop for player->addTile(getchar());		
		}		
	}	
};	
