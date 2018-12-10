#include "camera.h"

Camera::Camera()
{

}

Camera::~Camera()
{

}

bool Camera::Initialize(int w, int h)
{
  //--Init the view and projection matrices
  //  if you will be having a moving camera the view matrix will need to more dynamic
  //  ...Like you should update it before you render more dynamic 
  //  for this project having them static will be fine

  cameraSpeed = .3;

  cameraPosition = glm::vec3(1.0, 1.0, 0.0);
  cameraTarget = glm::vec3(0.0, 0.0, 0.0);
  cameraUp = glm::vec3(0.0, 1.0, 0.0);
  cameraFront = glm::vec3(1.0, 0.0, 0.0);

  //The target of the camera for the entirety of the program is simply directly
  //in front of it
  view = glm::lookAt( cameraPosition, cameraPosition + cameraFront , cameraUp);

  projection = glm::perspective( 45.0f, //the FoV typically 90 degrees is good which is what this is set to
                                 float(w)/float(h), //Aspect Ratio, so Circles stay Circular
                                 0.01f, //Distance to the near plane, normally a small value like this
                                 900.0f); //Distance to the far plane,

  enableMouse = 0;        //mouse motion flag
  last_x = 1000;         //set mouse to middle of screen
  last_y = 500;
  pitch = 0;
  yaw = 0;
  firstMouseMovement = 1; //flag to start the mouse in the center of the screen (no sudden jerks)

  return true;
}

glm::mat4 Camera::GetProjection()
{
  return projection;
}

glm::mat4 Camera::GetView()
{
  return view;
}

//returns the camera position without direction information
glm::mat4 Camera::GetLocation()
{
  return glm::translate(glm::mat4(1.0f), cameraPosition);
}

void Camera::MoveForward()
{
  cameraPosition += cameraSpeed * cameraFront;
  view = glm::lookAt( cameraPosition, cameraPosition + cameraFront , cameraUp);
}

void Camera::MoveBackward()
{
  cameraPosition -= cameraSpeed * cameraFront;
  view = glm::lookAt( cameraPosition, cameraPosition + cameraFront , cameraUp);
}

void Camera::MoveLeft()
{
  cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
  view = glm::lookAt( cameraPosition, cameraPosition + cameraFront , cameraUp);
}

void Camera::MoveRight()
{
  cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
  view = glm::lookAt( cameraPosition, cameraPosition + cameraFront , cameraUp);
}

void Camera::MoveUp()
{
  cameraPosition += glm::vec3(0.0, 1 * cameraSpeed, 0.0);
  view =  view = glm::lookAt( cameraPosition, cameraPosition + cameraFront , cameraUp);
}

//FPS style camera look around
void Camera::MouseMovement(double xpos, double ypos)
{

  if(firstMouseMovement)
  {
    last_x = xpos;
    last_y = ypos;
    firstMouseMovement = false;
  }

  float sensitivity = 0.05;
  xpos *= sensitivity;
  ypos *= sensitivity;

  //SDL relative mouse movement automatically calculates change in x and change in y
  //theres not need to calculate the difference ourselves
  yaw   += xpos;
  pitch += -ypos;

  //limiting head movement no frontflips or backflips :(
  if(pitch > 89.0f)
    pitch = 89.0f;
  if(pitch < -89.0f)
    pitch = -89.0f;

  //mapping the 2D x-y coords of the mouse to 3D world
  //with all of the fun pitch and yaw trig
  glm::vec3 direction;
  direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  direction.y = sin(glm::radians(pitch));
  direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  cameraFront = glm::normalize(direction);

  // Also re-calculate the Right and Up vector of the camera coord system
  glm::vec3 Right;
  Right = glm::normalize(glm::cross(cameraFront, glm::vec3(0.0, 1.0, 0.0)));
  cameraUp = glm::normalize(glm::cross(Right, cameraFront));

  view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
}

//set mouse information when entering FPS camera mode
void Camera::EnableMouse()
{
  enableMouse = !enableMouse;
  last_x = 1000;
  last_y = 500;
  pitch = 0;
  yaw = 0;

}

//resets camera info (for planet view/ top view jumping
void Camera::Reset()
{
  cameraPosition = glm::vec3(1.0, 1.0, 0.0);
  cameraTarget = glm::vec3(0.0, 0.0, 0.0);
  cameraUp = glm::vec3(0.0, 1.0, 0.0);
  cameraFront = glm::vec3(1.0, -.80, 0.0);
  firstMouseMovement = true;

  view = glm::lookAt( cameraPosition, cameraPosition + cameraFront , cameraUp);
  pitch = 0;
  yaw = 0;

}

//jump to specified planet location and offset from the location
//(further away from jupiter than pluto
void Camera::PlanetView(glm::vec3 planet_pos, glm::vec3 offset)
{
  cameraPosition = planet_pos + offset;
  view = glm::lookAt( cameraPosition, cameraPosition + cameraFront , cameraUp);
}

void Camera::TopView()
{
  cameraPosition = glm::vec3(0.0, 400, 0.0);
  cameraFront = glm::vec3(0.0, -1.0, 0.000001);

  glm::vec3 Right;
  Right = glm::normalize(glm::cross(cameraFront, glm::vec3(0.0, 1.0, 0.0)));
  cameraUp = glm::normalize(glm::cross(Right, cameraFront));

  view = glm::lookAt( cameraPosition, cameraPosition + cameraFront , cameraUp);
}

//Resets the camera and mouse information to avoid jerking motions while jumping views
void Camera::FaceFront()
{
  last_x = 1000;
  last_y = 500;
  pitch = 0;
  yaw = -90;

  cameraFront = glm::vec3(0.0, 0.0, -1.0);
  glm::vec3 Right;
  Right = glm::normalize(glm::cross(cameraFront, glm::vec3(0.0, 1.0, 0.0)));
  cameraUp = glm::normalize(glm::cross(Right, cameraFront));
}

glm::mat4 Camera::GetLocationSkybox(int skybox)
{
  glm::mat4 result;
  switch(skybox) {
    case 1:
      result = glm::translate(glm::mat4(1.0f), cameraPosition + glm::vec3(0.0, -10.0, 0.0));
      break;
    case 2:
      result = glm::translate(glm::mat4(1.0f), cameraPosition + glm::vec3(0.0, 0.0, 0.0));
      break;
  }
  return result;
}
