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
    void MouseMovement(double xpos, double ypos);
    void MoveUp();
    void EnableMouse();
    void Reset();
    glm::mat4 GetLocation();
    void PlanetView(glm::vec3 planet_pos, glm::vec3 offset);
    void TopView();
    void FaceFront();
    glm::mat4 GetLocationSkybox(int skybox);
    glm::vec3 RetrieveForceForward();
    void menuView(unsigned int time);

    glm::vec3 cameraPosition;
    glm::vec3 cameraTarget;
    glm::vec3 cameraUp;
    glm::vec3 cameraFront;  //our target will always be just in front of the camera position
    bool enableMouse;
    bool firstMouseMovement;
    float cameraSpeed;

  private:
    glm::mat4 projection;
    glm::mat4 view;

    double camera_angle;

    double last_x, last_y, pitch, yaw;


};

#endif /* CAMERA_H */
