#include "GameEngine.hpp"

class HeadFollower : public Behaviour{
    public:

    private:
        GameObject* object_to_follow = nullptr;

        void Begin() override{
            object_to_follow = Scene::active_scene->FindGameObject("Camera Follower");
        }

        void Update() override{
            if(object_to_follow){
                transform->LookAt(object_to_follow->transform->position);
            }
        }
};