# Snake Game in C++

A simple console-based implementation of the classic Snake game written in C++. This project is great for learning C++ fundamentals like loops, conditionals, enums, arrays, and input handling. The game runs in the terminal and features basic mechanics: eat fruit to grow, avoid walls and your tail, and score points.

## Features
- Cross-platform: Works on Windows, macOS, and Linux with standard C++ compilers.
- Non-blocking input for smooth controls.
- Random fruit generation.
- Growing snake tail.
- Score tracking.
- Game over on collisions.

## Requirements
- C++ compiler (e.g., GCC, Clang, or MSVC).
- Standard libraries only—no external dependencies.
- On macOS: Xcode Command Line Tools (install via `xcode-select --install`).
- On Linux: Build essentials (e.g., `sudo apt install build-essential` on Ubuntu).
- On Windows: Visual Studio or MinGW.

## Building the Game
1. Clone or download the repository (or just save `snake.cpp`).
2. Open a terminal/command prompt in the project folder.
3. Compile the code:
   ```
   g++ snake.cpp -o snake
   ```
   - On Windows, if using MinGW: Same command.
   - If using Visual Studio: Open Developer Command Prompt and run `cl snake.cpp`.

## Running the Game
1. In the terminal:
   ```
   ./snake
   ```
   - On Windows: `snake.exe`.
2. The game board will appear. The snake starts in the center and is initially stopped.
3. Use keys to move:
   - `w`: Up
   - `s`: Down
   - `a`: Left
   - `d`: Right
   - `x`: Quit
4. Eat the fruit (`#`) to grow and score 10 points each time.
5. Avoid hitting the walls or your own tail (`o` segments; head is `O`).
6. The game speed is fixed (adjustable in code via `sleep_for` milliseconds).

## Code Structure
- **snake.cpp**: The main source file containing all game logic.
  - `Setup()`: Initializes game state.
  - `Draw()`: Renders the board in the console.
  - `Input()`: Handles keyboard input (cross-platform).
  - `Logic()`: Updates snake movement, collisions, and fruit eating.
  - `main()`: Game loop.

## Customization
- Board size: Change `width` and `height` constants.
- Speed: Modify `this_thread::sleep_for(chrono::milliseconds(100))` in `main()` (lower value = faster).
- Enhancements: Add wrap-around borders, levels, or high scores (see comments in code).

## Troubleshooting
- **No input response**: Ensure terminal supports non-blocking input. On macOS/Linux, the code handles this automatically.
- **Compilation errors**: Verify C++11 support (e.g., add `-std=c++11` to compile command if needed).
- **Screen not clearing**: Adjust `system("clear")` or `system("cls")` based on OS.
- For graphical version: Extend with libraries like SFML (not included here).

## License
This project is open-source under the MIT License. Feel free to fork and improve!

For questions or contributions, open an issue or pull request. Happy coding! 🐍
