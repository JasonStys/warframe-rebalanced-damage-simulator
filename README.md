# warframe-rebalanced-damage-simulator
Upload of an old project, It was my first real big code project at CSUMS for the CS 211 course.


A C++ console application that simulates a custom rebalanced version of the Warframe damage system. The project models weapons, enemies, damage types, status effects, critical hits, multishot, damage over time, armor, shields, overguard, and color-coded console damage output.

This repository was recreated from a saved CS 211 project document after the original project files were no longer available. The recovered document included the original README notes, gameplay design notes, reference tables, and core C++ source code. A few small support files were reconstructed so the project has a complete buildable structure.

## Project Overview

The simulator calculates damage from a user-defined weapon against a user-defined enemy. It supports multiple Warframe-inspired damage types and a custom rebalance system that changes how several status effects work. The program prompts for weapon stats, enemy stats, and then displays simulated damage output through the console.

The project was originally built for a C++ course and demonstrates procedural programming, object-oriented design, vectors, maps, console input and output, functions, classes, and modular header/source organization.

## Features

- User input for weapon stats and enemy stats
- Weapon damage split across multiple physical and elemental damage types
- Multishot support with fractional extra shot chance
- Critical chance and critical multiplier calculations
- Status chance and status proc selection based on damage weighting
- Damage over time effects for Slash, Heat, Electric, Toxin, Viral, Blast, and Gas
- Armor, shields, health, and overguard handling
- Status stack behavior for armor and shield reduction effects
- Console health and shield bar output
- Color-coded damage numbers for critical tiers
- CSV reference files for enemy stats and damage type interactions
- Markdown reference files explaining damage effects and enemy level scaling

## Rebalanced Damage System Notes

This project changes several Warframe-inspired damage behaviors. Viral becomes a damage over time effect that can add its damage into other DOT effects. Slash no longer ignores armor and instead deals longer-lasting DOT. DOT damage decays over time instead of disappearing immediately. Enemy resistances are no longer faction based, and several health, shield, and armor types are reintroduced or modified.

## Repository Structure

```text
.
├── README.md
├── Damage.md
├── EnemyLevelScalling.md
├── DamageTypestoHPTypes.csv
├── EnemyList.csv
├── Main.cpp
├── DamageCalculator.cpp
├── DamageCalculator.hpp
├── Weapon.hpp
├── Weapon.cpp
├── Enemy.hpp
├── Enemy.cpp
├── ColorUtil.hpp
└── Makefile
```

## How to Build

Use a C++17 compatible compiler.

```bash
make
```

Or compile manually.

```bash
g++ -std=c++17 -Wall -Wextra -pedantic Main.cpp DamageCalculator.cpp Weapon.cpp Enemy.cpp -o warframe_damage_simulator
```

## How to Run

```bash
./warframe_damage_simulator
```

On Windows with MinGW, the output executable may be named:

```bash
warframe_damage_simulator.exe
```

## Main Program Flow

1. Enter weapon stats.
2. Enter each damage type value.
3. Enter enemy health, shield, armor, and overguard values.
4. Run the damage simulation.
5. Choose whether to fire again, change weapon values, change enemy values, or quit.

## Reference Files

`Damage.md` explains each damage type, status effect, symbol, and custom rebalance behavior.

`EnemyLevelScalling.md` explains faction-based level scaling formulas and armor resistance caps.

`DamageTypestoHPTypes.csv` contains the damage multiplier table for damage types against health, armor, shield, and overguard types.

`EnemyList.csv` contains enemy reference values such as base health, armor, shields, faction, unit type, and overguard status.

## Known Limitations

The recovered project document did not include every original implementation file. `Weapon.cpp`, `Enemy.hpp`, `Enemy.cpp`, and `ColorUtil.hpp` were recreated as compatible support files based on the interfaces used by the recovered C++ code.

The original README notes mention that Replit CPU limits could cause the simulation to stop during large test runs. Using smaller fire time, fire rate, and multishot values is recommended.

Some status symbols may not color correctly in every terminal because emoji and ANSI color support vary by environment.

## Skills Demonstrated

- C++ console application development
- Object-oriented programming with custom classes
- Header and source file organization
- Procedural simulation logic
- Vectors and maps
- User input validation
- Randomized probability simulation
- Damage over time logic
- Status effect stacking
- CSV reference data organization
- Game systems design and balancing

## Suggested Future Improvements

- Fully integrate the enemy CSV lookup into the program
- Add a weapon preset system
- Add exception handling for invalid input
- Add unit tests for damage and DOT calculations
- Add a cleaner combat log format
- Add damage statistics after each simulation
- Improve health bar scaling and display stability
- Add a CMake build file
