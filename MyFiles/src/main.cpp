#include "GMpch.hpp"
#include "Game.hpp"

//Proccess basic input
void processInput(GLFWwindow* window);
//Set Consts
const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 800;
int main(int argc, char** argv){  
    Game my_game("Testing Game", SCR_WIDTH, SCR_HEIGHT);
    my_game.InitGame();
    my_game.RunGame();
    return 0;
}



