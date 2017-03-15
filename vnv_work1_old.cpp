//#include "pvg610_api.h"
 //_____________________________________________





extern "C" void ResetPult(void)
{
  AT91RM9200_PIO_REG_STRUCT_PTR  pio_ptr;
  pio_ptr = (AT91RM9200_PIO_REG_STRUCT_PTR) AT91RM9200_PIOA_BASE;
  _at91rm9200_pio_set(AT91RM9200_PIO_PORT_A, 20, AT91RM9200_PIO_PERIPHERAL_IO, 1);

   pio_ptr->SODR = MASK_BIT_20;
   delay_mcs(10);
   pio_ptr->CODR = MASK_BIT_20;
   delay_mcs(10);
   pio_ptr->SODR = MASK_BIT_20;

}





extern "C" void InvertBitOrdering(void)
{
  printfp(">>>>InvertBitOrdering");

// char Test[TEST_DATA_SIZE];
// char TestR[TEST_DATA_SIZE];
// char * pBuff1 = &TFTP_Buffer1[0];
 char * pBuff = &TFTP_Buffer[0];
 unsigned char ByteBuff;
 unsigned char ByteBuff1;

#ifndef	PROG_DMU6

  for(unsigned i = 0; i < XilSizeToDownloadD; i++)	 //need header only
#else
    for(unsigned i = 0; i <XilSizeToDownloadD_DMU6; i++)	 //need header only

#endif
 //  for(unsigned i = 0; i < TEST_DATA_SIZE; i++)
  {
   ByteBuff = *pBuff; // TFTP_Buffer1[i]  =  TFTP_Buffer[i];
   ByteBuff1 = 0;
   if(ByteBuff & MASK_BIT_0)  (ByteBuff1 |= MASK_BIT_7);
   if(ByteBuff & MASK_BIT_1)  (ByteBuff1 |= MASK_BIT_6);
   if(ByteBuff & MASK_BIT_2)  (ByteBuff1 |= MASK_BIT_5);
   if(ByteBuff & MASK_BIT_3)  (ByteBuff1 |= MASK_BIT_4);
   if(ByteBuff & MASK_BIT_4)  (ByteBuff1 |= MASK_BIT_3);
   if(ByteBuff & MASK_BIT_5)  (ByteBuff1 |= MASK_BIT_2);
   if(ByteBuff & MASK_BIT_6)  (ByteBuff1 |= MASK_BIT_1);
   if(ByteBuff & MASK_BIT_7)  (ByteBuff1 |= MASK_BIT_0);
   *pBuff++ = ByteBuff1;
  
 //  if(!(i % 16))
//   printfpd("\n\r %X >", i);
//   printfpd(" %02X", TFTP_Buffer[i]);

  }

  	//  write_dataflash (CFG_DATAFLASH_LOGIC_ADDR_CS1,(unsigned int)&Test[0],  TEST_DATA_SIZE);
  }

#define  MODUL_LEN	(6)
#define  TMODE_LEN	(23)
#define  CDTYPE_LEN (4)



typedef	unsigned long long __int64;

  //#include <cstdio>
//#include <cmath>
 
//using std::printf;
 
//#define PRECISION 1e-4
#define PRECISION 1e-5
 
//exp(x) = 1 - x + (x^2)/2!-(x^3)/3!....+(-1)^n*(x^n)/n!+.....
 
double my_exp( const double x )
{
    double dVal, dTemp;
    int nStep = 1;
    for( dVal = 1.0, dTemp = 1.0; fabs(dTemp) >= PRECISION ; ++nStep )
    {
        dTemp *= -x/nStep;
        dVal += dTemp;
    }
    return dVal;
}
 
extern "C" void check_exp()
{
   double d_xstart = 0.0, d_xend = 10.0, dX = 0.1;
 //  printf( "%12s\t%12s\n", "x", "exp^(-x)" );
   for( double x = d_xstart; x<=d_xend;x+=dX ){
  //   printf( "%12.5f\t%12.5f\n", x, my_exp(x) );
     printfpdv( "%12.5f",x );
	    printfpdv( " %12.5f\r\n",  my_exp(x) );
   }
 
  // std::system("pause >> null");
}


extern "C" float64 my_log(double x)
{

//natur log :

      double sum = 0;
  //      double x = 8; // ???? ???????? ????????
 
        if ( x >= 0 && x <= 2)
        {
                x -= 1;
 
            //    for ( int i = 1; i < 5000; i += 2 )
			    for ( int i = 1; i < 200; i += 2 )
                {
                        sum += (double)(pow(x,i)/(double)i - (double)pow(x,(i+1))/(double)(i+1));
                }
 
           //     ShowMessage(sum);
	   //	   printfpdv("( s1 : %8.4f)", sum);
        }
        else if ( x > 2 )
        {
                x = (x /(float64) (x - 1));
 
             //   for ( int i = 1; i < 1000; i ++ )
			    for ( int i = 1; i < 200; i ++ )
                {
                        sum += (double)1.0 /(double) ( i*pow(x,i) );
                }
 
               // ShowMessage(sum);
		   //	     printfpdv("( s2 : %8.4f)", sum);

        }
        else
        {
               // ShowMessage("??????? ???????????? ????????");
	 //	  	 printfpd("(my_log :Argument is wrong ):%f", x);
        }

   return sum / (float64)2.302585 ;

}



float my_pow(const float x, const float y)
{
    if(y == 0.0) return 1.0;
    if(y==1.0) return x;
    if(x <= 0.0) return 0.0;

 //	printfpdv("\n\r my_log(x) :%8.4f", my_log(x));
  // printfpdv("\n\r my_log(x)*y:%8.4f", my_log(x)*y);
 //   printfpdv("\n\r my_exp:%8.4f",my_exp(my_log(x) * y));
  //	printfpdv("\n\rargs_my_pow :%8.4f", 2.303 * my_log(x) * y);
//	printfpdv(" x :%8.4f", x);
  //	printfpdv(" y :%8.4f", y);



  //	  x *= -1.0;

    return my_exp(2.303 * my_log(x) * y);	 //lnx = 2.303 * logx
 //   return  my_log(x);	//test //lnx = 2.303 * logx
}
