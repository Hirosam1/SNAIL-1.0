#pragma once
#include "GMpch.hpp"
#include "cmixer.h"
#include "portaudio/portaudio.h"

class SoundSystem {
    public:
        SoundSystem(double master_volume=1.0);

        double SetMasterVolume(double volume);
    private:
        double master_volume;
};