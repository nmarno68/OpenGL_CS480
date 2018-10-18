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

  cameraSpeed = .5;

  cameraPosition = glm::vec3(0.0, 0.0, 35.0);
  cameraTarget = glm::vec3(0.0, 0.0, 0.0);
  cameraUp = glm::vec3(0.0, 1.0, 0.0);
  cameraFront = glm::vec3(0.0, 0.0, -1.0);

  view = glm::lookAt( cameraPosition, cameraPosition + cameraFront , cameraUp);

  projection = glm::perspective( 45.0f, //the FoV typically 90 degrees is good which is what this is set to
                                 float(w)/float(h), //Aspect Ratio, so Circles stay Circular
                                 0.01f, //Distance to the near plane, normally a small value like this
                                 900.0f); //Distance to the far plane,

  enableMouse = 0;
  last_x = 1000;         //set to middle of screen - tweak it
  last_y = 500;
  pitch = 0;
  yaw = -90;
  firstMouseMovement = 1;

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

  yaw   += xpos;
  pitch += -ypos;

  if(pitch > 89.0f)
    pitch = 89.0f;
  if(pitch < -89.0f)
    pitch = -89.0f;

  glm::vec3 direction;
  direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  direction.y = sin(glm::radians(pitch));
  direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  cameraFront = glm::normalize(direction);

  // Also re-calculate the Right and Up vector
  glm::vec3 Right;
  Right = glm::normalize(glm::cross(cameraFront, glm::vec3(0.0, 1.0, 0.0)));
  cameraUp = glm::normalize(glm::cross(Right, cameraFront));

  view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
}

void Camera::EnableMouse()
{
  enableMouse = !enableMouse;
  last_x = 1000;
  last_y = 500;
  pitch = 0;
  yaw = 0;

}

void Camera::Reset()
{
  cameraPosition = glm::vec3(0.0, 0.0, 35.0);
  cameraTarget = glm::vec3(0.0, 0.0, 0.0);
  cameraUp = glm::vec3(0.0, 1.0, 0.0);
  cameraFront = glm::vec3(0.0, 0.0, -1.0);
  firstMouseMovement = true;

  view = glm::lookAt( cameraPosition, cameraPosition + cameraFront , cameraUp);
  pitch = 0;
  yaw = -90;

}

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