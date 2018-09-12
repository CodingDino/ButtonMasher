// Included Libraries
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>


// entry point for the program
int main()
{
	// --------------------------------------
	// Game Setup
	// --------------------------------------

	// Make a variable called gameWindow of type RenderWindow
	sf::RenderWindow gameWindow;
	gameWindow.create(sf::VideoMode::getDesktopMode(), "Button Masher", 
		sf::Style::Titlebar | sf::Style::Close);


	// Create Button Sprite
	sf::Texture buttonTexture;
	buttonTexture.loadFromFile("graphics/button.png");

	sf::Sprite buttonSprite;
	buttonSprite.setTexture(buttonTexture);

	// Center the sprite on the screen
	buttonSprite.setPosition(
		gameWindow.getSize().x / 2 - buttonTexture.getSize().x / 2,
		gameWindow.getSize().y / 2 - buttonTexture.getSize().y / 2
	);


	// Create Music
	sf::Music gameMusic;
	gameMusic.openFromFile("audio/music.ogg");
	//gameMusic.play();


	// Create Font
	sf::Font gameFont;
	gameFont.loadFromFile("fonts/mainFont.ttf");

	// Create Title
	sf::Text titleText;
	titleText.setFont(gameFont);
	titleText.setString("Button Masher!");

	titleText.setCharacterSize(100);
	titleText.setFillColor(sf::Color::Cyan);
	titleText.setStyle(sf::Text::Bold | sf::Text::Italic);

	titleText.setPosition(gameWindow.getSize().x / 2 
		- titleText.getLocalBounds().width / 2, 
		30);

	// Author Text
	sf::Text authorText;
	authorText.setFont(gameFont);
	authorText.setString("by Sarah Herzog");
	authorText.setCharacterSize(16);
	authorText.setFillColor(sf::Color::Magenta);
	authorText.setStyle(sf::Text::Italic);
	authorText.setPosition(gameWindow.getSize().x / 2 
		- authorText.getLocalBounds().width / 2, 
		150);

	// Prompt Text
	sf::Text promptText;
	promptText.setFont(gameFont);
	promptText.setString("Click the button to start the game!");
	promptText.setCharacterSize(16);
	promptText.setFillColor(sf::Color::White);
	promptText.setStyle(sf::Text::Italic);
	promptText.setPosition(gameWindow.getSize().x / 2
		- promptText.getLocalBounds().width / 2,
		200);

	// Score
	int score = 0;

	// Score Text
	sf::Text scoreText;
	scoreText.setFont(gameFont);
	scoreText.setString("Score: " + std::to_string(score));
	scoreText.setCharacterSize(16);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(30, 30);

	// Timer Text
	sf::Text timerText;
	timerText.setFont(gameFont);
	timerText.setString("Time Remaining: 0");
	timerText.setCharacterSize(16);
	timerText.setFillColor(sf::Color::White);
	timerText.setPosition(gameWindow.getSize().x - timerText.getLocalBounds().width -30, 
		30);

	// Timer functionality
	sf::Time timeLimit = sf::seconds(10.0f);
	sf::Time timeRemaining = timeLimit;
	sf::Time deadTimeLimit = sf::seconds(3.0f);
	sf::Time deadTimeRemaining = sf::seconds(0.0f);
	sf::Clock gameClock;

	// Click sound effect
	sf::SoundBuffer clickBuffer;
	clickBuffer.loadFromFile("audio/buttonclick.ogg");
	sf::Sound clickSound;
	clickSound.setBuffer(clickBuffer);

	// Game over sound effect
	sf::SoundBuffer gameOverBuffer;
	gameOverBuffer.loadFromFile("audio/gameover.ogg");
	sf::Sound gameOverSound;
	gameOverSound.setBuffer(gameOverBuffer);

	// Game State
	bool playing = false;

	// --------------------------------------
	// Game Loop
	// --------------------------------------
	// Runs every frame until the game window is closed
	while (gameWindow.isOpen())
	{

		// Check for input
		sf::Event gameEvent;
		while (gameWindow.pollEvent(gameEvent))
		{
			// Process events
			// Check if the event is a mouse button pressed event
			if (gameEvent.type == sf::Event::MouseButtonPressed)
			{
				if (buttonSprite.getGlobalBounds().contains(gameEvent.mouseButton.x, gameEvent.mouseButton.y))
				{
					// We clicked the button!!!!

					// Are we playing?
					if (playing == true)
					{
						// yes - increase score!
						score = score + 1;
					}
					else if (deadTimeRemaining.asSeconds() <= 0.0f)
					{
						// no - start playing now!
						playing = true;

						// reset the game data
						score = 0;
						timeRemaining = timeLimit; 

						promptText.setString("Click the button as fast as you can!!!!!");
					}

					// play the click sound
					clickSound.play();
				}
				else
				{
					// play bad click sound here
				}
			}

			// Check if the event is the closed event
			if (gameEvent.type == sf::Event::Closed)
			{
				// Close the game window
				gameWindow.close();
			}
		}

		// Update game state
		sf::Time frameTime = gameClock.restart();

		if (playing == true)
		{
			timeRemaining = timeRemaining - frameTime;

			if (timeRemaining.asSeconds() <= 0.0f)
			{
				timeRemaining = sf::seconds(0.0f);
				playing = false;
				promptText.setString("Your final score was " + std::to_string(score) + "!");
				gameOverSound.play();
				deadTimeRemaining = deadTimeLimit;
			}
		}
		else
		{
			deadTimeRemaining = deadTimeRemaining - frameTime;

			if (deadTimeRemaining.asSeconds() <= 0)
			{
				promptText.setString("Click the button to start a new game!");
			}
		}


		// update our text displays based on data
		timerText.setString("Time Remaining: " + std::to_string((int)std::ceilf(timeRemaining.asSeconds())));
		scoreText.setString("Score: " + std::to_string(score));

		// Draw graphics
		// Clear the window to a single colour
		gameWindow.clear(sf::Color::Black);

		// Draw everything
		gameWindow.draw(buttonSprite);
		gameWindow.draw(titleText);
		gameWindow.draw(authorText);
		gameWindow.draw(scoreText);
		gameWindow.draw(timerText);
		gameWindow.draw(promptText);

		// Display the window contents on the screen
		gameWindow.display();

	}

	// exit point for the program
	return 0;
}