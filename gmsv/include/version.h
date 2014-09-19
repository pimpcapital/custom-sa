#ifndef __VERSION_H__
#define __VERSION_H__
#include "correct_bug.h"  //BUG FIX

/*Server 锟芥本锟斤拷锟斤拷*/
#define _NEW_SERVER_
#define _SERVER_NUMS

#define UNIQUE_KEYCODEITEM	100
#define UNIQUE_KEYCODEPET	"i"
//#define _DEFAULT_PKEY "Wonwonwon"	// (锟缴匡拷锟斤拷)( 石锟斤拷 6.0 )
//#define _RUNNING_KEY  "11111111"  // (锟缴匡拷锟斤拷)( 石锟斤拷 6.0 )
//#define _DEFAULT_PKEY "ttttttttt"   // (锟缴匡拷锟斤拷)( 石锟斤拷 6.0 )
//#define _RUNNING_KEY  "20041215"    // (锟缴匡拷锟斤拷)( 石锟斤拷 6.0 )

/* -------------------------------------------------------------------
 * 专锟斤拷锟斤拷锟斤拷锟斤拷庄园锟斤拷锟斤拷锟睫革拷	锟斤拷员锟斤拷小瑜★拷锟斤拷勋锟斤拷志伟锟斤拷小锟斤拷
 */

/*
锟睫革拷装园锟斤拷锟斤拷锟斤拷式锟斤拷
Account Server 锟斤拷式:
	acfamily.h	MAX_FMPOINT要锟睫革拷
Account Server 锟斤拷戏锟斤拷锟斤拷:
	saac/family/fmpoint/db_fmpoint锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷庄园锟斤拷锟斤拷锟斤拷锟斤拷瓒?	庄园锟斤拷锟斤拷图锟斤拷|庄园锟斤拷锟斤拷锟斤拷锟斤拷|庄园锟斤拷锟斤拷锟斤拷锟斤拷|庄园锟藉长图锟斤拷|庄园锟节斤拷之锟斤拷庄|占锟斤拷庄园之锟斤拷锟斤拷 index|占锟斤拷庄园之锟斤拷锟斤拷 name|占锟斤拷庄园之锟斤拷锟斤拷锟桔猴拷锟斤拷锟斤拷值
	锟斤拷锟界：
		100|607|563|1041|1|3|shan|3132238
		200|73|588|2031|2|||
Game Server 锟斤拷式锟斤拷
	version.h FAMILY_MAXHOME锟斤拷MANORNUM要锟斤拷锟斤拷
	family.c	 FM_PKFLOOR	锟斤拷锟斤拷锟斤拷战锟斤拷图锟斤拷
				 FAMILY_RidePet() 锟斤拷锟斤拷锟斤拷锟斤拷宄わ拷锟酵硷拷锟?				 FAMILY_LeaderFunc() 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷牒痠d
	npcutil.c addNpcFamilyTax function锟斤拷锟斤拷锟斤拷锟?庄园图锟斤拷%100)锟斤拷为庄园税锟秸诧拷锟斤拷
Game Server 锟斤拷戏锟斤拷锟斤拷:
	gmsv_v2/data/npc/family/manorsman.arg* id锟斤拷锟斤拷锟斤拷
	gmsv_v2/data/npc/family/scheduleman.arg* id锟斤拷锟斤拷锟斤拷
*/

#define _FAMILY_MANORNUM_CHANGE	 // CoolFish 锟斤拷锟斤拷锟睫革拷装园锟斤拷锟斤拷(4.0)
#ifdef _FAMILY_MANORNUM_CHANGE
#define FAMILY_MAXHOME 4        // (4.0) 锟斤拷锟斤拷莸锟?#define MANORNUM       4        // (4.0) 庄园锟斤拷锟斤拷
#define FMPOINTNUM     4        // (4.0) 锟叫据碉拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟?#endif
#define _FMVER21                 // (锟缴匡拷锟斤拷) 锟斤拷锟斤拷职锟狡癸拷锟斤拷  
#define _PERSONAL_FAME           // (锟缴匡拷锟斤拷) Arminius 8.30 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟? 
// -------------------------------------------------------------------
//专锟斤拷锟斤拷石锟斤拷锟筋动锟皆讹拷锟斤拷		锟斤拷员锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷

#define _EVERYONE_RIDE           // (锟缴匡拷锟斤拷) Robin 0924 锟斤拷锟狡斤拷锟? 
// -------------------------------------------------------------------
//专锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷	锟斤拷员锟斤拷锟斤拷志
#define _ATTACK_MAGIC            // (锟缴匡拷锟斤拷)	锟结供战锟斤拷锟叫的癸拷锟斤拷锟斤拷锟斤拷锟斤拷
#define _ADD_ACTION              // (锟缴匡拷锟斤拷) 一锟斤拷NPC锟斤拷锟斤拷状锟斤拷锟斤拷锟借定

// -------------------------------------------------------------------
//专锟斤拷锟斤拷锟斤拷锟斤、锟斤拷锟竭憋拷锟斤拷		锟斤拷员锟斤拷小锟?#define _UNIQUE_P_I              // (锟缴匡拷锟斤拷) CoolFish 2001/10/11 

