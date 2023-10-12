#pragma once
//#include "SkillLookUpTables.h"

namespace m
{
    enum class eButtonSoundType
    {
        ButtonClick,
        ButtonHover,

        End,
    };

    static std::wstring buttonAudioPaths[(int)eButtonSoundType::End] = {
        L"..\\Resources\\sound\\cursor\\button.wav",
        L"..\\Resources\\sound\\cursor\\pass.wav",
    };

    static std::wstring buttonAudioMaterialNames[(int)eButtonSoundType::End] = {
        L"buttonClick",
        L"buttonHover",
    };

    enum class ePlayerRunSoundType
    {
        PlayerStoneRun,
        PlayerOStoneRun,
        PlayerSandRun,
        End,
    };
    static std::wstring playerRunAudioPath[(int)ePlayerRunSoundType::End][4] = {
        {
            L"..\\Resources\\sound\\ambient\\footstep\\LightIStoneRun1.wav",
            L"..\\Resources\\sound\\ambient\\footstep\\LightIStoneRun2.wav",
            L"..\\Resources\\sound\\ambient\\footstep\\LightIStoneRun3.wav",
            L"..\\Resources\\sound\\ambient\\footstep\\LightIStoneRun4.wav",
        },
        {
            L"..\\Resources\\sound\\ambient\\footstep\\LightOStoneRun1.wav",
            L"..\\Resources\\sound\\ambient\\footstep\\LightOStoneRun2.wav",
            L"..\\Resources\\sound\\ambient\\footstep\\LightOStoneRun3.wav",
            L"..\\Resources\\sound\\ambient\\footstep\\LightOStoneRun4.wav",
        },
        {
            L"..\\Resources\\sound\\ambient\\footstep\\LightSandRun1.wav",
            L"..\\Resources\\sound\\ambient\\footstep\\LightSandRun2.wav",
            L"..\\Resources\\sound\\ambient\\footstep\\LightSandRun3.wav",
            L"..\\Resources\\sound\\ambient\\footstep\\LightSandRun4.wav",
        },
    };
    enum class ePlayerVoiceSoundType
    {
        Hit,
        End,
    };
    static std::wstring playerVoiceAudioPath[(int)ePlayerRunSoundType::End][4] = {
       {
           L"..\\Resources\\sound\\combat\\player\\sorceress\\soft1.wav",
           L"..\\Resources\\sound\\combat\\player\\sorceress\\soft3.wav",
           L"..\\Resources\\sound\\combat\\player\\sorceress\\soft4.wav",
           L"..\\Resources\\sound\\combat\\player\\sorceress\\soft5.wav",
       },
    };
    static std::wstring skillSoundPath[37][3] = {
        {
        L"..\\Resources\\sound\\skill\\sorceress\\icebolt1.wav",
        L"..\\Resources\\sound\\skill\\sorceress\\icebolt2.wav",
        L"..\\Resources\\sound\\skill\\sorceress\\icebolt3.wav",
        },
        {},
        {
        L"..\\Resources\\sound\\skill\\sorceress\\novaice.wav",
        L"..\\Resources\\sound\\skill\\sorceress\\novaice.wav",
        L"..\\Resources\\sound\\skill\\sorceress\\novaice.wav",
        },
        {
        L"..\\Resources\\sound\\skill\\sorceress\\icebolt1.wav",
        L"..\\Resources\\sound\\skill\\sorceress\\icebolt2.wav",
        L"..\\Resources\\sound\\skill\\sorceress\\icebolt3.wav",
        },
        {},
        {
        L"..\\Resources\\sound\\skill\\sorceress\\icespike1.wav",
        L"..\\Resources\\sound\\skill\\sorceress\\icespike2.wav",
        L"..\\Resources\\sound\\skill\\sorceress\\icespike3.wav",
        },
        {
        L"..\\Resources\\sound\\skill\\sorceress\\blizzloop.wav",
        L"..\\Resources\\sound\\skill\\sorceress\\blizzloop.wav",
        L"..\\Resources\\sound\\skill\\sorceress\\blizzloop.wav",
        },
        {},
        {
        L"..\\Resources\\sound\\skill\\sorceress\\icespike1.wav",
        L"..\\Resources\\sound\\skill\\sorceress\\icespike2.wav",
        L"..\\Resources\\sound\\skill\\sorceress\\icespike3.wav",
        },
        {},

        {
        L"..\\Resources\\sound\\skill\\sorceress\\chargedbolt1.wav",
        L"..\\Resources\\sound\\skill\\sorceress\\chargedbolt2.wav",
        L"..\\Resources\\sound\\skill\\sorceress\\chargedbolt3.wav",
        },
        {},
        {
        L"..\\Resources\\sound\\skill\\sorceress\\telekinesis.wav",
        L"..\\Resources\\sound\\skill\\sorceress\\telekinesis.wav",
        L"..\\Resources\\sound\\skill\\sorceress\\telekinesis.wav",
        },
        {
        L"..\\Resources\\sound\\skill\\sorceress\\novaelec.wav",
        L"..\\Resources\\sound\\skill\\sorceress\\novaelec.wav",
        L"..\\Resources\\sound\\skill\\sorceress\\novaelec.wav",
        },
        {
        L"..\\Resources\\sound\\skill\\sorceress\\lightning1.wav",
        L"..\\Resources\\sound\\skill\\sorceress\\lightning2.wav",
        L"..\\Resources\\sound\\skill\\sorceress\\lightning3.wav",
        },
{},
        {
        L"..\\Resources\\sound\\skill\\sorceress\\teleport.wav",
        L"..\\Resources\\sound\\skill\\sorceress\\teleport.wav",
        L"..\\Resources\\sound\\skill\\sorceress\\teleport.wav",
        },
        {
        L"..\\Resources\\sound\\skill\\sorceress\\thundercast.wav",
        L"..\\Resources\\sound\\skill\\sorceress\\thundercast.wav",
        L"..\\Resources\\sound\\skill\\sorceress\\thundercast.wav",
        },
        {},
        {},

        {
        L"..\\Resources\\sound\\skill\\sorceress\\firebolt1.wav",
        L"..\\Resources\\sound\\skill\\sorceress\\firebolt2.wav",
        L"..\\Resources\\sound\\skill\\sorceress\\firebolt3.wav",
        },
        {},
        {
        L"..\\Resources\\sound\\skill\\sorceress\\infernoloop.wav",
        L"..\\Resources\\sound\\skill\\sorceress\\infernoloop.wav",
        L"..\\Resources\\sound\\skill\\sorceress\\infernoloop.wav",
        },
        {},
        {
        L"..\\Resources\\sound\\skill\\sorceress\\fireball1.wav",
        L"..\\Resources\\sound\\skill\\sorceress\\fireball2.wav",
        L"..\\Resources\\sound\\skill\\sorceress\\fireball3.wav",
        },
        {},
        {},
        {
        L"..\\Resources\\sound\\skill\\sorceress\\meteorlaunch.wav",
        L"..\\Resources\\sound\\skill\\sorceress\\meteorlaunch.wav",
        L"..\\Resources\\sound\\skill\\sorceress\\meteorlaunch.wav",
        },
        {},
        {},

    };
    static bool skillSoundLoop[32] = {

    };
}
