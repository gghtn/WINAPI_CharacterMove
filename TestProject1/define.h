#pragma once

// �̱���
#define SINGLE(type)  private:\
							type();\
							~type();\
					  public:\
							static type* GetInst() {\
							static type mgr;\
							return &mgr;\
							}

// Ŭ���̾�Ʈ â ũ��
#define WINDOW_X		1200
#define WINDOW_Y		 500


#define ROAD			 300
#define TCOLOR			RGB(255,0,255)

// �߷°� ���� ����
#define GRAVITY			 3000
#define JUMP_HEIGHT		 600


#define MAX_POSX	WINDOW_X - (m_userBitmapSize.x - m_nEmpty)