//=============================================================================
//
// TOTAL���� [total.cpp]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#include "main.h"
#include "total.h"
#include "totalboard.h"
#include "close.h"
#include "result.h"
#include "pressenter.h"
#include "sound.h"
#include <stdio.h>

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexTotal(void);
void SetTextureTotal(void);
void AddTotal(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pD3DTextureTotal = NULL;					// �e�N�X�`���ւ̃|���S��
VERTEX_2D				g_vertexWkTotal[TOTAL_DIGIT][NUM_VERTEX];	// ���_���i�[���[�N
D3DXVECTOR3				g_posTotal;									// �|���S���̈ړ���

int						g_nTotal;									// �X�R�A
int						g_nAddtotal;
bool					g_bTotalStop;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitTotal(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_TOTAL00,				// �t�@�C���̖��O
			&g_pD3DTextureTotal);				// �ǂݍ��ރ������̃|�C���^
	}

	g_posTotal = D3DXVECTOR3((float)TOTAL_POS_X + (float)TOTALBOARD_POS_X, (float)TOTAL_POS_Y + (float)TOTALBOARD_POS_Y, 0.0f);
	g_nTotal = 0;
	g_nAddtotal = 0;
	g_bTotalStop = false;

	// ���_���̍쐬
	MakeVertexTotal();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTotal(void)
{
	if (g_pD3DTextureTotal != NULL)
	{	// �e�N�X�`���̊J��
		g_pD3DTextureTotal->Release();
		g_pD3DTextureTotal = NULL;
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTotal(void)
{
	// �g�[�^���X�R�A
	AddTotal();

	SetTextureTotal();
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTotal(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pD3DTextureTotal);

	// �X�R�A
	for (int i = 0; i < TOTAL_DIGIT; i++)
	{
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_TOTAL, g_vertexWkTotal[i], sizeof(VERTEX_2D));
	}

}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexTotal(void)
{
	float fWidth = TEXTURE_TOTAL00_SIZE_X;	// �����̉���

	// ��������������
	for (int i = 0; i < TOTAL_DIGIT; i++)
	{
		// ���_���W�̐ݒ�
		g_vertexWkTotal[i][0].vtx.x = -fWidth * i + g_posTotal.x;
		g_vertexWkTotal[i][0].vtx.y = g_posTotal.y;
		g_vertexWkTotal[i][0].vtx.z = 0.0f;
		g_vertexWkTotal[i][1].vtx.x = -fWidth * i + g_posTotal.x + TEXTURE_TOTAL00_SIZE_X;
		g_vertexWkTotal[i][1].vtx.y = g_posTotal.y;
		g_vertexWkTotal[i][1].vtx.z = 0.0f;
		g_vertexWkTotal[i][2].vtx.x = -fWidth * i + g_posTotal.x;
		g_vertexWkTotal[i][2].vtx.y = g_posTotal.y + TEXTURE_TOTAL00_SIZE_Y;
		g_vertexWkTotal[i][2].vtx.z = 0.0f;
		g_vertexWkTotal[i][3].vtx.x = -fWidth * i + g_posTotal.x + TEXTURE_TOTAL00_SIZE_X;
		g_vertexWkTotal[i][3].vtx.y = g_posTotal.y + TEXTURE_TOTAL00_SIZE_Y;
		g_vertexWkTotal[i][3].vtx.z = 0.0f;

		// rhw�̐ݒ�
		g_vertexWkTotal[i][0].rhw =
		g_vertexWkTotal[i][1].rhw =
		g_vertexWkTotal[i][2].rhw =
		g_vertexWkTotal[i][3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		g_vertexWkTotal[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkTotal[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkTotal[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		g_vertexWkTotal[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		g_vertexWkTotal[i][0].tex = D3DXVECTOR2(0.0f, 0.0f);
		g_vertexWkTotal[i][1].tex = D3DXVECTOR2(1.0f, 0.0f);
		g_vertexWkTotal[i][2].tex = D3DXVECTOR2(0.0f, 1.0f);
		g_vertexWkTotal[i][3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	return S_OK;
}
//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetTextureTotal(void)
{
	int number = g_nTotal;

	for (int i = 0; i < TOTAL_DIGIT; i++)
	{
		// �e�N�X�`�����W�̐ݒ�
		float x = (float)(number % 10);
		g_vertexWkTotal[i][0].tex = D3DXVECTOR2(0.1f * x, 0.0f);
		g_vertexWkTotal[i][1].tex = D3DXVECTOR2(0.1f * (x + 1), 0.0f);
		g_vertexWkTotal[i][2].tex = D3DXVECTOR2(0.1f * x, 1.0f);
		g_vertexWkTotal[i][3].tex = D3DXVECTOR2(0.1f * (x + 1), 1.0f);
		number /= 10;
	}

}
//=============================================================================
// �X�R�A�̉��Z����
//=============================================================================
void AddTotal(void)
{
	PRESSENTER *pressenter = GetPressenter(0);

	if (g_nTotal <= g_nAddtotal)
	{
		g_nTotal += TOTAL_COUNT_UP;
		if (g_nTotal > g_nAddtotal)
		{
			g_nTotal = g_nAddtotal;
			pressenter->bUse = true;
		}
	}

	if (g_nTotal > TOTAL_MAX)
	{
		g_nTotal = TOTAL_MAX;
	}
	else if (g_nTotal < 0)
	{
		g_nTotal = 0;
	}

}
//=============================================================================
// �{�[�i�X�l���Z
//=============================================================================
void SetTotal(int nType,int nAdd)
{
	switch(nType)
	{
	case 0:
		g_nAddtotal += ((TOTAL_TIME_MAX - nAdd) * TOTAL_TIME_BONUS);
		break;
	case 1:
		g_nAddtotal += nAdd;
		break;
	case 2:
		g_nAddtotal += (nAdd * TOTAL_HP_BONUS);
		break;
	}
}

//=============================================================================
// �g�[�^���X�R�A�擾�֐�
//=============================================================================
int *GetTotal(void)
{
	return(&g_nTotal);
}