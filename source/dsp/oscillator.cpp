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
                break;
            }
            case OscillatorMode::OSCILLATOR_MODE_SAW: {
                value = generateSawBLEP();
                break;
            }
            case OscillatorMode::OSCILLATOR_MODE_SQUARE: {
                value = generateSquareBLEP();
                break;
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

    double Oscillator::polyBLEP(double phase, double phaseIncrement) {
        // polyBLEP has a jump of x(0+) - x(0-) = -1 - (1) = -2.
        // discontinuity on right half (start of cycle)
        if (phase < phaseIncrement) {
            const double t = phase / phaseIncrement;
            return -t * t + 2.0 * t - 1.0;
        }
        // discontinuity on left half (end of cycle)
        if (phase > 1.0 - phaseIncrement) {
            const double t = (phase - 1.0) / phaseIncrement;
            return t * t + 2.0 * t + 1.0;
        }

        return 0.0;
    }

    double Oscillator::generateSine() const {
        const auto value = std::sin(m_2PI * m_phase);

        return value;
    }

    double Oscillator::generateSawBLEP() const {
        double value = 2.0 * m_phase - 1;

        // Discontinuity at phase 0
        value -= polyBLEP(m_phase, m_phaseIncrement);

        return value;
    }

    double Oscillator::generateSquareBLEP() const {
        double value = (m_phase < 0.5) ? 1.0: -1.0;

        // Discontinuity at phase 0. Jump = 1 - (-1) = 2
        value += polyBLEP(m_phase, m_phaseIncrement);

        // Discontinuity at phase 0.5. Jump = -1 - (1) = -2
        double shiftedPhase = std::fmod(m_phase + 0.5, 1.0);
        value -= polyBLEP(shiftedPhase, m_phaseIncrement);

        return value;
    }
}
