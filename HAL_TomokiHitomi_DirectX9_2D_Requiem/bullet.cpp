//=============================================================================
//
// �o���b�g���� [bullet.cpp]
// Author : GP11B243 24 �l���F��
//
//=============================================================================
//#include "main.h"
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
HRESULT MakeVertexBullet(int no);
void SetTextureBullet( int no, int cntPattern );
void SetVertexBullet(int no);

void SetSearchEnemy(int nBullet);

void SetBulletType(int nBullet);
void SetBulletType00(int nBullet);
void SetBulletType01(int nBullet);
void SetBulletType02(int nBullet);
void SetBulletType03(int nBullet);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
BULLET					bulletWk[BULLET_MAX];
int						g_nTotalBullet;					// �o���b�g01�̑����ː�
int						g_nTotalBullet02;					// �o���b�g01�̑����ː�

int						g_nReloadBullet00;
int						g_nReloadBullet;
int						g_nReloadBullet02;

// �e�N�X�`���ւ̃|���S��
LPDIRECT3DTEXTURE9		pD3DTextureBullet = NULL;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitBullet(int type)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BULLET *bullet = &bulletWk[0];

	g_nTotalBullet = 0;
	g_nTotalBullet02 = 0;

	g_nReloadBullet00 = 0;
	g_nReloadBullet = 0;
	g_nReloadBullet02 = 0;

	if (type == 0)
	{
		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,		// �f�o�C�X�̃|�C���^
			TEXTURE_GAME_BULLET,				// �t�@�C���̖��O
			&pD3DTextureBullet);			// �ǂݍ��ރ������̃|�C���^
	}

	// �o���b�g�̏�����
	for (int i = 0; i < BULLET_MAX; i++, bullet++)
	{
		bullet->size = D3DXVECTOR2(TEXTURE_BULLET_SIZE_X, TEXTURE_BULLET_SIZE_Y);
		bullet->Texture = pD3DTextureBullet;	// �e�N�X�`���ւ̃o���b�g

		bullet->fBaseAngle = 0.0f;
		bullet->fRadius = 0.0f;

		// �o���b�g�X�e�[�^�X�̏�����
		InitStatusBullet(i);

		// ���_���̍쐬
		MakeVertexBullet(i);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitBullet(void)
{
	BULLET *bullet = &bulletWk[0];
	// ���������
	if (pD3DTextureBullet != NULL)
	{
		pD3DTextureBullet->Release();
		pD3DTextureBullet = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBullet(void)
{
	BULLET *bullet = &bulletWk[0];
	ENEMY *enemy;
	PLAYER *player;

	for (int i = 0; i < BULLET_MAX; i++, bullet++)
	{
		if (bullet->bUse)
		{
			// �e�N�X�`���[�������_���ݒ�
			if (bullet->bTextureUse == false)
			{
				bullet->nPatternAnim = (bullet->nBulletType * TEXTURE_PATTERN_DIVIDE_X_BULLET ) + (rand() % TEXTURE_PATTERN_DIVIDE_X_BULLET);
				bullet->bTextureUse = true;
			}

			SetBulletType(i);

			// �t�B�[���h�O�Ŗ��g�p���i��ʊO�e�������j
			if (bullet->pos.y < 0 - (TEXTURE_BULLET_SIZE_Y + SCREEN_MARGIN)
				|| bullet->pos.y > SCREEN_HEIGHT + (TEXTURE_BULLET_SIZE_Y + SCREEN_MARGIN)
				|| bullet->pos.x < 0 - (TEXTURE_BULLET_SIZE_X + SCREEN_MARGIN)
				|| bullet->pos.x > SCREEN_WIDTH + (TEXTURE_BULLET_SIZE_X + SCREEN_MARGIN) )
			{
				// �o���b�g�X�e�[�^�X�̏�����
				InitStatusBullet(i);
			}
			

			// ��]����
			if (bullet->nPatternHoming)
			{
				bullet->rot.z -= BULLET01_ROTATION;
			}
			else
			{
				bullet->rot.z += BULLET01_ROTATION;
			}

			// �e�N�X�`�����W��ݒ�
			SetTextureBullet(i, bullet->nPatternAnim);
			// �ړ���̍��W�Œ��_��ݒ�
			SetVertexBullet(i);
		}
	}
	// �A�ˑ��x����
	g_nReloadBullet00--;
	g_nReloadBullet--;
	g_nReloadBullet02--;
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BULLET *bullet = &bulletWk[0];

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int i = 0; i < BULLET_MAX; i++, bullet++)
	{
		if (bullet->bUse == true)
		{
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, bullet->Texture);

			// �o���b�g�̕`��
			pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_BULLET, bullet->vertexWk, sizeof(VERTEX_2D));
		}
	}
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexBullet(int no)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	BULLET *bullet = &bulletWk[no];

	// �p�x�Ɣ��a�����߂�
	bullet->fBaseAngle = atan2f(TEXTURE_BULLET_SIZE_Y, TEXTURE_BULLET_SIZE_X);
	D3DXVECTOR2 temp = D3DXVECTOR2(TEXTURE_BULLET_SIZE_X, TEXTURE_BULLET_SIZE_Y);
	bullet->fRadius = D3DXVec2Length(&temp);

	// ���_���W�̐ݒ�
	bullet->vertexWk[0].vtx = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	bullet->vertexWk[1].vtx = D3DXVECTOR3(100.0f+TEXTURE_BULLET_SIZE_X, 100.0f, 0.0f);
	bullet->vertexWk[2].vtx = D3DXVECTOR3(100.0f, 100.0f+TEXTURE_BULLET_SIZE_Y, 0.0f);
	bullet->vertexWk[3].vtx = D3DXVECTOR3(100.0f+TEXTURE_BULLET_SIZE_X, 100.0f+TEXTURE_BULLET_SIZE_Y, 0.0f);
	//SetVertexBullet();

	// rhw�̐ݒ�
	bullet->vertexWk[0].rhw =
	bullet->vertexWk[1].rhw =
	bullet->vertexWk[2].rhw =
	bullet->vertexWk[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	bullet->vertexWk[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, BULLET_ALPHA);
	bullet->vertexWk[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, BULLET_ALPHA);
	bullet->vertexWk[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, BULLET_ALPHA);
	bullet->vertexWk[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, BULLET_ALPHA);

	// �e�N�X�`�����W�̐ݒ�
	bullet->vertexWk[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	bullet->vertexWk[1].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_BULLET, 0.0f );
	bullet->vertexWk[2].tex = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_BULLET );
	bullet->vertexWk[3].tex = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X_BULLET, 1.0f/TEXTURE_PATTERN_DIVIDE_Y_BULLET );

	return S_OK;
}

