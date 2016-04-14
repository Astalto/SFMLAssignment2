#include <Book/GameOverState.hpp>
#include <Book/Utility.hpp>
#include <Book/ResourceHolder.hpp>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


GameOverState::GameOverState(StateStack& stack, Context context)
: State(stack, context)
, mGameOverText()
, mElapsedTime(sf::Time::Zero)
{
	sf::Font& font = context.fonts->get(Fonts::Main);
	sf::Vector2f windowSize(context.window->getSize());

	mGameOverText.setFont(font);
	if (context.player->getMissionStatus() == Player::MissionFailure)
	{
		mGameOverText.setString("Mission failed!");
		mPlayerFailed = true;
	}
	else
	{
		mGameOverText.setString("Mission successful!");
		mPlayerFailed = false;
	}

	mPrevMission = context.player->getPrevMission();

	mGameOverText.setCharacterSize(70);
	centerOrigin(mGameOverText);
	mGameOverText.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);
}

void GameOverState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	// Create dark, semitransparent background
	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(mGameOverText);
}

bool GameOverState::update(sf::Time dt)
{
	// Show state for 3 seconds, after return to menu
	mElapsedTime += dt;
	if (mElapsedTime > sf::seconds(3))
	{
		if (mPlayerFailed)
		{
			requestStateClear();
			requestStackPush(States::Menu);
		}
		else
		{
			switch (mPrevMission)
			{
			case Player::Mission1:
				requestStateClear();
				requestStackPush(States::MediumGame);
				break;
			case Player::Mission2:
				requestStateClear();
				requestStackPush(States::HardGame);
				break;
			case Player::Mission3:
				requestStateClear();
				requestStackPush(States::Menu);
			default: // Fail-safe
				requestStateClear();
				requestStackPush(States::Menu);
			}
		}
	}
	return false;
}

bool GameOverState::handleEvent(const sf::Event&)
{
	return false;
}
