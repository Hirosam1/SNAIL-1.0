#include "Sound.hpp"

#define CLAMP(x,a,b) x > a ? a : x < b ? b : x


Sound::Sound(std::string sound_path){
    sound_src = cm_new_source_from_file(sound_path.data());
    if(sound_src == NULL){
        std::cout<<"Error while loading sound!\n";
    }
}

void Sound::Play(){
    cm_play(this->sound_src);
}

void Sound::Pause(){
    cm_play(this->sound_src);
}

void Sound::Stop(){
    cm_stop(this->sound_src);
}

double Sound::SetVolume(double volume){
    this->volume = CLAMP(volume,MAX_VOLUME,0.0);
    cm_set_gain(this->sound_src,this->volume);
    return this->volume;
}

double Sound::AddVolume(double volume){
    this->volume = CLAMP(this->volume + volume,MAX_VOLUME,0.0);
    cm_set_gain(this->sound_src,this->volume);
    return this->volume;
}

double Sound::GetVolume(){
    return this->volume;
}

double Sound::SetPitch(double pitch){
    this->pitch = pitch > 0 ?  pitch : 0.001;
    cm_set_pitch(this->sound_src,this->pitch);
    return this->pitch;
}

double Sound::GetPitch(){
    return this->pitch;
}

void Sound::SetLoop(bool is_loop){
    cm_set_loop(this->sound_src,is_loop);
}