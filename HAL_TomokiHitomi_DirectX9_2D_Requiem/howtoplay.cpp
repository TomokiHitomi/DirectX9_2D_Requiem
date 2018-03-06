//=============================================================================
//
// HOWTOPLAY���� [howtoplay.cpp]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "howtoplay.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexHowtoplay(int no);
void SetTextureHowtoplay( int no, int cntPattern );	//
void SetVertexHowtoplay(int no);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
HOWTOPLAY					howtoplayWk[HOWTOPLAY_MAX];

// �e�N�X�`���ւ̃|���S��
LPDIRECT3DTEXTURE9		pD3DTextureHowtoplay = NULL;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitHowtoplay(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	HOWTOPLAY *howtoplay = &howtoplayWk[0];

	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_HOWTOPLAY,				// �t�@�C���̖��O
			&pD3DTextureHowtoplay);			// �ǂݍ��ރ������̃|�C���^
	}

	// HOWTOPLAY�̏�����
	for (int i = 0; i < HOWTOPLAY_MAX; i++, howtoplay++)
	{
		howtoplay->bUse = true;
		howtoplay->pos = D3DXVECTOR3((float)HOWTOPLAY_POS_X, (float)HOWTOPLAY_POS_Y, 0.0f);
		howtoplay->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		howtoplay->nCountAnim = 0;
		howtoplay->nPatternAnim = 0;

		howtoplay->Texture = pD3DTextureHowtoplay;			// �e�N�X�`���ւ�HOWTOPLAY
		howtoplay->size = D3DXVECTOR2(TEXTURE_HOWTOPLAY_SIZE_X, TEXTURE_HOWTOPLAY_SIZE_Y);

		// ���_���̍쐬
		MakeVertexHowtoplay(i);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitHowtoplay(void)
{
	HOWTOPLAY *howtoplay = &howtoplayWk[0];

	// ���������
	if (pD3DTextureHowtoplay != NULL)
	{
		pD3DTextureHowtoplay->Release();
		pD3DTextureHowtoplay = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateHowtoplay(void)
{
	HOWTOPLAY *howtoplay = &howtoplayWk[0];
	for (int i = 0; i < HOWTOPLAY_MAX; i++, howtoplay++)
	{
		if (howtoplay->bUse == true)
		{
			// �e�N�X�`�����W��ݒ�
			SetTextureHowtoplay(i, howtoplay->nPatternAnim);
			// �ړ���̍��W�Œ��_��ݒ�
			SetVertexHowtoplay(i);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawHowtoplay(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	HOWTOPLAY *howtoplay = &howtoplayWk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < HOWTOPLAY_MAX; i++, howtoplay++)
	{
		if (howtoplay->bUse)
		{
			// How to play�y�[�W�؂�ւ�
			if (GetKeyboardTrigger(DIK_P) || IsButtonTriggered(0, BUTTON_C))
			{
				if (howtoplay->nPatternAnim)
				{
					howtoplay->nPatternAnim = 0;
				}
				else
				{
					howtoplay->nPatternAnim = 1;
				}
			}
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, howtoplay->Texture);

			// HOWTOPLAY�̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_HOWTOPLAY, howtoplay->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexHowtoplay(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	HOWTOPLAY *howtoplay = &howtoplayWk[no];

	// ���_���W�̐ݒ�
	howtoplay->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	howtoplay->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_HOWTOPLAY_SIZE_X, 100.0f, 0.0f);
	howtoplay->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_HOWTOPLAY_SIZE_Y, 0.0f);
	howtoplay->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_HOWTOPLAY_SIZE_X, 100.0f+TEXTURE_HOWTOPLAY_SIZE_Y, 0.0f);
	//SetVertexHowtoplay();

	// rhw�̐ݒ�
	howtoplay->vertexWk[0].rhw =
	howtoplay->vertexWk[1].rhw =
	howtoplay->vertexWk[2].rhw =
	howtoplay->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	howtoplay->vertexWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_HOWTOPLAY_R, TEXTURE_HOWTOPLAY_G, TEXTURE_HOWTOPLAY_B, 255);
	howtoplay->vertexWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_HOWTOPLAY_R, TEXTURE_HOWTOPLAY_G, TEXTURE_HOWTOPLAY_B, 255);
	howtoplay->vertexWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_HOWTOPLAY_R, TEXTURE_HOWTOPLAY_G, TEXTURE_HOWTOPLAY_B, 255);
	howtoplay->vertexWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_HOWTOPLAY_R, TEXTURE_HOWTOPLAY_G, TEXTURE_HOWTOPLAY_B, 255);

	// �e�N�X�`�����W�̐ݒ�
	howtoplay->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	howtoplay->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_HOWTOPLAY, 0.0f );
	howtoplay->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_HOWTOPLAY );
	howtoplay->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_HOWTOPLAY, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_HOWTOPLAY );

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureHowtoplay( int no, int cntPattern )
{
	HOWTOPLAY *howtoplay = &howtoplayWk[no];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_HOWTOPLAY;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_HOWTOPLAY;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_HOWTOPLAY;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_HOWTOPLAY;
	howtoplay->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	howtoplay->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	howtoplay->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	howtoplay->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// ���_���W�̐ݒ�֐�
//=============================================================================
void SetVertexHowtoplay(int no)
{
	HOWTOPLAY *howtoplay = &howtoplayWk[no];

	howtoplay->vertexWk[0].vtx.x = howtoplay->pos.x - TEXTURE_HOWTOPLAY_SIZE_X;
	howtoplay->vertexWk[0].vtx.y = howtoplay->pos.y - TEXTURE_HOWTOPLAY_SIZE_Y;
	howtoplay->vertexWk[0].vtx.z = 0.0f;

	howtoplay->vertexWk[1].vtx.x = howtoplay->pos.x + TEXTURE_HOWTOPLAY_SIZE_X;
	howtoplay->vertexWk[1].vtx.y = howtoplay->pos.y - TEXTURE_HOWTOPLAY_SIZE_Y;
	howtoplay->vertexWk[1].vtx.z = 0.0f;

	howtoplay->vertexWk[2].vtx.x = howtoplay->pos.x - TEXTURE_HOWTOPLAY_SIZE_X;
	howtoplay->vertexWk[2].vtx.y = howtoplay->pos.y + TEXTURE_HOWTOPLAY_SIZE_Y;
	howtoplay->vertexWk[2].vtx.z = 0.0f;

	howtoplay->vertexWk[3].vtx.x = howtoplay->pos.x + TEXTURE_HOWTOPLAY_SIZE_X;
	howtoplay->vertexWk[3].vtx.y = howtoplay->pos.y + TEXTURE_HOWTOPLAY_SIZE_Y;
	howtoplay->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// HOWTOPLAY�擾�֐�
//=============================================================================
HOWTOPLAY *GetHowtoplay(int no)
{
	return(&howtoplayWk[no]);
}

