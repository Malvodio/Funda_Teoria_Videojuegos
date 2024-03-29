#include "Zombie.h"
#include "Human.h"


Zombie::Zombie()
{
}

void Zombie::init(float speed, glm::vec2 position) {
	_speed = speed;
	_position = position;
	color.set(0, 255, 0, 255);
}

void Zombie::update(const std::vector<std::string>& levelData,
	std::vector<Human*>& humans,
	std::vector<Zombie*>& zombies) {
	
	collideWithLevel(levelData);

	Human* closeHuman = getNearestHuman(humans);
	if (closeHuman != nullptr) {
		glm::vec2 direction = glm::normalize(
			closeHuman->getPosition() - _position);
		_position += direction*_speed;
	}
	for (size_t i = 0; i < humans.size(); i++) {
		if (collideWithAgent(humans[i])) {
			glm::vec2 humanPosition = humans[i]->getPosition();
			humans.erase(humans.begin() + i);
			zombies.push_back(new Zombie());
			zombies.back()->init(0.3f, humanPosition);
		}
	}

}

Human* Zombie::getNearestHuman(std::vector<Human*>& humans) {
	Human* closestHuman = nullptr;
	float smallestDistance = 88888888888.0f;
	for (size_t i = 0; i < humans.size(); i++)
	{
		glm::vec2 dist = humans[i]->getPosition() - _position;
		float distance = glm::length(dist);
		if (distance < smallestDistance) {
			smallestDistance = distance;
			closestHuman = humans[i];
		}
		
	}
	return closestHuman;

}


Zombie::~Zombie()
{
}
