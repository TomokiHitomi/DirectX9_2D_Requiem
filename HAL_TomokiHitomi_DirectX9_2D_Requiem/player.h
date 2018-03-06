//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"

// マクロ定義
#define NUM_PLAYER						(2)		// ポリゴン数
#define TEXTURE_GAME_PLAYER00		_T("data/TEXTURE/motion.png")	// プレイヤー00用画像
#define TEXTURE_PLAYER00_SIZE_X			(200 * SCREEN_SCALING / 2)	// テクスチャサイズ
#define TEXTURE_PLAYER00_SIZE_Y			(150 * SCREEN_SCALING / 2)	// 同上
#define TEXTURE_PATTERN_DIVIDE_X_PLAYER	(10)	// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_PLAYER	(6)		// アニメパターンのテクスチャ内分割数（Y)
#define TEXTURE_PATTERN_PLAYER			(3)		// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_PLAYER			(TEXTURE_PATTERN_DIVIDE_X_PLAYER*TEXTURE_PATTERN_DIVIDE_Y_PLAYER)	// アニメーションパターン数
#define TIME_ANIMATION_PLAYER			(7)		// アニメーションの切り替わるカウント

// プレイヤーの初期座標
#define PLAYER_POS_X			(200 * SCREEN_SCALING)		// 初期位置X
#define PLAYER_POS_Y			(670 * SCREEN_SCALING)		// 初期位置Y

// 当たり判定用サイズ
#define PLAYER_CUSTOM_SIZE_X			(10)
#define PLAYER_CUSTOM_SIZE_Y			(50)

#define PLAYER_TUTORIAL_MOVE_X			(450 * SCREEN_SCALING)	// チュートリアル時の移動制限

#define PLAYER_MAX						(1)		// プレイヤーの最大数
#define PLAYER_HPMAX					(20)	// プレイヤーの最大HP
#define PLAYER_MANAMAX					(1000)	// プレイヤーの最大MP
#define PLAYER_MANARECOVERY				(3)		// プレイヤーのMP回復速度
#define PLAYER_GROUND					(5)		// プレイヤーの最大数

#define PLAYER_SPEED					(8 * SCREEN_SCALING)		// プレイヤーの移動速度
#define PLAYER_MOVE_NORMAL				(1.0f)	// プレイヤーの通常移動倍率
#define PLAYER_MOVE_SLANT				(0.71f)	// プレイヤーの斜め移動倍率

#define PLAYER_SLOW						(3 * SCREEN_SCALING)		// プレイヤーの無重力時の速度
#define PLAYER_JUMP_POWER				(20 * SCREEN_SCALING)	// プレイヤーのジャンプ力
#define PLAYER_JUMP_MAX					(2)		// プレイヤーの連続ジャンプ回数
#define PLAYER_GRAVITI					(0.7 * SCREEN_SCALING)	// プレイヤーの重力
#define PLAYER_GRAVITI_ALERT			(250)	// 残りMPが設定値を下回るとアラート

#define PLAYER_ALPHA_MAX				(255)	// プレイヤーの最大アルファ値
#define PLAYER_INVISIBLE_MAX			(50)	// プレイヤー無敵時間
#define PLAYER_INVISIBLE_FREQUENCY		(5)		// プレイヤー無敵時の点滅速度

/*******************************************************************************
* 構造体定義
*******************************************************************************/

typedef struct
{
	LPDIRECT3DTEXTURE9		Texture;				// テクスチャ情報
	VERTEX_2D				vertexWk[NUM_VERTEX];	// 頂点情報格納ワーク
	D3DXVECTOR3				pos;					// 移動量
	D3DXVECTOR3				rot;					// 回転量
	D3DXVECTOR2				size;					// テクスチャサイズ(x,y)
	int						nCountAnim;				// アニメーションカウント
	int						nPatternAnim;			// アニメーションパターンナンバー
	int						nDirection;				// 向き
	int						nAlphaCount;			// アルファ値のカウント
	int						nInvisibleCount;		// 無敵カウント
	int						nJumpFlag;				// ジャンプフラグ

	float					fHitPoint;				// HP
	float					fManaPoint;				// MP
	float					fBaseAngle;				// 角度（θ）
	float					fRadius;				// 半径
	float					fGravity;				// 重力
	float					fAcceleration;			// ジャンプ加速度
	float					fMoveSlow;				// 移動減速
	float					fMove;					// 移動速度

	bool					bUse;					// プレイヤーフラグ
	bool					bGravityFlag;			// 重力フラグ
	bool					bParameterUse;			// パラメータフラグ
	bool					bAlphaFlag;				// 透明度フラグ
	bool					bInvisibleFlag;			// 無敵フラグ
}PLAYER;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPlayer(int type);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void SetPlayerVoice(int nVoice);
PLAYER *GetPlayer(int no);


#endif
