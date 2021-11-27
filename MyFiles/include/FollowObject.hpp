#include "GameEngine.hpp"


class FollowObject : public Behavior{
    public:
        GameObject* go_2_follow;
        void Begin() override{
            go_2_follow = Scene::active_scene->FindGameObject("character");
        }

        void Update() override{
            Vector3 pos = go_2_follow->transform->position;
            this->transform->SetPos(Vector3(pos.x,pos.y,this->transform->position.z));
        }
};