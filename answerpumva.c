// file: answerpum.cpp
///////////////////////////////
///   answer  ///
///////////////////////////////

//________________________________________________________________________
 /*
#ifdef RS485_MSG_BUFF
		   if(flag_wait_rs485)
		   {
		   if(time1 < time_lastsend_rs485) 	time_lastsend_rs485 = time1;
		   if((time1 - time_lastsend_rs485) > RS485_TRANS_TIMEOUT)	flag_wait_rs485 = 0;
		   }


 			if(tBuffRS485.Used() && (!(flag_wait_rs485)) )	//090713
			{
			   flag_wait_rs485 = 1;
			   time_lastsend_rs485 = time1;
				EmbMsg embMsgA;
				embMsgA.Init();
				tBuffRS485.Get(embMsgA);
//- - - - - - - - - -

				embRS485.TransEC(0x55);	  //EC - RDN!!! in all
			  	embRS485.TransEC(0xAA);
				for(i=0; i<embMsgA.FullSize(); i++) 
							{
								switch(embMsgA.body[i])
								{
								case 0x5A: embRS485.TransEC(0x5A); embRS485.TransEC(0x00); break;
								case 0x55: embRS485.TransEC(0x5A); embRS485.TransEC(0x01); break;
								case 0xA5: embRS485.TransEC(0x5A); embRS485.TransEC(0x02); break;
								case 0xAA: embRS485.TransEC(0x5A); embRS485.TransEC(0x03); break;
								default: embRS485.TransEC(embMsgA.body[i]);
								}
							   //	RS485_receive_reset();
							}
						   
							embRS485.TransEC(0x55);
						   	embRS485.Trans_RDN(embMsgA.AddrS());
 

//- - - - - - - - - -




			}

#endif //RS485_MSG_BUFF
   */
//________________________________________________________________________




  			if(embMsg232.IsEnd())//&&embMsg.ChkCRC())
			{
            if(embMsg.ChkCRC())
				{
				  embMsgRequest = &embMsg232;
					flagRequest=1;
				}
            else
            {
             embMsg232.Init();
            }
            
      	}
//________________________________________________________________________232e
		  /*	
		     else if(embMsg232E.IsEnd())//&&embMsg.ChkCRC())
  			{
				{
			  //	  embMsgRequest = &embMsg232;
			  		embMsgRequest = &embMsg232E;
					flagRequest=5;	//new
				//	my_printf(0x20);   //t
				}
			}
         */
