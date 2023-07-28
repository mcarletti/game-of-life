#include <stdlib.h>  // srand, rand, RAND_MAX
#include <string.h>  // memset, memcpy
#include <time.h>    // time
#include <assert.h>  // assert

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int main(void)
{
    // ==============
    // Settings
    // ==============

    const unsigned int rows     =  768;  // pixels
    const unsigned int cols     = 1024;  // pixels
    const unsigned int fps      =   24;  // frames per second
    const unsigned int duration =   10;  // seconds
    const float        density  =  0.5;  // probability of a cell being alive at the first iteration (0.0 to 1.0)
    const unsigned int seed     = time(NULL);

    // set random seed
    srand(seed);

    // sanity checks
    assert(rows > 0 && cols > 0);
    assert(fps > 0 && duration > 0);
    assert(density >= 0.0 && density <= 1.0);

    // ==============
    // World creation
    //
    // Create a grid of cells used to simulate the game of life.
    // The grid is a 2D array of chars, saved as an image at each iteration.
    // A buffer of the same size is used to store the next state of the grid.
    // ==============

    char grid[rows][cols];
    memset(grid, 0, rows * cols * sizeof(char));

    char buffer[rows][cols];
    memset(buffer, 0, rows * cols * sizeof(char));

    // initialize grid by randomly set cells to alive or dead
    unsigned int r = 0;
    unsigned int c = 0;
    for (r = 1; r < rows - 1; ++r)
    for (c = 1; c < cols - 1; ++c)
        grid[r][c] = (((float)rand() / RAND_MAX) < density) ? 255 : 0;

    // ==============
    // Update loop
    //
    // Iterate over cell neighbors to update its state
    // ==============

    const unsigned int iterations = fps * duration;
    unsigned int i = 0;
    for (; i < iterations; ++i)
    {
        // save current grid state as an image
        char filename[18];
        sprintf(filename, "images/%05d.bmp", i);
        stbi_flip_vertically_on_write(1);
        int success = stbi_write_bmp(filename, cols, rows, 1, grid);
        assert(success && "Cannot write image. Check if 'images' folder exists.");

        int neighbors = 0;
        int offset_r = 0;
        int offset_c = 0;

        // update cells (skip borders)
        for (r = 1; r < rows - 1; ++r)
        for (c = 1; c < cols - 1; ++c)
        {
            // count alive neighbors in a 3x3 grid (8 neighbors; skip center)
            neighbors = 0;
            for (offset_r = -1; offset_r <= 1; ++offset_r)
            for (offset_c = -1; offset_c <= 1; ++offset_c)
            {
                if (offset_r == 0 && offset_c == 0) continue;
                neighbors += grid[r + offset_r][c + offset_c] ? 1 : 0;
            }

            // apply game of life rules
            if (neighbors == 2) buffer[r][c] = grid[r][c] ? 128 : 0;    // keep state (already alive or dead)
            if (neighbors == 3) buffer[r][c] = grid[r][c] ? 128 : 255;  // keep state (already alive) or birth
            if (neighbors < 2 || neighbors > 3) buffer[r][c] = 0;       // death
        }

        // copy buffer to grid (ie. update grid state)
        memcpy(grid, buffer, rows * cols * sizeof(char));

        // clear buffer (ie. reset buffer state for next iteration)
        memset(buffer, 0, rows * cols * sizeof(char));
    }

    return 0;
}