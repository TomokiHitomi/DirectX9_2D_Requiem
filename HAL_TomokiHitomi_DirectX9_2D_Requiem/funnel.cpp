//=============================================================================
//
// �t�@���l������ [funnel.cpp]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
//#include "main.h"
#include "funnel.h"
#include "bullet.h"
#include "input.h"
#include "player.h"
#include "enemy.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexFunnel(int no);
void SetTextureFunnel( int no, int cntPattern );
void SetVertexFunnel(int no);

void SetFunnelBullet(void);

void SetFunnelType(int nFunnel);


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
FUNNEL					funnelWk[FUNNEL_MAX];
int						g_nTotalFunnel;					// �t�@���l��01�̑����ː�
int						g_nTotalFunnel02;					// �t�@���l��01�̑����ː�

int						g_nReloadFunnel00;
int						g_nReloadFunnel;
int						g_nReloadFunnel02;

// �e�N�X�`���ւ̃|���S��
LPDIRECT3DTEXTURE9		pD3DTextureFunnel = NULL;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitFunnel(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	FUNNEL *funnel = &funnelWk[0];

	g_nTotalFunnel = 0;
	g_nTotalFunnel02 = 0;

	g_nReloadFunnel00 = 0;
	g_nReloadFunnel = 0;
	g_nReloadFunnel02 = 0;

	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_FUNNEL,				// �t�@�C���̖��O
			&pD3DTextureFunnel);			// �ǂݍ��ރ������̃|�C���^
	}

	// �t�@���l���̏�����
	for (int i = 0; i < FUNNEL_MAX; i++, funnel++)
	{
		funnel->size = D3DXVECTOR2(TEXTURE_FUNNEL_SIZE_X, TEXTURE_FUNNEL_SIZE_Y);
		funnel->Texture = pD3DTextureFunnel;	// �e�N�X�`���ւ̃t�@���l��

		funnel->fBaseAngle = 0.0f;
		funnel->fRadius = 0.0f;

		// �t�@���l���X�e�[�^�X�̏�����
		InitStatusFunnel(i);

		// ���_���̍쐬
		MakeVertexFunnel(i);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitFunnel(void)
{
	FUNNEL *funnel = &funnelWk[0];
	// ���������
	if (pD3DTextureFunnel != NULL)
	{
		pD3DTextureFunnel->Release();
		pD3DTextureFunnel = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateFunnel(void)
{
	FUNNEL *funnel = &funnelWk[0];
	ENEMY *enemy;
	PLAYER *player = GetPlayer(0);

	for (int i = 0; i < FUNNEL_MAX; i++, funnel++)
	{
		if (funnel->bUse == true)
		{
			// �e�N�X�`���[�ݒ�
			funnel->nCountAnim++;
			if (funnel->nCountAnim % TIME_ANIMATION_FUNNEL == 0)
			{
				// �p�^�[���̐؂�ւ�
				funnel->nPatternAnim = (funnel->nPatternAnim + 1) % ANIM_PATTERN_NU_FUNNEL;
			}

			// ���d�̓��[�h�̓t�@���l����W�J�E�o���b�g����
			if (GetKeyboardPress(DIK_LSHIFT) || GetKeyboardPress(DIK_RSHIFT) || IsButtonPressed(0, BUTTON_R))
			{
				funnel->fDistance += FUNNEL_INJECTION_SPEED;
				if (funnel->fDistance > FUNNEL_DISTANCE_MAX)
				{
					funnel->fDistance = FUNNEL_DISTANCE_MAX;
				}
			}
			else
			{
				funnel->fDistance -= FUNNEL_INJECTION_SPEED;
				if (funnel->fDistance < 0.0f)
				{
					funnel->bUse = false;
				}
			}

			// �o���b�g����
			if (GetKeyboardPress(DIK_Z) || GetKeyboardPress(DIK_B) || IsButtonPressed(0, BUTTON_A))
			{
				if (funnel->fDistance == FUNNEL_DISTANCE_MAX)
				{
					SetFunnelBullet();
				}
			}

			SetFunnelType(i);

			// �t�@���l���̓����x��MP�{���ŕύX
			funnel->nAlpha = FUNNEL_ALPHA_MIN + (FUNNEL_ALPHA / (float)PLAYER_MANAMAX * player->fManaPoint);

			// ���G�_�ł̓K�p
			funnel->nAlpha = funnel->nAlpha - (PLAYER_ALPHA_MAX - player->nAlphaCount);
			if (funnel->nAlpha < 0)
			{
				funnel->nAlpha = 0;
			}
			
			// �e�N�X�`�����W��ݒ�
			SetTextureFunnel(i, funnel->nPatternAnim);

			// ��]����
			if (funnel->nPatternHoming)
			{
				funnel->rot.z -= FUNNEL01_ROTATION;
			}
			else
			{
				funnel->rot.z += FUNNEL01_ROTATION;
			}

			// �ړ���̍��W�Œ��_��ݒ�
			SetVertexFunnel(i);

			// �A�ˑ��x����
			funnel->nReloadBullet--;
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawFunnel(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	FUNNEL *funnel = &funnelWk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < FUNNEL_MAX; i++, funnel++)
	{
		if (funnel->bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, funnel->Texture);

			// �t�@���l���̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_FUNNEL, funnel->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexFunnel(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	FUNNEL *funnel = &funnelWk[no];

	// �p�x�Ɣ��a�����߂�
	funnel->fBaseAngle = atan2f(TEXTURE_FUNNEL_SIZE_Y, TEXTURE_FUNNEL_SIZE_X);
	D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_FUNNEL_SIZE_X, TEXTURE_FUNNEL_SIZE_Y);
	funnel->fRadius = D3DXVec2Length(&temp);

	// ���_���W�̐ݒ�
	funnel->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	funnel->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_FUNNEL_SIZE_X, 100.0f, 0.0f);
	funnel->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_FUNNEL_SIZE_Y, 0.0f);
	funnel->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_FUNNEL_SIZE_X, 100.0f+TEXTURE_FUNNEL_SIZE_Y, 0.0f);
	//SetVertexFunnel();

	// rhw�̐ݒ�
	funnel->vertexWk[0].rhw =
	funnel->vertexWk[1].rhw =
	funnel->vertexWk[2].rhw =
	funnel->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	funnel->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, funnel->nAlpha);
	funnel->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, funnel->nAlpha);
	funnel->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, funnel->nAlpha);
	funnel->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, funnel->nAlpha);

	// �e�N�X�`�����W�̐ݒ�
	funnel->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	funnel->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_FUNNEL, 0.0f );
	funnel->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_FUNNEL );
	funnel->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_FUNNEL, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_FUNNEL );

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureFunnel( int no, int cntPattern )
{
	FUNNEL *funnel = &funnelWk[no];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_FUNNEL;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_FUNNEL;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_FUNNEL;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_FUNNEL;
	funnel->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	funnel->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	funnel->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	funnel->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// ���_���W�̐ݒ�֐�
//=============================================================================
void SetVertexFunnel(int no)
{
	FUNNEL *funnel = &funnelWk[no];
	// ���_0:��]����
	funnel->vertexWk[0].vtx.x = funnel->pos.x - cosf(funnel->fBaseAngle + funnel->rot.z) * funnel->fRadius;
	funnel->vertexWk[0].vtx.y = funnel->pos.y - sinf(funnel->fBaseAngle + funnel->rot.z) * funnel->fRadius;
	funnel->vertexWk[0].vtx.z = 0.0f;

	// ���_1:��]����
	funnel->vertexWk[1].vtx.x = funnel->pos.x + cosf(funnel->fBaseAngle - funnel->rot.z) * funnel->fRadius;
	funnel->vertexWk[1].vtx.y = funnel->pos.y - sinf(funnel->fBaseAngle - funnel->rot.z) * funnel->fRadius;
	funnel->vertexWk[1].vtx.z = 0.0f;

	// ���_2:��]����
	funnel->vertexWk[2].vtx.x = funnel->pos.x - cosf(funnel->fBaseAngle - funnel->rot.z) * funnel->fRadius;
	funnel->vertexWk[2].vtx.y = funnel->pos.y + sinf(funnel->fBaseAngle - funnel->rot.z) * funnel->fRadius;
	funnel->vertexWk[2].vtx.z = 0.0f;

	// ���_3:��]����
	funnel->vertexWk[3].vtx.x = funnel->pos.x + cosf(funnel->fBaseAngle + funnel->rot.z) * funnel->fRadius;
	funnel->vertexWk[3].vtx.y = funnel->pos.y + sinf(funnel->fBaseAngle + funnel->rot.z) * funnel->fRadius;
	funnel->vertexWk[3].vtx.z = 0.0f;

	// ���ˌ��̐ݒ�
	funnel->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, funnel->nAlpha);
	funnel->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, funnel->nAlpha);
	funnel->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, funnel->nAlpha);
	funnel->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, funnel->nAlpha);
}

