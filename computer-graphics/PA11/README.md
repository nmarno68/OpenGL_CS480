# PA11: Wizard Duel

# Group Information
Our group is called Tessellation and the members are Natalie Arnold and Terra Williams.  The source code for the project is found here, in Natalie's repository.

# Dependencies, Building, and Running

## Dependency Instructions
For both of the operating systems to run this project installation of these three programs are required [GLEW](http://glew.sourceforge.net/), [GLM](http://glm.g-truc.net/0.9.7/index.html), and [SDL2](https://wiki.libsdl.org/Tutorials).

This project uses OpenGL 3.3. Some computers, such as virtual machines in the ECC, can not run this version. In in order to run OpenGL 2.7 follow the instructions at [Using OpenGL 2.7](https://github.com/HPC-Vis/computer-graphics/wiki/Using-OpenGL-2.7)

This project uses the Assimp library. To download and install [Assimp](http://www.assimp.org/).

This project uses the ImageMagick 7.0.8. To download, install, and build for linux, follow the instructions at [ImageMagick](https://linuxconfig.org/how-to-install-imagemagick-7-on-ubuntu-18-04-linux).

This project uses the Bullet3 library. Download and install on Linux with

```bash
sudo apt-get install libbullet-dev
```

### Ubuntu/Linux
```bash
sudo apt-get install libglew-dev libglm-dev libsdl2-dev
```

### Mac OSX
Installation of brew is suggested to easily install the libs. Ensure that the latest version of the Developer Tools is installed.
```bash
brew install glew glm sdl2
```

## Building and Running
To build this project there are two options. One is to use CMake which makes including new libraries easier, and handles new files added automatically to the src and include directory. CMake is a small new learning curve but makes things easier in the future.
The second option is to use the provided Makefile which is used as usual.

Running the make in a separate directory will allow easy cleanup of the build data, and an easy way to prevent unnecessary data to be added to the git repository.

### CMake Instructions
The building of the project is done using CMake, installation with apt-get or brew may be necessary. Later use with CMake and Shader files will be require the copy of a directory where those files are stored (ex. shaders). To do this in the ```add_custom_target``` function place
```cmake
COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/shaders/ ${CMAKE_CURRENT_BINARY_DIR}/shaders
```

```bash
mkdir build
cd build
cmake ..
make
./Wizard_Duel
```

### Makefile Instructions
The makefile works as expected and must be updated with new files added in.

```bash
mkdir build
cd build
cp ../makefile .
make
./Wizard_Duel
```

## Ubuntu.cse.unr.edu
OpenGL 3.3 will run on the [ubuntu.cse.unr.edu](https://ubuntu.cse.unr.edu/) website. To do so follow the build instructions, but when running the Tutorial executable use this line to execute.
```bash
/usr/NX/scripts/vgl/vglrun ./Wizard_Duel
```
# Project Description
We created a first-person shooter that takes place as a duel between two wizards. The player character can move around the map and will be chased by the enemy wizard. The player and the enemy can both shoot spells which will damage the other. 

## Player Controls

<table>
    <tr>
        <th>Action</th>
        <th>Control</th>
    </tr>
    <tr>
        <td>Move Forward</td>
        <td><kbd>W</kbd></td>
    </tr>
    <tr>
        <td>Strafe Left</td>
        <td><kbd>A</kbd></td>
    </tr>
    <tr>
        <td>Strafe Right</td>
        <td><kbd>D</kbd></td>
    </tr>
    <tr>
        <td>Move Backward</td>
        <td><kbd>S</kbd></td>
    </tr>
    <tr>
        <td>Cast Spell</td>
        <td><kbd>E</kbd></td>
    </tr>
</table>

