<div align="center">

# 🏺 ClayPOT

## A Custom-Built C++ Educational 2D Game Engine

![ClayPOT Logo](./Combined_Project/src_code/ClayPOT/Resources/logos/logo.png)

**Learn Game Engine Architecture • Master DSA & Software Engineering • Build RPG Games**

<p>
  <a href="#-quick-start"><strong>🚀 Quick Start</strong></a> •
  <a href="#-key-features"><strong>✨ Features</strong></a> •
  <a href="#-technologies--dependencies"><strong>🎯 Tech Stack</strong></a> •
  <a href="#-how-to-use-the-engine"><strong>📋 Guide</strong></a> •
  <a href="#-troubleshooting"><strong>🔧 Support</strong></a>
</p>

</div>

---

## 📖 Project Overview

**ClayPOT** is an educational 2D game engine prototype developed in C++ to demonstrate the fundamentals of game engine architecture, advanced data structures, and software engineering principles. This project bridges the gap between theoretical computer science concepts and practical game development by implementing:

- **Entity Component System (ECS)** - Flexible object management through composition
- **Behaviour Trees** - Intelligent NPC AI and decision-making
- **A * Pathfinding Algorithm** - Optimal path calculation for navigation
- **Grid-Based Tile System** - Map management and collision detection
- **AABB Collision Detection** - Efficient physics simulation

ClayPOT serves both as an **educational tool for learning engine development** and as a **functional game engine** capable of creating RPG-style games. It demonstrates real-world applications of Data Structures & Algorithms (DSA), Design Patterns, and Software Engineering principles in a practical, game development context.

### Why Build Your Own Engine?

Traditional game engines like Unreal and Unity abstract away the underlying complexity. **ClayPOT reveals the architecture**, allowing developers to:

- Understand how game engines work at a fundamental level
- Apply DSA concepts in real-world scenarios
- Learn professional C++ development practices
- Prototype and develop custom game mechanics

---

## ✨ Key Features

<table align="center">
  <tr>
    <td width="50%">
      <h3>🎮 Core Engine Systems</h3>
      <ul>
        <li>High-performance 2D sprite rendering (SFML)</li>
        <li>Entity Component System (ECS)</li>
        <li>State management (Menu → Game → Editor)</li>
        <li>Frame-based sprite animation</li>
      </ul>
    </td>
    <td width="50%">
      <h3>🤖 AI & Pathfinding</h3>
      <ul>
        <li>Behaviour Tree framework</li>
        <li>A* pathfinding implementation</li>
        <li>Blackboard pattern communication</li>
        <li>Intelligent NPC behavior</li>
      </ul>
    </td>
  </tr>
  <tr>
    <td width="50%">
      <h3>🛠 Game Development Tools</h3>
      <ul>
        <li>Built-in tile-based level editor</li>
        <li>Automated resource management</li>
        <li>AABB collision detection system</li>
        <li>Character attributes & inventory</li>
      </ul>
    </td>
    <td width="50%">
      <h3>🏗 Architecture & Design</h3>
      <ul>
        <li>Modular component-based design</li>
        <li>Template metaprogramming</li>
        <li>Professional design patterns</li>
        <li>Efficient spatial partitioning</li>
      </ul>
    </td>
  </tr>
</table>

---

## 🎯 Technologies & Dependencies

<div align="center">

| Component | Technology | Version |
|:-:|:-:|:-:|
| **Language** | C++ | C++17 Standard |
| **Graphics Library** | SFML | 2.5+ |
| **IDE** | Visual Studio | 2022 Community |
| **Platform** | Windows | 10+ (x64) |
| **Runtime** | Visual C++ Redistributable | 2022 |

**✅ All required runtime dependencies are included with the executable**

</div>

---

## 🚀 Quick Start

### Option 1: Run Pre-Built Executable ⭐ (Recommended)

<div align="center">

**1. Download the executable folder**
```
Navigate to: Combined_Project/ClayPOT_exe/
Keep all files (.exe, .dll, Resources/) together
```

**2. Launch the engine**
```
Double-click ClayPOT.exe
Click "Run anyway" if Windows shows a security prompt
Engine window should open immediately
```

✅ **Works immediately • No installation required • All dependencies included**

</div>

---

### Option 2: Build from Source Code

<div align="center">

**1. Clone the repository**
```bash
git clone https://github.com/Uzair62/ClayPOT.git
cd ClayPOT
```

**2. Prerequisites**
```
• Visual Studio 2022 (Community Edition works)
• C++17 capable compiler
• Windows 10 or later (x64)
```

**3. Build the project**
```
• Open: src_code/ClayPOT.sln in Visual Studio
• Set Build Configuration to: Release
• Build Solution (Ctrl+Shift+B)
• Executable appears in output folder
```

</div>

---

## 📋 How to Use the Engine

### Launching the Application

When you launch `ClayPOT.exe`, you'll see the **Editor Menu Screen**:

<div align="center">

```
┌───────────────────────────────────────────┐
│      🏺 ClayPOT Game Engine Editor🏺      │
│                                           │
│         ► File                            │
│           ► Open                          │
│           ► New                           │
│           ► Save                          │
└───────────────────────────────────────────┘
```

</div>

### Main Menu Options

Click the **Play** button to access Main Menu:

<div align="center">

| Option | Description |
|--------|-------------|
| **New Game** | Start a fresh gameplay session with loaded map |
| **Settings** | Configure graphics |
| **Exit** | Gracefully close the engine |

</div>

### Editor Mode Controls

When creating a new map:

1. **Enter world size** (e.g., 100x100 tiles)
2. **Set tile size** (only 64x64 is supported currently)
3. **Use these controls**:

<div align="center">

