//=============================================================================
//
// エネミー処理 [enemy.h]
// Author : GP11B243 24 人見友基
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"
#include "enemybullet.h"

// マクロ定義
#define NUM_ENEMY		(2)	// ポリゴン数

#define TEXTURE_GAME_ENEMY00	_T("data/TEXTURE/enemy.png")	// エネミー00用画像
#define TEXTURE_ENEMY00_SIZE_X			(80 * SCREEN_SCALING/2)	// テクスチャサイズ
#define TEXTURE_ENEMY00_SIZE_Y			(80 * SCREEN_SCALING/2)	// 同上
	
#define TEXTURE_CHANGE_ENEMY_X			(1.0f)	// テクスチャサイズ変更倍率
#define TEXTURE_CHANGE_ENEMY_Y			(1.0f)	// 同上
#define TEXTURE_CHANGE_BOSS_ENEMY_X		(1.5f)	// テクスチャサイズ変更倍率
#define TEXTURE_CHANGE_BOSS_ENEMY_Y		(1.5f)	// 同上

#define TEXTURE_PATTERN_DIVIDE_X_ENEMY	(3)		// アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y_ENEMY	(10)		// アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM_ENEMY			(TEXTURE_PATTERN_DIVIDE_X_ENEMY*TEXTURE_PATTERN_DIVIDE_Y_ENEMY)	// アニメーションパターン数
#define TIME_ANIMATION_ENEMY			(15)		// アニメーションの切り替わるカウント

#define ENEMY_POP_TYPE_MAX				(9)		// エネミータイプの最大数

#define ENEMY_POP_POS_X					(SCREEN_HEIGHT/ENEMY_POP_TYPE_MAX)	// エネミータイプの最大数

// エネミーステータス
#define ENEMY_MAX						(100)	// 最大数

#define ENEMY_COOLDOWN					(100)	// エネミー再使用クールダウン
#define ENEMY_MOVE_SPEED				(4 * SCREEN_SCALING)		// エネミーの移動スピード
#define ENEMY_ROTATION					(0.0f)	// エネミーバレットの回転量
#define ENEMY_ACTION					(100)	// アクション間隔

#define ENEMY_HPMAX						(70)	// 最大HP
#define STRONG_ENEMY_HPMAX				(120)	// 最大HP（強敵）
#define BOSS_ENEMY_HPMAX				(8000)	// 最大HP（ボス）


// ショットカウント
#define ENEMY_SHOT00					(20)
#define ENEMY_SHOT01					(60)
#define ENEMY_SHOT02					(60)
#define ENEMY_SHOT03					(60)
#define ENEMY_SHOT04					(60)
#define ENEMY_SHOT05					(20)
#define ENEMY_SHOT06					(60)

// ショット間隔
#define ENEMY_SHOT_ACTION00				(4)
#define ENEMY_SHOT_ACTION05				(4)
#define ENEMY_SHOT_ACTION06				(6)

// エネミーの出現タイプ
#define ENEMY_POP_TYPE00				(0)
#define ENEMY_POP_TYPE01				(1)
#define ENEMY_POP_TYPE02				(2)
#define ENEMY_POP_TYPE03				(3)
#define ENEMY_POP_TYPE04				(4)
#define ENEMY_POP_TYPE05				(5)

// エネミーの移動タイプ
#define ENEMY_MOVE_TYPE00				(0)
#define ENEMY_MOVE_TYPE01				(1)
#define ENEMY_MOVE_TYPE02				(2)
#define ENEMY_MOVE_TYPE03				(3)
#define ENEMY_MOVE_TYPE04				(4)
#define ENEMY_MOVE_TYPE05				(5)

// ファイル読み込み
#define		FILE_ENEMY_EASY		"data/CSV/enemy_easy.csv"
#define		FILE_ENEMY_NORMAL	"data/CSV/enemy_normal.csv"
#define		FILE_ENEMY_HARD		"data/CSV/enemy_hard.csv"
#define		FILE_DATA_MAX		(12)

enum
{
	ENEMY_NORMAL,
	ENEMY_STRONG,
	ENEMY_BOSS
};

