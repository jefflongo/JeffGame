#ifndef STAGE_H_
#define STAGE_H_

#include <vector>
#include "SFML/Graphics.hpp"

class Stage
{
public:
	Stage();
	//Stage(string stageName)

	std::vector<sf::RectangleShape> getCollidableObjects() const;
	std::vector<sf::RectangleShape> getPermeableObjects() const;
	sf::RectangleShape getCollidableObject(unsigned int i) const;
	sf::RectangleShape getPermeableObject(unsigned int i) const;
	int groundCollision(const sf::RectangleShape& player, sf::Vector2f pos);
	int platformCollision(const sf::RectangleShape& player, sf::Vector2f pos);
	void render(sf::RenderWindow& window);

private:
	std::vector<sf::RectangleShape> collidableObjects_, permeableObjects_;
};
#endif // STAGE_H_