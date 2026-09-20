//
// Created by adity on 20-09-2026.
//

#pragma once

#include "pluginterfaces/vst/vsttypes.h"

namespace psybass {
    enum PsyBassParams: Steinberg::Vst::ParamID {
        kBypassID = 100,

        kParamVolId = 102,
        kParamOnId = 1000
    };

}