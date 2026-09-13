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
}
