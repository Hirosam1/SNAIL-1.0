#pragma once
#include "GMpch.hpp"
#include <GLFW/glfw3.h>
#include <json/json.hpp>
//Keep track of game time
class Time{
    public:
        Time();
        void UpdateTime();
        static float GetTime();
        static float deltaTime;
    private:
        float last_time =0;
};

struct TraceEvent{
    //Trace event name
    std::string name;
    //Time stamp
    long long ts;
    //Duration
    long long dur;
    //Event categories
    std::string cat = "function";
    //Event type
    std::string ph = "X";
    //Thread id
    int tid = 0;
    //Proccess id
    int pid = 0;
};

class TraceEventsFile{
    public:
        std::list<TraceEvent> trace_events;
        
        TraceEventsFile(std::string file_path) : file_path(file_path + ".json"){}
        void PushBackEvent(const TraceEvent& trace_event){
            trace_events.push_back(trace_event);
        }
        void WriteJson(){
            std::cout<<"Wrting to " << file_path<<"\n";
            nlohmann::json js_events;
            std::ofstream out_f (file_path);
            js_events["otherData"] = "";
            for(TraceEvent te : trace_events){
                nlohmann::json js_event;
                js_event["name"] = te.name;
                js_event["ts"] = te.ts;
                js_event["dur"] = te.dur;
                js_event["cat"] = te.cat;
                js_event["ph"] = te.ph;
                js_event["tid"] = te.tid;
                js_event["pid"] = te.pid;
                js_events["traceEvents"].push_back(js_event);
            }
            out_f << js_events.dump(4);
        }
    private:
        std::string file_path;
};

//Measure time periods defined by the object life-time
class Timer{
    public:
        Timer(TraceEventsFile* tef, std::string function_name = "function") : tef(tef){
            start_time_point =  std::chrono::high_resolution_clock::now();
            te.name = function_name;
        }
        ~Timer(){
            Stop();
        }
        void Stop(){
            auto end_time_point = std::chrono::high_resolution_clock::now();
            auto start = std::chrono::time_point_cast<std::chrono::microseconds>(start_time_point).time_since_epoch().count();
            auto end = std::chrono::time_point_cast<std::chrono::microseconds>(end_time_point).time_since_epoch().count();

            auto duration = end - start;
            te.ts = start;
            te.dur = duration;
            tef->PushBackEvent(te);
            //double ms = duration * 0.001;
            

        }
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> start_time_point;
        TraceEvent te;
        TraceEventsFile* tef;
};