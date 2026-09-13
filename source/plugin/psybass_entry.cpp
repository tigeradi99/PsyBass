//
// Created by adity on 13-09-2026.
//

#include "plugin/processor.h"
#include "plugin/controller.h"
#include "plugin/psybass_cids.h"
#include "plugin/version.h"

#include "public.sdk/source/main/pluginfactory.h"

BEGIN_FACTORY_DEF(
    "Adi",
    "https://example.com",
    "mailto:example@example.com"
)

    DEF_CLASS2(
        INLINE_UID_FROM_FUID(psybass::kPsyBassProcessorUID),
        PClassInfo::kManyInstances,
        kVstAudioEffectClass,
        "Psybass",
        Vst::kDistributable,
        "Instrument|Synth",
        FULL_VERSION_STR,
        kVstVersionString,
        psybass::PsyBassProcessor::createInstance
    )

    DEF_CLASS2(
        INLINE_UID_FROM_FUID(psybass::kPsyBassControllerUID),
        PClassInfo::kManyInstances,
        kVstComponentControllerClass,
        "Psybass Controller",
        0,
        "",
        FULL_VERSION_STR,
        kVstVersionString,
        psybass::PsyBassController::createInstance
    )

END_FACTORY