//=============================================================================
// �e�N�X�`�����W�̐ݒ�
//=============================================================================
void SetTextureBullet( int no, int cntPattern )
{
	BULLET *bullet = &bulletWk[no];

	// �e�N�X�`�����W�̐ݒ�
	int x = cntPattern % TEXTURE_PATTERN_DIVIDE_X_BULLET;
	int y = cntPattern / TEXTURE_PATTERN_DIVIDE_X_BULLET;
	float sizeX = 1.0f / TEXTURE_PATTERN_DIVIDE_X_BULLET;
	float sizeY = 1.0f / TEXTURE_PATTERN_DIVIDE_Y_BULLET;
	bullet->vertexWk[0].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	bullet->vertexWk[1].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	bullet->vertexWk[2].tex = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	bullet->vertexWk[3].tex = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

//=============================================================================
// ���_���W�̐ݒ�֐�
//=============================================================================
void SetVertexBullet(int no)
{
	BULLET *bullet = &bulletWk[no];
	// ���_0:��]����
	bullet->vertexWk[0].vtx.x = bullet->pos.x - cosf(bullet->fBaseAngle + bullet->rot.z) * bullet->fRadius;
	bullet->vertexWk[0].vtx.y = bullet->pos.y - sinf(bullet->fBaseAngle + bullet->rot.z) * bullet->fRadius;
	bullet->vertexWk[0].vtx.z = 0.0f;

	// ���_1:��]����
	bullet->vertexWk[1].vtx.x = bullet->pos.x + cosf(bullet->fBaseAngle - bullet->rot.z) * bullet->fRadius;
	bullet->vertexWk[1].vtx.y = bullet->pos.y - sinf(bullet->fBaseAngle - bullet->rot.z) * bullet->fRadius;
	bullet->vertexWk[1].vtx.z = 0.0f;

	// ���_2:��]����
	bullet->vertexWk[2].vtx.x = bullet->pos.x - cosf(bullet->fBaseAngle - bullet->rot.z) * bullet->fRadius;
	bullet->vertexWk[2].vtx.y = bullet->pos.y + sinf(bullet->fBaseAngle - bullet->rot.z) * bullet->fRadius;
	bullet->vertexWk[2].vtx.z = 0.0f;

	// ���_3:��]����
	bullet->vertexWk[3].vtx.x = bullet->pos.x + cosf(bullet->fBaseAngle + bullet->rot.z) * bullet->fRadius;
	bullet->vertexWk[3].vtx.y = bullet->pos.y + sinf(bullet->fBaseAngle + bullet->rot.z) * bullet->fRadius;
	bullet->vertexWk[3].vtx.z = 0.0f;
}

//=============================================================================
// �o���b�g���v���C���[�ɐݒu
//=============================================================================
void SetBullet(D3DXVECTOR3 pos,int nBulletType)
{
	BULLET *bullet = &bulletWk[0];
	bool bReload00 = false;
	bool bReload01 = false;
	bool bReload02 = false;
	bool bReload03 = false;
	int nLoop = 0;
	int nAngleType = 0;

	switch (nBulletType)
	{
	case 0:
		if (g_nReloadBullet00 <= 0)
		{
			g_nReloadBullet00 = BULLET00_RELOAD_SPEED;
			bReload00 = true;
			nLoop = 2;
		}
		break;
	case 1:
		if (g_nReloadBullet <= 0)
		{
			g_nReloadBullet = BULLET01_RELOAD_SPEED;
			bReload01 = true;
		}
		break;
	case 2:
		if (g_nReloadBullet02 <= 0)
		{
			g_nReloadBullet02 = BULLET02_RELOAD_SPEED;
			bReload02 = true;
		}
		break;
	case 3:
		// �o���b�g03�̓t�@���l�����Ń����[�h�Ǘ�
		bReload03 = true;
		break;
	}

	if (bReload00 || bReload01 || bReload02 || bReload03)
	{
		// ���g�p�̒e��T��
		for (int i = 0; i < BULLET_MAX; i++, bullet++)
		{
			if (!bullet->bUse)
			{
				// pos�������ɃZ�b�g
				if (nBulletType != 3)
				{
					bullet->pos.x = pos.x + BULLET_ADJUSTMENT_X;
					bullet->pos.y = pos.y + BULLET_ADJUSTMENT_Y;
				}
				// �o���b�g�̌������Z�b�g
				bullet->nBulletType = nBulletType;
				// ���g�p�̒e����������g�p�ɕύX
				bullet->bUse = true;
				// �e�N�X�`�����W��ݒ�
				SetTextureBullet(i, bullet->nPatternAnim);
				// �ړ���̍��W�Œ��_��ݒ�
				SetVertexBullet(i);

				switch (nBulletType)
				{
				case 0:
					bullet->nAngleType = nAngleType;
					break;
				case 1:
					// �z�[�~���O�p�^�[���ݒu
					bullet->nPatternHoming = g_nTotalBullet % 2;
					// �����ː����J�E���g
					g_nTotalBullet++;
					break;
				case 2:
					// �z�[�~���O�p�^�[���ݒu
					bullet->nPatternHoming = g_nTotalBullet02 % 2;
					// �����ː����J�E���g
					g_nTotalBullet02++;
					break;
				case 3:
					// �t�@���l���o���b�g�͍��W�����Ȃ�
					bullet->pos.x = pos.x;
					bullet->pos.y = pos.y;
					break;
				}
				if (nLoop <= 0)
				{
					return;
				}
				else
				{
					nLoop--;
					nAngleType++;
				}
			}
		}
	}
}

//=============================================================================
// �o���b�g�p�^�[��
//=============================================================================
void SetBulletType(int nBullet)
{
	BULLET *bullet = &bulletWk[nBullet];

	switch(bullet->nBulletType)
	{
	case 0:
		SetBulletType00(nBullet);
		break;
	case 1:
		SetBulletType01(nBullet);
		break;
	case 2:
		SetBulletType02(nBullet);
		break;
	case 3:
		SetBulletType03(nBullet);
		break;
	}
}

//=============================================================================
// �o���b�g�p�^�[��00 �m�[�}���o���b�g
//=============================================================================
void SetBulletType00(int nBullet)
{
	BULLET *bullet = &bulletWk[nBullet];

	// �ʏ�e�i�p�x�Œ�j
	switch (bullet->nAngleType)
	{
	case 0:
		bullet->fAngle = 0.1f;
		break;
	case 1:
		bullet->fAngle = 0.0f;
		break;
	case 2:
		bullet->fAngle = -0.1f;
		break;
	}

	// �ړ��ʌv�Z
	bullet->move.x = cos(bullet->fAngle) * BULLET00_SPEED_MAX;
	bullet->move.y = sin(bullet->fAngle) * BULLET00_SPEED_MAX;
	// �ړ��ʓK�p
	bullet->pos.x += bullet->move.x;
	bullet->pos.y += bullet->move.y;
}


//=============================================================================
// �o���b�g�p�^�[��01 �z�[�~���O�o���b�g�i�p�ȁj
//=============================================================================
void SetBulletType01(int nBullet)
{
	BULLET *bullet = &bulletWk[nBullet];
	ENEMY *enemy;

	// �G�l�~�[����
	SetSearchEnemy(nBullet);

	// �z�[�~���O����
	if (bullet->nHomingFlag == 1)
	{
		bullet->nHomingFlag = 2;
		enemy = GetEnemy(bullet->nTarget);
		if (enemy->bUse)
		{
			bullet->vecTa.x = enemy->pos.x - bullet->pos.x;
			bullet->vecTa.y = enemy->pos.y - bullet->pos.y;

			// atan2�̃G���[�h�~
			if (bullet->vecTa.x == 0 && bullet->vecTa.y == 0)
			{
				bullet->vecTa.x += 0.00001;
			}

			// �p�x�v�Z
			bullet->fAngle = atan2(bullet->vecTa.y, bullet->vecTa.x);

			// �ˊp�ύX
			if (bullet->nPatternHoming == 0)
			{
				bullet->fAngle += 0.3;
			}
			else if (bullet->nPatternHoming == 1)
			{
				bullet->fAngle -= 0.3;
			}
		}
	}
	if (bullet->nHomingFlag == 2)
	{
		// �ړ��ʌv�Z
		bullet->move.x = cos(bullet->fAngle) * BULLET01_SPEED_MAX;
		bullet->move.y = sin(bullet->fAngle) * BULLET01_SPEED_MAX;
		// �ړ��ʓK�p
		bullet->pos.x += bullet->move.x;
		bullet->pos.y += bullet->move.y;
	}
	else
	{
		bullet->nHomingFlag = 3;
		if (bullet->nPatternHoming)
		{
			bullet->pos.x += BULLET01_SPEED_MAX;
			bullet->pos.y += BULLET01_SPEED_MAX / 4;
		}
		else
		{
			bullet->pos.x += BULLET01_SPEED_MAX;
			bullet->pos.y -= BULLET01_SPEED_MAX / 4;
		}
	}
}

//=============================================================================
// �o���b�g�p�^�[��02 �z�[�~���O�o���b�g
//=============================================================================
void SetBulletType02(int nBullet)
{
	BULLET *bullet = &bulletWk[nBullet];
	ENEMY *enemy;

	// �o���b�g02�̉���
	bullet->fBulletSpeed += BULLET02_SPEED_ACCELERATOR;
	if (bullet->fBulletSpeed >= BULLET02_SPEED_MAX)
	{
		bullet->fBulletSpeed = BULLET02_SPEED_MAX;
	}

	if (bullet->nBulletCount == 0)
	{
		// �ˊp�ύX
		if (bullet->nPatternHoming == 0)
		{
			bullet->vecTa.x = -50 - (rand() % 100);
			bullet->vecTa.y = +50 + (rand() % 200);
		}
		else if (bullet->nPatternHoming == 1)
		{
			bullet->vecTa.x = -50 - (rand() % 100);
			bullet->vecTa.y = -50 - (rand() % 200);
		}

		// atan2�̃G���[�h�~
		if (bullet->vecTa.x == 0 && bullet->vecTa.y == 0)
		{
			bullet->vecTa.x += 0.00001;
		}

		// �p�x�v�Z
		bullet->fAngle = atan2(bullet->vecTa.y, bullet->vecTa.x);

		// �ˊp�ύX
		if (bullet->nPatternHoming == 0)
		{
			bullet->fAngle += 0.5;
		}
		else if (bullet->nPatternHoming == 1)
		{
			bullet->fAngle -= 0.5;
		}
	}
	else if (bullet->nBulletCount <= 30)
	{
		// �ړ��ʌv�Z
		bullet->move.x = cos(bullet->fAngle) * bullet->fBulletSpeed;
		bullet->move.y = sin(bullet->fAngle) * bullet->fBulletSpeed;
		// �ړ��ʓK�p
		bullet->pos.x += bullet->move.x;
		bullet->pos.y += bullet->move.y;
	}
	else
	{
		// �G�l�~�[����
		SetSearchEnemy(nBullet);

		// �z�[�~���O����
		if (bullet->nHomingFlag == 1)
		{
			bullet->nHomingFlag = 2;
			enemy = GetEnemy(bullet->nTarget);
			if (enemy->bUse)
			{
				bullet->vecTa.x = enemy->pos.x - bullet->pos.x;
				bullet->vecTa.y = enemy->pos.y - bullet->pos.y;

				// atan2�̃G���[�h�~
				if (bullet->vecTa.x == 0 && bullet->vecTa.y == 0)
				{
					bullet->vecTa.x += 0.00001;
				}

				// �p�x�v�Z
				bullet->fAngle = atan2(bullet->vecTa.y, bullet->vecTa.x);
			}
		}
		if (bullet->nHomingFlag == 2)
		{
			// �ړ��ʌv�Z
			bullet->move.x = cos(bullet->fAngle) * bullet->fBulletSpeed;
			bullet->move.y = sin(bullet->fAngle) * bullet->fBulletSpeed;
			// �ړ��ʓK�p
			bullet->pos.x += bullet->move.x;
			bullet->pos.y += bullet->move.y;
		}
		else
		{
			bullet->pos.x += bullet->fBulletSpeed;
		}
	}


	bullet->nBulletCount++;

}

//=============================================================================
// �o���b�g�p�^�[��03 �z�[�~���O�o���b�g�i���i�E�t�@���l���p�j
//=============================================================================
void SetBulletType03(int nBullet)
{
	BULLET *bullet = &bulletWk[nBullet];
	ENEMY *enemy;

	// �G�l�~�[����
	SetSearchEnemy(nBullet);

	// �z�[�~���O����
	if (bullet->nHomingFlag == 1)
	{
		bullet->nHomingFlag = 2;
		enemy = GetEnemy(bullet->nTarget);
		if (enemy->bUse)
		{
			bullet->vecTa.x = enemy->pos.x - bullet->pos.x;
			bullet->vecTa.y = enemy->pos.y - bullet->pos.y;

			// atan2�̃G���[�h�~
			if (bullet->vecTa.x == 0 && bullet->vecTa.y == 0)
			{
				bullet->vecTa.x += 0.00001;
			}

			// �p�x�v�Z
			bullet->fAngle = atan2(bullet->vecTa.y, bullet->vecTa.x);
		}
	}
	if (bullet->nHomingFlag == 2)
	{
		// �ړ��ʌv�Z
		bullet->move.x = cos(bullet->fAngle) * BULLET03_SPEED_MAX;
		bullet->move.y = sin(bullet->fAngle) * BULLET03_SPEED_MAX;
		// �ړ��ʓK�p
		bullet->pos.x += bullet->move.x;
		bullet->pos.y += bullet->move.y;
	}
	else
	{
		bullet->pos.x += BULLET03_SPEED_MAX;
	}
}

//=============================================================================
// �o���b�g�̃G�l�~�[����
//=============================================================================
void SetSearchEnemy(int nBullet)
{
	BULLET *bullet = &bulletWk[nBullet];
	ENEMY *enemy;
	PLAYER *player;

	// �G�l�~�[����
	player = GetPlayer(0);
	for (int i = 0; i < PLAYER_MAX; i++, player++)
	{
		if (player->bUse)
		{
			if (bullet->nHomingFlag == 0)
			{
				enemy = GetEnemy(0);
				float fDistanceMin = 0.0f;
				int nEnemyCount = 0;
				for (int j = 0; j < ENEMY_MAX; j++, enemy++)
				{
					// �g�p���Ă���G�l�~�[�����邩���m�F
					if (enemy->bUse)
					{
						// �����v�Z
						D3DXVECTOR3 temp = player->pos - enemy->pos;
						float fTempLengthSq = D3DXVec3LengthSq(&temp);

						// �ŏ������Z�o
						if (fTempLengthSq < fDistanceMin || fDistanceMin == 0.0f)
						{
							fDistanceMin = fTempLengthSq;
							bullet->nTarget = j;
						}
						bullet->nHomingFlag = 1;
						nEnemyCount++;
					}
					if (nEnemyCount == 0)
					{
						bullet->nHomingFlag = 3;
					}
				}
			}
			if (bullet->nHomingFlag == 2)
			{
				bullet->nHomingFlag = 1;
			}
		}
	}
	return;
}

//=============================================================================
// �o���b�g�̍ė��p����
//=============================================================================
void InitStatusBullet(int nBullet)
{
	BULLET *bullet = &bulletWk[nBullet];

	// �o���b�g�X�e�[�^�X�̏�����
	bullet->bUse = false;
	bullet->bTextureUse = false;

	bullet->pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ���W�f�[�^��������
	bullet->rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bullet->vecDestination = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	bullet->nCountAnim = 0;
	bullet->nPatternAnim = 0;
	bullet->nBulletType = 0;
	bullet->nBulletCount = 0;
	bullet->nAngleType = 0;
	bullet->nPatternHoming = 0;
	bullet->nHomingFlag = 0;
	bullet->nTarget = 0;

	bullet->vecTa = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bullet->nDirection = 0;

	bullet->fBulletSpeed = 0.0f;
	bullet->fAngle = 0.0f;

	return;
}

//=============================================================================
// �o���b�g01�擾�֐�
//=============================================================================
BULLET *GetBullet(int no)
{
	return(&bulletWk[no]);
}
