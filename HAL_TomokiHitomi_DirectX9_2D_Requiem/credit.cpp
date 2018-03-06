//=============================================================================
//
// CREDIT���� [credit.cpp]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "credit.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexCredit(int no);
void SetTextureCredit( int no, int cntPattern );
void SetVertexCredit(int no);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
CREDIT					creditWk[CREDIT_MAX];

// �e�N�X�`���ւ̃|���S��
LPDIRECT3DTEXTURE9		pD3DTextureCredit = NULL;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitCredit(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CREDIT *credit = &creditWk[0];

	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_CREDIT,				// �t�@�C���̖��O
			&pD3DTextureCredit);			// �ǂݍ��ރ������̃|�C���^
	}

	// CREDIT�̏�����
	for (int i = 0; i < CREDIT_MAX; i++, credit++)
	{
		credit->bUse = true;
		credit->pos = D3DXVECTOR3((float)CREDIT_POS_X, (float)CREDIT_POS_Y, 0.0f);
		credit->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		credit->nCountAnim = 0;
		credit->nPatternAnim = 0;

		credit->Texture = pD3DTextureCredit;			// �e�N�X�`���ւ�CREDIT
		credit->size = D3DXVECTOR2(TEXTURE_CREDIT_SIZE_X, TEXTURE_CREDIT_SIZE_Y);

		// ���_���̍쐬
		MakeVertexCredit(i);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitCredit(void)
{
	CREDIT *credit = &creditWk[0];

	// ���������
	if (pD3DTextureCredit != NULL)
	{
		pD3DTextureCredit->Release();
		pD3DTextureCredit = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateCredit(void)
{
	CREDIT *credit = &creditWk[0];
	for (int i = 0; i < CREDIT_MAX; i++, credit++)
	{
		if (credit->bUse == true)
		{
			// �e�N�X�`�����W��ݒ�
			SetTextureCredit(i, credit->nPatternAnim);
			// �ړ���̍��W�Œ��_��ݒ�
			SetVertexCredit(i);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawCredit(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CREDIT *credit = &creditWk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < CREDIT_MAX; i++, credit++)
	{
		if (credit->bUse)
		{
			if (GetKeyboardTrigger(DIK_ESCAPE) || IsButtonTriggered(0, BUTTON_B) || IsButtonTriggered(0, BUTTON_START))
			{
				SetSe(3, E_DS8_FLAG_NONE, true);
				InitGame(1);
				SetStage(STAGE_TITLE);
			}

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, credit->Texture);

			// CREDIT�̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_CREDIT, credit->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexCredit(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	CREDIT *credit = &creditWk[no];

	// ���_���W�̐ݒ�
	credit->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	credit->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_CREDIT_SIZE_X, 100.0f, 0.0f);
	credit->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_CREDIT_SIZE_Y, 0.0f);
	credit->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_CREDIT_SIZE_X, 100.0f+TEXTURE_CREDIT_SIZE_Y, 0.0f);
	//SetVertexCredit();

	// rhw�̐ݒ�
	credit->vertexWk[0].rhw =
	credit->vertexWk[1].rhw =
	credit->vertexWk[2].rhw =
	credit->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	credit->vertexWk[0].diffuse = D3DCOLOR_RGBA(TEXTURE_CREDIT_R, TEXTURE_CREDIT_G, TEXTURE_CREDIT_B, 255);
	credit->vertexWk[1].diffuse = D3DCOLOR_RGBA(TEXTURE_CREDIT_R, TEXTURE_CREDIT_G, TEXTURE_CREDIT_B, 255);
	credit->vertexWk[2].diffuse = D3DCOLOR_RGBA(TEXTURE_CREDIT_R, TEXTURE_CREDIT_G, TEXTURE_CREDIT_B, 255);
	credit->vertexWk[3].diffuse = D3DCOLOR_RGBA(TEXTURE_CREDIT_R, TEXTURE_CREDIT_G, TEXTURE_CREDIT_B, 255);

	// �e�N�X�`�����W�̐ݒ�
	credit->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	credit->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_CREDIT, 0.0f );
	credit->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_CREDIT );
	credit->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_CREDIT, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_CREDIT );

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureCredit( int no, int cntPattern )
{
	CREDIT *credit = &creditWk[no];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_CREDIT;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_CREDIT;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_CREDIT;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_CREDIT;
	credit->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	credit->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	credit->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	credit->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// ���_���W�̐ݒ�֐�
//=============================================================================
void SetVertexCredit(int no)
{
	CREDIT *credit = &creditWk[no];

	credit->vertexWk[0].vtx.x = credit->pos.x - TEXTURE_CREDIT_SIZE_X;
	credit->vertexWk[0].vtx.y = credit->pos.y - TEXTURE_CREDIT_SIZE_Y;
	credit->vertexWk[0].vtx.z = 0.0f;

	credit->vertexWk[1].vtx.x = credit->pos.x + TEXTURE_CREDIT_SIZE_X;
	credit->vertexWk[1].vtx.y = credit->pos.y - TEXTURE_CREDIT_SIZE_Y;
	credit->vertexWk[1].vtx.z = 0.0f;

	credit->vertexWk[2].vtx.x = credit->pos.x - TEXTURE_CREDIT_SIZE_X;
	credit->vertexWk[2].vtx.y = credit->pos.y + TEXTURE_CREDIT_SIZE_Y;
	credit->vertexWk[2].vtx.z = 0.0f;

	credit->vertexWk[3].vtx.x = credit->pos.x + TEXTURE_CREDIT_SIZE_X;
	credit->vertexWk[3].vtx.y = credit->pos.y + TEXTURE_CREDIT_SIZE_Y;
	credit->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// CREDIT�Z�b�g�֐�
//=============================================================================
void SetCredit(void)
{
	CREDIT *credit = &creditWk[0];
	// ���g�p����
	for (int i = 0; i < CREDIT_MAX; i++, credit++)
	{
		if (!credit->bUse)
		{
			// �L���ɂ���
			credit->bUse = true;
			return;
		}
	}
}

//=============================================================================
// CREDIT�擾�֐�
//=============================================================================
CREDIT *GetCredit(int no)
{
	return(&creditWk[no]);
}

