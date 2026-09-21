//
// Created by adity on 20-09-2026.
//

#include "dsp/voice.h"

#include <cmath>

namespace dsp {
    void Voice::setSampleRate(const double sampleRate) {
        m_oscillator.setSampleRate(sampleRate);
    }

    void Voice::noteOn(const int midiNote, const float velocity) {
        m_note = midiNote;
        m_velocity = velocity;
        m_active = true;

        // A4 = 440 Hz, and index of A4 is 69
        const double frequency = 440.0f * powf(2.0f, static_cast<float>(midiNote - 69) / 12.0f);

        m_oscillator.setFrequency(frequency);
    }

    void Voice::noteOff(int note) {
        m_active = false;
    }

    void Voice::setOscillatorMode(const OscillatorMode mode) {
        m_oscillator.setMode(mode);
    }

    float Voice::processSample() {
        if (!m_active)
            return 0.0f;

        return static_cast<float>(m_oscillator.nextSample()) * m_velocity;
    }
}
