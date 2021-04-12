#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Resources/Model.hpp"
#include "Resources/Shader.hpp"
#include "Resources/Texture.hpp"
#include "Resources/Resource.hpp"

#include "Components/Component.hpp"
#include "Components/Behaviour.hpp"
#include "Components/Transform.hpp"
#include "Components/RigidBody2D.hpp"
#include "Components/Collider2D.hpp"
#include "Components/Renderer.hpp"
#include "Components/SpriteRenderer.hpp"
#include "Components/MeshRenderer.hpp"
#include "Components/Camera.hpp"

#include "Objects/Scene.hpp"
#include "Objects/GameObject.hpp"
#include "Objects/Scene.hpp"
#include "Objects/Mesh.hpp"
#include "Objects/SpriteAtlas.hpp"

#include "DataStructures/ImplicitObjects.hpp"
#include "DataStructures/Matrix.hpp"
#include "DataStructures/Vector.hpp"

#include "FileIO.hpp"
#include "Math.hpp"
#include "Matrix_Transform.hpp"
#include "Time.hpp"
#include "InputHandler.hpp"
#include "Window.hpp"
#include "Debug.hpp"
#include "EventTracer.hpp"
#include "GLStateManager.hpp"