// -------------------------------------------------------------------
//专锟斤拷锟斤拷锟铰帮拷锟斤拷锟斤储锟斤拷pn 锟斤拷 锟斤拷锟斤拷锟剿?1018	锟斤拷员锟斤拷锟斤拷勋
#define _NEWSAVE                 // (锟缴匡拷锟斤拷) Robin
#define _STORECHAR               // (锟缴匡拷锟斤拷) Robin
#define _DROPCHECK               // (锟缴匡拷锟斤拷) Robin 锟斤拷止锟截革拷锟斤拷锟斤拷锟斤拷
#define _DROPCHECK2              // (锟缴匡拷锟斤拷) Robin 锟斤拷止锟截革拷锟斤拷锟斤拷锟斤拷
// -------------------------------------------------------------------
//专锟斤拷 : 锟斤拷锟斤拷锟斤拷	锟斤拷员 : 锟斤拷锟?#define _PET_TRANS               // (锟缴匡拷锟斤拷) 锟斤拷锟斤拷转锟斤拷锟斤拷
#define _NEW_WARPMAN             // (锟缴匡拷锟斤拷) NPC锟斤拷锟斤拷WARP锟斤拷锟斤拷
#define _PET_TALK                // (锟缴匡拷锟斤拷) 锟斤拷锟斤拷曰锟?#define _PET_LIMITLEVEL          // (锟缴匡拷锟斤拷) 锟斤拷锟斤拷锟斤拷锟斤拷(锟斤拷锟斤拷)
#define _MAP_NOEXIT              // (锟缴匡拷锟斤拷) 锟斤拷锟斤拷锟酵硷拷锟斤拷锟皆拷锟?原锟角伙拷指锟斤拷锟斤拷
// -------------------------------------------------------------------
// 专锟斤拷锟斤拷GM指锟筋、锟姐级Reload		锟斤拷员锟斤拷小锟?#define _GMRELOAD                // (锟缴匡拷锟斤拷) CoolFish: 2001/11/12 
// -------------------------------------------------------------------
// 专锟斤拷锟斤拷锟斤拷锟斤拷锟铰?锟斤拷员锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟叫★拷
#define _GAMBLE_ROULETTE         // (锟缴匡拷锟斤拷) 锟斤拷锟?锟侥筹拷锟斤拷锟斤拷	锟斤拷锟斤拷小锟斤拷  
#define _FIX_GAMBLENUM           // (锟缴匡拷锟斤拷) 锟斤拷锟斤拷锟斤拷锟斤拷 : 锟斤拷锟竭扣伙拷锟?
#define _GAMBLE_BANK             // (锟缴匡拷锟斤拷) 锟斤拷锟? 锟侥筹拷锟斤拷锟斤拷  
#define _DROPSTAKENEW            // (锟缴匡拷锟斤拷) CoolFish:  锟侥筹拷锟斤拷注  
#define _PETRACE                 // (锟缴匡拷锟斤拷) CoolFish: 2001/12/3 锟斤拷锟斤竞锟劫筹拷  
#define _NEWEVENT                // (锟缴匡拷锟斤拷) CoolFish: 2001/12/5 锟铰碉拷锟斤拷锟斤拷锟斤拷锟? 
// -------------------------------------------------------------------
//专锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷	锟斤拷员锟斤拷锟斤拷锟斤拷
#define _ITEM_FIRECRACKER        // (锟缴匡拷锟斤拷) 战锟斤拷锟斤拷使锟矫憋拷锟节匡拷锟皆帮拷锟斤拷锟斤拷锟斤拷锟斤拷
// -------------------------------------------------------------------
//锟铰癸拷锟杰ｏ拷庄园PK锟斤拷锟斤拷(锟斤拷缍拷锟?		锟斤拷员锟斤拷志伟锟斤拷志锟斤拷
#define _MANOR_PKRULE            // (锟缴匡拷锟斤拷)
// -------------------------------------------------------------------
// 锟铰癸拷锟杰ｏ拷锟铰癸拷锟斤拷&锟斤拷锟斤技锟斤拷		锟斤拷员锟斤拷锟斤拷锟?#define _PSKILL_FALLGROUND       // (锟缴匡拷锟斤拷) 锟斤拷锟斤技锟斤拷  (锟斤拷锟斤拷锟斤拷)
#define _ENEMY_FALLGROUND        // (锟缴匡拷锟斤拷) NPC 锟斤拷锟斤拷
#define _BATTLE_NEWPOWER         // (锟缴匡拷锟斤拷)
#define _Item_MoonAct            // (锟缴匡拷锟斤拷) 锟斤拷锟斤拷锟斤拷鼗锟?#define _Item_DeathAct           // (锟缴匡拷锟斤拷) 锟斤拷魔锟斤拷锟斤拷锟斤拷
#define _Item_PetAct             // (锟缴匡拷锟斤拷) 驯锟睫斤拷指
#define _Item_ReLifeAct          // (锟缴匡拷锟斤拷) 锟斤拷要itemset1.txt 锟斤拷锟杰匡拷) 锟斤拷锟斤拷锟斤拷锟斤拷
#define _BATTLESTEAL_FIX         // (锟缴匡拷锟斤拷) 锟斤拷锟斤拷偷锟斤拷
#define _CFREE_petskill          // (锟缴匡拷锟斤拷) 锟斤拷要petskill1.txt 锟斤拷锟杰匡拷) 锟斤拷学习锟斤拷锟斤技锟杰硷拷锟斤拷
#define _data_newreadfile        // (锟缴匡拷锟斤拷) 锟铰碉拷server setup.cf 锟斤拷锟斤拷 锟斤拷 itemset1.txt petskill1.txt 锟斤拷锟斤拷锟铰碉拷
#define _ITEM_MAXUSERNUM         // (锟缴匡拷锟斤拷) 锟斤拷 itemset1.txt ITEM 使锟矫达拷锟斤拷
// -------------------------------------------------------------------
//锟铰癸拷锟杰ｏ拷锟斤拷锟斤拷锟斤拷锟?   锟斤拷员锟斤拷锟斤拷锟?#define _PET_TALKPRO             // (锟缴匡拷锟斤拷) 锟斤拷锟斤拷曰锟斤拷锟角? & 锟斤拷 END
#define _PRO_NPCFIX              // (锟缴匡拷锟斤拷) NPC锟斤拷锟杰硷拷强
#define _PRO_BATTLEENEMYSKILL    // (锟缴匡拷锟斤拷) 战锟斤拷锟斤拷强  锟斤拷锟斤拷NPC锟斤拷AI锟斤拷锟斤拷
#define _NEW_WARPPOINT           // (锟缴匡拷锟斤拷) 锟斤拷锟酵碉拷锟斤拷锟斤拷锟斤拷锟斤拷卸锟絎ARP
#define _FIX_CHECKITEM           // (锟缴匡拷锟斤拷) 锟斤拷锟竭诧拷锟斤拷锟角凤拷锟斤拷锟?// -------------------------------------------------------------------
//锟铰癸拷锟杰ｏ拷锟斤拷锟斤拷锟? 锟斤拷员锟斤拷小锟斤拷,WON
#define _ADD_ENCOUNT             // (锟缴匡拷锟斤拷) WON 锟斤拷锟接碉拷锟斤拷锟斤拷锟斤拷锟斤拷锟睫硷拷 
#define _WON_PET_MAIL_LOG        // (锟缴匡拷锟斤拷) WON 锟斤拷壹某锟斤拷锟?LOG 
// -------------------------------------------------------------------
// 锟铰癸拷锟杰ｏ拷锟斤拷锟斤拷锟斤拷锟斤拷  4.0  锟斤拷员锟斤拷锟斤拷锟? 志伟 , 锟斤拷锟斤拷 , 志锟斤拷
//#define _LOSE_FINCH_           // (锟斤拷锟缴匡拷) ANDY 锟斤拷雀锟斤拷锟斤拷
#define _FIX_FAMILY_PK_LIMIT     // (锟缴匡拷锟斤拷) WON 锟斤拷锟斤拷锟斤拷战庄园锟斤拷锟斤拷前十锟斤拷锟轿帮拷锟绞拷锟?#define _ADD_POOL_ITEM           // (锟缴匡拷锟斤拷) WON 锟斤拷锟接可寄放的碉拷锟斤拷
#define _ITEM_METAMO             // (锟缴匡拷锟斤拷) shan metamo sprite. code:robin->shan
#define _ENEMY_ATTACK_AI         // (锟缴匡拷锟斤拷) shan enemy attack mode. code:shan  
#define _ITEM_TIME_LIMIT         // (锟缴匡拷锟斤拷) shan time limit of item. code:shan
#define _MIND_ICON               // (锟缴匡拷锟斤拷) shan show icon from char mind. code:shan
#define _BATTLENPC_WARP_PLAYER   // (锟缴匡拷锟斤拷) shan npc warp player when n round. code:shan
#define _ITEM_WARP_FIX_BI        // (锟缴匡拷锟斤拷) shan fix bbi to bi. code:shan
#define _SKILL_DAMAGETOHP        // (锟缴匡拷锟斤拷) ANDY 锟斤拷血锟斤拷 
#define _Skill_MPDAMAGE          // (锟缴匡拷锟斤拷) ANDY MP锟剿猴拷
#define _WAEI_KICK               // (锟缴匡拷锟斤拷) ANDY 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷
#define _BATTLE_TIMESPEED        // (锟缴匡拷锟斤拷) ANDY 战锟斤拷时锟斤拷 锟斤拷锟斤拷(锟斤拷锟斤拷锟斤拷锟截匡拷锟斤拷锟斤拷锟斤拷锟劫癸拷锟斤拷)
#define _FIXBUG_ATTACKBOW        // (锟缴匡拷锟斤拷) ANDY 锟斤拷锟斤拷锟斤拷锟绞癸拷锟酵讹拷锟斤拷锟斤拷锟絙ug
#define _NPCCHANGE_PLAYERIMG     // (锟缴匡拷锟斤拷) ANDY NPC锟侥憋拷锟斤拷锟酵硷拷锟? 强锟斤拷锟斤拷锟斤拷,锟斤拷锟斤拷锟酵硷拷锟?(锟斤拷锟斤拷)
#define _ITEM_ATTSKILLMAGIC      // (锟缴匡拷锟斤拷) ANDY 锟斤拷锟竭硷拷锟斤拷  
#define _EQUIT_DEFMAGIC          // (锟缴匡拷锟斤拷) ANDY 锟斤拷魔装锟斤拷
#define _FIX_MAGICDAMAGE         // (锟缴匡拷锟斤拷) ANDY 锟斤拷锟斤拷魔锟斤拷锟斤拷式 锟斤拷锟节匡拷锟斤拷
#define _ITEM_CONSTITUTION       // (锟缴匡拷锟斤拷) ANDY 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟?#define _MAGIC_REHPAI            // (锟缴匡拷锟斤拷) ANDY 锟斤拷血AI
#define _TRANSER_MAN             // (锟缴匡拷锟斤拷) ANDY 锟斤拷锟斤拷师
#define _TAKE_ITEMDAMAGE         // (锟缴匡拷锟斤拷) ANDY 锟斤拷锟斤拷锟斤拷  ITEMSET2
#define _FIX_FIRECRACKER         // (锟缴匡拷锟斤拷) ANDY 锟斤拷锟斤拷 锟斤拷锟斤拷
#define _FIX_ITEMPROB            // (锟缴匡拷锟斤拷) ANDY 锟斤拷锟斤拷 锟斤拷锟斤拷锟斤拷
#define _ADD_DEAMGEDEFC          // (锟缴匡拷锟斤拷) ANDY 锟斤拷锟斤拷锟剿猴拷 & 锟斤拷锟接癸拷锟斤拷  ITEMSET2
#define _FIX_MAXCHARMP           // (锟缴匡拷锟斤拷) ANDY MP锟斤拷锟斤拷
#define _ITEM_INSLAY             // (锟缴匡拷锟斤拷) ANDY 锟解宝石 锟斤拷锟斤拷
#define _ITEMSET2_ITEM           // (锟缴匡拷锟斤拷) ANDY ITEMSET2
#define _ITEM_NPCCHANGE          // (锟缴匡拷锟斤拷) ANDY 锟斤拷锟斤拷 (锟斤拷锟斤拷, 锟斤拷锟斤拷)
#define _PETSKILL_FIXITEM        // (锟缴匡拷锟斤拷) ANDY 锟睫革拷 && 同锟斤拷锟斤拷锟斤拷
#define _FIX_SETWORKINT          // (锟缴匡拷锟斤拷) ANDY (FIXWORKINT)
#define _ITEM_ADDEXP             // (锟缴匡拷锟斤拷) vincent  锟斤拷锟斤拷:指锟斤拷时锟斤拷锟斤拷锟斤拷锟接撅拷锟斤拷值锟斤拷锟斤拷锟斤拷
#define _ITEM_ADDEXP2            // 锟角癸拷时锟斤拷锟斤拷锟斤拷奂锟?Robin
#define _FIX_METAMORIDE          // (锟缴匡拷锟斤拷) ANDY
#define _CHECK_ITEMDAMAGE        // (锟缴匡拷锟斤拷) 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷  7/26
#define _SKILL_WILDVIOLENT_ATT   // (锟缴匡拷锟斤拷) vincent  锟借技:锟今暴癸拷锟斤拷
#define _MAGIC_WEAKEN            // (锟缴匡拷锟斤拷) vincent  锟斤拷锟斤拷:锟斤拷锟斤拷
#define _SKILL_WEAKEN            // (锟缴匡拷锟斤拷) vincent  锟借技:锟斤拷锟斤拷//锟斤拷要锟斤拷#define _MAGIC_WEAKEN
#define _SKILL_SPEEDY_ATT        // (锟缴匡拷锟斤拷) vincent  锟借技:锟斤拷锟劫癸拷锟斤拷
#define _SKILL_GUARDBREAK2       // (锟缴匡拷锟斤拷) vincent  锟借技:锟狡筹拷锟斤拷锟?
#define _SKILL_SACRIFICE         // (锟缴匡拷锟斤拷) vincent  锟借技:锟斤拷援
#define _PSKILL_MODIFY           // (锟缴匡拷锟斤拷) ANDY 锟斤拷锟斤拷强锟斤拷锟斤拷锟斤拷
#define _PSKILL_MDFYATTACK       // (锟缴匡拷锟斤拷) ANDY 锟斤拷锟斤拷转锟斤拷锟斤拷锟斤拷
#define _MAGIC_DEFMAGICATT       // (锟缴匡拷锟斤拷) ANDY 魔锟斤拷锟斤拷锟斤拷
#define _MAGIC_SUPERWALL         // (锟缴匡拷锟斤拷) ANDY 锟斤拷诜锟斤拷锟?#define _OTHER_MAGICSTAUTS       // (锟缴匡拷锟斤拷) ANDY 
#define _SKILL_TOOTH             // (锟缴匡拷锟斤拷) ANDY   锟斤拷锟斤拷
#define _MAGIC_DEEPPOISON        // (锟缴匡拷锟斤拷) vincent  锟斤拷锟斤拷:锟界毒
#define _MAGIC_BARRIER           // (锟缴匡拷锟斤拷) vincent  锟斤拷锟斤拷:魔锟斤拷
#define _MAGIC_NOCAST            // (锟缴匡拷锟斤拷) vincent  锟斤拷锟斤拷:锟斤拷默
#define _ITEM_CRACKER            // (锟缴匡拷锟斤拷) vincent  锟斤拷锟斤拷:锟斤拷锟斤拷 //锟斤拷要锟斤拷#define _MIND_ICON
#define _SKILL_DEEPPOISON        // (锟缴匡拷锟斤拷) vincent  锟借技:锟界毒 //锟斤拷要锟斤拷#define _MAGIC_DEEPPOISON
#define _SKILL_BARRIER           // (锟缴匡拷锟斤拷) vincent  锟借技:魔锟斤拷 //锟斤拷要锟斤拷#define _MAGIC_BARRIER
#define _SKILL_ROAR              // (锟缴匡拷锟斤拷) vincent  锟借技:锟斤拷锟?锟斤拷锟斤拷锟斤拷)
#define _SKILL_REFRESH           // (锟缴匡拷锟斤拷) vincent  锟借技:锟斤拷锟斤拷斐Ｗ刺?#define _ITEM_REFRESH            // (锟缴匡拷锟斤拷) vincent  锟斤拷锟斤拷斐Ｗ刺拷锟斤拷锟?#define _MAGIC_TOCALL            // (锟缴匡拷锟斤拷) kjl     锟劫伙拷  02/06/20 kjl  

