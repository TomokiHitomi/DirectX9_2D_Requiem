//=============================================================================
//
// �p�����[�^���� [parameter.cpp]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "enemy.h"
#include "parameter.h"
#include "parameterbar.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexParameter(int no);
void SetTextureParameter( int no, int cntPattern );	//
void SetVertexParameter(int no);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
PARAMETER					parameterWk[PARAMETER_MAX];

// �e�N�X�`���ւ̃|���S��
LPDIRECT3DTEXTURE9		pD3DTextureParameter = NULL;
LPDIRECT3DTEXTURE9		pD3DTexturePlayermp = NULL;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitParameter(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PARAMETER *parameter = &parameterWk[0];

	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_PARAMETER00,				// �t�@�C���̖��O
			&pD3DTextureParameter);			// �ǂݍ��ރ������̃|�C���^
	}

	// �p�����[�^�̏�����
	for (int i = 0; i < PARAMETER_MAX; i++, parameter++)
	{
		parameter->Texture = pD3DTextureParameter;			// �e�N�X�`���ւ̃G�l�~�[
		parameter->size = D3DXVECTOR2(TEXTURE_PARAMETER00_SIZE_X, TEXTURE_PARAMETER00_SIZE_Y);
		parameter->vecChangeSize = D3DXVECTOR3(TEXTURE_CHANGE_PARAMETER_X, TEXTURE_CHANGE_PARAMETER_Y, 0.0f);

		InitStatusParameter(i);

		// ���_���̍쐬
		MakeVertexParameter(i);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitParameter(void)
{
	PARAMETER *parameter = &parameterWk[0];

	// ���������
	if (pD3DTextureParameter != NULL)
	{
		pD3DTextureParameter->Release();
		pD3DTextureParameter = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateParameter(void)
{
	PARAMETER *parameter = &parameterWk[0];
	PLAYER *player;
	ENEMY *enemy;

	for (int i = 0; i < PARAMETER_MAX; i++, parameter++)
	{
		if (parameter->bUse)
		{
			parameter->nPatternAnim = parameter->nType;
			switch (parameter->nType)
			{
			case 0:
				player = GetPlayer(parameter->nTarget);
				parameter->nPointGauge = (float)TEXTURE_PARAMETER00_SIZE_X / (float)PLAYER_HPMAX * player->fHitPoint;
				parameter->pos.x = player->pos.x - (float)TEXTURE_PARAMETER00_SIZE_X / 2;
				parameter->pos.y = player->pos.y + (float)PARAMETER_DRAW_HP;
				if (!player->bUse)
				{
					InitStatusParameter(i);
				}
				break;
			case 1:
				player = GetPlayer(parameter->nTarget);
				parameter->nPointGauge = (float)TEXTURE_PARAMETER00_SIZE_X / (float)PLAYER_MANAMAX * player->fManaPoint;
				parameter->pos.x = player->pos.x - (float)TEXTURE_PARAMETER00_SIZE_X / 2;
				parameter->pos.y = player->pos.y + (float)PARAMETER_DRAW_MP;
				if (!player->bUse)
				{
					InitStatusParameter(i);
				}
				break;
			case 2:
				enemy = GetEnemy(parameter->nTarget);
				if (enemy->nSpec == ENEMY_NORMAL)
				{
					parameter->nPointGauge = (float)TEXTURE_PARAMETER00_SIZE_X / (float)ENEMY_HPMAX * enemy->fHitPoint;
					parameter->pos.x = enemy->pos.x - (float)TEXTURE_PARAMETER00_SIZE_X / 2;
					parameter->pos.y = enemy->pos.y + (float)PARAMETER_DRAW_MP;
				}
				else if (enemy->nSpec == ENEMY_STRONG)
				{
					parameter->nPointGauge = (float)TEXTURE_PARAMETER00_SIZE_X / (float)STRONG_ENEMY_HPMAX * enemy->fHitPoint;
					parameter->pos.x = enemy->pos.x - (float)TEXTURE_PARAMETER00_SIZE_X / 2;
					parameter->pos.y = enemy->pos.y + (float)PARAMETER_DRAW_MP;
				}
				else if (enemy->nSpec == ENEMY_BOSS)
				{
					parameter->nPointGauge = (float)TEXTURE_PARAMETER00_SIZE_X / (float)BOSS_ENEMY_HPMAX * enemy->fHitPoint;
					parameter->vecChangeSize.x = TEXTURE_CHANGE_BOSS_PARAMETER_X;
					parameter->vecChangeSize.y = TEXTURE_CHANGE_BOSS_PARAMETER_Y;
					parameter->pos.x = BOSS_PARAMETER_POS_X - (float)TEXTURE_PARAMETER00_SIZE_X / 2 * TEXTURE_CHANGE_BOSS_PARAMETER_X;
					parameter->pos.y = BOSS_PARAMETER_POS_Y;
				}
				if (!enemy->bUse)
				{
					InitStatusParameter(i);
				}
				break;
			}

			// �e�N�X�`�����W��ݒ�
			SetTextureParameter(i, parameter->nPatternAnim);
			// �ړ���̍��W�Œ��_��ݒ�
			SetVertexParameter(i);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawParameter(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PARAMETER *parameter = &parameterWk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < PARAMETER_MAX; i++, parameter++)
	{
		if (parameter->bUse)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, parameter->Texture);

			// �p�����[�^�̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_PARAMETER, parameter->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexParameter(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PARAMETER *parameter = &parameterWk[no];

	// ���_���W�̐ݒ�
	parameter->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	parameter->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_PARAMETER00_SIZE_X, 100.0f, 0.0f);
	parameter->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_PARAMETER00_SIZE_Y, 0.0f);
	parameter->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_PARAMETER00_SIZE_X, 100.0f+TEXTURE_PARAMETER00_SIZE_Y, 0.0f);

	// rhw�̐ݒ�
	parameter->vertexWk[0].rhw =
	parameter->vertexWk[1].rhw =
	parameter->vertexWk[2].rhw =
	parameter->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	parameter->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	parameter->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	parameter->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	parameter->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	parameter->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	parameter->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_PARAMETER, 0.0f );
	parameter->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_PARAMETER );
	parameter->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_PARAMETER, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_PARAMETER );

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureParameter( int no, int cntPattern )
{
	PARAMETER *parameter = &parameterWk[no];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_PARAMETER;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_PARAMETER;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_PARAMETER;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_PARAMETER;
	parameter->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	parameter->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	parameter->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	parameter->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// ���_���W�̐ݒ�֐�
//=============================================================================
void SetVertexParameter(int no)
{
	PARAMETER *parameter = &parameterWk[no];

	parameter->vertexWk[0].vtx.x = parameter->pos.x;
	parameter->vertexWk[0].vtx.y = parameter->pos.y - TEXTURE_PARAMETER00_SIZE_Y * parameter->vecChangeSize.y;
	parameter->vertexWk[0].vtx.z = 0.0f;

	parameter->vertexWk[1].vtx.x = parameter->pos.x + parameter->nPointGauge * parameter->vecChangeSize.x;
	parameter->vertexWk[1].vtx.y = parameter->pos.y - TEXTURE_PARAMETER00_SIZE_Y * parameter->vecChangeSize.y;
	parameter->vertexWk[1].vtx.z = 0.0f;

	parameter->vertexWk[2].vtx.x = parameter->pos.x;
	parameter->vertexWk[2].vtx.y = parameter->pos.y + TEXTURE_PARAMETER00_SIZE_Y * parameter->vecChangeSize.y;
	parameter->vertexWk[2].vtx.z = 0.0f;

	parameter->vertexWk[3].vtx.x = parameter->pos.x + parameter->nPointGauge * parameter->vecChangeSize.x;
	parameter->vertexWk[3].vtx.y = parameter->pos.y + TEXTURE_PARAMETER00_SIZE_Y * parameter->vecChangeSize.y;
	parameter->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �p�����[�^�̃Z�b�g
//=============================================================================
void SetParameter(int nType, D3DXVECTOR3 vecTargetPos, int nTarget)
{
	PARAMETER *parameter = &parameterWk[0];

	// ���g�p�̃p�����[�^�[��T��
	for (int i = 0; i < PARAMETER_MAX; i++, parameter++)
	{
		if (!parameter->bUse)
		{
			// �p�����[�^��L���ɂ���
			parameter->bUse = true;
			// �p�����[�^�^�C�v��ݒ�
			parameter->nType = nType;
			// �p�����[�^�ݒu�Ώۂ��L��
			parameter->vecTargetPos = vecTargetPos;
			// �p�����[�^�^�[�Q�b�g��ݒ�
			parameter->nTarget = nTarget;
			// �p�����[�^�[�t���[����ݒ�
			SetParameterbar(nType, vecTargetPos, nTarget);
			// �e�N�X�`�����W��ݒ�
			SetTextureParameter(i, parameter->nPatternAnim);
			// �ړ���̍��W�Œ��_��ݒ�
			SetVertexParameter(i);
			return;
		}
	}
}

//=============================================================================
// �ė��p����
//=============================================================================
void InitStatusParameter(int nParameter)
{
	PARAMETER *parameter = &parameterWk[nParameter];

	// �p�����[�^�X�e�[�^�X�̏�����
	parameter->bUse = false;

	parameter->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	parameter->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	parameter->vecTargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	parameter->nCountAnim = 0;
	parameter->nPatternAnim = 0;
	parameter->nPointGauge = 0;
	parameter->nTarget = 0;
	parameter->nType = 0;

	return;
}

//=============================================================================
// �p�����[�^�擾�֐�
//=============================================================================
PARAMETER *GetParameter(int no)
{
	return(&parameterWk[no]);
}

