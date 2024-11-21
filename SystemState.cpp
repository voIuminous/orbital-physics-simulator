#include "SystemState.h"


// PRIVATE FUNCTIONS
void SystemState::initVariables()
{
	this->window = nullptr;

	//this->Planets.reset(new PlanetaryHandler(
	//	30,       // radius in pixels (scaled from 696,340 km)
	//	1000,     // x position 
	//	750,      // y position
	//	10000.0,  // scaled mass to maintain proper gravitational force
	//	0.0,      // sun is stationary at the system's center
	//	0.0,
	//	sf::Color::Yellow
	//));

	//Planets->createPlanet(
	//	8,        // radius in pixels (scaled from 6,371 km)
	//	1250,     // x position (250 pixels = scaled from 1 AU)
	//	750,      // y position
	//	1.0,      // mass scaled relative to sun's mass
	//	45.0,     // calculated velocity for stable orbit with our scaled G
	//	90.0,     // 90 degrees for circular orbit (perpendicular to radius)
	//	sf::Color::Blue
	//);
	this->Planets.reset(new PlanetaryHandler(
		25,       // radius
		800,      // First star positioned left of center
		750,      // y position (center)
		5000.0,   // equal masses for symmetric orbit
		15.0,     // initial velocity
		90.0,     // moving upward
		sf::Color::Blue
	));

	Planets->createPlanet(
		25,       // same radius
		1200,     // positioned right of center (200 pixels apart)
		750,      // same y position
		5000.0,   // equal mass
		15.0,     // same speed
		-90.0,    // moving downward (opposite direction)
		sf::Color::Red  // Orange color to distinguish
	);
}

void SystemState::initWindow()
{
	this->videoMode.height = 1500;
	this->videoMode.width = 2000;
	this->window.reset(new sf::RenderWindow(this->videoMode, "Gravity"));
}

// CONSTRUCTORS - DESTRUCTORS
SystemState::SystemState()
{
	this->initVariables();
	this->initWindow();
}

SystemState::~SystemState()
{

}

// ACCESSORS
const bool SystemState::running() const
{
	return this->window->isOpen();
}

// PUBLIC FUNCTIONS
void SystemState::pollEvents() {
	while (this->window->pollEvent(ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			window->close();
			break;
		}
	}
}

void SystemState::update()
{
	static sf::Clock clock;
	float dt = clock.restart().asSeconds();

	if (dt > 1.0f / 60.0f) {
		dt = 1.0f / 60.0f;
	}

	this->pollEvents();
	this->Planets->applyGravity();
	this->window->setFramerateLimit(60);
}


void SystemState::render()
{
	this->window->clear(sf::Color::Black);

	// DRAW OBJECTS v
	Planets->renderGravityField(*window);
	Planets->render(*window);

	this->window->display();
}