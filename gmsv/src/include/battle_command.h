#ifndef __BATTLE_COMMAND_H__
#define __BATTLE_COMMAND_H__

void BattleCommandDispach(
	int fd,
	char *command
);

void BattleEncountOut(
	int charaindex
);

int BATTLE_CommandSend( int charaindex, char *pszCommand );

int BATTLE_MakeCharaString(
	int battleindex,
	char *pszCommand,	// 平乓仿弁正□树  请  燮
	int	size 			// 扔奶术
);

void BATTLE_CharSendAll( int battleindex );

int	BATTLE_PetDefaultCommand( int petindex );

void BATTLE_ActSettingSend( int battleindex );

#endif