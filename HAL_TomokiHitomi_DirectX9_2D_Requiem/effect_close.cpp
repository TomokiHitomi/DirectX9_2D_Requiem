//=======================================================================Hitcircle======
//
// �v���C���[���� [effect_close.cpp]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#include "main.h"
#include "effect_close.h"
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
HRESULT MakeVertexEffect_close(int no);
void SetTextureEffect_close( int no, int cntPattern );	//
void SetVertexEffect_close(int no);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
EFFECT_CLOSE					effect_closeWk[EFFECT_CLOSE_MAX];

// �e�N�X�`���ւ̃|���S��
LPDIRECT3DTEXTURE9		pD3DTextureEffect_close = NULL;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEffect_close(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT_CLOSE *effect_close = &effect_closeWk[0];

	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_EFFECT_CLOSE,				// �t�@�C���̖��O
			&pD3DTextureEffect_close);				// �ǂݍ��ރ������̃|�C���^
	}

	// �v���C���[�̏�����
	for (int i = 0; i < EFFECT_CLOSE_MAX; i++, effect_close++)
	{
		effect_close->bUse = false;
		effect_close->pos = D3DXVECTOR3((float)EFFECT_CLOSE_POS_X, (float)EFFECT_CLOSE_POS_Y, 0.0f);
		effect_close->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		effect_close->nCountAnim = 0;
		effect_close->nPatternAnim = 0;
		effect_close->Texture = pD3DTextureEffect_close;			// �e�N�X�`���ւ̃G�l�~�[
		effect_close->size = D3DXVECTOR2(TEXTURE_EFFECT_CLOSE00_SIZE_X, TEXTURE_EFFECT_CLOSE00_SIZE_Y);

		// ���_���̍쐬
		MakeVertexEffect_close(i);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEffect_close(void)
{
	EFFECT_CLOSE *effect_close = &effect_closeWk[0];

	// ���������
	if (pD3DTextureEffect_close != NULL)
	{
		pD3DTextureEffect_close->Release();
		pD3DTextureEffect_close = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEffect_close(void)
{
	EFFECT_CLOSE *effect_close = &effect_closeWk[0];
	PLAYER *player = GetPlayer(0);

	for (int i = 0; i < EFFECT_CLOSE_MAX; i++, effect_close++)
	{
		if (effect_close->bUse)
		{
			// �A�j���[�V����
			effect_close->nCountAnim++;
			if ((effect_close->nCountAnim % TIME_ANIMATION_EFFECT_CLOSE) == 0)
			{
				// �p�^�[���̐؂�ւ�
				effect_close->nPatternAnim = (effect_close->nPatternAnim + 1) % ANIM_PATTERN_NUM_EFFECT_CLOSE;
				if (effect_close->nPatternAnim == EFFECT_CLOSE_SKIPANIME00 || effect_close->nPatternAnim == EFFECT_CLOSE_SKIPANIME14)
				{
					effect_close->nPatternAnim = 1;
				}
			}

			//if (effect_close->nCountAnim >= ANIM_PATTERN_NUM_EFFECT_CLOSE * TIME_ANIMATION_EFFECT_CLOSE)
			//{
			//	effect_close->bUse = false;
			//}

			// �e�N�X�`�����W��ݒ�
			SetTextureEffect_close(i, effect_close->nPatternAnim);
			// �ړ���̍��W�Œ��_��ݒ�
			SetVertexEffect_close(i);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEffect_close(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT_CLOSE *effect_close = &effect_closeWk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < EFFECT_CLOSE_MAX; i++, effect_close++)
	{
		if (effect_close->bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, effect_close->Texture);

			// �v���C���[�̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_EFFECT_CLOSE, effect_close->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexEffect_close(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT_CLOSE *effect_close = &effect_closeWk[no];

	// ���_���W�̐ݒ�
	effect_close->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	effect_close->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_EFFECT_CLOSE00_SIZE_X, 100.0f, 0.0f);
	effect_close->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_EFFECT_CLOSE00_SIZE_Y, 0.0f);
	effect_close->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_EFFECT_CLOSE00_SIZE_X, 100.0f+TEXTURE_EFFECT_CLOSE00_SIZE_Y, 0.0f);
	//SetVertexEffect_close();

	// rhw�̐ݒ�
	effect_close->vertexWk[0].rhw =
	effect_close->vertexWk[1].rhw =
	effect_close->vertexWk[2].rhw =
	effect_close->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	effect_close->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect_close->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect_close->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect_close->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	effect_close->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	effect_close->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_EFFECT_CLOSE, 0.0f );
	effect_close->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_EFFECT_CLOSE );
	effect_close->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_EFFECT_CLOSE, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_EFFECT_CLOSE );

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureEffect_close( int no, int cntPattern )
{
	EFFECT_CLOSE *effect_close = &effect_closeWk[no];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_EFFECT_CLOSE;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_EFFECT_CLOSE;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_EFFECT_CLOSE;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EFFECT_CLOSE;
	effect_close->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	effect_close->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	effect_close->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	effect_close->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// ���_���W�̐ݒ�֐�
//=============================================================================
void SetVertexEffect_close(int no)
{
	EFFECT_CLOSE *effect_close = &effect_closeWk[no];

	effect_close->vertexWk[0].vtx.x = effect_close->pos.x - TEXTURE_EFFECT_CLOSE00_SIZE_X;
	effect_close->vertexWk[0].vtx.y = effect_close->pos.y - TEXTURE_EFFECT_CLOSE00_SIZE_Y;
	effect_close->vertexWk[0].vtx.z = 0.0f;

	effect_close->vertexWk[1].vtx.x = effect_close->pos.x + TEXTURE_EFFECT_CLOSE00_SIZE_X;
	effect_close->vertexWk[1].vtx.y = effect_close->pos.y - TEXTURE_EFFECT_CLOSE00_SIZE_Y;
	effect_close->vertexWk[1].vtx.z = 0.0f;

	effect_close->vertexWk[2].vtx.x = effect_close->pos.x - TEXTURE_EFFECT_CLOSE00_SIZE_X;
	effect_close->vertexWk[2].vtx.y = effect_close->pos.y + TEXTURE_EFFECT_CLOSE00_SIZE_Y;
	effect_close->vertexWk[2].vtx.z = 0.0f;

	effect_close->vertexWk[3].vtx.x = effect_close->pos.x + TEXTURE_EFFECT_CLOSE00_SIZE_X;
	effect_close->vertexWk[3].vtx.y = effect_close->pos.y + TEXTURE_EFFECT_CLOSE00_SIZE_Y;
	effect_close->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �v���C���[�擾�֐�
//=============================================================================
void SetEffect_close(void)
{
	EFFECT_CLOSE *effect_close = &effect_closeWk[0];

	// ���g�p����
	for (int i = 0; i < EFFECT_CLOSE_MAX; i++, effect_close++)
	{
		if (!effect_close->bUse)
		{
			// �L���ɂ���
			effect_close->bUse = true;
			// �A�j���[�V�����J�E���^�̏�����
			effect_close->nCountAnim = 0;
			// �A�j���[�V�����p�^�[���̏�����
			effect_close->nPatternAnim = 0;
			return;
		}
	}
}

//=============================================================================
// �v���C���[�擾�֐�
//=============================================================================
EFFECT_CLOSE *GetEffect_close(int no)
{
	return(&effect_closeWk[no]);
}

