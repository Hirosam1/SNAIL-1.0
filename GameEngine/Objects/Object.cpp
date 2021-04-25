#include "Objects/Object.hpp"

//Initiate the entire array with 0 (nullptr)
std::vector<Object*> Object::objects = std::vector<Object*>(30,nullptr);

unsigned int Object::objects_count = 0;

void Object::AddObjectBack(Object* obj){
    Object::objects[objects_count] = obj;
    objects_count++;
}