// -------------------------------------------------------------------
// 锟铰癸拷锟杰ｏ拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷  锟斤拷员锟斤拷锟斤拷锟?#define _ITEMSET3_ITEM           // (锟缴匡拷锟斤拷) ANDY itemset3.txt
#define _SUIT_ITEM               // (锟缴匡拷锟斤拷) ANDY (锟斤拷装) 锟斤拷锟斤拷锟斤拷 锟斤拷锟斤拷itemset3.txt
#define _PETSKILL_SETDUCK        // (锟缴匡拷锟斤拷) ANDY 锟斤拷锟芥技锟斤拷
#define _VARY_WOLF               // (锟缴匡拷锟斤拷) pet skill : vary wolf. code:shan
// -------------------------------------------------------------------
// 锟铰癸拷锟杰ｏ拷专锟斤拷5.0    锟斤拷员锟斤拷
#define _USEWARP_FORNUM          // (锟缴匡拷锟斤拷) ANDY 锟斤拷锟斤拷锟斤拷毛 锟斤拷锟斤拷锟斤拷
#define _IMPRECATE_ITEM          // (锟缴匡拷锟斤拷) ANDY 锟斤拷锟斤拷锟斤拷锟?锟斤拷锟斤拷锟斤拷
#define _MAGICPET_SKILL          // (锟缴匡拷锟斤拷) ANDY 魔锟斤拷锟借技锟斤拷
#define _ITEM_CHECKWARES         // (锟缴匡拷锟斤拷) ANDY 锟斤拷锟酵诧拷锟斤拷
#define _NPC_REPLACEMENT         // (锟缴匡拷锟斤拷) ANDY 锟矫伙拷战锟斤拷npc
#define _TYPE_TOXICATION         // (锟缴匡拷锟斤拷) ANDY 锟叫讹拷锟睫凤拷锟斤拷血

