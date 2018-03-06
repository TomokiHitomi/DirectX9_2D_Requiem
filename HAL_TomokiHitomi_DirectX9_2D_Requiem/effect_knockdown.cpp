//=======================================================================Hitcircle======
//
// �v���C���[���� [effect_knockdown.cpp]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#include "main.h"
#include "effect_knockdown.h"
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
HRESULT MakeVertexEffect_knockdown(int no);
void SetTextureEffect_knockdown( int no, int cntPattern );	//
void SetVertexEffect_knockdown(int no);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
EFFECT_KNOCKDOWN					effect_knockdownWk[EFFECT_KNOCKDOWN_MAX];

// �e�N�X�`���ւ̃|���S��
LPDIRECT3DTEXTURE9		pD3DTextureEffect_knockdown = NULL;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitEffect_knockdown(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT_KNOCKDOWN *effect_knockdown = &effect_knockdownWk[0];

	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_EFFECT_KNOCKDOWN,				// �t�@�C���̖��O
			&pD3DTextureEffect_knockdown);				// �ǂݍ��ރ������̃|�C���^
	}

	// �v���C���[�̏�����
	for (int i = 0; i < EFFECT_KNOCKDOWN_MAX; i++, effect_knockdown++)
	{
		effect_knockdown->bUse = false;
		effect_knockdown->pos = D3DXVECTOR3(i*200.0f + 200.0f, 670.0f, 0.0f);
		effect_knockdown->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		effect_knockdown->nCountAnim = 0;
		effect_knockdown->nPatternAnim = 0;
		effect_knockdown->nTypeAnim = 0;
		effect_knockdown->Texture = pD3DTextureEffect_knockdown;			// �e�N�X�`���ւ̃G�l�~�[
		effect_knockdown->size = D3DXVECTOR2(TEXTURE_EFFECT_KNOCKDOWN00_SIZE_X, TEXTURE_EFFECT_KNOCKDOWN00_SIZE_Y);

		// ���_���̍쐬
		MakeVertexEffect_knockdown(i);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitEffect_knockdown(void)
{
	EFFECT_KNOCKDOWN *effect_knockdown = &effect_knockdownWk[0];

	// ���������
	if (pD3DTextureEffect_knockdown != NULL)
	{
		pD3DTextureEffect_knockdown->Release();
		pD3DTextureEffect_knockdown = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateEffect_knockdown(void)
{
	EFFECT_KNOCKDOWN *effect_knockdown = &effect_knockdownWk[0];
	PLAYER *player = GetPlayer(0);

	for (int i = 0; i < EFFECT_KNOCKDOWN_MAX; i++, effect_knockdown++)
	{
		if (effect_knockdown->bUse)
		{
			// �A�j���[�V����
			effect_knockdown->nCountAnim++;
			if ((effect_knockdown->nCountAnim % TIME_ANIMATION_EFFECT_KNOCKDOWN) == 0)
			{
				// �p�^�[���̐؂�ւ�
				effect_knockdown->nPatternAnim++;
			}

			// �A�j���[�V�����I����false
			if (effect_knockdown->nPatternAnim >= TEXTURE_PATTERN_DIVIDE_X_EFFECT_KNOCKDOWN * (effect_knockdown->nTypeAnim + 1))
			{
				effect_knockdown->bUse = false;
			}

			// �e�N�X�`�����W��ݒ�
			SetTextureEffect_knockdown(i, effect_knockdown->nPatternAnim);
			// �ړ���̍��W�Œ��_��ݒ�
			SetVertexEffect_knockdown(i);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawEffect_knockdown(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT_KNOCKDOWN *effect_knockdown = &effect_knockdownWk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < EFFECT_KNOCKDOWN_MAX; i++, effect_knockdown++)
	{
		if (effect_knockdown->bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, effect_knockdown->Texture);

			// �v���C���[�̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_EFFECT_KNOCKDOWN, effect_knockdown->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexEffect_knockdown(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	EFFECT_KNOCKDOWN *effect_knockdown = &effect_knockdownWk[no];

	// ���_���W�̐ݒ�
	effect_knockdown->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	effect_knockdown->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_EFFECT_KNOCKDOWN00_SIZE_X, 100.0f, 0.0f);
	effect_knockdown->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_EFFECT_KNOCKDOWN00_SIZE_Y, 0.0f);
	effect_knockdown->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_EFFECT_KNOCKDOWN00_SIZE_X, 100.0f+TEXTURE_EFFECT_KNOCKDOWN00_SIZE_Y, 0.0f);
	//SetVertexEffect_knockdown();

	// rhw�̐ݒ�
	effect_knockdown->vertexWk[0].rhw =
	effect_knockdown->vertexWk[1].rhw =
	effect_knockdown->vertexWk[2].rhw =
	effect_knockdown->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	effect_knockdown->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect_knockdown->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect_knockdown->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	effect_knockdown->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	effect_knockdown->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	effect_knockdown->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_EFFECT_KNOCKDOWN, 0.0f );
	effect_knockdown->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_EFFECT_KNOCKDOWN );
	effect_knockdown->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_EFFECT_KNOCKDOWN, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_EFFECT_KNOCKDOWN );

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureEffect_knockdown( int no, int cntPattern )
{
	EFFECT_KNOCKDOWN *effect_knockdown = &effect_knockdownWk[no];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_EFFECT_KNOCKDOWN;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_EFFECT_KNOCKDOWN;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_EFFECT_KNOCKDOWN;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_EFFECT_KNOCKDOWN;
	effect_knockdown->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	effect_knockdown->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	effect_knockdown->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	effect_knockdown->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// ���_���W�̐ݒ�֐�
//=============================================================================
void SetVertexEffect_knockdown(int no)
{
	EFFECT_KNOCKDOWN *effect_knockdown = &effect_knockdownWk[no];

	effect_knockdown->vertexWk[0].vtx.x = effect_knockdown->pos.x - TEXTURE_EFFECT_KNOCKDOWN00_SIZE_X;
	effect_knockdown->vertexWk[0].vtx.y = effect_knockdown->pos.y - TEXTURE_EFFECT_KNOCKDOWN00_SIZE_Y;
	effect_knockdown->vertexWk[0].vtx.z = 0.0f;

	effect_knockdown->vertexWk[1].vtx.x = effect_knockdown->pos.x + TEXTURE_EFFECT_KNOCKDOWN00_SIZE_X;
	effect_knockdown->vertexWk[1].vtx.y = effect_knockdown->pos.y - TEXTURE_EFFECT_KNOCKDOWN00_SIZE_Y;
	effect_knockdown->vertexWk[1].vtx.z = 0.0f;

	effect_knockdown->vertexWk[2].vtx.x = effect_knockdown->pos.x - TEXTURE_EFFECT_KNOCKDOWN00_SIZE_X;
	effect_knockdown->vertexWk[2].vtx.y = effect_knockdown->pos.y + TEXTURE_EFFECT_KNOCKDOWN00_SIZE_Y;
	effect_knockdown->vertexWk[2].vtx.z = 0.0f;

	effect_knockdown->vertexWk[3].vtx.x = effect_knockdown->pos.x + TEXTURE_EFFECT_KNOCKDOWN00_SIZE_X;
	effect_knockdown->vertexWk[3].vtx.y = effect_knockdown->pos.y + TEXTURE_EFFECT_KNOCKDOWN00_SIZE_Y;
	effect_knockdown->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �G�t�F�N�g�Z�b�g�擾�֐�
//=============================================================================
void SetEffect_knockdown(D3DXVECTOR3 vecPos, int nType)
{
	EFFECT_KNOCKDOWN *effect_knockdown = &effect_knockdownWk[0];

	// ���g�p����
	for (int i = 0; i < EFFECT_KNOCKDOWN_MAX; i++, effect_knockdown++)
	{
		if (!effect_knockdown->bUse)
		{
			// �L���ɂ���
			effect_knockdown->bUse = true;
			// �A�j���[�V�����J�E���^�̏�����
			effect_knockdown->nCountAnim = 0;
			// �A�j���[�V�����p�^�[���̏�����
			effect_knockdown->nPatternAnim = (TEXTURE_PATTERN_DIVIDE_X_EFFECT_KNOCKDOWN * nType);
			// �Ώۂ̃^�C�v���Z�b�g
			effect_knockdown->nTypeAnim = nType;
			// �Ώۍ��W�ɃZ�b�g
			effect_knockdown->pos.x = vecPos.x + EFFECT_KNOCKDOWN_ADJUSTMENT_X;
			effect_knockdown->pos.y = vecPos.y + EFFECT_KNOCKDOWN_ADJUSTMENT_Y;
			// �e�N�X�`�����W��ݒ�
			SetTextureEffect_knockdown(i, effect_knockdown->nPatternAnim);
			// �ړ���̍��W�Œ��_��ݒ�
			SetVertexEffect_knockdown(i);
			return;
		}
	}
}

//=============================================================================
// �G�t�F�N�g�擾�֐�
//=============================================================================
EFFECT_KNOCKDOWN *GetEffect_knockdown(int no)
{
	return(&effect_knockdownWk[no]);
}

