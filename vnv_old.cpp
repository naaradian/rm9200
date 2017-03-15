#include "hello7.h"
#include "embisr.h"
#include <mqx.h>
#include <bsp.h>
#include "menu1.h"


void t2ms(unsigned long d)
{
 delay_mcs(d * 2000l);
}

extern unsigned char NeedWriteID;
extern "C" void SetNeedWriteDevId(void);
extern "C" unsigned char GetNeedWriteDevId(void);
extern "C" void ClearNeedWriteDevId(void);

	/*
#define ulevelsn15503_SIZE	  (58)	//summ of bytes LevelSN15503

struct LevelSN15503
{
unsigned short absoluteMse[9];
unsigned short normalizedMse[9];
unsigned short radialMse[9];
unsigned char reserv[4];
};

union uLevelSN15503
{
  LevelSN15503 levelsn15503;
  unsigned char byte[ulevelsn15503_SIZE];
};

#define uerrsn15503work_SIZE	  (94)	 //sum of bytes Errsn15503work

struct ErrSN15503Work
{
  unsigned long fecBlockCounter[9];//
  unsigned long fecUncorrectedBlock[9];	
  unsigned short counterSlip[9];
  unsigned char reserv[2];
  unsigned char lock1;
  unsigned char lock2;
 // unsigned char reserv[2];
};

union uErrSN15503Work
{
   ErrSN15503Work errsn15303work;
   unsigned char byte[uerrsn15503work_SIZE];
};

	  */

  /*
unsigned char power1, power2;  
unsigned char crcud;
						//__________________________________________
unsigned char ldeviceindex;
unsigned char ldeviceindex1;
unsigned char ldeviceindex2;
unsigned char ldeviceindex3;
unsigned char ldeviceindex4;
unsigned char ldeviceindex5;
unsigned char ldeviceindex6;
unsigned char ldeviceindex7;
unsigned char ldeviceindex8;


unsigned char lprot;

unsigned char lacmprofile;
unsigned char lislocal;

unsigned char lrx;
unsigned char ltx;



unsigned short lprofile2;



unsigned char lengineTable;
unsigned char lprofile;
unsigned short lmseTenthsVal;
unsigned char lldpcMantissaTenths;
unsigned char lldpcExponent;
unsigned char lcriteria;
unsigned char lnextProfile;

*/
	  /*
void SetGEth(unsigned char im, unsigned long eth)
{
// printfp("\n\r SetGEth");
// printfpd(" %ld", im);
// printfpd(" %ld", eth);


 unsigned char reg;
 reg = inportb(BLOCK_SWEEP1*(im + 1) + ETH_PORT);
 if(eth <= RATE_100M) {reg |= GETH_BIT;}
 else { reg &= ~(GETH_BIT);}
 outportb((BLOCK_SWEEP1*(im + 1) + ETH_PORT), reg);

}
  */
	/*
#define FILTER_DATA_LENGTH (2)	
#define ADDR_TX	(0x19)
#define ADDR_RX	(0x24)

//uLevelSN15503	 ulevelsn15503;
//uErrSN15503Work	 uerrsn15503work;

unsigned long ratesymbol_far;
	*/
unsigned long 	timer_restart;


#define  TIME_WAIT_RESTART (5000)	 //121004


void Check_restart()
{
if((timer_restart < time1) && (timer_restart))
{
timer_restart = 0;
dev_restart();
}

}
union u2uc
{
//p  unsigned u;
//unsigned u;
    unsigned short u;
	unsigned char uc[2];
};



//extern "C" void wr4_8(void)
//{
//write_xil_char(4, 0x8);
//}

extern unsigned char Modify5A(unsigned char byte);


struct MsgStatus
{
	unsigned char readyToSend : 1;
	unsigned char isRS232 : 1;
	unsigned char isRS485 : 1;
	unsigned char reserved : 5;
};

union UnMsgStatus
{
	MsgStatus msgStatus;
	unsigned char byte;
};

struct TOM // [TRС00MEK]
{
	unsigned char K : 1; // K - признак получения пакета адресатом, устанавливается в "1" при получении пакета адресатом;
	unsigned char E : 1; // E - бит ошибки в CRC, устанавливается в "1" если не сходится CRC;
	unsigned char M : 1; // M - бит монитора, устанавливаемый в "1" при проходе кадром "активного монитора";
	unsigned char reserved : 2;
	unsigned char C : 1; // R - признак сообщение из RS-485 (был запрос маркера)
	unsigned char R : 1; // C - устанавливается в "1" если это запрос компьютера подключенного к станции.
	unsigned char T : 1; // T - бит маркера; 
//	TOM() { reserved=0; T=R=C=M=E=K=0; }
};

union UnTOM
{
	unsigned char byte;
	TOM tom;
};

struct EmbMsg
{
	unsigned char dir;
	UnMsgStatus readyToSend;
	unsigned short counter;
	unsigned char body[270];
// Start/8	TOM/8	Cycle/8	AddrI/16	AddrS/16	Type/8	Length/16	 BODY/ Length	CRC/16	Blank/8
	unsigned char TOM()		{   return body[0]; 			}
	unsigned char Cycle()	{   return body[1]; 			}
	unsigned short AddrI()	{	return body[3]  + (body[2]<<8);}		// 2
	unsigned short AddrS()	{	return body[5]  + (body[4]<<8);}		// 2
	unsigned short AddrR()	{	return body[10] + (body[9]<<8);}		// 2
	void SetAddrI(unsigned short word) { body[3]=word&0xFF; body[2]=(word>>8)&0xFF;	}
	void SetAddrS(unsigned short word) { body[5]=word&0xFF; body[4]=(word>>8)&0xFF;	}
	void SetAddrR(unsigned short word) { body[10]=word&0xFF; body[9]=(word>>8)&0xFF;}

	void SetRS485() { UnTOM unTOM; unTOM.byte = body[0]; unTOM.tom.R=1; body[0] = unTOM.byte; }
	unsigned char IsRS485() { UnTOM unTOM; unTOM.byte = body[0]; if(unTOM.tom.R) return 1; return 0; }
	void SetType(unsigned char byte) { body[6]=byte; }
	void SetLength(unsigned short word) { if(IsRS485()) word+=2; body[8]=word&0xFF; body[7]=(word>>8)&0xFF;	}


	unsigned char Type()	{ return body[6]; }		// 1
	unsigned short Length() {	return body[8] + (body[7]<<8);	 }			// 2
	unsigned short FullSize(); 			// 2
//	unsigned CRC() {	if(Length()<256) return body[Length()+1] + (body[Length()]<<8);	else return 0; }
  //t	unsigned short CRC() {	if(Length()<256) return body[Length()+10] + (body[Length()+9]<<8);	else return 0; }
	unsigned short CRC() {	if(Length()<256) return body[Length()+12] + (body[Length() + 11]<<8);	else return 0; }
//??????????????????????? calccrc used 11 and 12

	unsigned char Body(int i) { if(IsRS485()) return body[i+11]; else return body[i+9]; }
	unsigned char BodyR(int i) { return body[i+11]; }

	void SetTOM(unsigned char byte) { body[0]=byte; }
	void SetCycle(unsigned char byte) { body[1]=byte; }


	void SetBody(int i, unsigned char byte) { if(IsRS485()) body[i+11]=byte; else body[i+9]=byte; }
	void SetBodyR(int i, unsigned char byte) { body[i+11]=byte; }

//	void SetCRC() { if(Length()<256) { body[Length()+1]=CalculateCRC()&0xFF; body[Length()]=(CalculateCRC()>>8)&0xFF; }

