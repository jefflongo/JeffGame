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

class Controller
{
public:
	typedef sf::Joystick::Axis Axis;

	enum class CardinalDirections { Up, Down, Left, Right, None };

	// Always initialize framesSinceChange members as 0 and CardinalDirections as None

	// Assign axes to the stick?
	struct Stick
	{
		//Axis horizontal, vertical;
		float radius;
		int framesSinceHorizontalChange, framesSinceVerticalChange;
		CardinalDirections horizontalDir, verticalDir;
	};

	struct Button
	{
		unsigned int id;
		bool held;
		//unsigned int framesHeld;
	};

	// Make these all Controller members initialized by constructor.  Controller methods for each button
	struct Controls
	{
		Stick controlStick, cStick;
		float SHOULDER_MIN, SHOULDER_MAX;
		Button A, B, X, Y, Z, R, L, START, D_PAD_UP, D_PAD_LEFT, D_PAD_DOWN, D_PAD_RIGHT;
	};

	Controller();
	Controller(unsigned int controllerId, Controls controls);

	void update();

	Controls* getControls(); // hopefully find a way to get rid of this
	float getAxisPosition(Axis axis) const;
	int getControlStickAngle() const;

	bool buttonPressed(Button& button);
	bool axisPercentageGreaterThan(Axis axis, float percent);
	bool axisPercentageLessThan(Axis axis, float percent);
	bool axisPercentageBetween(Axis axis, float percentOne, float percentTwo);
	bool controlStickAngleBetween(int angleOne, int angleTwo);
	bool cardinalDirectionChange(Axis axis, int frames);

private:
	void checkHeldButtons();
	void checkStickDirections();

	Controls controls_;
	unsigned int controllerId_;
};

#endif // CONTROLLER_H_