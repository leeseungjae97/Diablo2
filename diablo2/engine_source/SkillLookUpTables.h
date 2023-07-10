#pragma once

namespace m
{
	enum class eColdSkillType
	{
		blizzard,
		chillingArmor,
		clacialSpike,
		coldMastery,
		frostNova,
		frozenArmor,
		frozenOrb,
		iceBlast,
		iceBolt,
		shiverArmor,
		END
	};
	enum class eFireSkillType
	{
		blaze,
		enchant,
		fireBall,
		fireBolt,
		fireMastery,
		fireWall,
		hydra,
		inferno,
		meteor,
		warmth,
		END
	};
	enum class eLightningSkillType
	{
		chainLightning,
		chargedBolt,
		energyShield,
		lightning,
		lightningMastery,
		nove,
		staticField,
		telekinesis,
		teleport,
		thunderStorm,
		END
	};
	std::wstring wsColdSkillNames[(int)eColdSkillType::END] = {
		L"blizzardIcon",
		L"chillingArmorIcon",
		L"clacialSpikeIcon",
		L"coldMasteryIcon",
		L"frostNovaIcon",
		L"frozenArmorIcon",
		L"frozenOrbIcon",
		L"iceBlastIcon",
		L"iceBoltIcon",
		L"shiverArmorIcon",
	};

	std::wstring wsFireSkillNames[(int)eFireSkillType::END] = {
		L"blazeIcon",
		L"enchantIcon",
		L"fireBallIcon",
		L"fireBoltIcon",
		L"fireMasteryIcon",
		L"fireWallIcon",
		L"hydraIcon",
		L"infernoIcon",
		L"meteorIcon",
		L"warmthIcon",
	};

	std::wstring wsLightningSkillNames[(int)eLightningSkillType::END] = {
		L"chainLightningIcon",
		L"chargedBoltIcon",
		L"energyShieldIcon",
		L"lightningIcon",
		L"lightningMasteryIcon",
		L"noveIcon",
		L"staticFieldIcon",
		L"telekinesisIcon",
		L"teleportIcon",
		L"thunderStormIcon",
	};

	std::wstring wsColdSkillClickNames[(int)eColdSkillType::END] = {
		L"blizzardClickIcon",
		L"chillingArmorClickIcon",
		L"clacialSpikeClickIcon",
		L"coldMasteryClickIcon",
		L"frostNovaClickIcon",
		L"frozenArmorClickIcon",
		L"frozenOrbClickIcon",
		L"iceBlastClickIcon",
		L"iceBoltClickIcon",
		L"shiverArmorClickIcon",
	};

	std::wstring wsFireSkillClickNames[(int)eFireSkillType::END] = {
		L"blazeClickIcon",
		L"enchantClickIcon",
		L"fireBallClickIcon",
		L"fireBoltClickIcon",
		L"fireMasteryClickIcon",
		L"fireWallClickIcon",
		L"hydraClickIcon",
		L"infernoClickIcon",
		L"meteorClickIcon",
		L"warmthClickIcon",
	};

	std::wstring wsLightningSkillClickNames[(int)eLightningSkillType::END] = {
		L"chainLightningClickIcon",
		L"chargedBoltClickIcon",
		L"energyShieldClickIcon",
		L"lightningClickIcon",
		L"lightningMasteryClickIcon",
		L"noveClickIcon",
		L"staticFieldClickIcon",
		L"telekinesisClickIcon",
		L"teleportClickIcon",
		L"thunderStormClickIcon",
	};
}