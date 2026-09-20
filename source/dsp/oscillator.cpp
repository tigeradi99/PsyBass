//
// Created by adity on 16-09-2026.
//

#include "dsp/oscillator.hpp"

#include <complex>


namespace dsp {
    Oscillator::Oscillator() {
        m_oscillatorMode =  OscillatorMode::OSCILLATOR_MODE_SINE;
        m_frequency = 440.0;
        m_sampleRate = 44100.0;
        m_phase = 0.0;
        updateIncrement();
    }

    void Oscillator::setFrequency(const double frequency) {
        m_frequency = frequency;
        updateIncrement();
    }

    void Oscillator::setSampleRate(const double sampleRate) {
        m_sampleRate = sampleRate;
        updateIncrement();
    }

    double Oscillator::nextSample() {
        double value = 0.0;

        switch (m_oscillatorMode) {
            case OscillatorMode::OSCILLATOR_MODE_SINE: {
                value = generateSine();
            }
        }

        // Update phase after generating sample
        updatePhase();
        return value;
    }

    void Oscillator::setMode(const OscillatorMode mode) {
        m_oscillatorMode = mode;
    }

    void Oscillator::updateIncrement() {
        m_phaseIncrement = m_frequency / m_sampleRate;
    }

    void Oscillator::updatePhase() {
        // Phase increment
        m_phase += m_phaseIncrement;

        if (m_phase >= 1.0)
            m_phase -= 1.0;
    }

    double Oscillator::generateSine() const {
        const auto value = std::sin(m_2PI * m_phase);

        return value;
    }
}
