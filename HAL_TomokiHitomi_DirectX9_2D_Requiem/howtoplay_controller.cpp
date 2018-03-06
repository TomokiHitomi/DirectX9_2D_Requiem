//=============================================================================
//
// HOWTOPLAY_CONTROLLER���� [howtoplay_controller.cpp]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "howtoplay_controller.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexHowtoplay_controller(int no);
void SetTextureHowtoplay_controller( int no, int cntPattern );	//
void SetVertexHowtoplay_controller(int no);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
HOWTOPLAY_CONTROLLER					howtoplay_controllerWk[HOWTOPLAY_CONTROLLER_MAX];

// �e�N�X�`���ւ̃|���S��
LPDIRECT3DTEXTURE9		pD3DTextureHowtoplay_controller = NULL;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitHowtoplay_controller(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	HOWTOPLAY_CONTROLLER *howtoplay_controller = &howtoplay_controllerWk[0];

	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_HOWTOPLAY_CONTROLLER,				// �t�@�C���̖��O
			&pD3DTextureHowtoplay_controller);			// �ǂݍ��ރ������̃|�C���^
	}

	// HOWTOPLAY_CONTROLLER�̏�����
	for (int i = 0; i < HOWTOPLAY_CONTROLLER_MAX; i++, howtoplay_controller++)
	{
		howtoplay_controller->bUse = true;
		howtoplay_controller->pos = D3DXVECTOR3((float)HOWTOPLAY_CONTROLLER_POS_X, (float)HOWTOPLAY_CONTROLLER_POS_Y, 0.0f);
		howtoplay_controller->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		howtoplay_controller->nCountAnim = 0;
		howtoplay_controller->nPatternAnim = 0;

		howtoplay_controller->Texture = pD3DTextureHowtoplay_controller;			// �e�N�X�`���ւ�HOWTOPLAY_CONTROLLER
		howtoplay_controller->size = D3DXVECTOR2(TEXTURE_HOWTOPLAY_CONTROLLER_SIZE_X, TEXTURE_HOWTOPLAY_CONTROLLER_SIZE_Y);

		// ���_���̍쐬
		MakeVertexHowtoplay_controller(i);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitHowtoplay_controller(void)
{
	HOWTOPLAY_CONTROLLER *howtoplay_controller = &howtoplay_controllerWk[0];

	// ���������
	if (pD3DTextureHowtoplay_controller != NULL)
	{
		pD3DTextureHowtoplay_controller->Release();
		pD3DTextureHowtoplay_controller = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateHowtoplay_controller(void)
{
	HOWTOPLAY_CONTROLLER *howtoplay_controller = &howtoplay_controllerWk[0];
	for (int i = 0; i < HOWTOPLAY_CONTROLLER_MAX; i++, howtoplay_controller++)
	{
		if (howtoplay_controller->bUse == true)
		{
			// �e�N�X�`�����W��ݒ�
			SetTextureHowtoplay_controller(i, howtoplay_controller->nPatternAnim);
			// �ړ���̍��W�Œ��_��ݒ�
			SetVertexHowtoplay_controller(i);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawHowtoplay_controller(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	HOWTOPLAY_CONTROLLER *howtoplay_controller = &howtoplay_controllerWk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < HOWTOPLAY_CONTROLLER_MAX; i++, howtoplay_controller++)
	{
		if (howtoplay_controller->bUse)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, howtoplay_controller->Texture);

			// HOWTOPLAY_CONTROLLER�̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_HOWTOPLAY_CONTROLLER, howtoplay_controller->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexHowtoplay_controller(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	HOWTOPLAY_CONTROLLER *howtoplay_controller = &howtoplay_controllerWk[no];

	// ���_���W�̐ݒ�
	howtoplay_controller->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	howtoplay_controller->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_HOWTOPLAY_CONTROLLER_SIZE_X, 100.0f, 0.0f);
	howtoplay_controller->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_HOWTOPLAY_CONTROLLER_SIZE_Y, 0.0f);
	howtoplay_controller->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_HOWTOPLAY_CONTROLLER_SIZE_X, 100.0f+TEXTURE_HOWTOPLAY_CONTROLLER_SIZE_Y, 0.0f);
	//SetVertexHowtoplay_controller();

	// rhw�̐ݒ�
	howtoplay_controller->vertexWk[0].rhw =
	howtoplay_controller->vertexWk[1].rhw =
	howtoplay_controller->vertexWk[2].rhw =
	howtoplay_controller->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	howtoplay_controller->vertexWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_HOWTOPLAY_CONTROLLER_R, TEXTURE_HOWTOPLAY_CONTROLLER_G, TEXTURE_HOWTOPLAY_CONTROLLER_B, 255);
	howtoplay_controller->vertexWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_HOWTOPLAY_CONTROLLER_R, TEXTURE_HOWTOPLAY_CONTROLLER_G, TEXTURE_HOWTOPLAY_CONTROLLER_B, 255);
	howtoplay_controller->vertexWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_HOWTOPLAY_CONTROLLER_R, TEXTURE_HOWTOPLAY_CONTROLLER_G, TEXTURE_HOWTOPLAY_CONTROLLER_B, 255);
	howtoplay_controller->vertexWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_HOWTOPLAY_CONTROLLER_R, TEXTURE_HOWTOPLAY_CONTROLLER_G, TEXTURE_HOWTOPLAY_CONTROLLER_B, 255);

	// �e�N�X�`�����W�̐ݒ�
	howtoplay_controller->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	howtoplay_controller->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_HOWTOPLAY_CONTROLLER, 0.0f );
	howtoplay_controller->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_HOWTOPLAY_CONTROLLER );
	howtoplay_controller->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_HOWTOPLAY_CONTROLLER, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_HOWTOPLAY_CONTROLLER );

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureHowtoplay_controller( int no, int cntPattern )
{
	HOWTOPLAY_CONTROLLER *howtoplay_controller = &howtoplay_controllerWk[no];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_HOWTOPLAY_CONTROLLER;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_HOWTOPLAY_CONTROLLER;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_HOWTOPLAY_CONTROLLER;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_HOWTOPLAY_CONTROLLER;
	howtoplay_controller->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	howtoplay_controller->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	howtoplay_controller->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	howtoplay_controller->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// ���_���W�̐ݒ�֐�
//=============================================================================
void SetVertexHowtoplay_controller(int no)
{
	HOWTOPLAY_CONTROLLER *howtoplay_controller = &howtoplay_controllerWk[no];

	howtoplay_controller->vertexWk[0].vtx.x = howtoplay_controller->pos.x - TEXTURE_HOWTOPLAY_CONTROLLER_SIZE_X;
	howtoplay_controller->vertexWk[0].vtx.y = howtoplay_controller->pos.y - TEXTURE_HOWTOPLAY_CONTROLLER_SIZE_Y;
	howtoplay_controller->vertexWk[0].vtx.z = 0.0f;

	howtoplay_controller->vertexWk[1].vtx.x = howtoplay_controller->pos.x + TEXTURE_HOWTOPLAY_CONTROLLER_SIZE_X;
	howtoplay_controller->vertexWk[1].vtx.y = howtoplay_controller->pos.y - TEXTURE_HOWTOPLAY_CONTROLLER_SIZE_Y;
	howtoplay_controller->vertexWk[1].vtx.z = 0.0f;

	howtoplay_controller->vertexWk[2].vtx.x = howtoplay_controller->pos.x - TEXTURE_HOWTOPLAY_CONTROLLER_SIZE_X;
	howtoplay_controller->vertexWk[2].vtx.y = howtoplay_controller->pos.y + TEXTURE_HOWTOPLAY_CONTROLLER_SIZE_Y;
	howtoplay_controller->vertexWk[2].vtx.z = 0.0f;

	howtoplay_controller->vertexWk[3].vtx.x = howtoplay_controller->pos.x + TEXTURE_HOWTOPLAY_CONTROLLER_SIZE_X;
	howtoplay_controller->vertexWk[3].vtx.y = howtoplay_controller->pos.y + TEXTURE_HOWTOPLAY_CONTROLLER_SIZE_Y;
	howtoplay_controller->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// HOWTOPLAY_CONTROLLER�擾�֐�
//=============================================================================
HOWTOPLAY_CONTROLLER *GetHowtoplay_controller(int no)
{
	return(&howtoplay_controllerWk[no]);
}

