//
// Created by adity on 14-09-2026.
//

#include "plugin/controller.h"
#include "plugin/psybass_cids.h"

#include "pluginterfaces/base/ibstream.h"


namespace psybass {
    Steinberg::tresult PsyBassController::initialize(Steinberg::FUnknown *context) {
        auto result = EditControllerEx1::initialize(context);

        if (result != Steinberg::kResultOk) {
            return result;
        }

        // Create parameters

        return Steinberg::kResultOk;
    }

    Steinberg::tresult PsyBassController::terminate() {
        return EditControllerEx1::terminate();
    }

    Steinberg::tresult PsyBassController::setComponentState(Steinberg::IBStream *state) {
        return EditControllerEx1::setComponentState(state);
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
