#ifndef CAMERA_H
#define CAMERA_H

#include "graphics_headers.h"

class Camera
{
  public:
    Camera();
    ~Camera();
    bool Initialize(int w, int h);
    glm::mat4 GetProjection();
    glm::mat4 GetView();
    void MoveForward();
    void MoveBackward();
    void MoveLeft();
    void MoveRight();
    void MoveUp();
    void MoveDown();
    void Reset();

    glm::vec3 cameraPosition;
    glm::vec3 cameraTarget;
    glm::vec3 cameraUp;
    glm::vec3 cameraFront;
  private:
    glm::mat4 projection;
    glm::mat4 view;


    float cameraSpeed;
};

#endif /* CAMERA_H */
