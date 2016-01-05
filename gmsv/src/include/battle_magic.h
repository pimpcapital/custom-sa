#ifndef _BATTLE_MAGIC_H_
#define _BATTLE_MAGIC_H_

#define MAGIC_EFFECT_USER	100600
#define SPR_heal	100601
#define SPR_heal2	100602
#define SPR_heal3	100603
#define SPR_tyusya	100604
#define SPR_hoshi	100605

enum{
	BFUKI_CAPTUREUP,
	BFUKI_END
};


enum{
	PC_KIND_NONE,
	PC_KIND_ATTACK,
	PC_KIND_DEFENSE,
	PC_KIND_QUICK,
	PC_KIND_CHARM,
	PC_KIND_CAPTURE,
	PC_KIND_END
};

int	MAGIC_Recovery_Battle(
	int charaindex,
	int toindex,
	int magicindex,
	int mp
);

int	MAGIC_FieldAttChange_Battle(
	int charaindex,
	int toindex,
	int marray,
	int mp
);

int	MAGIC_StatusChange_Battle(
	int charaindex,
	int toindex,
	int marray,
	int mp
);

#ifdef _MAGIC_DEEPPOISON
int	MAGIC_StatusChange_Battle2(
	int charaindex,
	int toindex,
	int marray,
	int mp
);
#endif

#ifdef _OTHER_MAGICSTAUTS
int	MAGIC_MagicStatusChange_Battle( int charaindex, int toNo, int marray, int mp );

#endif

int	MAGIC_MagicDef_Battle(
	int charaindex,
	int toNo,
	int marray,
	int mp
);

void BATTLE_MultiRecovery(
	int battleindex,
	int attackNo,
	int toNo,
	int kind,
	int power,
	int per,
	int UseEffect,
	int RecevEffect

);

#ifdef _IMPRECATE_ITEM
void BATTLE_ImprecateRecovery(
	int battleindex,
	int attackNo,
	int toNo,
	int kind,
	int powers,
	int rounds,
	int UseEffect,
	int RecevEffect
);
#endif
void BATTLE_MultiStatusChange(
	int battleindex,
	int attackNo,
	int toNo,
	int status,
	int turn,
	int UseEffect,
	int RecevEffect,
	int Success
);

#ifdef _OTHER_MAGICSTAUTS
void BATTLE_MultiMagicStatusChange(
	int battleindex,
	int attackNo,
	int toNo,
	int status,
	int turn,
	int UseEffect,
	int RecevEffect,
	int nums
);
#endif

void BATTLE_MultiMagicDef(
	int battleindex,
	int attackNo,
	int toNo,
	int kind,
	int count,
	int UseEffect,
	int RecevEffect
);

void BATTLE_MultiParamChange(
	int battleindex,
	int attackNo,
	int toNo,
	int kind,
	int power,
	int par,
	int UseEffect,
	int RecevEffect
);

int	MAGIC_FieldAttChange_Battle(
	int charaindex,
	int toNo,
	int marray,
	int mp 
);

int	BATTLE_FieldAttChange(
	int charaindex,
	char *pArg
);

void BATTLE_MultiAttReverse(
	int battleindex,
	int attackNo,
	int toNo,
	int UseEffect,
	int RecevEffect
);


void BATTLE_MultiStatusRecovery(
	int battleindex,
	int attackNo,
	int toNo,
	int status,
	int UseEffect,
	int RecevEffect
);

int	MAGIC_StatusRecovery_Battle(
	int charaindex,
	int toNo,
	int marray,
	int mp
);

void BATTLE_MultiRessurect(
	int battleindex,
	int attackNo,
	int toNo,
	int power,
	int per,
	int UseEffect,
	int RecevEffect
);

void BATTLE_MultiCaptureUp(
	int battleindex,
	int attackNo,
	int toNo,
	int power,
	int UseEffect,
	int RecevEffect
);
//
//***********************************************************

