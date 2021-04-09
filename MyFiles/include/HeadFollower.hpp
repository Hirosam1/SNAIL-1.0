#include "GameEngine.hpp"

class HeadFollower : public Behaviour{
    public:

    private:
        GameObject* object_to_follow = nullptr;

        void Begin() override{
            for(Object* obj : Window::main_window->object_list){
                if(obj->object_name == "Camera Follower"){
                    object_to_follow = dynamic_cast<GameObject*>(obj);
                }
            }
        }

        void Update() override{
            if(object_to_follow){
                transform->LookAt(object_to_follow->transform->position);
            }
        }
};