	void Init();
	unsigned short Add(unsigned char byte);
	unsigned short Used() { return counter; }
	unsigned short IsFree() { return 270-counter; }
	int short IsEnd();
	int short IsEndOfHeader();
	unsigned short ChkCRC();
	unsigned short CalcCRC();
	unsigned short ReCalcCRC();
	unsigned char IsReadyToSend() { return readyToSend.msgStatus.readyToSend; }	
	void SetReadyToSend(unsigned char i) { readyToSend.msgStatus.readyToSend=i; }
//	unsigned char IsRS485() { return readyToSend.msgStatus.isRS485; } 
//	void SetRS485(unsigned char i) { readyToSend.msgStatus.isRS485=i; } 
	unsigned char IsRS232() { return readyToSend.msgStatus.isRS232; } 
	void SetRS232(unsigned char i) { readyToSend.msgStatus.isRS232=i; } 
	unsigned char Dir() { return dir; }

	void SetDir(unsigned char d) { dir= d; } // dir = 1 пришел с West, dir=2 прищел с East

	void Copy(EmbMsg m);
};

void EmbMsg::Copy(EmbMsg m)
{
	for(int i=0; i<270; i++) body[i]=m.body[i];
} 

void EmbMsg::Init()
{
	counter=0;
  for(int i=0; i<270; i++) body[i]=0;
	readyToSend.msgStatus.readyToSend=0;
}

unsigned short EmbMsg::FullSize() 
{	
	if(Length()<256) return Length() + 13;	 
	else return counter;
}

unsigned short EmbMsg::Add(unsigned char byte)
{
  if(counter<270)
	{
		body[counter++]=byte;
		return 1;
	}
	else
	  return 0;
}

int short EmbMsg::IsEnd()
{
		if(counter>10)
			if(counter==Length()+13)
				return 1;
	return 0;
}

int short EmbMsg::IsEndOfHeader()
{
  if(counter==9) return 1;
	if(counter>9) return 2;
	return 0;
}


unsigned short EmbMsg::ChkCRC()
{
  int i;
	unsigned c=0, b=0;
		if(Length()<=256) 
		{
			for(i=0; i<Length()+11; i++) c += body[i];
			b = CRC();
 #ifdef DEBUG_LOOP_PRINT

			printfpd("\n\rc= %02X", c);	
			printfpd("b= %02X\n\r", b);	
 #endif
			if(b==c) return 1;
			else return 0;
		}
//	}
    return 1;
}

unsigned short EmbMsg::CalcCRC()
{
  int i;
	unsigned c=0;
		if(Length()<=256) 
		{
			for(i=0; i<Length()+11; i++) c += body[i];
			body[Length()+11]=(c>>8)&0xFF;
			body[Length()+12]=c&0xFF;
			return c;
		}
		else return 0;
} 
 
#define   EmbMsgBuffer_Size (32)
struct EmbMsgBuffer
{
    unsigned short BuffSize;
    unsigned short Head;
    unsigned short Tail;
	  EmbMsg Buff[EmbMsgBuffer_Size];
  public:
    void Init();
    void Add(EmbMsg&);
    void Get(EmbMsg&);
    unsigned short Used();
    unsigned short Free();
};

void EmbMsgBuffer::Init()
{
  BuffSize = EmbMsgBuffer_Size;
  Head = 0;
  Tail = 0;
}

void EmbMsgBuffer::Add(EmbMsg &msg)
{
	for(int i=0; i<msg.FullSize(); i++) Buff[Head].body[i] = msg.body[i];
	Head++;
  if(Head == BuffSize)
  {
   
   Head = 0;
   }
}

void EmbMsgBuffer::Get(EmbMsg &msg)
{
  if(++Tail < BuffSize) 
	{
		for(int i=0; i<msg.FullSize(); i++) msg.body[i] = Buff[Tail-1].body[i];
	}
	else
	{
		Tail = 0;
		for(int i=0; i<msg.FullSize(); i++) msg.body[i] = Buff[BuffSize-1].body[i];
	}
}

unsigned short EmbMsgBuffer::Used()
{
  int n = Head - Tail;

  if( n >= 0 )
  {
 //  printEthLongHex(Head);
   return n;
   }
  else
  {	 
  if(n == (BuffSize - 1))  {
#ifdef	ETH_DEBUG_ENABLED	
 //  printEthLongHex(0x99);
#endif	//ETH_DEBUG_ENABLED
   	 }
  return n+BuffSize;
  }
}

unsigned short EmbMsgBuffer::Free()
{
  int n = Tail - Head;
  if( n > 0 ) return n;
  else return n+BuffSize;
}
/////////////////////

#include "embmsg485.cpp"
//msg485______________________
#define   EmbMsg485Buffer_Size (16)
struct EmbMsg485Buffer
{
    unsigned short BuffSize;
    unsigned short Head;
    unsigned short Tail;
	  EmbMsg485 Buff[EmbMsg485Buffer_Size];
  public:
    void Init();
    void Add(EmbMsg485&);
    void Get(EmbMsg485&);
    unsigned short Used();
    unsigned short Free();
};

void EmbMsg485Buffer::Init()
{
  BuffSize = EmbMsg485Buffer_Size;
  Head = 0;
  Tail = 0;
}

void EmbMsg485Buffer::Add(EmbMsg485 &msg)
{
	for(int i=0; i<msg.FullSize(); i++) Buff[Head].body[i] = msg.body[i];
	Head++;
  if(Head == BuffSize)
  {
   
   Head = 0;
   }
}

void EmbMsg485Buffer::Get(EmbMsg485 &msg)
{
  if(++Tail < BuffSize) 
	{
		for(int i=0; i<msg.FullSize(); i++) msg.body[i] = Buff[Tail-1].body[i];
	}
	else
	{
		Tail = 0;
		for(int i=0; i<msg.FullSize(); i++) msg.body[i] = Buff[BuffSize-1].body[i];
	}
}

unsigned short EmbMsg485Buffer::Used()
{
  int n = Head - Tail;

  if( n >= 0 )
  {
 //  printEthLongHex(Head);
   return n;
   }
  else
  {	 
  if(n == (BuffSize - 1))  {
   	 }
  return n+BuffSize;
  }
}

unsigned short EmbMsg485Buffer::Free()
{
  int n = Tail - Head;
  if( n > 0 ) return n;
  else return n+BuffSize;
}


struct Emb2TypeVer
{
	unsigned short type;
	unsigned short softVer;
	unsigned short ctrlNumber;
	unsigned short ctrlYear;
	unsigned short ctrlVer1;
	unsigned short ctrlVer2;
	unsigned char signature_hardware[16];
	unsigned char signature_software[16];
};

