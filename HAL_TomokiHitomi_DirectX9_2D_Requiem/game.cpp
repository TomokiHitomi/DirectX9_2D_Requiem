//=============================================================================
//
// 入力処理 [game.cpp]
// Author :  GP11B243 24 人見友基
//
//=============================================================================
#include "main.h"
#include "game.h"
#include "enemy.h"
#include "enemybullet.h"
#include "effect_close.h"
#include "close.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void SetGame(int nLevel);
void GameLevelEasy(void);
void GameLevelNormal(void);
void GameLevelHard(void);
void GameLevelBossEasy(void);
void GameLevelBossNormal(void);
void GameLevelBossHard(void);
void GameLevelBossUltimate(void);

void SetGameLevelBossSpecEasy(int nEnemy);
void SetGameLevelBossSpecNormal(int nEnemy);
void SetGameLevelBossSpecHard(int nEnemy);
void SetGameLevelBossSpecUltimate(int nEnemy);

void SetGameBossActionEasy(int nEnemy, int nMoveFlag);
void SetGameBossActionNormal(int nEnemy, int nMoveFlag);
void SetGameBossActionHard(int nEnemy, int nMoveFlag);
void SetGameBossActionUltimate(int nEnemy, int nMoveFlag);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
int g_nGameLevel;

//=============================================================================
// ゲームの初期化
//=============================================================================
void InitGame(void)
{
	int g_nGameLevel = 0;
}

//=============================================================================
// ゲームの更新処理
// ・エネミーのセット方法
// 	SetEnemy(外見_HP, POP,移動,バレットタイプ,バレットテクスチャ,バレットスピード,
//		バレット発射時間,バレット連射速度,バレット分割,バレットスピードチェンジ,
//			バレットOP2);
// 			※バレット○○は数字、その他はenum
//
// 	SetEnemy(nType, nPopType, nMoveType, nBulletType, nBulletTexture, nBulletSpeed, 
//	nBulletSetTime, nBulletAction, nBulletSplit, nBulletSpeedChange, nBulletOption2);
//=============================================================================
void UpdateGame(void)
{
	SetGame(g_nGameLevel);
	// バレット08用サンプル
	// 		SetEnemy(TYPE_N_RD, POP02, MOVE04, BTYPE08, BTEX_RD1, 4 * SCREEN_SCALING, 1, 1, 9, BSPD_NO, 0.005f);
}

//=============================================================================
// 難易度設定
//=============================================================================
void SetGameLevel(int nLevel)
{
	g_nGameLevel = nLevel;
	SetEnemyLevel(nLevel);
}

//=============================================================================
// 難易度設定
//=============================================================================
void SetGame(int nLevel)
{
	switch (nLevel)
	{
	case EASY:
		GameLevelEasy();
		break;
	case NORMAL:
		GameLevelNormal();
		break;
	case HARD:
		GameLevelHard();
		break;
	case BOSS_EASY:
		GameLevelBossEasy();
		break;
	case BOSS_NORMAL:
		GameLevelBossNormal();
		break;
	case BOSS_HARD:
		GameLevelBossHard();
		break;
	case BOSS_ULTIMATE:
		GameLevelBossUltimate();
		break;
	}
}

