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

    void Oscillator::setFrequency(double frequency) {
        m_frequency = frequency;
        updateIncrement();
    }

    void Oscillator::setSampleRate(double sampleRate) {
        m_sampleRate = sampleRate;
        updateIncrement();
    }

    float Oscillator::process() {
        const auto value = static_cast<float>(std::sin(m_phase));

        m_phase += m_phaseIncrement;

        if (m_phase >= m_2PI)
            m_phase -= m_2PI;

        return value;
    }

    double Oscillator::nextSample() {
        switch (m_oscillatorMode) {
            case OscillatorMode::OSCILLATOR_MODE_SINE: {
                return generateSine();
            }
        }
    }

    void Oscillator::setMode(OscillatorMode mode) {
        m_oscillatorMode = mode;
    }

    void Oscillator::updateIncrement() {
        m_phaseIncrement = 2 * m_PI * m_frequency / m_sampleRate;
    }

    double Oscillator::generateSine() {
        const auto value = std::sin(m_phase);

        m_phase += m_phaseIncrement;

        if (m_phase >= m_2PI)
            m_phase -= m_2PI;

        return value;
    }
}
