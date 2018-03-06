//=============================================================================
//
// パラメータ処理 [parameterbar.h]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#ifndef _PARAMETERBAR_H_
#define _PARAMETERBAR_H_

#include "main.h"

// マクロ定義
#define NUM_PARAMETERBAR		(2)	// ポリゴン数

#define TEXTURE_GAME_PARAMETERBAR00	_T("data/TEXTURE/parameterframe.png")	// hp用画像
#define TEXTURE_PARAMETERBAR00_SIZE_X	(70 * SCREEN_SCALING/2) // テクスチャサイズ
#define TEXTURE_PARAMETERBAR00_SIZE_Y	(9 * SCREEN_SCALING/2) // 同上

#define TEXTURE_CHANGE_PARAMETERBAR_X		(1.0f)
#define TEXTURE_CHANGE_PARAMETERBAR_Y		(1.0f)

#define TEXTURE_CHANGE_BOSS_PARAMETERBAR_X	(15.0f)
#define TEXTURE_CHANGE_BOSS_PARAMETERBAR_Y	(1.5f)

#define BOSS_PARAMETERBAR_POS_X			(642 * SCREEN_SCALING)
#define BOSS_PARAMETERBAR_POS_Y			(110 * SCREEN_SCALING)

#define TEXTURE_PATTERN_DIVIDE_X_PARAMETERBAR	(3)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_PARAMETERBAR	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_PARAMETERBAR			(TEXTURE_PATTERN_DIVIDE_X_PARAMETERBAR*TEXTURE_PATTERN_DIVIDE_Y_PARAMETERBAR)	// アニメーションパターン数
#define TIME_ANIMATION_PARAMETERBAR				(4)	// アニメーションの切り替わるカウント

#define PARAMETERBAR_MAX					(30)// パラメータの最大数
#define PARAMETERBAR_SPEED					(8)	// パラメータの移動速度

#define PARAMETERBAR_DRAW_HP				(25 * SCREEN_SCALING)	// HPゲージの表示位置
#define PARAMETERBAR_DRAW_MP				(35 * SCREEN_SCALING)	// MPゲージの表示位置

/*******************************************************************************
* 構造体定義
*******************************************************************************/

typedef struct
{
	LPDIRECT3DTEXTURE9		Texture;				// テクスチャ情報
	VERTEX_2D				vertexWk[NUM_VERTEX];	// 頂点情報格納ワーク
	D3DXVECTOR3				pos;					// パラメータの移動量
	D3DXVECTOR3				rot;					// パラメータの回転量
	D3DXVECTOR2				size;					// パラメータのテクスチャサイズ(x,y)
	D3DXVECTOR3				vecTargetPos;			// ターゲット座標
	D3DXVECTOR3				vecChangeSize;			// テクスチャサイズ変更(x,y)

	int						nCountAnim;				// アニメーションカウント
	int						nPatternAnim;			// アニメーションパターンナンバー
	float					nPointGauge;			// 現在のポイント
	int						nTarget;				// ターゲット
	int						nType;					// パラメータタイプ
	float					fBaseAngle;				// 角度（θ）
	float					fRadius;				// 半径
	bool					bUse;					// true:使用  false:未使用
}PARAMETERBAR;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitParameterbar(int type);
void UninitParameterbar(void);
void UpdateParameterbar(void);
void DrawParameterbar(void);
void SetParameterbar(int nType, D3DXVECTOR3 vecTargetPos, int nTarget);
void InitStatusParameterbar(int nParameterbar);
PARAMETERBAR *GetParameterbar(int no);


#endif
