//
// Created by adity on 16-09-2026.
//

#pragma once


namespace dsp {
    enum OscillatorMode {
        OSCILLATOR_MODE_SINE,
    };

    class Oscillator {
    public:
        Oscillator();

        void setFrequency(double frequency);
        void setMode(OscillatorMode mode);
        void setSampleRate(double sampleRate);
        double nextSample();

    private:
        OscillatorMode m_oscillatorMode;
        const double m_PI = 3.14159265358979323846;
        const double m_2PI = 2 * m_PI;

        // Can be changed from frontend
        double m_frequency;
        double m_sampleRate;

        // Calculated from frequency and declared sample rate
        double m_phase;
        double m_phaseIncrement;

        void updateIncrement();

        void updatePhase();

        [[nodiscard]]
        double generateSine() const;
    };
}
