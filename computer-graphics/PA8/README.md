# PA9: Lighting

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
./PA_Ugly
```

### Makefile Instructions
The makefile works as expected and must be updated with new files added in.

```bash
mkdir build
cd build
cp ../makefile .
make
./PA_Ugly
```

## Ubuntu.cse.unr.edu
OpenGL 3.3 will run on the [ubuntu.cse.unr.edu](https://ubuntu.cse.unr.edu/) website. To do so follow the build instructions, but when running the Tutorial executable use this line to execute.
```bash
/usr/NX/scripts/vgl/vglrun ./PA_Ugly
```
# Project Description
This project introduces lighting to the foundational object and texture loading accomplished in previous projects. Gourand and Phong lighting are demonstrated and controls are available for a spotlight, specular strength of objects, ambient strength and ambient color in the menus.

## Lighting Controls
Our lighting controls include:    
Switching between Phong and Gourand shading   
Adjusting ambient strength   
Adjusting ambient color (RGB)      
Turning a spotlight on and off    
Switching between a spotlight with a sharp edge and a spotlight with a soft edge    
Adjusting spotlight size     
Adjusting spotlight brightness    
Adjusting specular brightness on the cube, ball, cylinder, and board      
     
All of our lighting controls can be found in the menus labeled appropriately.   

## Cube Controls

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
        <td>Move Left</td>
        <td><kbd>A</kbd></td>
    </tr>
    <tr>
        <td>Move Back</td>
        <td><kbd>S</kbd></td>
    </tr>
    <tr>
        <td>Move Right</td>
        <td><kbd>D</kbd></td>
    </tr>
    <tr>
        <td>Jump</td>
        <td><kbd>SPACE</kbd></td>
    </tr>

</table>

## Extra Credit (?)
Two versions of a spotlight were implemented, one with a very sharp edge and one with a more faded edge. The two versions can be swapped around in the menu. Sliders controlling ambient color were also implemented.

## Comments
We weren't sure if the spotlight was broken on Gourand shading, but we made the assumption that since our objects have so few vertices that the spotlight was behaving appropriately for that shader, the light interpolating very poorly across our objects (especially the board). We also noted that for the ball Gourand and Phong had very similar effects due to our sphere having a large number of faces/vertices for such a small object. Unfortunately the menus were a little "clunky" but all controls available can be found on them.
