#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#define _USE_MATH_DEFINES

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

struct Button
{
	unsigned int id;
	bool held;
	//unsigned int framesHeld;
};

struct Controls
{
	float ANALOG_STICK_RADIUS, C_STICK_RADIUS, SHOULDER_MIN, SHOULDER_MAX;
	Button A, B, X, Y, Z, R, L, START, D_PAD_UP, D_PAD_LEFT, D_PAD_DOWN, D_PAD_RIGHT;
};

class Controller
{
public:
	typedef sf::Joystick::Axis Axis;

	Controller();
	Controller(unsigned int controllerId, Controls controls);

	Controls* getControls(); // hopefully find a way to get rid of this
	void update();
	float getAxisPosition(Axis axis) const;
	bool axisPercentageGreaterThan(Axis axis, float percent);
	bool axisPercentageLessThan(Axis axis, float percent);
	bool axisPercentageBetween(Axis axis, float percentOne, float percentTwo);
	int getControlStickAngle();
	bool controlStickAngleBetween(int angleOne, int angleTwo);
	bool buttonPressed(Button& button);
	bool cardinalDirectionChange(Axis axis, int frames);

private:
	enum class CardinalDirections { Up, Down, Left, Right, None };

	struct Stick
	{
		CardinalDirections horizontalDir = CardinalDirections::None;
		CardinalDirections verticalDir = CardinalDirections::None;
		int framesSinceHorizontalChange = 0, framesSinceVerticalChange = 0;
	};

	void checkHeldButtons();
	void checkStickDirections();

	Controls controls_;
	Stick controlStick_, cStick_;
	unsigned int controllerId_;
	};

#endif // CONTROLLER_H_