//****************************************************************
//
// 竣濮井日汊唾允月热诸
//
int	MAGIC_Ressurect_Battle(
	int charaindex, // 井仃月谛及奶件犯永弁旦
	int toNo, 		// 井仃日木月谛及奶件犯永弁旦
	int marray, 	// magicindex
	int mp 			// MP
);
//  岳  仄凶日 TRUE
//  撩  仄凶日 FALSE
//****************************************************************

//****************************************************************
//
// 箪岭及  鳖毛允月热诸
//
int	MAGIC_AttReverse_Battle(
	int charaindex, // 井仃月谛及奶件犯永弁旦
	int toNo, 		// 井仃日木月谛及奶件犯永弁旦
	int marray, 	// magicindex
	int mp 			// MP
);
//  岳  仄凶日 TRUE
//  撩  仄凶日 FALSE
//****************************************************************
//****************************************************************
//
//   凯    祭允月热诸
//
int	MAGIC_CaptureUp_Battle(
	int charaindex, // 井仃月谛及奶件犯永弁旦
	int toNo, 		// 井仃日木月谛及奶件犯永弁旦
	int marray, 	// magicindex
	int mp 			// MP
);
//  岳  仄凶日 TRUE
//  撩  仄凶日 FALSE
//****************************************************************

//***********************************************************
//
//    芊羁匹  醒及平乓仿弁正□毛汊唾今六月今日卞  芊  豢毛馨笛
//
void BATTLE_MultiResAndDef( 
	int battleindex, 	// 田玄伙奶件犯永弁旦
	int attackNo,		// 井仃月谛  寞
	int toNo,			// 井仃日木月谛  寞
	int power,			// 湘  荚汊袄
	int per,			// ⊙井＂
	int kind, 			//   芊  豢及潘  
	int count, 			// 窒荚  什井
	int UseEffect,		// 银丹谛及巨白尼弁玄
	int RecevEffect		// 井仃日木月谛及巨白尼弁玄
);
//
//***********************************************************
//****************************************************************
//
// 汊唾≈  芊  豢毛芨尹月热诸
//
int	MAGIC_ResAndDef_Battle(
	int charaindex, // 井仃月谛及奶件犯永弁旦
	int toNo, 		// 井仃日木月谛及奶件犯永弁旦
	int marray, 	// magicindex
	int mp 			// MP
);
//  岳  仄凶日 TRUE
//  撩  仄凶日 FALSE
//****************************************************************

#ifdef _ATTACK_MAGIC
int MAGIC_AttMagic_Battle( int charaindex , int toNo , int marray , int mp );
#ifdef _FIX_MAGICDAMAGE
void BATTLE_MultiAttMagic( int battleindex, int attackNo, int toNo,
						  int attIdx ,int FieldAttr ,int Power, int MagicLv);

#else
void BATTLE_MultiAttMagic( int battleindex , int attackNo , int toNo , int attIdx , int FieldAttr , int Power );
#endif
int MAGIC_AttMagic_Battle( int charaindex , int toNo , int marray , int mp );

#endif



#ifdef _MAGIC_TOCALL
int MAGIC_ToCallDragon_Battle( int charaindex , int toNo , int marray , int mp );

void BATTLE_MultiToCallDragonMagic( int battleindex, int attackNo, int toNo,
						  int attIdx ,int FieldAttr ,int Power, int ImageNo);

#endif

#ifdef _Item_ReLifeAct
void BATTLE_MultiReLife( int battleindex, int attackNo, int toNo, int power, int RecevEffect );
#endif
#ifdef _MAGIC_WEAKEN
int	MAGIC_ParamChange_Turn_Battle(int charaindex,int toNo,int marray,int mp);
void BATTLE_MultiParamChangeTurn( int battleindex,int attackNo,int toNo,int status,int UseEffect,int RecevEffect,int turn, int Success);
#endif
int BATTLE_MagicEffect(	int battleindex,int attackNo,int ToList[],int MyEffect,int ToEffect );

#ifdef _PETSKILL_FIREKILL
void BATTLE_MultiAttMagic_Fire( int battleindex, int attackNo, int defNo,
						  int FieldAttr , int Power);
#endif
#endif
