//=============================================================================
//
// �^�C�g������ [thank.cpp]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#include "main.h"
#include "thank.h"
#include "input.h"
#include "sound.h"
#include "close.h"
#include "fade.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexThank(int no);
void SetTextureThank( int no, int cntPattern );	//
void SetVertexThank(int no);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
THANK					thankWk[THANK_MAX];

// �e�N�X�`���ւ̃|���S��
LPDIRECT3DTEXTURE9		pD3DTextureThank = NULL;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitThank(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	THANK *thank = &thankWk[0];

	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_THANK00,				// �t�@�C���̖��O
			&pD3DTextureThank);			// �ǂݍ��ރ������̃|�C���^
	}

	// �^�C�g���̏�����
	for (int i = 0; i < THANK_MAX; i++, thank++)
	{
		thank->bUse = false;
		thank->pos = D3DXVECTOR3((float)THANK_POS_X, (float)THANK_POS_Y, 0.0f);
		thank->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		thank->nCountAnim = 0;
		thank->nPatternAnim = 0;
		thank->nAlphaCount = 0;
		thank->nSceneCount = THANK_SCENE_COUNT;

		thank->Texture = pD3DTextureThank;			// �e�N�X�`���ւ̃G�l�~�[
		thank->size = D3DXVECTOR2(TEXTURE_THANK00_SIZE_X, TEXTURE_THANK00_SIZE_Y);

		// ���_���̍쐬
		MakeVertexThank(i);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitThank(void)
{
	THANK *thank = &thankWk[0];

	// ���������
	if (pD3DTextureThank != NULL)
	{
		pD3DTextureThank->Release();
		pD3DTextureThank = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateThank(void)
{
	THANK *thank = &thankWk[0];

	for (int i = 0; i < THANK_MAX; i++, thank++)
	{
		if (thank->bUse)
		{
			// �A�j���[�V����
			thank->nCountAnim++;
			if ((thank->nCountAnim % TIME_ANIMATION_THANK) == 0)
			{
				// �p�^�[���̐؂�ւ�
				thank->nPatternAnim = (thank->nPatternAnim + 1) % ANIM_PATTERN_NUM_THANK;
			}

			thank->nAlphaCount += THANK_ALPHA_SPEED;
			if (thank->nAlphaCount >= THANK_ALPHA_MAX)
			{
				thank->nAlphaCount = THANK_ALPHA_MAX;
			}

			thank->nSceneCount--;
			if (thank->nSceneCount <= 0)
			{
				InitGame(1);
				SetStage(STAGE_TITLE);
			}

			// ��ʑJ��(0)�A��T�ڗp����������
			if (GetKeyboardTrigger(DIK_RETURN) || GetKeyboardTrigger(DIK_NUMPADENTER) || IsButtonTriggered(0, BUTTON_B) || IsButtonTriggered(0, BUTTON_C))
			{
				InitGame(1);
				SetStage(STAGE_TITLE);
			}


			// �e�N�X�`�����W��ݒ�
			SetTextureThank(i, thank->nPatternAnim);
			// �ړ���̍��W�Œ��_��ݒ�
			SetVertexThank(i);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawThank(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	THANK *thank = &thankWk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < THANK_MAX; i++, thank++)
	{
		if (thank->bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, thank->Texture);

			// �^�C�g���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_THANK, thank->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexThank(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	THANK *thank = &thankWk[no];

	// ���_���W�̐ݒ�
	thank->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	thank->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_THANK00_SIZE_X, 100.0f, 0.0f);
	thank->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_THANK00_SIZE_Y, 0.0f);
	thank->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_THANK00_SIZE_X, 100.0f+TEXTURE_THANK00_SIZE_Y, 0.0f);
	//SetVertexThank();

	// rhw�̐ݒ�
	thank->vertexWk[0].rhw =
	thank->vertexWk[1].rhw =
	thank->vertexWk[2].rhw =
	thank->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	thank->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, thank->nAlphaCount);
	thank->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, thank->nAlphaCount);
	thank->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, thank->nAlphaCount);
	thank->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, thank->nAlphaCount);

	// �e�N�X�`�����W�̐ݒ�
	thank->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	thank->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_THANK, 0.0f );
	thank->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_THANK );
	thank->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_THANK, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_THANK );

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureThank( int no, int cntPattern )
{
	THANK *thank = &thankWk[no];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_THANK;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_THANK;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_THANK;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_THANK;
	thank->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	thank->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	thank->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	thank->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// ���_���W�̐ݒ�֐�
//=============================================================================
void SetVertexThank(int no)
{
	THANK *thank = &thankWk[no];

	thank->vertexWk[0].vtx.x = thank->pos.x - TEXTURE_THANK00_SIZE_X;
	thank->vertexWk[0].vtx.y = thank->pos.y - TEXTURE_THANK00_SIZE_Y;
	thank->vertexWk[0].vtx.z = 0.0f;

	thank->vertexWk[1].vtx.x = thank->pos.x + TEXTURE_THANK00_SIZE_X;
	thank->vertexWk[1].vtx.y = thank->pos.y - TEXTURE_THANK00_SIZE_Y;
	thank->vertexWk[1].vtx.z = 0.0f;

	thank->vertexWk[2].vtx.x = thank->pos.x - TEXTURE_THANK00_SIZE_X;
	thank->vertexWk[2].vtx.y = thank->pos.y + TEXTURE_THANK00_SIZE_Y;
	thank->vertexWk[2].vtx.z = 0.0f;

	thank->vertexWk[3].vtx.x = thank->pos.x + TEXTURE_THANK00_SIZE_X;
	thank->vertexWk[3].vtx.y = thank->pos.y + TEXTURE_THANK00_SIZE_Y;
	thank->vertexWk[3].vtx.z = 0.0f;

	// ���ˌ��̐ݒ�
	thank->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, thank->nAlphaCount);
	thank->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, thank->nAlphaCount);
	thank->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, thank->nAlphaCount);
	thank->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, thank->nAlphaCount);
}

//=============================================================================
// �^�C�g���擾�֐�
//=============================================================================
THANK *GetThank(int no)
{
	return(&thankWk[no]);
}

