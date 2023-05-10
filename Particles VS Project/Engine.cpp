#include "Engine.h"
#include "Particle.h"

Engine::Engine()
{
	//Call create on m_Window to populate the RenderWindow member variable

	//You can assign a custom resolution or you can call VideoMode::getDesktopMode() to get the screen resolution

	VideoMode vm(1920, 1080); //* Set to getDesktopMode after success
	m_Window.create(vm, "Particles", Style::Default);

}

void Engine::run()
{
	//Construct a local Clock object to track time per frame
	Clock frameTime;

	//Construct a local Particle to be used for the unit tests.  The tests will be given to you, and you can use them to check your progress as you go.  Use the following code exactly:
	cout << "Starting Particle unit tests..." << endl;
	Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
	p.unitTests();
	cout << "Unit tests complete.  Starting engine..." << endl;

	//After the unit tests are complete, create your game loop



	while (m_Window.isOpen()) //Loop while m_Window is open
	{
		float frameTimeSeconds = frameTime.getElapsedTime().asSeconds(); //Convert the clock time to seconds

		frameTime.restart(); // Restart the clock (this will return the time elapsed since the last frame)
		


		//				Call Input				//
		input();
		//				Call Update				//
		update(frameTimeSeconds);
		//				Call Draw				//
		draw();
	}
}

void Engine::input()
{
	Event event;
	bool getInput = true;
	// Poll the Windows event queue
	while (m_Window.pollEvent(event))
	{

		//Handle Inputs to {Close Window}
		if (event.key.code == Keyboard::Escape || event.type == Event::Closed)  // Handle the Escape key pressed and closed events so your program can exit
		{
			m_Window.close();
		}
		//Create a loop to construct #(5) particles (Any # of particles)
		if ((event.key.code == Mouse::isButtonPressed(Mouse::Left) && getInput))
		{
			getInput = false;

			Vector2i mPos = Mouse::getPosition();
			//Vector2i positionTest(1000, 300);	 UNUSED CODE *****************************TESTER
			//mPos = positionTest;

			cout << "Button Pressed At: " << endl
				 << "x: " << Mouse::getPosition().x << endl
			 	 << "y: " << Mouse::getPosition().y << endl;

			for (int i = 0; i < 5; i++)
			{
				//numPoints is a random number in the range [25:50] (you can experiment with this too)
				int numPoints = rand() % 26 + 25;
				//Pass the position of the mouse click into the constructor
				
				Particle pTemp(m_Window, numPoints, mPos); //Unsure when numPoints, target is m_Window or View Object.
				m_particles.push_back(pTemp);
			}

			if (event.type == Event::KeyReleased)
			{
				getInput = true;
			}
		}
	}
	
}

void Engine::update(float dtAsSeconds)
{
	//Loop thru m_particles and call update on each Particle in the vector whose ttl isnt expired.

	for (auto it = m_particles.begin(); it != m_particles.end();)
	{
		if (it->getTTL() > 0.0) 
		{
			//cout << "TTL LEFT: " << it->getTTL() << endl;

			it->update(dtAsSeconds);
			it++;
		}
		else
		{
			 it = m_particles.erase(it); //erase the element the iterator points to

			 cout << "Particle Killed" << endl;
			//erase returns an iterator that points to the next element after deletion, or end if it is the end of the vector
		}
	}
}


void Engine::draw()
{
	m_Window.clear();
	for (int i = 0; i < m_particles.size(); i++)
	{
		m_Window.draw(m_particles.at(i));
	}
	m_Window.display();
}