// -------------------------------------------------------------------
// 锟铰癸拷锟杰ｏ拷5.0追锟接诧拷锟斤拷    锟斤拷员锟斤拷
#define _AVID_TRADETRYBUG        // (锟缴匡拷锟斤拷) ANDY 锟斤拷止锟斤拷锟斤拷锟叫讹拷锟斤拷/锟斤拷锟斤拷 锟斤拷(锟斤拷锟斤拷)锟绞硷拷 石锟斤拷
#define _ASSESS_SYSEFFICACY      // (锟缴匡拷锟斤拷) ANDY 锟斤拷锟斤拷系统效锟斤拷 12/04 锟斤拷锟斤拷
#define _ASSESS_SYSEFFICACY_SUB  // (锟缴匡拷锟斤拷) Robin 锟斤拷锟斤拷系统效锟斤拷 锟斤拷锟接硷拷锟斤拷诨锟饺?#define _ITEM_ORNAMENTS          // (锟缴匡拷锟斤拷) ANDY 装锟轿碉拷锟斤拷  12/04 锟斤拷锟斤拷  //锟斤拷锟芥部
#define _CHIKULA_STONE           // (锟缴匡拷锟斤拷) ANDY 锟斤拷锟斤拷锟街?12/04 锟斤拷锟斤拷  //锟斤拷锟斤拷锟斤拷 锟斤拷锟?#define _SEND_EFFECT             // (锟缴匡拷锟斤拷) WON  AC锟斤拷锟斤拷雪锟斤拷锟斤拷锟斤拷锟斤拷锟叫?12/04 锟斤拷锟斤拷
#define _PETMAIL_DEFNUMS         // (锟缴匡拷锟斤拷) ANDY 锟斤拷锟斤拷锟绞硷拷锟斤拷锟斤拷
#define _PETSKILL_TIMID          // (锟缴匡拷锟斤拷) ANDY 锟借技-锟斤拷战
#define _PETS_SELECTCON          // (锟缴匡拷锟斤拷) ANDY 锟斤拷锟斤不锟缴碉拷选锟斤拷战
#define _CHRISTMAS_REDSOCKS      // (锟缴匡拷锟斤拷) ANDY 圣锟斤拷锟斤拷锟斤拷
#define _FIX_ARRAYBUG            // (锟缴匡拷锟斤拷) ANDY 锟斤拷锟斤拷array 锟斤拷位
#define _USER_CHARLOOPS          // (锟缴匡拷锟斤拷) ANDY 锟斤拷锟斤拷锟斤拷锟絃OOP
#define _BATTLE_PROPERTY         // (锟缴匡拷锟斤拷) ANDY 战锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷
#define _PETSKILL_PROPERTY       // (锟缴匡拷锟斤拷) ANDY 锟斤拷锟斤拷魔锟睫宠技
#define _ITEM_FIXALLBASE         // (锟缴匡拷锟斤拷) ANDY 锟睫革拷之石
#define _ITEM_LOVERPARTY         // (锟缴匡拷锟斤拷) ANDY 锟斤拷锟剿节碉拷锟斤拷
#define _ITEM_FORUSERNAMES       // (锟缴匡拷锟斤拷) ANDY 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷
#define _BATTLECOMMAND_TIME      // (锟缴匡拷锟斤拷) ANDY 锟斤拷止锟斤拷铱锟斤拷锟斤拷锟?锟截猴拷战锟斤拷时锟斤拷)
#define _NPCENEMY_ADDPOWER       // (锟缴匡拷锟斤拷) ANDY 锟睫改癸拷锟斤拷锟斤拷锟斤拷锟街?

