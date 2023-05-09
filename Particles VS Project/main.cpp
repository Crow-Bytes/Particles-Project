#include "Engine.h"

int main()
{
	// Declare an instance of Engine
	Engine engine;
	// Start the engine
	engine.run();
	
	// Quit in the usual way when the engine is stopped
	return 0;
}

/*
Matrix Unit Tests (3 points)
	X	RotationMatrix constructor
	X	ScalingMatrix constructor
	X	TranslationMatrix constructor
Particle Unit Tests  (5 points)
	X	Constructing a Particle in the center of the monitor that correctly maps to (0,0) on the Cartesian Plane
	X	Applying one rotation of 90 degrees
	X	Applying a scale of 0.5
	X	Applying a translation of (10, 5)
Graphical Tests  (8 points)
	X	Particles are generated where the user clicks
	X	Particles have randomized color
	X	Particles have randomized shape
	X	Particles are given randomized initial vertical and horizontal speeds
	X	Particles rotate
	X	Particles fall
	X	Particles shrink
	X	Particles are erased after their time to live expires
*/