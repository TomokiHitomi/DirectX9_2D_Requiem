//=============================================================================
//
// FADE���� [fade.cpp]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#include "main.h"
#include "fade.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexFade(int no);
void SetTextureFade( int no, int cntPattern );
void SetVertexFade(int no);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
FADE					fadeWk[FADE_MAX];

// �e�N�X�`���ւ̃|���S��
LPDIRECT3DTEXTURE9		pD3DTextureFade = NULL;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitFade(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	FADE *fade = &fadeWk[0];

	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_FADE,				// �t�@�C���̖��O
			&pD3DTextureFade);			// �ǂݍ��ރ������̃|�C���^
	}

	// FADE�̏�����
	for (int i = 0; i < FADE_MAX; i++, fade++)
	{
		fade->bUse = true;
		fade->nFadeFlag = 0;
		fade->pos = D3DXVECTOR3(i*0.0f + TEXTURE_FADE_SIZE_X, TEXTURE_FADE_SIZE_Y, 0.0f);
		fade->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		fade->nCountAnim = 0;
		fade->nPatternAnim = 0;
		fade->nAlphaCount = FADE_ALPHA_MAX;

		fade->Texture = pD3DTextureFade;			// �e�N�X�`���ւ�FADE
		fade->size = D3DXVECTOR2(TEXTURE_FADE_SIZE_X, TEXTURE_FADE_SIZE_Y);

		// ���_���̍쐬
		MakeVertexFade(i);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitFade(void)
{
	FADE *fade = &fadeWk[0];

	// ���������
	if (pD3DTextureFade != NULL)
	{
		pD3DTextureFade->Release();
		pD3DTextureFade = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateFade(void)
{
	FADE *fade = &fadeWk[0];
	for (int i = 0; i < FADE_MAX; i++, fade++)
	{
		if (fade->bUse)
		{
			// �A�j���[�V����
			fade->nCountAnim++;
			if ((fade->nCountAnim % TIME_ANIMATION_FADE) == 0)
			{
				// �p�^�[���̐؂�ւ�
				fade->nPatternAnim = (fade->nPatternAnim + 1) % ANIM_PATTERN_NUM_FADE;
			}

			switch (fade->nFadeFlag)
			{
			case 0:
				fade->nAlphaCount -= FADE_SPEED;
				if (fade->nAlphaCount <= 0)
				{
					fade->nAlphaCount = 0;
					fade->bUse = false;
				}
				break;
			case 1:
				fade->nAlphaCount += FADE_SPEED;
				if (fade->nAlphaCount > FADE_ALPHA_MAX)
				{
					fade->nAlphaCount = FADE_ALPHA_MAX;
				}
				break;
			case 2:
				fade->nAlphaCount += FADE_SPEED;
				if (fade->nAlphaCount > FADE_ALPHA_MID)
				{
					fade->nAlphaCount = FADE_ALPHA_MID;
				}
				break;
			}

			// �e�N�X�`�����W��ݒ�
			SetTextureFade(i, fade->nPatternAnim);
			// �ړ���̍��W�Œ��_��ݒ�
			SetVertexFade(i);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	FADE *fade = &fadeWk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < FADE_MAX; i++, fade++)
	{
		if (fade->bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, fade->Texture);

			// FADE�̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_FADE, fade->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexFade(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	FADE *fade = &fadeWk[no];

	// ���_���W�̐ݒ�
	fade->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	fade->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_FADE_SIZE_X, 100.0f, 0.0f);
	fade->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_FADE_SIZE_Y, 0.0f);
	fade->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_FADE_SIZE_X, 100.0f+TEXTURE_FADE_SIZE_Y, 0.0f);

	// rhw�̐ݒ�
	fade->vertexWk[0].rhw =
	fade->vertexWk[1].rhw =
	fade->vertexWk[2].rhw =
	fade->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	fade->vertexWk[0].diffuse = D3DCOLOR_RGBA(0, 0, 0, FADE_ALPHA_MAX);
	fade->vertexWk[1].diffuse = D3DCOLOR_RGBA(0, 0, 0, FADE_ALPHA_MAX);
	fade->vertexWk[2].diffuse = D3DCOLOR_RGBA(0, 0, 0, FADE_ALPHA_MAX);
	fade->vertexWk[3].diffuse = D3DCOLOR_RGBA(0, 0, 0, FADE_ALPHA_MAX);

	// �e�N�X�`�����W�̐ݒ�
	fade->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	fade->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_FADE, 0.0f );
	fade->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_FADE );
	fade->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_FADE, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_FADE );

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureFade( int no, int cntPattern )
{
	FADE *fade = &fadeWk[no];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_FADE;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_FADE;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_FADE;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_FADE;
	fade->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	fade->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	fade->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	fade->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// ���_���W�̐ݒ�֐�
//=============================================================================
void SetVertexFade(int no)
{
	FADE *fade = &fadeWk[no];

	fade->vertexWk[0].vtx.x = fade->pos.x - TEXTURE_FADE_SIZE_X;
	fade->vertexWk[0].vtx.y = fade->pos.y - TEXTURE_FADE_SIZE_Y;
	fade->vertexWk[0].vtx.z = 0.0f;

	fade->vertexWk[1].vtx.x = fade->pos.x + TEXTURE_FADE_SIZE_X;
	fade->vertexWk[1].vtx.y = fade->pos.y - TEXTURE_FADE_SIZE_Y;
	fade->vertexWk[1].vtx.z = 0.0f;

	fade->vertexWk[2].vtx.x = fade->pos.x - TEXTURE_FADE_SIZE_X;
	fade->vertexWk[2].vtx.y = fade->pos.y + TEXTURE_FADE_SIZE_Y;
	fade->vertexWk[2].vtx.z = 0.0f;

	fade->vertexWk[3].vtx.x = fade->pos.x + TEXTURE_FADE_SIZE_X;
	fade->vertexWk[3].vtx.y = fade->pos.y + TEXTURE_FADE_SIZE_Y;
	fade->vertexWk[3].vtx.z = 0.0f;

	// ���ˌ��̍X�V
	fade->vertexWk[0].diffuse = D3DCOLOR_RGBA(0, 0, 0, fade->nAlphaCount);
	fade->vertexWk[1].diffuse = D3DCOLOR_RGBA(0, 0, 0, fade->nAlphaCount);
	fade->vertexWk[2].diffuse = D3DCOLOR_RGBA(0, 0, 0, fade->nAlphaCount);
	fade->vertexWk[3].diffuse = D3DCOLOR_RGBA(0, 0, 0, fade->nAlphaCount);
}

//=============================================================================
// �t�F�[�h�ďo����
//=============================================================================
void SetFade(int nFade, int nFadeFlag)
{
	FADE *fade = &fadeWk[nFade];

	for (int i = 0; i < FADE_MAX; i++, fade++)
	{
		if (!fade->bUse)
		{
			// �t�F�[�h��L���ɂ���
			fade->bUse = true;
		}
		// �t�F�[�h�t���O���Z�b�g
		fade->nFadeFlag = nFadeFlag;
		return;
	}
}

//=============================================================================
// FADE�擾�֐�
//=============================================================================
FADE *GetFade(int no)
{
	return(&fadeWk[no]);
}

