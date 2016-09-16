//file bmdn4_work1.cpp



struct OperateProgramm
{
//unsigned long noise0;
//unsigned long noise1;

char		  noise0[8];
char		  noise1[8];	
unsigned char loop0set;
unsigned char loop0get;
unsigned char loop1set;
unsigned char loop1get;	  //20
unsigned char unmod0set;
unsigned char unmod0get;
unsigned char unmod1set;
unsigned char unmod1get;
unsigned char bbloop0set;
unsigned char bbloop0get;
unsigned char bbloop1set;
unsigned char bbloop1get;
unsigned char ifloop0set;
unsigned char ifloop0get;  //30
unsigned char ifloop1set;
unsigned char ifloop1get;
unsigned char lock0get;
unsigned char lock1get;
unsigned char temp[3];
unsigned char status;	  //38
unsigned char internalAgc0[4];
unsigned char externalAgcRegister0[4];
unsigned char internalAgc1[4];
unsigned char externalAgcRegister1[4];	   //54
unsigned char ModForSSset;
unsigned char ModForSSget;
//unsigned char tmp;	 //for even
unsigned char status1;
unsigned char empty;	  //58
unsigned char empty1;	
unsigned char endprint;		 // = 0

};


//OperateProgramm OperProg; //need init
unsigned char flagloop0, flagloop1, flagunmod0, flagunmod1;  //need init
unsigned char flagbbloop0, flagbbloop1;
unsigned char flagifloop0, flagifloop1, flagModForSS;
unsigned long timer_oper_prog;

//SetLoopi(unsigned char dev, unsigned char loop,unsigned long milli, unsigned char nearend, unsigned char trib)

extern "C" void InitOperProg()
{
OperateProgramm * pOperProg;
 pOperProg = (OperateProgramm *)OperateProg.Value;
 for(unsigned j = 0; j < TBUFF1_VALUE; j++)
 {
	OperateProg.Value[j] = '0';
 //	OperateProg.ChangingValue[j] = '0';

 }
 //pOperProg->ModForSSset = GetModForSS() ? '1' : '0'; //to do not set himself olweis zero!!!!
#ifndef PROG_MD310
 pOperProg->ModForSSset = (GetModForSS() + (GetModForSS1() << 1)) + 0x30;
#else
 pOperProg->ModForSSset = (0 + (GetModForSS1() << 1)) + 0x30;

#endif

}

#define OPER_POWER_BIT	(0x8)