union UnEmb2TypeVer
{
	Emb2TypeVer emb2TypeVer;
	unsigned char byte[44];
};

  /*


struct StateBMD155
{
	unsigned char state;  // Бит 0: "0" - остутсвтие связи с ППУ1, "1" - норма
									// Бит 1: "0" - остутсвтие связи с ППУ2, "1" - норма
									// Бит 1: "0" - остутсвтие связи ПИ, "1" - норма
	unsigned char state2;  // Состояние платы интерфейсов
	unsigned char ppu1_bytes[16];
	unsigned char ppu2_bytes[16];														// 34
	unsigned long count_no_correct_block1;									// 42
	unsigned long count_no_correct_block2;									// 46
	unsigned long count_no_correct_result;									// 50
	unsigned long count_notRS1;															// 54
	unsigned long count_notRS2;															// 58
	unsigned long count_block;															// 62
	unsigned char mod; // Состояние платы интерфейсов       // 63
	unsigned char dem1; // Состояние платы интерфейсов      // 64
	unsigned char dem2; // Состояние платы интерфейсов      // 65
	unsigned char state_dem1; // Состояние платы интерфейсов// 66
	unsigned char state_dem2; // Состояние платы интерфейсов// 67
	unsigned char statePI; // Состояние платы интерфейсов		// 68	
	unsigned char loopPI; // Состояние шлейфов							// 69
	unsigned char demPI; // Состояние демодуляторов					// 70
};

union UnStateBMD155
{
	StateBMD155 stateBMD155;
	unsigned char byte[72];
};

*/
   /*	
struct StatePUM
{
	unsigned char ver;						// 1   //0
	unsigned char reserv; 				// 2	   //1
	unsigned char reserv1;	 //my					// 1 //2
	unsigned char reserv2;	 //my						 //3
	unsigned long ulBlock;				// 6	 +2		  //4 5 6 7
	unsigned long ulErrOut;				// 10	 +2		 //8,9,10,11
	unsigned long ulErrAfterRS1;	// 14		 +2
	unsigned long ulErrAfterRS2;	// 18	    +2
	unsigned long ulErrBeforeRS1;	// 22	   +2
	unsigned long ulErrBeforeRS2;	// 26	   +2
	unsigned char state[16];			// 42	 +2
};

union UnStatePUM
{
	StatePUM statePUM;
	unsigned char byte[44];
};

*/

struct Command
{
	unsigned char chan;
	unsigned char command;
	unsigned char par;
	unsigned char done;
};

struct Emb2NetStat
{
	unsigned long selfPacketSend; // 4
	unsigned long selfPacketRecv; // 4
	unsigned long allPacketRecv;  // 4
	unsigned short requestMarker; // 2
	unsigned short genMarker;     // 2
	unsigned short highID;        // 2
	unsigned short buffModPd;        // 2
	unsigned short buffModPm;        // 2
	unsigned short buffTransPd;        // 2
	unsigned short buffTransPm;        // 2
	unsigned short buff232Pd;        // 2
	unsigned short buff232Pm;        // 2
	unsigned short markerTime; //2 
	unsigned char ready_transit; //1 
	unsigned char ready_mod; //1 
};

union UnEmb2NetStat
{
	Emb2NetStat emb2NetStat;
	unsigned char byte[32];
};

struct LtDiod
{
	unsigned char alarmIn1		 : 1;	
	unsigned char alarmSync1  : 1; 	
	unsigned char alarmLevel1 : 1; 
	unsigned char alarmBoard1 : 1; 
	unsigned char alarmIn2		 : 1; 
	unsigned char alarmSync2  : 1; 
	unsigned char alarmLevel2 : 1; 
	unsigned char alarmBoard2 : 1; 	
}; 

union UnLtDiod
{
	unsigned char byte;
	LtDiod ltDiod;
};

struct BmdState
{
	unsigned char alarmIn1		: 1; 
	unsigned char alarmSync1 : 1; 
	unsigned char alarmIn2   : 1; 
	unsigned char alarmSync2 : 1; 
	unsigned char reserv			: 4; 
}; 

union UnBmdState
{
	unsigned char byte;
	BmdState bmdState;
};
////////////////////////
 	EmbTimer embTimer;
////////////////////////

extern unsigned long time1;
unsigned long cntflag6;

 
void Callback0()
{
  time1++;
}
 
 extern	EmbTimerCallback embTimerCallback0;


EmbMsgBuffer rBuffEmbMsg;

		
	EmbMsgBuffer tBuffEmbMsgWest;
	EmbMsgBuffer tBuffEmbMsgEast;

	EmbMsg embMsg232;

//____________________________________________________________________________232e
#ifndef ETH_TRANZIT
EmbMsg embMsg232E;
#endif // ETH_TRANZIT
//____________________________________________________________________________232e
 EmbMsg embMsg485E;
 EmbMsg embMsgWest[MODEM_QUANTITY]; //101224 many channells to keep messages

//#ifdef ETH_TRANZIT

 EmbMsg embMsgEthTransitW;
 EmbMsg embMsgEthTransitE;
 EmbMsg embMsgWestE;	 //1223

 EmbMsgBuffer tBuffEmbMsgEthAll;
 EmbMsgBuffer tBuffEmbMsgEthAll1;

   
	EmbMsg485 embMsg485_1;
	EmbMsg485 embMsg485_2;

	EmbMsg485 embMsg485Request_1;
	EmbMsg485 embMsg485Request_2;

EmbMsg485Buffer tBuffEmbMsg485Request_1;
EmbMsg485Buffer tBuffEmbMsg485Request_2;


#ifdef RS485_MSG_BUFF
	   EmbMsgBuffer tBuffRS485;
	   unsigned long time_lastsend_rs485;
	   unsigned char flag_wait_rs485;
#endif

	EmbMsg embMsgEast;
	EmbMsg embMsgAns;
	EmbMsg *embMsgRequest;

	EmbRS232 embRS232;
	EmbRS485 embRS485;
#ifndef PROG_BMDN6MI   
   UnStateRRL unStateRRL;
#endif
   EmbMsg embMsg485;
  //	EmbSerialMD34AVTProv embSerialACT155;

	extern char ch;
	extern long f_len;
	extern unsigned char flagRequest;
	unsigned char stemp, serr=0xFF, crc_temp=0;
	extern unsigned long i;
	extern unsigned long time1old, time2old;
	extern unsigned char request1, request2;
	unsigned long /*time3Marker[MODEM_QUANTITY],*/ time3BlankTransit=0, time3BlankMod[MODEM_QUANTITY];
	extern unsigned long time1test;
	unsigned char markerWest[MODEM_QUANTITY], markerEast=0, ready_transit=0, ready_mod[MODEM_QUANTITY], dir=0; // 0 - "Transit->Mod", 1 - "Mod->Transit"
	unsigned char old_ready_transit=0, old_ready_mod[MODEM_QUANTITY]; // 0 - "Transit->Mod", 1 - "Mod->Transit"
	unsigned char delete_msgWest=0, delete_msgEast=0, recieveWest[MODEM_QUANTITY], recieveEast=0;
	extern unsigned short HighID, countSend, countRecv;
	extern unsigned long time3highID;
	extern char s1[25],s2[25];

 //	unsigned char far* bt;
    extern unsigned char * bt;

	extern unsigned short addr1;

	unsigned char send1[16];
	unsigned char send2[16];
	unsigned char err_ppu1; 
	unsigned char err_ppu2; 
	extern unsigned char byte;
	unsigned char  westByte, eastByte;

	extern unsigned char mode5A;
	unsigned char  mode5AWest[MODEM_QUANTITY], mode5AEast;
   	unsigned char mode5AUp1, mode5AUp2; 

//	unsigned char mode5A232E = 0;
	extern unsigned char mode5A485E;
	extern unsigned char mode5A485;

//________________________________________________________
	unsigned char modeA5West[MODEM_QUANTITY];
	TRBuffer<char,ACT_BUFFER_SIZE> embMsgWestR[MODEM_QUANTITY];
