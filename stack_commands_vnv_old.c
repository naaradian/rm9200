//file: stack_commands.c

command_counter++;

///////////////////////////////////////	UPP /////////////////////////////////////////////
             embMsgAns.SetLength(0); //121023 - if have wrong command - set as default minimum length
			 	switch(embMsgRequest->Type())
					{
               
              
               
					case 0x0A:
            //      break; //t121112
	  	  //			printEthLongHex(0x0A);

						//			Запрос: Установить биты <Номер байта/16><Номер бита/8><Число бит/8><Значение/8>
						//      Ответ: <Номер байта/16><Номер бита/8><Число бит/8><Значение/8>
#ifndef PROG_BMDN6MI                  
						WritePort();
#endif                  
						break;
					case 0x0B:
         //       break; //t121112
			//	  	printEthLongHex(0x0B);

						//      Запрос: Чтение порта: <Номер байта/16><Число байт/8>
						//      Ответ: <Номер байта/16><Число байт N/8><Байты/N >
#ifndef PROG_BMDN6MI                  
						ReadPort();
#endif                  
						break;
                  
                 
          //  #ifndef PROG_BMDN6M      
				case 0x10:
			 //  		printEthLongHex(0x10);

							embMsgAns.SetType(0x10);
							embMsgAns.SetLength(66);
            #ifndef PROG_BMDN6MI         
							for(i=0; i<66; i++) embMsgAns.SetBody(i,unStateRRL.byte[i]);
            #endif         
						break;
                  
				case 0x09:
          //  printEthLongHex(0x9);

				  //	printf("\n\r 0x09");
						 if(embMsgRequest->Body(1)<=0x10)
						{
							if(embMsgRequest->Body(0)==1) //was1
							{
                       //      printEthLongHex(1);

					 //		     printf(">>");

						//	printf("\n\r Body(0)==1");
								embMsg485Request_1.Init();
								embMsg485Request_1.SetAddr(0);//embMsg.Body(0));
								embMsg485Request_1.SetLength(2);
								embMsg485Request_1.SetBody(0,embMsgRequest->Body(1));
								embMsg485Request_1.SetBody(1,embMsgRequest->Body(2));
								embMsg485Request_1.CalcCRC();
				  //130626				embMsg485Request_1.SetReadyToSend();
                        tBuffEmbMsg485Request_1.Add(embMsg485Request_1); //130626
						//		printf(".%02X",embMsg485Request_1.IsReadyToSend());
							  //	printf(".%02X",embMsg485Request_1.Body(0));
							  //  printf(".%02X\n\r",embMsg485Request_1.Body(1));
						  //      printf("\n\r>>>>>>i: %d",  embSerialACT155.count);
                    
//____________________________________________________
#ifdef O_POWER
//hier can add == 4 (freq pd ) ==5 (freq pm)

                if (embMsgRequest->Body(1) == 2) //command operate power
//                if ((embMsgRequest->Body(1) == 2) || //command operate power      
  //                  (embMsgRequest->Body(1) == 4) ||
    //                (embMsgRequest->Body(1) == 5))
                  {
             //    printfp("\n\r___________________power");
                
                 if(GetModForSS1())
                 { 
           //ok        printfp("\n\r...............modfss1 off");
                   flag_command_power = 1;
                  SetModForSS1(0); //get off operate power mode - without saving
                  UsedExp.State.Reg2.bit.WriteId = 1;
                  UsedExp.State.Reg2.bit.Some = 1;
                 } 
                } /* Endbody */

#endif
//______________________________________________________                    

							}
							if(embMsgRequest->Body(0)==2) //1
							{
                        //      printEthLongHex(2);

					   //			printf("\n\r Body(0)==2");

								embMsg485Request_2.Init();
								embMsg485Request_2.SetAddr(0);//embMsg.Body(0));
								embMsg485Request_2.SetLength(2);
								embMsg485Request_2.SetBody(0,embMsgRequest->Body(1));
								embMsg485Request_2.SetBody(1,embMsgRequest->Body(2));
								embMsg485Request_2.CalcCRC();
					 //130626			embMsg485Request_2.SetReadyToSend();
                         tBuffEmbMsg485Request_2.Add(embMsg485Request_2); //130626

                        
//____________________________________________________
#ifdef O_POWER
                if (embMsgRequest->Body(1) == 2) //command operate power
                {
                flag_command_power = 1;
                  SetModForSS1(0); //get off operate power mode - without saving
                  UsedExp.State.Reg2.bit.WriteId = 1;
                  UsedExp.State.Reg2.bit.Some = 1;

                } /* Endbody */

#endif
//______________________________________________________                             
							}

						}
						embMsgAns.SetType(0x09);
						embMsgAns.SetLength(12); //3
						embMsgAns.SetBody(0,embMsgRequest->Body(0));
						embMsgAns.SetBody(1,embMsgRequest->Body(1));
						embMsgAns.SetBody(2,embMsgRequest->Body(2));
						//						embMsg.Init();
						break;
			                  
                  
                  
//_______________________________________________________________________________               
               
			 		case 0x01: // cai?in oeia
            //     printEthLongHex(0x1);
 
						embMsgAns.SetType(0x01);
						embMsgAns.SetLength(44);
				   		for(i=0; i<44; i++) embMsgAns.SetBody(i,unEmb2TypeVer.byte[i]);	 //hier added 0xff ...
					//	for(i=0; i<44; i++) embMsgAns.SetBody(i,i);	 //_______for test
						break;

//============================================================================================SVCPACK
//__________________________________________________________________________________

			 
					case 0x05: // Загрузка файла (запись в устройство) 
			   //		printEthLongHex(0x05);

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
				//	printEthLongHex(0x38);

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


//============================================================================================SVCPACK


					case 0x07: /// Aaia?ei cai?in ia?ea?a ai ana iai?aaeaiey
             //      for(i)
			  //101227			if(ready_transit) old_ready_transit=0;
			  //101227			if(ready_mod) old_ready_mod=0;
                  
						break;
		  			case 0x13:
							embMsgAns.SetType(0x13);
							embMsgAns.SetBody(0,embMsgRequest->Body(0));
							embMsgAns.SetBody(1,embMsgRequest->Body(1));
							embMsgAns.SetBody(2,embMsgRequest->Body(2));
							embMsgAns.SetBody(3,0);
							embMsgAns.SetLength(4);
							addr1 = (embMsgRequest->Body(2)<<8) +	embMsgRequest->Body(1);

   //							bt = (unsigned char far*)0x80000000;
							   bt = (unsigned char *)(NVRAM_BASE);

							if(embMsgRequest->Body(0)) *(bt + addr1)= embMsgRequest->Body(3);
							else embMsgAns.SetBody(3, *(bt + addr1));
						break;
                    
				                   
						case 0x15:
						break;
	   				case 0x22:
							embMsgAns.SetType(0x22);
#ifndef HAVE_GATEWAY						

//							if(embMsgRequest->Body(0))// set
							if(embMsgRequest->Body(0) == 1)// set
							{
							   SetIPRem(
							   (embMsgRequest->Body(1) << 24) +
							   (embMsgRequest->Body(2) << 16) +
							   (embMsgRequest->Body(3) << 8) +
							   	embMsgRequest->Body(4)
				 			   );
							}
						    else  if (embMsgRequest->Body(0) == 0)
                      	{ 
                     embMsgAns.SetLength(5);	
							embMsgAns.SetBody(0,embMsgRequest->Body(0)); 	
							embMsgAns.SetBody(1, (GetIPRem() >> 24) & 0xff);
							embMsgAns.SetBody(2, (GetIPRem() >> 16) & 0xff);
							embMsgAns.SetBody(3, (GetIPRem() >> 8) & 0xff);
							embMsgAns.SetBody(4, GetIPRem() & 0xff);
                     }
                     else
                     { 
                     embMsgAns.SetLength(5);	
							embMsgAns.SetBody(0,0); 	
							embMsgAns.SetBody(1,0);
							embMsgAns.SetBody(2,0);
							embMsgAns.SetBody(3,0);
							embMsgAns.SetBody(4,0);

                     
                     
                     }                     
   							break;
#else	

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


#endif

         }  //switch

