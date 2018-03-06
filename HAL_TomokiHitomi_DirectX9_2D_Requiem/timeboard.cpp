//=============================================================================
//
// �^�C�g������ [timeboard.cpp]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#include "main.h"
#include "timeboard.h"
#include "input.h"
#include "sound.h"
#include "result.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexTimeboard(int no);
void SetTextureTimeboard( int no, int cntPattern );	//
void SetVertexTimeboard(int no);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
TIMEBOARD					timeboardWk[TIMEBOARD_MAX];

// �e�N�X�`���ւ̃|���S��
LPDIRECT3DTEXTURE9		pD3DTextureTimeboard = NULL;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitTimeboard(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TIMEBOARD *timeboard = &timeboardWk[0];


	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_TIMEBOARD00,				// �t�@�C���̖��O
			&pD3DTextureTimeboard);			// �ǂݍ��ރ������̃|�C���^
	}

	// �^�C�g���̏�����
	for (int i = 0; i < TIMEBOARD_MAX; i++, timeboard++)
	{
		timeboard->bUse = true;
		timeboard->bPosMoveFlag = true;

		timeboard->pos = D3DXVECTOR3((float)TIMEBOARD_POS_X, (float)TIMEBOARD_POS_Y, 0.0f);
		timeboard->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		timeboard->nCountAnim = 0;
		timeboard->nPatternAnim = 0;

		timeboard->Texture = pD3DTextureTimeboard;			// �e�N�X�`���ւ̃G�l�~�[
		timeboard->size = D3DXVECTOR2(TEXTURE_TIMEBOARD00_SIZE_X, TEXTURE_TIMEBOARD00_SIZE_Y);

		// ���_���̍쐬
		MakeVertexTimeboard(i);
	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTimeboard(void)
{
	TIMEBOARD *timeboard = &timeboardWk[0];

	// ���������
	if (pD3DTextureTimeboard != NULL)
	{
		pD3DTextureTimeboard->Release();
		pD3DTextureTimeboard = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateTimeboard(void)
{
	TIMEBOARD *timeboard = &timeboardWk[0];
	RESULT *result = GetResult(0);
	for (int i = 0; i < TIMEBOARD_MAX; i++, timeboard++)
	{
		if (timeboard->bUse == true)
		{
			// �A�j���[�V����
			timeboard->nCountAnim++;
			if ((timeboard->nCountAnim % TIME_ANIMATION_TIMEBOARD) == 0)
			{
				// �p�^�[���̐؂�ւ�
				timeboard->nPatternAnim = (timeboard->nPatternAnim + 1) % ANIM_PATTERN_NUM_TIMEBOARD;
			}

			if (timeboard->bPosMoveFlag && !result->bPosMoveFlag)
			{
				timeboard->pos += result->vecPosMove;
				timeboard->bPosMoveFlag = false;
			}

			// �e�N�X�`�����W��ݒ�
			SetTextureTimeboard(i, timeboard->nPatternAnim);
			// �ړ���̍��W�Œ��_��ݒ�
			SetVertexTimeboard(i);

		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTimeboard(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TIMEBOARD *timeboard = &timeboardWk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < TIMEBOARD_MAX; i++, timeboard++)
	{
		if (timeboard->bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, timeboard->Texture);

			// �^�C�g���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_TIMEBOARD, timeboard->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexTimeboard(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	TIMEBOARD *timeboard = &timeboardWk[no];

	// ���_���W�̐ݒ�
	timeboard->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	timeboard->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_TIMEBOARD00_SIZE_X, 100.0f, 0.0f);
	timeboard->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_TIMEBOARD00_SIZE_Y, 0.0f);
	timeboard->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_TIMEBOARD00_SIZE_X, 100.0f+TEXTURE_TIMEBOARD00_SIZE_Y, 0.0f);
	//SetVertexTimeboard();

	// rhw�̐ݒ�
	timeboard->vertexWk[0].rhw =
	timeboard->vertexWk[1].rhw =
	timeboard->vertexWk[2].rhw =
	timeboard->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	timeboard->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	timeboard->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	timeboard->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	timeboard->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	timeboard->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	timeboard->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_TIMEBOARD, 0.0f );
	timeboard->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_TIMEBOARD );
	timeboard->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_TIMEBOARD, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_TIMEBOARD );

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureTimeboard( int no, int cntPattern )
{
	TIMEBOARD *timeboard = &timeboardWk[no];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_TIMEBOARD;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_TIMEBOARD;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_TIMEBOARD;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_TIMEBOARD;
	timeboard->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	timeboard->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	timeboard->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	timeboard->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// ���_���W�̐ݒ�֐�
//=============================================================================
void SetVertexTimeboard(int no)
{
	TIMEBOARD *timeboard = &timeboardWk[no];

	timeboard->vertexWk[0].vtx.x = timeboard->pos.x - TEXTURE_TIMEBOARD00_SIZE_X;
	timeboard->vertexWk[0].vtx.y = timeboard->pos.y - TEXTURE_TIMEBOARD00_SIZE_Y;
	timeboard->vertexWk[0].vtx.z = 0.0f;

	timeboard->vertexWk[1].vtx.x = timeboard->pos.x + TEXTURE_TIMEBOARD00_SIZE_X;
	timeboard->vertexWk[1].vtx.y = timeboard->pos.y - TEXTURE_TIMEBOARD00_SIZE_Y;
	timeboard->vertexWk[1].vtx.z = 0.0f;

	timeboard->vertexWk[2].vtx.x = timeboard->pos.x - TEXTURE_TIMEBOARD00_SIZE_X;
	timeboard->vertexWk[2].vtx.y = timeboard->pos.y + TEXTURE_TIMEBOARD00_SIZE_Y;
	timeboard->vertexWk[2].vtx.z = 0.0f;

	timeboard->vertexWk[3].vtx.x = timeboard->pos.x + TEXTURE_TIMEBOARD00_SIZE_X;
	timeboard->vertexWk[3].vtx.y = timeboard->pos.y + TEXTURE_TIMEBOARD00_SIZE_Y;
	timeboard->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �^�C�g���擾�֐�
//=============================================================================
TIMEBOARD *GetTimeboard(int no)
{
	return(&timeboardWk[no]);
}

