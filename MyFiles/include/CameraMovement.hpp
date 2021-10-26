#pragma once
#include "GameEngine.hpp"

class CameraMovement : public Behavior{

    enum CameraControlls{
        MOVE_FORWARDS,
        MOVE_BACKWARDS,
        MOVE_UPWARDS,
        MOVE_DOWNWARDS,
        MOVE_LEFT,
        MOVE_RIGHT,
        SWITCH_SCENE,
        SET_CURSOR
    };
    Camera* main_camera = nullptr;
    float yawn = 90;
    float pitch = 0;
    const float sensitivity = 0.05f;
    bool first_mouse = true;
    float lastX;
    float lastY;
    InputHandler ih = InputHandler(8);
    float velocity = 2.0f;
    bool cursor_hidden;
    std::string scene1 = "Scene1.sscene.json";
    std::string scene2 = "Scene2.sscene.json";
    void CalculateYawnPitch(){
        if(first_mouse && Window::main_window->cursor_info.x_pos >= 0){
            first_mouse = false;
            lastX = Window::main_window->cursor_info.x_pos;
            lastY = Window::main_window->cursor_info.y_pos;
        }
        float xoffset = Window::main_window->cursor_info.x_pos - lastX;
        float yoffset = lastY - Window::main_window->cursor_info.y_pos;
        lastX = Window::main_window->cursor_info.x_pos;
        lastY = Window::main_window->cursor_info.y_pos;
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
            cursor_hidden = true;
            glfwSetInputMode(Window::main_window->window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
            ih.AddCommandBack(GLFW_KEY_W,PressType::KEY_HOLD,MOVE_FORWARDS);
            ih.AddCommandBack(GLFW_KEY_S,PressType::KEY_HOLD,MOVE_BACKWARDS);
            ih.AddCommandBack(GLFW_KEY_Q,PressType::KEY_HOLD,MOVE_UPWARDS);
            ih.AddCommandBack(GLFW_KEY_E,PressType::KEY_HOLD,MOVE_DOWNWARDS);
            ih.AddCommandBack(GLFW_KEY_A,PressType::KEY_HOLD,MOVE_LEFT);
            ih.AddCommandBack(GLFW_KEY_D,PressType::KEY_HOLD,MOVE_RIGHT);
            ih.AddCommandBack(GLFW_KEY_X,PressType::KEY_PRESS, SWITCH_SCENE);
            ih.AddCommandBack(GLFW_KEY_ESCAPE,PressType::KEY_PRESS,SET_CURSOR);
            main_camera = game_object->GetComponent<Camera>();
            yawn *= main_camera->Front().z;

        }
        void UpdateCamera(){
            Vector3 direction(cos(Math::ToRadians(pitch))*cos(Math::ToRadians(yawn)),sin(Math::ToRadians(pitch)),cos(Math::ToRadians(pitch))*sin(Math::ToRadians(yawn)));
            Vector3 move_pos;
                if(ih.GetInputInfo(MOVE_FORWARDS).was_activated){
                    move_pos += main_camera->Front();
                }
                if(ih.GetInputInfo(MOVE_BACKWARDS).was_activated){
                    move_pos -= main_camera->Front();
                }
                if(ih.GetInputInfo(MOVE_LEFT).was_activated){
                    move_pos -= Vector::Normalize(main_camera->Front().Cross(main_camera->Up()));
                }
                if(ih.GetInputInfo(MOVE_RIGHT).was_activated){
                    move_pos += Vector::Normalize(main_camera->Front().Cross(main_camera->Up()));
                }
                if(ih.GetInputInfo(MOVE_UPWARDS).was_activated){
                    move_pos += main_camera->Up();
                }
                if(ih.GetInputInfo(MOVE_DOWNWARDS).was_activated){
                    move_pos -= main_camera->Up();
                }
            main_camera->game_object->transform->Translate(Vector::Normalize(move_pos) * velocity * Time::deltaTime);
            main_camera->LookAt(direction, Vector3(0.0,1.0,0.0));
        }
        void Update() override{
            if(cursor_hidden){
                CalculateYawnPitch();
                UpdateCamera();
            }
            ih.HandleInput();
            if(ih.GetInputInfo(SWITCH_SCENE).was_activated){
                if(Scene::active_scene->scene_path == scene1){
                    Scene::LoadScene(scene2);
                }else{
                    Scene::LoadScene(scene1);
                }
            }
            
            if(ih.GetInputInfo(SET_CURSOR).was_activated){
                if(cursor_hidden){
                    cursor_hidden = false;
                    glfwSetInputMode(Window::main_window->window,GLFW_CURSOR,GLFW_CURSOR_NORMAL);
                }else{
                    cursor_hidden = true;
                    lastX = Window::main_window->cursor_info.x_pos;
                    lastY = Window::main_window->cursor_info.y_pos;
                    glfwSetInputMode(Window::main_window->window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
                }
            }
        }
};