| Control | Action |
|---------|--------|
| **Tab** | Toggle tile selector panel |
| **Left Click** | Select tile / Place on map |
| **Right Click** | Remove tiles from map |
| **WASD** | Pan camera around world |
| **Arrow Keys** | Move selected tile |
| **U / I** | Increase/Decrease tile render layer |
| **Mouse Scroll** | Zoom in/out of editor |

</div>

**Note:** Tile type determines rendering order (0 = bottom, 1 = top, 2 = depth sorted)

### In-Game Controls

#### Movement & Interaction
- **WASD**: Move player character
- **E**: Interact with NPCs

#### Combat
- **Left Click**: Attack in facing direction

---

## 📂 Repository Structure

<div align="center">

```
ClayPOT/
│
├── 📁 Combined_Project/
│   │
│   ├── 📁 ClayPOT_exe/                    ← Ready-to-run executable
│   │   ├── 📄 ClayPOT.exe                 (main executable)
│   │   ├── 📄 *.dll                       (dependencies)
│   │   ├── 📁 Resources/                  (game assets)
│   │   │   ├── Textures/
│   │   │   ├── Fonts/
│   │   │   └── Map/
│   │   └── 📁 Saves/                      (save files)
│   │
│   └── 📁 src_code/                       ← Complete source code
│       ├── 📄 ClayPOT.sln                 (Visual Studio solution)
│       ├── 📄 *.h & *.cpp                 (implementation files)
│       ├── 📁 Resources/                  (asset sources)
│
├── 📄 README.md                           (this file)
└── 📄 PROJECT_REPORT.md                   (full technical report)
```

</div>

---

## 🏗 Architecture Overview

### Entity Component System (ECS)

<div align="center">

```
Entity (Game Object)
├── Transform Component (position, rotation)
├── Sprite Component (rendering)
├── Collider Component (physics)
├── Health Component (attributes)
└── Behaviour Component (AI logic)
```

**Benefits:** Flexible composition, data-oriented design, reusable components

</div>

### Behaviour Trees

<div align="center">

```
      Root Node
       /  |  \
      /   |   \
  Selector  Sequence  Action
    / \      / \        |
   /   \    /   \    AttackEnemy
IsNear  Chase  Check  Health
```

**Benefits:** Readable AI logic, composable decisions, hierarchical control

## 📚 Learning Resources

### Data Structures Implemented
- **Vectors**: Dynamic arrays for entities and components
- **Hash Maps**: O(1) resource and entity lookups
- **Priority Queues**: A* algorithm open set management
- **Stacks & Queues**: State and event management
- **Graphs & Trees**: Pathfinding networks and behaviour trees
- **Spatial Grids**: Efficient collision detection and rendering

### Algorithms Demonstrated
- **A * Search**: Optimal pathfinding with Manhattan distance heuristic
- **Depth-First Search (DFS)**: Behaviour tree node traversal
- **AABB Intersection**: Rectangle-based collision detection
- **Spatial Culling**: Rendering optimization for large maps
- **Graph Generation**: Converting tilemaps to navigation graphs

---

## 🔧 Troubleshooting

<div align="center">

| Problem | Solution |
|---------|----------|
| **"DLL not found" error** | Ensure all `.dll` files are in the same folder as `ClayPOT.exe` |
| **Visual C++ Redistributable missing** | Download [VC++ 2022 Redistributable](https://support.microsoft.com/en-us/help/2977003) |
| **Engine crashes on startup** | Run as Administrator, verify Windows is updated |
| **Low FPS / Performance issues** | Reduce graphics quality in Settings, close background apps |
| **Map won't load** | Check file path: `Resources/Map/map.dat` exists |
| **Tiles not rendering** | Verify tile size is 64x64 pixels (only supported size) |

</div>

---

---

## 🤝 Contributing

We welcome contributions! Here's how:

<div align="center">

```
1. Fork the repository
2. Create feature branch: git checkout -b feature/YourFeature
3. Commit changes: git commit -m 'Add YourFeature'
4. Push branch: git push origin feature/YourFeature
5. Submit Pull Request
```

**Guidelines:**
- Follow C++17 standards
- Comment complex logic
- Test thoroughly
- Update documentation

</div>

---


---

## 👨‍💻 Author & Credits

<div align="center">

**[Uzair Kayani]**

• [GitHub](https://github.com/Uzair62) • [LinkedIn](https://linkedin.com/in/Uzair12) • [Email](mailto:uzairkayani7774@gmail.com)

**Developed as an educational project to demonstrate game engine architecture and practical DSA applications.**

</div>

---

## 🎓 Educational Use Cases

**ClayPOT is perfect for:**

- 🎓 **Students** - Learning game engine internals and game development
- 👨‍🏫 **Educators** - Teaching DSA, C++, and software engineering
- 💼 **Junior Developers** - Building portfolio projects and demonstrating skills
- 🔬 **Researchers** - Exploring game AI systems and pathfinding algorithms

---

## 🐛 Report Issues

<div align="center">

**Found a bug or have a feature request?**

[👉 Open an Issue on GitHub](https://github.com/Uzair62/ClayPOT/issues)

Please provide:
- Clear bug description
- Steps to reproduce
- System information (Windows version, graphics card)
- Expected vs actual behavior

</div>

---

## ⭐ Show Your Support

<div align="center">

If ClayPOT helped you learn or inspired your own project, please consider:

- **⭐ Star** the repository to show support
- **👀 Watch** for updates and new features
- **🔗 Share** with others learning game development
- **💬 Discuss** ideas in GitHub Discussions

</div>

---

<div align="center">

---

**Made with ❤️ for game developers and computer science enthusiasts**

**© 2025 ClayPOT Game Engine • All Rights Reserved**

</div>
