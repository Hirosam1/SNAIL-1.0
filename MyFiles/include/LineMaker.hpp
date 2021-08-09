#pragma once
#include "GameEngine.hpp"

class LineDraw : public Behavior{
    VertexData vertex_data;
    float line_thickness = 0.02f;
    std::vector<Vector3> points;
    void Begin() override{
        Shader* white_line_shader = new Shader("resources/shaders/vertex/atlas.vert", "resources/shaders/fragment/solid_colorW.frag");
        Scene::active_scene->AddObject(white_line_shader);
        // points = std::vector<Vector3>{Vector3(0.0,0.0,0.01), Vector3(0.1,0.1,0.01),
        //                               Vector3(0.1,0.05,0.01), Vector3(0.2,0.05,0.01)};
        //Vector3(0.1,1.1,0.01), Vector3(0.2,1.1,0.01)
        points.push_back(Vector3(0.1,0.3,0.01));
        points.push_back(Vector3(0.2,0.4,0.01));
        Model* model = new Model(BuildPolygons(points));
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

    ModelData BuildPolygons(std::vector<Vector3> points){
        ModelData md = ModelData();
        
        //Line start
        Vector3 vec1 = Vector::Normalize(points[1] - points[0]);
        if(points.size() > 1){
            md.vertex_data.push_back(VertexData{Vector3(vec1.y,-vec1.x,vec1.z) * line_thickness + points[0], Vector2()});
            if(points.size() == 1 + 1){
                md.vertex_data.push_back(VertexData{Vector3(vec1.y,-vec1.x,vec1.z) * line_thickness + points[1], Vector2()});
                md.vertex_data.push_back(VertexData{Vector3(-vec1.y,vec1.x,vec1.z) * line_thickness + points[1], Vector2()});
            }
            md.vertex_data.push_back(VertexData{Vector3(-vec1.y,vec1.x,vec1.z) * line_thickness + points[0], Vector2()});
            md.indices.push_back(0);
            md.indices.push_back(1);
            md.indices.push_back(2);

            md.indices.push_back(3);
            md.indices.push_back(0);
            md.indices.push_back(2);
        }
        return md;
    }

};