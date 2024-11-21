#pragma once

#ifndef PLANETARYHANDLER_H
#define PLANETARYHANDLER_H

#include <iostream>
#include <cmath>
#include <math.h>
#include <vector>
#include <time.h>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"

class PlanetaryHandler
{
public:
	PlanetaryHandler(int r, int posX, int posY, double mass, double initialV, float angle, sf::Color color);

	void createPlanet(int r, int posX, int posY, double mass, double initialV, float angle, sf::Color color);
	void applyGravity();
	
	void render(sf::RenderWindow& window);
	void renderGravityField(sf::RenderWindow& window);

private:
	static constexpr double POSITION_SCALE = 1.0;
	static constexpr double TIME_SCALE = 1.0;
	static constexpr double SCALED_G = 50.0;
	static constexpr int FIELD_RESOLUTION = 40; // Space between field points
	std::vector<sf::VertexArray> fieldLines;

	void updateGravityField();
	sf::Color getFieldColor(double strength);
	std::vector<sf::CircleShape> planets;
	std::vector<sf::CircleShape> path;
	std::vector<sf::Vector2f> velocities;
	std::vector<sf::Vector2f> accelerations;
	std::vector<double>	m_mass;
};

#endif