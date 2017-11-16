
#define VNV_TANZIT_STATUS	(10)
#define VNV_MODEM_STATUS	(12)
#define VNV_MODEM_DATA		(11)
#define VNV_TRANZIT_DATA 	(9)



void EmbSerialPU_M::IsrXX() 
{
//printfp(".");
 unsigned char status_transit1;
 unsigned char status_transit2;
 UnEmbSerialPU_MIRQ irq,mask;
 unsigned long wd;  

 irq.byte  = inportb(0x505);
 mask.byte = inportb(0x506);

 status_transit1 = inportb(VNV_MODEM_STATUS);
 status_transit2 = inportb(VNV_TANZIT_STATUS);

//#ifdef TEST_PUM
//  printfpd("\n\r %02x", status.byte);
//   printfpd("\n\r 5: %02x", irq.byte);
  // printfpd("ms %02x", mask.byte);
//	OperateBuffers_usart1t();
  //	  printfp("I");

//#endif

 if(irq.bit.IRQ_TX_mod) 
 {
 	wd = 15;
	
	  while((status_transit1 & TX_READY_BIT) && wd && irq.bit.IRQ_TX_mod)
    {
	if(m_TBuffMod.Used())
	 { 
	 outportb(VNV_MODEM_DATA,m_TBuffMod.Get());
  //	  tmc++;
   	 }
	  else { mask.bit.IRQ_TX_mod=0; break;}
 
 	irq.byte  = inportb(0x505);
	wd--;
	status_transit1 = inportb(VNV_MODEM_STATUS);
   } //while
 }
 
	
 if(irq.bit.IRQ_TX_trans)
  {
 //  printfp(">");

   wd = 15;
   while((status_transit2 & TX_READY_BIT) && wd && irq.bit.IRQ_TX_trans)
   {
	 if(m_TBuffTransit.Used()) 
	 { 
	 outportb(VNV_TRANZIT_DATA,m_TBuffTransit.Get());
 	 } 
	  else { mask.bit.IRQ_TX_trans=0; break;}
    irq.byte  = inportb(0x505);
	wd--;
	status_transit2 = inportb(VNV_TANZIT_STATUS);
   }   //while
 }
 
 if(irq.bit.IRQ_RX_mod)
 {
	 wd = 128;
  	 while(irq.bit.IRQ_RX_mod && wd)
	 {
	 m_RBuffMod.Add(inportb(VNV_MODEM_DATA)); 
	 irq.byte  = inportb(0x505);
	 wd--;
	 }
  //	 mask.bit.IRQ_RX_mod=0;	   //temporary commented
    }
 

 if(irq.bit.IRQ_RX_trans)
 {
 //printfp("<");
   	wd = 128;
	while(irq.bit.IRQ_RX_trans && wd)
	{
	 m_RBuffTransit.Add(inportb(VNV_TRANZIT_DATA));
     irq.byte  = inportb(0x505);
	 wd--;
	}
//   mask.bit.IRQ_RX_trans=0;	   //temporary commented
 }
  //  printfpd("mf %02x", mask.byte);
  	outportb(0x506,mask.byte);
	count++;
}

 

  void EmbSerialPU_M::Init() 
{ 
	count=0;
	Empty(); 
	EmbIsrINT1::Init(); 
	UnEmbSerialPU_MIRQ mask;
	mask.byte = 0;//inportb(0x5A6);
	mask.bit.IRQ_RX_mod=1;
	mask.bit.IRQ_RX_trans=1;
  	outportb(0x506,mask.byte);
 printfpd("\n\r write init_ints mask-> 0x06 : %02X", mask.byte);
  mask.byte = inportb(0x506);
   printfpd("\n\r read init_ints mask-> 0x06 : %02X", mask.byte);

   	 
} 

void EmbSerialPU_M::AddMod(unsigned char byte)
{ 

	m_TBuffMod.Add(byte); 	
	UnEmbSerialPU_MIRQ mask;
	mask.byte = inportb(0x506);
	mask.bit.IRQ_TX_mod = 1;
	outportb(0x506,mask.byte);
}

void EmbSerialPU_M::AddModM(unsigned char byte)
{ 

	m_TBuffMod.Add(byte); 	
	UnEmbSerialPU_MIRQ mask;
	mask.byte = inportb(0x506);
	mask.bit.IRQ_TX_mod = 1;
	outportb(0x506,mask.byte);
}

void EmbSerialPU_M::AddTransit(unsigned char byte)
{ 

	m_TBuffTransit.Add(byte); 
	UnEmbSerialPU_MIRQ mask;
	mask.byte = inportb(0x506);
 //	printfpd("\n\r add transit read mask ->  %02X", mask.byte);
	mask.bit.IRQ_TX_trans = 1;
	outportb(0x506,mask.byte);
  //	printfpd("\n\r add transit write mask -> %02X", mask.byte);

}

void EmbSerialPU_M::AddTransitM(unsigned char byte)
{ 

	m_TBuffTransit.Add(byte); 
	UnEmbSerialPU_MIRQ mask;
	mask.byte = inportb(0x506);
	mask.bit.IRQ_TX_trans = 1;
	outportb(0x506,mask.byte);
}


void EmbSerialPU_M::AddUD1(unsigned char byte)
{
}

void EmbSerialPU_M::SetTransmitUD1()
{
}

void EmbSerialPU_M::SetTransmitUD2()
{
}



void EmbSerialPU_M::AddUD1M(unsigned char byte)
{
}


void EmbSerialPU_M::AddUD2(unsigned char byte)
{ 
}

void EmbSerialPU_M::AddUD2M(unsigned char byte)
{ 
}


void EmbSerialPU_M::ChangeReceive1() 
{
  UnEmbSerialPU_MIRQ mask;
  mask.byte = inportb(0x506);
  mask.bit.IRQ_RX_trans=1;
  mask.bit.IRQ_RX_mod=1;
  outportb(0x506,mask.byte);	//hier need add writing mask to every modem
 //	printfpd("\n\r ChangeReceive1 -> 0x06 : %02X", mask.byte);

}

void EmbSerialPU_M::ChangeReceive2() 
{
  UnEmbSerialPU_MIRQ mask;
  mask.byte = inportb(0x506);
  mask.bit.IRQ_RX_trans=1;
  mask.bit.IRQ_RX_mod=1;
  outportb(0x506,mask.byte);	//hier need add writing mask to every modem
}



