#pragma once
#include "GMpch.hpp"
#include "cmixer.h"
#include "portaudio.h"

class SoundSystem {
    public:
        SoundSystem(int sample_rate, double master_volume);

        double SetMasterVolume(double volume);
    private:
        double master_volume;
        int sample_rate;
};