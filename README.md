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

- Some bugs need fixing