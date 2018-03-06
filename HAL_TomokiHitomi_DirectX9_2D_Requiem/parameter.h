//=============================================================================
//
// パラメータ処理 [parameter.h]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#ifndef _PARAMETER_H_
#define _PARAMETER_H_

#include "main.h"

// マクロ定義
#define NUM_PARAMETER		(2)	// ポリゴン数

#define TEXTURE_GAME_PARAMETER00	_T("data/TEXTURE/parameter.png")	// hp用画像
#define TEXTURE_PARAMETER00_SIZE_X	(70 * SCREEN_SCALING) // テクスチャサイズ
#define TEXTURE_PARAMETER00_SIZE_Y	(9 * SCREEN_SCALING/2) // 同上

#define TEXTURE_CHANGE_PARAMETER_X		(1.0f)
#define TEXTURE_CHANGE_PARAMETER_Y		(1.0f)

#define TEXTURE_CHANGE_BOSS_PARAMETER_X	(15.0f)
#define TEXTURE_CHANGE_BOSS_PARAMETER_Y	(1.5f)

#define BOSS_PARAMETER_POS_X			(642 * SCREEN_SCALING)
#define BOSS_PARAMETER_POS_Y			(110 * SCREEN_SCALING)

#define TEXTURE_PATTERN_DIVIDE_X_PARAMETER	(3)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_PARAMETER	(1)	// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_PARAMETER			(TEXTURE_PATTERN_DIVIDE_X_PARAMETER*TEXTURE_PATTERN_DIVIDE_Y_PARAMETER)	// アニメーションパターン数
#define TIME_ANIMATION_PARAMETER				(4)	// アニメーションの切り替わるカウント

#define PARAMETER_MAX					(30)// パラメータの最大数
#define PARAMETER_SPEED					(8)	// パラメータの移動速度

#define PARAMETER_DRAW_HP				(25 * SCREEN_SCALING)	// HPゲージの表示位置
#define PARAMETER_DRAW_MP				(35 * SCREEN_SCALING)	// MPゲージの表示位置

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
}PARAMETER;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitParameter(int type);
void UninitParameter(void);
void UpdateParameter(void);
void DrawParameter(void);
void SetParameter(int nType, D3DXVECTOR3 vecTargetPos, int nTarget);
void InitStatusParameter(int nParameter);
PARAMETER *GetParameter(int no);


#endif
