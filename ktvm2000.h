#ifndef _ktvm2000_h_
#define _ktvm2000_h_ 

extern unsigned char en_sts;
extern short int cvbs_cnt;


/*
#define video_on     (0x01) // ������� �������� ������������
#define start_err    (0x02) // ������ ������������� ������
#define Fifo_full    (0x40) // ������ ������������� ������
#define stuff_err    (0x04) // ������  ������
#define VLD_off      (0x08) // ������  ������
#define video_int    (0x10) // ���������� �� ������������
#define start_ok     (0x20) // ����� ������
*/

void ConvertToWin1251(char *);
 /*
class EmbTreeTVM : public EmbTree
{
//port 	unsigned lastport;
	public:
  unsigned Inport(int port);// { return inport(port); }
  unsigned char Inportb(int port);// { return inportb(port); }
  void Outportb(int port, unsigned char value); //{ outportb(port,value); }
  unsigned GetParameterNum(); //port
  char *ViewParameter(char *);
  char *ViewComParameter(char *);
	int SetComParameter(char *);

};
  */
//port extern EmbTreeTVM  embTree;
extern EmbTree  embTree;
extern  EmbCommand embCommand2;
extern  EmbCommand embCommand3;
extern  void InitFreePtr(void);
extern "C" void ReadDPD(char * );
extern BYTE GetBitFromByte(BYTE , BYTE , BYTE );
extern void  ltoa(long , char *, int);
extern char HighHalfByte(char);
extern char LowHalfByte(char);
extern BYTE SetBitIntoByte(BYTE , BYTE , BYTE , BYTE );
//extern void EmbInit(void);

#endif
