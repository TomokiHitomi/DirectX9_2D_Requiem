//=============================================================================
//
// �G�l�~�[�o���b�g���� [enemybullet.cpp]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
//#include "main.h"
#include "enemy.h"
#include "enemybullet.h"
#include "input.h"
#include "player.h"
#include "sound.h"
#include "game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexEnemybullet(int no);
void SetTextureEnemybullet( int no, int cntPattern );
void SetVertexEnemybullet(int no);

void SetSearchPlayer(int nBullet);
void SetEnemyBulletType(int nBullet);
void SetEnemyBulletSpeedChange(int nBullet, int nBulletType);

void SetEnemyBulletType00(int nBullet);
void SetEnemyBulletType01(int nBullet);
void SetEnemyBulletType02(int nBullet);
void SetEnemyBulletType03(int nBullet);
void SetEnemyBulletType04(int nBullet);
void SetEnemyBulletType05(int nBullet);
void SetEnemyBulletType06(int nBullet);
void SetEnemyBulletType07(int nBullet);
void SetEnemyBulletType08(int nBullet);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
ENEMYBULLET				enemybulletWk[ENEMYBULLET_MAX];

// �e�N�X�`���ւ̃|���S��
LPDIRECT3DTEXTURE9		pD3DTextureEnemybullet = NULL;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEnemybullet(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMYBULLET *enemybullet = &enemybulletWk[0];

	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_ENEMYBULLET,				// �t�@�C���̖��O
			&pD3DTextureEnemybullet);			// �ǂݍ��ރ������̃|�C���^
	}

	// �G�l�~�[�o���b�g�̏�����
	for (int i = 0; i < ENEMYBULLET_MAX; i++, enemybullet++)
	{
		enemybullet->Texture = pD3DTextureEnemybullet;			// �e�N�X�`���ւ̃G�l�~�[�o���b�g
		enemybullet->size = D3DXVECTOR2(ENEMYBULLET_CUSTOM_SIZE_NORMAL_X, ENEMYBULLET_CUSTOM_SIZE_NORMAL_Y);

		enemybullet->fBaseAngle = 0.0f;
		enemybullet->fRadius = 0.0f;

		InitStatusEnemyBullet(i);
		// ���_���̍쐬
		MakeVertexEnemybullet(i);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEnemybullet(void)
{
	ENEMYBULLET *enemybullet = &enemybulletWk[0];
	// ���������
	if (pD3DTextureEnemybullet != NULL)
	{
		pD3DTextureEnemybullet->Release();
		pD3DTextureEnemybullet = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEnemybullet(void)
{
	ENEMYBULLET *enemybullet = &enemybulletWk[0];

	for (int i = 0; i < ENEMYBULLET_MAX; i++, enemybullet++)
	{
		if (enemybullet->bUse == true)
		{
			// �e�N�X�`����ݒ�
			if (enemybullet->bTextureUse == false)
			{
				enemybullet->nPatternAnim = enemybullet->nBulletTexture;
				enemybullet->bTextureUse = true;
			}

			SetEnemyBulletType(i);

			// �t�B�[���h�O�Ŗ��g�p���i��ʊO�e�������j
			if (enemybullet->pos.y < 0 - (TEXTURE_ENEMYBULLET_SIZE_Y + SCREEN_MARGIN_BULLET)
				|| enemybullet->pos.y > SCREEN_HEIGHT + (TEXTURE_ENEMYBULLET_SIZE_Y + SCREEN_MARGIN_BULLET)
				|| enemybullet->pos.x < 0 - (TEXTURE_ENEMYBULLET_SIZE_X + SCREEN_MARGIN)
				|| enemybullet->pos.x > SCREEN_WIDTH + (TEXTURE_ENEMYBULLET_SIZE_X + SCREEN_MARGIN_BULLET) )
			{
				InitStatusEnemyBullet(i);
			}
			
			// �e�N�X�`�����W��ݒ�
			SetTextureEnemybullet(i, enemybullet->nPatternAnim);
			// �ړ���̍��W�Œ��_��ݒ�
			SetVertexEnemybullet(i);
			// ��]����
			enemybullet->rot.z = enemybullet->fAngle;

			enemybullet->nBulletTime++;
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEnemybullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMYBULLET *enemybullet = &enemybulletWk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < ENEMYBULLET_MAX; i++, enemybullet++)
	{
		if (enemybullet->bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, enemybullet->Texture);

			// �G�l�~�[�o���b�g�̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_ENEMYBULLET, enemybullet->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexEnemybullet(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	ENEMYBULLET *enemybullet = &enemybulletWk[no];

	// �p�x�Ɣ��a�����߂�
	enemybullet->fBaseAngle = atan2f(TEXTURE_ENEMYBULLET_SIZE_Y, TEXTURE_ENEMYBULLET_SIZE_X);
	D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_ENEMYBULLET_SIZE_X, TEXTURE_ENEMYBULLET_SIZE_Y);
	enemybullet->fRadius = D3DXVec2Length(&temp);

	// ���_���W�̐ݒ�
	enemybullet->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	enemybullet->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_ENEMYBULLET_SIZE_X, 100.0f, 0.0f);
	enemybullet->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_ENEMYBULLET_SIZE_Y, 0.0f);
	enemybullet->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_ENEMYBULLET_SIZE_X, 100.0f+TEXTURE_ENEMYBULLET_SIZE_Y, 0.0f);
	//SetVertexEnemybullet();

	// rhw�̐ݒ�
	enemybullet->vertexWk[0].rhw =
	enemybullet->vertexWk[1].rhw =
	enemybullet->vertexWk[2].rhw =
	enemybullet->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	enemybullet->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemybullet->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemybullet->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	enemybullet->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	enemybullet->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	enemybullet->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_ENEMYBULLET, 0.0f );
	enemybullet->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_ENEMYBULLET );
	enemybullet->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_ENEMYBULLET, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_ENEMYBULLET );

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureEnemybullet( int no, int cntPattern )
{
	ENEMYBULLET *enemybullet = &enemybulletWk[no];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_ENEMYBULLET;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_ENEMYBULLET;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_ENEMYBULLET;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_ENEMYBULLET;
	enemybullet->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	enemybullet->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	enemybullet->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	enemybullet->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// ���_���W�̐ݒ�֐�
//=============================================================================
void SetVertexEnemybullet(int no)
{
	ENEMYBULLET *enemybullet = &enemybulletWk[no];
	// ���_0:��]����
	enemybullet->vertexWk[0].vtx.x = enemybullet->pos.x - cosf(enemybullet->fBaseAngle + enemybullet->rot.z) * enemybullet->fRadius;
	enemybullet->vertexWk[0].vtx.y = enemybullet->pos.y - sinf(enemybullet->fBaseAngle + enemybullet->rot.z) * enemybullet->fRadius;
	enemybullet->vertexWk[0].vtx.z = 0.0f;

	// ���_1:��]����
	enemybullet->vertexWk[1].vtx.x = enemybullet->pos.x + cosf(enemybullet->fBaseAngle - enemybullet->rot.z) * enemybullet->fRadius;
	enemybullet->vertexWk[1].vtx.y = enemybullet->pos.y - sinf(enemybullet->fBaseAngle - enemybullet->rot.z) * enemybullet->fRadius;
	enemybullet->vertexWk[1].vtx.z = 0.0f;

	// ���_2:��]����
	enemybullet->vertexWk[2].vtx.x = enemybullet->pos.x - cosf(enemybullet->fBaseAngle - enemybullet->rot.z) * enemybullet->fRadius;
	enemybullet->vertexWk[2].vtx.y = enemybullet->pos.y + sinf(enemybullet->fBaseAngle - enemybullet->rot.z) * enemybullet->fRadius;
	enemybullet->vertexWk[2].vtx.z = 0.0f;

	// ���_3:��]����
	enemybullet->vertexWk[3].vtx.x = enemybullet->pos.x + cosf(enemybullet->fBaseAngle + enemybullet->rot.z) * enemybullet->fRadius;
	enemybullet->vertexWk[3].vtx.y = enemybullet->pos.y + sinf(enemybullet->fBaseAngle + enemybullet->rot.z) * enemybullet->fRadius;
	enemybullet->vertexWk[3].vtx.z = 0.0f;
}


//=============================================================================
// �G�l�~�[�o���b�g�p�^�[��
//=============================================================================
void SetEnemyBulletType(int nBullet)
{
	ENEMYBULLET *enemybullet = &enemybulletWk[nBullet];

	switch (enemybullet->nBulletType)
	{
	case 0:
		SetEnemyBulletType00(nBullet);
		break;
	case 1:
		SetEnemyBulletType01(nBullet);
		break;
	case 2:
		SetEnemyBulletType02(nBullet);
		break;
	case 3:
		SetEnemyBulletType03(nBullet);
		break;
	case 4:
		SetEnemyBulletType04(nBullet);
		break;
	case 5:
		SetEnemyBulletType05(nBullet);
		break;
	case 6:
		SetEnemyBulletType06(nBullet);
		break;
	case 7:
		SetEnemyBulletType07(nBullet);
		break;
	case 8:
		SetEnemyBulletType08(nBullet);
		break;
	}
}

//=============================================================================
// �G�l�~�[�o���b�g���G�l�~�[�ɐݒu
//=============================================================================
void SetEnemybullet(int nEnemy, int nBulletSplit)
{
	ENEMYBULLET *enemybullet = &enemybulletWk[0];
	ENEMY *enemy = GetEnemy(nEnemy);

	int nEnemyBulletWay = enemy->nBulletSplit[BTYPE00];
	int nEnemyBulletSplit05 = enemy->nBulletSplit[BTYPE05];
	int nEnemyBulletSplit06 = enemy->nBulletSplit[BTYPE06];
	int nEnemyBulletSplit07 = enemy->nBulletSplit[BTYPE07];
	int nEnemyBulletSplit08 = enemy->nBulletSplit[BTYPE08];

	// ���g�p�̒e��T��
	for (int i = 0; i < ENEMYBULLET_MAX; i++, enemybullet++)
	{
		if (!enemybullet->bUse)
		{
			SetSe(6, E_DS8_FLAG_NONE, false);
			// �Z�b�g����G�l�~�[���L��
			enemybullet->nSetEnemy = nEnemy;
			// pos�������ɃZ�b�g
			enemybullet->pos = enemy->pos;
			// �o���b�g�^�C�v���Z�b�g
			enemybullet->nBulletType = enemy->nBulletType;
			// �o���b�g�e�N�X�`���[���Z�b�g
			enemybullet->nBulletTexture = enemy->nBulletTexture[enemy->nBulletType];

			if (enemybullet->nBulletTexture >= ENEMYBULLET_SIZE_SMALL_NUM)
			{
				enemybullet->size = D3DXVECTOR2(ENEMYBULLET_CUSTOM_SIZE_SMALL_X, ENEMYBULLET_CUSTOM_SIZE_SMALL_Y);
			}

			// ���g�p�̒e����������g�p�ɕύX
			enemybullet->bUse = true;
			// �^�[�Q�b�g���W��ݒ�
			enemybullet->vecTargetPos = enemy->vecTargetPos;
			// �����ː����J�E���g
			switch(enemy->nBulletType)
			{
			case 0:
				// �z�[�~���O�p�^�[���ݒu
				enemybullet->nPatternHoming = enemy->nBulletCount[enemy->nBulletType] % nBulletSplit;
				if (nEnemyBulletWay == 0)
				{
					return;
				}
				else
				{
					nEnemyBulletWay--;
				}
				enemy->nBulletCount[BTYPE00]++;
				break;
			case 1:
				enemy->nBulletCount[BTYPE01]++;
				return;
				break;
			case 2:
				enemy->nBulletCount[BTYPE02]++;
				return;
				break;
			case 3:
				enemy->nBulletCount[BTYPE03]++;
				return;
				break;
			case 4:
				enemy->nBulletCount[BTYPE04]++;
				return;
				break;
			case 5:
				enemybullet->nPatternHoming = enemy->nBulletCount[enemy->nBulletType] % enemy->nBulletSplit[enemy->nBulletType];
				if (nEnemyBulletSplit05 == 0)
				{
					return;
				}
				else
				{
					nEnemyBulletSplit05--;
				}
				enemy->nBulletCount[BTYPE05]++;
				break;
			case 6:
				enemybullet->nPatternHoming = enemy->nBulletCount[enemy->nBulletType] % enemy->nBulletSplit[enemy->nBulletType];
				if (nEnemyBulletSplit06 == 0)
				{
					return;
				}
				else
				{
					nEnemyBulletSplit06--;
				}
				enemy->nBulletCount[BTYPE06]++;
				break;
			case 7:
				enemybullet->nPatternHoming = enemy->nBulletCount[enemy->nBulletType] % enemy->nBulletSplit[enemy->nBulletType];
				if (nEnemyBulletSplit07 == 0)
				{
					return;
				}
				else
				{
					nEnemyBulletSplit07--;
				}
				enemy->nBulletCount[BTYPE07]++;
				break;
			case 8:
				enemybullet->vecOldEnemyPos = enemy->pos;
				enemybullet->nPatternHoming = enemy->nBulletCount[enemy->nBulletType] % enemy->nBulletSplit[enemy->nBulletType];
				if (nEnemyBulletSplit08 == 0)
				{
					return;
				}
				else
				{
					nEnemyBulletSplit08--;
				}
				enemy->nBulletCount[BTYPE08]++;
				break;
			}
		}
	}
}

//=============================================================================
// �G�l�~�[�o���b�g�̑��x�ύX
//=============================================================================
void SetEnemyBulletSpeedChange(int nBullet, int nBulletType)
{
	ENEMYBULLET *enemybullet = &enemybulletWk[nBullet];
	ENEMY *enemy = GetEnemy(enemybullet->nSetEnemy);

	// ���x�ύX
	if (enemybullet->nBulletTime >= ENEMYBULLET_SPEEDCHANGE_TIME)
	{
		switch (enemy->nBulletSpeedChange[nBulletType])
		{
		case 1:
			enemybullet->fMoveChange += ENEMYBULLET_SPEED_CHANGE;
			if (enemybullet->fMoveChange >= ENEMYBULLET_SPEED_CHANGE_MAX)
			{
				enemybullet->fMoveChange = ENEMYBULLET_SPEED_CHANGE_MAX;
			}
			break;
		case 2:
			enemybullet->fMoveChange -= ENEMYBULLET_SPEED_CHANGE;
			if (enemybullet->fMoveChange <= ENEMYBULLET_SPEED_CHANGE_MIN)
			{
				enemybullet->fMoveChange = ENEMYBULLET_SPEED_CHANGE_MIN;
			}
			break;
		default:
			break;
		}
	}
}

//=============================================================================
// �G�l�~�[�o���b�g�p�^�[��00 �m�[�}�� 1�`7WAY
//=============================================================================
void SetEnemyBulletType00(int nBullet)
{
	ENEMYBULLET *enemybullet = &enemybulletWk[nBullet];
	ENEMY *enemy = GetEnemy(enemybullet->nSetEnemy);
	PLAYER *player;

	// ���x�ύX
	SetEnemyBulletSpeedChange(nBullet, BTYPE00);

	// �v���C���[����
	SetSearchPlayer(nBullet);

	// �z�[�~���O����
	if (enemybullet->nHomingFlag == 1)
	{
		enemybullet->nHomingFlag = 2;

		enemybullet->vecTa.x = enemybullet->pos.x - enemybullet->vecTargetPos.x;
		enemybullet->vecTa.y = enemybullet->pos.y - enemybullet->vecTargetPos.y;

		// atan2�̃G���[�h�~
		if (enemybullet->vecTa.x == 0 && enemybullet->vecTa.y == 0)
		{
			enemybullet->vecTa.x += 0.00001;
		}

		// �p�x�v�Z
		enemybullet->fAngle = atan2(enemybullet->vecTa.y, enemybullet->vecTa.x);

		// �ˊp�ύX
		switch(enemybullet->nPatternHoming)
		{
		case 0:
			enemybullet->fAngle += 0.0f;
			break;
		case 1:
			enemybullet->fAngle += 0.2f;
			break;
		case 2:
			enemybullet->fAngle -= 0.2f;
			break;
		case 3:
			enemybullet->fAngle += 0.4f;
			break;
		case 4:
			enemybullet->fAngle -= 0.4f;
			break;
		case 5:
			enemybullet->fAngle += 0.6f;
			break;
		case 6:
			enemybullet->fAngle -= 0.6f;
			break;
		}


		// �ړ��ʌv�Z
		enemybullet->move.x = cos(enemybullet->fAngle) * enemy->nBulletSpeed[BTYPE00];
		enemybullet->move.y = sin(enemybullet->fAngle) * enemy->nBulletSpeed[BTYPE00];
	}
	if (enemybullet->nHomingFlag == 2)
	{
		// �ړ��ʓK�p
		enemybullet->pos.x -= enemybullet->move.x * enemybullet->fMoveChange;
		enemybullet->pos.y -= enemybullet->move.y * enemybullet->fMoveChange;
	}
}

//=============================================================================
// �G�l�~�[�o���b�g�p�^�[��01 360�x ���v���
//=============================================================================
void SetEnemyBulletType01(int nBullet)
{
	ENEMYBULLET *enemybullet = &enemybulletWk[nBullet];
	ENEMY *enemy = GetEnemy(enemybullet->nSetEnemy);
	PLAYER *player;

	// ���x�ύX
	SetEnemyBulletSpeedChange(nBullet, BTYPE01);

	// �v���C���[����
	SetSearchPlayer(nBullet);

	// �z�[�~���O����
	if (enemybullet->nHomingFlag == 1)
	{
		enemybullet->nHomingFlag = 2;

		enemybullet->vecTa.x = enemybullet->pos.x - enemybullet->vecTargetPos.x;
		enemybullet->vecTa.y = enemybullet->pos.y - enemybullet->vecTargetPos.y;

		// atan2�̃G���[�h�~
		if (enemybullet->vecTa.x == 0 && enemybullet->vecTa.y == 0)
		{
			enemybullet->vecTa.x += 0.00001;
		}

		// �p�x�v�Z
		enemybullet->fAngle = atan2(enemybullet->vecTa.y, enemybullet->vecTa.x);
		enemybullet->fAngle += ((D3DX_PI * 2.0f) / enemy->nBulletSplit[BTYPE01])
			* (enemy->nBulletCount[BTYPE01] % enemy->nBulletSplit[BTYPE01]);

		// 360�x�𒴂�����360�x������
		if (enemybullet->fAngle >= D3DX_PI * 2.0f)
		{
			enemybullet->fAngle -= D3DX_PI * 2.0f;
		}

		// �ړ��ʌv�Z
		enemybullet->move.x = cos(enemybullet->fAngle) * enemy->nBulletSpeed[BTYPE01];
		enemybullet->move.y = sin(enemybullet->fAngle) * enemy->nBulletSpeed[BTYPE01];

	}
	if (enemybullet->nHomingFlag == 2)
	{
		// �ړ��ʓK�p
		enemybullet->pos.x -= enemybullet->move.x * enemybullet->fMoveChange;
		enemybullet->pos.y -= enemybullet->move.y * enemybullet->fMoveChange;
	}
}

//=============================================================================
// �G�l�~�[�o���b�g�p�^�[��02 360�x �����v���
//=============================================================================
void SetEnemyBulletType02(int nBullet)
{
	ENEMYBULLET *enemybullet = &enemybulletWk[nBullet];
	ENEMY *enemy = GetEnemy(enemybullet->nSetEnemy);
	PLAYER *player;

	// ���x�ύX
	SetEnemyBulletSpeedChange(nBullet, BTYPE02);

	// �v���C���[����
	SetSearchPlayer(nBullet);

	// �z�[�~���O����
	if (enemybullet->nHomingFlag == 1)
	{
		enemybullet->nHomingFlag = 2;

		enemybullet->vecTa.x = enemybullet->pos.x - enemybullet->vecTargetPos.x;
		enemybullet->vecTa.y = enemybullet->pos.y - enemybullet->vecTargetPos.y;

		// atan2�̃G���[�h�~
		if (enemybullet->vecTa.x == 0 && enemybullet->vecTa.y == 0)
		{
			enemybullet->vecTa.x += 0.00001;
		}

		// �p�x�v�Z
		enemybullet->fAngle = atan2(enemybullet->vecTa.y, enemybullet->vecTa.x);
		enemybullet->fAngle -= ((D3DX_PI * 2.0f) / enemy->nBulletSplit[BTYPE02])
			* (enemy->nBulletCount[BTYPE02] % enemy->nBulletSplit[BTYPE02]);

		// 360�x�𒴂�����360�x������
		if (enemybullet->fAngle >= D3DX_PI * 2.0f)
		{
			enemybullet->fAngle -= D3DX_PI * 2.0f;
		}

		// �ړ��ʌv�Z
		enemybullet->move.x = cos(enemybullet->fAngle) * enemy->nBulletSpeed[BTYPE02];
		enemybullet->move.y = sin(enemybullet->fAngle) * enemy->nBulletSpeed[BTYPE02];

	}
	if (enemybullet->nHomingFlag == 2)
	{
		// �ړ��ʓK�p
		enemybullet->pos.x -= enemybullet->move.x * enemybullet->fMoveChange;
		enemybullet->pos.y -= enemybullet->move.y * enemybullet->fMoveChange;
	}
}

//=============================================================================
// �G�l�~�[�o���b�g�p�^�[��03 360�x ���v��� �p�x�ω�����
//=============================================================================
void SetEnemyBulletType03(int nBullet)
{
	ENEMYBULLET *enemybullet = &enemybulletWk[nBullet];
	ENEMY *enemy = GetEnemy(enemybullet->nSetEnemy);
	PLAYER *player;

	// ���x�ύX
	SetEnemyBulletSpeedChange(nBullet, BTYPE03);

	// �v���C���[����
	SetSearchPlayer(nBullet);

	// �z�[�~���O����
	if (enemybullet->nHomingFlag == 1)
	{
		enemybullet->nHomingFlag = 2;
		player = GetPlayer(enemybullet->nTarget);

		enemybullet->vecTa.x = enemybullet->pos.x - 1;
		enemybullet->vecTa.y = enemybullet->pos.y;

		// atan2�̃G���[�h�~
		if (enemybullet->vecTa.x == 0 && enemybullet->vecTa.y == 0)
		{
			enemybullet->vecTa.x += 0.00001;
		}

		// �p�x�v�Z
		enemybullet->fAngle = atan2(enemybullet->vecTa.y, enemybullet->vecTa.x);
		enemybullet->fAngle += (((D3DX_PI * 2.0f) / enemy->nBulletSplit[BTYPE03])
			*(enemy->nBulletCount[BTYPE03] % enemy->nBulletSplit[BTYPE03]))
			+ (enemy->nBulletShiftAngle*ENEMYBULLET_SHIFT03);

		if (enemy->nBulletCount[BTYPE03] % enemy->nBulletSplit[BTYPE03] == 0)
		{
			enemy->nBulletShiftAngle++;
		}

		// 360�x�𒴂�����360�x������
		if (enemybullet->fAngle >= D3DX_PI * 2.0f)
		{
			enemybullet->fAngle -= D3DX_PI * 2.0f;
		}

		// �ړ��ʌv�Z
		enemybullet->move.x = cos(enemybullet->fAngle) * enemy->nBulletSpeed[BTYPE03];
		enemybullet->move.y = sin(enemybullet->fAngle) * enemy->nBulletSpeed[BTYPE03];

	}
	if (enemybullet->nHomingFlag == 2)
	{
		// �ړ��ʓK�p
		enemybullet->pos.x -= enemybullet->move.x * enemybullet->fMoveChange;
		enemybullet->pos.y -= enemybullet->move.y * enemybullet->fMoveChange;
	}
}

//=============================================================================
// �G�l�~�[�o���b�g�p�^�[��04 360�x �����v��� �p�x�ω�����
//=============================================================================
void SetEnemyBulletType04(int nBullet)
{
	ENEMYBULLET *enemybullet = &enemybulletWk[nBullet];
	ENEMY *enemy = GetEnemy(enemybullet->nSetEnemy);
	PLAYER *player;

	// ���x�ύX
	SetEnemyBulletSpeedChange(nBullet, BTYPE04);

	// �v���C���[����
	SetSearchPlayer(nBullet);

	// �z�[�~���O����
	if (enemybullet->nHomingFlag == 1)
	{
		enemybullet->nHomingFlag = 2;

		enemybullet->vecTa.x = enemybullet->pos.x - 1;
		enemybullet->vecTa.y = enemybullet->pos.y;

		// atan2�̃G���[�h�~
		if (enemybullet->vecTa.x == 0 && enemybullet->vecTa.y == 0)
		{
			enemybullet->vecTa.x += 0.00001;
		}

		// �p�x�v�Z
		enemybullet->fAngle = atan2(enemybullet->vecTa.y, enemybullet->vecTa.x);
		enemybullet->fAngle -= (((D3DX_PI * 2.0f) / enemy->nBulletSplit[BTYPE04])
			*(enemy->nBulletCount[BTYPE04] % enemy->nBulletSplit[BTYPE04]))
			+ (enemy->nBulletShiftAngle*ENEMYBULLET_SHIFT04);

		if (enemy->nBulletCount[BTYPE04] % enemy->nBulletSplit[BTYPE04] == 0)
		{
			enemy->nBulletShiftAngle++;
		}

		// 360�x�𒴂�����360�x������
		if (enemybullet->fAngle >= D3DX_PI * 2.0f)
		{
			enemybullet->fAngle -= D3DX_PI * 2.0f;
		}

		// �ړ��ʌv�Z
		enemybullet->move.x = cos(enemybullet->fAngle) * enemy->nBulletSpeed[BTYPE04];
		enemybullet->move.y = sin(enemybullet->fAngle) * enemy->nBulletSpeed[BTYPE04];

	}
	if (enemybullet->nHomingFlag == 2)
	{
		// �ړ��ʓK�p
		enemybullet->pos.x -= enemybullet->move.x * enemybullet->fMoveChange;
		enemybullet->pos.y -= enemybullet->move.y * enemybullet->fMoveChange;
	}
}

//=============================================================================
// �G�l�~�[�o���b�g�p�^�[��05 360�x �����W�J
//=============================================================================
void SetEnemyBulletType05(int nBullet)
{
	ENEMYBULLET *enemybullet = &enemybulletWk[nBullet];
	ENEMY *enemy = GetEnemy(enemybullet->nSetEnemy);
	PLAYER *player;

	// ���x�ύX
	SetEnemyBulletSpeedChange(nBullet, BTYPE05);

	// �v���C���[����
	SetSearchPlayer(nBullet);

	// �z�[�~���O����
	if (enemybullet->nHomingFlag == 1)
	{
		enemybullet->nHomingFlag = 2;

		enemybullet->vecTa.x = enemybullet->pos.x - enemybullet->vecTargetPos.x;
		enemybullet->vecTa.y = enemybullet->pos.y - enemybullet->vecTargetPos.y;

		// atan2�̃G���[�h�~
		if (enemybullet->vecTa.x == 0 && enemybullet->vecTa.y == 0)
		{
			enemybullet->vecTa.x += 0.00001;
		}

		// �p�x�v�Z
		enemybullet->fAngle = atan2(enemybullet->vecTa.y, enemybullet->vecTa.x);
		enemybullet->fAngle += ((D3DX_PI * 2.0f) / enemy->nBulletSplit[BTYPE05]) * enemybullet->nPatternHoming;

		// 360�x�𒴂�����360�x������
		if (enemybullet->fAngle >= D3DX_PI * 2.0f)
		{
			enemybullet->fAngle -= D3DX_PI * 2.0f;
		}

		// �ړ��ʌv�Z
		enemybullet->move.x = cos(enemybullet->fAngle) * enemy->nBulletSpeed[BTYPE05];
		enemybullet->move.y = sin(enemybullet->fAngle) * enemy->nBulletSpeed[BTYPE05];

	}
	if (enemybullet->nHomingFlag == 2)
	{
		// �ړ��ʓK�p
		enemybullet->pos.x -= enemybullet->move.x * enemybullet->fMoveChange;
		enemybullet->pos.y -= enemybullet->move.y * enemybullet->fMoveChange;
	}
}

//=============================================================================
// �G�l�~�[�o���b�g�p�^�[��06 360�x �����W�J �p�x�ω�����
//=============================================================================
void SetEnemyBulletType06(int nBullet)
{
	ENEMYBULLET *enemybullet = &enemybulletWk[nBullet];
	ENEMY *enemy = GetEnemy(enemybullet->nSetEnemy);
	PLAYER *player;

	// ���x�ύX
	SetEnemyBulletSpeedChange(nBullet, BTYPE06);

	// �v���C���[����
	SetSearchPlayer(nBullet);

	// �z�[�~���O����
	if (enemybullet->nHomingFlag == 1)
	{
		enemybullet->nHomingFlag = 2;

		enemybullet->vecTa.x = enemybullet->pos.x - enemybullet->vecTargetPos.x;
		enemybullet->vecTa.y = enemybullet->pos.y - enemybullet->vecTargetPos.y;

		// atan2�̃G���[�h�~
		if (enemybullet->vecTa.x == 0 && enemybullet->vecTa.y == 0)
		{
			enemybullet->vecTa.x += 0.00001;
		}

		// �p�x�v�Z
		enemybullet->fAngle = atan2(enemybullet->vecTa.y, enemybullet->vecTa.x);

		enemybullet->fAngle += (((D3DX_PI * 2.0f) / enemy->nBulletSplit[BTYPE06]) * enemybullet->nPatternHoming)
			+ (enemy->nBulletShiftAngle * enemy->nBulletSplit[BTYPE06]);

		// 360�x�𒴂�����360�x������
		if (enemybullet->fAngle >= D3DX_PI * 2.0f)
		{
			enemybullet->fAngle -= D3DX_PI * 2.0f;
		}

		// �ړ��ʌv�Z
		enemybullet->move.x = cos(enemybullet->fAngle) * enemy->nBulletSpeed[BTYPE06];
		enemybullet->move.y = sin(enemybullet->fAngle) * enemy->nBulletSpeed[BTYPE06];

	}
	if (enemybullet->nHomingFlag == 2)
	{
		// �ړ��ʓK�p
		enemybullet->pos.x -= enemybullet->move.x * enemybullet->fMoveChange;
		enemybullet->pos.y -= enemybullet->move.y * enemybullet->fMoveChange;
	}
}

//=============================================================================
// �G�l�~�[�o���b�g�p�^�[��07 360�x �t�����W�J �p�x�ω�����
//=============================================================================
void SetEnemyBulletType07(int nBullet)
{
	ENEMYBULLET *enemybullet = &enemybulletWk[nBullet];
	ENEMY *enemy = GetEnemy(enemybullet->nSetEnemy);
	PLAYER *player;

	// ���x�ύX
	SetEnemyBulletSpeedChange(nBullet, BTYPE07);

	// �v���C���[����
	SetSearchPlayer(nBullet);

	// �z�[�~���O����
	if (enemybullet->nHomingFlag == 1)
	{
		enemybullet->nHomingFlag = 2;

		enemybullet->vecTa.x = enemybullet->pos.x - enemybullet->vecTargetPos.x;
		enemybullet->vecTa.y = enemybullet->pos.y - enemybullet->vecTargetPos.y;

		// atan2�̃G���[�h�~
		if (enemybullet->vecTa.x == 0 && enemybullet->vecTa.y == 0)
		{
			enemybullet->vecTa.x += 0.00001;
		}

		// �p�x�v�Z
		enemybullet->fAngle = atan2(enemybullet->vecTa.y, enemybullet->vecTa.x);

		enemybullet->fAngle -= (((D3DX_PI * 2.0f) / enemy->nBulletSplit[BTYPE07]) * enemybullet->nPatternHoming)
			+ (enemy->nBulletShiftAngle * enemy->nBulletSplit[BTYPE07]);

		// 360�x�𒴂�����360�x������
		if (enemybullet->fAngle >= D3DX_PI * 2.0f)
		{
			enemybullet->fAngle -= D3DX_PI * 2.0f;
		}

		// �ړ��ʌv�Z
		enemybullet->move.x = cos(enemybullet->fAngle) * enemy->nBulletSpeed[BTYPE07];
		enemybullet->move.y = sin(enemybullet->fAngle) * enemy->nBulletSpeed[BTYPE07];

	}
	if (enemybullet->nHomingFlag == 2)
	{
		// �ړ��ʓK�p
		enemybullet->pos.x -= enemybullet->move.x * enemybullet->fMoveChange;
		enemybullet->pos.y -= enemybullet->move.y * enemybullet->fMoveChange;
	}
}

//=============================================================================
// �G�l�~�[�o���b�g�p�^�[��08 360�x ��]�o���b�g
//=============================================================================
void SetEnemyBulletType08(int nBullet)
{
	ENEMYBULLET *enemybullet = &enemybulletWk[nBullet];
	ENEMY *enemy = GetEnemy(enemybullet->nSetEnemy);

	// ���x�ύX
	SetEnemyBulletSpeedChange(nBullet, BTYPE08);

	if (enemybullet->nHomingFlag == 0)
	{
		enemybullet->fAngle += ((D3DX_PI * 2.0f) / enemy->nBulletSplit[BTYPE08] * enemybullet->nPatternHoming)
			+ (enemy->nBulletShiftAngle * enemy->nBulletSplit[BTYPE08]);
		enemybullet->nHomingFlag = 1;
	}

	enemybullet->fAngle -= enemy->nBulletOption[BTYPE08];

	// 360�x�𒴂�����360�x������
	if (enemybullet->fAngle >= D3DX_PI * 2.0f)
	{
		enemybullet->fAngle -= D3DX_PI * 2.0f;
	}

	enemybullet->fDistance += enemy->nBulletSpeed[BTYPE08] * enemybullet->fMoveChange;

	// �ړ��ʓK�p
	enemybullet->pos.x = enemybullet->vecOldEnemyPos.x + (cos(enemybullet->fAngle) * enemybullet->fDistance);
	enemybullet->pos.y = enemybullet->vecOldEnemyPos.y + (sin(enemybullet->fAngle) * enemybullet->fDistance);
}

//=============================================================================
// �o���b�g�̃v���C���[����
//=============================================================================
void SetSearchPlayer(int nBullet)
{
	ENEMYBULLET *enemybullet = &enemybulletWk[nBullet];
	ENEMY *enemy;
	PLAYER *player;

	// �v���C���[����
	enemy = GetEnemy(0);
	for (int j = 0; j < ENEMY_MAX; j++, enemy++)
	{
		if (enemy->bUse)
		{
			if (enemybullet->nHomingFlag == 0)
			{
				player = GetPlayer(0);
				float fDistanceMin = 0.0f;
				for (int k = 0; k < PLAYER_MAX; k++, player++)
				{
					// �����v�Z
					D3DXVECTOR3 temp = player->pos - enemy->pos;
					float fTempLengthSq = D3DXVec3LengthSq(&temp);

					// �ŏ������Z�o
					if (fTempLengthSq < fDistanceMin || fDistanceMin == 0.0f)
					{
						fDistanceMin = fTempLengthSq;
						enemybullet->nTarget = k;
					}
					enemybullet->nHomingFlag = 1;
				}
			}
		}
	}
	return;
}

//=============================================================================
// �o���b�g�̍ė��p����
//=============================================================================
void InitStatusEnemyBullet(int nBullet)
{
	ENEMYBULLET *enemybullet = &enemybulletWk[nBullet];

	// �G�l�~�[�o���b�g�X�e�[�^�X�̏�����
	enemybullet->bUse = false;
	enemybullet->bTextureUse = false;
	enemybullet->bPatternHomingFlag = false;

	enemybullet->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ���W�f�[�^��������
	enemybullet->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	enemybullet->vecTargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	enemybullet->vecTa = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	enemybullet->move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	enemybullet->vecOldEnemyPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	enemybullet->nCountAnim = 0;
	enemybullet->nPatternAnim = 0;
	enemybullet->nPatternHoming = 0;
	enemybullet->nHomingFlag = 0;
	enemybullet->nTarget = 0;
	enemybullet->nBulletType = 0;
	enemybullet->nBulletTexture = 0;
	enemybullet->nBulletWay = 0;
	enemybullet->nBulletTime = 0;
	enemybullet->nSetEnemy = 0;
	enemybullet->nDirection = 0;

	enemybullet->fMoveChange = ENEMYBULLET_SPEED_CHENGE_DEFAULT;
	enemybullet->fDistance = 0.0f;
	enemybullet->fAngle = 0.0f;
	return;
}

//=============================================================================
// �G�l�~�[�o���b�g�擾�֐�
//=============================================================================
ENEMYBULLET *GetEnemybullet(int no)
{
	return(&enemybulletWk[no]);
}
