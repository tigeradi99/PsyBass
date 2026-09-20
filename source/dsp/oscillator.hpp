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
        void generate(float* buffer, int n_samples);
        float process();

    private:
        OscillatorMode m_oscillatorMode;
        const double m_PI = 3.14159265358979323846;
        const double m_2PI = 2 * m_PI;
        double m_frequency;
        double m_phase;
        double m_sampleRate;
        double m_phaseIncrement;

        void updateIncrement();
    };
}
