//
// Created by adity on 14-09-2026.
//

#include "plugin/processor.h"
#include "plugin/psybass_cids.h"
#include "plugin/params.h"

#include "base/source/fstreamer.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"

#include <algorithm>

#include "pluginterfaces/vst/ivstevents.h"


namespace psybass {
    PsyBassProcessor::PsyBassProcessor() {
        // set the intended controller
        setControllerClass(kPsyBassControllerUID);
    }

    PsyBassProcessor::~PsyBassProcessor() {}

    Steinberg::tresult PsyBassProcessor::initialize(Steinberg::FUnknown *context) {
        auto t_result = AudioEffect::initialize(context);

        if (t_result != Steinberg::kResultOk) {
            return t_result;
        }

        // For synth later:
        addAudioOutput(STR16("Stereo Out"), Steinberg::Vst::SpeakerArr::kStereo);
        addEventInput(STR16("Event In"),1);

        return Steinberg::kResultOk;
    }

    Steinberg::tresult PsyBassProcessor::terminate() {
        return AudioEffect::terminate();
    }

    Steinberg::tresult PsyBassProcessor::setActive(Steinberg::TBool state) {
        return AudioEffect::setActive(state);
    }

    Steinberg::tresult PsyBassProcessor::setupProcessing(Steinberg::Vst::ProcessSetup &newSetup) {
        mEngine.setSampleRate(newSetup.sampleRate);
        return AudioEffect::setupProcessing(newSetup);
    }

    Steinberg::tresult PsyBassProcessor::canProcessSampleSize(Steinberg::int32 symbolicSampleSize) {
        if (symbolicSampleSize == Steinberg::Vst::kSample32)
            return Steinberg::kResultTrue;

        return Steinberg::kResultFalse;
    }

    Steinberg::tresult PsyBassProcessor::process(Steinberg::Vst::ProcessData &data) {
        //--- Read inputs parameter changes-----------
        if (data.inputParameterChanges) {

            Steinberg::int32 numParamsChanged  = data.inputParameterChanges->getParameterCount();
            for (Steinberg::int32 index = 0; index < numParamsChanged; index++) {

                if (auto* paramQueue = data.inputParameterChanges->getParameterData(index)) {

                    Steinberg::Vst::ParamValue value;
                    Steinberg::int32 sampleOffset;
                    Steinberg::int32 numPoints = paramQueue->getPointCount();
                    if (numPoints > 0) {
                        paramQueue->getPoint(numPoints - 1, sampleOffset, value);
                    }

                    switch (paramQueue->getParameterId()) {
                        case kBypassId:
                            mGate = value >= 0.5;
                            break;

                        case kGlobalMasterVolumeId:
                            //something
                            break;
                    }
                }
            }
        }

        // Processing implementation
        Steinberg::Vst::IEventList* events = data.inputEvents;
        if (events != nullptr) {
            Steinberg::int32 numEvents = events->getEventCount();

            for (Steinberg::int32 i = 0; i < numEvents; i++) {
                Steinberg::Vst::Event event{};
                if (events->getEvent(i, event) == Steinberg::kResultOk) {
                    switch (event.type) {
                        case Steinberg::Vst::Event::kNoteOnEvent:
                            mEngine.noteOn(event.noteOn.pitch, event.noteOn.velocity);
                            break;
                        case Steinberg::Vst::Event::kNoteOffEvent:
                            mEngine.noteOff(event.noteOff.pitch);
                            break;
                    }
                }
            }
        }

        // Parameter-flush calls can contain no audio buffers.
        if (data.numOutputs == 0 || data.outputs == nullptr || data.numSamples == 0) {
            return Steinberg::kResultOk;
        }

        auto& outputs = data.outputs[0];
        if (outputs.numChannels < 2 || outputs.channelBuffers32 == nullptr) {
            return Steinberg::kResultOk;
        }


        Steinberg::Vst::Sample32* outL = outputs.channelBuffers32[0];
        Steinberg::Vst::Sample32* outR = outputs.channelBuffers32[1];

        if (!outL || !outR) {
            return Steinberg::kResultOk;
        }

        mEngine.process(outL, outR, data.numSamples);

        return Steinberg::kResultOk;
    }

    Steinberg::tresult PsyBassProcessor::setState(Steinberg::IBStream *state) {
        return AudioEffect::setState(state);
    }

    Steinberg::tresult PsyBassProcessor::getState(Steinberg::IBStream *state) {
        return AudioEffect::getState(state);
    }
}
