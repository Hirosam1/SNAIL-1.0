#pragma once
#include "GMpch.hpp"
#include <json/json.hpp>

//Info of an Event
struct TraceEvent{
    //Trace event name
    std::string name;
    //Time stamp
    long long ts;
    //Duration
    long long dur = 0.0;
    //Event categories
    std::string cat = "function";
    //Event type
    std::string ph = "X";
    //Thread id
    int tid = 0;
    //Proccess id
    int pid = 0;
};

//This class handles all events in a session
class TraceEventsSession{
    public:
        int count = 0;
        //Creates a session with a Name, the file generated will have this name
        TraceEventsSession(std::string file_path) : file_path(file_path + ".json"){}
        //Pushes back an TraceEvent into the TraveEventsSession list
        void PushBackEvent(const TraceEvent trace_event){
            #ifdef DEBUG
                trace_events.push_back(trace_event);
            #endif
        }
        //Ends the file amd serialize data into json file
        void EndSession(){
            #ifdef DEBUG
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
            #endif
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
            #ifdef DEBUG
                start_time_point =  std::chrono::high_resolution_clock::now();
                te.name = function_name;
            #endif
        }
        ~Timer(){
            if(!has_stopped){
                Stop();
            }
        }
        //Stops timer and pushes it info back into the TraceEventSession list
        void Stop(){
            #ifdef DEBUG
                auto end_time_point = std::chrono::high_resolution_clock::now();
                auto start = std::chrono::time_point_cast<std::chrono::microseconds>(start_time_point).time_since_epoch().count();
                auto end = std::chrono::time_point_cast<std::chrono::microseconds>(end_time_point).time_since_epoch().count();

                auto duration = end - start;
                te.ts = start;
                te.dur = duration;
                tes->PushBackEvent(te);
                has_stopped = true;
                //double ms = duration * 0.001;
            #endif

        }
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> start_time_point;
        TraceEvent te;
        TraceEventsSession* tes;
        bool has_stopped  =false;
};

class InstantEvent{
    public:
        static void CreateInstantEvent(TraceEventsSession* tes, const std::string& name){
            auto time_point = std::chrono::high_resolution_clock::now();
            TraceEvent te;
            te.ts = std::chrono::time_point_cast<std::chrono::milliseconds>(time_point).time_since_epoch().count();
            te.name = name;
            te.ph = "i";
            tes->PushBackEvent(te);
        }
};