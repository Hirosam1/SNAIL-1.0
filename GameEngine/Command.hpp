#pragma once
class GameObject;


class Command{
    public:
        float velocity = 3.0;
        virtual void Execute(GameObject& object)=0;
        virtual void Release(){};
};