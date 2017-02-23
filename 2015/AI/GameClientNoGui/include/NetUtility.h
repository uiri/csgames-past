/* ------------------------------------------------------------------------------
** _________   _________      ________    _____      _____  ___________ _________
** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
**  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
**        \/        \/             \/         \/         \/        \/        \/ 
**
** NetUtility.h
** Some tools for the network
**
** Author: Samuel-Ricardo Carriere
** ------------------------------------------------------------------------------*/

#ifndef __NetUtility_h_
#define __NetUtility_h_

#include <iostream>
#include <stdio.h>

namespace NetUtility
{
	static std::string generateMoveCharacterPacket(int playerId, int characterId, double x, double z)
	{
		char numstr[21]; // enough to hold all numbers up to 64-bits
		sprintf(numstr, "%d", playerId);
		std::string message = "UpdateCharacter:";
		message += numstr;
		sprintf(numstr, "%d", characterId);
		message += ":";
		message += numstr;

		message += ":";
		sprintf(numstr, "%g", x);
		message += numstr;
		message += ":";
		sprintf(numstr, "%g", z);
		message += numstr;

		return message;
	}

	static std::string updatePlayer(int playerId)
	{
		char numstr[21]; // enough to hold all numbers up to 64-bits
		sprintf(numstr, "%d", playerId);
		std::string message = "UpdatePlayer:";
		message += numstr;

		return message;
	}
};

#endif // #ifndef __NetUtility_h_