//________________________________________________________

	unsigned countUD1;
	unsigned countUD2;

	extern unsigned char cycle;

	extern unsigned char ttbb;
	extern unsigned char mtbb;
	unsigned long count_tr;
	unsigned long count_md;
	unsigned short err_tr;
	unsigned short err_md;

//	UnStateBMD155 unStateBMD155;
 //	UnStateBMD155 unStateBMD155p[MODEM_QUANTITY<<1];
//	UnStateBMD155 unStateBMD155p[MODEM_QUANTITY];
	extern UnEmb2TypeVer unEmb2TypeVer; 
//	UnStatePUM unStatePUM;
//	UnStatePUM unStatePUMp[MODEM_QUANTITY];
	UnEmb2NetStat unEmb2NetStat;

	long count_block;
	long count_no_correct_block1;
	long count_no_correct_block2;
	long count_no_correct_result;
	long count_notRS1;
	long count_notRS2;
	extern long err_tmp;

	extern int rrr;

	extern int i232;
	unsigned short aI, aS, aR;

	UnLtDiod unLtDiod;
	UnBmdState unBmdState;

	unsigned long send41, send42, received1, received2, good1, good2, bad1, bad2;		//t

#define TIME_WAITING_FAR_END	  (STATE_SCAN_PERIOD + 1000l)
#define		FAR_ERR_TRESHOLD	  (1000l) //for example errors from 5sec
#define PERIOD_MIN_MAX 	(10)
#define   NO_LOCK_LEVEL (-100)


#define TRANZIT_SEND_PERIOD (4500) //9 modems - *9



extern unsigned long ErrResSNMP;
extern unsigned long timeres;
extern unsigned char start_count;


union UL2UC
{
	unsigned long ul;
	unsigned char uc[4];
};

union UI2UC
{
	unsigned long ui;
//	unsigned char uc[2];
	unsigned char uc[4];
};

extern unsigned char * addrRAM;
extern unsigned long shift;
extern unsigned long len;
extern unsigned short temp_crc;

extern UL2UC ul2uc;
extern UI2UC ui2uc;

unsigned long sendboxes;
unsigned long receivedboxes;
unsigned long error_timer;
unsigned char current_channel;
unsigned long used_modems;
	 long err_tmp_prev1 = 0l;
    long err_tmp_prev3 = 0l;
    long err_tmp_prev4 = 0l;


extern "C" void Init_structs()
{
/*
 for(long ic = 0; ic < (MODEM_QUANTITY); ic++)
  {
	for(i=0; i<16; i++)
	{
   		unStateBMD155p[ic].stateBMD155.ppu1_bytes[i]=0;
		unStateBMD155p[ic].stateBMD155.ppu2_bytes[i]=0;
		unStateBMD155p[ic].stateBMD155.state=0;
	}

	unStateBMD155p[ic].stateBMD155.count_block=0;
	unStateBMD155p[ic].stateBMD155.count_no_correct_block1=0;
	unStateBMD155p[ic].stateBMD155.count_no_correct_block2=0;
	unStateBMD155p[ic].stateBMD155.count_no_correct_result=0;
	unStateBMD155p[ic].stateBMD155.count_notRS1=0;
	unStateBMD155p[ic].stateBMD155.count_notRS2=0;
	unStateBMD155p[ic].stateBMD155.demPI=0;
	unStateBMD155p[ic].stateBMD155.loopPI=0;
	unStateBMD155p[ic].stateBMD155.statePI=0;
//______________________________________________________

				unStatePUMp[ic].statePUM.ulErrOut 		  = 0;
				unStatePUMp[ic].statePUM.ulBlock 		  = 0; 
  				unStatePUMp[ic].statePUM.ulErrAfterRS1 	   = 0;
				unStatePUMp[ic].statePUM.ulErrBeforeRS1    = 0;
   }
   */
}
  
unsigned long RestartTestE;
unsigned long RestartTest;
unsigned char reqcounter[MODEM_QUANTITY];
unsigned char rescounter[MODEM_QUANTITY];


 unsigned char currentgetrezerv;	//current modem is on protection transmit
 unsigned char currenthaverezerv;	//current modem is on protection receive
 unsigned char currentrezerv;

#ifndef PROG_BMDN6MI
StatRez statrez[MODEM_QUANTITY];
#endif
unsigned long protection_mode;
unsigned long norma_status[MODEM_QUANTITY << 1];

unsigned long time_start_prt, time_rcv_req_to_get, time_end_prt;

unsigned long ans_correct, ans_correctr,ans_no_correct, ans_no_correctr;
unsigned short acmmask0;
unsigned long timer_config;
unsigned char currenttrunk;
unsigned char cur_err;
unsigned char  flag_trunk;
unsigned char OldStatus;
signed long farinplev1;
signed long farinplev2;
unsigned char pdpower1;
unsigned char pdpower2;
unsigned char deltapdpower1;
unsigned char deltapdpower2;

unsigned char flag_enable_operate_power1;
unsigned char flag_enable_operate_power2;
unsigned char operate_power_mode;
unsigned long try_counter1;
unsigned long try_counter2;
unsigned char power_modul;
unsigned long power_rate;
unsigned char flag_command_power; 

unsigned long modem_bytes_counter;
unsigned long transit_bytes_counter;
unsigned long modem_bytes_time;
unsigned long transit_bytes_time;
unsigned long  timeChannels;


unsigned long command_counter;

unsigned long txtrans, rxtrans, txmod, rxmod;
unsigned long txtransb, rxtransb;//, txmod, rxmod;
unsigned long txusart, rxusart;


unsigned char used_TCP;
unsigned long ver_api;

unsigned char send_keeper1, send_keeper2;
unsigned char  hot_restart;

unsigned long syntez_error_counter;
unsigned long pvg710_error_counter;
unsigned long flagproti;

#ifdef PROG_MD310_SAT

unsigned long SetACMCounter;
#endif

#ifdef IncEmbIndicator
 EmbIndicator embIndicator;
#endif

EmbRS232 embRS232S;
 unsigned long password_state;
 unsigned char key_enter_flag;
#ifdef USE_HTTP
unsigned long page_number;
unsigned long start_event;
#endif

unsigned long ReallyNumCfg[MAX_NUM_CFG1];

float errf;
float dataf;

double ethsend;
double ethreceived;
  extern "C" unsigned char EventToMenu1();

unsigned char acm_status;
unsigned char acm_status1;


unsigned char CON_IFSAT140;	//operate if block

unsigned char Er, Et;

unsigned char Ld0, Ld1;


unsigned long timescan;

extern unsigned char use_md310_snmp;
extern unsigned char no_high_freq_char;

float64 blocks, uncblocks;
float64 blocks6, uncblocks6;
float64 blocks7, uncblocks7;
float64 blocks8, uncblocks8;
float64 blocks9, uncblocks9;
float64 blocks10, uncblocks10;
float64 blocks11, uncblocks11;
float64   MEbN0_snmp;

 unsigned lost_mailboxes;


 unsigned cnt_bmdn;

unsigned char flagstartparseop;


