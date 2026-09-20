//
// Created by adity on 14-09-2026.
//

#include "plugin/controller.h"
#include "plugin/psybass_cids.h"
#include "plugin/params.h"

#include "base/source/fstreamer.h"
#include "pluginterfaces/base/ibstream.h"


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

        if (!streamer.readBool(bypass)) {
            return Steinberg::kResultFalse;
        }

        setParamNormalized(kBypassId, bypass ? 1.0 : 0.0);

        return Steinberg::kResultOk;
    }

    Steinberg::IPlugView * PsyBassController::createView(Steinberg::FIDString name) {
        return EditControllerEx1::createView(name);
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
