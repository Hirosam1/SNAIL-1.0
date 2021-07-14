#pragma once
#include "Components/Component.hpp"
#include "Components/Transform.hpp"

#include "GMpch.hpp"
#include "Object.hpp"

class GameObject : public Object{
    public:
        Transform* transform;
        GameObject(){transform = new Transform(); PushComponentBack(transform);};
        void Begin(){for(Component* component : components){component->Begin(this);}} 
        void Update(){for(Component* component : components){component->Update(this);}}
        void UnloadObject() override{for(Component* component : components){component->End(this); delete component; std::cout<<object_name <<" DELETE DA COMPOENENT!!!\n";}}
        //Seraches for the desired component
        template <class T>
        T* GetComponent(){
            T* component_return;
            for(Component* component : components){
                if((component_return = dynamic_cast<T*>(component))){
                    return component_return;
                }
            }
            return nullptr;
        };
        //Safely pushes back a component !!(MAYBE??)IMPLEMENT CHECK FOR UNIQUE COMPONENT!!
        template <class T>
        void PushComponentBack(T* component){
            Component* component_add = dynamic_cast<Component*>(component);
            if(component_add){
                component_add->game_object = this;
                components.push_back(component_add);
            }
        };
    private:
        //GameObject is responsable in deleting its components
        std::vector<Component*> components;
        bool is_enabled;
};