extern "C" void Init_BMDN(void)
{  
 unsigned char chn; 
return;


  flagstartparseop = 1;

cnt_bmdn = 0;

// chn = SetSelectorToProv();
   SetSelector(SDMP);


  lost_mailboxes =0;



MEbN0_snmp = 0;
printfp("\n\r Init_BMDN();");
OperateBuffers_usart0t();

//ok return; //t

blocks = uncblocks = (float64)0l;
blocks6 = uncblocks6 = (float64)0l;
blocks7 = uncblocks7 = (float64)0l;
blocks8 = uncblocks8 = (float64)0l;
blocks9 = uncblocks9 = (float64)0l;
blocks10 = uncblocks10 = (float64)0l;
blocks11 = uncblocks11 = (float64)0l;

 Ld0 = 1;
 Ld1 = 1;

 Er = 0;
 Et = 0;

  //okreturn;
CON_IFSAT140 = 0;

oldflag_ifloop = 0x99;
oldflag_unmodul = 0x99;
oldflag_mrcntl = 0x99;
oldflag_alarms = 0;


acm_status = 1;  //t
acm_status1 = 1;  //t


ethsend = 0l;
ethreceived = 0l;

errf = 0.0;
dataf = 0.0;

//printfp("\n\r start  Init_web_prm();");
OperateBuffers_usart0t();
#ifdef USE_HTTP
Init_web_prm();
 start_event = 1;
#endif

//printfp("\n\r finish  Init_web_prm();");
OperateBuffers_usart0t();



password_state = 0;

key_enter_flag = 0;

  #ifdef PROG_MD310_SAT
  SetACMCounter = 0;
 //printfp("\n\r  INIT");
#endif




 flagproti  = 1;
 syntez_error_counter = 0;
 pvg710_error_counter = 0;

  hot_restart = 0;
  txusart = rxusart = 0;
  send_keeper1 = send_keeper2 = 1;


used_TCP = 0;

txtrans = rxtrans =  txmod =  rxmod = 0;

txtransb = rxtransb = 0;


timeChannels = 0;
 modem_bytes_counter = 0;
 transit_bytes_counter = 0;
  modem_bytes_time = 0;
 transit_bytes_time = 0;


command_counter = 0;
power_modul = 0;
power_rate = 0;
flag_command_power = 0;
farinplev1 = -85;
farinplev2 = -85;

pdpower1 = 140;
pdpower2 = 140;
deltapdpower1 = 1;
deltapdpower2 = 1;
flag_enable_operate_power1 = 1;
flag_enable_operate_power2 = 1;
operate_power_mode = 1;
try_counter1 = 0;
try_counter2 = 0;

 OldStatus = 0x0F;
timer_restart = 0l;
 cur_err = 0;
 flag_trunk = 0;
 currenttrunk = 0;
#ifndef PROG_BMDN6MI
 trunk1.byte = 0;
 trunk2.byte = 0;
#endif
// power1 = 0;
// power2 = 0;


#ifndef PROG_BMDN6MI
unStateRRL.stateRRL.ver = 0x01;
unStateRRL.stateRRL.state = 0x01;
#endif

countUD1=0;
countUD2=0;

mode5AUp1 = 0;
mode5AUp2 = 0; 

oldflag = 0xff;
oldflag_prv = 0xff;
oldflag_prv1 = 0xff;
dev_status = 0x0;
acmmask0 = 0;
ans_correct = 0;
ans_correctr = 0;

ans_no_correct = 0;
ans_no_correctr = 0;

#ifdef PRINT_START
//printfp("\n\r Init_BMDN");
#endif
 time_start_prt = 0;
time_rcv_req_to_get = 0;
time_end_prt = 0;

//ok160219 return;

for(unsigned long im= 0; im < (MODEM_QUANTITY<<1); im++)
{
 norma_status[im] = 0; //ALARM_QUANTITY + 1; //0;
}
protection_mode = MODE_NO_PROT; //160523

currentgetrezerv = NO_MODEM;
currenthaverezerv = NO_MODEM;
currentrezerv = NO_MODEM;  //this make error

RestartTestE = 0;
RestartTest = 0;
// err_tmp_now = 0l;			 // need init!!!!!
 err_tmp_prev1 = 0l;
 err_tmp_prev3 = 0l;
 err_tmp_prev4 = 0l;


 current_channel = 0;
 error_timer = 0;
 sendboxes = 0;
 receivedboxes = 0;
 count_send = 0;
 count_res = 0;
 count_res_ok = 0;
 count_res_bad = 0;

  time1=0;
  flagRequest=0;
  serr=0xFF; crc_temp=0;
  i=0;
  time1old=0; time2old=0;
  request1=0; request2=0;
 // time3Marker=0; 
  time3BlankTransit=0;// time3BlankMod=0;
  time1test=0;
  /*markerWest=0;*/ markerEast=0; ready_transit=0; /*ready_mod=0; */ dir=0; // 0 - "Transit->Mod", 1 - "Mod->Transit"
  old_ready_transit=0;/* old_ready_mod=0;*/ // 0 - "Transit->Mod", 1 - "Mod->Transit"
  delete_msgWest=0; delete_msgEast=0; /*recieveWest=0;*/ recieveEast=0;
  HighID=0; countSend=0; countRecv=0;
  time3highID=0;
  mode5A=0;/* mode5AWest=0; */ mode5AEast=0; 

 for(long i = 0; i < MODEM_QUANTITY; i++)
 {
   recieveWest[i]=0;
   ready_mod[i]=0;
   modeA5West[i]=0;
   markerWest[i]=0;
   time3BlankMod[i]=0;
   mode5AWest[i]=0;
   old_ready_mod[i]=0;
  // time3Marker[i]=0;
  embMsgWestR[i].Init();
  // time3Marker[i]=0;
 // embMsgWestR[i].Init();
 reqcounter[i] = 0;
 rescounter[i] = 0;
 }


  cycle=0;

	ttbb=0;
	mtbb=0;
	count_tr=0;
	count_md=0;
	err_tr=0;
	err_md=0;
     
	rrr=0;

	tBuffEmbMsgWest.Init();
	tBuffEmbMsgEast.Init();
	tBuffEmbMsg485Request_1.Init();
	tBuffEmbMsg485Request_2.Init();
#ifdef ETH_TRANZIT
    rBuffEmbMsgE.Init();
	rBuffEmbMsgEast.Init();
	rBuffEmbMsgWest.Init();
#else
	rBuffEmbMsg.Init();
#endif //ETH_TRANZIT


#ifdef RS485_MSG_BUFF
	   tBuffRS485.Init();
	   time_lastsend_rs485 = 0;
	   flag_wait_rs485 = 0;
#endif //RS485_MSG_BUFF

  
	   
	embTimer.Init(10); // *0,1 ms темп следования прерываний от таймера
	embTimerCallback0.callback = &Callback0;
	embTimerCallback0.interval = 1; // вызов функции 1 раз за N срабатываний таймера
	embTimerCallback0.count = 0;
	embTimer.SetCallBack0(&embTimerCallback0);
	  


printfp("\n\r start modem init();");
OperateBuffers_usart0t();


	/*
	for(i=0; i<MODEM_QUANTITY<<1; i++)
	{
 		send1[i]=0;
		send2[i]=0;
		unStateBMD155.stateBMD155.ppu1_bytes[i]=0;
		unStateBMD155.stateBMD155.ppu2_bytes[i]=0;
		unStateBMD155.stateBMD155.state=0;
 	}
	*/
	  /*
	unStateBMD155.stateBMD155.count_block=0;
	unStateBMD155.stateBMD155.count_no_correct_block1=0;
	unStateBMD155.stateBMD155.count_no_correct_block2=0;
	unStateBMD155.stateBMD155.count_no_correct_result=0;
	unStateBMD155.stateBMD155.count_notRS1=0;
	unStateBMD155.stateBMD155.count_notRS2=0;
	unStateBMD155.stateBMD155.demPI=0;
	unStateBMD155.stateBMD155.loopPI=0;
	unStateBMD155.stateBMD155.statePI=0;

		*/

	unEmb2TypeVer.emb2TypeVer.type       = 0x0116;
 	unEmb2TypeVer.emb2TypeVer.softVer    = SOFT_VER;  //add suppourt protocol	rs232 from ethernet protocol 888
	unEmb2TypeVer.emb2TypeVer.ctrlNumber = SelfID();
	unEmb2TypeVer.emb2TypeVer.ctrlYear   = SelfYear();
	unEmb2TypeVer.emb2TypeVer.ctrlVer1   = SelfVer1();	//was 0
	unEmb2TypeVer.emb2TypeVer.ctrlVer2   = SelfVer2();	//was 0
	   /*
	for(i=0; i < ulevelsn15503_SIZE; i++)
	{
	  ulevelsn15503.byte[i] = 0;
	}

	for(i=0; i < uerrsn15503work_SIZE; i++)
	{
	  uerrsn15503work.byte[i] = 0;
	}
	  */

	write_nvram_char(RESTARTS_NVRAM_ADDRESS, (unEmb2TypeVer.emb2TypeVer.signature_hardware[15] + 1));
#ifdef PROG_BMDN6	//131227
#ifndef PROG_BMDN6MI


	bt = (unsigned char *)(NVRAM_BASE);
 #endif
#endif 
   embMsg232.Init();
   embMsg232E.Init();
   embMsg485E.Init();


	embMsgEast.Init();
	embMsgAns.Init();
	embMsgRequest = NULL;
    used_modems = 0;

   if(chn == CODE_WRONG) 	return;


  SetUsart0BaudRate(38400l);

unsigned long ir;

unsigned short mod_mask = 1;
unsigned char typemodem;

 if(!hot_restart)
  {
    delay_mcs(SYNT_SET_DELAY);	  //1 c ?
  }

Init_structs();
if( GetTestMode() != 0x8e) //do not restart rtcs only
{
if(!hot_restart)
  {
 wd_reset();
   wd_reset();
   }
 wd_reset();

   

}



 hot_restart = 0; // to be loading all in work
}





