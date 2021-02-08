#pragma once
#include "GLFW/glfw3.h"
#include "GMpch.hpp"
#include "Window.hpp"

enum InputType{
    KEY_RELEASE,
    KEY_PRESSED
};

struct InputInfo{
    bool was_activated;
};

struct InputConfig{
    unsigned int glfw_Key;
    unsigned int glfw_press_type;
    int command;
};

class InputHandler{
    public:
        
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
                if(glfwGetKey(window,inputs_config[i].glfw_Key) == inputs_config[i].glfw_press_type){
                    inputs_info[i].was_activated = true;
                }
            }
        };
        void AddCommandBack(unsigned int key, unsigned int press_type,int command){
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
        }
    private:
        int command_position = 0;
        std::vector<InputConfig> inputs_config;
        std::vector<InputInfo> inputs_info;
        std::map<int,int> input_mapping;
        GLFWwindow* window;

};