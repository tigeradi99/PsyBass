#pragma once

#include "public.sdk/source/vst/vstaudioeffect.h"
#include "dsp/oscillator.hpp"

namespace psybass {
    class PsyBassProcessor: public Steinberg::Vst::AudioEffect {
        public:
        PsyBassProcessor();
        ~PsyBassProcessor() SMTG_OVERRIDE;

        // create function
        static Steinberg::FUnknown* createInstance(void*) {
            return  static_cast<Steinberg::Vst::IAudioProcessor*>(new PsyBassProcessor);
        }

        //--- ---------------------------------------------------------------------
        // AudioEffect overrides:
        //--- ---------------------------------------------------------------------
        /** Called at first after constructor */
        Steinberg::tresult PLUGIN_API initialize (Steinberg::FUnknown* context) SMTG_OVERRIDE;
        
        /** Called at the end before destructor */
        Steinberg::tresult PLUGIN_API terminate () SMTG_OVERRIDE;
        
        /** Switch the Plug-in on/off */
        Steinberg::tresult PLUGIN_API setActive (Steinberg::TBool state) SMTG_OVERRIDE;

        /** Will be called before any process call */
        Steinberg::tresult PLUGIN_API setupProcessing (Steinberg::Vst::ProcessSetup& newSetup) SMTG_OVERRIDE;
        
        /** Asks if a given sample size is supported see SymbolicSampleSizes. */
        Steinberg::tresult PLUGIN_API canProcessSampleSize (Steinberg::int32 symbolicSampleSize) SMTG_OVERRIDE;

        /** Here we go...the process call */
        Steinberg::tresult PLUGIN_API process (Steinberg::Vst::ProcessData& data) SMTG_OVERRIDE;
            
        /** For persistence */
        Steinberg::tresult PLUGIN_API setState (Steinberg::IBStream* state) SMTG_OVERRIDE;
        Steinberg::tresult PLUGIN_API getState (Steinberg::IBStream* state) SMTG_OVERRIDE;

        protected:
        Steinberg::Vst::ParamValue mParam1 = 0;
        int16_t mParam2 = 0;
        bool mBypass = false;

        private:
        // Create engine here
        dsp::Oscillator mOscillator;
        bool mGate = false;
    };
}