#define SCAN_PERIOD (10000) //10c
#define READ_ERRORS_PERIOD (333) //1c
  /*
 extern "C" void FillLock(unsigned char mod, unsigned char status)
{

 if(status)
 {
 switch(mod)
 {
  case 0 : uerrsn15503work.errsn15303work.lock1 |=  MASK_BIT_0; break;
  case 1 : uerrsn15503work.errsn15303work.lock1 |=  MASK_BIT_1; break;
  case 2 : uerrsn15503work.errsn15303work.lock1 |=  MASK_BIT_2; break;
  case 3 : uerrsn15503work.errsn15303work.lock1 |=  MASK_BIT_3; break;
  case 4 : uerrsn15503work.errsn15303work.lock1 |=  MASK_BIT_4; break;
  case 5 : uerrsn15503work.errsn15303work.lock1 |=  MASK_BIT_5; break;
  case 6 : uerrsn15503work.errsn15303work.lock1 |=  MASK_BIT_6; break;
  case 7 : uerrsn15503work.errsn15303work.lock1 |=  MASK_BIT_7; break;
  case 8 : uerrsn15503work.errsn15303work.lock2 |=  MASK_BIT_0; break;
  default : break;
 }
 }
 else
 {
 switch(mod)
 {
  case 0 : uerrsn15503work.errsn15303work.lock1 &=  ~MASK_BIT_0; break;
  case 1 : uerrsn15503work.errsn15303work.lock1 &=  ~MASK_BIT_1; break;
  case 2 : uerrsn15503work.errsn15303work.lock1 &=  ~MASK_BIT_2; break;
  case 3 : uerrsn15503work.errsn15303work.lock1 &=  ~MASK_BIT_3; break;
  case 4 : uerrsn15503work.errsn15303work.lock1 &=  ~MASK_BIT_4; break;
  case 5 : uerrsn15503work.errsn15303work.lock1 &=  ~MASK_BIT_5; break;
  case 6 : uerrsn15503work.errsn15303work.lock1 &=  ~MASK_BIT_6; break;
  case 7 : uerrsn15503work.errsn15303work.lock1 &=  ~MASK_BIT_7; break;
  case 8 : uerrsn15503work.errsn15303work.lock2 &=  ~MASK_BIT_0; break;
  default : break;
 }


 }

}

*/

signed long NMSE;
unsigned char LOCK;
#ifndef  CHECK_LOSS_MEM
#define QUICK_READ_ERRORS_PERIOD  (2)
//#define QUICK_READ_ERRORS_PERIOD  (100)
#else
#define QUICK_READ_ERRORS_PERIOD  (0)

#endif



#define	DISABLING_TIME	(10)

//_________________________________________________________quick

extern "C" unsigned char ReadingEnabled(unsigned char enabling)
{
 static unsigned long timer;

 if(!enabling) 
 {
 timer = time1;
 return 1;
 }
 else
 {
  if(timer > time1) timer = time1;
  if((time1 - timer) > DISABLING_TIME) 
  {
	return 1;
  }
  else return 0;
 }


  



}

#define UPDATE_ACM_COUNTERS_PERIOD	(2)
 

#define M_1_0  (1)
#define M_1_1  (2)
#define M_0_0  (0)
#define CLEAR_M  (0xf0)
#define MAX_MOD (9)
#define NO_TYPE (0)

#define RESET_DELAY (1000)
 
  unsigned char  RearrangeByte(unsigned char inpByte)
{
unsigned char mask = 0x80;
unsigned char outbyte = 0;
while(mask)
 {
   outbyte >>= 1;
  if(inpByte & mask)
  {
   outbyte += 0x80;
  }
   mask >>= 1;


 }
return outbyte;

}
#define  LED_CH		  (7)
#define  LED_A		  (8)
#define	 AWAR_BIT	  (0x2)
#define	 NORMA_BIT	  (0x1)
#define	 NORMA_BIT1	  (0x4)
#define	 TESTMOD_BIT  (0x2)
#define	 REMOTE_BIT	  (0x4)
#define	 STOR_AL_BIT  (0x1)

 
unsigned char oldflag; //need init
unsigned char oldflag2; //need init
unsigned char oldflag_prv;
unsigned char oldflag_prv1;
unsigned char dev_status;
unsigned char oldflag_ifloop;
unsigned char oldflag_unmodul;
unsigned char oldflag_mrcntl;
unsigned char oldflag_alarms;




 extern "C" void OperateLeds3()
{

}



#define  MAX_TIME_WITHOUT_LOCK (30000l) //30 sec
#define  MAX_TIMES_TRY_GET_LOCK	(6)

