//��������� ��������� �������� ������� KOM2 � DEC2
//#define ENCODER   //test
//#define  DECODER    //test 
// Need init!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

int nTS1[4] = {0,0,0,0}; // ����� TS1,TS2,TS3,TS4 ��� 1 ������  ::���� ������������� 4 TS ��� ������(nTS1-4)!=0  !!!
int nTS2[4] = {0,0,0,0}; // ����� TS1,TS2,TS3,TS4 ��� 2 ������  ::���� ������������� 4 TS ��� ������(nTS1-4)!=0  !!!
int n_line = 0;
int n_slot = 15;  
//int n_slot = 2;     //test decoder
//  ������������� ��� ������ 4 ������ E1
//int nTS1[4] = {4,5,6,7}; // ����� TS1,TS2,TS3,TS4 ��� 1 ������  ::���� ������������� 4 TS ��� ������(nTS1-4)!=0  !!!
//int nTS2[4] = {8,9,10,11}; // ����� TS1,TS2,TS3,TS4 ��� 2 ������  ::���� ������������� 4 TS ��� ������(nTS1-4)!=0  !!!
// n_line = 20;  //�� ���������

//  ������������� ��� ������ 3 ������ E1
//int nTS1[4] = {4,5,6,8}; // ����� TS1,TS2,TS3,TS4 ��� 1 ������  ::���� ������������� 4 TS ��� ������(nTS1-4)!=0  !!!
//int nTS2[4] = {9,10,12,13}; // ����� TS1,TS2,TS3,TS4 ��� 2 ������  ::���� ������������� 4 TS ��� ������(nTS1-4)!=0  !!!
// n_line = 20;  //�� ���������



//  ������������� ��� �������� 4 ������ E1
//int nTS1[4] = {4,5,6,7}; // ����� TS1,TS2,TS3,TS4 ��� 1 ������  ::���� ������������� 4 TS ��� ������(nTS1-4)!=0  !!!
//int nTS2[4] = {8,9,10,11}; // ����� TS1,TS2,TS3,TS4 ��� 2 ������  ::���� ������������� 4 TS ��� ������(nTS1-4)!=0  !!!
// n_line = 16;  //�� ���������

//  ������������� ��� �������� 3 ������ E1
//int nTS1[4] = {4,5,6,8}; // ����� TS1,TS2,TS3,TS4 ��� 1 ������  ::���� ������������� 4 TS ��� ������(nTS1-4)!=0  !!!
//int nTS2[4] = {9,10,12,13}; // ����� TS1,TS2,TS3,TS4 ��� 2 ������  ::���� ������������� 4 TS ��� ������(nTS1-4)!=0  !!!
// n_line = 16;  //�� ���������


//**************************************************************************************
//  ������ � ����� KOM2 � DEC2   
//  �������� ������(256,128,64,), ����� �����(4-43), ���������� TS (1-31)
//  ���������� :����� ������ �����,
//  ������������: 
//             - ����� �������� ����� n_slot
//             - ����� ������� ��������� TS  (nTS1[4] ��� nTS2[4]) 1 ��� 2 ������ ����� 
//               � ����������� �� �������� ��������� 4,2 ��� 1 TS
//             - ����� �����
//
//--------------------------------------------------------------------------------------
// adres matrix TS:
//
//               0:  BADR+n_slot*16+8(HIGH+LOW)
//               1:  BADR+n_slot*16+9(HIGH+LOW)
//               2:  BADR+n_slot*16+A(HIGH+LOW)     WINDOW = 0xf (��� ������ ������) 
//               3:  BADR+n_slot*16+B(HIGH+LOW)
//
//               matrix TS:  // ��������� 1 � ��������������� ������� ���������� ������ TS ��� ������
//               adr             bit 7    6    5    4    3    2    1    0       
//               08                  TS7  TS6  TS5  TS4  TS3  TS2  TS1  TS0   
//               09                  TS15 TS14 TS13 TS12 TS11 TS10 TS9  TS8
//               0A                  TS23 TS22 TS21 TS20 TS19 TS18 TS17 TS16
//               0B                  TS31 TS30 TS29 TS28 TS27 TS26 TS25 TS24
//               ---------------------  
// adres nLine   :   BADR+n_slot*16+0(HIGH+LOW)     LINE =0x0a  (��� ������ ������)
// 
//**************************************************************************************
//**************************************************************************************
#define EN_LINE        0x80
#define WINDOW         0x0f      //����� � "����"
#define NLINE1         0x0a      //����� �������� ������ ����� ������ 1 ��� KOM2,DEC2 
#define NLINE2         0x0b      //����� �������� ������ ����� ������ 2 ��� KOM2,DEC2 
#define SA             0x08      //����� ��������-�������������� �������� ������ 1  
#define SB             0x09      //����� ��������-�������������� �������� ������ 2  
#define STOP_KODER     0x10      //���������� ����� DSP33
#define SET_SPEED      0x20      //���������� �������� ������ 21=64K  24=128K  28=256K
#define PUSK_KODER     0x50      //��������� �����  

// ��� ������������� �������/���������:n_slot=15; 

void out_compare_ind(int bt1,int bt2);
// ������� ����� ������ �-� 0x500 �� 0x5ff
unsigned char RDBUS( unsigned int BADR,unsigned int SLOT,unsigned int ADR )  // FUNC FOR  READ DATA ON FLEX BUS
{	
  unsigned int busadr;      // shift on 4 - module selecktor
  unsigned int adr ;        // addr  of bus data window
  
  busadr=(SLOT*16) | 0x0500;      // shift on 4 - module selecktor
  adr = (busadr  | ADR);        // addr  of bus data window

  outportb(busadr | 0x001, BADR/256);      // set base H adr
  outportb(busadr , BADR);               // set base L adr
  return ( inportb( adr )); 
}

