# PuyoPuyo
Simple Puyo Puyo game in C++ with SDL

## Dependencies

- [Git][]
- C Compiler (gcc, ...)
- [CMake][]
- [SDL2][SDL] library
- [SDL2_gfx][] library

**On Debian/Ubuntu based distributions, use the following command:**

```sh
sudo apt install git build-essential pkg-config cmake cmake-data libsdl2-dev libsdl2-gfx-dev
```

**Optional packages:**

- [SDL2_image][] library
- [SDL2_ttf][] library
- [SDL2_net][] library
- [SDL2_mixer][] library

```sh
sudo apt install libsdl2-image-dev libsdl2-ttf-dev libsdl2-net-dev libsdl2-mixer-dev
```

## Bulld instructions

```sh
# Clone git repo
git clone https://github.com/NunoRibeiro185/PuyoPuyo.git
cd PuyoPuyo

# Create a build folder
mkdir build
cd build

# Build
cmake ..
make

# Run
./PuyoPuyo
```


## How to play
A - Move Left
D - Mode Right
S - Move Down Faster
(Can also use arrow keys)
                           ___
E - Turn 90 Degrees Right     |
                              V
                            ___
Q - Turn 90 Degrees Left   |  
                           V

ESC - Quit
P - Pause

ENTER after Game Over - Restart

## Notes

This was the first time I used SDL and C++ to make a game. There were a lot of mistakes that I made when
starting this exercise and using the SDL library that if the exercise were to be repeated I would be much better at. 
It was a very nice and interesting experience and fun to be a part of. 
My main focus was the criteria presented in the document as I knew I would be tight on time
because I couldn't spend many hours daily working on this exercise. 

Some bugs that need fixing:
- Some slow downs here and there that could be fixed with some optimization
- Moving with arrow keys is much faster
- Falling faster feature when player isn't in control isn't fully functional

For this exercise I stuck to the things that were asked for the sake of brevity
However here are some thing that could be added with more time/if wanted:
- Score
- Pause Menu
- Game Over Screen