//________________________________________________________________________232e	
			else
			{
//#ifndef ETH_TRANZIT
/*
				if(rBuffEmbMsg.Used())
				{
				//	printf("1");
					EmbMsg embMsgA;
					 embMsgA.Init();	//my

					rBuffEmbMsg.Get(embMsgA);

					if(embMsgA.TOM()&0x01)
					{
						if(embMsgA.TOM()&0x20)
						{
							if(embMsgA.AddrS()==SelfID())//eee ?aaai 0000 eee FFFF
							{
											
								embRS232.Trans(0x55);
								embRS232.Trans(0xAA);
								for(i=0; i<embMsgA.FullSize(); i++) 
								{
									switch(embMsgA.body[i])
									{
									case 0x5A: embRS232.Trans(0x5A); embRS232. Trans(0x00); break;
									case 0x55: embRS232.Trans(0x5A); embRS232. Trans(0x01); break;
									case 0xA5: embRS232.Trans(0x5A); embRS232. Trans(0x02); break;
									case 0xAA: embRS232.Trans(0x5A); embRS232. Trans(0x03); break;
									default: embRS232. Trans(embMsgA.body[i]);
									}
								}	//for
								embRS232. Trans(0x55);
							 //	embRS232.Trans_RDN(COMP_DEF_MAC_END);
							//	embRS232.Trans_RDN_Full(embRS232.HostMAC);	

								flagRequest = 0;
							}
						}
					}
					else
					{
						if(embMsgA.AddrI()!=embMsgA.AddrS())
						{
							if(embMsgA.AddrS()==SelfID())
							{
								flagRequest=2;
								embMsgRequest = &embMsgA;
							}
						}
					}
				}  //buf
            */
            /*
#else 	//ETH_TRANZIT

//=================================================================================
				if(rBuffEmbMsgEast.Used())
				{
					EmbMsg embMsgA;
					 embMsgA.Init();	//my

					rBuffEmbMsgEast.Get(embMsgA);
#ifndef ANSWER_OLWAIS
					 if(buff_cashe_request.compare((unsigned long)embMsgA.body[1], (unsigned long)embMsgA.AddrS(), (unsigned long)embMsgA.AddrI(), (unsigned long)embMsgA.AddrR(), (unsigned long)embMsgA.IsRS485()) != 1)
#else  //ANSWER_OLWAIS
   			   	  	 if(1)
#endif //ANSWER_OLWAIS
   			   		{
#ifndef ANSWER_OLWAIS
   	   	 	  	  	buff_cashe_request.add(embMsgA.body[1], embMsgA.AddrS(), embMsgA.AddrI(), embMsgA.AddrR());
#endif //ANSWER_OLWAIS

				 //	   printf(" %02X", embMsgA.TOM());

				 	if(embMsgA.TOM()&0x01)
				//	if(1)	//t
					{
				 //	 printf(" p2");

						if(embMsgA.TOM()&0x20)
						{
				   //		 printf(" p3");

							if(embMsgA.AddrS()==SelfID())//eee ?aaai 0000 eee FFFF
							{  
					  //		 printf(" p4");
//______________________________________________________________________
//_________________________________________________________________________
//______________________________________________________________________________
 //my_int_disable();	//t
						embRS232.Trans(0x55);
						embRS232.Trans(0xAA);
						for(i=0; i<embMsgA.FullSize(); i++) 
						{
							switch(embMsgA.body[i])
							{
								case 0x5A: embRS232.Trans(0x5A); embRS232.Trans(0x00); break;
								case 0x55: embRS232.Trans(0x5A); embRS232.Trans(0x01); break;
								case 0xA5: embRS232.Trans(0x5A); embRS232.Trans(0x02); break;
								case 0xAA: embRS232.Trans(0x5A); embRS232.Trans(0x03); break;
								default: embRS232.Trans(embMsgA.body[i]);
							}
						}
						embRS232.Trans(0x55);

 //  my_int_enable();

//#endif	 // NOT CAN_ETHERNET_ASU
//___________________________________________________________________________________




								flagRequest = 0;
							}  //embMsgA.AddrS()==SelfID()
						}	//embMsgA.TOM()&0x20
					}		//(embMsgA.TOM()&0x01)
					else
					{	
				//	   	 printf(" p5");

						if(embMsgA.AddrI()!=embMsgA.AddrS())
						{
					//  	 printf(" p6");

							if(embMsgA.AddrS()==SelfID())
							{
					 //  	  	  printf(" p7");
					  	

								flagRequest=2;
								embMsgRequest = &embMsgA;

				   	//		for(i=0; i<embMsgRequest->FullSize(); i++) 
				   	  //		{
				   	 	//	   printf(" %02X",	embMsgRequest->body[i]);
				   	   //		}
 	   	 		   	  //		printf("\n\rCRC : %X CalcCRC : % X", embMsgRequest->CRC(), embMsgRequest->CalcCRC());

							}
						}  //embMsgA.AddrI()!=embMsgA.AddrS()
					}  //else	embMsgA.TOM()&0x01
					}
				}	//rBuffEmbMsg.Used()
//=================================================================================
//=================================================================================
			   else // 090115
			 	if(rBuffEmbMsgWest.Used())
				{
					EmbMsg embMsgA;
					 embMsgA.Init();	//my

					rBuffEmbMsgWest.Get(embMsgA);
#ifndef ANSWER_OLWAIS
					 if(buff_cashe_request.compare((unsigned long)embMsgA.body[1], (unsigned long)embMsgA.AddrS(), (unsigned long)embMsgA.AddrI(), (unsigned long)embMsgA.AddrR(), (unsigned long)embMsgA.IsRS485()) != 1)
#else  //ANSWER_OLWAIS
   			   	  	 if(1)
#endif //ANSWER_OLWAIS
   			   		{
#ifndef ANSWER_OLWAIS
   	   	 	  	  	buff_cashe_request.add(embMsgA.body[1], embMsgA.AddrS(), embMsgA.AddrI(), embMsgA.AddrR());
#endif //ANSWER_OLWAIS

				 //	   printf(" %02X", embMsgA.TOM());

				 	if(embMsgA.TOM()&0x01)
				//	if(1)	//t
					{
				//	 printf(" p2");

						if(embMsgA.TOM()&0x20)
						{
				  //		 printf(" p3");

							if(embMsgA.AddrS()==SelfID())//eee ?aaai 0000 eee FFFF
							{  
					 //		 printf(" p4");
//______________________________________________________________________
#ifdef CAN_ETHERNET_ASU
											
								embRS232.TransEC(0x55);
								embRS232.TransEC(0xAA);
								for(i=0; i<embMsgA.FullSize(); i++) 
								{
									switch(embMsgA.body[i])
									{
									case 0x5A: embRS232.TransEC(0x5A); embRS232.TransEC(0x00); break;
									case 0x55: embRS232.TransEC(0x5A); embRS232.TransEC(0x01); break;
									case 0xA5: embRS232.TransEC(0x5A); embRS232.TransEC(0x02); break;
									case 0xAA: embRS232.TransEC(0x5A); embRS232.TransEC(0x03); break;
									default: embRS232.TransEC(embMsgA.body[i]);
									}
								}
								embRS232. Trans(0x55);
							 //	embRS232.Trans_RDN(COMP_DEF_MAC_END);
								embRS232.Trans_RDN_Full(embRS232.HostMAC);	
#else	// NOT CAN_ETHERNET_ASU
//_________________________________________________________________________
//______________________________________________________________________________
 //my_int_disable();	//t
						embRS232.Trans(0x55);
						embRS232.Trans(0xAA);
						for(i=0; i<embMsgA.FullSize(); i++) 
						{
							switch(embMsgA.body[i])
							{
								case 0x5A: embRS232.Trans(0x5A); embRS232.Trans(0x00); break;
								case 0x55: embRS232.Trans(0x5A); embRS232.Trans(0x01); break;
								case 0xA5: embRS232.Trans(0x5A); embRS232.Trans(0x02); break;
								case 0xAA: embRS232.Trans(0x5A); embRS232.Trans(0x03); break;
								default: embRS232.Trans(embMsgA.body[i]);
							}
						}
						embRS232.Trans(0x55);

 //  my_int_enable();

#endif	 // NOT CAN_ETHERNET_ASU
//___________________________________________________________________________________




								flagRequest = 0;
							}  //embMsgA.AddrS()==SelfID()
						}	//embMsgA.TOM()&0x20
					}		//(embMsgA.TOM()&0x01)
					else
					{	
					   //	 printf(" p5");

						if(embMsgA.AddrI()!=embMsgA.AddrS())
						{
					  //	 printf(" p6");

							if(embMsgA.AddrS()==SelfID())
							{
						  //	  printf(" p7");

								flagRequest=7;
								embMsgRequest = &embMsgA;
							}
						}  //embMsgA.AddrI()!=embMsgA.AddrS()
					}  //else	embMsgA.TOM()&0x01
				  }	//cashe
				}	//rBuffEmbMsg.Used()
//=================================================================================

//=================================================================================
//#ifdef ETH_TRANZIT
 				else // 090115
			   	if(rBuffEmbMsgE.Used())
				{
					EmbMsg embMsgA;
					 embMsgA.Init();	//my

					rBuffEmbMsgE.Get(embMsgA);

#ifndef ANSWER_OLWAIS
					 if(buff_cashe_request.compare((unsigned long)embMsgA.body[1], (unsigned long)embMsgA.AddrS(), (unsigned long)embMsgA.AddrI(), (unsigned long)embMsgA.AddrR(), (unsigned long)embMsgA.IsRS485()) != 1)
#else  //ANSWER_OLWAIS
   			   	  	 if(1)
#endif //ANSWER_OLWAIS
   			   		{
#ifndef ANSWER_OLWAIS
   	   	 	  	  	buff_cashe_request.add(embMsgA.body[1], embMsgA.AddrS(), embMsgA.AddrI(), embMsgA.AddrR());
#endif //ANSWER_OLWAIS

			   	 //   printf(" p0");

				 //	   printf(" %02X", embMsgA.TOM());

				 	if(embMsgA.TOM()&0x01)
				//	if(1)	//t
					{
				//	 printf(" p2");

						if(embMsgA.TOM()&0x20)
						{
				 // 		 printf(" p3");

							if(embMsgA.AddrS()==SelfID())//eee ?aaai 0000 eee FFFF
							{  
				  //	 		 printf(" p4");
//______________________________________________________________________
#ifdef CAN_ETHERNET_ASU
											
								embRS232. Trans(0x55);
								embRS232. Trans(0xAA);
							//	printf("\n\r");
								for(i=0; i<embMsgA.FullSize(); i++) 
								{
									switch(embMsgA.body[i])
									{
							   //		 printf(" %02X",embMsgA.body[i]);

									case 0x5A: embRS232. Trans(0x5A); embRS232. Trans(0x00); break;
									case 0x55: embRS232. Trans(0x5A); embRS232. Trans(0x01); break;
									case 0xA5: embRS232. Trans(0x5A); embRS232. Trans(0x02); break;
									case 0xAA: embRS232. Trans(0x5A); embRS232. Trans(0x03); break;
									default: embRS232. Trans(embMsgA.body[i]);
									}
								}
								embRS232. Trans(0x55);
							 //	embRS232.Trans_RDN(COMP_DEF_MAC_END);
								embRS232.Trans_RDN_Full(embRS232.HostMAC);	
#else	// NOT CAN_ETHERNET_ASU
//_________________________________________________________________________
//______________________________________________________________________________
 //my_int_disable();	//t
						embRS232.Trans(0x55);
						embRS232.Trans(0xAA);
						for(i=0; i<embMsgA.FullSize(); i++) 
						{
							switch(embMsgA.body[i])
							{
								case 0x5A: embRS232.Trans(0x5A); embRS232.Trans(0x00); break;
								case 0x55: embRS232.Trans(0x5A); embRS232.Trans(0x01); break;
								case 0xA5: embRS232.Trans(0x5A); embRS232.Trans(0x02); break;
								case 0xAA: embRS232.Trans(0x5A); embRS232.Trans(0x03); break;
								default: embRS232.Trans(embMsgA.body[i]);
							}
						}
						embRS232.Trans(0x55);

 //  my_int_enable();

#endif	 // NOT CAN_ETHERNET_ASU
//___________________________________________________________________________________




								flagRequest = 0;
							}  //embMsgA.AddrS()==SelfID()
						}	//embMsgA.TOM()&0x20
					}		//(embMsgA.TOM()&0x01)
					else
					{	
				 //	  	 printf(" p5");

						if(embMsgA.AddrI()!=embMsgA.AddrS())
						{
				 //	  	 printf(" p6");

							if(embMsgA.AddrS()==SelfID())
							{
	 //						cnt_req++;
	 //1230				 	  	  printf("r:%d ",cnt_req);	  //without this print work worst
						//	 EthSendTimer =	(( ETH_ANS_TIMER) * ((BSP_ALARM_FREQUENCY * CORE_ALARM_FREQUENCY) / 1000l));
							//	flagRequest=2;
								flagRequest=6;

		 //		cntflag6++;				 //test
		  //		printf(" %d", cntflag6);  //test

								embMsgRequest = &embMsgA;
							}
						}  //embMsgA.AddrI()!=embMsgA.AddrS()
					}  //else	embMsgA.TOM()&0x01
			  	   }  // buff_cashe.request
				}	//rBuffEmbMsg.Used()

//#endif // ETH_TRANZIT


//#endif //  MPC35_MOD_CHANNEL


#endif	//ETH_TRANZIT
    */
			}


			if(flagRequest) //embMsgRequest->IsEnd())
			{
		//  	  printf(" f:%d",flagRequest );

	   //		printf("\n\r> %04X ", embMsgRequest->AddrS());

 if((embMsgRequest->AddrS()==0)||(embMsgRequest->AddrS()==SelfID()))
					// &&(embMsgRequest->TOM()|0x01))
				{
					embMsgAns.Init();
					embMsgAns.SetTOM(0x21);
					if(embMsgRequest->IsRS485()) 
					{
					//t	if(flagRequest!=3)
 //____________________________________________________________________________________RDN >>
						if( (flagRequest!=3)   &&  (flagRequest!=4)) //rdn
 						{

	   /*
							aI = embMsgRequest->AddrI();
							if(embMsgRequest->AddrS()) aS = embMsgRequest->AddrS();
							else aS = SelfID();
							aR = embMsgRequest->AddrR();
							embMsgRequest->SetAddrI(aS);
							embMsgRequest->SetAddrS(aR);
							embMsgRequest->SetAddrR(aI);

				   //			RS485_disable_RX_interrupt();
#ifndef RS485_MSG_BUFF

							embRS485. Trans(0x55);	  //EC - RDN!!! in all

					 	  //	 printf("\n\r###55");

							embRS485. Trans(0xAA);
					 //			 printf(".AA");


							for(i=0; i<embMsgRequest->FullSize(); i++) 
							{
					 //		   printf(".%0X",	embMsgRequest->body[i]);
								switch(embMsgRequest->body[i])
								{
								case 0x5A: embRS485. Trans(0x5A); embRS485. Trans(0x00); break;
								case 0x55: embRS485. Trans(0x5A); embRS485. Trans(0x01); break;
								case 0xA5: embRS485. Trans(0x5A); embRS485. Trans(0x02); break;
								case 0xAA: embRS485. Trans(0x5A); embRS485. Trans(0x03); break;
								default: embRS485. Trans(embMsgRequest->body[i]);
								}
							   //	RS485_receive_reset();
							}
						   
							embRS485. Trans(0x55);
						   	embRS485.Trans_RDN(embMsgRequest->AddrS());
#else  //	 RS485_MSG_BUFF
		tBuffRS485.Add(*embMsgRequest);
#endif	//   RS485_MSG_BUFF

		 */
					 //	  }
					//    }
//____________________________________________________________________________________RDN  <<
 						}	 //!= 3
						else   //flagRequest == 3 or 4
						{
				 //		printf("\n\r I = %X S = %X R = %X", embMsgRequest->AddrI(),embMsgRequest->AddrS(), embMsgRequest->AddrR());
							embMsgAns.SetRS485();
							aI = embMsgRequest->AddrI();
							if(embMsgRequest->AddrS()) aS = embMsgRequest->AddrS();
							else aS = SelfID();
							aR = embMsgRequest->AddrR();

						//	embMsgRequest->SetAddrI(aS);   //t	 091019
						//	embMsgRequest->SetAddrS(aR);   //t	091019
						//	embMsgRequest->SetAddrR(aI);   //t	091019
							  
				   //100118			embMsgAns.SetAddrI(aR);
				   //100118			embMsgAns.SetAddrS(aI);
				   //100118			embMsgAns.SetAddrR(aS);

							embMsgAns.SetAddrI(aS);
							embMsgAns.SetAddrS(aI);
							embMsgAns.SetAddrR(aR);

							
						}	 //==3
		  //				printf("5");
		//100118			   flagRequest = 0;	 //t	   //new! 21.02.2008

					}
					else //no RS485
					{
						embMsgAns.SetAddrI(SelfID());
						embMsgAns.SetAddrS(embMsgRequest->AddrI());					
					}
			   //ok 1			printf("\n\r     embMsgRequest->Type:%d ",embMsgRequest->Type());

					//	embMsgAns.SetAddrI(SelfID());  //t
					//	embMsgAns.SetAddrS(SelfID());  //t
 // printfp("\n\r Request :");
   //				      printfpd(" %X", embMsgRequest->Body(0));
	 //				     printfpd(" %X", embMsgRequest->Body(1));
	   //					     printfpd(" %X", embMsgRequest->Body(2));
		 //					    printfpd(" %X", embMsgRequest->Body(3));
		   //						   printfpd(" %X", embMsgRequest->Body(4));
#ifdef TEST_PUMVA
	  		  printfp("\n\n\n\r command:");
			  printfpd("%X", embMsgRequest->Type());
#endif           
      
				switch(embMsgRequest->Type())
					{
					case 0x01: // ������ ����

			   //		printEthLongHex(0x01);

					 //	embMsgAns.SetAddrI(SelfID());  //t
					 //	embMsgAns.SetAddrS(SelfID());  //t

						embMsgAns.SetType(0x01);
						embMsgAns.SetLength(44);
						for(i=0; i<44; i++) embMsgAns.SetBody(i,unEmb2TypeVer.byte[i]);
						break;

		  //			case 0x05: // �������� ����� (������ � ����������) 

		  //				SaveFile();
		  //				break;
					 

//______________________________________________________________________________________________						
					case 0x02 :
			   //		printEthLongHex(0x02);

						   embMsgAns.SetType(0x02);
						   embMsgAns.SetLength(embMsgRequest->Body(2) + 3);
						   embMsgAns.SetBody(0,embMsgRequest->Body(0));	//#	number 1 Byte
						   embMsgAns.SetBody(1,embMsgRequest->Body(1));	//#	number 2 Byte
						   embMsgAns.SetBody(2,embMsgRequest->Body(2));	// celling

						   for( i = 0; i < embMsgRequest->Body(2); i++)
						   {
							write_xil_char( ( (embMsgRequest->Body(0)<<8) + embMsgRequest->Body(1) + i), embMsgRequest->Body(3 + i));
						   }


						   for( i = 0; i < embMsgRequest->Body(2); i++)
						   {
							 embMsgAns.SetBody(3 + i ,read_xil_char((embMsgRequest->Body(0)<<8) + embMsgRequest->Body(1) + i));
						   }
							//need make GetPort
					    break;
					   	   				

			 
					case 0x05: // �������� ����� (������ � ����������) 
				//	printEthLongHex(0x05);

 			   	 	   	ul2uc.uc[0] = embMsgRequest->Body(0);
				  		ul2uc.uc[1] = embMsgRequest->Body(1);
				  		ul2uc.uc[2] = embMsgRequest->Body(2);
				   		ul2uc.uc[3] = embMsgRequest->Body(3);


				  		ui2uc.uc[0] = embMsgRequest->Body(4);
						ui2uc.uc[1] = embMsgRequest->Body(5);

						ui2uc.uc[2] = 0;  //port
						ui2uc.uc[3] = 0;  //port

				  		shift = ui2uc.ui;

		 				ui2uc.uc[0] = embMsgRequest->Body(6);
						ui2uc.uc[1] = embMsgRequest->Body(7);
						ui2uc.uc[2] = 0;  //port
						ui2uc.uc[3] = 0;  //port
				 		len = ui2uc.ui;
						temp_crc=0;

			 			for(i=0; i<len; i++) temp_crc += embMsgRequest->Body(i+8);

		   				ui2uc.uc[0] = embMsgRequest->Body(len+8);
		   				ui2uc.uc[1] = embMsgRequest->Body(len+9);
		   				ui2uc.uc[2] = 0;  //1107
						ui2uc.uc[3] = 0;  //1107

						if(ui2uc.ui==temp_crc)
						{ //crc

						if(ul2uc.uc[3] == 0x80) //port : if try use nvram
						{
	  			 		 for(i=0; i<len; i++)
				  		   {
		  			    			write_nvram_char(i + shift, embMsgRequest->Body(i+8));
				  		   }
						 }
						 else  //enover memory
						 {
					  //   shift +=  (unsigned long)(embMsgRequest->Body(0)) << 16;	 //add to address 
						    wd_reset();
						   shift +=  ul2uc.ul;	 //add to address 
						   for(i=0; i<len; i++)
				  		   {
					 //   	write_buffer_char( embMsgRequest->Body(i+8), NO_START_WRITE_BUFFER);
						   	write_buffer_char1( embMsgRequest->Body(i+8), i+ shift);
						   }
					
						 }
				  	 
					 	} //crc
					
						embMsgAns.SetType(0x05);
						embMsgAns.SetLength(10);
						embMsgAns.SetBody(0,embMsgRequest->Body(0));
						embMsgAns.SetBody(1,embMsgRequest->Body(1));
						embMsgAns.SetBody(2,embMsgRequest->Body(2));
						embMsgAns.SetBody(3,embMsgRequest->Body(3));
						embMsgAns.SetBody(4,embMsgRequest->Body(4));
						embMsgAns.SetBody(5,embMsgRequest->Body(5));
						embMsgAns.SetBody(6,embMsgRequest->Body(6));
						embMsgAns.SetBody(7,embMsgRequest->Body(7));
						ui2uc.ui=temp_crc;
						embMsgAns.SetBody(8,ui2uc.uc[0]);
						embMsgAns.SetBody(9,ui2uc.uc[1]);		
				 
				 	break;
				 				
//___________________________________________________________________________________
					case 0x38:	 //all commands
			  //		printEthLongHex(0x38);

						embMsgAns.SetType(0x38);
						embMsgAns.SetLength(10);
						embMsgAns.SetBody(0,embMsgRequest->Body(0));
						embMsgAns.SetBody(1,embMsgRequest->Body(1));
						embMsgAns.SetBody(2,embMsgRequest->Body(2));
						embMsgAns.SetBody(3,embMsgRequest->Body(3));
						embMsgAns.SetBody(4,embMsgRequest->Body(4));
						embMsgAns.SetBody(5,embMsgRequest->Body(5));
						embMsgAns.SetBody(6,embMsgRequest->Body(6));
						embMsgAns.SetBody(7,embMsgRequest->Body(7));
						ui2uc.ui=temp_crc;
						embMsgAns.SetBody(8,ui2uc.uc[0]);
						embMsgAns.SetBody(9,ui2uc.uc[1]);
						if(
							(embMsgRequest->Body(0) == 0x42) &&
							(embMsgRequest->Body(1) == 0x31) &&
							(embMsgRequest->Body(2) == 0x58) &&
							(embMsgRequest->Body(3) == 0x76) &&
							(embMsgRequest->Body(4) == 0x9C) &&
							(embMsgRequest->Body(5) == 0xBA) 
						   )
						   {
						   	switch(embMsgRequest->Body(6))
							{
					  		 case 0:   break; // write_buffer_char( 0, START_WRITE_BUFFER);	break;
							 case 1:   ProgWrite(); break;
							 case 2:   XilWrite(); break;
							 case 3:   DPDWrite(); break;
							 case 4 :  set_test_mode(0x27);	  dev_restart(); 	break;
							 case 5 :  dev_restart(); 	break;
							 case 6 :  write_nvram_char(RESTARTS_NVRAM_ADDRESS,0);
							 case 7 :  m_load_xilinx3((char)XILINXPG, 1);

					  	 	}							   
						   }
						   break;
		  
//___________________________________________________________________________________

					case 0x08: // ������ ���������
				//	printEthLongHex(0x08);

						embMsgAns.SetType(0x08);
						embMsgAns.SetLength(72);
						for(i=0; i<72; i++) embMsgAns.SetBody(i,unStateBMD155.byte[i]);
						unStateBMD155.stateBMD155.count_block=0;
						unStateBMD155.stateBMD155.count_no_correct_block1=0;
						unStateBMD155.stateBMD155.count_no_correct_block2=0;
						unStateBMD155.stateBMD155.count_no_correct_result=0;
						unStateBMD155.stateBMD155.count_notRS1=0;
						unStateBMD155.stateBMD155.count_notRS2=0;
//						unStateBMD155.stateBMD155.demPI=0;
//						unStateBMD155.stateBMD155.loopPI=0;
//						unStateBMD155.stateBMD155.statePI=0;
						break;
					case 0x09:
			  	//	printEthLongHex(0x09);

						if(embMsgRequest->Body(1)<=0x10)
						{
							if(embMsgRequest->Body(0)==1)
							{
					   //		printEthLongHex(0x91);
								embMsg485Request_1.Init();
								embMsg485Request_1.SetAddr(0);//embMsg.Body(0));
								embMsg485Request_1.SetLength(2);
								embMsg485Request_1.SetBody(0,embMsgRequest->Body(1));
								embMsg485Request_1.SetBody(1,embMsgRequest->Body(2));
								embMsg485Request_1.CalcCRC();
							//	embMsg485Request_1.SetReadyToSend();
                          tBuffEmbMsg485Request_1.Add(embMsg485Request_1);

							}
							if(embMsgRequest->Body(0)==2)
							{
								embMsg485Request_2.Init();
								embMsg485Request_2.SetAddr(0);//embMsg.Body(0));
								embMsg485Request_2.SetLength(2);
								embMsg485Request_2.SetBody(0,embMsgRequest->Body(1));
								embMsg485Request_2.SetBody(1,embMsgRequest->Body(2));
								embMsg485Request_2.CalcCRC();
							 //	embMsg485Request_2.SetReadyToSend();
                          tBuffEmbMsg485Request_2.Add(embMsg485Request_2);

							}
						}
						embMsgAns.SetType(0x09);
						embMsgAns.SetLength(12); //3
						embMsgAns.SetBody(0,embMsgRequest->Body(0));
						embMsgAns.SetBody(1,embMsgRequest->Body(1));
						embMsgAns.SetBody(2,embMsgRequest->Body(2));
						//						embMsg.Init();
						break;
					case 0x0A:
 #ifdef TEST_PUMVA
              
               printfp("\n\n\n\n\n\\rAAAAAAAAAAAAAAAAA\n\n");
 #endif              
               
               

				//	printEthLongHex(0x0A);

						//			������: ���������� ���� <����� �����/16><����� ����/8><����� ���/8><��������/8>
						//      �����: <����� �����/16><����� ����/8><����� ���/8><��������/8>
						WritePort();
						break;
					case 0x0B:
				  //	printEthLongHex(0x0B);

						//      ������: ������ �����: <����� �����/16><����� ����/8>
						//      �����: <����� �����/16><����� ���� N/8><�����/N >
						ReadPort();
						break;
					case 0x10:
			   //		printEthLongHex(0x10);

							embMsgAns.SetType(0x10);
			   				embMsgAns.SetLength(66);
			   				for(i=0; i<66; i++) embMsgAns.SetBody(i,unStateRRL.byte[i]);
					/*
						embMsgAns.SetLength(70);
                     
							for(i=0; i<66; i++) embMsgAns.SetBody(i,unStateRRL.byte[i]);
//_________________________101213  
				ansnum++;
                for(i=0; i<32; i++)
				{
					 Packet[i] = unStateRRL.byte[i+2];
				}

			//    Packet[5] = 44; //for test

			   if(CheckPacket(Packet))
			   {ch1ok++;}
			   else
			   {ch1bad++;}
            
             for(i=0; i<32; i++)
				{
					 Packet[i] = unStateRRL.byte[i+34];
				}
			 //	Packet[5] = 22; //for test

			   if(CheckPacket(Packet))
			   {ch2ok++;}
			   else
			   {ch2bad++;}

                   
                     
//______________________101213                     
                     embMsgAns.SetBody(66,ansnum>>24);
                     embMsgAns.SetBody(67,ansnum>>16);
                    embMsgAns.SetBody(68,ansnum>>8);
                     embMsgAns.SetBody(69,ansnum);
//______________________101213
                     
                     	 */

						break;


				   //		break;
					case 0x12: // ������ ���������
			   //		printEthLongHex(0x12);


							embMsgAns.SetType(0x12);
							embMsgAns.SetLength(40);
#ifdef PROG_PU_M_MUX
							for(i=0; i<42; i++) embMsgAns.SetBody(i,unEmb2Mux34.byte[i]);
#endif // PROG_PU_M_MUX

					break;
					case 0x13:
				//	printEthLongHex(0x13);

							embMsgAns.SetType(0x13);
							embMsgAns.SetBody(0,embMsg.Body(0));
							embMsgAns.SetBody(1,embMsg.Body(1));
							embMsgAns.SetBody(2,embMsg.Body(2));
							embMsgAns.SetBody(3,0);
							embMsgAns.SetLength(4);
							addr1 = (embMsg.Body(2)<<8) +	embMsg.Body(1);

							bt = (unsigned char *)(NVRAM_BASE);
//							bt = (unsigned char far*)0x80000000;

							if(embMsg.Body(0)) *(bt + addr1)= embMsg.Body(3);
							else embMsgAns.SetBody(3, *(bt + addr1));
						break;
					case 0x14: // ������ ���������
			   //		printEthLongHex(0x14);

							embMsgAns.SetType(0x14);
							embMsgAns.SetLength(42);
//							for(i=0; i<42; i++) embMsgAns.SetBody(i,unStatePUM.byte[i]);
						 	for(i=0; i<2; i++) embMsgAns.SetBody(i,unStatePUM.byte[i]);
							for(i=4; i<44; i++) embMsgAns.SetBody((i - 2),unStatePUM.byte[i]);

						break;
	   				case 0x22:
							embMsgAns.SetType(0x22);
                     /*
#ifndef HAVE_GATEWAY						

							if(embMsgRequest->Body(0))// set
							{
							   SetIPRem(
							   (embMsgRequest->Body(1) << 24) +
							   (embMsgRequest->Body(2) << 16) +
							   (embMsgRequest->Body(3) << 8) +
							   	embMsgRequest->Body(4)
				 			   );
							}
						   						   
							embMsgAns.SetLength(5);	
							embMsgAns.SetBody(0,embMsgRequest->Body(0)); 	
							embMsgAns.SetBody(1, (GetIPRem() >> 24) & 0xff);
							embMsgAns.SetBody(2, (GetIPRem() >> 16) & 0xff);
							embMsgAns.SetBody(3, (GetIPRem() >> 8) & 0xff);
							embMsgAns.SetBody(4, GetIPRem() & 0xff);
   							break;
#else	
  */
			 //		  printfp("\n\r Request :");
			 //	      printfpd(" %X", embMsgRequest->Body(0));
			 //		     printfpd(" %X", embMsgRequest->Body(1));
			 //			     printfpd(" %X", embMsgRequest->Body(2));
			 //				    printfpd(" %X", embMsgRequest->Body(3));
			  //					   printfpd(" %X", embMsgRequest->Body(4));
						 
							 embMsgAns.SetLength(5);	
							embMsgAns.SetBody(0,embMsgRequest->Body(0)); 

							 switch(embMsgRequest->Body(0))
							 {
							case 0:
								   	embMsgAns.SetBody(1, (GetIPRem() >> 24) & 0xff);
									embMsgAns.SetBody(2, (GetIPRem() >> 16) & 0xff);
									embMsgAns.SetBody(3, (GetIPRem() >> 8) & 0xff);
									embMsgAns.SetBody(4, GetIPRem() & 0xff);
   									break;
							case 1:

									SetIPRem(
								   (embMsgRequest->Body(1) << 24) +
								   (embMsgRequest->Body(2) << 16) +
								   (embMsgRequest->Body(3) << 8) +
								   	embMsgRequest->Body(4)
					 			   );
									
								   	embMsgAns.SetBody(1, (GetIPRem() >> 24) & 0xff);
									embMsgAns.SetBody(2, (GetIPRem() >> 16) & 0xff);
									embMsgAns.SetBody(3, (GetIPRem() >> 8) & 0xff);
									embMsgAns.SetBody(4, GetIPRem() & 0xff);
   									break;
							case 2:
   									SetNetworkRem(
								   (embMsgRequest->Body(1) << 24) +
								   (embMsgRequest->Body(2) << 16) +
								   (embMsgRequest->Body(3) << 8) +
								   	embMsgRequest->Body(4)
					 			   );
									
								   	embMsgAns.SetBody(1, (GetNetworkRem() >> 24) & 0xff);
									embMsgAns.SetBody(2, (GetNetworkRem() >> 16) & 0xff);
									embMsgAns.SetBody(3, (GetNetworkRem() >> 8) & 0xff);
									embMsgAns.SetBody(4, GetNetworkRem() & 0xff);
   									break;

						   	 case 3:
   									SetNetMaskRem(
								   (embMsgRequest->Body(1) << 24) +
								   (embMsgRequest->Body(2) << 16) +
								   (embMsgRequest->Body(3) << 8) +
								   	embMsgRequest->Body(4)
					 			   );
									
								   	embMsgAns.SetBody(1, (GetNetMaskRem() >> 24) & 0xff);
									embMsgAns.SetBody(2, (GetNetMaskRem() >> 16) & 0xff);
									embMsgAns.SetBody(3, (GetNetMaskRem() >> 8) & 0xff);
									embMsgAns.SetBody(4, GetNetMaskRem() & 0xff);
   									break;

							 case 0x12:
   								 		
								   	embMsgAns.SetBody(1, (GetNetworkRem() >> 24) & 0xff);
									embMsgAns.SetBody(2, (GetNetworkRem() >> 16) & 0xff);
									embMsgAns.SetBody(3, (GetNetworkRem() >> 8) & 0xff);
									embMsgAns.SetBody(4, GetNetworkRem() & 0xff);
   									break;

						   	 case 0x13:
								   	embMsgAns.SetBody(1, (GetNetMaskRem() >> 24) & 0xff);
									embMsgAns.SetBody(2, (GetNetMaskRem() >> 16) & 0xff);
									embMsgAns.SetBody(3, (GetNetMaskRem() >> 8) & 0xff);
									embMsgAns.SetBody(4, GetNetMaskRem() & 0xff);
   									break;
							 default: 
							  	embMsgAns.SetBody(1,  1);
									embMsgAns.SetBody(2, 2);
									embMsgAns.SetBody(3,  3);
									embMsgAns.SetBody(4, 4);
   									break;

									
							 }
						  break;


//#endif
   /*
#ifdef USE_RS125

					case 0x39: // request rs125 state

			   		// printEthLongHex(0x01);
					//	embMsgAns.SetAddrI(SelfID());  //t
					//	embMsgAns.SetAddrS(SelfID());  //t

						embMsgAns.SetType(0x39);
						embMsgAns.SetLength(MES_MAX_LEN);
						for(i=0; i<MES_MAX_LEN; i++) embMsgAns.SetBody(i,StatBuffer[i]);
						break;

					case 0x40: // request rs125 state

			   //		printEthLongHex(0x01);
			   //		embMsgAns.SetAddrI(SelfID());  //t
			   //		embMsgAns.SetAddrS(SelfID());  //t

						embMsgAns.SetType(0x40);
						embMsgAns.SetLength(MES_OCT_LEN);
						for(i=0; i<MES_OCT_LEN; i++) embMsgAns.SetBody(i,StatBuffer[i]);
						break;

					case 0x41: // request rs125 state

			   		// printEthLongHex(0x01);
					//	embMsgAns.SetAddrI(SelfID());  //t
					//	embMsgAns.SetAddrS(SelfID());  //t
						im = 0;
						embMsgAns.SetType(0x41);
						embMsgAns.SetLength(REAL_MES_LEN);
						for(i=0; i<MES_MAX_LEN; i++) 
						{
						if(IsNotRezerved(i))
							{
							embMsgAns.SetBody(im++,StatBuffer[i]);
							}
						}
						break;

					case 0x42: // request max, min , centered values of period of keep

			   			embMsgAns.SetType(0x42);
						embMsgAns.SetLength(MAX_MIN_CENTER_LEN);
						MakeStat();
				   		 for(i=0; i<MAX_MIN_CENTER_LEN; i++) 
				   		 {
				   	  		embMsgAns.SetBody(i,ukeep_st.byte[i]);
				   	  	 }
						
						break;

#endif //USE_RS125
   */
//_______________________________________________>> changed 0x9 -> 0x49; 0xA -> 0x4A; 0xB -. 0x4B                  
//101110					case 0x09:
					case 0x49:   //101110
			//			if(embMsgRequest->Body(1)<=0x10)
			//			{
 						embMsg485Request.Init();
 						embMsg485Request.SetAddr(embMsgRequest->Body(0));
						embMsg485Request.SetLength(2);
						embMsg485Request.SetBody(0,embMsgRequest->Body(1));
 					    embMsg485Request.SetBody(1,embMsgRequest->Body(2));
						embMsg485Request.CalcCRC();
						embMsg485Request.SetReadyToSend();

			//			}
			//			else
			//			{
			//				switch(embMsgRequest->Body(1))
			//				{
			//				case 0x11: 
			//					if(embMsgRequest->Body(2)) outportb(0x583,(inportb(0x583)&0xFD)|0x02);
			//					else outportb(0x583,inportb(0x583)&0xFD);
			//					break;
			//				case 0x12: 
			 //					if(embMsgRequest->Body(2)) outportb(0x583,(inportb(0x583)&0xFE)|0x01);
			 //					else outportb(0x583,inportb(0x583)&0xFE);
			 //					break;
			 //				}
			 //			}
						embMsgAns.SetType(0x49);
						embMsgAns.SetLength(3);
						embMsgAns.SetBody(0,embMsgRequest->Body(0));
						embMsgAns.SetBody(1,embMsgRequest->Body(1));
						embMsgAns.SetBody(2,embMsgRequest->Body(2));
						//						embMsg.Init();
						break;
//101110					case 0x0A:
					case 0x4A:  //101110
		 //			if((embMsgRequest->Body(1)&0xC0)==0x80)
		  //			{
						embMsg485Request.Init();
						embMsg485Request.SetAddr(embMsgRequest->Body(0));
			   	//		embMsg485Request.SetLength(4);
			           	embMsg485Request.SetLength(8);
			   //			embMsg485Request.SetBody(0,0x07);
			   //			embMsg485Request.SetBody(1,embMsgRequest->Body(0));
			   //			embMsg485Request.SetBody(2,embMsgRequest->Body(1)&0x3F);
			   //			embMsg485Request.SetBody(3,embMsgRequest->Body(4));
						embMsg485Request.SetBody(0,embMsgRequest->Body(1));//byte
						embMsg485Request.SetBody(1,embMsgRequest->Body(2));	//bit
						embMsg485Request.SetBody(2,embMsgRequest->Body(3));	//quantity
						embMsg485Request.SetBody(3,embMsgRequest->Body(4));	//value
						embMsg485Request.SetBody(4,embMsgRequest->Body(5));	//value
						embMsg485Request.SetBody(5,embMsgRequest->Body(6));	//value
						embMsg485Request.SetBody(6,embMsgRequest->Body(7));	//value
						embMsg485Request.SetBody(7,embMsgRequest->Body(8));	//value
   



						embMsg485Request.CalcCRC();
						embMsg485Request.SetReadyToSend();
			//		}
			//		else if((embMsgRequest->Body(1)&0xC0)==0xC0)
			//		{
		   //				embMsg485Request.Init();
			//			embMsg485Request.SetAddr(0x02);
			//			embMsg485Request.SetLength(4);
			//			embMsg485Request.SetBody(0,0x07);
			//			embMsg485Request.SetBody(1,embMsgRequest->Body(0));
			//			embMsg485Request.SetBody(2,embMsgRequest->Body(1)&0x3F);
			//			embMsg485Request.SetBody(3,embMsgRequest->Body(4));
			//			embMsg485Request.CalcCRC();
			//			embMsg485Request.SetReadyToSend();
		   //			}
		   //			else
		  //			{
		  //			 outportb(embMsgRequest->Body(0)+(embMsgRequest->Body(1)<<8), embMsgRequest->Body(4));
		  //			 embMsgAns.SetType(0x4A);
		  //			 embMsgAns.SetBody(0,embMsgRequest->Body(0));
		  //			 embMsgAns.SetBody(1,embMsgRequest->Body(1));
		  //			 embMsgAns.SetBody(2,0);
		  //			 embMsgAns.SetBody(3,8);
		  //			 embMsgAns.SetBody(4,embMsgRequest->Body(4));
		 //			 embMsgAns.SetLength(5);
		 //			}

		  			 embMsgAns.SetType(0x4A);
		  			 embMsgAns.SetBody(0,embMsgRequest->Body(0));
		  			 embMsgAns.SetBody(1,embMsgRequest->Body(1));
		  			 embMsgAns.SetBody(2,embMsgRequest->Body(2));
		  			 embMsgAns.SetBody(3,embMsgRequest->Body(3));
		  			 embMsgAns.SetBody(4,embMsgRequest->Body(4));
		  			 embMsgAns.SetBody(5,embMsgRequest->Body(5));
		  			 embMsgAns.SetBody(6,embMsgRequest->Body(6));
		  			 embMsgAns.SetBody(7,embMsgRequest->Body(7));
 		 			 embMsgAns.SetLength(8);

					   
						break;
//101110					case 0x0B:
					case 0x4B: //101110
 					if((embMsgRequest->Body(1)&0xC0)==0x80)
					{
						embMsg485Request.Init();
						embMsg485Request.SetAddr(0x01);
						embMsg485Request.SetLength(3);
						embMsg485Request.SetBody(0,0x08);
						embMsg485Request.SetBody(1,embMsgRequest->Body(0));
						embMsg485Request.SetBody(2,embMsgRequest->Body(1)&0x3F);
						embMsg485Request.CalcCRC();
						embMsg485Request.SetReadyToSend();
					}
					 else if((embMsgRequest->Body(1)&0xC0)==0xC0)
					{
						embMsg485Request.Init();
						embMsg485Request.SetAddr(0x02);
						embMsg485Request.SetLength(3);
						embMsg485Request.SetBody(0,0x08);
						embMsg485Request.SetBody(1,embMsgRequest->Body(0));
						embMsg485Request.SetBody(2,embMsgRequest->Body(1)&0x3F);
						embMsg485Request.CalcCRC();
						embMsg485Request.SetReadyToSend();
					}
		   			else
					{
					  inportb(embMsgRequest->Body(0)+(embMsgRequest->Body(1)<<8));
					  embMsgAns.SetType(0x4B);
					  embMsgAns.SetBody(0,embMsgRequest->Body(0));
					  embMsgAns.SetBody(1,embMsgRequest->Body(1));
					  embMsgAns.SetBody(2,0);
					  embMsgAns.SetBody(3,8);
					  embMsgAns.SetBody(4,inportb(embMsgRequest->Body(0)+(embMsgRequest->Body(1)<<8)));
					  embMsgAns.SetLength(5);

					}
					  
						break;
		                 
				case 0x4C: 
            	  embMsgAns.SetType(0x4C);
                 embMsgAns.SetLength((DEVCONFIG_QUANTITY << 1) + 2);
                 if(embMsgRequest->Body(0) > DEVCONFIG_QUANTITY)    //get current
                 {
                 for(i=0; i<((DEVCONFIG_QUANTITY << 1) + 2); i++) embMsgAns.SetBody(i,Getudevconfig(i));
                 }
                 else    //need set and write to flash
                 {
                  for(i=0; i<((DEVCONFIG_QUANTITY << 1) + 2); i++)
                  {
              
                   embMsgAns.SetBody(i,embMsgRequest->Body(i));
                   Setudevconfig((unsigned char)i,(unsigned char)embMsgRequest->Body(i));
                //   Setudevconfig(1,1); //t
                 //  SetNeedWriteDevId();
                  }
                  SetNeedWriteDevId();
                 } 
                	                  
                 break; 
			case 0x4D: 
	  //		printfp("\n\r 4d"); //___________________________
            	  embMsgAns.SetType(0x4D);
                 embMsgAns.SetLength(DEV_INFO_SIZE + 4);
                 embMsgAns.SetBody(0,embMsgRequest->Body(0));
//_______________________________________________________________
           if((embMsgRequest->Body(0) <= DEVCONFIG_QUANTITY) && embMsgRequest->Body(0))
           {
           cur_rem_pointer = GetDevPointer(embMsgRequest->Body(0));
       //    printfp("ok quantityr");		//________________________

           if(cur_rem_pointer != BAD_POINTER)
            {
		//	printfp("ok pointer");	  //________________________

            embMsgAns.SetBody(1,GetDevType(cur_rem_pointer));
            embMsgAns.SetBody(2,devstate[embMsgRequest->Body(0) - 1]); 
            embMsgAns.SetBody(3,0);
            
            for(i = 0; i < DEV_INFO_SIZE; i++)
            {
             embMsgAns.SetBody(4 + i,statedev[embMsgRequest->Body(0) - 1].byte[i]);  //addr from 1 to 16
            }
           
            }    // BAD_POINTER
            else
            { 
             for(i = 0; i < DEV_INFO_SIZE + 3; i++)
            {
             embMsgAns.SetBody(1 + i,0);  //addr from 1 to 16
            }
            } 
           } // DEVCONFIG_QUANTITy
            else
            { 
             for(i = 0; i < DEV_INFO_SIZE + 3; i++)
            {
             embMsgAns.SetBody(1 + i,0);  //addr from 1 to 16
            }
            } 
			   break;

	case 0x4E: // 

			   //		printEthLongHex(0x4e);

					 //	embMsgAns.SetAddrI(SelfID());  //t
					 //	embMsgAns.SetAddrS(SelfID());  //t

						embMsgAns.SetType(0x4E);
						embMsgAns.SetLength(32);
						for(i=0; i<44; i++) embMsgAns.SetBody(i,uemb4pumfabinfo.byte[i]);
						break;


//_______________________________________________________________                 
                 
                 
                 
                 /*
                 
                 if(embMsgRequest->Body(0) > DEVCONFIG_QUANTITY)    //get current
                 {
                 for(i=0; i<((DEVCONFIG_QUANTITY << 1) + 2); i++) embMsgAns.SetBody(i,Getudevconfig(i));
                 }
                 else    //need set and write to flash
                 {
                  for(i=0; i<((DEVCONFIG_QUANTITY << 1) + 2); i++)
                  {
              
                   embMsgAns.SetBody(i,embMsgRequest->Body(i));
                   Setudevconfig((unsigned char)i,(unsigned char)embMsgRequest->Body(i));
                //   Setudevconfig(1,1); //t
                   SetNeedWriteDevId();
                  }
                 } 
                 */
                  /*
              	  embMsgAns.SetBody(0,embMsgRequest->Body(0));
					  embMsgAns.SetBody(1,embMsgRequest->Body(1));
					  embMsgAns.SetBody(2,0);
					  embMsgAns.SetBody(3,8);
					  embMsgAns.SetBody(4,inportb(embMsgRequest->Body(0)+(embMsgRequest->Body(1)<<8)));
					  embMsgAns.SetLength(5);
                  
	                  
                 break; 
                 
                 	*/
                 
//_________________________________________________________________<< changed 0x9 -> 0x49; 0xA -> 0x4A; 0xB -. 0x4B                  

//#endif //USE_RS125

					}
//>>>>
					embMsgAns.SetCycle(cycle++);
					embMsgAns.CalcCRC();

					if(flagRequest == 1) 
					{
						embRS232.Trans(0x55);
						embRS232.Trans(0xAA);
						for(i=0; i<embMsgAns.FullSize(); i++) 
						{
							switch(embMsgAns.body[i])
							{
								case 0x5A: embRS232.Trans(0x5A); embRS232.Trans(0x00); break;
								case 0x55: embRS232.Trans(0x5A); embRS232.Trans(0x01); break;
								case 0xA5: embRS232.Trans(0x5A); embRS232.Trans(0x02); break;
								case 0xAA: embRS232.Trans(0x5A); embRS232.Trans(0x03); break;
								default: embRS232.Trans(embMsgAns.body[i]);
							}
						}
						embRS232.Trans(0x55);
			 //			embRS232.EmptyReceive();
						embMsg232.Init(); //090122
						flagRequest = 0;
					}	//  == 1
//___________________________________________________________________________________232e
/*
					if(flagRequest == 5) 
					{
						embRS232.TransE(0x55);
						embRS232.TransE(0xAA);
						for(i=0; i<embMsgAns.FullSize(); i++) 
						{
							switch(embMsgAns.body[i])
							{
								case 0x5A: embRS232.TransE(0x5A); embRS232.TransE(0x00); break;
								case 0x55: embRS232.TransE(0x5A); embRS232.TransE(0x01); break;
								case 0xA5: embRS232.TransE(0x5A); embRS232.TransE(0x02); break;
								case 0xAA: embRS232.TransE(0x5A); embRS232.TransE(0x03); break;
								default: embRS232.TransE(embMsgAns.body[i]);
							}
						}
						embRS232.TransE(0x55);
				 //		embRS232.Trans_RDN(COMP_DEF_MAC_END);	
						embRS232.Trans_RDN_Full(embRS232.HostMAC);	
		  //				embRS232.EmptyReceiveE();

					  	embMsgAns.Init(); //my as in mf_20 previons
						embMsg232E.Init(); //090122
					 	flagRequest = 0;
					}
               */
//______________________________________________________________________________________232e
			   //	 for(long it = 0; it< 50; it++)	//t
                /*
					if(flagRequest == 3) 
					{
			  //		RS485_receive_disable();

						embRS485.Trans(0x55);
					//	 printf("\n\r>>>>embMsgRequest->AddrS() = %X", embMsgRequest->AddrS());	 //3310
					//	 printf("\n\r>>>>embMsgRequest->AddrI() = %X", embMsgRequest->AddrI());	 //	3309
					//	 printf("\n\r>>>>embMsgRequest->AddrR() = %X", embMsgRequest->AddrR());	 //enower
				   
				   	// 	 printf("\n\r>>>>55");

						embRS485.Trans(0xAA);
					// 	 printf(".AA");

						for(i=0; i<embMsgAns.FullSize(); i++) 
						{
					 //	  printf(".%0X",	embMsgAns.body[i]);

							switch(embMsgAns.body[i])
							{
								case 0x5A: embRS485.Trans(0x5A); embRS485.Trans(0x00); break;
								case 0x55: embRS485.Trans(0x5A); embRS485.Trans(0x01); break;
								case 0xA5: embRS485.Trans(0x5A); embRS485.Trans(0x02); break;
								case 0xAA: embRS485.Trans(0x5A); embRS485.Trans(0x03); break;
								default: embRS485.Trans(embMsgAns.body[i]);
							}
						}
			  						embRS485.Trans(0x55);
									embRS485.EmptyReceive();

				   //		 printf(".55");
			//	  RS485_receive_enable();
   	  		 embMsg485.Init();	//090122
		  //t		 printf(".");
		 		flagRequest = 0;

			 	}	   // ==3
              */
	//_________________________________________________________________________________RDN
			    /*
	if(flagRequest == 4) 
			   	{ 
						   embRS485.TransE(0x55);
		  					embRS485.TransE(0xAA);
		  				for(i=0; i<embMsgAns.FullSize(); i++) 
						{
					//	  printf(".%0X",	embMsgAns.body[i]);

							switch(embMsgAns.body[i])
							{
								case 0x5A: embRS485.TransE(0x5A); embRS485.TransE(0x00); break;
								case 0x55: embRS485.TransE(0x5A); embRS485.TransE(0x01); break;
								case 0xA5: embRS485.TransE(0x5A); embRS485.TransE(0x02); break;
								case 0xAA: embRS485.TransE(0x5A); embRS485.TransE(0x03); break;
								default: embRS485.TransE(embMsgAns.body[i]);
							}
						}
						embRS485.TransE(0x55);
						embRS485.EmptyReceiveE();

			 			  embRS485.Trans_RDN(embMsgAns.AddrS());
						   embMsg485E.Init();	//090122

								flagRequest = 0;
					}	// ==3
               */
					
 //________________________________________________________________________________________RDN


				}
		 //		else	//not self addr
		  //		{
			//		if(flagRequest == 1) 
			//		{
//						if((ready_transit)||(ready_mod))
			   //			{
   	 	 	   //	   	  	printf("\n\rT");
	   			 //		printd('\n');
				 //		printd('\r');
				 //		printd('T');



			//		   		printf("\n\r> %04X ", embMsgRequest->AddrS());		//t
	   	//	my_int_disable_irq0();

			//				tBuffEmbMsgEast.Add(embMsg232);
			//				tBuffEmbMsgWest.Add(embMsg232);
                   
                     /*
#ifdef 	ETH_TRANZIT
					   	   	 tBuffEmbMsgEthAll.Add(embMsg232);
						     tBuffEmbMsgEthAll1.Add(embMsg232);
#endif //ETH_TRANZIT
*/

		 //					unEmb2NetStat.emb2NetStat.selfPacketSend++;
			//_____________my
				   //			if	(tBuffEmbMsgEast.Used())
					 //		{
								 //	printf("\n\r@");
							 //		printf("\n\r@, %d", uscnt);
							//		my_int_disable_usart0();
							//		uscnt++;
					   //		}
           //_______________my
	   	//	my_int_enable_irq0();
				//		}
			//		}
		//  			else
	  	//   		embMsg232.Init();
 //_________________________________________________________________________________232e
            /*
	if(flagRequest == 5) 
					{
				   			tBuffEmbMsgEast.Add(embMsg232E);
							tBuffEmbMsgWest.Add(embMsg232E);
                     
#ifdef 	ETH_TRANZIT
					   		  tBuffEmbMsgEthAll.Add(embMsg232E);
							  tBuffEmbMsgEthAll1.Add(embMsg232E);
#endif //ETH_TRANZIT
   
							unEmb2NetStat.emb2NetStat.selfPacketSend++;
					}
		//  		else
		 // 				embMsg232E.Init();
       */

 //_________________________________________________________________________________232e
 
			 //	}	   //not self addr
		
		 //		if(flagRequest == 2) 
		 //		{
		 //				tBuffEmbMsgEast.Add(embMsgAns);
		 //				tBuffEmbMsgWest.Add(embMsgAns);
		 //		}	// == 2

//============================================================================================		
         /*
				if(flagRequest == 7) 
				{
		  		   
					 	tBuffEmbMsgEast.Add(embMsgAns);
				 //tranzit not need		tBuffEmbMsgWest.Add(embMsgAns);
						unEmb2NetStat.emb2NetStat.selfPacketSend++;
 				}	// == 7
//================================================================================================

 //============================================================================================		
 #ifdef 	ETH_TRANZIT			
				if(flagRequest == 6) 
				{
				 tBuffEmbMsgEthAll.Add(embMsgAns);
			  	 tBuffEmbMsgEthAll1.Add(embMsgAns);
				 unEmb2NetStat.emb2NetStat.selfPacketSend++;
			  	}	// == 6

 #endif //ETH_TRANZIT
             */




			 //	embRS485.Trans(0x99); //t100118
			 //	 printf(".");	   //t100118

				flagRequest = 0;
				embMsgRequest = NULL;
			}  //have flagrequest not zero

//	}
  //		embRS485.Trans(0x99); //t100118	    - get to not ping mode!!!!
  //				 printf(".");	   //t100118


/////////////////////////////////////////////////////////////////////////////////////
////////////////////////////    ANSWER   ////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
