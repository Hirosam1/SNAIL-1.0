#include "GameEngine.hpp"

class CameraMovement : public Behaviour{

    enum CameraControlls{
        MOVE_FORWARDS,
        MOVE_BACKWARDS,
        MOVE_UPWARDS,
        MOVE_DOWNWARDS,
        MOVE_LEFT,
        MOVE_RIGHT
    };
    Camera* main_camera;
    float yawn = -90;
    float pitch = 0;
    const float sensitivity = 0.05f;
    bool first_mouse = true;
    float lastX;
    float lastY;
    InputHandler ih = InputHandler(6);
    float velocity = 2.0f;
    void CalculateYawnPitch(){
        if(first_mouse && main_window->cursor_info.x_pos >= 0){
            first_mouse = false;
            lastX = main_window->cursor_info.x_pos;
            lastY = main_window->cursor_info.y_pos;
        }
        float xoffset = main_window->cursor_info.x_pos - lastX;
        float yoffset = lastY - main_window->cursor_info.y_pos;
        lastX = main_window->cursor_info.x_pos;
        lastY = main_window->cursor_info.y_pos;
        yawn += xoffset * sensitivity;
        yawn = yawn > 359 ? yawn - 360 : yawn < -359 ? yawn + 359 : yawn;
        pitch += yoffset * sensitivity;
        if(pitch > 89.0f){
            pitch = 89.0f;
        }else if(pitch < -89.0f){
            pitch = -89.0f;
        }

    }
    public:
        void Begin() override{
            glfwSetInputMode(main_window->window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
            ih.AddCommandBack(GLFW_KEY_W,GLFW_PRESS,MOVE_FORWARDS);
            ih.AddCommandBack(GLFW_KEY_S,GLFW_PRESS,MOVE_BACKWARDS);
            ih.AddCommandBack(GLFW_KEY_Q,GLFW_PRESS,MOVE_UPWARDS);
            ih.AddCommandBack(GLFW_KEY_E,GLFW_PRESS,MOVE_DOWNWARDS);
            ih.AddCommandBack(GLFW_KEY_A,GLFW_PRESS,MOVE_LEFT);
            ih.AddCommandBack(GLFW_KEY_D,GLFW_PRESS,MOVE_RIGHT);
            for(Object* obj : main_window->object_list){
                if(obj->object_name == "Main Camera"){
                    main_camera = dynamic_cast<Camera*>(obj);
                }
            }

        }
        void Update() override{
            CalculateYawnPitch();
            ih.HandleInput();
            Vector3 direction(cos(ToRadians(pitch))*cos(ToRadians(yawn)),sin(ToRadians(pitch)),cos(ToRadians(pitch))*sin(ToRadians(yawn)));
            Vector3 move_pos;
            if(ih.GetInputInfo(MOVE_FORWARDS).was_activated){
                move_pos += main_camera->Front();
            }
            if(ih.GetInputInfo(MOVE_BACKWARDS).was_activated){
                move_pos -= main_camera->Front();
            }
            if(ih.GetInputInfo(MOVE_LEFT).was_activated){
                move_pos -= Normalize(main_camera->Front().Cross(main_camera->Up()));
            }
            if(ih.GetInputInfo(MOVE_RIGHT).was_activated){
                move_pos += Normalize(main_camera->Front().Cross(main_camera->Up()));
            }
            if(ih.GetInputInfo(MOVE_UPWARDS).was_activated){
                move_pos += main_camera->Up();
            }
            if(ih.GetInputInfo(MOVE_DOWNWARDS).was_activated){
                move_pos -= main_camera->Up();
            }
            main_camera->MoveCameraPos(Normalize(move_pos) * Time::deltaTime * velocity);
            main_camera->SetCameraDir(direction);
        }
};