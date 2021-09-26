#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "DataStructures/Vector.hpp"
#include "DataStructures/Matrix.hpp"
#include "DataStructures/ImplicitObjects.hpp"
#include "DataStructures/Quaternion.hpp"

#include "Math/Math.hpp"
#include "Math/Matrix_Transform.hpp"
#include "Math/Quternion_Transform.hpp"

#include "Resources/Resource.hpp"
#include "Resources/Model.hpp"
#include "Resources/Shader.hpp"
#include "Resources/Texture.hpp"

#include "Objects/Object.hpp"
#include "Objects/Scene.hpp"
#include "Objects/GameObject.hpp"
#include "Objects/Mesh.hpp"
#include "Objects/SpriteAtlas.hpp"
//Bad idea?? 
//#include "Objects/ObjectFactory.hpp"

#include "Components/Component.hpp"
#include "Components/Behavior.hpp"
#include "Components/Transform.hpp"
#include "Components/RigidBody2D.hpp"
#include "Components/Collider2D.hpp"
#include "Components/Renderer.hpp"
#include "Components/SpriteRenderer.hpp"
#include "Components/MeshRenderer.hpp"
#include "Components/Camera.hpp"

#include "FileIO.hpp"
#include "Time.hpp"
#include "InputHandler.hpp"
#include "Window.hpp"
#include "Debug.hpp"
#include "EventTracer.hpp"
#include "GLHandler/GLStateManager.hpp"
#include "ResourcesMetaData.hpp"

