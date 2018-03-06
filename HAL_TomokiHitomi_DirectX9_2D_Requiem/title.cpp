//=============================================================================
//
// �^�C�g������ [title.cpp]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#include "main.h"
#include "title.h"
#include "input.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexTitle(int no);
void SetTextureTitle( int no, int cntPattern );	//
void SetVertexTitle(int no);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
TITLE					titleWk[TITLE_MAX];

// �e�N�X�`���ւ̃|���S��
LPDIRECT3DTEXTURE9		pD3DTextureTitle = NULL;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitTitle(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TITLE *title = &titleWk[0];

	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_TITLE00,				// �t�@�C���̖��O
			&pD3DTextureTitle);			// �ǂݍ��ރ������̃|�C���^
	}

	// �^�C�g���̏�����
	for (int i = 0; i < TITLE_MAX; i++, title++)
	{
		title->bUse = true;
		title->pos = D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y, 0.0f);
		title->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		title->nCountAnim = 0;
		title->nPatternAnim = 0;

		title->Texture = pD3DTextureTitle;			// �e�N�X�`���ւ̃G�l�~�[
		title->size = D3DXVECTOR2(TEXTURE_TITLE00_SIZE_X, TEXTURE_TITLE00_SIZE_Y);

		// ���_���̍쐬
		MakeVertexTitle(i);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTitle(void)
{
	TITLE *title = &titleWk[0];

	// ���������
	if (pD3DTextureTitle != NULL)
	{
		pD3DTextureTitle->Release();
		pD3DTextureTitle = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTitle(void)
{
	TITLE *title = &titleWk[0];

	SetBgmVol(0, true);
	SetBgmVol(1, false);
	SetBgmVol(2, false);
	SetBgmVol(3, false);
	SetBgmVol(4, false);

	for (int i = 0; i < TITLE_MAX; i++, title++)
	{
		if (title->bUse == true)
		{
			// �A�j���[�V����
			title->nCountAnim++;
			if ((title->nCountAnim % TIME_ANIMATION_TITLE) == 0)
			{
				// �p�^�[���̐؂�ւ�
				title->nPatternAnim = (title->nPatternAnim + 1) % ANIM_PATTERN_NUM_TITLE;
			}

			// �e�N�X�`�����W��ݒ�
			SetTextureTitle(i, title->nPatternAnim);
			// �ړ���̍��W�Œ��_��ݒ�
			SetVertexTitle(i);

		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TITLE *title = &titleWk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < TITLE_MAX; i++, title++)
	{
		if (title->bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, title->Texture);

			// �^�C�g���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_TITLE, title->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexTitle(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TITLE *title = &titleWk[no];

	// ���_���W�̐ݒ�
	title->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	title->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_TITLE00_SIZE_X, 100.0f, 0.0f);
	title->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_TITLE00_SIZE_Y, 0.0f);
	title->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_TITLE00_SIZE_X, 100.0f+TEXTURE_TITLE00_SIZE_Y, 0.0f);
	//SetVertexTitle();

	// rhw�̐ݒ�
	title->vertexWk[0].rhw =
	title->vertexWk[1].rhw =
	title->vertexWk[2].rhw =
	title->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	title->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	title->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	title->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	title->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	title->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	title->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_TITLE, 0.0f );
	title->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_TITLE );
	title->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_TITLE, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_TITLE );

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureTitle( int no, int cntPattern )
{
	TITLE *title = &titleWk[no];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_TITLE;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_TITLE;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_TITLE;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_TITLE;
	title->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	title->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	title->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	title->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// ���_���W�̐ݒ�֐�
//=============================================================================
void SetVertexTitle(int no)
{
	TITLE *title = &titleWk[no];

	title->vertexWk[0].vtx.x = title->pos.x - TEXTURE_TITLE00_SIZE_X;
	title->vertexWk[0].vtx.y = title->pos.y - TEXTURE_TITLE00_SIZE_Y;
	title->vertexWk[0].vtx.z = 0.0f;

	title->vertexWk[1].vtx.x = title->pos.x + TEXTURE_TITLE00_SIZE_X;
	title->vertexWk[1].vtx.y = title->pos.y - TEXTURE_TITLE00_SIZE_Y;
	title->vertexWk[1].vtx.z = 0.0f;

	title->vertexWk[2].vtx.x = title->pos.x - TEXTURE_TITLE00_SIZE_X;
	title->vertexWk[2].vtx.y = title->pos.y + TEXTURE_TITLE00_SIZE_Y;
	title->vertexWk[2].vtx.z = 0.0f;

	title->vertexWk[3].vtx.x = title->pos.x + TEXTURE_TITLE00_SIZE_X;
	title->vertexWk[3].vtx.y = title->pos.y + TEXTURE_TITLE00_SIZE_Y;
	title->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �^�C�g���擾�֐�
//=============================================================================
TITLE *GetTitle(int no)
{
	return(&titleWk[no]);
}

