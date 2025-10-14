# Conway's Game of Life SFML Edition

## Controls

Keyboard:
- `space` Toggle simulation auto-run
- `R` Randomize all cells
- `C` Clear all cells and reset iteration to 0
- `Right Arrow` Go forwards one iteration (when paused)
- `Left Arrow` Go backwards one iteration (when paused, up to 500 iterations from last most generated)

Mouse:
- `Scroll` - Zoom in or out of the grid
- `Right Mouse Drag` - Pan the grid.
- `Left Mouse Click` - Toggle a cell to be alive or dead (when paused; reset iteration to zero and clears history)

## Building

1. Install [Git](https://git-scm.com/downloads) and [CMake](https://cmake.org/download/). Use your system's package manager if available.

2. Clone this repo and open the it in your text editor of choice.

3. If you use Linux, install SFML's dependencies using your system package manager. A list of dependencies can be found [here](https://www.sfml-dev.org/tutorials/3.0/getting-started/cmake/)

4. Configure and build your project. Most popular IDEs support CMake projects with very little effort on your part.

   - [VS Code](https://code.visualstudio.com) via the [CMake extension](https://code.visualstudio.com/docs/cpp/cmake-linux)
   - [Visual Studio](https://docs.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=msvc-170)
   - [CLion](https://www.jetbrains.com/clion/features/cmake-support.html)
   - [Qt Creator](https://doc.qt.io/qtcreator/creator-project-cmake.html)

   Using CMake from the command line is straightforward as well.
   Be sure to run these commands in the root directory of the project you just created.

   ```
   cmake -B build
   cmake --build build
   ```

5. Enjoy!

## License

Conway's Game of Life SFML Edition - Copyright © 2025 Jeffrey Morris

This program comes with ABSOLUTELY NO WARRANTY.

This is free software, and you are welcome to redistribute it
under certain conditions; see LICENSE.txt for more info.