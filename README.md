# JeffGame
A SSBM physics engine clone in progress using the SFML library image rendering.

Currently, the game engine is implemented which creates a fixed instance of the game at 60 FPS. Different game states are supported such as a menu (very basic at the moment) and actual gameplay. The game can be controlled with either a keyboard or a GameCube controller. The physics engine is still entirely WIP but currently supports movement and collision detection. Adjusting variables such as gravity, friction, and acceleration are still WIP to get proper values. An animation engine is impleted via a given spritesheet and supports most animations in game. Still TODO is linking actions besides animations to the playerstates, and implementing respawning.

For a lower level look at the code, the game creates the instance and links a player with a controller based on how they press start. The start press also triggers a transition to the gameplay game state. Once in game the animation engine starts running and the player can be  controller to explore the current implementation of the physics engine.
