#include <Book/MenuState.hpp>
#include <Book/Button.hpp>
#include <Book/Utility.hpp>
#include <Book/ResourceHolder.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


MenuState::MenuState(StateStack& stack, Context context)
: State(stack, context)
, mGUIContainer()
{
	sf::Texture& texture = context.textures->get(Textures::TitleScreen);
	mBackgroundSprite.setTexture(texture);

	auto playLevelOne = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	playLevelOne->setPosition(100, 300);
	playLevelOne->setText("Play Level 1 (Easy)");
	playLevelOne->setCallback([this] ()
	{
		requestStackPop();
		requestStackPush(States::EasyGame);
	});

	auto playLevelTwo = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	playLevelTwo->setPosition(100, 350);
	playLevelTwo->setText("Play Level 2 (Medium)");
	playLevelTwo->setCallback([this]()
	{
		requestStackPop();
		requestStackPush(States::MediumGame);
	});

	auto playLevelThree = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	playLevelThree->setPosition(100, 400);
	playLevelThree->setText("Play Level 3 (Hard)");
	playLevelThree->setCallback([this]()
	{
		requestStackPop();
		requestStackPush(States::HardGame);
	});

	auto settingsButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	settingsButton->setPosition(100, 450);
	settingsButton->setText("Settings");
	settingsButton->setCallback([this] ()
	{
		requestStackPush(States::Settings);
	});

	auto exitButton = std::make_shared<GUI::Button>(*context.fonts, *context.textures);
	exitButton->setPosition(100, 500);
	exitButton->setText("Exit Game");
	exitButton->setCallback([this] ()
	{
		requestStackPop();
	});

	mGUIContainer.pack(playLevelOne);
	mGUIContainer.pack(playLevelTwo);
	mGUIContainer.pack(playLevelThree);
	mGUIContainer.pack(settingsButton);
	mGUIContainer.pack(exitButton);
}

void MenuState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());

	window.draw(mBackgroundSprite);
	window.draw(mGUIContainer);
}

bool MenuState::update(sf::Time)
{
	return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
	mGUIContainer.handleEvent(event);
	return false;
}
