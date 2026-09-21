//
// Created by adity on 20-09-2026.
//

#ifndef PSYBASS_ENGINE_HPP
#define PSYBASS_ENGINE_HPP

#include "dsp/voice.h"

namespace dsp {
    class SynthEngine {
    public:
        void setSampleRate(double sampleRate);

        void noteOn(int note, float velocity);
        void noteOff(int note);

        void setOscillatorMode(OscillatorMode mode);
        void process(float* left, float* right, int numSamples);

    private:
        Voice m_voice;
    };
}

#endif //PSYBASS_ENGINE_HPP
