//=============================================================================
//
// ファンネル処理 [funnel.h]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#ifndef _FUNNEL_H_
#define _FUNNEL_H_

#include "main.h"
#include <time.h>

// マクロ定義
#define NUM_FUNNEL						(2)					// ポリゴン数

#define TEXTURE_GAME_FUNNEL	_T("data/TEXTURE/funnel.png")	// ファンネル用画像

#define TEXTURE_FUNNEL_SIZE_X			(100 * SCREEN_SCALING/2)				// 横テクスチャサイズ
#define TEXTURE_FUNNEL_SIZE_Y			(100 * SCREEN_SCALING/2)				// 縦テクスチャサイズ

#define TEXTURE_PATTERN_DIVIDE_X_FUNNEL	(5)			// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_FUNNEL	(6)			// アニメパターンのテクスチャ内分割数（Y)

// アニメーションパターン数
#define ANIM_PATTERN_NU_FUNNEL			(TEXTURE_PATTERN_DIVIDE_X_FUNNEL*TEXTURE_PATTERN_DIVIDE_Y_FUNNEL)
#define TIME_ANIMATION_FUNNEL			(4)					// アニメーションの切り替わるカウント

#define FUNNEL_MAX						(3)				// ファンネルの最大数
#define FUNNEL_TYPE_MAX					(2)				// ファンネルのタイプ最大数

#define FUNNEL_ALPHA_MAX				(255)			// ファンネルの最大α値
#define FUNNEL_ALPHA					(100)			// ファンネルの最小α値
#define FUNNEL_ALPHA_MIN				(FUNNEL_ALPHA_MAX - FUNNEL_ALPHA)			// ファンネルのα値

#define FUNNEL01_ROTATION				(0.05f)				// ファンネルの回転量
#define FUNNEL01_COOLDOWN				(5)					// ファンネル連射速度（数値が大きいと遅い）

// ファンネルの移動速度
#define FUNNEL00_SPEED_MAX				(20)	// ファンネル00の最大速度
#define FUNNEL01_SPEED_MAX				(5)	// ファンネル01の最大速度
#define FUNNEL02_SPEED_MAX				(50)	// ファンネル02の最大速度

#define FUNNEL02_SPEED_ACCELERATOR		(0.2)	// ファンネル02の加速度

// ファンネルの連射速度
#define FUNNEL00_RELOAD_SPEED			(10)	// ファンネル00
#define FUNNEL01_RELOAD_SPEED			(5)		// ファンネル01
#define FUNNEL02_RELOAD_SPEED			(5)		// ファンネル02

// ファンネルバレットの連射速度
#define FUNNEL_BULLET_RELOAD_SPEED		(4)

#define FUNNEL_DISTANCE_MAX				(80 * SCREEN_SCALING)	// ファンネルと設置対象の距離
#define FUNNEL_INJECTION_SPEED			(2.0f)	// ファンネルの射出速度
#define FUNNEL_ROTATIONAL_SPEED			(40)	// ファンネルの回転速度

/*******************************************************************************
* 構造体定義
*******************************************************************************/

typedef struct
{
	LPDIRECT3DTEXTURE9		Texture;				// テクスチャ情報
	VERTEX_2D				vertexWk[NUM_VERTEX];	// 頂点情報格納ワーク
	D3DXVECTOR3				pos;					// ファンネル01の座標
	D3DXVECTOR3				rot;					// ファンネル01の回転量
	D3DXVECTOR2				size;					// ファンネル01のテクスチャサイズ(x,y)
	D3DXVECTOR3				vecTa;					// 距離
	D3DXVECTOR2				move;					// 移動量
	D3DXVECTOR3				vecDestination;			// ファンネルの移動先

	int						nCountAnim;				// アニメーションカウント
	int						nPatternAnim;			// アニメーションパターンナンバー
	int						nFunnelType;			// ファンネルのタイプ
	int						nFunnelCount;			// ファンネルカウント
	int						nAngleType;				// ファンネルの角度タイプ
	int						nPatternHoming;			// ホーミングパターンナンバー
	int						nHomingFlag;			// ファンネルのホーミングフラグ
	int						nDirection;				// ファンネルの向き
	int						nTarget;				// ファンネルのターゲット
	int						nReloadBullet;			// ファンネルバレットのリロードカウント
	int						nAlpha;					// ファンネルのα値

	float					fFunnelSpeed;			// ファンネルの移動速度
	float					fAngle;					// ファンネルの角度
	float					fBaseAngle;				// 角度（θ）
	float					fRadius;				// 半径
	float					fDistance;				// プレイヤーとファンネルの距離

	bool					bUse;					// ファンネルの使用フラグ
	bool					bTextureUse;			// ファンネルのテクスチャフラグ
	bool					bReload;				// ファンネルバレットのリロードフラグ

}FUNNEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitFunnel(int type);
void UninitFunnel(void);
void UpdateFunnel(void);
void DrawFunnel(void);
FUNNEL *GetFunnel(int no);
void SetFunnel(D3DXVECTOR3 pos);
void ReleaseFunnel(void);
void InitStatusFunnel(int nFunnel);

#endif