//=============================================================================
// �t�@���l�����v���C���[�ɐݒu
//=============================================================================
void SetFunnel(D3DXVECTOR3 pos)
{
	FUNNEL *funnel = &funnelWk[0];

	// �S�t�@���l���𓙊Ԋu�ɃZ�b�g
	for (int i = 0; i < FUNNEL_MAX; i++, funnel++)
	{
		if (!funnel->bUse)
		{
			// �t�@���l�����W��ΏۂɃZ�b�g
			funnel->pos.x = pos.x;
			funnel->pos.y = pos.y;
			// �t�@���l���̃^�C�v���Z�b�g
			funnel->nFunnelType = i % FUNNEL_TYPE_MAX;
			// �t�@���l���ˏo�p�x���Z�b�g
			funnel->fAngle = ((D3DX_PI * 2.0f) / FUNNEL_MAX) * i;
			// �t�@���l�����A�N�e�B�u�ɂ���
			funnel->bUse = true;
		}
	}
}

//=============================================================================
// �t�@���l�����v���C���[�Ɋi�[
//=============================================================================
void ReleaseFunnel(void)
{
	FUNNEL *funnel = &funnelWk[0];

	// �S�t�@���l�����m���A�N�e�B�u
	for (int i = 0; i < FUNNEL_MAX; i++, funnel++)
	{
		if (funnel->bUse)
		{
			InitStatusFunnel(i);
			funnel->bUse = false;
		}
	}
}

