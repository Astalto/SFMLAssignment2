#include <Book/TextNode.hpp>
#include <Book/Utility.hpp>

#include <SFML/Graphics/RenderTarget.hpp>

    
TextNode::TextNode(const FontHolder& fonts, const std::string& text)
{
	mText.setFont(fonts.get(Fonts::Main));
	mText.setCharacterSize(20);
	setString(text);
}

void TextNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mText, states);
}

void TextNode::setString(const std::string& text)
{
	mText.setString(text);
	centerOrigin(mText);
}

void TextNode::setColor(const sf::Color& newColor)
{
	mText.setColor(newColor);
}

void TextNode::setStyle(const sf::Text::Style& newStyle)
{
	mText.setStyle(newStyle);
}

void TextNode::setFont(sf::Font& newFont)
{
	mText.setFont(newFont);
}