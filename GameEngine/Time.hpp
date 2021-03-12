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
//Info of an Event
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

class TraceEventsSession{
    public:
        
        
        TraceEventsSession(std::string file_path) : file_path(file_path + ".json"){}
        //Pushes back an TraceEvent into the TraveEventsSession list
        void PushBackEvent(const TraceEvent& trace_event){
            trace_events.push_back(trace_event);
        }
        //Ends the file amd serialize data into json file
        void EndSession(){
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
        std::list<TraceEvent> trace_events;
        std::string file_path;
};

//Measure time periods defined by the object life-time
class Timer{
    public:
        //Creates timer object and starts clock, it will end clock automatically on object destruction
        Timer(TraceEventsSession* tes, std::string function_name = "function") : tes(tes){
            start_time_point =  std::chrono::high_resolution_clock::now();
            te.name = function_name;
        }
        ~Timer(){
            if(!has_stopped){
                Stop();
            }
        }
        //Stops timer and pushes it info back into the TraceEventSession list
        void Stop(){
            auto end_time_point = std::chrono::high_resolution_clock::now();
            auto start = std::chrono::time_point_cast<std::chrono::microseconds>(start_time_point).time_since_epoch().count();
            auto end = std::chrono::time_point_cast<std::chrono::microseconds>(end_time_point).time_since_epoch().count();

            auto duration = end - start;
            te.ts = start;
            te.dur = duration;
            tes->PushBackEvent(te);
            has_stopped = true;
            //double ms = duration * 0.001;
            

        }
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> start_time_point;
        TraceEvent te;
        TraceEventsSession* tes;
        bool has_stopped  =false;
};