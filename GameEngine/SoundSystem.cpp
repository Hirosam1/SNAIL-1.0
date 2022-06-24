#include "SoundSystem.hpp"

#define GLOBAL_SAMPLERATE 44100
#define FRAMES_PER_BUFFER 512

static int PlaySoundCallback(const void* input_buffer, void* output_buffer,
                            unsigned long frames_per_buffer,
                            const PaStreamCallbackTimeInfo* time_info,
                            PaStreamCallbackFlags status_flags,
                            void* usr_data){
    cm_Int16* out = (cm_Int16*) output_buffer;
    cm_process(out,FRAMES_PER_BUFFER*2);
    return 0;
}

SoundSystem::SoundSystem(int sample_rate, double master_volume){
    cm_init(sample_rate);
    this->master_volume = master_volume;
    cm_set_master_gain(master_volume);

    PaStream* stream;
    PaError err = Pa_Initialize();
    if (err != paNoError){
        printf("Something while initializing PortAudio!");
    }
    err = Pa_OpenDefaultStream(&stream,0,2,paInt16,GLOBAL_SAMPLERATE,FRAMES_PER_BUFFER,PlaySoundCallback,NULL);
}