//=============================================================================
//
// �p�����[�^���� [parameterbar.cpp]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "enemy.h"
#include "parameterbar.h"
#include "parameter.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexParameterbar(int no);
void SetTextureParameterbar( int no, int cntPattern );	//
void SetVertexParameterbar(int no);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
PARAMETERBAR					parameterbarWk[PARAMETERBAR_MAX];

// �e�N�X�`���ւ̃|���S��
LPDIRECT3DTEXTURE9		pD3DTextureParameterbar = NULL;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitParameterbar(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PARAMETERBAR *parameterbar = &parameterbarWk[0];

	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_PARAMETERBAR00,				// �t�@�C���̖��O
			&pD3DTextureParameterbar);			// �ǂݍ��ރ������̃|�C���^
	}

	// �p�����[�^�̏�����
	for (int i = 0; i < PARAMETERBAR_MAX; i++, parameterbar++)
	{
		parameterbar->Texture = pD3DTextureParameterbar;			// �e�N�X�`���ւ̃G�l�~�[
		parameterbar->size = D3DXVECTOR2(TEXTURE_PARAMETERBAR00_SIZE_X, TEXTURE_PARAMETERBAR00_SIZE_Y);
		parameterbar->vecChangeSize = D3DXVECTOR3(TEXTURE_CHANGE_PARAMETERBAR_X, TEXTURE_CHANGE_PARAMETERBAR_Y, 0.0f);

		InitStatusParameterbar(i);

		// ���_���̍쐬
		MakeVertexParameterbar(i);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitParameterbar(void)
{
	PARAMETERBAR *parameterbar = &parameterbarWk[0];

	// ���������
	if (pD3DTextureParameterbar != NULL)
	{
		pD3DTextureParameterbar->Release();
		pD3DTextureParameterbar = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateParameterbar(void)
{
	PARAMETERBAR *parameterbar = &parameterbarWk[0];
	PLAYER *player;
	ENEMY *enemy;

	for (int i = 0; i < PARAMETERBAR_MAX; i++, parameterbar++)
	{
		if (parameterbar->bUse)
		{
			parameterbar->nPatternAnim = parameterbar->nType;

			switch (parameterbar->nType)
			{
			case 0:
				player = GetPlayer(parameterbar->nTarget);
				parameterbar->pos.x = player->pos.x;
				parameterbar->pos.y = player->pos.y + (float)PARAMETERBAR_DRAW_HP;
				if (!player->bUse)
				{
					InitStatusParameterbar(i);
				}
				break;
			case 1:
				player = GetPlayer(parameterbar->nTarget);
				parameterbar->pos.x = player->pos.x;
				parameterbar->pos.y = player->pos.y + (float)PARAMETERBAR_DRAW_MP;
				if (!player->bUse)
				{
					InitStatusParameterbar(i);
				}
				break;
			case 2:
				enemy = GetEnemy(parameterbar->nTarget);
				if (enemy->nSpec == ENEMY_NORMAL || enemy->nSpec == ENEMY_STRONG)
				{
					parameterbar->pos.x = enemy->pos.x;
					parameterbar->pos.y = enemy->pos.y + (float)PARAMETERBAR_DRAW_MP;
				}
				else if (enemy->nSpec == ENEMY_BOSS)
				{
					parameterbar->vecChangeSize.x = TEXTURE_CHANGE_BOSS_PARAMETERBAR_X;
					parameterbar->vecChangeSize.y = TEXTURE_CHANGE_BOSS_PARAMETERBAR_Y;
					parameterbar->pos.x = BOSS_PARAMETERBAR_POS_X;
					parameterbar->pos.y = BOSS_PARAMETERBAR_POS_Y;
				}
				if (!enemy->bUse)
				{
					InitStatusParameterbar(i);
				}
				break;
			}

			// �e�N�X�`�����W��ݒ�
			SetTextureParameterbar(i, parameterbar->nPatternAnim);
			// �ړ���̍��W�Œ��_��ݒ�
			SetVertexParameterbar(i);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawParameterbar(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PARAMETERBAR *parameterbar = &parameterbarWk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < PARAMETERBAR_MAX; i++, parameterbar++)
	{
		if (parameterbar->bUse)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, parameterbar->Texture);

			// �p�����[�^�̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_PARAMETERBAR, parameterbar->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexParameterbar(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	PARAMETERBAR *parameterbar = &parameterbarWk[no];

	// ���_���W�̐ݒ�
	parameterbar->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	parameterbar->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_PARAMETERBAR00_SIZE_X, 100.0f, 0.0f);
	parameterbar->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_PARAMETERBAR00_SIZE_Y, 0.0f);
	parameterbar->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_PARAMETERBAR00_SIZE_X, 100.0f+TEXTURE_PARAMETERBAR00_SIZE_Y, 0.0f);

	// rhw�̐ݒ�
	parameterbar->vertexWk[0].rhw =
	parameterbar->vertexWk[1].rhw =
	parameterbar->vertexWk[2].rhw =
	parameterbar->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	parameterbar->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	parameterbar->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	parameterbar->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	parameterbar->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	parameterbar->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	parameterbar->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_PARAMETERBAR, 0.0f );
	parameterbar->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_PARAMETERBAR );
	parameterbar->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_PARAMETERBAR, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_PARAMETERBAR );

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureParameterbar( int no, int cntPattern )
{
	PARAMETERBAR *parameterbar = &parameterbarWk[no];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_PARAMETERBAR;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_PARAMETERBAR;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_PARAMETERBAR;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_PARAMETERBAR;
	parameterbar->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	parameterbar->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	parameterbar->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	parameterbar->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// ���_���W�̐ݒ�֐�
//=============================================================================
void SetVertexParameterbar(int no)
{
	PARAMETERBAR *parameterbar = &parameterbarWk[no];

	parameterbar->vertexWk[0].vtx.x = parameterbar->pos.x - TEXTURE_PARAMETERBAR00_SIZE_X * parameterbar->vecChangeSize.x;
	parameterbar->vertexWk[0].vtx.y = parameterbar->pos.y - TEXTURE_PARAMETERBAR00_SIZE_Y * parameterbar->vecChangeSize.y;
	parameterbar->vertexWk[0].vtx.z = 0.0f;

	parameterbar->vertexWk[1].vtx.x = parameterbar->pos.x + TEXTURE_PARAMETERBAR00_SIZE_X * parameterbar->vecChangeSize.x;
	parameterbar->vertexWk[1].vtx.y = parameterbar->pos.y - TEXTURE_PARAMETERBAR00_SIZE_Y * parameterbar->vecChangeSize.y;
	parameterbar->vertexWk[1].vtx.z = 0.0f;

	parameterbar->vertexWk[2].vtx.x = parameterbar->pos.x - TEXTURE_PARAMETERBAR00_SIZE_X * parameterbar->vecChangeSize.x;
	parameterbar->vertexWk[2].vtx.y = parameterbar->pos.y + TEXTURE_PARAMETERBAR00_SIZE_Y * parameterbar->vecChangeSize.y;
	parameterbar->vertexWk[2].vtx.z = 0.0f;

	parameterbar->vertexWk[3].vtx.x = parameterbar->pos.x + TEXTURE_PARAMETERBAR00_SIZE_X * parameterbar->vecChangeSize.x;
	parameterbar->vertexWk[3].vtx.y = parameterbar->pos.y + TEXTURE_PARAMETERBAR00_SIZE_Y * parameterbar->vecChangeSize.y;
	parameterbar->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �p�����[�^�̃Z�b�g
//=============================================================================
void SetParameterbar(int nType, D3DXVECTOR3 vecTargetPos, int nTarget)
{
	PARAMETERBAR *parameterbar = &parameterbarWk[0];

	// ���g�p�̃p�����[�^�[��T��
	for (int i = 0; i < PARAMETERBAR_MAX; i++, parameterbar++)
	{
		if (!parameterbar->bUse)
		{
			// �p�����[�^��L���ɂ���
			parameterbar->bUse = true;
			// �p�����[�^�^�C�v��ݒ�
			parameterbar->nType = nType;
			// �p�����[�^�ݒu�Ώۂ��L��
			parameterbar->vecTargetPos = vecTargetPos;
			// �p�����[�^�^�[�Q�b�g��ݒ�
			parameterbar->nTarget = nTarget;
			return;
		}
	}
}

//=============================================================================
// �o���b�g�̍ė��p����
//=============================================================================
void InitStatusParameterbar(int nParameterbar)
{
	PARAMETERBAR *parameterbar = &parameterbarWk[nParameterbar];

	// �p�����[�^�X�e�[�^�X�̏�����
	parameterbar->bUse = false;

	parameterbar->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	parameterbar->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	parameterbar->vecTargetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	parameterbar->nCountAnim = 0;
	parameterbar->nPatternAnim = 0;
	parameterbar->nPointGauge = 0;
	parameterbar->nTarget = 0;
	parameterbar->nType = 0;

	return;
}

//=============================================================================
// �p�����[�^�擾�֐�
//=============================================================================
PARAMETERBAR *GetParameterbar(int no)
{
	return(&parameterbarWk[no]);
}

