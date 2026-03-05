*This project has been created as part of the 42 curriculum by Nbaldes Laudinot.*

# Cub3D

## Description

Cub3D is a 3D rendering project inspired by early raycasting games such as Wolfenstein 3D.

The objective is to build a simple 3D game engine in C using the raycasting technique.  
The program reads a `.cub` configuration file describing:

- Wall textures (North, South, East, West)
- Floor and ceiling colors
- A 2D map layout

From this configuration, the engine generates a real-time pseudo-3D view of the environment.  
The player can move inside the maze with collision detection preventing movement through walls.

Main concepts covered:

- File parsing and validation
- 2D grid-based world representation
- Raycasting using the DDA algorithm
- Texture mapping
- Event handling with MiniLibX

---

## Instructions

### Requirements

- Linux or macOS
- GCC
- Make
- MiniLibX

### Compilation

```bash
make
```

This generates the executable:

cub3D
Execution
```
./cub3D map.cub
```
Controls

W, A, S, D — Move

Arrow keys — Rotate

ESC — Exit

Project Structure
```
cub3d/
│
├── src/            # Source files
├── includes/        # Header files
├── maps/           # .cub configuration files
├── textures/       # Texture files (.xpm)
├── Makefile
└── README.md
```
Technical Choices

Language: C

Graphics library: MiniLibX

Rendering technique: Raycasting with DDA

Map validation: Flood fill algorithm

Texture format: XPM

The engine renders one vertical stripe per screen column by casting a ray into the 2D grid and calculating wall distance using perpendicular projection to avoid fish-eye distortion.

---

## Resources

Raycasting tutorial:

https://lodev.org/cgtutor/raycasting.html

MiniLibX documentation:

https://harm-smits.github.io/42docs/libs/minilibx

DDA algorithm reference:

Amanatides & Woo — A Fast Voxel Traversal Algorithm for Ray Tracing

AI Usage

AI was used for:

Architectural guidance for parsing and rendering modules

Concept clarification on raycasting and DDA

README structuring assistance

All implementation logic and code were written manually.