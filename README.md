# ScreenTennis

ScreenTennis is a simple 2D game developed in C++ using SDL2. It serves as a fun experiment in basic game programming, where two players control platforms (paddles) to keep a moving ball in play. The project demonstrates fundamental concepts like event handling, collision detection, and basic rendering.

## Features

- **Two-Player Gameplay:**  
  - **Player 1:** Use **W** (up) and **S** (down) to move the left paddle.
  - **Player 2:** Use **Up Arrow** (up) and **Down Arrow** (down) to move the right paddle.
- **Game Start & Speed Adjustment:**  
  - Press **Enter** to launch the ball.
  - Increase ball speed with **G** and decrease with **F** (speed is capped at 10×).
- **Splash Screen & Game Guide:**  
  - A splash screen is displayed at startup.
  - A simple message box shows game instructions before the game begins.
- **Collision Detection:**  
  - The game uses Axis-Aligned-Bounding-Box method for detecting collisions between the ball and the paddles, as well as the window edges to determine the winner.
- **Basic Rendering:**  
  - Uses SDL2’s rendering capabilities to draw the game objects and guidelines on the screen.

## Project Structure

- **gamesrc.cpp**  
  This is the main source file where the core game logic resides. It handles:
  - Initialization and shutdown of SDL.
  - Creation of the game window and renderer.
  - Event processing (keyboard inputs for paddle movement and game control).
  - Main game loop with object movement, collision detection, and rendering.
  
- **rendering.cpp**  
  Contains example code for:
  - Setting up an SDL renderer.
  - Loading images and creating textures.
  - Implementing a simple scaling logic to adapt textures to the window size.
  
- **scene.cpp**  
  Includes (commented-out) code for setting up a basic game scene. It shows how to:
  - Create target and shooter rectangles.
  - Draw guidelines (x-axis and y-axis) for layout purposes.
 
- **Asset Files**  
  - **BMP Images:**  
    - `EA.bmp`, `dot.bmp`, and `splash2.bmp` are used for splash screens and in-game textures.
  - **Code::Blocks Project Files:**  
    - Files such as `Fun.cbp`, `Fun.depend`, and `Fun.layout` are included for building the project with Code::Blocks.

## Getting Started

### Prerequisites

- **C++ Compiler:** Ensure you have a C++ compiler set up.
- **SDL2 Library:** Install SDL2, which is required for rendering, event handling, and multimedia functions.
- **Code::Blocks (Optional):** The project includes Code::Blocks project files for easy setup.

### Building the Project

1. **Clone the Repository:**

   ```bash
   git clone https://github.com/SXZZ5/ScreenTennis.git
   cd ScreenTennis
   ```

2. **Open the Project:**
   - Open the provided Code::Blocks project file (e.g., `Fun.cbp`) if you use Code::Blocks.
   - Alternatively, configure your build system to compile the `.cpp` files and link against the SDL2 library.

3. **Ensure Assets are in Place:**  
   - Make sure the BMP files (`EA.bmp`, `dot.bmp`, `splash2.bmp`) are in the working directory so that the game can load them correctly.

4. **Build and Run:**  
   - Compile the project and run the executable to start the game.

## Future Improvements

- **Timer-Based Movement:**  
  Although the current implementation uses a frame-count workaround, a proper implementation using SDL timers would make the game more consistent across different hardware.
- **Enhanced Graphics & Sound:**  
  Integration of more advanced graphics, sound effects, and animations can further improve the gameplay experience.
- **Code Refinement:**  
  Further modularization and cleanup of the code can make it easier to extend and maintain.