//=============================================================================
// イージー															イージー
//=============================================================================
void GameLevelEasy(void)
{
	int *count = GetCount();

	switch (*count)
	{

	//case 100: // テスト用
	//	//SetEnemy(TYPE_S_WH, POP04, MOVE07, BTYPE08, BTEX_VO1, 5 * SCREEN_SCALING, 60, 6, 11, BSPD_NO, 0.005f);
	//	break;
	case 200:
		SetEnemy(TYPE_N_RD, POP02, MOVE04, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 250:
		SetEnemy(TYPE_N_RD, POP02, MOVE04, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 300:
		SetEnemy(TYPE_N_RD, POP02, MOVE04, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 350:
		break;
	case 400:
		SetEnemy(TYPE_N_BU, POP04, MOVE04, BTYPE00, BTEX_BU1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 450:
		SetEnemy(TYPE_N_BU, POP04, MOVE04, BTYPE00, BTEX_BU1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 500:
		SetEnemy(TYPE_N_BU, POP04, MOVE04, BTYPE00, BTEX_BU1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 550:
		break;
	case 600:
		SetEnemy(TYPE_N_PI, POP03, MOVE04, BTYPE00, BTEX_PI1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 650:
		SetEnemy(TYPE_N_PI, POP03, MOVE04, BTYPE00, BTEX_PI1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 700:
		SetEnemy(TYPE_N_PI, POP03, MOVE04, BTYPE00, BTEX_PI1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 750:
		break;
	case 800:
		SetEnemy(TYPE_N_GR, POP07, MOVE04, BTYPE00, BTEX_GR1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 850:
		SetEnemy(TYPE_N_GR, POP07, MOVE04, BTYPE00, BTEX_GR1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 900:
		SetEnemy(TYPE_N_GR, POP07, MOVE04, BTYPE00, BTEX_GR1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		SetEnemy(TYPE_S_WH, POP04, MOVE07, BTYPE05, BTEX_LB1, 5 * SCREEN_SCALING, 1, 1, 11, BSPD_NO, NULL);
		break;
	case 950:
		break;
	case 1000:
		break;
	case 1050:
		break;
	case 1100:
		SetEnemy(TYPE_S_WH, POP02, MOVE07, BTYPE05, BTEX_LB1, 5 * SCREEN_SCALING, 1, 1, 11, BSPD_NO, NULL);
		break;
	case 1150:
		break;
	case 1200:
		break;
	case 1250:
		break;
	case 1300:
		SetEnemy(TYPE_S_WH, POP06, MOVE07, BTYPE05, BTEX_LB1, 5 * SCREEN_SCALING, 1, 1, 11, BSPD_NO, NULL);
		break;
	case 1350:
		SetEnemy(TYPE_N_GR, POP01, MOVE00, BTYPE00, BTEX_GR1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 1400:
		SetEnemy(TYPE_N_GR, POP01, MOVE00, BTYPE00, BTEX_GR1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 1450:
		SetEnemy(TYPE_N_GR, POP01, MOVE00, BTYPE00, BTEX_GR1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 1500:
		break;
	case 1550:
		SetEnemy(TYPE_S_WH, POP04, MOVE07, BTYPE05, BTEX_BU1, 5 * SCREEN_SCALING, 1, 1, 20, BSPD_NO, NULL);
		break;
	case 1600:
		break;
	case 1650:
		SetEnemy(TYPE_N_RD, POP07, MOVE01, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 1700:
		SetEnemy(TYPE_N_RD, POP07, MOVE01, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 1750:
		SetEnemy(TYPE_N_RD, POP07, MOVE01, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 1800:
		break;
	case 1850:
		break;
	case 1900:
		SetEnemy(TYPE_S_WH, POP04, MOVE07, BTYPE06, BTEX_LB1, 5 * SCREEN_SCALING, 1, 1, 20, BSPD_NO, NULL);
		break;
	case 1950:
		break;
	case 2000:
		SetEnemy(TYPE_S_WH, POP06, MOVE07, BTYPE06, BTEX_LB1, 5 * SCREEN_SCALING, 1, 1, 20, BSPD_NO, NULL);
		break;
	case 2050:
		break;
	case 2100:
		SetEnemy(TYPE_S_WH, POP02, MOVE07, BTYPE06, BTEX_LB1, 5 * SCREEN_SCALING, 1, 1, 20, BSPD_NO, NULL);
		break;
	case 2150:
		break;
	case 2200:
		break;
	case 2250:
		SetEnemy(TYPE_N_GR, POP01, MOVE02, BTYPE00, BTEX_GR1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 2300:
		SetEnemy(TYPE_N_GR, POP01, MOVE02, BTYPE00, BTEX_GR1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 2350:
		SetEnemy(TYPE_N_GR, POP01, MOVE02, BTYPE00, BTEX_GR1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		SetEnemy(TYPE_N_LB, POP07, MOVE02, BTYPE00, BTEX_LB1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 2400:
		SetEnemy(TYPE_N_LB, POP07, MOVE02, BTYPE00, BTEX_LB1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 2450:
		SetEnemy(TYPE_N_LB, POP07, MOVE02, BTYPE00, BTEX_LB1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 2500:
		break;
	case 2550:
		break;
	case 2600:
		break;
	case 2650:
		SetEnemy(TYPE_N_YE, POP02, MOVE02, BTYPE00, BTEX_YE1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 2700:
		SetEnemy(TYPE_N_YE, POP02, MOVE02, BTYPE00, BTEX_YE1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 2750:
		SetEnemy(TYPE_N_YE, POP02, MOVE02, BTYPE00, BTEX_YE1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 2800:
		break;
	case 2850:
		break;
	case 2900:
		SetEnemy(TYPE_S_PI, POP07, MOVE08, BTYPE01, BTEX_PI3, 5 * SCREEN_SCALING, 20, NULL, 20, BSPD_NO, NULL);
		break;
	case 2950:
		SetEnemy(TYPE_N_RD, POP02, MOVE04, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 3000:
		SetEnemy(TYPE_N_RD, POP02, MOVE04, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		SetEnemy(TYPE_S_PI, POP01, MOVE08, BTYPE01, BTEX_PI3, 5 * SCREEN_SCALING, 20, NULL, 20, BSPD_NO, NULL);
		break;
	case 3050:
		SetEnemy(TYPE_N_RD, POP02, MOVE04, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 3100:
		SetEnemy(TYPE_S_PI, POP04, MOVE08, BTYPE01, BTEX_PI3, 5 * SCREEN_SCALING, 20, NULL, 20, BSPD_NO, NULL);
		break;
	case 3150:
		SetEnemy(TYPE_N_BU, POP04, MOVE04, BTYPE00, BTEX_BU1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 3200:
		SetEnemy(TYPE_N_BU, POP04, MOVE04, BTYPE00, BTEX_BU1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 3250:
		SetEnemy(TYPE_N_BU, POP04, MOVE04, BTYPE00, BTEX_BU1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 3300:
		break;
	case 3350:
		break;
	case 3400:
		break;
	case 3450:
		break;
	case 3500:
		break;
	case 3550:
		SetEnemy(TYPE_S_WH, POP04, MOVE07, BTYPE05, BTEX_BU1, 5 * SCREEN_SCALING, 1, 1, 20, BSPD_NO, NULL);
		SetEnemy(TYPE_N_RD, POP07, MOVE01, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 3600:
		SetEnemy(TYPE_N_RD, POP07, MOVE01, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 3650:
		SetEnemy(TYPE_N_RD, POP07, MOVE01, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 3700:
		break;
	case 3750:
		SetEnemy(TYPE_N_RD, POP07, MOVE04, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 3800:
		SetEnemy(TYPE_N_RD, POP07, MOVE04, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		SetEnemy(TYPE_S_WH, POP04, MOVE07, BTYPE05, BTEX_LB1, 5 * SCREEN_SCALING, 1, 1, 11, BSPD_NO, NULL);
		break;
	case 3850:
		SetEnemy(TYPE_N_RD, POP07, MOVE04, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 3900:
		SetEnemy(TYPE_S_WH, POP02, MOVE07, BTYPE05, BTEX_LB1, 5 * SCREEN_SCALING, 1, 1, 11, BSPD_NO, NULL);
		break;
	case 3950:
		break;
	case 4000:
		SetEnemy(TYPE_S_WH, POP06, MOVE07, BTYPE05, BTEX_LB1, 5 * SCREEN_SCALING, 1, 1, 11, BSPD_NO, NULL);
		break;
	case 4050:
		break;
	case 4100:
		break;
	case 4150:
		SetEnemy(TYPE_N_GR, POP01, MOVE02, BTYPE00, BTEX_GR1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 4200:
		SetEnemy(TYPE_N_GR, POP01, MOVE02, BTYPE00, BTEX_GR1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 4250:
		SetEnemy(TYPE_N_GR, POP01, MOVE02, BTYPE00, BTEX_GR1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 4300:
		break;
	case 4350:
		SetEnemy(TYPE_N_LB, POP07, MOVE02, BTYPE00, BTEX_LB1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 4400:
		SetEnemy(TYPE_N_LB, POP07, MOVE02, BTYPE00, BTEX_LB1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 4450:
		SetEnemy(TYPE_N_LB, POP07, MOVE02, BTYPE00, BTEX_LB1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 4500:
		break;
	case 4550:
		SetEnemy(TYPE_N_YE, POP02, MOVE02, BTYPE00, BTEX_YE1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 4600:
		SetEnemy(TYPE_N_YE, POP02, MOVE02, BTYPE00, BTEX_YE1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 4650:
		SetEnemy(TYPE_N_YE, POP02, MOVE02, BTYPE00, BTEX_YE1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 4700:
		break;
	case 4750:
		break;
	case 4800:
		break;
	case 4850:
		break;
	case 4900:
		break;
	case 4950:
		break;
	case 5000:
		SetBossEnemy(TYPE_B_WH, POP04, MOVE09, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 20, 4, 3, BSPD_NO, NULL);
		break;
	}
}

//=============================================================================
// ノーマル															ノーマル
//=============================================================================
void GameLevelNormal(void)
{
	int *count = GetCount();

	switch (*count)
	{

	case 200:
		SetEnemy(TYPE_N_RD, POP02, MOVE04, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 250:
		SetEnemy(TYPE_N_RD, POP02, MOVE04, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 300:
		SetEnemy(TYPE_N_RD, POP02, MOVE04, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 350:
		break;
	case 400:
		SetEnemy(TYPE_N_BU, POP04, MOVE04, BTYPE00, BTEX_BU1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 450:
		SetEnemy(TYPE_N_BU, POP04, MOVE04, BTYPE00, BTEX_BU1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 500:
		SetEnemy(TYPE_N_BU, POP04, MOVE04, BTYPE00, BTEX_BU1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 550:
		break;
	case 600:
		SetEnemy(TYPE_N_PI, POP03, MOVE04, BTYPE00, BTEX_PI1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 650:
		SetEnemy(TYPE_N_PI, POP03, MOVE04, BTYPE00, BTEX_PI1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 700:
		SetEnemy(TYPE_N_PI, POP03, MOVE04, BTYPE00, BTEX_PI1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 750:
		break;
	case 800:
		SetEnemy(TYPE_N_GR, POP07, MOVE04, BTYPE00, BTEX_GR1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 850:
		SetEnemy(TYPE_N_GR, POP07, MOVE04, BTYPE00, BTEX_GR1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 900:
		SetEnemy(TYPE_N_GR, POP07, MOVE04, BTYPE00, BTEX_GR1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		SetEnemy(TYPE_S_WH, POP04, MOVE07, BTYPE05, BTEX_LB1, 5 * SCREEN_SCALING, 30, 10, 9, BSPD_NO, NULL);
		break;
	case 950:
		break;
	case 1000:
		break;
	case 1050:
		break;
	case 1100:
		SetEnemy(TYPE_S_WH, POP02, MOVE07, BTYPE05, BTEX_LB1, 5 * SCREEN_SCALING, 30, 10, 9, BSPD_NO, NULL);
		break;
	case 1150:
		break;
	case 1200:
		break;
	case 1250:
		break;
	case 1300:
		SetEnemy(TYPE_S_WH, POP06, MOVE07, BTYPE05, BTEX_LB1, 5 * SCREEN_SCALING, 30, 10, 9, BSPD_NO, NULL);
		break;
	case 1350:
		SetEnemy(TYPE_N_GR, POP01, MOVE00, BTYPE00, BTEX_GR1, 7 * SCREEN_SCALING, 20, 6, 1, BSPD_NO, NULL);
		break;
	case 1400:
		SetEnemy(TYPE_N_GR, POP01, MOVE00, BTYPE00, BTEX_GR1, 7 * SCREEN_SCALING, 20, 6, 1, BSPD_NO, NULL);
		break;
	case 1450:
		SetEnemy(TYPE_N_GR, POP01, MOVE00, BTYPE00, BTEX_GR1, 7 * SCREEN_SCALING, 20, 6, 1, BSPD_NO, NULL);
		break;
	case 1500:
		break;
	case 1550:
		SetEnemy(TYPE_S_WH, POP04, MOVE07, BTYPE05, BTEX_BU1, 5 * SCREEN_SCALING, 30, 10, 20, BSPD_NO, NULL);
		break;
	case 1600:
		break;
	case 1650:
		SetEnemy(TYPE_N_BU, POP07, MOVE01, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 20, 6, 1, BSPD_NO, NULL);
		break;
	case 1700:
		SetEnemy(TYPE_N_RD, POP07, MOVE01, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 20, 6, 1, BSPD_NO, NULL);
		break;
	case 1750:
		SetEnemy(TYPE_N_RD, POP07, MOVE01, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 20, 6, 1, BSPD_NO, NULL);
		break;
	case 1800:
		break;
	case 1850:
		break;
	case 1900:
		SetEnemy(TYPE_S_WH, POP04, MOVE07, BTYPE06, BTEX_LB1, 5 * SCREEN_SCALING, 30, 10, 11, BSPD_NO, NULL);
		break;
	case 1950:
		break;
	case 2000:
		SetEnemy(TYPE_S_WH, POP06, MOVE07, BTYPE06, BTEX_LB1, 5 * SCREEN_SCALING, 30, 10, 11, BSPD_NO, NULL);
		break;
	case 2050:
		break;
	case 2100:
		SetEnemy(TYPE_S_WH, POP02, MOVE07, BTYPE06, BTEX_LB1, 5 * SCREEN_SCALING, 30, 10, 11, BSPD_NO, NULL);
		break;
	case 2150:
		break;
	case 2200:
		break;
	case 2250:
		SetEnemy(TYPE_N_GR, POP01, MOVE02, BTYPE00, BTEX_GR1, 7 * SCREEN_SCALING, 20, 6, 1, BSPD_NO, NULL);
		break;
	case 2300:
		SetEnemy(TYPE_N_GR, POP01, MOVE02, BTYPE00, BTEX_GR1, 7 * SCREEN_SCALING, 20, 6, 1, BSPD_NO, NULL);
		break;
	case 2350:
		SetEnemy(TYPE_N_GR, POP01, MOVE02, BTYPE00, BTEX_GR1, 7 * SCREEN_SCALING, 20, 6, 1, BSPD_NO, NULL);
		SetEnemy(TYPE_N_LB, POP07, MOVE02, BTYPE00, BTEX_LB1, 7 * SCREEN_SCALING, 20, 6, 1, BSPD_NO, NULL);
		break;
	case 2400:
		SetEnemy(TYPE_N_LB, POP07, MOVE02, BTYPE00, BTEX_LB1, 7 * SCREEN_SCALING, 20, 6, 1, BSPD_NO, NULL);
		break;
	case 2450:
		SetEnemy(TYPE_N_LB, POP07, MOVE02, BTYPE00, BTEX_LB1, 7 * SCREEN_SCALING, 20, 6, 1, BSPD_NO, NULL);
		break;
	case 2500:
		break;
	case 2550:
		break;
	case 2600:
		break;
	case 2650:
		SetEnemy(TYPE_N_YE, POP02, MOVE02, BTYPE00, BTEX_YE1, 7 * SCREEN_SCALING, 20, 6, 1, BSPD_NO, NULL);
		break;
	case 2700:
		SetEnemy(TYPE_N_YE, POP02, MOVE02, BTYPE00, BTEX_YE1, 7 * SCREEN_SCALING, 20, 6, 1, BSPD_NO, NULL);
		break;
	case 2750:
		SetEnemy(TYPE_N_YE, POP02, MOVE02, BTYPE00, BTEX_YE1, 7 * SCREEN_SCALING, 20, 6, 1, BSPD_NO, NULL);
		break;
	case 2800:
		break;
	case 2850:
		break;
	case 2900:
		SetEnemy(TYPE_S_PI, POP07, MOVE08, BTYPE01, BTEX_PI3, 5 * SCREEN_SCALING, 40, NULL, 20, BSPD_NO, NULL);
		break;
	case 2950:
		SetEnemy(TYPE_N_RD, POP02, MOVE04, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 3000:
		SetEnemy(TYPE_N_RD, POP02, MOVE04, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		SetEnemy(TYPE_S_PI, POP01, MOVE08, BTYPE01, BTEX_PI3, 5 * SCREEN_SCALING, 40, NULL, 20, BSPD_NO, NULL);
		break;
	case 3050:
		SetEnemy(TYPE_N_RD, POP02, MOVE04, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 3100:
		SetEnemy(TYPE_S_PI, POP04, MOVE08, BTYPE01, BTEX_PI3, 5 * SCREEN_SCALING, 40, NULL, 20, BSPD_NO, NULL);
		break;
	case 3150:
		SetEnemy(TYPE_N_BU, POP04, MOVE04, BTYPE00, BTEX_BU1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 3200:
		SetEnemy(TYPE_N_BU, POP04, MOVE04, BTYPE00, BTEX_BU1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 3250:
		SetEnemy(TYPE_N_BU, POP04, MOVE04, BTYPE00, BTEX_BU1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 3300:
		break;
	case 3350:
		break;
	case 3400:
		break;
	case 3450:
		break;
	case 3500:
		break;
	case 3550:
		SetEnemy(TYPE_S_WH, POP04, MOVE07, BTYPE05, BTEX_BU1, 5 * SCREEN_SCALING, 30, 10, 11, BSPD_NO, NULL);
		SetEnemy(TYPE_N_RD, POP07, MOVE01, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 20, 6, 1, BSPD_NO, NULL);
		break;
	case 3600:
		SetEnemy(TYPE_N_RD, POP07, MOVE01, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 20, 6, 1, BSPD_NO, NULL);
		break;
	case 3650:
		SetEnemy(TYPE_N_RD, POP07, MOVE01, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 20, 6, 1, BSPD_NO, NULL);
		break;
	case 3700:
		break;
	case 3750:
		SetEnemy(TYPE_N_RD, POP07, MOVE04, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 3800:
		SetEnemy(TYPE_N_RD, POP07, MOVE04, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		SetEnemy(TYPE_S_WH, POP04, MOVE07, BTYPE05, BTEX_LB1, 5 * SCREEN_SCALING, 30, 10, 11, BSPD_NO, NULL);
		break;
	case 3850:
		SetEnemy(TYPE_N_RD, POP07, MOVE04, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 3900:
		SetEnemy(TYPE_S_WH, POP02, MOVE07, BTYPE05, BTEX_LB1, 5 * SCREEN_SCALING, 30, 10, 11, BSPD_NO, NULL);
		break;
	case 3950:
		break;
	case 4000:
		SetEnemy(TYPE_S_WH, POP06, MOVE07, BTYPE05, BTEX_LB1, 5 * SCREEN_SCALING, 30, 10, 11, BSPD_NO, NULL);
		break;
	case 4050:
		break;
	case 4100:
		break;
	case 4150:
		SetEnemy(TYPE_N_GR, POP01, MOVE02, BTYPE00, BTEX_GR1, 7 * SCREEN_SCALING, 20, 6, 1, BSPD_NO, NULL);
		break;
	case 4200:
		SetEnemy(TYPE_N_GR, POP01, MOVE02, BTYPE00, BTEX_GR1, 7 * SCREEN_SCALING, 20, 6, 1, BSPD_NO, NULL);
		break;
	case 4250:
		SetEnemy(TYPE_N_GR, POP01, MOVE02, BTYPE00, BTEX_GR1, 7 * SCREEN_SCALING, 20, 6, 1, BSPD_NO, NULL);
		break;
	case 4300:
		break;
	case 4350:
		SetEnemy(TYPE_N_LB, POP07, MOVE02, BTYPE00, BTEX_LB1, 7 * SCREEN_SCALING, 20, 6, 1, BSPD_NO, NULL);
		break;
	case 4400:
		SetEnemy(TYPE_N_LB, POP07, MOVE02, BTYPE00, BTEX_LB1, 7 * SCREEN_SCALING, 20, 6, 1, BSPD_NO, NULL);
		break;
	case 4450:
		SetEnemy(TYPE_N_LB, POP07, MOVE02, BTYPE00, BTEX_LB1, 7 * SCREEN_SCALING, 20, 6, 1, BSPD_NO, NULL);
		break;
	case 4500:
		break;
	case 4550:
		SetEnemy(TYPE_N_YE, POP02, MOVE02, BTYPE00, BTEX_YE1, 7 * SCREEN_SCALING, 20, 6, 1, BSPD_NO, NULL);
		break;
	case 4600:
		SetEnemy(TYPE_N_YE, POP02, MOVE02, BTYPE00, BTEX_YE1, 7 * SCREEN_SCALING, 20, 6, 1, BSPD_NO, NULL);
		break;
	case 4650:
		SetEnemy(TYPE_N_YE, POP02, MOVE02, BTYPE00, BTEX_YE1, 7 * SCREEN_SCALING, 20, 6, 1, BSPD_NO, NULL);
		break;
	case 4700:
		break;
	case 4750:
		break;
	case 4800:
		break;
	case 4850:
		break;
	case 4900:
		break;
	case 4950:
		break;
	case 5000:
		SetBossEnemy(TYPE_B_WH, POP04, MOVE09, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 20, 4, 3, BSPD_NO, NULL);
		break;
	}
}

//=============================================================================
// ハード															ハード
//=============================================================================
void GameLevelHard(void)
{
	int *count = GetCount();

	switch (*count)
	{

	case 200:
		SetEnemy(TYPE_N_RD, POP02, MOVE04, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 250:
		SetEnemy(TYPE_N_RD, POP02, MOVE04, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 300:
		SetEnemy(TYPE_N_RD, POP02, MOVE04, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 350:
		break;
	case 400:
		SetEnemy(TYPE_N_BU, POP04, MOVE04, BTYPE00, BTEX_BU1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 450:
		SetEnemy(TYPE_N_BU, POP04, MOVE04, BTYPE00, BTEX_BU1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 500:
		SetEnemy(TYPE_N_BU, POP04, MOVE04, BTYPE00, BTEX_BU1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 550:
		break;
	case 600:
		SetEnemy(TYPE_N_PI, POP03, MOVE04, BTYPE00, BTEX_PI1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 650:
		SetEnemy(TYPE_N_PI, POP03, MOVE04, BTYPE00, BTEX_PI1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 700:
		SetEnemy(TYPE_N_PI, POP03, MOVE04, BTYPE00, BTEX_PI1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 750:
		break;
	case 800:
		SetEnemy(TYPE_N_GR, POP07, MOVE04, BTYPE00, BTEX_GR1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 850:
		SetEnemy(TYPE_N_GR, POP07, MOVE04, BTYPE00, BTEX_GR1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 900:
		SetEnemy(TYPE_N_GR, POP07, MOVE04, BTYPE00, BTEX_GR1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		SetEnemy(TYPE_S_WH, POP04, MOVE07, BTYPE05, BTEX_LB1, 5 * SCREEN_SCALING, 30, 6, 15, BSPD_NO, NULL);
		break;
	case 950:
		break;
	case 1000:
		break;
	case 1050:
		break;
	case 1100:
		SetEnemy(TYPE_S_WH, POP02, MOVE07, BTYPE05, BTEX_LB1, 5 * SCREEN_SCALING, 30, 6, 15, BSPD_NO, NULL);
		break;
	case 1150:
		break;
	case 1200:
		break;
	case 1250:
		break;
	case 1300:
		SetEnemy(TYPE_S_WH, POP06, MOVE07, BTYPE05, BTEX_LB1, 5 * SCREEN_SCALING, 30, 6, 15, BSPD_NO, NULL);
		break;
	case 1350:
		SetEnemy(TYPE_N_GR, POP01, MOVE00, BTYPE00, BTEX_GR1, 7 * SCREEN_SCALING, 20, 4, 3, BSPD_NO, NULL);
		break;
	case 1400:
		SetEnemy(TYPE_N_GR, POP01, MOVE00, BTYPE00, BTEX_GR1, 7 * SCREEN_SCALING, 20, 4, 3, BSPD_NO, NULL);
		break;
	case 1450:
		SetEnemy(TYPE_N_GR, POP01, MOVE00, BTYPE00, BTEX_GR1, 7 * SCREEN_SCALING, 20, 4, 3, BSPD_NO, NULL);
		break;
	case 1500:
		break;
	case 1550:
		SetEnemy(TYPE_S_WH, POP04, MOVE07, BTYPE05, BTEX_BU1, 5 * SCREEN_SCALING, 30, 6, 21, BSPD_NO, NULL);
		break;
	case 1600:
		break;
	case 1650:
		SetEnemy(TYPE_N_BU, POP07, MOVE01, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 20, 4, 3, BSPD_NO, NULL);
		break;
	case 1700:
		SetEnemy(TYPE_N_RD, POP07, MOVE01, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 20, 4, 3, BSPD_NO, NULL);
		break;
	case 1750:
		SetEnemy(TYPE_N_RD, POP07, MOVE01, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 20, 4, 3, BSPD_NO, NULL);
		break;
	case 1800:
		break;
	case 1850:
		break;
	case 1900:
		SetEnemy(TYPE_S_WH, POP04, MOVE07, BTYPE06, BTEX_LB1, 5 * SCREEN_SCALING, 60, 5, 11, BSPD_NO, NULL);
		break;
	case 1950:
		break;
	case 2000:
		SetEnemy(TYPE_S_WH, POP06, MOVE07, BTYPE06, BTEX_LB1, 5 * SCREEN_SCALING, 60, 5, 11, BSPD_NO, NULL);
		break;
	case 2050:
		break;
	case 2100:
		SetEnemy(TYPE_S_WH, POP02, MOVE07, BTYPE06, BTEX_LB1, 5 * SCREEN_SCALING, 60, 5, 11, BSPD_NO, NULL);
		break;
	case 2150:
		break;
	case 2200:
		break;
	case 2250:
		SetEnemy(TYPE_N_GR, POP01, MOVE02, BTYPE00, BTEX_GR1, 7 * SCREEN_SCALING, 20, 4, 3, BSPD_NO, NULL);
		break;
	case 2300:
		SetEnemy(TYPE_N_GR, POP01, MOVE02, BTYPE00, BTEX_GR1, 7 * SCREEN_SCALING, 20, 4, 3, BSPD_NO, NULL);
		break;
	case 2350:
		SetEnemy(TYPE_N_GR, POP01, MOVE02, BTYPE00, BTEX_GR1, 7 * SCREEN_SCALING, 20, 4, 3, BSPD_NO, NULL);
		SetEnemy(TYPE_N_LB, POP07, MOVE02, BTYPE00, BTEX_LB1, 7 * SCREEN_SCALING, 20, 4, 3, BSPD_NO, NULL);
		break;
	case 2400:
		SetEnemy(TYPE_N_LB, POP07, MOVE02, BTYPE00, BTEX_LB1, 7 * SCREEN_SCALING, 20, 4, 3, BSPD_NO, NULL);
		break;
	case 2450:
		SetEnemy(TYPE_N_LB, POP07, MOVE02, BTYPE00, BTEX_LB1, 7 * SCREEN_SCALING, 20, 4, 3, BSPD_NO, NULL);
		break;
	case 2500:
		break;
	case 2550:
		break;
	case 2600:
		break;
	case 2650:
		SetEnemy(TYPE_N_YE, POP02, MOVE02, BTYPE00, BTEX_YE1, 7 * SCREEN_SCALING, 20, 4, 5, BSPD_NO, NULL);
		break;
	case 2700:
		SetEnemy(TYPE_N_YE, POP02, MOVE02, BTYPE00, BTEX_YE1, 7 * SCREEN_SCALING, 20, 4, 5, BSPD_NO, NULL);
		break;
	case 2750:
		SetEnemy(TYPE_N_YE, POP02, MOVE02, BTYPE00, BTEX_YE1, 7 * SCREEN_SCALING, 20, 4, 5, BSPD_NO, NULL);
		break;
	case 2800:
		break;
	case 2850:
		break;
	case 2900:
		SetEnemy(TYPE_S_PI, POP07, MOVE08, BTYPE01, BTEX_PI3, 5 * SCREEN_SCALING, 60, NULL, 20, BSPD_NO, NULL);
		break;
	case 2950:
		SetEnemy(TYPE_N_RD, POP02, MOVE04, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 3000:
		SetEnemy(TYPE_N_RD, POP02, MOVE04, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		SetEnemy(TYPE_S_PI, POP01, MOVE08, BTYPE01, BTEX_PI3, 5 * SCREEN_SCALING, 60, NULL, 20, BSPD_NO, NULL);
		break;
	case 3050:
		SetEnemy(TYPE_N_RD, POP02, MOVE04, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 3100:
		SetEnemy(TYPE_S_PI, POP04, MOVE08, BTYPE01, BTEX_PI3, 5 * SCREEN_SCALING, 60, NULL, 20, BSPD_NO, NULL);
		break;
	case 3150:
		SetEnemy(TYPE_N_BU, POP04, MOVE04, BTYPE00, BTEX_BU1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 3200:
		SetEnemy(TYPE_N_BU, POP04, MOVE04, BTYPE00, BTEX_BU1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 3250:
		SetEnemy(TYPE_N_BU, POP04, MOVE04, BTYPE00, BTEX_BU1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 3300:
		break;
	case 3350:
		break;
	case 3400:
		break;
	case 3450:
		break;
	case 3500:
		break;
	case 3550:
		SetEnemy(TYPE_S_WH, POP04, MOVE07, BTYPE05, BTEX_BU1, 5 * SCREEN_SCALING, 30, 6, 21, BSPD_NO, NULL);
		SetEnemy(TYPE_N_RD, POP07, MOVE01, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 20, 4, 3, BSPD_NO, NULL);
		break;
	case 3600:
		SetEnemy(TYPE_N_RD, POP07, MOVE01, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 20, 4, 5, BSPD_NO, NULL);
		break;
	case 3650:
		SetEnemy(TYPE_N_RD, POP07, MOVE01, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 20, 4, 5, BSPD_NO, NULL);
		break;
	case 3700:
		break;
	case 3750:
		SetEnemy(TYPE_N_RD, POP07, MOVE04, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 3800:
		SetEnemy(TYPE_N_RD, POP07, MOVE04, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		SetEnemy(TYPE_S_WH, POP04, MOVE07, BTYPE05, BTEX_LB1, 5 * SCREEN_SCALING, 30, 6, 21, BSPD_NO, NULL);
		break;
	case 3850:
		SetEnemy(TYPE_N_RD, POP07, MOVE04, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 1, 1, 1, BSPD_NO, NULL);
		break;
	case 3900:
		SetEnemy(TYPE_S_WH, POP02, MOVE07, BTYPE05, BTEX_LB1, 5 * SCREEN_SCALING, 30, 6, 21, BSPD_NO, NULL);
		break;
	case 3950:
		break;
	case 4000:
		SetEnemy(TYPE_S_WH, POP06, MOVE07, BTYPE05, BTEX_LB1, 5 * SCREEN_SCALING, 30, 6, 21, BSPD_NO, NULL);
		break;
	case 4050:
		break;
	case 4100:
		break;
	case 4150:
		SetEnemy(TYPE_N_GR, POP01, MOVE02, BTYPE00, BTEX_GR1, 7 * SCREEN_SCALING, 20, 4, 5, BSPD_NO, NULL);
		break;
	case 4200:
		SetEnemy(TYPE_N_GR, POP01, MOVE02, BTYPE00, BTEX_GR1, 7 * SCREEN_SCALING, 20, 4, 5, BSPD_NO, NULL);
		break;
	case 4250:
		SetEnemy(TYPE_N_GR, POP01, MOVE02, BTYPE00, BTEX_GR1, 7 * SCREEN_SCALING, 20, 4, 5, BSPD_NO, NULL);
		break;
	case 4300:
		break;
	case 4350:
		SetEnemy(TYPE_N_LB, POP07, MOVE02, BTYPE00, BTEX_LB1, 7 * SCREEN_SCALING, 20, 4, 5, BSPD_NO, NULL);
		break;
	case 4400:
		SetEnemy(TYPE_N_LB, POP07, MOVE02, BTYPE00, BTEX_LB1, 7 * SCREEN_SCALING, 20, 4, 5, BSPD_NO, NULL);
		break;
	case 4450:
		SetEnemy(TYPE_N_LB, POP07, MOVE02, BTYPE00, BTEX_LB1, 7 * SCREEN_SCALING, 20, 4, 5, BSPD_NO, NULL);
		break;
	case 4500:
		break;
	case 4550:
		SetEnemy(TYPE_N_YE, POP02, MOVE02, BTYPE00, BTEX_YE1, 7 * SCREEN_SCALING, 20, 4, 5, BSPD_NO, NULL);
		break;
	case 4600:
		SetEnemy(TYPE_N_YE, POP02, MOVE02, BTYPE00, BTEX_YE1, 7 * SCREEN_SCALING, 20, 4, 5, BSPD_NO, NULL);
		break;
	case 4650:
		SetEnemy(TYPE_N_YE, POP02, MOVE02, BTYPE00, BTEX_YE1, 7 * SCREEN_SCALING, 20, 4, 5, BSPD_NO, NULL);
		break;
	case 4700:
		break;
	case 4750:
		break;
	case 4800:
		break;
	case 4850:
		break;
	case 4900:
		break;
	case 4950:
		break;
	case 5000:
		SetBossEnemy(TYPE_B_WH, POP04, MOVE09, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 20, 4, 3, BSPD_NO, NULL);
		break;
	}
}

//=============================================================================
// イージー（ボスのみ）
//=============================================================================
void GameLevelBossEasy(void)
{
	int *count = GetCount();

	// ボス登場
	if (*count == 200)
	{
		SetBossEnemy(TYPE_B_WH, POP04, MOVE09, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 20, 4, 3, BSPD_NO, NULL);
	}
}

//=============================================================================
// ノーマル（ボスのみ）
//=============================================================================
void GameLevelBossNormal(void)
{
	int *count = GetCount();

	// ボス登場
	if (*count == 200)
	{
		SetBossEnemy(TYPE_B_WH, POP04, MOVE09, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 20, 4, 3, BSPD_NO, NULL);
	}
}

//=============================================================================
// ハード（ボスのみ）
//=============================================================================
void GameLevelBossHard(void)
{
	int *count = GetCount();

	// ボス登場
	if (*count == 200)
	{
		SetBossEnemy(TYPE_B_WH, POP04, MOVE09, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 20, 4, 3, BSPD_NO, NULL);
	}
}

//=============================================================================
// アルティメット（ボスのみ）
//=============================================================================
void GameLevelBossUltimate(void)
{
	int *count = GetCount();

	// ボス登場
	if (*count == 200)
	{
		SetBossEnemy(TYPE_B_WH, POP04, MOVE09, BTYPE00, BTEX_RD1, 7 * SCREEN_SCALING, 20, 4, 3, BSPD_NO, NULL);
	}
}

//=============================================================================
// ボススペック設定（イージー）
//=============================================================================
void SetGameLevelBossSpec(int nEnemy)
{
	switch (g_nGameLevel)
	{
	case EASY:
		SetGameLevelBossSpecEasy(nEnemy);
		break;
	case NORMAL:
		SetGameLevelBossSpecNormal(nEnemy);
		break;
	case HARD:
		SetGameLevelBossSpecHard(nEnemy);
		break;
	case BOSS_EASY:
		SetGameLevelBossSpecEasy(nEnemy);
		break;
	case BOSS_NORMAL:
		SetGameLevelBossSpecNormal(nEnemy);
		break;
	case BOSS_HARD:
		SetGameLevelBossSpecHard(nEnemy);
		break;
	case BOSS_ULTIMATE:
		SetGameLevelBossSpecUltimate(nEnemy);
		break;
	}
}

//=============================================================================
// ボススペック設定（イージー）
//=============================================================================
void SetGameLevelBossSpecEasy(int nEnemy)
{
	ENEMY *enemy = GetEnemy(nEnemy);

	enemy->nBulletTexture[BTYPE00] = BTEX_OR2;
	enemy->nBulletSpeed[BTYPE00] = 7 * SCREEN_SCALING;
	enemy->nBulletSetTime[BTYPE00] = 20;
	enemy->nBulletAction[BTYPE00] = 6;
	enemy->nBulletSplit[BTYPE00] = 5;
	enemy->nBulletSpeedChange[BTYPE00] = BSPD_NO;
	enemy->nBulletOption[BTYPE00] = 0;

	enemy->nBulletTexture[BTYPE01] = BTEX_RD3;
	enemy->nBulletSpeed[BTYPE01] = 5 * SCREEN_SCALING;
	enemy->nBulletSetTime[BTYPE01] = 100;
	enemy->nBulletAction[BTYPE01] = 1;
	enemy->nBulletSplit[BTYPE01] = 20;
	enemy->nBulletSpeedChange[BTYPE01] = BSPD_NO;
	enemy->nBulletOption[BTYPE01] = 0;

	enemy->nBulletTexture[BTYPE02] = BTEX_PI3;
	enemy->nBulletSpeed[BTYPE02] = 5 * SCREEN_SCALING;
	enemy->nBulletSetTime[BTYPE02] = 100;
	enemy->nBulletAction[BTYPE02] = 1;
	enemy->nBulletSplit[BTYPE02] = 20;
	enemy->nBulletSpeedChange[BTYPE02] = BSPD_NO;
	enemy->nBulletOption[BTYPE02] = 0;

	enemy->nBulletTexture[BTYPE03] = BTEX_VO3;
	enemy->nBulletSpeed[BTYPE03] = 5 * SCREEN_SCALING;
	enemy->nBulletSetTime[BTYPE03] = 100;
	enemy->nBulletAction[BTYPE03] = 1;
	enemy->nBulletSplit[BTYPE03] = 20;
	enemy->nBulletSpeedChange[BTYPE03] = BSPD_NO;
	enemy->nBulletOption[BTYPE03] = 0;

	enemy->nBulletTexture[BTYPE04] = BTEX_PI3;
	enemy->nBulletSpeed[BTYPE04] = 5 * SCREEN_SCALING;
	enemy->nBulletSetTime[BTYPE04] = 100;
	enemy->nBulletAction[BTYPE04] = 1;
	enemy->nBulletSplit[BTYPE04] = 20;
	enemy->nBulletSpeedChange[BTYPE04] = BSPD_NO;
	enemy->nBulletOption[BTYPE04] = 0;

	enemy->nBulletTexture[BTYPE05] = BTEX_GR2;
	enemy->nBulletSpeed[BTYPE05] = 7 * SCREEN_SCALING;
	enemy->nBulletSetTime[BTYPE05] = 20;
	enemy->nBulletAction[BTYPE05] = 6;
	enemy->nBulletSplit[BTYPE05] = 10;
	enemy->nBulletSpeedChange[BTYPE05] = BSPD_NO;
	enemy->nBulletOption[BTYPE05] = 0;

	enemy->nBulletTexture[BTYPE06] = BTEX_RD2;
	enemy->nBulletSpeed[BTYPE06] = 5 * SCREEN_SCALING;
	enemy->nBulletSetTime[BTYPE06] = 20;
	enemy->nBulletAction[BTYPE06] = 4;
	enemy->nBulletSplit[BTYPE06] = 5;
	enemy->nBulletSpeedChange[BTYPE06] = BSPD_NO;
	enemy->nBulletOption[BTYPE06] = 0;

	enemy->nBulletTexture[BTYPE07] = BTEX_BU2;
	enemy->nBulletSpeed[BTYPE07] = 5 * SCREEN_SCALING;
	enemy->nBulletSetTime[BTYPE07] = 20;
	enemy->nBulletAction[BTYPE07] = 4;
	enemy->nBulletSplit[BTYPE07] = 5;
	enemy->nBulletSpeedChange[BTYPE07] = BSPD_NO;
	enemy->nBulletOption[BTYPE07] = 0;
}

//=============================================================================
// ボススペック設定（ノーマル）
//=============================================================================
void SetGameLevelBossSpecNormal(int nEnemy)
{
	ENEMY *enemy = GetEnemy(nEnemy);

	enemy->nBulletTexture[BTYPE00] = BTEX_OR2;
	enemy->nBulletSpeed[BTYPE00] = 8 * SCREEN_SCALING;
	enemy->nBulletSetTime[BTYPE00] = 20;
	enemy->nBulletAction[BTYPE00] = 4;
	enemy->nBulletSplit[BTYPE00] = 5;
	enemy->nBulletSpeedChange[BTYPE00] = BSPD_NO;
	enemy->nBulletOption[BTYPE00] = 0;

	enemy->nBulletTexture[BTYPE01] = BTEX_RD3;
	enemy->nBulletSpeed[BTYPE01] = 5 * SCREEN_SCALING;
	enemy->nBulletSetTime[BTYPE01] = 200;
	enemy->nBulletAction[BTYPE01] = 1;
	enemy->nBulletSplit[BTYPE01] = 30;
	enemy->nBulletSpeedChange[BTYPE01] = BSPD_NO;
	enemy->nBulletOption[BTYPE01] = 0;

	enemy->nBulletTexture[BTYPE02] = BTEX_PI3;
	enemy->nBulletSpeed[BTYPE02] = 5 * SCREEN_SCALING;
	enemy->nBulletSetTime[BTYPE02] = 200;
	enemy->nBulletAction[BTYPE02] = 1;
	enemy->nBulletSplit[BTYPE02] = 30;
	enemy->nBulletSpeedChange[BTYPE02] = BSPD_NO;
	enemy->nBulletOption[BTYPE02] = 0;

	enemy->nBulletTexture[BTYPE03] = BTEX_VO3;
	enemy->nBulletSpeed[BTYPE03] = 5 * SCREEN_SCALING;
	enemy->nBulletSetTime[BTYPE03] = 200;
	enemy->nBulletAction[BTYPE03] = 1;
	enemy->nBulletSplit[BTYPE03] = 30;
	enemy->nBulletSpeedChange[BTYPE03] = BSPD_NO;
	enemy->nBulletOption[BTYPE03] = 0;

	enemy->nBulletTexture[BTYPE04] = BTEX_PI3;
	enemy->nBulletSpeed[BTYPE04] = 5 * SCREEN_SCALING;
	enemy->nBulletSetTime[BTYPE04] = 200;
	enemy->nBulletAction[BTYPE04] = 1;
	enemy->nBulletSplit[BTYPE04] = 30;
	enemy->nBulletSpeedChange[BTYPE04] = BSPD_NO;
	enemy->nBulletOption[BTYPE04] = 0;

	enemy->nBulletTexture[BTYPE05] = BTEX_GR2;
	enemy->nBulletSpeed[BTYPE05] = 7 * SCREEN_SCALING;
	enemy->nBulletSetTime[BTYPE05] = 20;
	enemy->nBulletAction[BTYPE05] = 4;
	enemy->nBulletSplit[BTYPE05] = 16;
	enemy->nBulletSpeedChange[BTYPE05] = BSPD_NO;
	enemy->nBulletOption[BTYPE05] = 0;

	enemy->nBulletTexture[BTYPE06] = BTEX_RD2;
	enemy->nBulletSpeed[BTYPE06] = 5 * SCREEN_SCALING;
	enemy->nBulletSetTime[BTYPE06] = 30;
	enemy->nBulletAction[BTYPE06] = 3;
	enemy->nBulletSplit[BTYPE06] = 11;
	enemy->nBulletSpeedChange[BTYPE06] = BSPD_NO;
	enemy->nBulletOption[BTYPE06] = 0;

	enemy->nBulletTexture[BTYPE07] = BTEX_BU2;
	enemy->nBulletSpeed[BTYPE07] = 5 * SCREEN_SCALING;
	enemy->nBulletSetTime[BTYPE07] = 30;
	enemy->nBulletAction[BTYPE07] = 3;
	enemy->nBulletSplit[BTYPE07] = 11;
	enemy->nBulletSpeedChange[BTYPE07] = BSPD_NO;
	enemy->nBulletOption[BTYPE07] = 0;
}

//=============================================================================
// ボススペック設定（ハード）
//=============================================================================
void SetGameLevelBossSpecHard(int nEnemy)
{
	ENEMY *enemy = GetEnemy(nEnemy);

	enemy->nBulletTexture[BTYPE00] = BTEX_OR2;
	enemy->nBulletSpeed[BTYPE00] = 8 * SCREEN_SCALING;
	enemy->nBulletSetTime[BTYPE00] = 20;
	enemy->nBulletAction[BTYPE00] = 4;
	enemy->nBulletSplit[BTYPE00] = 5;
	enemy->nBulletSpeedChange[BTYPE00] = BSPD_NO;
	enemy->nBulletOption[BTYPE00] = 0;

	enemy->nBulletTexture[BTYPE01] = BTEX_RD3;
	enemy->nBulletSpeed[BTYPE01] = 5 * SCREEN_SCALING;
	enemy->nBulletSetTime[BTYPE01] = 200;
	enemy->nBulletAction[BTYPE01] = 1;
	enemy->nBulletSplit[BTYPE01] = 30;
	enemy->nBulletSpeedChange[BTYPE01] = BSPD_NO;
	enemy->nBulletOption[BTYPE01] = 0;

	enemy->nBulletTexture[BTYPE02] = BTEX_PI3;
	enemy->nBulletSpeed[BTYPE02] = 5 * SCREEN_SCALING;
	enemy->nBulletSetTime[BTYPE02] = 200;
	enemy->nBulletAction[BTYPE02] = 1;
	enemy->nBulletSplit[BTYPE02] = 30;
	enemy->nBulletSpeedChange[BTYPE02] = BSPD_NO;
	enemy->nBulletOption[BTYPE02] = 0;

	enemy->nBulletTexture[BTYPE03] = BTEX_VO3;
	enemy->nBulletSpeed[BTYPE03] = 5 * SCREEN_SCALING;
	enemy->nBulletSetTime[BTYPE03] = 200;
	enemy->nBulletAction[BTYPE03] = 1;
	enemy->nBulletSplit[BTYPE03] = 30;
	enemy->nBulletSpeedChange[BTYPE03] = BSPD_NO;
	enemy->nBulletOption[BTYPE03] = 0;

	enemy->nBulletTexture[BTYPE04] = BTEX_PI3;
	enemy->nBulletSpeed[BTYPE04] = 5 * SCREEN_SCALING;
	enemy->nBulletSetTime[BTYPE04] = 200;
	enemy->nBulletAction[BTYPE04] = 1;
	enemy->nBulletSplit[BTYPE04] = 30;
	enemy->nBulletSpeedChange[BTYPE04] = BSPD_NO;
	enemy->nBulletOption[BTYPE04] = 0;

	enemy->nBulletTexture[BTYPE05] = BTEX_GR2;
	enemy->nBulletSpeed[BTYPE05] = 8 * SCREEN_SCALING;
	enemy->nBulletSetTime[BTYPE05] = 20;
	enemy->nBulletAction[BTYPE05] = 4;
	enemy->nBulletSplit[BTYPE05] = 20;
	enemy->nBulletSpeedChange[BTYPE05] = BSPD_NO;
	enemy->nBulletOption[BTYPE05] = 0;

	enemy->nBulletTexture[BTYPE06] = BTEX_RD2;
	enemy->nBulletSpeed[BTYPE06] = 5 * SCREEN_SCALING;
	enemy->nBulletSetTime[BTYPE06] = 36;
	enemy->nBulletAction[BTYPE06] = 3;
	enemy->nBulletSplit[BTYPE06] = 11;
	enemy->nBulletSpeedChange[BTYPE06] = BSPD_NO;
	enemy->nBulletOption[BTYPE06] = 0;

	enemy->nBulletTexture[BTYPE07] = BTEX_BU2;
	enemy->nBulletSpeed[BTYPE07] = 5 * SCREEN_SCALING;
	enemy->nBulletSetTime[BTYPE07] = 36;
	enemy->nBulletAction[BTYPE07] = 3;
	enemy->nBulletSplit[BTYPE07] = 11;
	enemy->nBulletSpeedChange[BTYPE07] = BSPD_NO;
	enemy->nBulletOption[BTYPE07] = 0;
}

//=============================================================================
// ボススペック設定（アルティメット）
//=============================================================================
void SetGameLevelBossSpecUltimate(int nEnemy)
{
	ENEMY *enemy = GetEnemy(nEnemy);

	enemy->nBulletTexture[BTYPE00] = BTEX_OR2;
	enemy->nBulletSpeed[BTYPE00] = 8 * SCREEN_SCALING;
	enemy->nBulletSetTime[BTYPE00] = 28;
	enemy->nBulletAction[BTYPE00] = 4;
	enemy->nBulletSplit[BTYPE00] = 7;
	enemy->nBulletSpeedChange[BTYPE00] = BSPD_NO;
	enemy->nBulletOption[BTYPE00] = 0;

	enemy->nBulletTexture[BTYPE01] = BTEX_RD3;
	enemy->nBulletSpeed[BTYPE01] = 5 * SCREEN_SCALING;
	enemy->nBulletSetTime[BTYPE01] = 200;
	enemy->nBulletAction[BTYPE01] = 1;
	enemy->nBulletSplit[BTYPE01] = 40;
	enemy->nBulletSpeedChange[BTYPE01] = BSPD_NO;
	enemy->nBulletOption[BTYPE01] = 0;

	enemy->nBulletTexture[BTYPE02] = BTEX_PI3;
	enemy->nBulletSpeed[BTYPE02] = 5 * SCREEN_SCALING;
	enemy->nBulletSetTime[BTYPE02] = 200;
	enemy->nBulletAction[BTYPE02] = 1;
	enemy->nBulletSplit[BTYPE02] = 40;
	enemy->nBulletSpeedChange[BTYPE02] = BSPD_NO;
	enemy->nBulletOption[BTYPE02] = 0;

	enemy->nBulletTexture[BTYPE03] = BTEX_VO3;
	enemy->nBulletSpeed[BTYPE03] = 5 * SCREEN_SCALING;
	enemy->nBulletSetTime[BTYPE03] = 200;
	enemy->nBulletAction[BTYPE03] = 1;
	enemy->nBulletSplit[BTYPE03] = 40;
	enemy->nBulletSpeedChange[BTYPE03] = BSPD_NO;
	enemy->nBulletOption[BTYPE03] = 0;

	enemy->nBulletTexture[BTYPE04] = BTEX_PI3;
	enemy->nBulletSpeed[BTYPE04] = 5 * SCREEN_SCALING;
	enemy->nBulletSetTime[BTYPE04] = 200;
	enemy->nBulletAction[BTYPE04] = 1;
	enemy->nBulletSplit[BTYPE04] = 40;
	enemy->nBulletSpeedChange[BTYPE04] = BSPD_NO;
	enemy->nBulletOption[BTYPE04] = 0;

	enemy->nBulletTexture[BTYPE05] = BTEX_GR2;
	enemy->nBulletSpeed[BTYPE05] = 8 * SCREEN_SCALING;
	enemy->nBulletSetTime[BTYPE05] = 28;
	enemy->nBulletAction[BTYPE05] = 4;
	enemy->nBulletSplit[BTYPE05] = 35;
	enemy->nBulletSpeedChange[BTYPE05] = BSPD_NO;
	enemy->nBulletOption[BTYPE05] = 0;

	enemy->nBulletTexture[BTYPE06] = BTEX_RD2;
	enemy->nBulletSpeed[BTYPE06] = 5 * SCREEN_SCALING;
	enemy->nBulletSetTime[BTYPE06] = 45;
	enemy->nBulletAction[BTYPE06] = 3;
	enemy->nBulletSplit[BTYPE06] = 11;
	enemy->nBulletSpeedChange[BTYPE06] = BSPD_NO;
	enemy->nBulletOption[BTYPE06] = 0;

	enemy->nBulletTexture[BTYPE07] = BTEX_BU2;
	enemy->nBulletSpeed[BTYPE07] = 5 * SCREEN_SCALING;
	enemy->nBulletSetTime[BTYPE07] = 45;
	enemy->nBulletAction[BTYPE07] = 3;
	enemy->nBulletSplit[BTYPE07] = 11;
	enemy->nBulletSpeedChange[BTYPE07] = BSPD_NO;
	enemy->nBulletOption[BTYPE07] = 0;
}

//=============================================================================
// ボスアクション
//=============================================================================
void SetGameBossAction(int nEnemy, int nMoveFlag)
{
	switch (g_nGameLevel)
	{
	case EASY:
		SetGameBossActionEasy(nEnemy, nMoveFlag);
		break;
	case NORMAL:
		SetGameBossActionNormal(nEnemy, nMoveFlag);
		break;
	case HARD:
		SetGameBossActionHard(nEnemy, nMoveFlag);
		break;
	case BOSS_EASY:
		SetGameBossActionEasy(nEnemy, nMoveFlag);
		break;
	case BOSS_NORMAL:
		SetGameBossActionNormal(nEnemy, nMoveFlag);
		break;
	case BOSS_HARD:
		SetGameBossActionHard(nEnemy, nMoveFlag);
		break;
	case BOSS_ULTIMATE:
		SetGameBossActionUltimate(nEnemy, nMoveFlag);
		break;
	}
}

//=============================================================================
// ボスアクション（イージー）
//=============================================================================
void SetGameBossActionEasy(int nEnemy, int nMoveFlag)
{
	ENEMY *enemy = GetEnemy(nEnemy);

	switch (nMoveFlag)
	{
	case 0:
		break;
	case 1:
		enemy->bBulletStandby[BTYPE00] = true;
		break;
	case 2:
		enemy->bBulletStandby[BTYPE05] = true;
		break;
	case 3:
		enemy->bBulletStandby[BTYPE01] = true;
		break;
	case 4:
		break;
	case 5:
		enemy->bBulletStandby[BTYPE00] = true;
		break;
	case 6:
		enemy->bBulletStandby[BTYPE00] = true;
		break;
	case 7:
		enemy->bBulletStandby[BTYPE02] = true;
		enemy->bBulletStandby[BTYPE01] = true;
		break;
	case 8:
		break;
	case 9:
		break;
	case 10:
		enemy->bBulletStandby[BTYPE00] = true;
		break;
	case 11:
		enemy->bBulletStandby[BTYPE05] = true;
		break;
	case 12:
		enemy->bBulletStandby[BTYPE05] = true;
		enemy->bBulletStandby[BTYPE00] = true;
		break;
	case 13:
		enemy->bBulletStandby[BTYPE03] = true;
		enemy->bBulletStandby[BTYPE04] = true;
		break;
	case 14:
		break;
	case 15:
		enemy->bBulletStandby[BTYPE05] = true;
		break;
	case 16:
		enemy->bBulletStandby[BTYPE05] = true;
		break;
	case 17:
		enemy->bBulletStandby[BTYPE07] = true;
		break;
	case 18:
		enemy->bBulletStandby[BTYPE06] = true;
		break;
	case 19:
		enemy->bBulletStandby[BTYPE07] = true;
		break;
	case 20:
		enemy->bBulletStandby[BTYPE06] = true;
		break;
	case 21:
		enemy->bBulletStandby[BTYPE07] = true;
		break;
	case 22:
		enemy->bBulletStandby[BTYPE03] = true;
		break;
	case 23:
		enemy->bBulletStandby[BTYPE00] = true;
		break;
	case 24:
		enemy->bBulletStandby[BTYPE04] = true;
		break;
	case 25:
		enemy->nMoveFlag = 1;
		break;
	}
}

//=============================================================================
// ボスアクション（ノーマル）
//=============================================================================
void SetGameBossActionNormal(int nEnemy, int nMoveFlag)
{
	ENEMY *enemy = GetEnemy(nEnemy);

	switch (nMoveFlag)
	{
	case 0:
		break;
	case 1:
		enemy->bBulletStandby[BTYPE00] = true;
		break;
	case 2:
		enemy->bBulletStandby[BTYPE05] = true;
		break;
	case 3:
		enemy->bBulletStandby[BTYPE01] = true;
		break;
	case 4:
		break;
	case 5:
		enemy->bBulletStandby[BTYPE00] = true;
		break;
	case 6:
		enemy->bBulletStandby[BTYPE00] = true;
		break;
	case 7:
		enemy->bBulletStandby[BTYPE02] = true;
		enemy->bBulletStandby[BTYPE01] = true;
		break;
	case 8:
		break;
	case 9:
		break;
	case 10:
		enemy->bBulletStandby[BTYPE00] = true;
		break;
	case 11:
		enemy->bBulletStandby[BTYPE05] = true;
		break;
	case 12:
		enemy->bBulletStandby[BTYPE05] = true;
		enemy->bBulletStandby[BTYPE00] = true;
		break;
	case 13:
		enemy->bBulletStandby[BTYPE03] = true;
		enemy->bBulletStandby[BTYPE04] = true;
		break;
	case 14:
		break;
	case 15:
		enemy->bBulletStandby[BTYPE05] = true;
		break;
	case 16:
		enemy->bBulletStandby[BTYPE05] = true;
		break;
	case 17:
		enemy->bBulletStandby[BTYPE07] = true;
		break;
	case 18:
		enemy->bBulletStandby[BTYPE06] = true;
		break;
	case 19:
		enemy->bBulletStandby[BTYPE07] = true;
		break;
	case 20:
		enemy->bBulletStandby[BTYPE06] = true;
		break;
	case 21:
		enemy->bBulletStandby[BTYPE07] = true;
		break;
	case 22:
		enemy->bBulletStandby[BTYPE03] = true;
		break;
	case 23:
		enemy->bBulletStandby[BTYPE00] = true;
		break;
	case 24:
		enemy->bBulletStandby[BTYPE04] = true;
		break;
	case 25:
		enemy->nMoveFlag = 1;
		break;
	}
}

//=============================================================================
// ボスアクション（ハード）
//=============================================================================
void SetGameBossActionHard(int nEnemy, int nMoveFlag)
{
	ENEMY *enemy = GetEnemy(nEnemy);

	switch (nMoveFlag)
	{
	case 0:
		break;
	case 1:
		enemy->bBulletStandby[BTYPE00] = true;
		break;
	case 2:
		enemy->bBulletStandby[BTYPE05] = true;
		break;
	case 3:
		enemy->bBulletStandby[BTYPE01] = true;
		break;
	case 4:
		enemy->bBulletStandby[BTYPE05] = true;
		break;
	case 5:
		enemy->bBulletStandby[BTYPE00] = true;
		break;
	case 6:
		enemy->bBulletStandby[BTYPE00] = true;
		break;
	case 7:
		enemy->bBulletStandby[BTYPE02] = true;
		enemy->bBulletStandby[BTYPE01] = true;
		break;
	case 8:
		enemy->bBulletStandby[BTYPE05] = true;
		break;
	case 9:
		enemy->bBulletStandby[BTYPE01] = true;
		break;
	case 10:
		enemy->bBulletStandby[BTYPE00] = true;
		break;
	case 11:
		enemy->bBulletStandby[BTYPE05] = true;
		break;
	case 12:
		enemy->bBulletStandby[BTYPE05] = true;
		enemy->bBulletStandby[BTYPE00] = true;
		break;
	case 13:
		enemy->bBulletStandby[BTYPE03] = true;
		enemy->bBulletStandby[BTYPE04] = true;
		break;
	case 14:
		enemy->bBulletStandby[BTYPE00] = true;
		break;
	case 15:
		enemy->bBulletStandby[BTYPE00] = true;
		enemy->bBulletStandby[BTYPE05] = true;
		break;
	case 16:
		enemy->bBulletStandby[BTYPE05] = true;
		break;
	case 17:
		enemy->bBulletStandby[BTYPE07] = true;
		break;
	case 18:
		enemy->bBulletStandby[BTYPE00] = true;
		enemy->bBulletStandby[BTYPE06] = true;
		break;
	case 19:
		enemy->bBulletStandby[BTYPE00] = true;
		enemy->bBulletStandby[BTYPE07] = true;
		break;
	case 20:
		enemy->bBulletStandby[BTYPE00] = true;
		enemy->bBulletStandby[BTYPE06] = true;
		break;
	case 21:
		enemy->bBulletStandby[BTYPE00] = true;
		enemy->bBulletStandby[BTYPE07] = true;
		break;
	case 22:
		enemy->bBulletStandby[BTYPE00] = true;
		enemy->bBulletStandby[BTYPE03] = true;
		break;
	case 23:
		enemy->bBulletStandby[BTYPE00] = true;
		break;
	case 24:
		enemy->bBulletStandby[BTYPE04] = true;
		enemy->bBulletStandby[BTYPE05] = true;
		break;
	case 25:
		enemy->nMoveFlag = 1;
		break;
	}
}

//=============================================================================
// ボスアクション（アルティメット）
//=============================================================================
void SetGameBossActionUltimate(int nEnemy, int nMoveFlag)
{
	ENEMY *enemy = GetEnemy(nEnemy);

	switch (nMoveFlag)
	{
	case 0:
		break;
	case 1:
		enemy->bBulletStandby[BTYPE00] = true;
		enemy->bBulletStandby[BTYPE02] = true;
		break;
	case 2:
		enemy->bBulletStandby[BTYPE00] = true;
		enemy->bBulletStandby[BTYPE05] = true;
		break;
	case 3:
		enemy->bBulletStandby[BTYPE00] = true;
		enemy->bBulletStandby[BTYPE01] = true;
		break;
	case 4:
		enemy->bBulletStandby[BTYPE00] = true;
		break;
	case 5:
		enemy->bBulletStandby[BTYPE00] = true;
		enemy->bBulletStandby[BTYPE05] = true;
		enemy->bBulletStandby[BTYPE02] = true;
		break;
	case 6:
		enemy->bBulletStandby[BTYPE00] = true;
		break;
	case 7:
		enemy->bBulletStandby[BTYPE00] = true;
		enemy->bBulletStandby[BTYPE01] = true;
		break;
	case 8:
		enemy->bBulletStandby[BTYPE05] = true;
		break;
	case 9:
		enemy->bBulletStandby[BTYPE05] = true;
		enemy->bBulletStandby[BTYPE04] = true;
		break;
	case 10:
		enemy->bBulletStandby[BTYPE00] = true;
		break;
	case 11:
		enemy->bBulletStandby[BTYPE05] = true;
		break;
	case 12:
		enemy->bBulletStandby[BTYPE00] = true;
		enemy->bBulletStandby[BTYPE05] = true;
		break;
	case 13:
		enemy->bBulletStandby[BTYPE00] = true;
		enemy->bBulletStandby[BTYPE03] = true;
		break;
	case 14:
		enemy->bBulletStandby[BTYPE00] = true;
		break;
	case 15:
		enemy->bBulletStandby[BTYPE05] = true;
		break;
	case 16:
		enemy->bBulletStandby[BTYPE05] = true;
		break;
	case 17:
		enemy->bBulletStandby[BTYPE07] = true;
		break;
	case 18:
		enemy->bBulletStandby[BTYPE06] = true;
		enemy->bBulletStandby[BTYPE00] = true;
		break;
	case 19:
		enemy->bBulletStandby[BTYPE07] = true;
		enemy->bBulletStandby[BTYPE00] = true;
		break;
	case 20:
		enemy->bBulletStandby[BTYPE06] = true;
		enemy->bBulletStandby[BTYPE00] = true;
		break;
	case 21:
		enemy->bBulletStandby[BTYPE07] = true;
		enemy->bBulletStandby[BTYPE00] = true;
		break;
	case 22:
		enemy->bBulletStandby[BTYPE03] = true;
		enemy->bBulletStandby[BTYPE00] = true;
		break;
	case 23:
		enemy->bBulletStandby[BTYPE00] = true;
		break;
	case 24:
		enemy->bBulletStandby[BTYPE04] = true;
		enemy->bBulletStandby[BTYPE00] = true;
		break;
	case 25:
		enemy->bBulletStandby[BTYPE05] = true;
		enemy->bBulletStandby[BTYPE00] = true;
		enemy->nMoveFlag = 1;
		break;
	}
}