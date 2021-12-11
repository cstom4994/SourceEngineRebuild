//============================ AdV Software, 2019 ============================//
//
//	Vance Weapon script parsing
//
//============================================================================//

#ifndef	VANCE_WEAPON_PARSE_H
#define	VANCE_WEAPON_PARSE_H

#include "weapon_parse.h"

class VanceWeaponInfo_t : public FileWeaponInfo_t
{
public:
	VanceWeaponInfo_t();

	virtual void Parse(KeyValues *pKeyValuesData, const char *szWeaponName);
	
	char		szCameraAttachment[MAX_WEAPON_STRING];
	bool		bHaveCamera;
	float		flCameraMovementScale;
	bool		bHasFirstDrawAnim;  // Does this weapon have a first draw animation the first time it's picked up?
	char		szMuzzleFlashTexture[MAX_WEAPON_STRING];

	float		roundsPerMinute;

	int			iWeaponLength;
	Vector		vCollisionOffset;
	QAngle		angCollisionRotation;

	Vector		vIronsightOffset;
	QAngle		recoilMin; // If we don't want randomness, just use the min
	QAngle		recoilMax;
};

#endif // VANCE_WEAPON_PARSE_H