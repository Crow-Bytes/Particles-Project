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
		frameTime.restart(); // Restart the clock (this will return the time elapsed since the last frame)
		float frameTimeSeconds = frameTime.getElapsedTime().asSeconds(); //Convert the clock time to seconds

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
		if (event.key.code == sf::Keyboard::Escape)  // Handle the Escape key pressed and closed events so your program can exit
		{
			cout << "Escape Button Pressed." << endl;
			m_Window.close();
		}

		//Create a loop to construct #(5) particles (Any # of particles)
		if (event.key.code == Mouse::isButtonPressed(Mouse::Left))
		{
			getInput = false;
			cout << "Button Pressed At: " << endl
				<< "x: " << Mouse::getPosition().x << endl
				<< "y: " << Mouse::getPosition().y << endl;
			Vector2i mPos;
			mPos = Mouse::getPosition();
			//mPos.x = -810; //May need to specify m_Window in getPosition
			//mPos.y = 675;

			for (int i = 0; i < 5; i++)
			{
				
				//numPoints is a random number in the range [25:50] (you can experiment with this too)
				int numPoints = rand() % 26 + 25;
				//Pass the position of the mouse click into the constructor
				
				m_particles.emplace_back(m_Window, 30, mPos); //Unsure when numPoints, target is m_Window or View Object.

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

	for (int i = 0; i < m_particles.size(); i = i + 0)
	{
		if (m_particles.at(i).getTTL() > 0.0)
		{
			m_particles.at(i).update(dtAsSeconds);
			i++;
		}
		else
		{
			 m_particles.erase(m_particles.begin() + i); //erase the element the iterator points to
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
