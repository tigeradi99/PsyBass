//
// Created by adity on 14-09-2026.
//

#include "plugin/controller.h"
#include "plugin/psybass_cids.h"
#include "plugin/params.h"

#include "base/source/fstreamer.h"
#include "pluginterfaces/base/ibstream.h"
#include "pluginterfaces/vst/ivstplugview.h"
#include "vstgui/plugin-bindings/vst3editor.h"

#include <cstring>


namespace psybass {
    Steinberg::tresult PsyBassController::initialize(Steinberg::FUnknown *context) {
        auto result = EditControllerEx1::initialize(context);

        if (result != Steinberg::kResultOk) {
            return result;
        }

        // Create parameters
        parameters.addParameter(
            STR16("Bypass"),
            nullptr,
            1,
            0,
            Steinberg::Vst::ParameterInfo::kCanAutomate | Steinberg::Vst::ParameterInfo::kIsBypass,
            kBypassId);

        parameters.addParameter(
            STR16("Master Volume"),
            STR16(""),
            0,
            1.0,
            Steinberg::Vst::ParameterInfo::kCanAutomate,
            kGlobalMasterVolumeId);

        auto* osc1Waveform = new Steinberg::Vst::StringListParameter(
                STR16("Osc1 Waveform"),
                kOsc1ModeId
            );
        osc1Waveform->appendString(STR16("Sine"));
        osc1Waveform->appendString(STR16("Square"));
        osc1Waveform->appendString(STR16("Saw"));
        parameters.addParameter(osc1Waveform);

        return Steinberg::kResultOk;
    }

    Steinberg::tresult PsyBassController::terminate() {
        return EditControllerEx1::terminate();
    }

    Steinberg::tresult PsyBassController::setComponentState(Steinberg::IBStream *state) {
        if (!state) {
            return Steinberg::kInvalidArgument;
        }

        Steinberg::IBStreamer streamer(state, kLittleEndian);
        bool bypass = false;
        double osc1Waveform = 0.0;

        if (!streamer.readBool(bypass)) {
            return Steinberg::kResultFalse;
        }
        if (!streamer.readDouble(osc1Waveform)) {
            return Steinberg::kResultFalse;
        }

        setParamNormalized(kBypassId, bypass ? 1.0 : 0.0);
        setParamNormalized(kOsc1ModeId, osc1Waveform);

        return Steinberg::kResultOk;
    }

    Steinberg::IPlugView * PsyBassController::createView(Steinberg::FIDString name) {
        if (name && std::strcmp(name, Steinberg::Vst::ViewType::kEditor) == 0) {
            return new VSTGUI::VST3Editor(
                this,
                "view",
                "psybass.uidesc"
                );
        }

        return nullptr;
    }

    Steinberg::tresult PsyBassController::setState(Steinberg::IBStream *state) {
        return EditControllerEx1::setState(state);
    }

    Steinberg::tresult PsyBassController::getState(Steinberg::IBStream *state) {
        return EditControllerEx1::getState(state);
    }

    Steinberg::tresult PsyBassController::setParamNormalized(Steinberg::Vst::ParamID tag,
        Steinberg::Vst::ParamValue value) {
        return EditControllerEx1::setParamNormalized(tag, value);
    }

    Steinberg::tresult PsyBassController::getParamStringByValue(Steinberg::Vst::ParamID tag,
        Steinberg::Vst::ParamValue valueNormalized, Steinberg::Vst::String128 string) {
        return EditControllerEx1::getParamStringByValue(tag, valueNormalized, string);
    }

    Steinberg::tresult PsyBassController::getParamValueByString(Steinberg::Vst::ParamID tag,
        Steinberg::Vst::TChar *string, Steinberg::Vst::ParamValue &valueNormalized) {
        return EditControllerEx1::getParamValueByString(tag, string, valueNormalized);
    }
}
