#pragma once
#include "GMpch.hpp"
#include "Resource.hpp"

#include "cmixer.h"

#define MAX_VOLUME 1.0

class Sound : public Resource{
    public:
        Sound(std::string path_to_sound);
        void Play();
        void Pause();
        void Stop();

        double SetVolume(double vol);
        double AddVolume(double vol);
        double GetVolume();

        double SetPitch(double pitch);
        double GetPitch();

        void SetLoop(bool is_loop);
    private:
        double volume;
        bool is_loop;
        double pitch;

        cm_Source* sound_src;
        
};