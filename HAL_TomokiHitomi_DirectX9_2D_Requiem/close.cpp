//=============================================================================
//
// �^�C�g������ [close.cpp]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#include "main.h"
#include "close.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "player.h"
#include "motion_result.h"
#include "bg002.h"
#include "bg003.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexClose(int no);
void SetTextureClose( int no, int cntPattern );	//
void SetVertexClose(int no);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
CLOSE					closeWk[CLOSE_MAX];
int						g_nCloseCount;
bool					g_bSeFlag;
bool					g_bVoiceFlag;

// �e�N�X�`���ւ̃|���S��
LPDIRECT3DTEXTURE9		pD3DTextureClose = NULL;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitClose(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CLOSE *close = &closeWk[0];

	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_CLOSE00,				// �t�@�C���̖��O
			&pD3DTextureClose);			// �ǂݍ��ރ������̃|�C���^
	}

	// �^�C�g���̏�����
	for (int i = 0; i < CLOSE_MAX; i++, close++)
	{
		close->bUse = false;
		close->bClearFlag = false;
		close->pos = D3DXVECTOR3(CLOSE00_POS_X, CLOSE00_POS_Y, 0.0f);
		close->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		close->nCountAnim = 0;
		close->nPatternAnim = 0;

		close->Texture = pD3DTextureClose;			// �e�N�X�`���ւ̃G�l�~�[
		close->size = D3DXVECTOR2(TEXTURE_CLOSE00_SIZE_X, TEXTURE_CLOSE00_SIZE_Y);

		// ���_���̍쐬
		MakeVertexClose(i);
	}

	g_nCloseCount = 0;
	g_bSeFlag = true;
	g_bVoiceFlag = true;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitClose(void)
{
	CLOSE *close = &closeWk[0];

	// ���������
	if (pD3DTextureClose != NULL)
	{
		pD3DTextureClose->Release();
		pD3DTextureClose = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateClose(void)
{
	CLOSE *close = &closeWk[0];
	FADE *fade = GetFade(0);

	SetBgmVol(0, false);
	SetBgmVol(1, false);
	SetBgmVol(2, false);
	SetBgmVol(3, false);
	SetBgmVol(4, false);

	for (int i = 0; i < CLOSE_MAX; i++,close++)
	{
		if (close->bUse)
		{
			if (g_bSeFlag && g_nCloseCount >= 100)
			{
				// close�T�E���h�Đ�
				SetSe(0, E_DS8_FLAG_NONE, false);
				g_bSeFlag = false;
			}

			// �A�j���[�V����
			// �p�^�[���̐؂�ւ�
			if (close->bClearFlag)
			{
				close->nPatternAnim = 0;
				if (g_bVoiceFlag && g_nCloseCount >= 50)
				{
					SetPlayerVoice(4);
					g_bVoiceFlag = false;
				}
				SetBg002();
				SetMotion_result();
			}
			else
			{
				close->nPatternAnim = 1;
				if (g_bVoiceFlag && g_nCloseCount >= 50)
				{
					SetPlayerVoice(2);
					g_bVoiceFlag = false;
				}
				SetBg003();
			}

			g_nCloseCount++;

			int nFadeCount = FADE_COMPLETE;

			if (g_nCloseCount == CLOSE_COUNTMAX - FADE_COMPLETE)
			{
				fade->nFadeFlag = 1;
				fade->bUse = true;
			}
			
			if (g_nCloseCount == CLOSE_COUNTMAX)
			{
				g_nCloseCount = 0;
				SetStage(STAGE_RESULT);
				close->bUse = false;
				g_bSeFlag = true;
				SetSe(7, E_DS8_FLAG_NONE, true);
			}

			// �e�N�X�`�����W��ݒ�
			SetTextureClose(i, close->nPatternAnim);
			// �ړ���̍��W�Œ��_��ݒ�
			SetVertexClose(i);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawClose(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CLOSE *close = &closeWk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < CLOSE_MAX; i++, close++)
	{
		if (close->bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, close->Texture);

			// �^�C�g���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_CLOSE, close->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexClose(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CLOSE *close = &closeWk[no];

	// ���_���W�̐ݒ�
	close->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	close->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_CLOSE00_SIZE_X, 100.0f, 0.0f);
	close->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_CLOSE00_SIZE_Y, 0.0f);
	close->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_CLOSE00_SIZE_X, 100.0f+TEXTURE_CLOSE00_SIZE_Y, 0.0f);
	//SetVertexClose();

	// rhw�̐ݒ�
	close->vertexWk[0].rhw =
	close->vertexWk[1].rhw =
	close->vertexWk[2].rhw =
	close->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	close->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	close->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	close->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	close->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	close->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	close->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_CLOSE, 0.0f );
	close->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_CLOSE );
	close->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_CLOSE, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_CLOSE );

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureClose( int no, int cntPattern )
{
	CLOSE *close = &closeWk[no];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_CLOSE;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_CLOSE;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_CLOSE;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_CLOSE;
	close->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	close->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	close->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	close->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// ���_���W�̐ݒ�֐�
//=============================================================================
void SetVertexClose(int no)
{
	CLOSE *close = &closeWk[no];

	close->vertexWk[0].vtx.x = close->pos.x - TEXTURE_CLOSE00_SIZE_X;
	close->vertexWk[0].vtx.y = close->pos.y - TEXTURE_CLOSE00_SIZE_Y;
	close->vertexWk[0].vtx.z = 0.0f;

	close->vertexWk[1].vtx.x = close->pos.x + TEXTURE_CLOSE00_SIZE_X;
	close->vertexWk[1].vtx.y = close->pos.y - TEXTURE_CLOSE00_SIZE_Y;
	close->vertexWk[1].vtx.z = 0.0f;

	close->vertexWk[2].vtx.x = close->pos.x - TEXTURE_CLOSE00_SIZE_X;
	close->vertexWk[2].vtx.y = close->pos.y + TEXTURE_CLOSE00_SIZE_Y;
	close->vertexWk[2].vtx.z = 0.0f;

	close->vertexWk[3].vtx.x = close->pos.x + TEXTURE_CLOSE00_SIZE_X;
	close->vertexWk[3].vtx.y = close->pos.y + TEXTURE_CLOSE00_SIZE_Y;
	close->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �^�C�g���擾�֐�
//=============================================================================
CLOSE *GetClose(int no)
{
	return(&closeWk[no]);
}

