🛠️ Phase 1: Refactoring & CLI Tools

[ ] Extract GameState: Move the core logic and map into a separate header file (e.g., GameState.h / GameState.cpp).

[ ] Argument Parsing (Dimensions): Add command-line arguments to dynamically set the width and height of the board.

                                   [ ] Argument Parsing (Speed): Add a command-line argument to control the tick time (replacing the hardcoded usleep duration).

                                                                 [ ] CLI Board Initialization: Add the ability to pass the coordinates of initial live cells directly from the command line so you don't have to recompile every time you want a new pattern.

                                                                 🚀 Phase 2: The High-Performance Engine ("Waaaaaaaaaaay Later")

                                                                 [ ] Multithreading: Implement a thread pool to divide the grid into chunks and calculate the neighbor rules in parallel.

                                                                 [ ] The GPU Port (OpenGL): Finish reading the OpenGL book and port the entire simulation to the graphics card (this is where you will use that Double Buffering swap-chain we talked about!).<
