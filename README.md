# cpp-tetris

Tetris clone written in modern C++ with OpenGL.

---

### Goals

- Utilize modern C++11 (except shared_ptr/unique_ptr) and the standard libary
- Avoid use of Singleton pattern in favor of DI (dependency injection) where applicable
- Learn manual memory management through the use of new & delete
- Implement collision detection using bitwise manipulation (bitmask)
- Utilize googletest for unit testing and creation of test fixtures
- Gain experience debugging with gdb
- Use a minimal amount of textures

### Screenshot

![screenshot](/doc/screenshot-scaled.png)

### Dependencies
- **cmake** minimum 3.14
- **opengl** minimum 3.3
- **glfw3** minimum 3.2

### Instructions
**Linux**

1.  Download & install dependencies
2.  `$ git clone https://github.com/tony-redekop/cpp-tetris.git`
3.  `$ cd cpp-tetris`
4.  `$ mkdir build`
5.  `$ cd build`
6.  `$ cmake -G "Unix Makefiles" ..`
7.  `$ make`
8.  `$ ./test/demo`

**Windows**

Note: The project has not been tested on Windows. 

### Credit

Credit to [Joey de Vries](https://twitter.com/JoeyDeVriez) of [learnopengl.com](http://learnopengl.com) for providing the best resource on modern OpenGL on the internet and for providing a lot of the OpenGL boilerplate.
