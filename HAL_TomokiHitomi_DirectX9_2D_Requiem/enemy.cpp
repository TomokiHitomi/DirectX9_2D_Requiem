
//=============================================================================
//
// �G�l�~�[���� [enemy.cpp]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
//#include "main.h"
#include "enemy.h"
#include "enemybullet.h"
#include "input.h"
#include "parameter.h"
#include "close.h"
#include "player.h"
#include "game.h"
#include "sound.h"
#include "score.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexEnemy(int no);
void SetTextureEnemy( int no, int cntPattern );
void SetVertexEnemy(int no);
void SetMoveEnemy(int nEnemy, int nMoveType);
void SetMovePosEnemy(int nEnemy, float fPosX, float fPosY);
void SetMoveStopEnemy(int nEnemy);
void SetMoveStopPosEnemy(int nEnemy);

void SetBulletTypeEnemy(int nEnemy);
void SetBulletTypeBossEnemy(int nEnemy);
void SetBulletTypeEnemy00(int nEnemy);
void SetBulletTypeEnemy01(int nEnemy);
void SetBulletTypeEnemy02(int nEnemy);
void SetBulletTypeEnemy03(int nEnemy);
void SetBulletTypeEnemy04(int nEnemy);
void SetBulletTypeEnemy05(int nEnemy);
void SetBulletTypeEnemy06(int nEnemy);
void SetBulletTypeEnemy07(int nEnemy);
void SetBulletTypeEnemy08(int nEnemy);

void SetMoveTypeEnemy(int nEnemy, int nMoveType);
void SetMoveCalculationEnemy(int nEnemy);

void SetMovePatternEnemy00(int nEnemy, int nMoveFlag);
void SetMovePatternEnemy01(int nEnemy, int nMoveFlag);
void SetMovePatternEnemy02(int nEnemy, int nMoveFlag);
void SetMovePatternEnemy03(int nEnemy, int nMoveFlag);
void SetMovePatternEnemy04(int nEnemy, int nMoveFlag);
void SetMovePatternEnemy05(int nEnemy, int nMoveFlag);
void SetMovePatternEnemy06(int nEnemy, int nMoveFlag);
void SetMovePatternEnemy07(int nEnemy, int nMoveFlag);
void SetMovePatternEnemy08(int nEnemy, int nMoveFlag);
void SetMovePatternEnemy09(int nEnemy, int nMoveFlag);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
ENEMY					enemyWk[ENEMY_MAX];

// �e�N�X�`���ւ̃|���S��
LPDIRECT3DTEXTURE9		pD3DTextureEnemy = NULL;