// -------------------------------------------------------------------
// 锟铰癸拷锟杰ｏ拷专锟斤拷6.0    锟斤拷员锟斤拷
//
#define _PETSKILL_CANNEDFOOD     // (锟缴匡拷锟斤拷) ANDY 锟斤拷锟斤技锟杰癸拷头  for 6.0
#define _TEST_DROPITEMS          // (锟缴匡拷锟斤拷) ANDY 锟斤拷锟皆讹拷锟斤拷
#define _MAP_WARPPOINT           // (锟缴匡拷锟斤拷) ANDY Map WarpPoint
#define _TREASURE_BOX            // (锟缴匡拷锟斤拷) ANDY 锟斤拷锟斤拷
#define _BENEMY_EVENTRUN         // (锟缴匡拷锟斤拷) ANDY 战锟斤拷npc锟斤拷锟斤拷锟?#define _BATTLE_ABDUCTII         // (锟缴匡拷锟斤拷) ANDY 锟斤拷途夥帮拷2
#define _BATTLE_LIGHTTAKE        // (锟缴匡拷锟斤拷) ANDY 锟缴癸拷锟斤拷
#define _BATTLE_ATTCRAZED        // (锟缴匡拷锟斤拷) ANDY 锟斤拷锟斤拷锟?#define _CAPTURE_FREES           // (锟缴匡拷锟斤拷) ANDY 锟斤拷抓锟斤拷锟斤拷
#define _THROWITEM_ITEMS         // (锟缴匡拷锟斤拷) 锟斤拷锟斤拷锟斤拷锟叫斤拷品
//--------------------------------------------------------------------------
//专锟斤拷 7.0  职业系统  锟斤拷员锟斤拷锟斤拷锟?志锟斤拷 锟斤拷锟?锟斤拷锟斤拷
#define _ACFMPK_LIST             // (锟缴匡拷锟斤拷) ANDY 锟斤拷锟斤拷锟秸斤拷斜锟斤拷锟斤拷锟?#define _NPC_NOSAVEPOINT         // (锟缴匡拷锟斤拷) ANDY 锟斤拷录锟姐不锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷
#define _PETSKILL2_TXT           // (锟缴匡拷锟斤拷) ANDY petskill2.txt
#define _PETSKILL_CHECKTYPE      // (锟缴匡拷锟斤拷) ANDY 锟斤拷锟斤技锟斤拷使锟斤拷时锟斤拷
#define _PETSKILL_TEAR           // (锟缴匡拷锟斤拷) ANDY 锟借技 撕锟斤拷锟剿匡拷
#define _ITEMSET4_TXT            // (锟缴匡拷锟斤拷) ANDY itemset4.txt
#define _PET_LOSTPET             // (锟缴匡拷锟斤拷) ANDY 锟斤拷失锟斤拷锟斤拷锟斤拷寻锟狡伙拷锟斤拷锟斤拷
#define _ITEMSET5_TXT            // (锟缴匡拷锟斤拷) ANDY itemset5.txt
#define _ITEMSET6_TXT            // (锟缴匡拷锟斤拷) ANDY itemset6.txt
#define _EQUIT_SEQUENCE          // (锟缴匡拷锟斤拷) ANDY 锟斤拷锟斤拷顺锟斤拷 锟斤拷要 itemset5.txt
#define _EQUIT_HITRIGHT          // (锟缴匡拷锟斤拷) ANDY 锟斤拷锟斤拷 锟斤拷要 itemset5.txt
#define _EQUIT_NEGLECTGUARD      // (锟缴匡拷锟斤拷) ANDY 锟斤拷锟斤拷目锟斤拷锟斤拷锟斤拷锟? 锟斤拷要 itemset6.txt
#define _FIX_MAX_GOLD            // (锟缴匡拷锟斤拷) WON ADD 锟斤拷锟斤拷锟斤拷锟斤拷锟角拷锟斤拷锟? 
#define _PET_SKILL_SARS          // (锟缴匡拷锟斤拷) WON ADD 锟斤拷煞锟斤拷锟斤拷
#define _SONIC_ATTACK            // (锟缴匡拷锟斤拷) WON ADD 锟斤拷锟斤拷锟斤拷锟斤拷
#define _NET_REDUCESEND          // (锟缴匡拷锟斤拷) ANDY 锟斤拷锟斤拷DB锟斤拷锟较达拷锟斤拷
#define _FEV_ADD_NEW_ITEM        // (锟缴匡拷锟斤拷) Change 锟斤拷锟接革拷锟斤拷锟截撅拷
#define _ALLDOMAN                // (锟缴匡拷锟斤拷) Syu ADD 锟斤拷锟叫帮拷NPC
#define _LOCKHELP_OK             // (锟缴匡拷锟斤拷) Syu ADD 锟斤拷锟缴硷拷锟斤拷战锟斤拷

//系统锟斤拷锟斤拷
#define _SIMPLIFY_ITEMSTRING     // (锟缴匡拷锟斤拷) ANDY 锟津化碉拷锟斤拷锟街达拷

#define _SIMPLIFY_PETSTRING      // (锟缴匡拷锟斤拷) ANDY 锟津化筹拷锟斤拷娴碉拷执锟?#define _SIMPLIFY_ITEMSTRING2    // (锟缴匡拷锟斤拷) ANDY 锟津化碉拷锟斤拷锟街达拷2
#define _WOLF_TAKE_AXE           // (锟缴匡拷锟斤拷) WON ADD 抓双头锟角碉拷锟斤拷锟斤拷
#define _FIX_UNNECESSARY         // (锟缴匡拷锟斤拷) ANDY 锟斤拷锟斤拷锟揭拷锟斤拷卸锟?#define _ITEM_MAGICRECOVERY      // (锟缴匡拷锟斤拷) ANDY 锟铰光镜锟斤拷
//9/17锟斤拷锟斤拷
#define _PETSKILL_GYRATE         // (锟缴匡拷锟斤拷) Change 锟借技:锟斤拷锟斤拷锟?#define _PETSKILL_RETRACE        // (锟缴匡拷锟斤拷) Change 锟借技:追锟斤拷锟斤拷锟斤拷
#define _PETSKILL_HECTOR         // (锟缴匡拷锟斤拷) Change 锟借技:锟斤拷锟斤拷
//10/13锟斤拷锟斤拷
#define _PETSKILL_FIREKILL       // (锟缴匡拷锟斤拷) Change 锟借技:锟斤拷锟斤拷锟斤拷杀
#define _PETSKILL_DAMAGETOHP     // (锟缴匡拷锟斤拷) Change 锟借技:锟斤拷锟铰匡拷锟斤拷(锟斤拷血锟斤拷锟侥憋拷锟斤拷) 
#define _PETSKILL_BECOMEFOX      // (锟缴匡拷锟斤拷) Change 锟借技:锟侥伙拷锟斤拷

