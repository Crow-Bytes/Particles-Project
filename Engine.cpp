#include "Engine.h"
#include "Particle.h"

Engine::Engine()
{
	VideoMode vm(1920, 1080); //* Set to getDesktopMode after success
	m_Window.create(vm, "Particles", Style::Default);

}

void Engine::run()
{
	Clock frameTime;
	cout << "Starting Particle unit tests..." << endl;
	Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
	p.unitTests();
	cout << "Unit tests complete.  Starting engine..." << endl;

	while (m_Window.isOpen())
	{
		frameTime.restart();
		float frameTimeSeconds = frameTime.getElapsedTime().asSeconds();
		//////////////////////////////////////////
		//				Call Input				//
		//////////////////////////////////////////

		input();

		//////////////////////////////////////////
		//				Call Update				//
		//////////////////////////////////////////

		update(frameTimeSeconds);

		//////////////////////////////////////////
		//				Call Draw				//
		//////////////////////////////////////////

		draw();
	}
}

void Engine::input()
{
	Event event;

	while (m_Window.pollEvent(event))
	{
		//Handle Inputs to {Close Window}
		if (event.type == (Keyboard::isKeyPressed(Keyboard::Escape) || Event::Closed))
		{
			m_Window.close();
		}
		//Create a loop to construct #(5) particles (Any # of particles)
		if (event.type == Mouse::isButtonPressed(Mouse::Left))
		{
			for (int i = 0; i < 5; i++)
			{
				Vector2i mPos;
				mPos.x = Mouse::getPosition().x; //May need to specify m_Window in getPosition
				mPos.y = Mouse::getPosition().y;
				m_particles.at(i) =(m_Window, numPoints, mPos); //Unsure when numPoints, target is m_Window or View Object.

			}
		}
	}
	
	
}

void Engine::update(float dtAsSeconds)
{
	//Loop thru m_particles and call update on each Particle in the vector whose ttl isnt expired.
	for (int i = 0; i < m_particles.size(); i++)
	{
		if (m_particles.at(i).getTTL() <= 0) //If a particle's ttl has expired, it must be erased from the vector
		{
			m_particles.erase(m_particles.begin() + i);
		}
		for (int i = 0; i < m_particles.size(); i++)
		{
			if (m_particles.at(i).getTTL() > 0.0)
			{
				m_particles.at(i).update(dtAsSeconds);
				i++;
			}
			else
			{
				m_particles.erase(m_particles.begin() + i);
			}
		}
	}

}


void Engine::draw()
{

}