int g_nEnemyCount;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemy(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY *enemy = &enemyWk[0];

	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,	// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_ENEMY00,			// �t�@�C���̖��O
			&pD3DTextureEnemy);				// �ǂݍ��ރ������̃|�C���^
	}

	// �G�l�~�[�̏�����
	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		enemy->Texture = pD3DTextureEnemy;			// �e�N�X�`���ւ̃G�l�~�[
		enemy->size = D3DXVECTOR2(TEXTURE_ENEMY00_SIZE_X, TEXTURE_ENEMY00_SIZE_Y);

		// �e�X�e�[�^�X�̏�����
		InitStatusEnemy(i);

		// ���_���̍쐬
		MakeVertexEnemy(i);
	}

	g_nEnemyCount = 1;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemy(void)
{
	ENEMY *enemy = &enemyWk[0];
	// ���������
	if (pD3DTextureEnemy != NULL)
	{
		pD3DTextureEnemy->Release();
		pD3DTextureEnemy = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemy(void)
{
	ENEMY *enemy = &enemyWk[0];
	CLOSE *close = GetClose(0);
	int *count = GetCount();

	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		// �N�[���_�E���i�z�[�~���O�o���b�g�̍Ēǔ��h�~�j
		if (enemy->nCoolDown > 0)
		{
			enemy->nCoolDown--;
			if (enemy->nCoolDown <= 0)
			{
				enemy->nCoolDown = 0;
			}
		}

		// �t�@�C����荞�ݗp�i�^�p���~�j
		//if (enemy->nPopCount == *count && *count > 0)
		//{
		//	enemy->bUse = true;
		//}

		if (enemy->bUse)
		{
			// �A�j���[�V����
			enemy->nCountAnim++;
			if ((enemy->nCountAnim % TIME_ANIMATION_ENEMY) == 0)
			{
				// �p�^�[���̐؂�ւ�
				enemy->nPatternAnim = (enemy->nPatternAnim + 1) % TEXTURE_PATTERN_DIVIDE_X_ENEMY + (TEXTURE_PATTERN_DIVIDE_X_ENEMY * enemy->nType);

			}

			// HP�EMP�Q�[�W�̐ݒ�
			if (!enemy->bParameterUse)
			{
				SetParameter(2, enemy->pos, i);
				enemy->bParameterUse = true;
			}

			// �ړ�����
			SetMoveEnemy(i,enemy->nMoveType);

			if (enemy->nSpec == ENEMY_NORMAL || enemy->nSpec == ENEMY_STRONG)
			{
				// �V���b�g����
				SetBulletTypeEnemy(i);
			}
			else if (enemy->nSpec == ENEMY_BOSS)
			{
				if (!close->bUse && enemy->bBossReversal)
				{
					SetBgmVol(2, true);
				}
				// �V���b�g����
				SetBulletTypeBossEnemy(i);
			}

			// ��]����
			enemy->rot.z += ENEMY_ROTATION;
			if (enemy->rot.z >= D3DX_PI * 2.0f)
			{
				// 360�x�𒴂�����360�x������
				enemy->rot.z -= D3DX_PI * 2.0f;
			}

			// �e�N�X�`�����W��ݒ�
			SetTextureEnemy(i, enemy->nPatternAnim);
			// �ړ���̍��W�Œ��_��ݒ�
			SetVertexEnemy(i);
			enemy->nActionCount++;
		}
	}
	if (g_nEnemyCount == 0)
	{
		close->bUse = true;
		close->bClearFlag = true;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY *enemy = &enemyWk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		if (enemy->bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, enemy->Texture);

			// �G�l�~�[�̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_ENEMY, enemy->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexEnemy(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMY *enemy = &enemyWk[no];

	// �p�x�����߂�
	enemy->fBaseAngle = atan2f(TEXTURE_ENEMY00_SIZE_Y, TEXTURE_ENEMY00_SIZE_X);

	// ���a�����߂�
	D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_ENEMY00_SIZE_X, TEXTURE_ENEMY00_SIZE_Y);
	enemy->fRadius = D3DXVec2Length(&temp);

	// ���_���W�̐ݒ�
	enemy->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	enemy->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_ENEMY00_SIZE_X, 100.0f, 0.0f);
	enemy->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_ENEMY00_SIZE_Y, 0.0f);
	enemy->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_ENEMY00_SIZE_X, 100.0f+TEXTURE_ENEMY00_SIZE_Y, 0.0f);

	// rhw�̐ݒ�
	enemy->vertexWk[0].rhw =
	enemy->vertexWk[1].rhw =
	enemy->vertexWk[2].rhw =
	enemy->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	enemy->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemy->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	enemy->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	enemy->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_ENEMY, 0.0f );
	enemy->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_ENEMY );
	enemy->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_ENEMY, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_ENEMY );

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureEnemy( int no, int cntPattern )
{
	ENEMY *enemy = &enemyWk[no];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_ENEMY;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_ENEMY;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMY;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMY;
	enemy->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	enemy->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	enemy->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	enemy->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// ���_���W�̐ݒ�֐�
//=============================================================================
void SetVertexEnemy(int no)
{
	ENEMY *enemy = &enemyWk[no];
	//// ���_0:��]����
	//enemy->vertexWk[0].vtx.x = (enemy->pos.x - cosf(enemy->fBaseAngle + enemy->rot.z) * enemy->fRadius) * enemy->vecChangeSize.x;
	//enemy->vertexWk[0].vtx.y = (enemy->pos.y - sinf(enemy->fBaseAngle + enemy->rot.z) * enemy->fRadius) * enemy->vecChangeSize.y;
	//enemy->vertexWk[0].vtx.z = 0.0f;

	//// ���_1:��]����
	//enemy->vertexWk[1].vtx.x = (enemy->pos.x + cosf(enemy->fBaseAngle - enemy->rot.z) * enemy->fRadius) * enemy->vecChangeSize.x;
	//enemy->vertexWk[1].vtx.y = (enemy->pos.y - sinf(enemy->fBaseAngle - enemy->rot.z) * enemy->fRadius) * enemy->vecChangeSize.y;
	//enemy->vertexWk[1].vtx.z = 0.0f;

	//// ���_2:��]����
	//enemy->vertexWk[2].vtx.x = (enemy->pos.x - cosf(enemy->fBaseAngle - enemy->rot.z) * enemy->fRadius) * enemy->vecChangeSize.x;
	//enemy->vertexWk[2].vtx.y = (enemy->pos.y + sinf(enemy->fBaseAngle - enemy->rot.z) * enemy->fRadius) * enemy->vecChangeSize.y;
	//enemy->vertexWk[2].vtx.z = 0.0f;

	//// ���_3:��]����
	//enemy->vertexWk[3].vtx.x = (enemy->pos.x + cosf(enemy->fBaseAngle + enemy->rot.z) * enemy->fRadius) * enemy->vecChangeSize.x;
	//enemy->vertexWk[3].vtx.y = (enemy->pos.y + sinf(enemy->fBaseAngle + enemy->rot.z) * enemy->fRadius) * enemy->vecChangeSize.y;
	//enemy->vertexWk[3].vtx.z = 0.0f;

	enemy->vertexWk[0].vtx.x = enemy->pos.x - (TEXTURE_ENEMY00_SIZE_X * enemy->vecChangeSize.x);
	enemy->vertexWk[0].vtx.y = enemy->pos.y - (TEXTURE_ENEMY00_SIZE_Y * enemy->vecChangeSize.y);
	enemy->vertexWk[0].vtx.z = 0.0f;

	enemy->vertexWk[1].vtx.x = enemy->pos.x + (TEXTURE_ENEMY00_SIZE_X * enemy->vecChangeSize.x);
	enemy->vertexWk[1].vtx.y = enemy->pos.y - (TEXTURE_ENEMY00_SIZE_Y * enemy->vecChangeSize.y);
	enemy->vertexWk[1].vtx.z = 0.0f;

	enemy->vertexWk[2].vtx.x = enemy->pos.x - (TEXTURE_ENEMY00_SIZE_X * enemy->vecChangeSize.x);
	enemy->vertexWk[2].vtx.y = enemy->pos.y + (TEXTURE_ENEMY00_SIZE_Y * enemy->vecChangeSize.y);
	enemy->vertexWk[2].vtx.z = 0.0f;

	enemy->vertexWk[3].vtx.x = enemy->pos.x + (TEXTURE_ENEMY00_SIZE_X * enemy->vecChangeSize.x);
	enemy->vertexWk[3].vtx.y = enemy->pos.y + (TEXTURE_ENEMY00_SIZE_Y * enemy->vecChangeSize.y);
	enemy->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �G�l�~�[�V���b�g�^�C�v
//=============================================================================
void SetBulletTypeEnemy(int nEnemy)
{
	ENEMY *enemy = &enemyWk[nEnemy];

	switch (enemy->nBulletType)
	{
	case 0:
		SetBulletTypeEnemy00(nEnemy);
		break;
	case 1:
		SetBulletTypeEnemy01(nEnemy);
		break;
	case 2:
		SetBulletTypeEnemy02(nEnemy);
		break;
	case 3:
		SetBulletTypeEnemy03(nEnemy);
		break;
	case 4:
		SetBulletTypeEnemy04(nEnemy);
		break;
	case 5:
		SetBulletTypeEnemy05(nEnemy);
		break;
	case 6:
		SetBulletTypeEnemy06(nEnemy);
		break;
	case 7:
		SetBulletTypeEnemy07(nEnemy);
		break;
	case 8:
		SetBulletTypeEnemy08(nEnemy);
		break;
	}

	enemy->nBulletTime[enemy->nBulletType]--;
	if (enemy->nBulletTime[enemy->nBulletType] <= 0)
	{
		enemy->nBulletTime[enemy->nBulletType] = 0;
	}
}

//=============================================================================
// �{�X�G�l�~�[�V���b�g�^�C�v
//=============================================================================
void SetBulletTypeBossEnemy(int nEnemy)
{
	ENEMY *enemy = &enemyWk[nEnemy];

	enemy->nBulletType = BTYPE00;
	SetBulletTypeEnemy00(nEnemy);

	enemy->nBulletType = BTYPE01;
	SetBulletTypeEnemy01(nEnemy);

	enemy->nBulletType = BTYPE02;
	SetBulletTypeEnemy02(nEnemy);

	enemy->nBulletType = BTYPE03;
	SetBulletTypeEnemy03(nEnemy);

	enemy->nBulletType = BTYPE04;
	SetBulletTypeEnemy04(nEnemy);

	enemy->nBulletType = BTYPE05;
	SetBulletTypeEnemy05(nEnemy);

	enemy->nBulletType = BTYPE06;
	SetBulletTypeEnemy06(nEnemy);

	enemy->nBulletType = BTYPE07;
	SetBulletTypeEnemy07(nEnemy);

	enemy->nBulletType = BTYPE08;
	SetBulletTypeEnemy07(nEnemy);

	for (int i = 0; i < ENEMYBULLET_TYPE_MAX; i++)
	{
		enemy->nBulletTime[i]--;
		if (enemy->nBulletTime[i] <= 0)
		{
			enemy->nBulletTime[i] = 0;
		}
	}
}

//=============================================================================
// �G�l�~�[�V���b�g�^�C�v00
//=============================================================================
void SetBulletTypeEnemy00(int nEnemy)
{
	ENEMY *enemy = &enemyWk[nEnemy];
	PLAYER *player = GetPlayer(0);

	if (enemy->bBulletFlag[enemy->nBulletType])
	{
		enemy->nBulletTime[enemy->nBulletType] = enemy->nBulletSetTime[enemy->nBulletType];
		enemy->vecTargetPos = player->pos;
		enemy->bBulletFlag[enemy->nBulletType] = false;
	}
	if (enemy->nBulletTime[enemy->nBulletType] != 0)
	{
		if (enemy->nBulletTime[enemy->nBulletType] % enemy->nBulletAction[enemy->nBulletType] == 0)
		{
			SetEnemybullet(nEnemy, enemy->nBulletSplit[enemy->nBulletType]);
		}
	}
}

//=============================================================================
// �G�l�~�[�V���b�g�^�C�v01
//=============================================================================
void SetBulletTypeEnemy01(int nEnemy)
{
	ENEMY *enemy = &enemyWk[nEnemy];
	PLAYER *player = GetPlayer(0);

	if (enemy->bBulletFlag[enemy->nBulletType])
	{
		enemy->nBulletTime[enemy->nBulletType] = enemy->nBulletSetTime[enemy->nBulletType];
		enemy->vecTargetPos = player->pos;
		enemy->bBulletFlag[enemy->nBulletType] = false;
	}
	if (enemy->nBulletTime[enemy->nBulletType] != 0)
	{
		SetEnemybullet(nEnemy, enemy->nBulletSplit[enemy->nBulletType]);
	}
}

//=============================================================================
// �G�l�~�[�V���b�g�^�C�v02
//=============================================================================
void SetBulletTypeEnemy02(int nEnemy)
{
	ENEMY *enemy = &enemyWk[nEnemy];
	PLAYER *player = GetPlayer(0);

	if (enemy->bBulletFlag[enemy->nBulletType])
	{
		enemy->nBulletTime[enemy->nBulletType] = enemy->nBulletSetTime[enemy->nBulletType];
		enemy->vecTargetPos = player->pos;
		enemy->bBulletFlag[enemy->nBulletType] = false;
	}
	if (enemy->nBulletTime[enemy->nBulletType] != 0)
	{
		SetEnemybullet(nEnemy, enemy->nBulletSplit[enemy->nBulletType]);
	}
}

//=============================================================================
// �G�l�~�[�V���b�g�^�C�v03
//=============================================================================
void SetBulletTypeEnemy03(int nEnemy)
{
	ENEMY *enemy = &enemyWk[nEnemy];
	PLAYER *player = GetPlayer(0);

	if (enemy->bBulletFlag[enemy->nBulletType])
	{
		enemy->nBulletTime[enemy->nBulletType] = enemy->nBulletSetTime[enemy->nBulletType];
		enemy->vecTargetPos = player->pos;
		enemy->bBulletFlag[enemy->nBulletType] = false;
	}
	if (enemy->nBulletTime[enemy->nBulletType] != 0)
	{
		SetEnemybullet(nEnemy, enemy->nBulletSplit[enemy->nBulletType]);
	}
}

//=============================================================================
// �G�l�~�[�V���b�g�^�C�v04
//=============================================================================
void SetBulletTypeEnemy04(int nEnemy)
{
	ENEMY *enemy = &enemyWk[nEnemy];
	PLAYER *player = GetPlayer(0);

	if (enemy->bBulletFlag[enemy->nBulletType])
	{
		enemy->nBulletTime[enemy->nBulletType] = enemy->nBulletSetTime[enemy->nBulletType];
		enemy->vecTargetPos = player->pos;
		enemy->bBulletFlag[enemy->nBulletType] = false;
	}
	if (enemy->nBulletTime[enemy->nBulletType] != 0)
	{
		SetEnemybullet(nEnemy, enemy->nBulletSplit[enemy->nBulletType]);
	}
}

//=============================================================================
// �G�l�~�[�V���b�g�^�C�v05
//=============================================================================
void SetBulletTypeEnemy05(int nEnemy)
{
	ENEMY *enemy = &enemyWk[nEnemy];
	PLAYER *player = GetPlayer(0);

	if (enemy->bBulletFlag[enemy->nBulletType])
	{
		enemy->nBulletTime[enemy->nBulletType] = enemy->nBulletSetTime[enemy->nBulletType];
		enemy->vecTargetPos = player->pos;
		enemy->bBulletFlag[enemy->nBulletType] = false;
	}
	if (enemy->nBulletTime[enemy->nBulletType] != 0)
	{
		if (enemy->nBulletTime[enemy->nBulletType] % enemy->nBulletAction[enemy->nBulletType] == 0)
		{
			SetEnemybullet(nEnemy, enemy->nBulletSplit[enemy->nBulletType]);
		}
		enemy->nBulletShiftAngle++;
	}
}

//=============================================================================
// �G�l�~�[�V���b�g�^�C�v06
//=============================================================================
void SetBulletTypeEnemy06(int nEnemy)
{
	ENEMY *enemy = &enemyWk[nEnemy];
	PLAYER *player = GetPlayer(0);

	if (enemy->bBulletFlag[enemy->nBulletType])
	{
		enemy->nBulletTime[enemy->nBulletType] = enemy->nBulletSetTime[enemy->nBulletType];
		enemy->vecTargetPos = player->pos;
		enemy->bBulletFlag[enemy->nBulletType] = false;
	}
	if (enemy->nBulletTime[enemy->nBulletType] != 0)
	{
		if (enemy->nBulletTime[enemy->nBulletType] % enemy->nBulletAction[enemy->nBulletType] == 0)
		{
			SetEnemybullet(nEnemy, enemy->nBulletSplit[enemy->nBulletType]);
		}
		enemy->nBulletShiftAngle++;
	}
}

//=============================================================================
// �G�l�~�[�V���b�g�^�C�v07
//=============================================================================
void SetBulletTypeEnemy07(int nEnemy)
{
	ENEMY *enemy = &enemyWk[nEnemy];
	PLAYER *player = GetPlayer(0);

	if (enemy->bBulletFlag[enemy->nBulletType])
	{
		enemy->nBulletTime[enemy->nBulletType] = enemy->nBulletSetTime[enemy->nBulletType];
		enemy->vecTargetPos = player->pos;
		enemy->bBulletFlag[enemy->nBulletType] = false;
	}
	if (enemy->nBulletTime[enemy->nBulletType] != 0)
	{
		if (enemy->nBulletTime[enemy->nBulletType] % enemy->nBulletAction[enemy->nBulletType] == 0)
		{
			SetEnemybullet(nEnemy, enemy->nBulletSplit[enemy->nBulletType]);
		}
		enemy->nBulletShiftAngle++;
	}
}

//=============================================================================
// �G�l�~�[�V���b�g�^�C�v08
//=============================================================================
void SetBulletTypeEnemy08(int nEnemy)
{
	ENEMY *enemy = &enemyWk[nEnemy];
	PLAYER *player = GetPlayer(0);

	if (enemy->bBulletFlag[enemy->nBulletType])
	{
		enemy->nBulletTime[enemy->nBulletType] = enemy->nBulletSetTime[enemy->nBulletType];
		enemy->vecTargetPos = player->pos;
		enemy->bBulletFlag[enemy->nBulletType] = false;
	}
	if (enemy->nBulletTime[enemy->nBulletType] != 0)
	{
		if (enemy->nBulletTime[enemy->nBulletType] % enemy->nBulletAction[enemy->nBulletType] == 0)
		{
			SetEnemybullet(nEnemy, enemy->nBulletSplit[enemy->nBulletType]);
		}
		enemy->nBulletShiftAngle++;
	}
}

//=============================================================================
// �G�l�~�[�̐ݒ菈���i�s��̂��߉^�p���~�j
//=============================================================================
void SetEnemyLevel(int nLevel)
{
	//ENEMY *enemy = &enemyWk[0];

	//FILE *fp;
	//char *fname;
	//int data[FILE_DATA_MAX];

	//// ���x���ɉ������t�@�C����I��
	//switch (nLevel)
	//{
	//case EASY:
	//	fname = FILE_ENEMY_EASY;
	//	break;
	//case NORMAL:
	//	fname = FILE_ENEMY_NORMAL;
	//	break;
	//case HARD:
	//	fname = FILE_ENEMY_HARD;
	//	break;
	//}

	//// �t�@�C���I�[�v���G���[����
	//fp = fopen(fname, "r");
	//if (fp == NULL) {
	//	return;
	//}

	//// �G�l�~�[�X�e�[�^�X�ݒ�
	//while (fscanf(fp, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", &data[0], &data[1], &data[2], &data[3], &data[4], &data[5], &data[6], &data[7], &data[8], &data[9], &data[10], &data[11]) != EOF)
	//{
	//	if (data[0] <= 0)
	//	{
	//		break;
	//	}
	//	enemy->nPopCount = data[0];
	//	enemy->nType = data[1];
	//	if (data[1] >= TYPE_S_WH)
	//	{
	//		enemy->nSpec = ENEMY_STRONG;
	//		enemy->fHitPoint = STRONG_ENEMY_HPMAX;
	//	}
	//	enemy->pos = D3DXVECTOR3(SCREEN_WIDTH + TEXTURE_ENEMY00_SIZE_X, data[2] * ENEMY_POP_POS_X + (ENEMY_POP_POS_X / 2), 0.0f);
	//	enemy->nMoveType = data[3];
	//	enemy->nBulletType = data[4];					// �o���b�g�^�C�v��ݒ�
	//	enemy->nBulletTexture[data[1]] = data[5];		// �o���b�g�e�N�X�`���[��ݒ�
	//	enemy->nBulletSpeed[data[1]] = data[6];			// �o���b�g�̃X�s�[�h��ݒ�
	//	enemy->nBulletSetTime[data[1]] = data[7];		// �o���b�g�̔��ˎ��Ԃ�ݒ�
	//	enemy->nBulletAction[data[1]] = data[8];		// �o���b�g�̘A�ˑ��x��ݒ�
	//	enemy->nBulletSplit[data[1]] = data[9];			// �o���b�g�̎ˊp������ݒ�
	//	enemy->nBulletSpeedChange[data[1]] = data[10];	// �o���b�g�̃X�s�[�h�`�F���W��ݒ�
	//	enemy->nBulletOption[data[1]] = data[11];		// �o���b�g�̃I�v�V������ݒ�
	//	enemy++;
	//}

	//fclose(fp);
}


//=============================================================================
// �G�l�~�[�̏o������
//=============================================================================
void SetEnemy(int nType, int nPopType, int nMoveType, int nBulletType, int nBulletTexture, int nBulletSpeed, int nBulletSetTime, int nBulletAction, int nBulletSplit, int nBulletSpeedChange, float nBulletOption)
{
	ENEMY *enemy = &enemyWk[0];

	// ���g�p�̃G�l�~�[��T��
	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		if (!enemy->bUse && enemy->nCoolDown == 0)
		{
			// �G�l�~�[��L���ɂ���
			enemy->bUse = true;
			// �G�l�~�[�̏����e�N�X�`����ݒ�
			enemy->nPatternAnim = TEXTURE_PATTERN_DIVIDE_X_ENEMY * nType;
			// �G�l�~�[�̃^�C�v��ݒ�
			enemy->nType = nType;
			if (nType >= TYPE_S_WH)
			{
				enemy->nSpec = ENEMY_STRONG;
				enemy->fHitPoint = STRONG_ENEMY_HPMAX;
			}

			// �o�����W�E�ړ��E���E�̐ݒ�
			enemy->nMoveType = nMoveType;
			// �o�����W�̐ݒ�
			enemy->pos = D3DXVECTOR3(SCREEN_WIDTH + TEXTURE_ENEMY00_SIZE_X, nPopType*ENEMY_POP_POS_X + (ENEMY_POP_POS_X/2), 0.0f);
			// �o���b�g�^�C�v��ݒ�
			enemy->nBulletType = nBulletType;
			// �o���b�g�e�N�X�`���[��ݒ�
			enemy->nBulletTexture[nBulletType] = nBulletTexture;
			// �o���b�g�̃X�s�[�h��ݒ�
			enemy->nBulletSpeed[nBulletType] = nBulletSpeed;
			// �o���b�g�̔��ˎ��Ԃ�ݒ�
			enemy->nBulletSetTime[nBulletType] = nBulletSetTime;
			// �o���b�g�̘A�ˑ��x��ݒ�
			enemy->nBulletAction[nBulletType] = nBulletAction;
			// �o���b�g�̎ˊp������ݒ�
			enemy->nBulletSplit[nBulletType] = nBulletSplit;
			// �o���b�g�̃X�s�[�h�`�F���W��ݒ�
			enemy->nBulletSpeedChange[nBulletType] = nBulletSpeedChange;
			// �o���b�g�̃I�v�V������ݒ�
			enemy->nBulletOption[nBulletType] = nBulletOption;

			return;
		}
	}
}

//=============================================================================
// �{�X�G�l�~�[�̏o������
//=============================================================================
void SetBossEnemy(int nType, int nPopType, int nMoveType, int nBulletType, int nBulletTexture, int nBulletSpeed, int nBulletSetTime, int nBulletAction, int nBulletSplit, int nBulletSpeedChange, float nBulletOption)
{
	ENEMY *enemy = &enemyWk[0];

	// ���g�p�̃G�l�~�[��T��
	for (int i = 0; i < ENEMY_MAX; i++, enemy++)
	{
		if (!enemy->bUse && enemy->nCoolDown == 0)
		{
			// �G�l�~�[��L���ɂ���
			enemy->bUse = true;
			// �G�l�~�[�̏����e�N�X�`����ݒ�
			enemy->nPatternAnim = TEXTURE_PATTERN_DIVIDE_X_ENEMY * nType;
			// �G�l�~�[�̃^�C�v��ݒ�
			enemy->nType = nType;
			// �o�����W�E�ړ��E���E�̐ݒ�
			enemy->nMoveType = nMoveType;
			// �o�����W�̐ݒ�
			enemy->pos = D3DXVECTOR3(SCREEN_WIDTH + TEXTURE_ENEMY00_SIZE_X, nPopType*ENEMY_POP_POS_X + (ENEMY_POP_POS_X / 2), 0.0f);
			// �o���b�g�^�C�v��ݒ�
			enemy->nBulletType = nBulletType;

			// �{�X�o���b�g�̃X�e�[�^�X�ݒ�
			SetGameLevelBossSpec(i);
			// �{�X�t���O��ݒ�
			enemy->nSpec = ENEMY_BOSS;
			// �{�XHP��ݒ�
			enemy->fHitPoint = BOSS_ENEMY_HPMAX;
			// �{�X�p�T�C�Y�ύX
			enemy->size = D3DXVECTOR2(TEXTURE_ENEMY00_SIZE_X*TEXTURE_CHANGE_BOSS_ENEMY_X, TEXTURE_ENEMY00_SIZE_Y*TEXTURE_CHANGE_BOSS_ENEMY_Y);
			// ���_���W�ύX
			enemy->vecChangeSize = D3DXVECTOR2(TEXTURE_CHANGE_BOSS_ENEMY_X, TEXTURE_CHANGE_BOSS_ENEMY_Y);
			return;
		}
	}
}

//=============================================================================
// �G�l�~�[�̍ė��p����
//=============================================================================
void InitStatusEnemy(int nEnemy)
{
	ENEMY *enemy = &enemyWk[nEnemy];

	// �G�l�~�[�X�e�[�^�X�̏�����
	enemy->bUse = false;
	enemy->bCalculation = false;
	enemy->bParameterUse = false;
	enemy->bBossReversal = false;

	enemy->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	enemy->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	enemy->vecDestination = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	enemy->vecTargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	enemy->vecOldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	enemy->vecMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	enemy->vecTa = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	enemy->vecChangeSize = D3DXVECTOR2((float)TEXTURE_CHANGE_ENEMY_X, (float)TEXTURE_CHANGE_ENEMY_Y);

	for (int i = 0; i < ENEMYBULLET_TYPE_MAX; i++)
	{
		enemy->bBulletStandby[i] = false;
		enemy->bBulletFlag[i] = false;
		enemy->nBulletTexture[i] = 0;
		enemy->nBulletCount[i] = 0;
		enemy->nBulletSpeed[i] = 0;
		enemy->nBulletSetTime[i] = 0;
		enemy->nBulletTime[i] = 0;
		enemy->nBulletAction[i] = 0;
		enemy->nBulletSplit[i] = 0;
		enemy->nBulletSpeedChange[i] = 0;
		enemy->nBulletOption[i] = 0;
	}

	enemy->nCountAnim = 0;
	enemy->nPatternAnim = 0;
	enemy->nType = 0;
	enemy->nMoveType = 0;
	enemy->nBulletType = 0;
	enemy->nBulletPattern = 0;
	enemy->nBulletShiftAngle = 0;

	enemy->nBulletTime[enemy->nBulletType] = 0;
	enemy->nMoveCount = 0;
	enemy->nMoveFlag = 0;
	enemy->nStopFlag = 0;
	enemy->nActionCount = 0;
	enemy->nActionFlag = 0;
	enemy->nCoolDown = ENEMY_COOLDOWN;
	enemy->nSpec = ENEMY_NORMAL;
	enemy->nPopCount = 0;

	enemy->fHitPoint = ENEMY_HPMAX;
	enemy->fAngle = 0.0f;
	return;
}

//=============================================================================
// �G�l�~�[�̈ړ�����
//=============================================================================
void SetMoveEnemy(int nEnemy, int nMoveType)
{
	ENEMY *enemy = &enemyWk[nEnemy];

	// �ړ�����
	if (enemy->nActionCount % ENEMY_ACTION == 0)
	{
		SetMoveTypeEnemy(nEnemy, nMoveType);
	}

	// �ړ��ʌv�Z
	if (enemy->bCalculation)
	{
		SetMoveCalculationEnemy(nEnemy);
	}

	// �ړ���~����
	SetMoveStopEnemy(nEnemy);

	// �ړ��ʓK�p
	enemy->pos.x += enemy->vecMove.x;
	enemy->pos.y += enemy->vecMove.y;

	return;
}

//=============================================================================
// �G�l�~�[�̈ړ��^�C�v�ݒ�
//=============================================================================
void SetMoveTypeEnemy(int nEnemy, int nMoveType)
{
	ENEMY *enemy = &enemyWk[nEnemy];

	// �^�C�v�ɉ������ړ�����
	switch (nMoveType)
	{
	case 0:
		SetMovePatternEnemy00(nEnemy, enemy->nMoveFlag);
		break;
	case 1:
		SetMovePatternEnemy01(nEnemy, enemy->nMoveFlag);
		break;
	case 2:
		SetMovePatternEnemy02(nEnemy, enemy->nMoveFlag);
		break;
	case 3:
		SetMovePatternEnemy03(nEnemy, enemy->nMoveFlag);
		break;
	case 4:
		SetMovePatternEnemy04(nEnemy, enemy->nMoveFlag);
		break;
	case 5:
		SetMovePatternEnemy05(nEnemy, enemy->nMoveFlag);
		break;
	case 6:
		SetMovePatternEnemy06(nEnemy, enemy->nMoveFlag);
		break;
	case 7:
		SetMovePatternEnemy07(nEnemy, enemy->nMoveFlag);
		break;
	case 8:
		SetMovePatternEnemy08(nEnemy, enemy->nMoveFlag);
		break;
	case 9:
		SetMovePatternEnemy09(nEnemy, enemy->nMoveFlag);
		break;
	}
	enemy->bCalculation = true;
	return;
}

//=============================================================================
// �G�l�~�[�̈ړ��p�^�[��00
//=============================================================================
void SetMovePatternEnemy00(int nEnemy, int nMoveFlag)
{
	ENEMY *enemy = &enemyWk[nEnemy];

	switch (nMoveFlag)
	{
	case 0:
		SetMovePosEnemy(nEnemy, -300.0f * SCREEN_SCALING, +100.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 1:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, +300.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 2:
		SetMovePosEnemy(nEnemy, +200.0f * SCREEN_SCALING, +100.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 3:
		SetMovePosEnemy(nEnemy, +500.0f, 0.0f);
		break;
	case 4:
		SetMovePosEnemy(nEnemy, +500.0f, 0.0f);
		break;
	case 5:
		SetMovePosEnemy(nEnemy, +500.0f, 0.0f);
		break;
	case 6:
		InitStatusEnemy(nEnemy);
		break;
	}
	return;
}


//=============================================================================
// �G�l�~�[�̈ړ��p�^�[��01
//=============================================================================
void SetMovePatternEnemy01(int nEnemy, int nMoveFlag)
{
	ENEMY *enemy = &enemyWk[nEnemy];

	switch (nMoveFlag)
	{
	case 0:
		SetMovePosEnemy(nEnemy, -300.0f * SCREEN_SCALING, -100.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 1:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, -300.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 2:
		SetMovePosEnemy(nEnemy, +200.0f * SCREEN_SCALING, -100.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 3:
		SetMovePosEnemy(nEnemy, +500.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 4:
		SetMovePosEnemy(nEnemy, +500.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 5:
		SetMovePosEnemy(nEnemy, +500.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 6:
		InitStatusEnemy(nEnemy);
		break;
	}
	return;
}

//=============================================================================
// �G�l�~�[�̈ړ��p�^�[��02
//=============================================================================
void SetMovePatternEnemy02(int nEnemy, int nMoveFlag)
{
	ENEMY *enemy = &enemyWk[nEnemy];

	switch (nMoveFlag)
	{
	case 0:
		SetMovePosEnemy(nEnemy, -300.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 1:
		SetMovePosEnemy(nEnemy, -300.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 2:
		SetMovePosEnemy(nEnemy, -300.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 3:
		SetMovePosEnemy(nEnemy, -300.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 4:
		SetMovePosEnemy(nEnemy, -300.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 5:
		SetMovePosEnemy(nEnemy, -300.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 6:
		InitStatusEnemy(nEnemy);
		break;
	}
	return;
}

//=============================================================================
// �G�l�~�[�̈ړ��p�^�[��03
//=============================================================================
void SetMovePatternEnemy03(int nEnemy, int nMoveFlag)
{
	ENEMY *enemy = &enemyWk[nEnemy];

	switch (nMoveFlag)
	{
	case 0:
		SetMovePosEnemy(nEnemy, -300.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 1:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 2:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 3:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 4:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 5:
		SetMovePosEnemy(nEnemy, 500.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 6:
		SetMovePosEnemy(nEnemy, 500.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 7:
		InitStatusEnemy(nEnemy);
		break;
	}
	return;
}

//=============================================================================
// �G�l�~�[�̈ړ��p�^�[��04
//=============================================================================
void SetMovePatternEnemy04(int nEnemy, int nMoveFlag)
{
	ENEMY *enemy = &enemyWk[nEnemy];

	switch (nMoveFlag)
	{
	case 0:
		SetMovePosEnemy(nEnemy, -396.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 1:
		SetMovePosEnemy(nEnemy, -396.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 2:
		SetMovePosEnemy(nEnemy, -396.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 3:
		SetMovePosEnemy(nEnemy, -396.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 4:
		SetMovePosEnemy(nEnemy, -400.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 5:
		SetMovePosEnemy(nEnemy, -500.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 6:
		SetMovePosEnemy(nEnemy, -500.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 7:
		InitStatusEnemy(nEnemy);
		break;
	}
	return;
}

//=============================================================================
// �G�l�~�[�̈ړ��p�^�[��05
//=============================================================================
void SetMovePatternEnemy05(int nEnemy, int nMoveFlag)
{
	ENEMY *enemy = &enemyWk[nEnemy];

	switch (nMoveFlag)
	{
	case 0:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 1:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 2:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 3:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 4:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 5:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 6:
		InitStatusEnemy(nEnemy);
		break;
	}
	return;
}

//=============================================================================
// �G�l�~�[�̈ړ��p�^�[��06
//=============================================================================
void SetMovePatternEnemy06(int nEnemy, int nMoveFlag)
{
	ENEMY *enemy = &enemyWk[nEnemy];

	switch (nMoveFlag)
	{
	case 0:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 1:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 2:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 3:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 4:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 5:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 6:
		InitStatusEnemy(nEnemy);
		break;
	}
	return;
}

//=============================================================================
// �G�l�~�[�̈ړ��p�^�[��07
//=============================================================================
void SetMovePatternEnemy07(int nEnemy, int nMoveFlag)
{
	ENEMY *enemy = &enemyWk[nEnemy];

	switch (nMoveFlag)
	{
	case 0:
		SetMovePosEnemy(nEnemy, -300.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 1:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 2:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 3:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 4:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 5:
		SetMovePosEnemy(nEnemy, 500.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 6:
		SetMovePosEnemy(nEnemy, 500.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 7:
		InitStatusEnemy(nEnemy);
		break;
	}
	return;
}

//=============================================================================
// �G�l�~�[�̈ړ��p�^�[��08
//=============================================================================
void SetMovePatternEnemy08(int nEnemy, int nMoveFlag)
{
	ENEMY *enemy = &enemyWk[nEnemy];

	switch (nMoveFlag)
	{
	case 0:
		SetMovePosEnemy(nEnemy, -300.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 1:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 2:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 3:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 4:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		enemy->bBulletStandby[enemy->nBulletType] = true;
		break;
	case 5:
		SetMovePosEnemy(nEnemy, 500.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 6:
		SetMovePosEnemy(nEnemy, 500.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 7:
		InitStatusEnemy(nEnemy);
		break;
	}
	return;
}

//=============================================================================
// �G�l�~�[�̈ړ��p�^�[��09 �{�X�p
//=============================================================================
void SetMovePatternEnemy09(int nEnemy, int nMoveFlag)
{

	ENEMY *enemy = &enemyWk[nEnemy];

	switch (nMoveFlag)
	{
	case 0:
		SetMovePosEnemy(nEnemy, -300.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 1:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 2:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 3:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 4:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 5:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 6:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 7:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 8:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 9:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 10:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 11:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 12:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 13:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 14:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 15:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 16:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 17:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 18:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 19:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 20:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 21:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 22:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 23:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 24:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	case 25:
		SetMovePosEnemy(nEnemy, 0.0f * SCREEN_SCALING, 0.0f * SCREEN_SCALING);
		break;
	}

	SetGameBossAction(nEnemy, nMoveFlag);

	if (enemy->fHitPoint <= BOSS_ENEMY_HPMAX / 2 && !enemy->bBossReversal)
	{
		AddScore(100000000);
		enemy->nBulletSpeedChange[BTYPE00] = BSPD_UP;
		enemy->nBulletSpeedChange[BTYPE01] = BSPD_DOWN;
		enemy->nBulletSpeedChange[BTYPE02] = BSPD_DOWN;
		enemy->nBulletSpeedChange[BTYPE03] = BSPD_DOWN;
		enemy->nBulletSpeedChange[BTYPE04] = BSPD_DOWN;
		enemy->nBulletSpeedChange[BTYPE05] = BSPD_DOWN;
		enemy->nBulletSpeedChange[BTYPE06] = BSPD_DOWN;
		enemy->nBulletSpeedChange[BTYPE07] = BSPD_DOWN;
		SetSe(13, E_DS8_FLAG_NONE, CONTINUITY_OFF);
		enemy->bBossReversal = true;
	}
	return;
}

//=============================================================================
// �G�l�~�[�̈ړ����W�ݒ�
//=============================================================================
void SetMovePosEnemy(int nEnemy, float fPosX, float fPosY)
{
	ENEMY *enemy = &enemyWk[nEnemy];

	enemy->vecDestination.x = enemy->pos.x + fPosX;
	enemy->vecDestination.y = enemy->pos.y + fPosY;

	// �ړ���~�t���O
	if (enemy->vecDestination.x <= enemy->pos.x && enemy->vecDestination.y <= enemy->pos.y)
	{
		enemy->nStopFlag = 0;
	}
	else if (enemy->vecDestination.x >= enemy->pos.x && enemy->vecDestination.y <= enemy->pos.y)
	{
		enemy->nStopFlag = 1;
	}
	else if (enemy->vecDestination.x <= enemy->pos.x && enemy->vecDestination.y >= enemy->pos.y)
	{
		enemy->nStopFlag = 2;
	}
	else if (enemy->vecDestination.x >= enemy->pos.x && enemy->vecDestination.y >= enemy->pos.y)
	{
		enemy->nStopFlag = 3;
	}
	enemy->nMoveFlag++;
	return;
}

//=============================================================================
// �G�l�~�[�̈ړ����W�ݒ�
//=============================================================================
void SetMoveCalculationEnemy(int nEnemy)
{
	ENEMY *enemy = &enemyWk[nEnemy];

	enemy->vecTa.x = enemy->vecDestination.x - enemy->pos.x;
	enemy->vecTa.y = enemy->vecDestination.y - enemy->pos.y;

	// atan2�̃G���[�h�~
	if (enemy->vecTa.x == 0 && enemy->vecTa.y == 0)
	{
		enemy->vecTa.x += 0.00001;
	}

	// �p�x�v�Z
	enemy->fAngle = atan2(enemy->vecTa.y, enemy->vecTa.x);

	//// �ˊp�ύX
	//enemy->fAngle = -1.570;

	// �ړ��ʌv�Z
	enemy->vecMove.x = cos(enemy->fAngle) * ENEMY_MOVE_SPEED;
	enemy->vecMove.y = sin(enemy->fAngle) * ENEMY_MOVE_SPEED;
	enemy->bCalculation = false;
	return;
}

//=============================================================================
// �G�l�~�[�̈ړ����W�ݒ�
//=============================================================================
void SetMoveStopEnemy(int nEnemy)
{
	ENEMY *enemy = &enemyWk[nEnemy];

	// �w����W�����ňړ���~
	switch (enemy->nStopFlag)
	{
	case 0:		// ����
		if (enemy->vecDestination.x >= enemy->pos.x && enemy->vecDestination.y >= enemy->pos.y)
		{
			SetMoveStopPosEnemy(nEnemy);
		}
		break;
	case 1:		// �E��
		if (enemy->vecDestination.x <= enemy->pos.x && enemy->vecDestination.y >= enemy->pos.y)
		{
			SetMoveStopPosEnemy(nEnemy);
		}
		break;
	case 2:		// ����
		if (enemy->vecDestination.x >= enemy->pos.x && enemy->vecDestination.y <= enemy->pos.y)
		{
			SetMoveStopPosEnemy(nEnemy);
		}
		break;
	case 3:		// �E��
		if (enemy->vecDestination.x <= enemy->pos.x && enemy->vecDestination.y <= enemy->pos.y)
		{
			SetMoveStopPosEnemy(nEnemy);
		}
		break;
	}
	return;
}

//=============================================================================
// �G�l�~�[�̃X�g�b�v���W�{�o���b�g�t���O
//=============================================================================
void SetMoveStopPosEnemy(int nEnemy)
{
	ENEMY *enemy = &enemyWk[nEnemy];

	enemy->vecMove.x = 0.0f;
	enemy->vecMove.y = 0.0f;
	if (enemy->nSpec == ENEMY_NORMAL || enemy->nSpec == ENEMY_STRONG)
	{
		if (enemy->bBulletStandby[enemy->nBulletType])
		{
			enemy->bBulletFlag[enemy->nBulletType] = true;
			enemy->bBulletStandby[enemy->nBulletType] = false;
		}
	}
	else if (enemy->nSpec == ENEMY_BOSS)
	{
		for (int i = 0; i < ENEMYBULLET_TYPE_MAX; i++)
		{
			if (enemy->bBulletStandby[i])
			{
				enemy->bBulletFlag[i] = true;
				enemy->bBulletStandby[i] = false;
			}
		}
	}
}


//=============================================================================
// �G�l�~�[�擾�֐�
//=============================================================================
ENEMY *GetEnemy(int no)
{
	return(&enemyWk[no]);
}

