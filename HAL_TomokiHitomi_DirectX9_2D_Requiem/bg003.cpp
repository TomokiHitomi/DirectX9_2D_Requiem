//=============================================================================
//
// BG003���� [bg003.cpp]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#include "main.h"
#include "bg003.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexBg003(int no);
void SetTextureBg003( int no, int cntPattern );	//
void SetVertexBg003(int no);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
BG003					bg003Wk[BG003_MAX];

// �e�N�X�`���ւ̃|���S��
LPDIRECT3DTEXTURE9		pD3DTextureBg003 = NULL;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitBg003(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BG003 *bg003 = &bg003Wk[0];

	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_BG003,				// �t�@�C���̖��O
			&pD3DTextureBg003);			// �ǂݍ��ރ������̃|�C���^
	}

	// BG003�̏�����
	for (int i = 0; i < BG003_MAX; i++, bg003++)
	{
		bg003->bUse = false;
		bg003->pos = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);
		bg003->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		bg003->nCountAnim = 0;
		bg003->nPatternAnim = 0;

		bg003->Texture = pD3DTextureBg003;			// �e�N�X�`���ւ�BG003
		bg003->size = D3DXVECTOR2(TEXTURE_BG003_SIZE_X, TEXTURE_BG003_SIZE_Y);

		// ���_���̍쐬
		MakeVertexBg003(i);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBg003(void)
{
	BG003 *bg003 = &bg003Wk[0];

	// ���������
	if (pD3DTextureBg003 != NULL)
	{
		pD3DTextureBg003->Release();
		pD3DTextureBg003 = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBg003(void)
{
	BG003 *bg003 = &bg003Wk[0];
	for (int i = 0; i < BG003_MAX; i++, bg003++)
	{
		if (bg003->bUse == true)
		{
			// �A�j���[�V����
			bg003->nCountAnim++;
			if ((bg003->nCountAnim % TIME_ANIMATION_BG003) == 0)
			{
				// �p�^�[���̐؂�ւ�
				bg003->nPatternAnim = (bg003->nPatternAnim + 1) % ANIM_PATTERN_NUM_BG003;
			}

			// �e�N�X�`�����W��ݒ�
			SetTextureBg003(i, bg003->nPatternAnim);
			// �ړ���̍��W�Œ��_��ݒ�
			SetVertexBg003(i);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBg003(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BG003 *bg003 = &bg003Wk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BG003_MAX; i++, bg003++)
	{
		if (bg003->bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, bg003->Texture);

			// BG003�̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BG003, bg003->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexBg003(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BG003 *bg003 = &bg003Wk[no];

	// ���_���W�̐ݒ�
	bg003->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	bg003->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_BG003_SIZE_X, 100.0f, 0.0f);
	bg003->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_BG003_SIZE_Y, 0.0f);
	bg003->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_BG003_SIZE_X, 100.0f+TEXTURE_BG003_SIZE_Y, 0.0f);
	//SetVertexBg003();

	// rhw�̐ݒ�
	bg003->vertexWk[0].rhw =
	bg003->vertexWk[1].rhw =
	bg003->vertexWk[2].rhw =
	bg003->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	bg003->vertexWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_BG003_R, TEXTURE_BG003_G, TEXTURE_BG003_B, 255);
	bg003->vertexWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_BG003_R, TEXTURE_BG003_G, TEXTURE_BG003_B, 255);
	bg003->vertexWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_BG003_R, TEXTURE_BG003_G, TEXTURE_BG003_B, 255);
	bg003->vertexWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_BG003_R, TEXTURE_BG003_G, TEXTURE_BG003_B, 255);

	// �e�N�X�`�����W�̐ݒ�
	bg003->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	bg003->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_BG003, 0.0f );
	bg003->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_BG003 );
	bg003->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_BG003, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_BG003 );

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureBg003( int no, int cntPattern )
{
	BG003 *bg003 = &bg003Wk[no];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_BG003;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_BG003;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_BG003;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BG003;
	bg003->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	bg003->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	bg003->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	bg003->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// ���_���W�̐ݒ�֐�
//=============================================================================
void SetVertexBg003(int no)
{
	BG003 *bg003 = &bg003Wk[no];

	bg003->vertexWk[0].vtx.x = bg003->pos.x - TEXTURE_BG003_SIZE_X;
	bg003->vertexWk[0].vtx.y = bg003->pos.y - TEXTURE_BG003_SIZE_Y;
	bg003->vertexWk[0].vtx.z = 0.0f;

	bg003->vertexWk[1].vtx.x = bg003->pos.x + TEXTURE_BG003_SIZE_X;
	bg003->vertexWk[1].vtx.y = bg003->pos.y - TEXTURE_BG003_SIZE_Y;
	bg003->vertexWk[1].vtx.z = 0.0f;

	bg003->vertexWk[2].vtx.x = bg003->pos.x - TEXTURE_BG003_SIZE_X;
	bg003->vertexWk[2].vtx.y = bg003->pos.y + TEXTURE_BG003_SIZE_Y;
	bg003->vertexWk[2].vtx.z = 0.0f;

	bg003->vertexWk[3].vtx.x = bg003->pos.x + TEXTURE_BG003_SIZE_X;
	bg003->vertexWk[3].vtx.y = bg003->pos.y + TEXTURE_BG003_SIZE_Y;
	bg003->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �A�N�e�B�u����
//=============================================================================
void SetBg003(void)
{
	BG003 *bg003 = &bg003Wk[0];

	// ���g�p����
	for (int i = 0; i < BG003_MAX; i++, bg003++)
	{
		if (!bg003->bUse)
		{
			// �L���ɂ���
			bg003->bUse = true;
			return;
		}
	}
}

//=============================================================================
// BG003�擾�֐�
//=============================================================================
BG003 *GetBg003(int no)
{
	return(&bg003Wk[no]);
}

