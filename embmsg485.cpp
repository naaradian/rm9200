//file : embmsg485.cpp

struct EmbMsg485
{
	unsigned char readyToSend;
	unsigned short counter;
	unsigned char body[64];

	unsigned char Addr()	{	return body[0];	 }
	unsigned char Length() {	return body[1];	 }
	unsigned short CRC() {	return body[body[1]+2]+1; }
	unsigned char Body(int i) { return body[i+2]; }

	void SetAddr(unsigned char byte) { body[0]=byte|0x10; }
	void SetLength(unsigned char byte) { body[1]=byte;	}
	void SetBody(int i, unsigned char byte) { body[i+2]=byte; }

	void Init();
	unsigned short Add(unsigned char byte);
	unsigned short Used() { return counter; }
	unsigned short IsFree() { return 64-counter; }
	int short IsEnd();
	unsigned short ChkCRC();
	unsigned short FullSize();
	unsigned short CalcCRC();

	unsigned char IsReadyToSend() { return readyToSend; }	
	void SetReadyToSend() { readyToSend=1; }
};

unsigned short EmbMsg485::FullSize() 
{	
	if(Length()<256) return Length() + 5;	 
	else return counter;
}


void EmbMsg485::Init()
{
	counter=0;
	readyToSend=0;
  for(int i=0; i<64; i++) body[i]=0;
}

unsigned short EmbMsg485::Add(unsigned char byte)
{
  if(counter<64)
	{
		body[counter++]=byte;
	}
	else
	  return 0;
}

int short EmbMsg485::IsEnd()
{

  #ifdef ETH_DEBUG_ENABLED
   //     printEthLongHex(counter + ((Length()+3) << 8));

//	  printEthStringAdd(0,0);
//	  printEthStringAdd(1,1);
//	  printEthStringAdd(2,0);
#endif
// printfpd("(c:%d)", counter);

  //if(counter>2)
#ifndef PROG_ODU1
#ifndef PROG_ODU4
	 	if(counter>=Length()+3)
#endif
#endif

#ifdef PROG_ODU4
	 	if(counter>=Length()+2)
#endif

#ifdef PROG_ODU1
	 	if(counter>=Length()+2)
#endif




		{
		 #ifdef ETH_DEBUG_ENABLED
  //      printEthLongHex(99);

//	  printEthStringAdd(0,0);
//	  printEthStringAdd(1,1);
//	  printEthStringAdd(2,0);
#endif


			return 1;
		}
	return 0;
} 

unsigned short EmbMsg485::ChkCRC()
{
	if(CRC()==CalcCRC()) return 1;
	else return 0;
}

unsigned short EmbMsg485::CalcCRC()
{
  int i;
	unsigned short c=0;
	if(Length()<64) 
	{
		for(i=0; i<Length()+2; i++) c += body[i];
		body[Length()+2]=c+1;
		return c+1;
	}
	else return 0;
} 
