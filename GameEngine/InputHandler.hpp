#pragma once
#include "GLFW/glfw3.h"
#include "GMpch.hpp"
#include "Window.hpp"

enum PressType{
    KEY_RELEASE,
    KEY_HOLD,
    KEY_PRESS
};

class InputHandler{

    struct InputInfo{
        bool was_activated;
        bool is_ready;
    };

    struct InputConfig{
        unsigned int glfw_Key;
        PressType ih_press_type;
        int command;
    };

    public:
        //checks if at least one key was activated
        bool activated = false;
        InputHandler(unsigned int commands_amount){
            window = Window::main_window->window;
            input_mapping = std::map<int,int>();
            inputs_config = std::vector<InputConfig>(commands_amount);
            inputs_info = std::vector<InputInfo>(commands_amount);
            for(int i = 0; i < inputs_info.size(); i++){
                inputs_info[i] = InputInfo{false};
            }
        };
        //Use this function to get inout info based on the commands you passed. Use it once per frame.
        void HandleInput(){ 
            ResetInputInfo();
            for(int i = 0; i < inputs_config.size(); i++){
                unsigned int glfw_press_type = inputs_config[i].ih_press_type == PressType::KEY_PRESS || inputs_config[i].ih_press_type == PressType::KEY_HOLD ? GLFW_PRESS 
                                                : GLFW_RELEASE;
                if(inputs_config[i].ih_press_type == PressType::KEY_PRESS){
                    if(!inputs_info[i].is_ready){
                        if (glfwGetKey(window,inputs_config[i].glfw_Key) == GLFW_RELEASE){
                            inputs_info[i].is_ready = true;
                        }
                    }else{
                        if (glfwGetKey(window,inputs_config[i].glfw_Key) == GLFW_PRESS){
                            inputs_info[i].is_ready = false;
                            inputs_info[i].was_activated = true;
                        }
                    }
                }
                else if(glfwGetKey(window,inputs_config[i].glfw_Key) == glfw_press_type){
                    activated = true;
                    inputs_info[i].was_activated = true;
                }
            }
        };
        void AddCommandBack(unsigned int key, PressType press_type,int command){
            if(command_position < inputs_config.size()){
                inputs_config[command_position] = InputConfig{key,press_type,command};
                input_mapping[command] = command_position;
                command_position++;
            }
        }

        InputInfo GetInputInfo(int command){
            if(input_mapping.count(command)){
                return inputs_info[input_mapping[command]];
            }
            return InputInfo{false};
        }

        void ResetInputInfo(){
            for(int i = 0; i < inputs_info.size(); i++){
                inputs_info[i].was_activated = false;
            }
            activated = false;
        }
    private:
        int command_position = 0;
        std::vector<InputConfig> inputs_config;
        std::vector<InputInfo> inputs_info;
        std::map<int,int> input_mapping;
        GLFWwindow* window;

};