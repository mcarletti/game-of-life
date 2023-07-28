# Game of Life

A plain C implementation of Conway's Game of Life.

## What is Conway's Game of Life?

Conway's Game of Life is a cellular automaton that is played on a 2D square grid. Each square (or "cell") on the grid can be either alive or dead, and they evolve according to the following rules:

* Any live cell with fewer than two live neighbours dies (referred to as underpopulation).
* Any live cell with more than three live neighbours dies (referred to as overpopulation).
* Any live cell with two or three live neighbours lives, unchanged, to the next generation.
* Any dead cell with exactly three live neighbours comes to life.

The initial configuration of cells can be created by a human, but all generations thereafter are completely determined by the above rules.

Source: https://conwaylife.com/

## Getting Started

Compile using `gcc` compiler.  
Before running the simulation, create an output directory called `images` in the same folder as the executable. The simulation will create one frame per iteration in the `images` directory.
```bash
gcc main.c -o life -O3 -Wall  # compile
mkdir images                  # create output directory
./life                        # run the simulation
```

### Optional

Create a video of the simulation via `ffmpeg`.
```bash
ffmpeg -framerate 24 -i images/%05d.bmp -c:v libx264 -profile:v high -crf 20 -pix_fmt yuv420p life.mp4
```

## License
MIT License. See [LICENSE](LICENSE) for more information.