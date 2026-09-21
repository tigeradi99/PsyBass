//
// Created by adity on 16-09-2026.
//

#pragma once


namespace dsp {
    enum OscillatorMode {
        OSCILLATOR_MODE_SINE = 0,
        OSCILLATOR_MODE_SQUARE,
        OSCILLATOR_MODE_SAW,

        COUNT
    };

    class Oscillator {
    public:
        Oscillator();

        void setFrequency(double frequency);
        void setMode(OscillatorMode mode);
        void setSampleRate(double sampleRate);
        double nextSample();

        // Utility method
        static double polyBLEP(double phase, double phaseIncrement);

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

        [[nodiscard]] double generateSine() const;
        [[nodiscard]] double generateSawBLEP() const;
        [[nodiscard]] double generateSquareBLEP() const;
    };
}