//11/12锟斤拷锟斤拷
#define _PETSKILL_SHOWMERCY      // (锟缴匡拷) Change 锟借技:锟斤拷锟斤拷锟斤拷锟斤拷
#define _NPC_ActionFreeCmp       // (锟缴匡拷) Change 锟斤拷NPC锟斤拷锟斤拷锟斤拷锟斤拷碌谋冉戏锟绞?//--------------------------------------------------------------------------


//11/26
#define _NPC_NewDelPet           // (锟缴匡拷) Change 锟斤拷NPC锟斤拷锟斤拷删锟斤拷锟斤拷锟?原锟斤拷锟斤拷锟斤拷锟斤拷,只锟斤拷锟斤拷warpman使锟斤拷时锟斤拷锟缴癸拷,锟斤拷锟斤拷锟斤拷锟斤拷一锟斤拷锟斤拷一锟斤拷)
#define _ALLDOMAN_DEBUG          // (锟缴匡拷) Change 锟斤拷锟斤拷锟斤拷锟斤拷server锟斤拷锟斤拷锟叫帮拷锟斤拷失bug
//20031217
#define _CHRISTMAS_REDSOCKS_NEW  // (锟缴匡拷) Change 锟斤拷圣锟斤拷锟斤拷锟斤拷
#define _PETSKILL_COMBINED       // (锟缴匡拷) Change 锟借技:锟窖得猴拷涂 [锟桔猴拷魔锟斤拷(锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷取锟斤拷魔锟斤拷)]
//锟斤拷锟剿节活动
#define _NPC_ADDWARPMAN1         // (锟缴匡拷锟斤拷) Change npcgen_warpman锟斤拷锟接癸拷锟斤拷(锟借定锟斤拷锟斤拷锟斤拷锟斤拷瓒拷锟斤拷锟斤拷女锟斤拷锟斤拷)
#define _ITEM_QUITPARTY          // (锟缴匡拷锟斤拷) Change 锟斤拷锟斤拷锟缴⑹憋拷囟锟斤拷锟斤拷呒锟斤拷锟斤拷锟绞?#define _ITEM_ADDEQUIPEXP        // (锟缴匡拷) Change 装锟斤拷锟结经锟斤拷值锟斤拷锟斤拷
//2004/2/18
#define _ITEM_LVUPUP             // (锟缴匡拷) Change 突锟狡筹拷锟斤拷燃锟斤拷锟斤拷频锟揭?锟斤拷锟斤拷专锟斤拷)
//2004/02/25
#define _PETSKILL_BECOMEPIG      // (锟缴匡拷) Change 锟借技:锟斤拷锟斤拷锟斤拷
#define _ITEM_UNBECOMEPIG        // (锟缴匡拷) Change 锟斤拷锟斤拷锟斤拷锟侥斤拷药
#define _PET_TALKBBI             // (锟缴匡拷) Change 锟斤拷锟斤拷锟叫讹拷bbi
#define _ITEM_USEMAGIC           // (锟缴匡拷) Change 锟缴碉拷锟斤拷使锟斤拷魔锟斤拷
//2004/04/07
#define _ITEM_PROPERTY           // (锟缴匡拷) Change 锟侥憋拷锟斤拷锟斤拷锟皆碉拷锟斤拷
#define _SUIT_ADDENDUM           // (锟缴匡拷) Change 锟斤拷锟斤拷装锟斤拷锟接癸拷锟斤拷 (_SUIT_ITEM要锟斤拷)
//2004/05/05
#define _ITEM_CHECKDROPATLOGOUT  // (锟缴匡拷) Change 锟斤拷锟截硷拷录锟斤拷时锟斤拷锟斤拷锟斤拷锟睫登筹拷锟斤拷锟斤拷失锟斤拷锟斤拷,锟斤拷锟斤拷,锟斤拷锟缴回硷拷录锟斤拷
#define _FM_MODIFY               // 锟斤拷锟藉功锟斤拷锟睫革拷(锟斤拷锟斤拷)
#define _STANDBYPET              // Robin 锟斤拷锟斤拷锟斤拷
#define  _PETSKILL_OPTIMUM       // Robin 锟斤拷锟斤技锟杰达拷锟斤拷锟斤拷鸦锟?#define _MAGIC_OPTIMUM           // Robin Magic table 锟斤拷鸦锟?#define _AC_PIORITY              // Nuke 锟斤拷锟紸C锟斤拷锟斤拷锟斤拷权(锟缴匡拷)
// -------------------------------------------------------------------

//专锟斤拷 7.5  锟斤拷锟斤拷锟斤拷谢锟? 锟斤拷员锟斤拷锟斤拷勋 锟斤拷锟斤拷 小锟斤拷
// Terry define start -------------------------------------------------------------------
#define _MAP_TIME                // 锟斤拷锟斤拷锟酵?锟结倒锟斤拷(锟斤拷锟斤拷)

