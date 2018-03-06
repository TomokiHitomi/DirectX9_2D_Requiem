//=============================================================================
//BTYPE
// 入力処理 [game.h]
// Author :  GP11B243 24 人見友基
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************


enum
{	// ゲームステージ
	EASY,
	NORMAL,
	HARD,
	ONLY_BOSS,
	BOSS_EASY,
	BOSS_NORMAL,
	BOSS_HARD,
	BOSS_ULTIMATE
};

enum
{
	TYPE_N_RD,
	TYPE_N_PI,
	TYPE_N_YE,
	TYPE_N_GR,
	TYPE_N_LB,
	TYPE_N_BU,
	TYPE_N_WH,
	TYPE_S_WH,
	TYPE_S_PI,
	TYPE_B_WH
};

enum
{	// エネミーポップ座標
	POP00,
	POP01,
	POP02,
	POP03,
	POP04,
	POP05,
	POP06,
	POP07,
	POP08
};

enum
{	// エネミー移動
	MOVE00,
	MOVE01,
	MOVE02,
	MOVE03,
	MOVE04,
	MOVE05,
	MOVE06,
	MOVE07,
	MOVE08,
	MOVE09
};
enum
{	// エネミーバレットタイプ
	BTYPE00,
	BTYPE01,
	BTYPE02,
	BTYPE03,
	BTYPE04,
	BTYPE05,
	BTYPE06,
	BTYPE07,
	BTYPE08
};
enum
{	// エネミーバレットテクスチャ
	BTEX_RD1,
	BTEX_OR1,
	BTEX_YE1,
	BTEX_GR1,
	BTEX_LB1,
	BTEX_BU1,
	BTEX_VO1,
	BTEX_PI1,
	BTEX_WH1,
	BTEX_RD2,
	BTEX_OR2,
	BTEX_YE2,
	BTEX_GR2,
	BTEX_LB2,
	BTEX_BU2,
	BTEX_VO2,
	BTEX_PI2,
	BTEX_WH2,
	BTEX_RD3,
	BTEX_OR3,
	BTEX_YE3,
	BTEX_GR3,
	BTEX_LB3,
	BTEX_BU3,
	BTEX_VO3,
	BTEX_PI3,
	BTEX_WH3,
};
enum
{	// エネミーバレット速度変更
	BSPD_NO,
	BSPD_UP,
	BSPD_DOWN
};
/*******************************************************************************
* 構造体定義
*******************************************************************************/

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitGame(void);
void UpdateGame(void);
void SetGameLevel(int nLevel);
void SetGameLevelBossSpec(int nEnemy);
void SetGameBossAction(int nEnemy, int nMoveFlag);

#endif