void WRBUS( unsigned int BADR,unsigned int SLOT,unsigned int ADR,unsigned char data )  // FUNC FOR  write DATA ON FLEX BUS
{
  unsigned int busadr;      // shift on 4 - module selecktor
  unsigned int adr ;        // addr  of bus data window

  busadr=(SLOT*16) | 0x0500;      // shift on 4 - module selecktor
  adr = (busadr  | ADR);        // addr  of bus data window

  outportb(busadr | 0x01, BADR/256);      // set base H adr
  outportb(busadr, BADR);               // set base L adr
  outportb( adr, data );	
}


void wr_set_zv(int n_chenal_zv,int n_line,int speedf)
{
 int i,a,a1;
 unsigned char b,b1;
 int nTS[4];
 unsigned char matrix[4];    // ������� ��������� TS 
 
for (i=0;i<4;i++)  //���������� � ����� 
  {
   if (n_chenal_zv==1) nTS[i]=nTS1[i];
   else nTS[i]=nTS2[i];  
   matrix[i]=0;  
  }

      //����������  ������� ������������ TS
      for (i=0;i<4;i++)
      {         
        //if (nTS[i]!=0) a=8+fmod(nTS[i],8); // high + low adress  
        if ((nTS[i]!=0)&&(nTS[i]<32))
         { 
          a=(int)(nTS[i]/8); //����� � �������  
          b=0x01;
          b=b<<(nTS[i]%8);                //data
          matrix[a]|=b;
         }
      }
      //������ ������� ������������ TS      
      if (n_chenal_zv==1)
      { 
        for (i=0;i<4;i++)
         {
          WRBUS((i+8),n_slot,WINDOW,matrix[i]);
          b=RDBUS((i+8),n_slot,WINDOW);
          //b=0x37;              //���� �� ������
          a=(int)(b);   
          a1=(int)matrix[i]; 
          if (b!=matrix[i]) out_compare_ind(a,a1);
         }   
       }
              
       else 
        { 
          for (i=0;i<4;i++) 
          { 
           WRBUS((i+12),n_slot,WINDOW,matrix[i]);
           b=RDBUS((i+12),n_slot,WINDOW);
           a=(int)(b);   
           a1=(int)matrix[i]; 
           if (b!=matrix[i]) out_compare_ind(a,a1);
          } 
        }   
      //������ ������ �����
      if (n_chenal_zv==1) 
       {   
        WRBUS(0,n_slot,NLINE1,(unsigned char)(n_line|EN_LINE));
        b=(RDBUS(0,n_slot,NLINE1))&0xBF;
        a=(int)(b);   
        a1=(int)(n_line|EN_LINE);
        if (b!=(unsigned char)(n_line|EN_LINE)) out_compare_ind(a,a1);
       }
      else 
       { 
        WRBUS(0,n_slot,NLINE2,(unsigned char)(n_line|EN_LINE));
        b=(RDBUS(0,n_slot,NLINE1))&0xBF;
        a=(int)(b);   
        a1=(int)(n_line|EN_LINE);  
        if (b!=(unsigned char)(n_line|EN_LINE)) out_compare_ind(a,a1);
        }


       // ����������� ������������� �� ��������� �������� 
       if (speedf==256) {a=3; b=0x08;}
       if (speedf==128) {a=1; b=0x04;}
       if (speedf==64)  {a=0; b=0x01;}
       if (n_chenal_zv==1)  WRBUS(0,n_slot,SA,(unsigned char)(a));
       else WRBUS(0,n_slot,SB,(unsigned char)(a));     
   
}


void out_compare_ind(int bt1,int bt2)
{        
   int i;
   char str1[5]={' ',' ',' ',' ',' '};     //������ ��� �������������� itoa  
   char str[25];

   
         for(i=0; i<25; i++) str[i]=0;
	 itoa(bt1,str1,10);
         str[0]=str1[0];
         str[1]=str1[1];
         str[3]=str1[2];
         str[4]=str1[3];

         //itoa(bt2,str1,10);
         //str[6]=str1[0];
         //str[7]=str1[1];
         //str[8]=str1[2];
         //str[9]=str1[3];

         //printf(str);  
//				 printf("bt1=%X bt2=%X",bt1,bt2);
}


void set_audio(int rate,int mode)
{

	if(rate)
	{
		nTS1[0]=4; nTS1[1]=5; nTS1[2]=6; nTS1[3]=7; 
		if(mode)
		{
			nTS2[0]=8; nTS2[1]=9; nTS2[2]=10; nTS2[3]=11; 
		}
		else
		{
			nTS2[0]=0; nTS2[1]=0; nTS2[2]=0;  nTS2[3]=0; 
		}
	}
	else
	{
		nTS1[0]=4; nTS1[1]=5; nTS1[2]=6; nTS1[3]=8; 
		if(mode)	
		{
			nTS2[0]=9; nTS2[1]=10; nTS2[2]=12; nTS2[3]=13; 
		}
		else	
		{
			nTS2[0]=0; nTS2[1]=0; nTS2[2]=0; nTS2[3]=0; 
		}
	}

#ifdef ENCODER
	n_line = 20;
#else
	n_line = 16;
#endif

	wr_set_zv(1,n_line,256);
	wr_set_zv(2,n_line,256);

}