// Terry define end   -------------------------------------------------------------------
#define _ITEM_ADDPETEXP          // (锟缴匡拷) Change 锟斤拷锟接筹拷锟斤经锟斤拷值锟斤拷锟斤拷(锟缴吃此碉拷锟竭筹拷锟斤拷,平锟斤拷锟斤拷锟缴伙拷镁锟斤拷锟街?
#define _TRANS_6                 // (锟缴匡拷) Change 锟斤拷锟斤拷6转
#define _PET_2TRANS              // (锟缴匡拷) Change 锟斤拷锟斤拷2转
#define _PET_2LIMITLEVEL         // (锟缴匡拷) Change 锟斤拷锟斤拷锟斤拷锟?转锟斤拷锟斤拷锟斤拷
#define _MAGICSTAUTS_RESIST      // (锟缴匡拷) Change (锟斤拷锟斤拷)锟斤拷锟皆撅拷锟斤拷
#define _SUIT_TWFWENDUM          // (锟缴匡拷) Change 锟斤拷锟斤拷锟斤拷锟斤拷装锟斤拷锟斤拷 (_SUIT_ITEM要锟斤拷)
#define _EXCHANGEMAN_REQUEST_DELPET   // (锟缴匡拷) Change 锟斤拷exchangeman锟斤拷TYPE:REQUEST锟斤拷锟斤拷删锟斤拷锟斤拷锟?//--------------------------------------------------------------------------
#define _DEL_DROP_GOLD           // 删锟斤拷锟斤拷瞎锟绞憋拷锟绞拷锟? Robin
#define _ITEM_STONE              // cyg 锟斤拷值锟绞?#define _HELP_NEWHAND            // cyg 锟铰达拷锟斤拷色锟斤拷锟斤拷锟斤拷锟街碉拷锟斤拷)
#define _DEF_GETYOU              // cyg GM指锟斤拷 锟斤拷询锟皆硷拷锟斤拷锟斤拷  围锟节碉拷锟斤拷锟斤拷屎锟?#define _DEF_NEWSEND             // cyg GM指锟斤拷 锟斤拷锟斤拷锟斤拷锟绞憋拷杉泳锟斤拷锟揭诧拷刹锟斤拷锟?#define _DEF_SUPERSEND           // cyg GM指锟斤拷 锟缴达拷锟斤拷锟斤拷某锟绞猴拷为锟斤拷锟侥革拷锟斤拷3锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟?#define _SUIT_ADDPART3           // (锟缴匡拷) Change 锟斤拷装锟斤拷锟杰碉拷锟斤拷锟斤拷 锟截憋拷锟斤拷锟? 锟斤拷默锟斤拷锟斤拷锟斤拷锟? 锟斤拷锟斤拷锟? 锟斤拷锟斤拷锟? 锟斤拷锟斤拷锟?
#define _PETSKILL_2TIMID         // (锟缴匡拷) Change 锟斤拷战锟节讹拷锟斤拷(锟斤拷狮怒锟斤拷)
#define _TIME_TICKET             // Robin 锟斤拷时锟诫场 森锟斤拷捉锟斤拷锟斤拷
#define _HALLOWEEN_EFFECT        // 锟斤拷圣锟斤拷锟斤拷效
#define _ADD_reITEM              // (锟缴匡拷) Change 锟斤拷锟斤拷锟斤拷锟斤拷位锟秸革拷
#define _ADD_NOITEM_BATTLE       // 锟斤拷锟斤拷NPC锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟矫伙拷锟斤拷呋锟斤拷锟斤拷战锟斤拷
#define _PETSKILL_BATTLE_MODEL   // 锟斤拷锟斤技锟斤拷战锟斤拷模锟斤拷
#define _PETSKILL_ANTINTER       // (锟缴匡拷) Change 锟借技:锟斤拷之锟斤拷 锟轿匡拷_PETSKILL_2TIMID
#define _PETSKILL_REGRET         // (锟缴匡拷) Change 锟借技:锟斤拷锟斤拷一锟斤拷 锟轿匡拷_SONIC_ATTACK
//----------xfei--------------------------
#define  _NEW_RIDEPETS
#define _RIDE_CF 
#define _FM_LEADER_RIDE          // 锟藉长专锟斤拷锟斤拷锟?#define _RIDEMODE_20             // 2.0锟斤拷锟侥Ｊ?#define _ITEM_SETLOVER           // 锟斤拷楣︼拷锟?#define _ITEM_RIDE               // 驯锟斤拷装锟斤拷
#define _SHOW_VIP_CF             // 锟皆讹拷锟斤拷锟斤拷锟絍IP锟斤拷锟斤拷锟剿ｏ拷锟斤拷锟藉，锟斤拷锟斤拷锟绞撅拷锟绞?#define _VIP_RIDE                // 锟斤拷员锟斤拷诩锟?#define _VIP_ALL
#define _VIP_SERVER              // 锟斤拷员锟斤拷锟斤拷
#define _PLAYER_ANNOUNCE         // 锟斤拷锟斤拷锟斤拷锟?#define _MAKE_PET_CF             // 锟皆讹拷锟斤拷锟斤拷锟缴筹拷
#define _MAKE_PET_ABILITY        // 锟皆讹拷锟斤拷锟斤拷锟斤拷锟轿?#define _RELOAD_CF               // 锟截讹拷CF
#define _PET_UP                  // 锟缴硷拷锟斤拷硕锟斤拷锟斤拷某锟斤拷锟?#define _BATTLE_GOLD             // 锟斤拷取锟斤拷锟斤拷同时锟斤拷媒锟角?#define _ITEM_GOLD               // 锟斤拷钱锟斤拷锟斤拷品
#define _PLAYER_NUM              // 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟?#define _NEW_PLAYER_CF           // 锟斤拷锟斤拷状态锟斤拷锟斤拷
#define _TRANS_LEVEL_CF          // 转锟斤拷越160锟斤拷锟斤拷锟斤拷
#define _UNLAW_WARP_FLOOR        // 锟斤拷止锟斤拷锟酵碉拷锟斤拷
#define _UNREG_NEMA              // 锟斤拷止锟斤拷锟斤拷锟斤拷锟?#define _LOCK_IP                 // 锟斤拷IP
#define _POINT                   // 锟斤拷锟斤拷锟斤拷锟斤拷
#define _FIX_CHARLOOPS           // 锟斤拷锟斤拷锟侥э拷锟绞拷锟斤拷锟绞憋拷锟?#define _TALK_ACTION             // 说锟斤拷锟斤拷锟斤拷
#define _ENEMY_ACTION            // 锟斤拷也锟斤拷锟斤拷锟斤拷谢锟斤拷锟?#define _CHAR_CDKEY              // 锟斤拷止锟斤拷锟斤拷锟斤拷锟斤拷
#define _CHECK_PEPEAT            // 锟角凤拷锟斤拷锟斤拷锟斤拷
#define _SILENTZERO              // 锟斤拷锟斤拷锟斤拷品
#define _SAVE_GAME_ID            // 锟斤拷示锟斤拷锟斤拷姆锟斤拷锟斤拷锟斤拷锟?#define _AUTO_PK                 // 锟皆讹拷锟斤拷PK系统
//锟斤拷通锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷-------------------------------------
//#define _PUB_ALL
#ifdef _PUB_ALL
#define _CREATE_MM_1_2           // 锟斤拷锟斤拷锟斤拷品锟斤拷锟劫凤拷锟斤拷
#define _SendTo                  // 锟斤拷锟酵碉拷锟斤拷锟斤拷锟斤拷
#define _GET_BATTLE_EXP          // 锟斤拷锟斤拷锟斤拷锟斤拷
#define _NEW_PLAYER_CF           // 锟斤拷锟斤拷状态锟斤拷锟斤拷
#define _USER_EXP_CF             // 锟矫伙拷锟皆讹拷锟藉经锟斤拷
#define _TRANS_LEVEL_CF          // 转锟斤拷越160锟斤拷锟斤拷锟斤拷
#define _UNLAW_WARP_FLOOR        // 锟斤拷止锟斤拷锟酵碉拷锟斤拷
#define _UNREG_NEMA              // 锟斤拷止锟斤拷锟斤拷锟斤拷锟?#define _GM_ITEM                 // 锟斤拷锟紾M锟斤拷锟斤拷锟斤拷品
#define _GM_METAMO_RIDE          // GM锟斤拷锟斤拷锟斤拷锟斤拷锟叫筹拷
#define _GM_RIDE                 // GM锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟饺拷锟?#define _LOCK_IP                 // 锟斤拷IP
#define _POINT                   // 锟斤拷锟斤拷锟斤拷锟斤拷
#define _VIP_SERVER              // 锟斤拷员锟斤拷锟斤拷
#define _WATCH_FLOOR             // 锟皆讹拷锟斤拷晒锟秸斤拷锟酵?#define _BATTLE_FLOOR            // 锟皆讹拷锟斤拷强锟斤拷战锟斤拷锟斤拷图
#define _VIP_SHOP                // 锟斤拷员锟教碉拷
#define _LOOP_ANNOUNCE           // 循锟斤拷锟斤拷锟斤拷
#define _SKILLUPPOINT_CF         // 锟皆讹拷锟斤拷锟斤拷锟斤拷锟?#define _RIDELEVEL               // 锟皆讹拷锟斤拷锟斤拷锟斤拷锟斤拷燃锟?#define _REVLEVEL                // 锟皆讹拷锟斤拷原锟饺硷拷
#define _FM_ITEM                 // 锟斤拷锟斤拷锟斤拷锟?#define _LUCK_ITEM               // 锟斤拷锟斤拷锟斤拷锟?#define _NEW_PLAYER_RIDE         // 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟?#define _FIX_CHARLOOPS           // 锟斤拷锟斤拷锟侥э拷锟绞拷锟斤拷锟绞憋拷锟?#define _PLAYER_ANNOUNCE         // 锟斤拷锟斤拷锟斤拷锟?#define _BATTLE_GOLD             // 锟斤拷取锟斤拷锟斤拷同时锟斤拷媒锟角?#define _ITEM_GOLD               // 锟斤拷钱锟斤拷锟斤拷品
#define _PLAYER_NUM              // 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟?#define _PET_MM                  // 锟斤拷锟斤拷锟绞疢M
#define _MYSTERIOUS_GIFT         // 锟斤拷锟斤拷锟斤拷锟斤拷
#define _RELOAD_CF               // 锟截讹拷CF
#define _PET_UP                  // 锟缴硷拷锟斤拷硕锟斤拷锟斤拷某锟斤拷锟?#define _TRANS                   // 锟斤拷锟斤拷转锟斤拷锟斤拷锟斤拷
#define _TRANS_7                 // 实锟斤拷锟斤拷锟斤拷7转
#define _RIDEMODE_20             // 2.0锟斤拷锟侥Ｊ?#define _TALK_ACTION             // 说锟斤拷锟斤拷锟斤拷
#define _ENEMY_ACTION            // 锟斤拷也锟斤拷锟斤拷锟斤拷谢锟斤拷锟?#define _CHAR_CDKEY              // 锟斤拷止锟斤拷锟斤拷锟斤拷锟斤拷
#define _CHECK_PEPEAT            // 锟角凤拷锟斤拷锟斤拷锟斤拷
#define _SILENTZERO              // 锟斤拷锟斤拷锟斤拷品
#define _SAVE_GAME_ID            // 锟斤拷示锟斤拷锟斤拷姆锟斤拷锟斤拷锟斤拷锟?#endif
//锟斤拷员锟斤拷追锟接癸拷锟斤拷--------------------------------------
//#define _VIP_ALL
#ifdef _VIP_ALL
#define _VIP_RIDE                // 锟斤拷员锟斤拷诩锟?#define _AUTO_PK                 // 锟皆讹拷锟斤拷PK系统
#define _FM_METAMO               // 锟斤拷锟斤拷专锟矫憋拷锟斤拷锟街?#define _ITEM_METAMO_TIME        // 锟斤拷锟皆讹拷锟斤拷锟斤拷锟侥斤拷指
#define _SHOW_VIP_CF             // 锟皆讹拷锟斤拷锟斤拷锟絍IP锟斤拷锟斤拷锟剿ｏ拷锟斤拷锟藉，锟斤拷锟斤拷锟绞撅拷锟绞?#define _GM_KING                 // GM锟斤拷魔锟斤拷
#define _ANGEL_TIME              // 锟皆讹拷锟藉精锟斤拷锟劫伙拷时锟斤拷
#define _FM_POINT_PK             // 庄园锟斤拷锟藉互锟斤拷庄园
#define _PLAYER_MOVE             // 锟斤拷锟剿筹拷乒锟斤拷锟?#define _BATTLE_PK               // 强锟斤拷PK锟斤拷锟竭ｏ拷锟斤拷锟剿回硷拷录锟斤拷
#define _TRANS_7_NPC             // 锟斤拷锟斤拷锟斤拷转NPC
#define _DP_NPC                  // DP锟脚憋拷
#define _RIDE_CF                 // 锟皆讹拷锟斤拷锟斤拷锟?#define _PET_LEVEL_ITEM          // 锟斤拷锟斤拷燃锟斤拷锟斤拷锟斤拷锟狡?#define _FM_LEADER_RIDE          // 锟藉长专锟斤拷锟斤拷锟?#define _FM_JOINLIMIT            // 锟斤拷锟斤拷锟斤拷俅渭锟斤拷锟斤拷锟斤拷锟绞憋拷锟斤拷锟斤拷锟?#define _PET_BEATITUDE           // 锟斤拷锟斤拷祝锟斤拷
#define _ITEM_EFMETAMO           // 锟斤拷锟矫憋拷锟斤拷锟街?#define _OPEN_E_PETSKILL         // 锟斤拷锟脚筹拷锟斤拷E锟斤拷锟斤拷
#define _ITEM_RIDE               // 驯锟斤拷装锟斤拷
#define _MAKE_MAP                // 锟斤拷图锟斤拷锟斤拷
#define _MAKE_PET_CF             // 锟皆讹拷锟斤拷锟斤拷锟缴筹拷
#define _MAKE_PET_ABILITY        // 锟皆讹拷锟斤拷锟斤拷锟斤拷锟轿?#define _NEED_ITEM_ENEMY         // 抓锟斤拷锟斤拷锟斤拷锟斤拷品锟皆讹拷锟斤拷
#define _GET_MULTI_ITEM          // 一锟轿革拷锟斤拷锟斤拷品
#endif
//私锟斤拷锟芥本锟斤拷锟斤拷----------------------------------------
#define _DEFAULT_PKEY "cary"   // ( 石锟斤拷 2.5 )
#define _RUNNING_KEY  "cary"   // ( 石锟斤拷 2.5 )
#define _SA_VERSION 'L'
#define SERVER_VERSION "锟斤拷zoro锟斤拷GMSV_2.5锟斤拷锟斤拷锟?
//锟斤拷锟解功锟杰匡拷锟斤拷----------------------------------------

#define _BACK_DOOR               // 锟斤拷锟脚癸拷锟斤拷

//#define _DEBUG                   // 锟斤拷锟斤拷

//#define _DEBUG_RET               // 锟斤拷锟秸客伙拷锟斤拷锟斤拷莸锟斤拷锟?//#define _DEBUG_RET_CLI           // 锟斤拷锟秸客伙拷锟斤拷锟斤拷莸锟斤拷锟?//#define _DEBUG_SEND_CLI          // 锟斤拷锟酵客伙拷锟斤拷锟斤拷莸锟斤拷锟?//#define _GMSV_DEBUG              // GMSV锟斤拷锟斤拷锟斤拷息
#endif