unsigned char * ExChangeSpi(unsigned long length_of_data, unsigned char * BufferData)
{
unsigned long do_not_hangt = 0xfff;

unsigned long lentmp;
unsigned char * BufferDataTmp;
static unsigned char ReadBuffer[MAX_SP_LEN];


 if((length_of_data > MAX_SP_LEN) || (!length_of_data)) return ReadBuffer;

write_xil_char(ADDR_STATUS, RESET_BIT);

lentmp = length_of_data;
BufferDataTmp =  BufferData;
while(lentmp--)
{

 write_xil_char(ADDR_DATA, * BufferDataTmp++);

}
write_xil_char(ADDR_STATUS, GO_BIT);

while(do_not_hangt--)
{
 if(!(read_xil_char(ADDR_STATUS) & GO_BIT)) break;
}

lentmp = length_of_data;
BufferDataTmp =  ReadBuffer;
while(lentmp--)
{
 * BufferDataTmp = read_xil_char(ADDR_DATA);
BufferDataTmp++;

}

return 	ReadBuffer;
}


void WriteSpiB(unsigned long length_of_data, unsigned char * BufferData)
{
unsigned long do_not_hangt = 0xfffl;

unsigned long lentmp;
unsigned char * BufferDataTmp;


 if((length_of_data > MAX_SP_LEN) || (!length_of_data)) return;

write_xil_char(ADDR_STATUS, RESET_BIT);

lentmp = length_of_data;
BufferDataTmp =  BufferData;
while(lentmp--)
{
 write_xil_char(ADDR_DATA, * BufferDataTmp++);
}
write_xil_char(ADDR_STATUS, GO_BIT);

while(do_not_hangt--)
{
 if(!(read_xil_char(ADDR_STATUS) & GO_BIT))
 {
 break;
 }
}

}

unsigned char * ReadSpiB(unsigned long length_of_data)
{
unsigned long do_not_hangt = 0xfff;

unsigned long lentmp;
unsigned char * BufferDataTmp;
static unsigned char ReadBuffer[MAX_SP_LEN];

 if((length_of_data > MAX_SP_LEN) || (!length_of_data))
 {
  return ReadBuffer;
 }

write_xil_char(ADDR_STATUS, RESET_BIT);

lentmp = length_of_data;
while(lentmp--)
{
 write_xil_char(ADDR_DATA, 0x7e);
}
write_xil_char(ADDR_STATUS, GO_BIT);

while(do_not_hangt--)
{
 if(!(read_xil_char(ADDR_STATUS) & GO_BIT)) break;
}

lentmp = length_of_data;
BufferDataTmp =  ReadBuffer;

while(lentmp--)
{
 * BufferDataTmp = read_xil_char(ADDR_DATA);
#ifdef PRINT_SPI_DATA
if(print_flag)
{
//printEthStringAdd(1,*BufferDataTmp);
}
#endif

BufferDataTmp++;

}
return 	ReadBuffer;
}



extern "C" unsigned char GetUsart0Data(unsigned char *pBuff)
{
if(embRS232.UsedReceive())
 {
  *pBuff = embRS232.Receive();
//  printf("\n\r > %02X",*pBuff);
  return 1;
 }
return 0;
}

extern "C" void BMDN()
 {
 return;

cnt_bmdn++;
 // if(SetSelectorToProv() == CODE_WRONG)	return;
   SetSelector(SDMP);

  Check_restart();

//__________________________________________________________________
//131227#ifndef PROG_MD310
#ifdef PROG_BMDN6	//131227
#ifndef PROG_BMDN6MI

bt = (unsigned char *)(NVRAM_BASE);

	unEmb2TypeVer.emb2TypeVer.signature_software[0] = *bt;
	unEmb2TypeVer.emb2TypeVer.signature_software[1] = *(bt+1);
	unEmb2TypeVer.emb2TypeVer.signature_software[2] = *(bt+2);
	unEmb2TypeVer.emb2TypeVer.signature_software[3] = *(bt+3);
	unEmb2TypeVer.emb2TypeVer.signature_software[4] = *(bt+4);
	unEmb2TypeVer.emb2TypeVer.signature_software[5] = *(bt+5);
	unEmb2TypeVer.emb2TypeVer.signature_software[6] = *(bt+6);
	unEmb2TypeVer.emb2TypeVer.signature_software[7] = *(bt+7);
	unEmb2TypeVer.emb2TypeVer.signature_software[8] = *(bt+8);
	unEmb2TypeVer.emb2TypeVer.signature_software[9] = *(bt+9);
	unEmb2TypeVer.emb2TypeVer.signature_softftre[10] = *(bt+10);
	unEmb2TypeVer.emb2TypeVer.signature_software[11] = *(bt+11);
	unEmb2TypeVer.emb2TypeVer.signature_software[12] = *(bt+12);
	unEmb2TypeVer.emb2TypeVer.signature_software[13] = *(bt+13);
	unEmb2TypeVer.emb2TypeVer.signature_software[14] = *(bt+14);
 //	unEmb2TypeVer.emb2TypeVer.signature_software[15] = *(bt+15); 
	unEmb2TypeVer.emb2TypeVer.signature_software[15] = *(bt+ETH_TRANZIT_ON_ADDRESS); 
#endif
#endif

   if(GetNeedWriteDevId())
		   {
	 //  	 printf("\n\r Write!!");
	 //t
			 WriteDevId();
			 ClearNeedWriteDevId();
		   }


static unsigned long periodcnt;
 periodcnt++;
 if(periodcnt > 1000)
{
  if((counter_restart_web_prog < time1) &&  flag_restart_web_prog) 
  {
  flag_restart_web_prog = 0;
  dev_restart1();
  }
  periodcnt = 0;
} 


  #include vnv_rem.c //100110

}

/*FUNCTION*-------------------------------------------------------------------
* 
* Function Name    : time_notify_core(void)
* Returned Value   : none
* Comments         :
*    This routine is used to port embisr to be called from timer isr
*END*----------------------------------------------------------------------*/

extern "C" void time_notify_core(void)	// called frequency = 1 ms
 {
 //hier need call EmbTimer::IsrXX for any exemplar, declared as type EmbTimer
    embTimer.IsrXX();
	TimerCounter ++;
   	TimerCounter1 ++;
#ifdef ETH_TRANZIT
 //	if(EthSendTimer) EthSendTimer--;
	EthReceiveTimer++; 
#endif // ETH_TRANZIT

	timeres++; 
     timer++;
 } 
extern "C" void emb_use_irq1()
{


}

extern "C" void emb_use_irq0()
{
 IntFlag |= INT0_FLAG;
#ifdef IRQ_LIMITED
 if(InterruptWatchDog < (unsigned long)INTERRUPT_WAIT)
 {
   InterruptWatchDog++;
#endif
   my_int_enable_irq0();
#ifdef IRQ_LIMITED
 }
#endif

}

//_____________________________________________________________________________
#ifndef PROG_BMDN6MI

#define a14 ab22  
#define a15 ab23
#define a16 ab24  
#define a17 ab25
#define a18 ab26  
#define a19 ab27

#define a20 ab29  
#define a21 ab28
#define a23 ab30
#define ac   aa



void StartTestTlf()
{

}

void TestTlf()
	{
 }

#endif // no PROG_BMDN6M

extern "C" void test_PU37_start()
{
 }
 unsigned char  rm[MODEM_QUANTITY], rmo[MODEM_QUANTITY], rtz,rtzo, tm[MODEM_QUANTITY], ttz, tup0, tup1;     
  unsigned int   merc[MODEM_QUANTITY], zerc,up0erc,up1erc;
  unsigned char rup0, rup0o,  rup1, rup1o;
  unsigned long rmc[MODEM_QUANTITY], tmc[MODEM_QUANTITY], rtzc,  ttzc, tup0c, rup0c, tup1c, rup1c;
 unsigned long PeriodCounter;

