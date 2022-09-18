# GameOfLifeCPlus

Conway's "Life" in C++

Game loads by default with TerminalRenderer.

Binary arguments:
- **--size [int]** Sets grid resolution
- **--res [int]** Sets screen resultion
- **--file [string]** Reads initial state from bmp file
- **-random** Gerenates random initial state
- **-gfx** Use OpenGL Renderer

Example:

`$ ./gol --size 100 --res 1000 -random -gfx`
