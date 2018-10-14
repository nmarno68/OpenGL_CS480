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

  cameraSpeed = .05;

  cameraPosition = glm::vec3(0.0, 8.0, -30.0);
  cameraTarget = glm::vec3(0.0, 0.0, 0.0);
  cameraUp = glm::vec3(0.0, 1.0, 0.0);
  cameraFront = glm::vec3(0.0, 0.0, 1.0);

  view = glm::lookAt( cameraPosition, cameraTarget , cameraUp);

  projection = glm::perspective( 45.0f, //the FoV typically 90 degrees is good which is what this is set to
                                 float(w)/float(h), //Aspect Ratio, so Circles stay Circular
                                 0.01f, //Distance to the near plane, normally a small value like this
                                 500.0f); //Distance to the far plane,
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

void Camera::MoveForward()
{
  cameraPosition -= cameraSpeed * (cameraPosition - cameraTarget);
  view = glm::lookAt(cameraPosition, cameraTarget, cameraUp);
}

void Camera::MoveBackward()
{
  cameraPosition += cameraSpeed * (cameraPosition - cameraTarget);
  view = glm::lookAt(cameraPosition, cameraTarget, cameraUp);
}

void Camera::MoveLeft()
{
  cameraPosition += cameraSpeed * (glm::cross((cameraPosition - cameraTarget)  ,cameraUp));
  view = glm::lookAt(cameraPosition, cameraTarget, cameraUp);
}

void Camera::MoveRight()
{
  cameraPosition -= cameraSpeed * (glm::cross((cameraPosition - cameraTarget)  ,cameraUp));
  view = glm::lookAt(cameraPosition, cameraTarget, cameraUp);
}

void Camera::MoveUp()
{
  cameraPosition += glm::vec3(0.0, 1.0, 0.0);
  view = glm::lookAt(cameraPosition, cameraTarget, cameraUp);
}

void Camera::MoveDown()
{
  cameraPosition -= glm::vec3(0.0, 1.0, 0.0);
  view = glm::lookAt(cameraPosition, cameraTarget, cameraUp);

}

void Camera::Target(glm::vec3 position, glm::vec3 target)
{

}