#define  SEND_CHAR_T (0xC3)

unsigned char irq_byte, irqm_byte;




//#ifdef PROG_BMD155
extern  "C" unsigned long TypeVer(void)
{
static unsigned long ret;
ret =  (unsigned long)unEmb2TypeVer.emb2TypeVer.type;
ret <<=16;
ret += (unsigned long)unEmb2TypeVer.emb2TypeVer.softVer;
//ret = 0x12345678;

//printfpd("\n\r TypeVer 0x%x", ret);
return ret;
}

extern  "C" unsigned long CtrlNumberS(void)
{
static unsigned long ret;
ret =  (unsigned long)unEmb2TypeVer.emb2TypeVer.ctrlYear;
ret <<=16;
ret += (unsigned long)unEmb2TypeVer.emb2TypeVer.ctrlNumber;
//ret = 0x12345678;
return ret;
}

extern  "C" unsigned long CtrlVerS(void)
{
static unsigned long ret;
ret =  (unsigned long)unEmb2TypeVer.emb2TypeVer.ctrlVer1;
ret <<=16;
ret += (unsigned long)unEmb2TypeVer.emb2TypeVer.ctrlVer2;
return ret;
}
/*

extern  "C" unsigned long BlockS(void)
{
static unsigned long ret;
ret =  unStatePUM.statePUM.ulBlock;
return ret;
}

extern  "C" unsigned long ErrOutS(void)
{
static unsigned long ret;
ret =  unStatePUM.statePUM.ulErrOut;
return ret;
}

extern  "C" unsigned long ErrAfterRS1S(void)
{
static unsigned long ret;
ret =  unStatePUM.statePUM.ulErrAfterRS1;
return ret;
}

extern  "C" unsigned long ErrAfterRS2S(void)
{
static unsigned long ret;
ret =  unStatePUM.statePUM.ulErrAfterRS2;
return ret;
}

extern  "C" unsigned long ErrBeforeRS1S(void)
{
static unsigned long ret;
ret =  unStatePUM.statePUM.ulErrBeforeRS1;
return ret;
}

extern  "C" unsigned long ErrBeforeRS2S(void)
{
static unsigned long ret;
ret =  unStatePUM.statePUM.ulErrBeforeRS2;
return ret;
}

extern  "C" unsigned long StateModemS(void)
{
static unsigned long ret;
ret =  unStatePUM.statePUM.state[4];
ret <<= 24;
ret =  unStatePUM.statePUM.state[2];
ret <<= 8;
 return ret;
}
*/
extern  "C" void SetTlfNumberO(unsigned char* data_ptr, unsigned long* data_len)
{
  unsigned char* bt = (unsigned char *)(NVRAM_BASE);
  unEmb2TypeVer.emb2TypeVer.signature_software[1] = (unsigned char)*data_ptr;
  *(bt+1) =   (unsigned char)*data_ptr;
  //Stephany19 = (unsigned char)*data_ptr;
}


 

//___________________________________________________________________________________
#ifndef PROG_BMDN6MI
char TestRing()
{
	return 0;
}

void StartRing()
{
// Ring();
}

#endif //no PROG_BMDN6M
#define MAX_RECEIVE (4)	

unsigned long count_send, count_res, count_res_ok, count_res_bad;
					

#define SEND_TIMEOUT (2)
 #ifndef PROG_BMDN6MI

extern "C" void EnablePhone(void)
{
	write_xil_char(SERV_CH, EN_SERV);
}
#endif
#define  MAX_SENDS_VAL (64)	 //19
#define  BUFF_SYNT_SIZE (6)
#define MAX_DIGIT_SIZE (2)

unsigned char ConvertASCII(unsigned char val)
{
 // printf(" _%02X", val);
 unsigned long ret;
 if(val <= 0x39) {ret = val - 0x30; //printf("-%X", ret);
 }
 else if(val <= 0x46)
 { ret = 10 + val - 0x41;//ABCDEF printf("+%X", ret);
 }
 else if((val == 0xD1) ||(val == 0xf1))
 { ret = 12;//rashe  С c
 }
  else if(val <= 0x66)
 { ret = 10 + val - 0x61;//abcdef printf("+%X", ret);
 }
   else if(val <= 0xC5)
 { ret = 10 + val - 0xc0;//rashe ABE
 }
   else if(val <= 0xE5)
 { ret = 10 + val - 0xE0;//rash abe
 }
	else
	{ret = 0;}



 return (unsigned char)ret;
}
 #define	 REQUEST_QUANTITY (3)
 #define DUMMY	(0)
unsigned char ScanTxtFilesNum[MAX_CFG_FILE_VARIANT];
unsigned lononSavedTxtFilesVal;
#define ETH_COMMAND_PORT (0x7f)
#define ETH_STATE_PORT   (0x7E)
#define  ZERO_REG (0)
#define  ZERO_REG_MOD (0x20)
#define  RELE_REG (0x12)
#define  INPUT_REG (0x13)


#ifndef PROG_BMDN6MI

void ReleTest()
{
 unsigned char receive1;
 static unsigned char test_char1;//, test_char1o;
  outportb(RELE_REG,test_char1);
  test_char1 <<= 1;
  if(!test_char1) test_char1 = 1;
  receive1 = inportb(INPUT_REG);
  printfpd("\n\r %02X",receive1);
  OperateBuffers_usart0t();
  wd_reset();
}

void BusTest()
{
 unsigned char receive1;
 static unsigned char test_char1, test_char1o;
 test_char1o = test_char1;
 outportb(ZERO_REG,test_char1++);
  receive1 = inportb(ZERO_REG);

 if(test_char1o != receive1)
 {
 printfp("\n\rloc error wait");
 printfpd(" %02X",test_char1o);
 printfp( "have");
 printfpd(" %02X",receive1);
  OperateBuffers_usart0t();

 }
 else
 {	
 printfp("\rTest 8...Ok");
 OperateBuffers_usart0t();

 }
	wd_reset();
}


void BusTestFar()
{
 unsigned char receive1;
 static unsigned char test_char1, test_char1o;
 test_char1o = test_char1;
 outportb(ZERO_REG_MOD,test_char1++);
 receive1 = inportb(ZERO_REG_MOD);

 if(test_char1o != receive1)
 {
 printfp("\n\r mod error wait");
 printfpd(" %02X",test_char1o);
 printfp( "have");
 printfpd(" %02X",receive1);
  OperateBuffers_usart0t();
 }
 else
 {	
 printfp("\rTest 9...Ok");
 OperateBuffers_usart0t();

 }
	wd_reset();
}




extern "C" void LoadReg_5C3F_2(unsigned char deviceIndex)
{
}

#endif
  #define E1000 (0x4)

extern unsigned char OldStatus;

 extern "C" void MaskIrq0()
{
//embSerialACT155.MaskAll();
}

extern "C" void UnMaskIrq0()
{
//embSerialACT155.UnMaskAll();
}

extern "C" void MaskReceive()
{
//embSerialACT155.MaskReceive();
}

extern "C" void UnMaskReceive()
{
//embSerialACT155.UnMaskReceive();
}
  extern "C" void test_PU37(void)
  {
  }

extern "C" void test_PU37_transit(void)
  {
  }

extern "C" void SetStartRezerv(void)
  {
  }

extern "C" char* GetDFESNMP(unsigned long* data_len)
{
   *data_len = 4;
  // return GetDFE();
   return "N/A";
}




