//
// Created by adity on 14-09-2026.
//

#include "plugin/processor.h"
#include "plugin/psybass_cids.h"

#include "base/source/fstreamer.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"

#include <algorithm>


namespace psybass {
    PsyBassProcessor::PsyBassProcessor() {
        // set the intended controller
        setControllerClass(kPsyBassControllerUID);
    }

    PsyBassProcessor::~PsyBassProcessor() {}

    Steinberg::tresult PsyBassProcessor::initialize(Steinberg::FUnknown *context) {
        auto tresult = AudioEffect::initialize(context);

        if (tresult != Steinberg::kResultOk) {
            return tresult;
        }

        // For synth later:
        // addAudioOutput(...);
        // addEventInput(...);

        return Steinberg::kResultOk;
    }

    Steinberg::tresult PsyBassProcessor::terminate() {
        return AudioEffect::terminate();
    }

    Steinberg::tresult PsyBassProcessor::process(Steinberg::Vst::ProcessData &data) {
        // Barebones: generate silence for now.

        if (data.numOutputs == 0)
            return Steinberg::kResultOk;

        auto& output = data.outputs[0];

        if (data.symbolicSampleSize == Steinberg::Vst::kSample32) {
            for (Steinberg::int32 channel = 0; channel < output.numChannels; ++channel){
                auto* buffer = output.channelBuffers32[channel];

                std::fill(buffer,buffer + data.numSamples, 0.0f);
            }
        }

        return Steinberg::kResultOk;
    }
}
