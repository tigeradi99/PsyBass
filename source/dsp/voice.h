//
// Created by adity on 20-09-2026.
//

#ifndef PSYBASS_VOICE_H
#define PSYBASS_VOICE_H

#include "dsp/oscillator.hpp"

#include <cstdint>

namespace dsp {
    class Voice {
    public:
        void setSampleRate(double sampleRate);

        void noteOn(int midiNote, float velocity);
        void noteOff(int note);

        float processSample();

    private:
        Oscillator m_oscillator;

        int32_t m_note = -1;
        float m_velocity = 1.0f;
        bool m_active = false;

    };
}

#endif //PSYBASS_VOICE_H
