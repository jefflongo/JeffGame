#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#define _USE_MATH_DEFINES

#include <map>
#include <math.h>
#include "SFML/Graphics.hpp"

/*
GC CONTROLLER INPUT
X Axis     - Analog stick X   (-80 to 80)
Y Axis     - Analog stick Y   (-80 to 80)
V Axis     - C-stick (right)  (-50 to 50)
U Axis     - C-stick (down)   (-50 to 50)
Z Axis     - L Analog         (-100 to 60)
R Axis     - R Analog         (-100 to 60)
Button 0   - A
Button 1   - B
Button 2   - X
Button 3   - Y
Button 4   - Z
Button 5   - R Digital
Button 6   - L Digital
Button 7   - Start
Button 8   - D-pad up
Button 9   - D-pad left
Button 10  - D-pad down
Button 11  - D-pad right
*/

enum class StickName { CONTROL_STICK, C_STICK };
enum class ShoulderName { L, R };
enum class ButtonName { A, B, X, Y, Z, R, L, START, D_PAD_UP, D_PAD_LEFT, D_PAD_DOWN, D_PAD_RIGHT };
enum class CardinalDirections { Up, Down, Left, Right, None };

class Controller
{
public:
	typedef sf::Joystick::Axis Axis;

	Controller();
	Controller(unsigned int controllerId);

	void update();

	void mapStick(StickName name, Axis x, Axis y, float radius);
	void mapShoulder(ShoulderName name, Axis axis, float min, float max);
	void mapButton(ButtonName name, unsigned int id);

	sf::Vector2f getStickPosition(StickName name) const;
	sf::Vector2f getStickPositionPercentage(StickName name) const;
	int getStickAngle(StickName name) const;
	sf::Vector2f getFramesSinceDirectionChange(StickName name) const;
	float getShoulderPosition(ShoulderName name) const;
	float getShoulderPositionPercentage(ShoulderName name) const;

	bool buttonPressed(ButtonName name);
	bool cardinalDirectionChange(Axis axis, int frames);

private:
	struct Stick
	{
		Axis x, y;
		float radius;
		sf::Vector2f framesSinceChange;
		CardinalDirections horizontalDir, verticalDir;
	};

	struct Shoulder
	{
		Axis axis;
		float min, max;
	};

	struct Button
	{
		unsigned int id;
		bool held;
		//unsigned int framesHeld;
	};

	void checkStickDirections();
	void checkHeldButtons();

	unsigned int controllerId_;
	std::map<StickName, Stick> stickMap_;
	std::map<ButtonName, Button> buttonMap_;
	std::map<ShoulderName, Shoulder> shoulderMap_;
};

#endif // CONTROLLER_H_