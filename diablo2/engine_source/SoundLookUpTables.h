#pragma once

namespace m
{
    enum class eButtonSoundType
    {
        ButtonClick,
        ButtonHover,

        End,
    };

    std::wstring buttonAudioPaths[(int)eButtonSoundType::End] = {
        L"..\\Resources\\sound\\cursor\\button.wav",
        L"..\\Resources\\sound\\cursor\\pass.wav",
    };

    std::wstring buttonAudioMaterialNames[(int)eButtonSoundType::End] = {
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
    std::wstring playerRunAudioPath[(int)ePlayerRunSoundType::End][4] = {
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
    std::wstring playerVoiceAudioPath[(int)ePlayerRunSoundType::End][4] = {
       {
           L"..\\Resources\\sound\\combat\\player\\sorceress\\soft1.wav",
           L"..\\Resources\\sound\\combat\\player\\sorceress\\soft3.wav",
           L"..\\Resources\\sound\\combat\\player\\sorceress\\soft4.wav",
           L"..\\Resources\\sound\\combat\\player\\sorceress\\soft5.wav",
       },
    };
    enum class ePlayerSkillSoundType
    {
        
    };
}
