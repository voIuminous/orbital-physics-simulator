#include "PlanetaryHandler.h"

#define M_PI 3.14
#define TRANSPARENCY 150

// CONSTRUCTORS & DESTRUCTORS
PlanetaryHandler::PlanetaryHandler(int r, int posX, int posY, double mass, double initialV, float angle, sf::Color color)
{
	sf::CircleShape planet;
	planet.setRadius(r);
	planet.setPosition(posX, posY);
	planet.setOrigin(planet.getRadius(), planet.getRadius());
	planet.setFillColor(color);

    float angleRad = angle * M_PI / 180.0f;
    sf::Vector2f temp = sf::Vector2f(
        (initialV * TIME_SCALE / POSITION_SCALE) * cos(angleRad),
        (initialV * TIME_SCALE / POSITION_SCALE) * sin(angleRad)
    );

	m_mass.push_back(mass);
	accelerations.push_back(sf::Vector2f(0, 0));
	velocities.push_back(temp);
	planets.push_back(planet);
}

// PUBLIC FUNCTIONS
void PlanetaryHandler::createPlanet(int r, int posX, int posY, double mass, double initialV, float angle, sf::Color color)
{
	
	sf::CircleShape planet;
	planet.setRadius(r);
	planet.setPosition(posX, posY);
	planet.setOrigin(planet.getRadius(), planet.getRadius());
	planet.setFillColor(color);

    float angleRad = angle * M_PI / 180.0f;
    sf::Vector2f temp = sf::Vector2f(
        (initialV * TIME_SCALE / POSITION_SCALE) * cos(angleRad),
        (initialV * TIME_SCALE / POSITION_SCALE) * sin(angleRad)
    );

	m_mass.push_back(mass);
	accelerations.push_back(sf::Vector2f(0, 0));
	velocities.push_back(temp);
	planets.push_back(planet);
}

void PlanetaryHandler::applyGravity()
{
    updateGravityField();
    static const double timestep = 0.16;
    static const double softening = 100.0;

    std::vector<sf::Vector2f> new_accelerations(planets.size(), sf::Vector2f(0, 0));

    for (size_t i = 0; i < planets.size(); i++)
    {
        for (size_t j = 0; j < planets.size(); j++)
        {
            if (i != j)
            {
                double dx = planets[j].getPosition().x - planets[i].getPosition().x;
                double dy = planets[j].getPosition().y - planets[i].getPosition().y;

                double distSquared = dx * dx + dy * dy + softening;
                double dist = sqrt(distSquared);

                double forceMagnitude = SCALED_G * m_mass[i] * m_mass[j] / distSquared;

                double ax = forceMagnitude * dx / (dist * m_mass[i]);
                double ay = forceMagnitude * dy / (dist * m_mass[i]);

                new_accelerations[i].x += ax;
                new_accelerations[i].y += ay;
            }
        }
    }

    for (size_t i = 0; i < planets.size(); i++)
    {
        velocities[i].x += new_accelerations[i].x * timestep;
        velocities[i].y += new_accelerations[i].y * timestep;

        planets[i].move(velocities[i].x * timestep, velocities[i].y * timestep);
        accelerations[i] = new_accelerations[i];
    }

}

void PlanetaryHandler::updateGravityField()
{
    fieldLines.clear();

    // Create field lines across the screen
    for (int x = 0; x < 2000; x += FIELD_RESOLUTION) {
        for (int y = 0; y < 1500; y += FIELD_RESOLUTION) {
            double totalAccX = 0;
            double totalAccY = 0;

            for (size_t i = 0; i < planets.size(); i++) {
                double dx = planets[i].getPosition().x - x;
                double dy = planets[i].getPosition().y - y;
                double distSquared = dx * dx + dy * dy + 100.0;
                double dist = sqrt(distSquared);

                double force = SCALED_G * m_mass[i] / distSquared;
                totalAccX += force * dx / dist;
                totalAccY += force * dy / dist;
            }

            double magnitude = sqrt(totalAccX * totalAccX + totalAccY * totalAccY);
            double normalizedLength = std::min(FIELD_RESOLUTION * 0.8, magnitude * FIELD_RESOLUTION * 0.1);

            sf::VertexArray line(sf::Lines, 2);
            line[0].position = sf::Vector2f(x, y);
            line[1].position = sf::Vector2f(
                x + (totalAccX / magnitude) * normalizedLength,
                y + (totalAccY / magnitude) * normalizedLength
            );

            sf::Color fieldColor = getFieldColor(magnitude);
            line[0].color = fieldColor;
            line[1].color = fieldColor;

            fieldLines.push_back(line);
        }
    }
}

sf::Color PlanetaryHandler::getFieldColor(double strength)
{
    const double maxStrength = 2.0;
    strength = std::min(strength, maxStrength) / maxStrength;

    if (strength < 0.25) {
        int blue = 255;
        int green = (strength * 4) * 255;
        return sf::Color(0, green, blue, TRANSPARENCY);
    }
    else if (strength < 0.5) {
        int blue = (2 - strength * 4) * 255;
        return sf::Color(0, 255, blue, TRANSPARENCY);
    }
    else if (strength < 0.75) {
        int red = (strength * 4 - 2) * 255;
        return sf::Color(red, 255, 0, TRANSPARENCY);
    }
    else {
        int green = (4 - strength * 4) * 255;
        return sf::Color(255, green, 0, TRANSPARENCY);
    }
}

void PlanetaryHandler::renderGravityField(sf::RenderWindow& window)
{
    for (const auto& line : fieldLines) {
        window.draw(line);
    }
}

void PlanetaryHandler::render(sf::RenderWindow& window)
{
	for (int i = 0; i < planets.size(); i++)
	{
        /*std::cout << "Planet " << i << " velocity: " <<
            velocities[i].x << ", " << velocities[i].y << std::endl;*/
		window.draw(this->planets[i]);
	}
}