extern "C" void ParseOperProg( )
{

//return; //t160624


 if(timer_oper_prog) timer_oper_prog--;
 char buffer[9];
 OperateProgramm * pOperProg;
 pOperProg = (OperateProgramm *)OperateProg.Value;
 unsigned char flagloop0710, flagloop1710;
// unsigned long timer_oper_prog;
unsigned char dev_status5 = 0x80;
unsigned char tw;
//  printfpd("(%02X) ", dev_status);
//  printfpd("[%02X] ", dev_status & 0xfe );


  // 	  printfpd(".%02X ", dev_status);

 // dev_status5 += (unsigned char)(dev_status & 0xfe); //duble first bit of dev_status
	 tw =  dev_status & 0x1;
 //	  printfpd(">%d ",tw);

	if(tw)
	 {
   //	 	printEthLongHex(dev_status);
 //   printfp("1");
	 	dev_status5 += 1;
	  }
   //	  else
 //	  {
	//     printfp("0");

	  
   //		printEthLongHex(dev_status+ 0x100);
	//   }
 flagloop0710 = 0;
 flagloop1710 = 0;
 //char Buff[7];
//   sprintf((char*)&pOperProg->noise0, "%8d",  GetNoise0());
// pOperProg->noise0 = (unsigned long)(Buff);
// sprintf((char*)&pOperProg->noise0, "%8d",  GetNoise0());
//   sprintf((char*)&pOperProg->noise1, "%8d",  GetNoise1());
// pOperProg->noise1 = (unsigned long)(Buff);

// sprintf((char*)&pOperProg->noise1, "%8d",  GetNoise1());
//  printfp("\n\rs");
//  printfp(OperateProg.Value);


//   printfp("\n\rf");

//printfp("-");
// printfpd("%02X",pOperProg->loop0set);

//ok return; //t
  

 if(pOperProg->loop0set != '0')
 {//printfp(" 1"); 
 if(!flagloop0){SetLoopi(0, PVG610_LOOPBACK_MODEM_E,0, 1,0); flagloop0 = 1;}}
 else  {// printfp(" 2"); 
 if(flagloop0){ SetLoopi(0, PVG610_LOOPBACK_NONE_E,0, 1,0); flagloop0 = 0;}}
 pOperProg->loop0get = flagloop0 ? '1' : '0';
 
 if(pOperProg->loop1set != '0') 
 {//printfp(" 3");
  if(!flagloop1){SetLoopi(1, PVG610_LOOPBACK_MODEM_E,0, 1,0); flagloop1 = 1;}}
 else  {//printfp(" 4");
  if(flagloop1){SetLoopi(1, PVG610_LOOPBACK_NONE_E,0, 1,0); flagloop1 = 0;}}
 pOperProg->loop1get = flagloop1 ? '1' : '0';


//ok return; //t

 if(pOperProg->unmod0set != '0')
 {//printfp(" 5");
  if(!flagunmod0){SetModuli(0, PVG610_TRANSMITTER_MODE_ONETONE_E, 0, 0); flagunmod0 = 1;}}
 else  {//printfp(" 6"); 
 if(flagunmod0){SetModuli(0, PVG610_TRANSMITTER_MODE_NORMAL_E, 0, 0); flagunmod0 = 0;}}
 pOperProg->unmod0get = flagunmod0 ? '1' : '0';

 if(pOperProg->unmod1set != '0')
 {//printfp(" 7");
  if(!flagunmod1){SetModuli(1, PVG610_TRANSMITTER_MODE_ONETONE_E, 0, 0); flagunmod1 = 1;}}
 else  {//printfp(" 8"); 
 if(flagunmod1){SetModuli(1, PVG610_TRANSMITTER_MODE_NORMAL_E, 0, 0); flagunmod1 = 0;}}
 pOperProg->unmod1get = flagunmod1 ? '1' : '0';

 if(pOperProg->bbloop0set != '0')
 {//printfp(" 9");
  if(!flagbbloop0){flagloop0710 = 1; flagbbloop0 = 1;}}
 else  {//printfp(" 10");
  if(flagbbloop0){ flagloop0710 = 1; flagbbloop0 = 0;}}
 pOperProg->bbloop0get = flagbbloop0 ? '1' : '0';

 if(pOperProg->bbloop1set != '0')
 {//printfp(" 11"); 
 if(!flagbbloop1){flagloop1710 = 1; flagbbloop1 = 1;}}
 else  {//printfp(" 12"); 
 if(flagbbloop1){ flagloop1710 = 1; flagbbloop1 = 0;}}
 pOperProg->bbloop1get = flagbbloop1 ? '1' : '0';

 if(pOperProg->ifloop0set != '0')
 {//printfp(" 13");
  if(!flagifloop0){flagloop0710 = 1; flagifloop0 = 1;}}
 else  {//printfp(" 14"); 
 if(flagifloop0){ flagloop0710 = 1; flagifloop0 = 0;}}

 pOperProg->ifloop0get = flagifloop0 ? '1' : '0';

 if(pOperProg->ifloop1set != '0')
 {//printfp(" 15");
  if(!flagifloop1){flagloop1710 = 1; flagifloop1 = 1;}}
 else  {//printfp(" 16");
  if(flagifloop1){ flagloop1710 = 1; flagifloop1 = 0;}}


 pOperProg->ifloop1get = flagifloop1 ? '1' : '0';


//ok return;

 if(flagloop0710) 
 {

#ifndef PROG_MD310_SATI	
 SetLoop710(0, flagbbloop0, flagifloop0);
#else
  
if(flagifloop0)
{
 MIfLoop.Value = 1;
 }
else
{
 MIfLoop.Value = 0;
}


  MIfLoop.ChangingValue =   MIfLoop.Value;

  UsedExp.State.Reg2.bit.MIfLoop = 1;//need use bit MIfLoop.Value == 0 ? flagloop0 = 1; :  flagloop0 = 0; break; //if loop
 
  UsedExp.State.Reg2.bit.WriteId = 1;  //160610 >>>it get to hanging!
 
  UsedExp.State.Reg2.bit.Some = 1;


#endif
// printfpd("\n\r bb: %d", flagbbloop0);
// printfpd(" if: %d", flagifloop0);

}

//wrong return;

 if(flagloop1710) 
 {
   SetLoop710(1, flagbbloop1, flagifloop1);
 }


sprintf((char*)buffer, "%8d",  GetNoise0());
for(unsigned j = 0; j < 8; j++)
{
 pOperProg->noise0[j] = buffer[j];
}

sprintf((char*)buffer, "%8d",  GetNoise1());
for(j = 0; j < 8; j++)
{
 pOperProg->noise1[j] = buffer[j];
}

  pOperProg->lock0get = GetLock0();
  pOperProg->lock1get = GetLock1();

#ifndef PROG_MD310_SATI	
sprintf((char*)buffer, "%3d",  (unsigned char)GetTemp());
#else
sprintf((char*)buffer, "%3d", GetTempSat());	 //temporary

#endif

for(j = 0; j < 3; j++)
{
 pOperProg->temp[j] =  buffer[j];
}

//______________________status
 if(!dev_status)
 {
  pOperProg->status = 1; //to do not have zero
 }
 else
 {
 pOperProg->status = dev_status;			 
 }

//printfpd("\n\r>%02X ", dev_status);//______________________status

sprintf((char*)buffer, "%4d",GetinternalAgc(0));

for(j = 0; j < 4; j++)
{
 pOperProg->internalAgc0[j] =  buffer[j];
}

sprintf((char*)buffer, "%4d",GetexternalAgcRegister(0));

for(j = 0; j < 4; j++)
{
 pOperProg->externalAgcRegister0[j] =  buffer[j];
}

sprintf((char*)buffer, "%4d",GetinternalAgc(1));

for(j = 0; j < 4; j++)
{
 pOperProg->internalAgc1[j] =  buffer[j];
}

sprintf((char*)buffer, "%4d",GetexternalAgcRegister(1));

for(j = 0; j < 4; j++)
{
 pOperProg->externalAgcRegister1[j] =  buffer[j];
}
#ifndef PROG_MD310
pOperProg->ModForSSget = (GetModForSS() + (GetModForSS1() << 1)) + 0x30;
#else
pOperProg->ModForSSget = (0 + (GetModForSS1() << 1)) + 0x30;

#endif
//printfpd("-%02X-", pOperProg->ModForSSget); 
//printfpd(".%02X.", pOperProg->ModForSSset);  
//printfpd(",%02X,", flagModForSS);  

#ifndef PROG_MD310	    //bmdn6

#ifndef PROG_BMDN6M

if(pOperProg->ModForSSset == '1')	  //one trunk
 {//printfp(" 15");
  if((flagModForSS != 1)){
   //	printfp(" 17");
//#ifndef PROG_MD310
  SetModForSS1(0);
   SetModForSS(1); flagModForSS = 1;
//#endif   
   }
  }
  else if(pOperProg->ModForSSset == '0')				 //two trunks
   {//printfp(" 16");
  if(flagModForSS)
  {
  // printfp(" 18");
    SetModForSS1(0);
   SetModForSS(0); flagModForSS = 0;
   }
  }
   else if(pOperProg->ModForSSset == '2')				 //two trunks
   {//printfp(" 16");
  if(flagModForSS != 2)
  {
  // printfp(" 18");
   SetModForSS1(1);
   SetModForSS(0); flagModForSS = 2;

   }
  }

   else if(pOperProg->ModForSSset == '3')				 //two trunks
   {//printfp(" 16");
  if(flagModForSS != 3)
  {
  // printfp(" 18");
   SetModForSS1(1);
   SetModForSS(1); flagModForSS = 3;

   }
  }

#else //t150911 //BMDN6M	    as md310

// printEthLongHex(pOperProg->ModForSSset);
if(pOperProg->ModForSSset == '1')	  //one trunk
 {
// printfp(" 15");
  if((flagModForSS != 1)){
// 	printfp(" 17");
//#ifndef PROG_MD310
  SetModForSS1(0);
 //  SetModForSS(1); 
 flagModForSS = 1;
//#endif   
   }
  }
  else if(pOperProg->ModForSSset == '0')				 //two trunks
   {
//  printfp(" 16");
  if(flagModForSS)
  {
//   printfp(" 18");
    SetModForSS1(0);
  // SetModForSS(0); 
  flagModForSS = 0;
   }
  }
   else if(pOperProg->ModForSSset == '2')				 //two trunks
   {
//   printfp(" 19");
  if(flagModForSS != 2)
  {
 //  printfp(" 20");
   SetModForSS1(1);
 //  SetModForSS(0);
  flagModForSS = 2;

   }
   }
	  
   else if(pOperProg->ModForSSset == '3')				 //two trunks
   {
//   printfp(" 21");
  if(flagModForSS != 3)
  {
//   printfp(" 22");
   SetModForSS1(1);
 //  SetModForSS(1);
    flagModForSS = 3;

   }


  
  }




#endif //t150911	//BMDN6M




#else	  //md310


 // printEthLongHex(pOperProg->ModForSSset);
if(pOperProg->ModForSSset == '1')	  //one trunk
 {
// printfp(" 15");
  if((flagModForSS != 1)){
// 	printfp(" 17");
//#ifndef PROG_MD310
  SetModForSS1(0);
 //  SetModForSS(1); 
 flagModForSS = 1;
//#endif   
   }
  }
  else if(pOperProg->ModForSSset == '0')				 //two trunks
   {
//  printfp(" 16");
  if(flagModForSS)
  {
//   printfp(" 18");
    SetModForSS1(0);
  // SetModForSS(0); 
  flagModForSS = 0;
   }
  }
   else if(pOperProg->ModForSSset == '2')				 //two trunks
   {
//   printfp(" 19");
  if(flagModForSS != 2)
  {
 //  printfp(" 20");
   SetModForSS1(1);
 //  SetModForSS(0);
  flagModForSS = 2;

   }
   }
	  
   else if(pOperProg->ModForSSset == '3')				 //two trunks
   {
//   printfp(" 21");
  if(flagModForSS != 3)
  {
//   printfp(" 22");
   SetModForSS1(1);
 //  SetModForSS(1);
    flagModForSS = 3;

   }

  }
  
#endif


//  printfpd("_%02X ", dev_status5);

 if(!(GetModForSS())) {dev_status5 |= 0x6;} //set two bits
 else  {
 	tw =   1 << (currenttrunk + 1);
 dev_status5 |= tw;
 } 

if(GetModForSS1()) {dev_status5 |= OPER_POWER_BIT;} //operating power 
 
   
 // printfpd(":%02X ", dev_status);
 
//t pOperProg->status1 = dev_status1;
  pOperProg->status1 = dev_status5 + 0x80;
//  pOperProg->status1 = 0x81; //t
  pOperProg->empty = '2'; 
  pOperProg->empty1 = 0; 

 pOperProg->endprint = 0;
//	printfp("\n\r");
//    printfp(OperateProg.Value);

 /*
 sprintf((char*)&pOperProg->noise0, "%8d",  GetNoise0());
// pOperProg->noise0 = (unsigned long)(Buff);
// sprintf((char*)&pOperProg->noise0, "%8d",  GetNoise0());
 sprintf((char*)&pOperProg->noise1, "%8d",  GetNoise1());	  //last to not set zero in operating loop0
  */

// pOperProg->unmod1get = flagunmod1;

 if(flagstartparseop)
   {
    // printfp("\n\r flagstartparseop ");
     flagstartparseop = 0;
	 ClearNeedWriteDevId();
   }


}
  /*
extern "C" unsigned char* GetOperProg()
{
 return  (unsigned char*)&OperProg;
}
 */


 /*
extern "C" void FillDataOperProg(char deviceindex)
{
 char * pData;
 int i;
 char* pDataX;

 pDataX =  OperateProg.Value;

 pData =  (char *)(GetOperProg());
 for(i = 0; i < TBUFF1_VALUE; i++)
 {
  *pDataX++ = *pData++;
 }

}

 */



extern "C" void BlinkLed(void)
{
   AT91RM9200_PIO_REG_STRUCT_PTR pio_ptr1;
   pio_ptr1 = (AT91RM9200_PIO_REG_STRUCT_PTR) AT91RM9200_PIOC_BASE;
   static unsigned char led;
   uint_32         tg = 1<<13;

 if(led)
   {
   pio_ptr1->CODR = tg; //(1<<pin);
   led = 0;
  // TUTS_Output_Set(0);
  //  send485_enabled = 0;
   }
  else
   {
   led = 1;
   pio_ptr1->SODR = tg; //(1<<pin);
 //   send485_enabled = 1;
 //   TUTS_Output_Set(0xff);
   }

 }