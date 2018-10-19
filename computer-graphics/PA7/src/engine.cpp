
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
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();
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

  //Menu Initialization
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void) io;

  ImGui_ImplSDL2_InitForOpenGL(m_window->GetSDLWindow(), m_window->GetContext());
  ImGui_ImplOpenGL3_Init("#version 330");
  ImGui::StyleColorsClassic();


  submenu = 0;
  subsubmenu = 0;


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

    //Menu setup for frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(m_window->GetSDLWindow());
    ImGui::NewFrame();

    // Check the keyboard input
    while(SDL_PollEvent(&m_event) != 0)
    {
      ImGui_ImplSDL2_ProcessEvent(&m_event);
      Keyboard();
    }


    //A ton of menu code


    {

          ImGui::Begin("Camera Controls");

          ImGui::Text("Enable/Disable FPS Camera Mode"); ImGui::SameLine(280); ImGui::Text("E");

          ImGui::Text("Move Forward"); ImGui::SameLine(280); ImGui::Text("W");

          ImGui::Text("Move Left"); ImGui::SameLine(280); ImGui::Text("A");

          ImGui::Text("Move Back"); ImGui::SameLine(280); ImGui::Text("S");

          ImGui::Text("Move Right"); ImGui::SameLine(280); ImGui::Text("D");

          ImGui::Text("Move Up"); ImGui::SameLine(253); ImGui::Text("SPACE");

          if (ImGui::Button("Top View")) {

            if(!m_graphics->top_view) {
              m_graphics->m_camera->TopView();
              m_graphics->planet_view = false;
              m_graphics->target_planet = -1;
              m_graphics->top_view = true;
            }
            else
            {
              m_graphics->m_camera->Reset();
              m_graphics->top_view = false;
              m_graphics->planet_view = false;
              m_graphics->target_planet = -1;

            }
          }

          if (ImGui::Button("Scaled View"))
          {
            if(m_graphics->scaled_view)
            {
              m_graphics->actualView();
            }
            else {
              m_graphics->scaledView();
            }
            m_graphics->scaled_view = !m_graphics->scaled_view;
          }

          ImGui::End();


          //simulation submenu

          ImGui::Begin("Simulation Controls");
          ImGui::Text("Increase Sim Speed");
          ImGui::SameLine(200);
          ImGui::Text("Hold P");

          ImGui::Text("Decrease Sim Speed");
          ImGui::SameLine(200);
          ImGui::Text("Hold O");

          if(ImGui::Button("Reset Sim Speed"))
          {
            m_graphics->resetAll();
          }


          ImGui::End();

          ImGui::Begin("Planet View");

            if(ImGui::Button("Sun"))
            {
              m_graphics->m_camera->FaceFront();
              m_graphics->planet_view = true;
              m_graphics->target_planet = 0;
              m_graphics->top_view = false;
            }
            ImGui::SameLine(200);
            ImGui::Text("0");

            if(ImGui::Button("Mercury"))
            {
              m_graphics->m_camera->FaceFront();
              m_graphics->planet_view = true;
              m_graphics->target_planet = 1;
              m_graphics->top_view = false;
            }
            ImGui::SameLine(200);
            ImGui::Text("1");

            if(ImGui::Button("Venus"))
            {
              m_graphics->m_camera->FaceFront();
              m_graphics->planet_view = true;
              m_graphics->target_planet = 2;
              m_graphics->top_view = false;
            }
            ImGui::SameLine(200);
            ImGui::Text("2");

            if(ImGui::Button("Earth"))
            {
              m_graphics->m_camera->FaceFront();
              m_graphics->planet_view = true;
              m_graphics->target_planet = 3;
              m_graphics->top_view = false;
            }
            ImGui::SameLine(200);
            ImGui::Text("3");

            if(ImGui::Button("Mars"))
            {
              m_graphics->m_camera->FaceFront();
              m_graphics->planet_view = true;
              m_graphics->target_planet = 4;
              m_graphics->top_view = false;
            }
            ImGui::SameLine(200);
            ImGui::Text("4");

            if(ImGui::Button("Jupiter"))
            {
              m_graphics->m_camera->FaceFront();
              m_graphics->planet_view = true;
              m_graphics->target_planet = 5;
              m_graphics->top_view = false;
            }
            ImGui::SameLine(200);
            ImGui::Text("5");

            if(ImGui::Button("Saturn"))
            {
              m_graphics->m_camera->FaceFront();
              m_graphics->planet_view = true;
              m_graphics->target_planet = 6;
              m_graphics->top_view = false;
            }
            ImGui::SameLine(200);
            ImGui::Text("6");

            if(ImGui::Button("Uranus"))
            {
              m_graphics->m_camera->FaceFront();
              m_graphics->planet_view = true;
              m_graphics->target_planet = 7;
              m_graphics->top_view = false;
            }
            ImGui::SameLine(200);
            ImGui::Text("7");

            if(ImGui::Button("Neptune"))
            {
              m_graphics->m_camera->FaceFront();
              m_graphics->planet_view = true;
              m_graphics->target_planet = 8;
              m_graphics->top_view = false;
            }
            ImGui::SameLine(200);
            ImGui::Text("8");

            if(ImGui::Button("Pluto and Charon"))
            {
              m_graphics->m_camera->FaceFront();
              m_graphics->planet_view = true;
              m_graphics->target_planet = 9;
              m_graphics->top_view = false;
            }
            ImGui::SameLine(200);
            ImGui::Text("9");

          ImGui::End();
    }


    // Update and render the graphics
    m_graphics->Update(m_DT);
    m_newEvent = false;

    m_graphics->Render();

    //Render menus
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

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
    if((m_event.key.keysym.mod == KMOD_LSHIFT) or ( m_event.key.keysym.mod == KMOD_RSHIFT))
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

      case SDLK_w:
        m_graphics->planet_view = false;
        m_graphics->target_planet = -1;
        m_graphics->m_camera->MoveForward();
        break;

      case SDLK_s:
        m_graphics->planet_view = false;
        m_graphics->target_planet = -1;
        m_graphics->m_camera->MoveBackward();
        break;

      case SDLK_a:
        m_graphics->planet_view = false;
        m_graphics->target_planet = -1;
        m_graphics->m_camera->MoveLeft();
        break;

      case SDLK_d:
        m_graphics->planet_view = false;
        m_graphics->target_planet = -1;
        m_graphics->m_camera->MoveRight();
        break;

      case SDLK_p:
        m_graphics->IncSimSpeed();
        break;

      case SDLK_o:
        m_graphics->DecSimSpeed();
        break;

      case SDLK_SPACE:
        m_graphics->planet_view = false;
        m_graphics->target_planet = -1;
        m_graphics->m_camera->MoveUp();
        break;

      case SDLK_e:
        if(m_graphics->m_camera->enableMouse)
        {
          SDL_SetRelativeMouseMode((SDL_bool) 0);
          m_graphics->m_camera->enableMouse = 0;
        }
        else
        {
          SDL_SetRelativeMouseMode((SDL_bool) 1);
          m_graphics->m_camera->enableMouse = 1;
        }
        break;


      //Planet View Mode
      //follow sun
      case SDLK_0:
        m_graphics->m_camera->FaceFront();
        m_graphics->planet_view = true;
        m_graphics->target_planet = 0;
        m_graphics->top_view = false;
        break;

      case SDLK_1:
        m_graphics->m_camera->FaceFront();
        m_graphics->planet_view = true;
        m_graphics->target_planet = 1;
        m_graphics->top_view = false;
        break;

      case SDLK_2:
        m_graphics->m_camera->FaceFront();
        m_graphics->planet_view = true;
        m_graphics->target_planet = 2;
        m_graphics->top_view = false;
        break;

      case SDLK_3:
        m_graphics->m_camera->FaceFront();
        m_graphics->planet_view = true;
        m_graphics->target_planet = 3;
        m_graphics->top_view = false;
        break;

      case SDLK_4:
        m_graphics->m_camera->FaceFront();
        m_graphics->planet_view = true;
        m_graphics->target_planet = 4;
        m_graphics->top_view = false;
        break;

      case SDLK_5:
        m_graphics->m_camera->FaceFront();
        m_graphics->planet_view = true;
        m_graphics->target_planet = 5;
        m_graphics->top_view = false;
        break;

      case SDLK_6:
        m_graphics->m_camera->FaceFront();
        m_graphics->planet_view = true;
        m_graphics->target_planet = 6;
        m_graphics->top_view = false;
        break;

      case SDLK_7:
        m_graphics->m_camera->FaceFront();
        m_graphics->planet_view = true;
        m_graphics->target_planet = 7;
        m_graphics->top_view = false;
        break;

      case SDLK_8:
        m_graphics->m_camera->FaceFront();
        m_graphics->planet_view = true;
        m_graphics->target_planet = 8;
        m_graphics->top_view = false;
        break;

      case SDLK_9:
        m_graphics->m_camera->FaceFront();
        m_graphics->planet_view = true;
        m_graphics->target_planet = 9;
        m_graphics->top_view = false;
        break;
    }
  }

  else if (m_event.type == SDL_MOUSEMOTION )
  {
    if(m_graphics->m_camera->enableMouse)
    {
      int x, y;
      x = m_event.motion.xrel;
      y = m_event.motion.yrel;
      m_graphics->m_camera->MouseMovement(x, y);
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

