<div align="center">

# 🏺 ClayPOT

## A Custom-Built C++ Educational 2D Game Engine

![ClayPOT Logo](./Combined_Project/src_code/ClayPOT/Resources/logos/logo.png)

**Learn Game Engine Architecture. Master DSA & Software Engineering. Build RPG Games.**

[Features](#features) • [Quick Start](#quick-start) • [Architecture](#architecture) • [Documentation](#documentation) • [Contributing](#contributing)

---

</div>

## 📖 Project Overview

**ClayPOT** is an educational 2D game engine prototype developed in C++ to demonstrate the fundamentals of game engine architecture, advanced data structures, and software engineering principles. This project bridges the gap between theoretical computer science concepts and practical game development by implementing:

- **Entity Component System (ECS)** architecture for flexible object management
- **Behaviour Trees** for intelligent NPC AI and decision-making
- **A * Heuristic Algorithm** for optimal path calculation and navigation
- **Grid-Based Tile System** for map management and collision detection
- **AABB Collision Detection** for efficient physics simulation

ClayPOT serves both as an **educational tool for learning engine development** and as a **functional game engine** capable of creating RPG-style games. It demonstrates real-world applications of Data Structures & Algorithms (DSA), Design Patterns, and Software Engineering principles in a practical, game development context.

### Why ClayPOT?

Traditional game engines like Unreal and Unity abstract away the underlying complexity. **ClayPOT reveals the architecture**, allowing developers to:
- Understand how game engines work at a fundamental level
- Apply DSA concepts in real-world scenarios
- Learn professional C++ development practices
- Prototype and develop custom game mechanics

---

## ✨ Key Features

### Core Engine Systems
- **Rendering Engine**: High-performance 2D sprite and tilemap rendering using SFML
- **Entity Component System**: Modular entity management with reusable components
- **State Management**: Seamless game state transitions (Menu → Game → Editor)
- **Animation System**: Frame-based sprite animation with timing controls

### AI & Pathfinding
- **Behaviour Tree Framework**: Node-based AI decision-making system
- **A * Heuristic Pathfinding**: Optimal shortest-path calculation for NPC movement
- **Blackboard Pattern**: Shared memory system for AI agent communication
- **Intelligent NPC Behavior**: Combat, patrol, and chase mechanics

### Game Development Tools
- **Level Editor**: Built-in tile-based map editor for creating game worlds
- **Resource Management**: Automated loading and caching of textures, fonts, and game data
- **Hitbox System**: AABB collision detection with dynamic hitbox management
- **Attribute System**: Character stats, health, damage, and inventory management

### Architecture & Design
- **Modular Design**: Separation of concerns with loosely coupled components
- **Template Metaprogramming**: Type-safe data structures and algorithms
- **Design Patterns**: Factory, Observer, State, and Composite patterns
- **Grid-Based World**: Efficient spatial partitioning for large maps

---

## 🎯 Technologies & Dependencies

### Platform Requirements
- **Operating System**: Windows 10 or later
- **Architecture**: x64 (64-bit)
- **Runtime**: Visual C++ Redistributable 2022

### Development Stack
| Component | Technology | Version |
|-----------|-----------|---------|
| **Language** | C++ | C++17 |
| **Graphics Library** | SFML | 3+ |
| **IDE** | Visual Studio | 2022 |
| **Build System** | MSBuild | 17.0+ |

### Dependencies Included
- **SFML 3.0.0**: Graphics, window management, and input handling
- **Visual C++ Runtime**: Standard library and runtime components
- All required `.dll` files are bundled with the executable

---

## 🚀 Quick Start

### Option 1: Run Pre-Built Executable (Recommended)

1. **Download the executable folder**
   - Navigate to `Combined_Project/ClayPOT_exe/`
   - Download or clone the entire folder (keep all `.dll` files together with the `.exe`)

2. **Launch the engine**
   - Double-click `ClayPOT.exe`
   - If Windows shows a security warning: Click "More info" → "Run anyway"
   - The engine window should open showing the main menu

3. **First-Time Setup**
   - The engine will automatically load all required resources
   - Ensure you have at least 100MB of free disk space
   - Verify all `.dll` files are in the same directory as the `.exe`

### Option 2: Build from Source

1. **Clone the repository**
   ```bash
   git clone https://github.com/Uzair62/ClayPOT.git
   cd ClayPOT
   ```

2. **Prerequisites**
   - Visual Studio 2022 (Community Edition works)
   - C++17 capable compiler

3. **Build the project**
   - Open `src_code/ClayPOT.sln` in Visual Studio
   - Set build configuration to `Release` for optimal performance
   - Build the solution (Ctrl+Shift+B)
   - Executable will be generated in the output folder

---

## 📋 How to Use the Engine

### Starting the Application

When you launch `ClayPOT.exe`, you'll see the **Engine Editor**:

![Engine Startup](./Steps/1.PNG)

This screen shows success!

### File Menu Options

Click the **File** button in the menu to access the following options:
1. Open
2. New
3. Save

![File Menu Dropdown](./Steps/2.PNG)

### Creating New Map

Slecting the new option, there is a pre-built map in the project exe and src_code you can load it by putting this location : Resources/Map/map, for now i will teach you how to create your own map for game.
After clicking new you will see this holder, enter the world bounds and tile size.

![Engine Startup](./Steps/3.PNG)


### Filled attributes
I have filled the world size with 100 tiles in width and 100 tiles in height, and with 64 x 64 pixel size of tile.
64 x 64 is the only supported pixel size for current development on later updates the tile size would be dynamic!.

![File Menu Dropdown](./Steps/4.PNG)

### Map had been set

#### Editor Mode
- **Tab**: Hide and display tile selector panel
- **Left Click**: To select tile from selector and after pressing tab, to add tiles to map
- **Right Click**: Remove Tiles
- **WASD**: Move camera aound editor
- **WASD**: While inside selector move around selector
- **Arrows keys**: Move around selected tile
- **U**: Increase the level of tile type
- **I**: Decrease the level of tile type
- **Note the tile type is the rendering order of tile if is 0 means would be at bottom is is 1 means always on top if is 2 means will be dynamically rendered determined by depth sorting of the position of grids object.**

After setting world bounds, you have successfully created the map boundries, now it's time to make the world alive.
The current state you are seeing is editor, where the state is aimed to make the whole game by simple drag and drop, the current engine code does not allow user to add the player and enemies by it's own, it only allows user to make maps for games to test level. How ever in future developer aims to make fully functional drag and drop editor state.
Create your own map by the sprite sheet you have added(there is added sprite sheet in the engine exe feel free to use it). Save it, hit play on the top 
![Engine Startup](./Steps/5.PNG)


### Main Menu State

This is the main menu state

![File Menu Dropdown](./Steps/6.PNG)

#### Available Options:

1. **Play Game**
   - Starts a fresh gameplay session
   - Loads the default map and player character
   - Resets all game state and variables
   - 
2. **Settings**
   - Configure graphics quality and resolution
   - Toggle fullscreen mode

3. **Exit**
   - Gracefully shut down the engine

### In-Game Controls

#### Movement
- **Arrow Keys** or **WASD**: Move the player character
- **E**: Interact with NPCs and objects

#### Combat
- **Left Click**: Attack in the direction facing

---

## 📂 Repository Structure

```
ClayPOT/
├── Combined_Project/
│   ├── ClayPOT_exe/              # Ready-to-run executable package
│   │   ├── ClayPOT.exe           # Main executable (double-click to run)
│   │   ├── *.dll                 # Required dependency libraries
│   │   ├── Resources/            # Game assets (textures, fonts, data)
│   │   └── Saves/                # Saved game files directory
│   │
│   └── src_code/                 # Complete source code
│       ├── ClayPOT/              # Main project directory
│       ├── *.h & *.cpp           # Header and implementation files
│       ├── ClayPOT.sln           # Visual Studio solution file
│       ├── Resources/            # Asset source files
│       └── Documentation/        # Technical documentation
│
├── README.md                      # This file
└── LICENSE                        # Project license
```

## 🔧 Troubleshooting

### "DLL not found" Error
- **Solution**: Ensure all `.dll` files are in the same folder as `ClayPOT.exe`
- Download the entire `ClayPOT_exe` folder, not individual files

### "Visual C++ Redistributable is missing"
- **Solution**: Install the Visual C++ 2022 Redistributable from Microsoft
- [Download link](https://support.microsoft.com/en-us/help/2977003/the-latest-supported-visual-c-downloads)

### Engine Crashes on Startup
- **Solution**: Verify all required dependencies are installed
- Check that Windows is up to date
- Try running as Administrator

### Low FPS or Performance Issues
- **Solution**: Reduce graphics quality in Settings
- Close unnecessary background applications
- Update your graphics drivers

---

## 📜 License

This project is licensed under the **MIT License** - see the [LICENSE](LICENSE) file for details.

This means you can:
- Use it for educational and commercial projects
- Modify and distribute the code
- Use it in your own projects

Just include a copy of the license and give credit to the original author.

---

## 🎓 Educational Use

ClayPOT is designed as an **educational project** and is ideal for:
- **Students**: Learning game engine architecture and game development
- **Educators**: Teaching DSA, software engineering, and C++ programming
- **Hobbyists**: Understanding how games work under the hood
- **Junior Developers**: Building portfolio projects and demonstrating skills

---

## 🐛 Reporting Issues

Found a bug or have a feature request? 
- Open an issue on [GitHub Issues](https://github.com/yourusername/ClayPOT/issues)
- Provide detailed reproduction steps
- Include relevant system information

---

## 📞 Support

For questions and discussions:
- **GitHub Discussions**: Ask questions and share ideas
- **Email**: [uzairkayani7774@gmail.com]

---

## 🌟 Star & Follow

If you find this project useful for learning, please:
- ⭐ **Star the repository** to show your support
- 👁️ **Watch for updates** to stay informed about new features
- 🔗 **Share with others** learning game development

---

<div align="center">

**Made with ❤️ for game developers and computer science enthusiasts**

© 2025 ClayPOT Game Engine. All rights reserved.

</div>
