#pragma once
#include "Components/Component.hpp"
#include "GMpch.hpp"
#include "Components/Transform.hpp"

class GameObject{
    public:
        std::string object_name = "New GameObject";
        Transform* transform;
        GameObject(){transform = new Transform(); PushComponentBack(transform);};
        void Begin(){for(Component* component : components){component->Begin(this);};}
        void Update(){for(Component* component : components){component->Update(this);};}
        //Seraches for the desired component
        template <class T>
        T* GetComponent(){
            T* component_return;
            for(Component* component : components){
                if((component_return = dynamic_cast<T*>(component))){
                    return component_return;
                }
            }
            std::cout<<"Could not find operator \""<< typeid(T).name() <<"\" For the game object: "<<object_name<<"\n";
            return nullptr;
        };
        //Safely pushes back a component !!(MAYBE??)IMPLEMENT CHECK FOR UNIQUE COMPOENT!!
        template <class T>
        void PushComponentBack(T* component){
            Component* component_add = dynamic_cast<Component*>(component);
            if(component_add){
                components.push_back(component_add);
            }
        };
    private:
        //GameObject is responsable in deleting its components
        std::vector<Component*> components;
        bool is_enabled;
};