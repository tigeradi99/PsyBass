//
// Created by adity on 20-09-2026.
//

#include "dsp/engine.hpp"

namespace dsp {
    void SynthEngine::setSampleRate(const double sampleRate) {
        m_voice.setSampleRate(sampleRate);
    }

    void SynthEngine::noteOn(const int note, const float velocity) {
        // Set note on for voices
        m_voice.noteOn(note, velocity);
    }

    void SynthEngine::noteOff(const int note) {
        // Set note off for voices
        m_voice.noteOff(note);
    }

    void SynthEngine::setOscillatorMode(const OscillatorMode mode) {
        m_voice.setOscillatorMode(mode);
    }

    void SynthEngine::process(float *left, float *right, int numSamples) {
        for (int i = 0; i < numSamples; i++) {
            const float sample =  m_voice.processSample();

            left[i] = sample;
            right[i] = sample;
        }
    }
}
