#ifndef _sound_h_
#define _sound_h_ 
extern "C" void set_audio(int ,int );
void WRBUS( unsigned int ,unsigned int ,unsigned int ,unsigned char );
void Init_sound(void);
void  itoa(long , char *, int );

extern int nTS1[4];// = {0,0,0,0}; // ����� TS1,TS2,TS3,TS4 ��� 1 ������  ::���� ������������� 4 TS ��� ������(nTS1-4)!=0  !!!
extern int nTS2[4];// = {0,0,0,0}; // ����� TS1,TS2,TS3,TS4 ��� 2 ������  ::���� ������������� 4 TS ��� ������(nTS1-4)!=0  !!!
extern int n_line;// = 0;
extern int n_slot;// = 15;


#define EN_LINE        0x80
#define WINDOW         0x0f      //����� � "����"
#define NLINE1         0x0a      //����� �������� ������ ����� ������ 1 ��� KOM2,DEC2 
#define NLINE2         0x0b      //����� �������� ������ ����� ������ 2 ��� KOM2,DEC2 
#define SA             0x08      //����� ��������-�������������� �������� ������ 1  
#define SB             0x09      //����� ��������-�������������� �������� ������ 2  
#define STOP_KODER     0x10      //���������� ����� DSP33
#define SET_SPEED      0x20      //���������� �������� ������ 21=64K  24=128K  28=256K
#define PUSK_KODER     0x50      //��������� �����  
#define GET_DELAY_TIME      0x40      //
#define SET_DELAY_TIME      0x80      //

#endif
