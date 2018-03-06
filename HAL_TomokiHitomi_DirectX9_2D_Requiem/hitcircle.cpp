//=============================================================================
//
// �v���C���[���� [hitcircle.cpp]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#include "main.h"
#include "hitcircle.h"
#include "input.h"
#include "bullet.h"
#include "sound.h"
#include "close.h"
#include "player.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexHitcircle(int no);
void SetTextureHitcircle( int no, int cntPattern );	//
void SetVertexHitcircle(int no);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
HITCIRCLE					hitcircleWk[HITCIRCLE_MAX];

// �e�N�X�`���ւ̃|���S��
LPDIRECT3DTEXTURE9		pD3DTextureHitcircle = NULL;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitHitcircle(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	HITCIRCLE *hitcircle = &hitcircleWk[0];

	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_HITCIRCLE00,				// �t�@�C���̖��O
			&pD3DTextureHitcircle);				// �ǂݍ��ރ������̃|�C���^
	}

	// �v���C���[�̏�����
	for (int i = 0; i < HITCIRCLE_MAX; i++, hitcircle++)
	{
		hitcircle->bUse = true;
		hitcircle->pos = D3DXVECTOR3(i*200.0f + 200.0f, 670.0f, 0.0f);
		hitcircle->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		hitcircle->nCountAnim = 0;
		hitcircle->nPatternAnim = 0;

		hitcircle->Texture = pD3DTextureHitcircle;			// �e�N�X�`���ւ̃G�l�~�[
		hitcircle->size = D3DXVECTOR2(HITCIRCLE_CUSTOM_SIZE_X, HITCIRCLE_CUSTOM_SIZE_Y);

		// ���_���̍쐬
		MakeVertexHitcircle(i);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitHitcircle(void)
{
	HITCIRCLE *hitcircle = &hitcircleWk[0];

	// ���������
	if (pD3DTextureHitcircle != NULL)
	{
		pD3DTextureHitcircle->Release();
		pD3DTextureHitcircle = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateHitcircle(void)
{
	HITCIRCLE *hitcircle = &hitcircleWk[0];
	PLAYER *player = GetPlayer(0);

	for (int i = 0; i < HITCIRCLE_MAX; i++, hitcircle++)
	{
		if (player->bUse)
		{
			hitcircle->bUse = true;
			// �A�j���[�V����
			hitcircle->nCountAnim++;
			if ((hitcircle->nCountAnim % TIME_ANIMATION_HITCIRCLE) == 0)
			{
				// �p�^�[���̐؂�ւ�
				hitcircle->nPatternAnim = (hitcircle->nPatternAnim + 1) % ANIM_PATTERN_NUM_HITCIRCLE;
			}

			hitcircle->pos.x = player->pos.x + HITCIRCLE_ADJUSTMENT_X;
			hitcircle->pos.y = player->pos.y + HITCIRCLE_ADJUSTMENT_Y;
		}
		else
		{
			hitcircle->bUse = false;
		}
		// �e�N�X�`�����W��ݒ�
		SetTextureHitcircle(i, hitcircle->nPatternAnim);
		// �ړ���̍��W�Œ��_��ݒ�
		SetVertexHitcircle(i);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawHitcircle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	HITCIRCLE *hitcircle = &hitcircleWk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < HITCIRCLE_MAX; i++, hitcircle++)
	{
		if (hitcircle->bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, hitcircle->Texture);

			// �v���C���[�̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_HITCIRCLE, hitcircle->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexHitcircle(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	HITCIRCLE *hitcircle = &hitcircleWk[no];

	// ���_���W�̐ݒ�
	hitcircle->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	hitcircle->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_HITCIRCLE00_SIZE_X, 100.0f, 0.0f);
	hitcircle->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_HITCIRCLE00_SIZE_Y, 0.0f);
	hitcircle->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_HITCIRCLE00_SIZE_X, 100.0f+TEXTURE_HITCIRCLE00_SIZE_Y, 0.0f);
	//SetVertexHitcircle();

	// rhw�̐ݒ�
	hitcircle->vertexWk[0].rhw =
	hitcircle->vertexWk[1].rhw =
	hitcircle->vertexWk[2].rhw =
	hitcircle->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	hitcircle->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	hitcircle->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	hitcircle->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	hitcircle->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	hitcircle->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	hitcircle->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_HITCIRCLE, 0.0f );
	hitcircle->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_HITCIRCLE );
	hitcircle->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_HITCIRCLE, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_HITCIRCLE );

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureHitcircle( int no, int cntPattern )
{
	HITCIRCLE *hitcircle = &hitcircleWk[no];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_HITCIRCLE;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_HITCIRCLE;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_HITCIRCLE;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_HITCIRCLE;
	hitcircle->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	hitcircle->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	hitcircle->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	hitcircle->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// ���_���W�̐ݒ�֐�
//=============================================================================
void SetVertexHitcircle(int no)
{
	HITCIRCLE *hitcircle = &hitcircleWk[no];

	hitcircle->vertexWk[0].vtx.x = hitcircle->pos.x - TEXTURE_HITCIRCLE00_SIZE_X;
	hitcircle->vertexWk[0].vtx.y = hitcircle->pos.y - TEXTURE_HITCIRCLE00_SIZE_Y;
	hitcircle->vertexWk[0].vtx.z = 0.0f;

	hitcircle->vertexWk[1].vtx.x = hitcircle->pos.x + TEXTURE_HITCIRCLE00_SIZE_X;
	hitcircle->vertexWk[1].vtx.y = hitcircle->pos.y - TEXTURE_HITCIRCLE00_SIZE_Y;
	hitcircle->vertexWk[1].vtx.z = 0.0f;

	hitcircle->vertexWk[2].vtx.x = hitcircle->pos.x - TEXTURE_HITCIRCLE00_SIZE_X;
	hitcircle->vertexWk[2].vtx.y = hitcircle->pos.y + TEXTURE_HITCIRCLE00_SIZE_Y;
	hitcircle->vertexWk[2].vtx.z = 0.0f;

	hitcircle->vertexWk[3].vtx.x = hitcircle->pos.x + TEXTURE_HITCIRCLE00_SIZE_X;
	hitcircle->vertexWk[3].vtx.y = hitcircle->pos.y + TEXTURE_HITCIRCLE00_SIZE_Y;
	hitcircle->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �v���C���[�擾�֐�
//=============================================================================
HITCIRCLE *GetHitcircle(int no)
{
	return(&hitcircleWk[no]);
}

