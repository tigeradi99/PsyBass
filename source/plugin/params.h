//
// Created by adity on 20-09-2026.
//

#pragma once

#include "pluginterfaces/vst/vsttypes.h"

namespace psybass {
    enum PsyBassParams: Steinberg::Vst::ParamID {
        // Global
        kBypassId = 100,
        kGlobalMasterVolumeId = 101,

        // Oscillator 1
        kOsc1OnId = 1000,
        kOsc1ModeId = 1001,
        kOsc1CoarseTuneId = 1002,
        kOsc1FineTuneId = 1003,

        // Envelope
        kAmpEnvAttackId = 2000,
        kAmpEnvDecayId = 2001,
        kAmpEnvSustainId = 2002,
        kAmpEnvReleaseId = 2003,

        // Filter
        kFilterCutoffId = 3000,
        kFilterResonanceId = 3001,
        kFilterMode = 3002
    };

}