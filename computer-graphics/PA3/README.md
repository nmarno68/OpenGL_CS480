#PA3: Moons

# Dependencies, Building, and Running

## Dependency Instructions
For both of the operating systems to run this project installation of these three programs are required [GLEW](http://glew.sourceforge.net/), [GLM](http://glm.g-truc.net/0.9.7/index.html), and [SDL2](https://wiki.libsdl.org/Tutorials).

This project uses OpenGL 3.3. Some computers, such as virtual machines in the ECC, can not run this version. In in order to run OpenGL 2.7 follow the instructions at [Using OpenGL 2.7](https://github.com/HPC-Vis/computer-graphics/wiki/Using-OpenGL-2.7)

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
./Tutorial
```

### Makefile Instructions
The makefile works as expected and must be updated with new files added in.

```bash
mkdir build
cd build
cp ../makefile .
make
./Tutorial
```

## Ubuntu.cse.unr.edu
OpenGL 3.3 will run on the [ubuntu.cse.unr.edu](https://ubuntu.cse.unr.edu/) website. To do so follow the build instructions, but when running the Tutorial executable use this line to execute.
```bash
/usr/NX/scripts/vgl/vglrun ./Tutorial
```

# Project Description
This project builds on the concepts in PA1 and PA2. A moon object has been added to orbit the planet cube. User interactions are defined below.


## Cube Controls
This section is devided into two parts, one for the required controls and one for the conrols that were done
for funsies.

##Required Controls

<table>
    <tr>
        <th>Action</th>
        <th>Planet Control</th>
        <th>Moon Control</th>
    </tr>
    <tr>
        <td>Stop/Start Everything</td>
        <td>:a:</td>
        <td>:SHIFT: + :a:</td>
    </tr>
</table>

a - stop/start everything
f - stop/start orbit  
d - stop/start rotation  
s - reverse orbit and rotation    
w - reverse orbit  
e - reverse rotation  

### Mouse
Left Button - reverse rotation  
Right Button - reverse orbit  
Middle Button - stop/start orbit and rotation (direction of orbit and rotation is maintained, not reset)  

## Moon Controls

Left Arrow - stop/start orbit
Right Arrow - stop/start rotation
Down Arrow - reverse rotation
Up Arrow - reverse orbit


