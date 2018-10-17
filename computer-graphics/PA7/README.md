# PA7: Solar System

# Group Information
Our group is called Tessellation and the members are Natalie Arnold and Terra Williams.  The source code for the project is found here, in Natalie's repository.

# Dependencies, Building, and Running

## Dependency Instructions
For both of the operating systems to run this project installation of these three programs are required [GLEW](http://glew.sourceforge.net/), [GLM](http://glm.g-truc.net/0.9.7/index.html), and [SDL2](https://wiki.libsdl.org/Tutorials).

This project uses OpenGL 3.3. Some computers, such as virtual machines in the ECC, can not run this version. In in order to run OpenGL 2.7 follow the instructions at [Using OpenGL 2.7](https://github.com/HPC-Vis/computer-graphics/wiki/Using-OpenGL-2.7)

This project uses the Assimp library. To download and install [Assimp](http://www.assimp.org/).

This project uses the ImageMagick 7.0.8. To download, install, and build for linux, follow the instructions at [ImageMagick](https://linuxconfig.org/how-to-install-imagemagick-7-on-ubuntu-18-04-linux).

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
./SolarSystem
```

### Makefile Instructions
The makefile works as expected and must be updated with new files added in.

```bash
mkdir build
cd build
cp ../makefile .
make
./SolarSystem
```

## Ubuntu.cse.unr.edu
OpenGL 3.3 will run on the [ubuntu.cse.unr.edu](https://ubuntu.cse.unr.edu/) website. To do so follow the build instructions, but when running the Tutorial executable use this line to execute.
```bash
/usr/NX/scripts/vgl/vglrun ./SolarSystem
```
# Project Description
This project combines all of the elements that have been covered in our class so far including keyboard interaction, object movement, object loading, and texture loading.  We have created a solar system including the sun, planets (including Pluto), and the major moons of those planets that have them.


## Camera Controls

<table>
    <tr>
        <th>Action</th>
        <th>Control</th>
    </tr>
    <tr>
        <td>Focus on Sun</td>
        <td><kbd>0</kbd></td>
    </tr>
    <tr>
        <td>Focus on Mercury</td>
        <td><kbd>1</kbd></td>
    </tr>
    <tr>
        <td>Focus on Venus</td>
        <td><kbd>2</kbd></td>
    </tr>
    <tr>
        <td>Focus on Earth</td>
        <td><kbd>3</kbd></td>
    </tr>
    <tr>
        <td>Focus on Mars</td>
        <td><kbd>4</kbd></td>
    </tr>
    <tr>
        <td>Focus on Jupiter</td>
        <td><kbd>5</kbd></td>
    </tr>
    <tr>
        <td>Focus on Saturn</td>
        <td><kbd>6</kbd></td>
    </tr>
    <tr>
        <td>Focus on Uranus</td>
        <td><kbd>7</kbd></td>
    </tr>
    <tr>
        <td>Focus on Neptune</td>
        <td><kbd>8</kbd></td>
    </tr>
    <tr>
        <td>Focus on Pluto</td>
        <td><kbd>9</kbd></td>
    </tr>
    <tr>
        <td>Enable/Disable FPS Camera Mode</td>
        <td><kbd>m</kbd></td>
    </tr>
    <tr>
        <td>Reset View</td>
        <td><kbd>r</kbd></td>
    </tr>
    <tr>
        <td>Move Forward</td>
        <td><kbd>w</kbd></td>
    </tr>
    <tr>
        <td>Move Left</td>
        <td><kbd>a</kbd></td>
    </tr>
    <tr>
        <td>Move Right</td>
        <td><kbd>d</kbd></td>
    </tr>
    <tr>
        <td>Move Backward</td>
        <td><kbd>s</kbd></td>
    </tr>
    <tr>
        <td>Move Up</td>
        <td><kbd>SPACE</kbd></td>
    </tr>

</table>

## Simulation Controls

<table>
    <tr>
        <th>Action</th>
        <th>Control</th>
    </tr>
    <tr>
        <td>Toggle Scaled View</td>
        <td><kbd>l</kbd></td>
    </tr>
    <tr>
        <td>Increase Simulation Speed</td>
        <td>Hold <kbd>p</kbd></td>
    </tr>
    <tr>
        <td>Decrease Simulation Speed</td>
        <td>Hold <kbd>o</kbd></td>
    </tr>
    <tr>
        <td>Reset Simulation Speed</td>
        <td><kbd>q</kbd></td>
    </tr>

</table>

# Extra Credit
1) Rings on all of the gaseous planets
2) Adjustment of Simulation Speed
3) Switch Between Actual View and Scaled View
4) Pluto and Charon orbit their center of mass
5) Skybox centered on camera
6) FPS camera movement
