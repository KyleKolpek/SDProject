#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iomanip>
#include <iostream>

float color[3] = {1, 0, 0};

void rotate(bool dir);

int main()
{
	sf::WindowSettings Settings;
	Settings.DepthBits = 24;
	Settings.StencilBits = 8;
	sf::Window App(sf::VideoMode(800, 600, 32), "SFML Demo", sf::Style::Close, Settings);
	sf::SoundBuffer Buffer;
	if(!Buffer.LoadFromFile("../assets/sounds/huh.wav"))
	{
		std::cout << "Failure to load sound filei\n";
		return 0;
	}
	sf::Clock Clock;
	sf::Sound Sound;
	Sound.SetBuffer(Buffer);
	Sound.SetVolume(50.0f);

	//Set clear values.
	glClearDepth(1.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, 1.0f, 1.0f, 500.0f);

	const sf::Input& Input = App.GetInput();
	
	while(App.IsOpened())
	{
		sf::Event Event;
	
		//Some simple event handling.
		while (App.GetEvent(Event))
		{
			if(Event.Type == sf::Event::Closed)
				App.Close();
			
			if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
				App.Close();

			if((Event.Type == sf::Event::Resized))
				glViewport(0, 0, Event.Size.Width, Event.Size.Height);
			
			if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Left))
			{
				if(Sound.GetStatus() == sf::Sound::Playing)
					Sound.Stop();
				Sound.Play();
				rotate(false);
			}
			if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Right))
			{
				if(Sound.GetStatus() == sf::Sound::Playing)
					Sound.Stop();
				Sound.Play();
				rotate(true);
			}
		}
		
		App.SetActive();
		
		/*
			Example of getting some values from the input object. Also pretty 
			easy to get mouse below. 
		*/
		bool leftKeyDown = Input.IsKeyDown(sf::Key::Left);
		bool rightButtonDown = Input.IsMouseButtonDown(sf::Mouse::Right);
		unsigned int mouseX = Input.GetMouseX();
		unsigned int mouseY = Input.GetMouseY();
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		/*
			Drawing goes below. Easily done in another function or the method
			of render object! So that is pretty easy.
		*/
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0.0f, 0.0f, -200.0f);
		glRotatef(Clock.GetElapsedTime() * 50, 1.0f, 0.0f, 0.0f);
		glRotatef(Clock.GetElapsedTime() * 30, 0.0f, 1.0f, 0.0f);
		glRotatef(Clock.GetElapsedTime() * 90, 0.0f, 0.0f, 1.0f);

		glColor3f(color[0], color[1], color[2]);
		
		glBegin(GL_QUADS);

    		glVertex3f(-50.f, -50.f, -50.f);
    		glVertex3f(-50.f,  50.f, -50.f);
    		glVertex3f( 50.f,  50.f, -50.f);
    		glVertex3f( 50.f, -50.f, -50.f);

    		glVertex3f(-50.f, -50.f, 50.f);
    		glVertex3f(-50.f,  50.f, 50.f);
    		glVertex3f( 50.f,  50.f, 50.f);
    		glVertex3f( 50.f, -50.f, 50.f);

    		glVertex3f(-50.f, -50.f, -50.f);
    		glVertex3f(-50.f,  50.f, -50.f);
    		glVertex3f(-50.f,  50.f,  50.f);
    		glVertex3f(-50.f, -50.f,  50.f);

    		glVertex3f(50.f, -50.f, -50.f);
    		glVertex3f(50.f,  50.f, -50.f);
    		glVertex3f(50.f,  50.f,  50.f);
    		glVertex3f(50.f, -50.f,  50.f);

    		glVertex3f(-50.f, -50.f,  50.f);
    		glVertex3f(-50.f, -50.f, -50.f);
    		glVertex3f( 50.f, -50.f, -50.f);
    		glVertex3f( 50.f, -50.f,  50.f);

    		glVertex3f(-50.f, 50.f,  50.f);
    		glVertex3f(-50.f, 50.f, -50.f);
    		glVertex3f( 50.f, 50.f, -50.f);
    		glVertex3f( 50.f, 50.f,  50.f);

		glEnd();
		
		//Call to actually display the things.
		App.Display();
	}

	return EXIT_SUCCESS;
}

//false for left movement and true for right
void rotate(bool dir)
{
	if(dir)
	{
		float temp = color[0];
		color[0] = color[2];
		color[2] = color[1];
		color[1] = temp;
	}
	else
	{
		float temp = color[2];
		color[2] = color[0];
		color[0] = color[1];
		color[1] = temp;
	}
}
