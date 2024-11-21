# Gravitational Physics Simulator

A gravitational physics simulator that visualizes orbital mechanics and space-time warping effects. Built with C++ and SFML.

### Default Configuration
The simulation comes with a preset configuration featuring:
- Initial velocities set for stable orbital patterns
- Color-coded gravity field indicating force strength

### Customization
You can modify the simulation parameters in `SystemState.cpp`:
- Star masses
- Initial positions
- Velocities
- Visual properties
- Field resolution
- Number of bodies

Example configuration:
```cpp
Planets->createPlanet(
    25,       // radius
    640,      // x position
    360,      // y position
    5000.0,   // mass
    15.0,     // initial velocity
    90.0,     // direction angle
    sf::Color::Yellow
);
```

## Technical Details

### Physics Implementation

The simulation uses several key components for accurate physics calculations:

1. **Gravitational Force**:
   - Implements Newton's law of universal gravitation
   - Force calculated as: F = G * (m1 * m2) / r²
   - Scaled appropriately for visualization

2. **Numerical Integration**:
   - Uses Velocity Verlet integration for stable orbits
   - Handles multiple body interactions simultaneously

3. **Field Visualization**:
   - Vector field showing gravitational force direction and magnitude
   - Dynamic color mapping based on field strength
   - Adjustable resolution and sensitivity

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments

- SFML team for the graphics library
- Physics simulation resources and references