/*******************************************************************************
* 構造体定義
*******************************************************************************/

typedef struct
{
	LPDIRECT3DTEXTURE9		Texture;				// テクスチャ情報
	VERTEX_2D				vertexWk[NUM_VERTEX];	// 頂点情報格納ワーク
	D3DXVECTOR3				pos;					// エネミーの移動量
	D3DXVECTOR3				rot;					// エネミーの回転量
	D3DXVECTOR3				vecOldPos;				// エネミーの旧座標
	D3DXVECTOR3				vecDestination;			// エネミーの移動先
	D3DXVECTOR3				vecTargetPos;			// エネミーのターゲット座標
	D3DXVECTOR3				vecTa;					// 距離
	D3DXVECTOR3				vecMove;				// 移動量
	D3DXVECTOR2				vecChangeSize;			// エネミーのテクスチャサイズ変更(x,y)
	D3DXVECTOR2				size;					// エネミーのテクスチャサイズ(x,y)

	int						nCountAnim;				// アニメーションカウント
	int						nPatternAnim;			// アニメーションパターンナンバー
	int						nType;					// 適用テクスチャタイプ
	int						nPopType;				// 出現タイプ
	int						nMoveType;				// 移動タイプ
	int						nBulletType;			// バレットタイプ
	int						nBulletShiftAngle;		// バレット角度変更
	int						nBulletPattern;			// バレットパターン

	int						nBulletTexture[ENEMYBULLET_TYPE_MAX];		// バレットのテクスチャー
	int						nBulletCount[ENEMYBULLET_TYPE_MAX];			// バレットの発射数カウント
	int						nBulletSpeed[ENEMYBULLET_TYPE_MAX];			// バレットの移動速度
	int						nBulletSetTime[ENEMYBULLET_TYPE_MAX];		// バレットの発射時間セット
	int						nBulletTime[ENEMYBULLET_TYPE_MAX];			// バレットの発射時間
	int						nBulletAction[ENEMYBULLET_TYPE_MAX];		// バレットの連射速度
	int						nBulletSplit[ENEMYBULLET_TYPE_MAX];			// バレットの射角分割
	int						nBulletSpeedChange[ENEMYBULLET_TYPE_MAX];	// バレットの移動速度変更
	float					nBulletOption[ENEMYBULLET_TYPE_MAX];		// バレットのオプション(WAY数など)

	int						nShotTime;				// ショットタイム
	int						nMoveCount;				// 移動カウント
	int						nMoveFlag;				// 移動フラグ
	int						nStopFlag;				// 停止フラグ
	int						nActionCount;			// アクションカウント
	int						nActionFlag;			// アクションフラグ
	int						nCoolDown;				// 再使用クールダウン
	int						nSpec;					// エネミーの性能
	int						nPopCount;				// エネミーの出現カウント

	float					fHitPoint;				// エネミーのHP
	float					fBaseAngle;				// 回転用角度（θ）
	float					fRadius;				// 回転用半径

	bool					bUse;					// true:使用  false:未使用
	bool					bCalculation;			// 計算フラグ
	bool					bParameterUse;			// パラメータフラグ
	bool					bBossReversal;			// ボスバレット逆転フラグ
	bool					bBulletStandby[ENEMYBULLET_TYPE_MAX];			// ショット準備完了
	bool					bBulletFlag[ENEMYBULLET_TYPE_MAX];			// バレットフラグ

	float					fAngle;					// バレット01の角度
}ENEMY;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitEnemy(int type);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void InitStatusEnemy(int nEnemy);
void SetEnemyLevel(int nLevel);
void SetEnemy(int nType, int nPopType, int nMoveType, int nBulletType, int nBulletTexture, int nBulletSpeed, int nBulletSetTime, int nBulletAction, int nBulletSplit, int nBulletSpeedChange, float nBulletOption);
void SetBossEnemy(int nType, int nPopType, int nMoveType, int nBulletType, int nBulletTexture, int nBulletSpeed, int nBulletSetTime, int nBulletAction, int nBulletSplit, int nBulletSpeedChange, float nBulletOption);
ENEMY *GetEnemy(int no);

#endif
