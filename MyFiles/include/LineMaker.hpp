#pragma once
#include "GameEngine.hpp"

class LineDraw : public Behavior{
    VertexData vertex_data;
    void Begin() override{
        std::vector<Vector3> points;
        Shader* white_line_shader = new Shader("resources/shaders/vertex/atlas.vert", "resources/shaders/fragment/solid_colorW.frag");
        Scene::active_scene->AddObject(white_line_shader);
        points.push_back(Vector3(0.0,0.0,0.00));
        points.push_back(Vector3(0.2,0.2,0.00));

        Model* model = new Model(BuildLine(points[0],points[1]));
        Scene::active_scene->AddObject(model);
        Mesh* mesh = new Mesh(model);
        Scene::active_scene->AddObject(mesh);
        GameObject* go = new GameObject();
        go->PushComponentBack(new MeshRenderer(mesh,white_line_shader));
        go->object_name = "Line";
        Scene::active_scene->AddGameObject(go);
    }

    void Update() override{

    }

    ModelData BuildLine(Vector3 point_s, Vector3 point_e,float line_thickness = 0.02f){
        ModelData md = ModelData();
        //Line start
        Vector3 vec1 = Vector::Normalize(point_e - point_s);
        md.vertex_data.push_back(VertexData{Vector3(vec1.y,-vec1.x,vec1.z) * line_thickness + point_s, Vector2()});
        md.vertex_data.push_back(VertexData{Vector3(vec1.y,-vec1.x,vec1.z) * line_thickness + point_e, Vector2()});
        md.vertex_data.push_back(VertexData{Vector3(-vec1.y,vec1.x,vec1.z) * line_thickness + point_e, Vector2()});
        md.vertex_data.push_back(VertexData{Vector3(-vec1.y,vec1.x,vec1.z) * line_thickness + point_s, Vector2()});
        md.indices.push_back(0);
        md.indices.push_back(1);
        md.indices.push_back(2);

        md.indices.push_back(3);
        md.indices.push_back(0);
        md.indices.push_back(2);
            
        return md;
    }

};