#include "Objects/Object.hpp"

//Initiate the entire array with 0 (nullptr)
std::vector<Object*> Object::objects = std::vector<Object*>(30,nullptr);

unsigned int Object::objects_count = 0;

void Object::AddObjectBack(Object* obj){
    Object::objects[objects_count] = obj;
    objects_count++;
}

void Object::UnloadAllObjects(){
    for(Object* o : objects){
        if(o){
            o->UnloadObject();
        }
    }
}

Object* Object::FindObjectByName(const std::string& name){
    for(Object* o : objects){
        if(o){
            if(strcmp(o->object_name.data(),name.data()) == 0){
                return o;
            }
        }
    }
    return nullptr;
}