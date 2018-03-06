//=============================================================================
//
// タイトル処理 [level_boss.h]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#ifndef _LEVEL_BOSS_H_
#define _LEVEL_BOSS_H_

#include "main.h"

// マクロ定義
#define NUM_LEVEL_BOSS		(2)	// ポリゴン数

#define TEXTURE_GAME_LEVEL_BOSS00	_T("data/TEXTURE/level_boss.png")	// タイトル00用画像
#define TEXTURE_LEVEL_BOSS00_SIZE_X	(400 * SCREEN_SCALING/2) // テクスチャサイズ
#define TEXTURE_LEVEL_BOSS00_SIZE_Y	(80 * SCREEN_SCALING/2) // 同上
#define LEVEL_BOSS_POS_X			(SCREEN_CENTER_X)	// 初期座標X
#define LEVEL_BOSS_POS_Y			(380 * SCREEN_SCALING)				// 初期座標Y
#define LEVEL_BOSS_SPACING		(75 * SCREEN_SCALING)

#define TEXTURE_PATTERN_DIVIDE_X_LEVEL_BOSS	(2)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_LEVEL_BOSS	(4)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_LEVEL_BOSS			(TEXTURE_PATTERN_DIVIDE_X_LEVEL_BOSS*TEXTURE_PATTERN_DIVIDE_Y_LEVEL_BOSS)	// アニメーションパターン数
#define TIME_ANIMATION_LEVEL_BOSS				(1)	// アニメーションの切り替わるカウント

#define LEVEL_BOSS_MAX					(4)	// タイトルの最大数
#define LEVEL_BOSS_SELECT_PRESS			(40)	// メニュー自動送り開始タイム
#define LEVEL_BOSS_SELECT_SPEED			(7)		// メニュ－自動送り速度

/*******************************************************************************
* 構造体定義
*******************************************************************************/

typedef struct
{
	LPDIRECT3DTEXTURE9		Texture;				// テクスチャ情報
	VERTEX_2D				vertexWk[NUM_VERTEX];	// 頂点情報格納ワーク
	D3DXVECTOR3				pos;					// タイトルの移動量
	D3DXVECTOR3				rot;					// タイトルの回転量
	D3DXVECTOR2				size;					// タイトルのテクスチャサイズ(x,y)
	int						nCountAnim;				// アニメーションカウント
	int						nPatternAnim;			// アニメーションパターンナンバー
	float					fBaseAngle;				// 角度（θ）
	float					fRadius;					// 半径
	bool					bUse;					// true:使用  false:未使用
}LEVEL_BOSS;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitLevel_boss(int type);
void UninitLevel_boss(void);
void UpdateLevel_boss(void);
void DrawLevel_boss(void);
void SetLevel_boss(void);
void ReleaseLevel_boss(void);
LEVEL_BOSS *GetLevel_boss(int no);


#endif
