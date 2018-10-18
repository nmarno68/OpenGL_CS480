#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <string>
#include <GL/glew.h>
#include <iostream>
using namespace std;

class Window
{
  public:
    Window();
    ~Window();
    bool Initialize(const string &name, int* width, int* height);
    void Swap();
    SDL_Window* GetSDLWindow();
    SDL_GLContext GetContext();

  private:
    SDL_Window* gWindow;
    SDL_GLContext gContext;
    SDL_Renderer* renderer;
};

#endif /* WINDOW_H */