//=============================================================================
// �t�@���l���Ƀo���b�g��ݒu
//=============================================================================
void SetFunnelBullet(void)
{
	FUNNEL *funnel = &funnelWk[0];

	// �S�t�@���l�����m���A�N�e�B�u
	for (int i = 0; i < FUNNEL_MAX; i++, funnel++)
	{
		// �����[�h���m�F
		if (funnel->nReloadBullet <= 0)
		{
			funnel->nReloadBullet = FUNNEL_BULLET_RELOAD_SPEED;
			funnel->bReload = true;
		}
		// �����[�h���������Ă���ꍇ�̓o���b�g���Z�b�g
		if (funnel->bReload)
		{
			SetBullet(funnel->pos, 3);
		}
		funnel->bReload = false;
	}
}

//=============================================================================
// �t�@���l���p�^�[��00 �t�@���l��
//=============================================================================
void SetFunnelType(int nFunnel)
{
	FUNNEL *funnel = &funnelWk[nFunnel];
	PLAYER *player = GetPlayer(0);

	// �p�x�ύX
	funnel->fAngle += D3DX_PI / FUNNEL_ROTATIONAL_SPEED;

	// 360�x�𒴂�����360�x������
	if (funnel->fAngle >= D3DX_PI * 2.0f)
	{
		funnel->fAngle -= D3DX_PI * 2.0f;
	}

	// �ړ��ʓK�p
	funnel->pos.x = player->pos.x + (cos(funnel->fAngle) * funnel->fDistance);
	funnel->pos.y = player->pos.y + (sin(funnel->fAngle) * funnel->fDistance);
}

//=============================================================================
// �t�@���l���̍ė��p����
//=============================================================================
void InitStatusFunnel(int nFunnel)
{
	FUNNEL *funnel = &funnelWk[nFunnel];

	// �t�@���l���X�e�[�^�X�̏�����
	funnel->bUse = false;
	funnel->bTextureUse = false;
	funnel->bReload = false;

	funnel->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ���W�f�[�^��������
	funnel->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	funnel->vecDestination = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	funnel->nCountAnim = 0;
	funnel->nPatternAnim = 0;
	funnel->nFunnelType = 0;
	funnel->nFunnelCount = 0;
	funnel->nAngleType = 0;
	funnel->nPatternHoming = 0;
	funnel->nHomingFlag = 0;
	funnel->nTarget = 0;
	funnel->nReloadBullet = 0;
	funnel->nAlpha = FUNNEL_ALPHA_MAX;

	funnel->vecTa = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	funnel->nDirection = 0;

	funnel->fFunnelSpeed = 0.0f;
	funnel->fAngle = 0.0f;
	funnel->fDistance = 0.0f;
		

	return;
}

//=============================================================================
// �t�@���l���擾�֐�
//=============================================================================
FUNNEL *GetFunnel(int no)
{
	return(&funnelWk[no]);
}
