
#include "engine.h"

Engine::Engine(string name, int width, int height)
{
  m_WINDOW_NAME = name;
  m_WINDOW_WIDTH = width;
  m_WINDOW_HEIGHT = height;
  m_FULLSCREEN = false;
}

Engine::Engine(string name)
{
  m_WINDOW_NAME = name;
  m_WINDOW_HEIGHT = 0;
  m_WINDOW_WIDTH = 0;
  m_FULLSCREEN = true;
}

Engine::~Engine()
{
  delete m_window;
  delete m_graphics;
  m_window = NULL;
  m_graphics = NULL;
}

bool Engine::Initialize()
{
  // Start a window
  m_window = new Window();
  if(!m_window->Initialize(m_WINDOW_NAME, &m_WINDOW_WIDTH, &m_WINDOW_HEIGHT))
  {
    printf("The window failed to initialize.\n");
    return false;
  }

  // Start the graphics
  m_graphics = new Graphics();
  if(!m_graphics->Initialize(m_WINDOW_WIDTH, m_WINDOW_HEIGHT))
  {
    printf("The graphics failed to initialize.\n");
    return false;
  }

  // Set the time
  m_currentTimeMillis = GetCurrentTimeMillis();

  // No errors
  return true;
}

void Engine::Run()
{
  m_running = true;

  while(m_running)
  {
    // Update the DT
    m_DT = getDT();

    // Check the keyboard input
    while(SDL_PollEvent(&m_event) != 0)
    {
      Keyboard();                                   //////////////////////PA2//////////////////////////
    }

    // Update and render the graphics
    m_graphics->Update(m_DT);
    m_newEvent = false;
    m_graphics->Render();

    // Swap to the Window
    m_window->Swap();
  }
}

void Engine::Keyboard()
{
  if(m_event.type == SDL_QUIT)
  {
    m_running = false;
  }
  else if (m_event.type == SDL_KEYDOWN)
  {
    bool shift = false;

    //Using the actual numerical value of SDLK_SHIFTs because directly comparing
    //Was not working for some reason
    if((m_event.key.keysym.mod == 4097) or ( m_event.key.keysym.mod == 4098))
    {
      shift = true;
    }
    // handle key down events here
    m_newEvent = true;
    //Handling keyboard events
    switch (m_event.key.keysym.sym) {
      case SDLK_ESCAPE:
        m_running = false;
        break;
      case SDLK_f:
        if(shift)
        {
          m_graphics->m_lil_cube->StopStartOrbit();
        }
        else
          m_graphics->m_cube->StopStartOrbit();
        break;
      case SDLK_d:
        if(shift)
        {
          m_graphics->m_lil_cube->StopStartRotation();
        }
        else
          m_graphics->m_cube->StopStartRotation();
        break;
      case SDLK_a:
        if(shift)
        {
          m_graphics->m_lil_cube->StopStartAll();
        }
        else
          m_graphics->m_cube->StopStartAll();
        break;
      case SDLK_s:
        if(shift)
        {
          m_graphics->m_lil_cube->ReverseAll();
        }
        else
          m_graphics->m_cube->ReverseAll();
        break;
      case SDLK_w:
        if(shift)
        {
          m_graphics->m_lil_cube->ReverseOrbit();
        }
        else
          m_graphics->m_cube->ReverseOrbit();
        break;
      case SDLK_e:
        if(shift)
        {
          m_graphics->m_lil_cube->ReverseRoatation();
        }
        else
          m_graphics->m_cube->ReverseRoatation();
        break;
      case SDLK_UP:
        m_graphics->m_lil_cube->ReverseOrbit();
        break;
      case SDLK_DOWN:
        m_graphics->m_lil_cube->ReverseRoatation();
        break;
      case SDLK_LEFT:
        m_graphics->m_lil_cube->StopStartOrbit();
        break;
      case SDLK_RIGHT:
        m_graphics->m_lil_cube->StopStartRotation();
        break;
      case SDLK_i:
        if(shift)
        {
          m_graphics->m_lil_cube->DecreaseSize();
        }
        else
          m_graphics->m_cube->DecreaseSize();
        break;
      case SDLK_o:
        if(shift)
        {
          m_graphics->m_lil_cube->IncreaseSize();
        }
        else
          m_graphics->m_cube->IncreaseSize();
        break;
      case SDLK_k:
        if(shift)
        {
          m_graphics->m_lil_cube->DecreaseOrbitSpeed();
        }
        else
          m_graphics->m_cube->DecreaseOrbitSpeed();
        break;
      case SDLK_l:
        if(shift)
        {
          m_graphics->m_lil_cube->IncreaseOrbitSpeed();
        }
        else
          m_graphics->m_cube->IncreaseOrbitSpeed();
        break;
      case SDLK_q:
        m_graphics->m_cube->ResetAll();
        m_graphics->m_lil_cube->ResetAll();
        break;
      case SDLK_n:
        if(shift)
        {
          m_graphics->m_lil_cube->DecreaseRoationSpeed();
        }
        else
          m_graphics->m_cube->DecreaseRoationSpeed();
        break;
      case SDLK_m:
        if(shift)
        {
          m_graphics->m_lil_cube->IncreaseRotationSpeed();
        }
        else
          m_graphics->m_cube->IncreaseRotationSpeed();
        break;
      case SDLK_g:
        if(shift)
        {
          m_graphics->m_lil_cube->DecreaseOrbitWidth();
        }
        else
          m_graphics->m_cube->DecreaseOrbitWidth();
        break;
      case SDLK_h:
        if(shift)
        {
          m_graphics->m_lil_cube->IncreaseOrbitWidth();
        }
        else
          m_graphics->m_cube->IncreaseOrbitWidth();
        break;
      case SDLK_v:
        if(shift)
        {
          m_graphics->m_lil_cube->DecreaseOrbitLength();
        }
        else
          m_graphics->m_cube->DecreaseOrbitLength();
        break;
      case SDLK_b:
        if(shift)
        {
          m_graphics->m_lil_cube->IncreaseOrbitLength();
        }
        else
          m_graphics->m_cube->IncreaseOrbitLength();
        break;
      default:
        break;
    }
  }
  //Handling mouse events
  else if (m_event.type == SDL_MOUSEBUTTONDOWN)
  {
    m_newEvent = true;
    switch (m_event.button.button) {
      case SDL_BUTTON_LEFT:
        m_graphics->m_cube->ReverseRoatation();
        break;
      case SDL_BUTTON_MIDDLE:
        m_graphics->m_cube->StopStartAll();
        break;
      case SDL_BUTTON_RIGHT:
        m_graphics->m_cube->ReverseOrbit();
        break;
      default:
        break;
    }
  }
}

unsigned int Engine::getDT()
{
  long long TimeNowMillis = GetCurrentTimeMillis();
  assert(TimeNowMillis >= m_currentTimeMillis);
  unsigned int DeltaTimeMillis = (unsigned int)(TimeNowMillis - m_currentTimeMillis);
  m_currentTimeMillis = TimeNowMillis;
  return DeltaTimeMillis;
}

long long Engine::GetCurrentTimeMillis()
{
  timeval t;
  gettimeofday(&t, NULL);
  long long ret = t.tv_sec * 1000 + t.tv_usec / 1000;
  return ret;
}
