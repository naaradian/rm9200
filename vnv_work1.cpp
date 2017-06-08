//file : vnv_work1.cpp

typedef struct _AT91S_SPI {
	unsigned long	 SPI_CR; 	// Control Register
	unsigned long	 SPI_MR; 	// Mode Register
	unsigned long	 SPI_RDR; 	// Receive Data Register
	unsigned long	 SPI_TDR; 	// Transmit Data Register
	unsigned long	 SPI_SR; 	// Status Register
	unsigned long	 SPI_IER; 	// Interrupt Enable Register
	unsigned long	 SPI_IDR; 	// Interrupt Disable Register
	unsigned long	 SPI_IMR; 	// Interrupt Mask Register
	unsigned long	 Reserved0[4]; 	// 
	unsigned long	 SPI_CSR[4]; 	// Chip Select Register
	unsigned long	 Reserved1[48]; 	// 
	unsigned long	 SPI_RPR; 	// Receive Pointer Register
	unsigned long	 SPI_RCR; 	// Receive Counter Register
	unsigned long	 SPI_TPR; 	// Transmit Pointer Register
	unsigned long	 SPI_TCR; 	// Transmit Counter Register
	unsigned long	 SPI_RNPR; 	// Receive Next Pointer Register
	unsigned long	 SPI_RNCR; 	// Receive Next Counter Register
	unsigned long	 SPI_TNPR; 	// Transmit Next Pointer Register
	unsigned long	 SPI_TNCR; 	// Transmit Next Counter Register
	unsigned long	 SPI_PTCR; 	// PDC Transfer Control Register
	unsigned long	 SPI_PTSR; 	// PDC Transfer Status Register
} AT91S_SPI, *AT91PS_SPI;

   
#define AT91C_BASE_SPI       ((AT91PS_SPI) 	0xFFFE0000) // (SPI) Base Address
#define AT91C_PDC_RXTEN       ((unsigned int) 0x1 <<  0) // (PDC) Receiver Transfer Enable
#define AT91C_PDC_RXTDIS      ((unsigned int) 0x1 <<  1) // (PDC) Receiver Transfer Disable
#define AT91C_PDC_TXTEN       ((unsigned int) 0x1 <<  8) // (PDC) Transmitter Transfer Enable
#define AT91C_PDC_TXTDIS      ((unsigned int) 0x1 <<  9) // (PDC) Transmitter Transfer Disable
#define AT91C_SPI_PCS1_SERIAL_DATAFLASH		0xD     /* Chip Select 1 : NPCS1 %1101 */
#define AT91C_SPI_PCS         ((unsigned int) 0xF << 16) // (SPI) Peripheral Chip Select
#define AT91C_SPI_RXBUFF      ((unsigned int) 0x1 <<  6) // (SPI) RXBUFF Interrupt
#define AT91C_SPI_SPIEN       ((unsigned int) 0x1 <<  0) // (SPI) SPI Enable
#define AT91C_SPI_SPIDIS       ((unsigned int) 0x1 <<  1) // (SPI) SPI Disable

#define AT91C_SPI_PCS2_SERIAL_DATAFLASH		0xB     /* Chip Select 2 : NPCS2 %1011 */
#define AT91C_SPI_PCS3_SERIAL_DATAFLASH		0x7     /* Chip Select 3 : NPCS3 %0111 */

extern "C" char* SpiWriteReadCS3 ( unsigned long len, char * pData)
{
	   _at91rm9200_pio_set(AT91RM9200_PIO_PORT_A, 6, AT91RM9200_PIO_PERIPHERAL_A, 0);   //cs3
	   static char RxBuff[8];
//select needed cs:
	   AT91C_BASE_SPI->SPI_MR &= 0xFFF0FFFF;
	   AT91C_BASE_SPI->SPI_MR |= ((AT91C_SPI_PCS3_SERIAL_DATAFLASH<<16) & AT91C_SPI_PCS);

	   AT91C_BASE_SPI->SPI_CR = AT91C_SPI_SPIEN;
       AT91C_BASE_SPI->SPI_PTCR = AT91C_PDC_TXTDIS + AT91C_PDC_RXTDIS;
   
   	/* Initialize the Transmit and Receive Pointer */
    	AT91C_BASE_SPI->SPI_RPR =(unsigned long)RxBuff; //(unsigned int)pDesc->rx_cmd_pt ;
    	AT91C_BASE_SPI->SPI_TPR = (unsigned long)pData; //(unsigned int)pDesc->tx_cmd_pt ;

    	/* Intialize the Transmit and Receive Counters */
    	AT91C_BASE_SPI->SPI_RCR = len;//pDesc->rx_cmd_size;
    	AT91C_BASE_SPI->SPI_TCR = len; //pDesc->tx_cmd_size;
 
   	    AT91C_BASE_SPI->SPI_PTCR = AT91C_PDC_TXTEN + AT91C_PDC_RXTEN;
   
   		while(!(AT91C_BASE_SPI->SPI_SR & AT91C_SPI_RXBUFF));

   		AT91C_BASE_SPI->SPI_PTCR = AT91C_PDC_TXTDIS + AT91C_PDC_RXTDIS;
 		return RxBuff;
}




	   