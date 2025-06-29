
#include "xparameters_ps.h"
#include <xbasic_types.h>
#include <xstatus.h>
#include <xusbps.h>
#include "usb_hid_setup_endpoint.h"
#include "logging.h"


void XUsbPs_ClassReq(XUsbPs *InstancePtr, XUsbPs_SetupData *SetupData);
void XUsbPs_StdDevReq(XUsbPs *InstancePtr, XUsbPs_SetupData *SetupData);
int XUsbPs_HandleVendorReq(XUsbPs *InstancePtr, XUsbPs_SetupData *SetupData);

static u8 Response ALIGNMENT_CACHELINE;

/*****************************************************************************
* This function handles a Setup Data packet from the host.
* @param	InstancePtr is a pointer to XUsbPs instance of the controller.
* @param	SetupData is the structure containing the setup request.
* @return XST_SUCCESS if the function is successful. XST_FAILURE if an Error occurred.
******************************************************************************/
int HandleSetupPacket(XUsbPs *InstancePtr, XUsbPs_SetupData *SetupData)
{
    int Status = XST_SUCCESS;


    LOG("\r\n\rHandle setup packet\n");


    switch (SetupData->bmRequestType & XUSBPS_REQ_TYPE_MASK) {
        case XUSBPS_CMD_STDREQ:
            LOG("Std request %x\n", SetupData->bRequest);
            XUsbPs_StdDevReq(InstancePtr, SetupData);
            break;

        case XUSBPS_CMD_CLASSREQ:
            LOG("Class request %x\n", SetupData->bRequest);
            XUsbPs_ClassReq(InstancePtr, SetupData);
            break;

        case XUSBPS_CMD_VENDREQ:


            LOG("Vendor request %x\n", SetupData->bRequest);

            Status = XUsbPs_HandleVendorReq(InstancePtr, SetupData);
            break;

        default:
            /* Stall on Endpoint 0 */

            LOG("unknown class req, stall 0 in out\n");

            XUsbPs_EpStall(InstancePtr, 0, XUSBPS_EP_DIRECTION_IN |
                    XUSBPS_EP_DIRECTION_OUT);
            break;
    }

    return Status;
}

void XUsbPs_ClassReq(XUsbPs *InstancePtr, XUsbPs_SetupData *SetupData)
{
	int Status;
	u8	*BufferPtr;
	u32	BufferLen = 0;
	u32	Handle;
	static u8 Reply[XUSBPS_REQ_REPLY_LEN] ALIGNMENT_CACHELINE;

	Xil_AssertVoid(InstancePtr != NULL);
	Xil_AssertVoid(SetupData   != NULL);

	uint8_t reportId = (SetupData->wValue) & 0xFF;
	u32 ReplyLen = SetupData->wLength;

	switch (SetupData->bRequest) {

		case XUSBPS_CLASSREQ_HID_GET_REPORT:

			LOG("ClassReq XUSBPS_CLASSREQ_HID_GET_REPORT\n");
			LOG("ClassReq XUSBPS_CLASSREQ_HID_GET_REPORT wValue 0x%x\n", SetupData->wValue);
			LOG("ClassReq XUSBPS_CLASSREQ_HID_GET_REPORT wIndex %u\n", SetupData->wIndex);
			LOG("ClassReq XUSBPS_CLASSREQ_HID_GET_REPORT wLength %u\n", SetupData->wLength);

			switch (reportId) {
			        case 0x01: //PID Pool Report
			            //printf("GET reportId 0x01\n"); //RAM Pool Size, Parameter Block Size x5, Device Managed Pool
						unsigned char mmos_report01[] = {0x1, 0xff, 0x0d, 0x06, 0x0e, 0x08, 0x04, 0x80};
						
						Status = XUsbPs_EpBufferSend(InstancePtr, 0, mmos_report01, sizeof(mmos_report01));
						if (XST_SUCCESS != Status) {
							LOG("XUsbPs_EpBufferSend 0x01 FAILED \n");
						}else{
							LOG("ClassReq XUSBPS_CLASSREQ_HID_GET_REPORT 0x01 EpBufferSend len %u\n", sizeof(mmos_report01));
						}
			            break;

			        case 0x33: //PID Block Load Report
			            //printf("GET reportId 0x33 wValue %u wIndex %u wLength %u\n", SetupData->wValue, SetupData->wIndex, SetupData->wLength);
						unsigned char mmos_report33_0[] = {0x33, 0x01, 0x01, 0xff}; // Effect Block Index, Block Load Status, RAM Pool Available
						Status = XUsbPs_EpBufferSend(InstancePtr, 0, mmos_report33_0, sizeof(mmos_report33_0));
						if (XST_SUCCESS != Status) {
							LOG("XUsbPs_EpBufferSend 0x33 FAILED \n");
						}else{
							LOG("ClassReq XUSBPS_CLASSREQ_HID_GET_REPORT 0x33 EpBufferSend len %u\n", sizeof(mmos_report01));
						}
			            break;

			        default:
			            //printf("GET reportId no handled 0x%02X\n", reportId);
			            // Cï¿½digo para otros valores del primer byte
						XUsbPs_EpBufferSend(InstancePtr, 0, NULL, 0);
			            break;
			    }
			break;

		case XUSBPS_CLASSREQ_HID_SET_REPORT:
			LOG("ClassReq XUSBPS_CLASSREQ_HID_SET_REPORT\n");
			LOG("ClassReq XUSBPS_CLASSREQ_HID_SET_REPORT wValue 0x%x\n", SetupData->wValue);
			LOG("ClassReq XUSBPS_CLASSREQ_HID_SET_REPORT wIndex %u\n", SetupData->wIndex);
			LOG("ClassReq XUSBPS_CLASSREQ_HID_SET_REPORT wLength %u\n", SetupData->wLength);

            // Esto no esta recibiendo el mensaje, entra en el log XST_USB_NO_BUF
			Status = XUsbPs_EpDataBufferReceive((XUsbPs *)InstancePtr, 0, Reply,
						   ReplyLen);

			if (XST_SUCCESS == Status) {

			}else if(XST_USB_NO_BUF == Status) {
		        //printf("XST_USB_NO_BUF\n");
			}
			else {
		        //printf("No data\n");
			}

			switch (reportId) {
			        case 0x44: // Create New Effect Report
			            //printf("Set reportId 0x44 wValue %u wIndex %u wLength %u\n", SetupData->wValue, SetupData->wIndex, SetupData->wLength);
                        //printf("Create New Effect Report");
			            break;
			        default:
			            //printf("Set reportId no handled 0x%02X\n", reportId);
			            break;
			    }

			XUsbPs_EpBufferSend(InstancePtr, 0, NULL, 0);
			break;

		default:
			LOG("ClassReq DEFAULT\n");
			XUsbPs_EpBufferSend(InstancePtr, 0, NULL, 0);
			//XUsbPs_EpStall(InstancePtr, 0, XUSBPS_EP_DIRECTION_IN);
			break;
	}
}


/*****************************************************************************/
/**
* This function handles a standard device request.
*
* @param	InstancePtr is a pointer to XUsbPs instance of the controller.
* @param	SetupData is a pointer to the data structure containing the
*		setup request.
*
* @return	None.
*
* @note		None.
*
******************************************************************************/
void XUsbPs_StdDevReq(XUsbPs *InstancePtr, XUsbPs_SetupData *SetupData)
{
	int Status;
	int Error = 0;
	u32 Handler;
	u32 TmpBufferLen = 6;
	u8 *TempPtr;
	XUsbPs_Local	*UsbLocalPtr;

	int ReplyLen;
#ifdef __ICCARM__
#pragma data_alignment = 32
	static u8  	Reply[XUSBPS_REQ_REPLY_LEN];
	static u8 TmpBuffer[10];
#else
	static u8  	Reply[XUSBPS_REQ_REPLY_LEN] ALIGNMENT_CACHELINE;
	static u8 TmpBuffer[10] ALIGNMENT_CACHELINE;
#endif

	TempPtr = (u8 *)&TmpBuffer;

	/* Check that the requested reply length is not bigger than our reply
	 * buffer. This should never happen...
	 */
	if (SetupData->wLength > XUSBPS_REQ_REPLY_LEN) {
		LOG("REQUEST DISCARDED wLength %u > XUSBPS_REQ_REPLY_LEN %u\n", SetupData->wLength, XUSBPS_REQ_REPLY_LEN);
        XUsbPs_EpBufferSend(InstancePtr, 0, NULL, 0);
        return;
	}

	UsbLocalPtr = (XUsbPs_Local *) InstancePtr->UserDataPtr;

	LOG("std dev req %d\n", SetupData->bRequest);

	switch (SetupData->bRequest) {

		case XUSBPS_REQ_GET_STATUS:

			switch (SetupData->bmRequestType & XUSBPS_STATUS_MASK) {
				case XUSBPS_STATUS_DEVICE:
					/* It seems we do not have to worry about zeroing out the rest
					 * of the reply buffer even though we are only using the first
					 * two bytes.
					 */
					*((u16 *) &Reply[0]) = 0x1; /* Self powered */
					break;

				case XUSBPS_STATUS_INTERFACE:
					*((u16 *) &Reply[0]) = 0x0;
					break;

				case XUSBPS_STATUS_ENDPOINT: {
						u32 Status;
						int EpNum = SetupData->wIndex;

						Status = XUsbPs_ReadReg(InstancePtr->Config.BaseAddress,
									XUSBPS_EPCRn_OFFSET(EpNum & 0xF));

						if (EpNum & 0x80) { /* In EP */
							if (Status & XUSBPS_EPCR_TXS_MASK) {
								*((u16 *) &Reply[0]) = 1;
							} else {
								*((u16 *) &Reply[0]) = 0;
							}
						} else {	/* Out EP */
							if (Status & XUSBPS_EPCR_RXS_MASK) {
								*((u16 *) &Reply[0]) = 1;
							} else {
								*((u16 *) &Reply[0]) = 0;
							}
						}
						break;
					}

				default:
					LOG("unknown request for status %x\n", SetupData->bmRequestType);
			}
			XUsbPs_EpBufferSend(InstancePtr, 0, Reply, SetupData->wLength);
			break;

		case XUSBPS_REQ_SET_ADDRESS:

			/* With bit 24 set the address value is held in a shadow
			 * register until the status phase is acked. At which point it
			 * address value is written into the address register.
			 */
			XUsbPs_SetDeviceAddress(InstancePtr, SetupData->wValue);
			LOG("Set address %d\n", SetupData->wValue);
			/* There is no data phase so ack the transaction by sending a
			 * zero length packet.
			 */
			XUsbPs_EpBufferSend(InstancePtr, 0, NULL, 0);
			break;

		case XUSBPS_REQ_GET_INTERFACE:
			LOG("Get interface %d/%d/%d\n",
			       SetupData->wIndex, SetupData->wLength,
			       InstancePtr->CurrentAltSetting);
			Response = (u8)InstancePtr->CurrentAltSetting;

			/* Ack the host */
			XUsbPs_EpBufferSend(InstancePtr, 0, &Response, 1);

			break;

		case XUSBPS_REQ_GET_DESCRIPTOR:
			LOG("Get desc %x/%d\n", (SetupData->wValue >> 8) & 0xff,
			       SetupData->wLength);

			/* Get descriptor type. */
			switch ((SetupData->wValue >> 8) & 0xff) {

				case XUSBPS_TYPE_DEVICE_DESC:
				case XUSBPS_TYPE_DEVICE_QUALIFIER:

					/* Set up the reply buffer with the device descriptor
					 * data.
					 */
					ReplyLen = XUsbPs_Ch9SetupDevDescReply(
							   Reply, XUSBPS_REQ_REPLY_LEN);

					ReplyLen = ReplyLen > SetupData->wLength ?
						   SetupData->wLength : ReplyLen;

					if (((SetupData->wValue >> 8) & 0xff) ==
					    XUSBPS_TYPE_DEVICE_QUALIFIER) {
						Reply[0] = (u8)ReplyLen;
						Reply[1] = (u8)0x6;
						Reply[2] = (u8)0x0;
						Reply[3] = (u8)0x2;
						Reply[4] = (u8)0xFF;
						Reply[5] = (u8)0x00;
						Reply[6] = (u8)0x0;
						Reply[7] = (u8)0x10;
						Reply[8] = (u8)0;
						Reply[9] = (u8)0x0;
					}
					Status = XUsbPs_EpBufferSend(InstancePtr, 0,
								     Reply, ReplyLen);
					if (XST_SUCCESS != Status) {
						/* Failure case needs to be handled */
						for (;;);
					}
					else{
						LOG("Get desc DEVICE_DESC, requested %d bytes, send %u bytes\n", SetupData->wLength, ReplyLen);
					}
					break;

				case XUSBPS_TYPE_CONFIG_DESC:

					/* Set up the reply buffer with the configuration
					 * descriptor data.
					 */
					ReplyLen = XUsbPs_Ch9SetupCfgDescReply(
							   Reply, XUSBPS_REQ_REPLY_LEN);

					LOG("get config %d/%d\n", ReplyLen, SetupData->wLength);

					ReplyLen = ReplyLen > SetupData->wLength ?
						   SetupData->wLength : ReplyLen;

					Status = XUsbPs_EpBufferSend(InstancePtr, 0,
								     Reply, ReplyLen);
					if (XST_SUCCESS != Status) {
						/* Failure case needs to be handled */
						for (;;);
					}
					else{
						LOG("Get desc CONFIG_DESC, requested %d bytes, send %u bytes\n", SetupData->wLength, ReplyLen);
					}
					break;


				case XUSBPS_TYPE_STRING_DESC:

					/* Set up the reply buffer with the string descriptor
					 * data.
					 */
					ReplyLen = XUsbPs_Ch9SetupStrDescReply(
							   Reply, XUSBPS_REQ_REPLY_LEN,
							   SetupData->wValue & 0xFF);

					ReplyLen = ReplyLen > SetupData->wLength ?
						   SetupData->wLength : ReplyLen;

					Status = XUsbPs_EpBufferSend(InstancePtr, 0,
								     Reply, ReplyLen);
					if (XST_SUCCESS != Status) {
						/* Failure case needs to be handled */
						for (;;);
					}
					else{
						LOG("Get desc STRING_DESC, requested %d bytes, send %u bytes\n", SetupData->wLength, ReplyLen);
					}
					break;

#ifdef MOUSE_SIMULATION
				case XUSBPS_TYPE_HID_DESC:

					/* Set up the reply buffer with the HID descriptor
					 * data.
					 */
					ReplyLen = XUsbPs_Ch9SetupHidDescReply(
							   Reply, XUSBPS_REQ_REPLY_LEN);

					ReplyLen = ReplyLen > SetupData->wLength ?
						   SetupData->wLength : ReplyLen;

					Status = XUsbPs_EpBufferSend(InstancePtr, 0,
								     Reply, ReplyLen);
					if (XST_SUCCESS != Status) {
						/* Failure case needs to be handled */
						for (;;);
					}
					break;

				case XUSBPS_TYPE_REPORT_DESC:

					/* Set up the reply buffer with the report descriptor
					 * data.
					 */
					ReplyLen = XUsbPs_Ch9SetupReportDescReply(
							   Reply, XUSBPS_REQ_REPLY_LEN);
					LOG("report desc len %d\n", ReplyLen);

					ReplyLen = ReplyLen > SetupData->wLength ?
						   SetupData->wLength : ReplyLen;

					Status = XUsbPs_EpBufferSend(InstancePtr, 0,
								     Reply, ReplyLen);
					if (XST_SUCCESS != Status) {
						/* Failure case needs to be handled */
						for (;;);
					}
					break;
#endif /* MOUSE_SIMULATION */

				case XUSBPS_TYPE_HID_REPORT_DESCRIPTOR:
					LOG("Alejandro XUSBPS_REQ_HID_REPORT_DESCRIPTOR \r\n\r");
					ReplyLen = XUsbPs_Ch9SetupHidReportDescReply(
							   Reply, XUSBPS_REQ_REPLY_LEN);

					ReplyLen = ReplyLen > SetupData->wLength ?
						   SetupData->wLength : ReplyLen;

					Status = XUsbPs_EpBufferSend(InstancePtr, 0,
								     Reply, ReplyLen);
					if (XST_SUCCESS != Status) {
						/* Failure case needs to be handled */
						for (;;);
					}
					else{
						LOG("Get desc HID_REPORT_DESC, requested %d bytes, send %u bytes\n", SetupData->wLength, ReplyLen);
					}
					break;

				default:
					Error = 1;
					break;
			}
			break;


		case XUSBPS_REQ_SET_CONFIGURATION:

			/*
			 *  allow configuration index 0 and 1.
			 */
			if (((SetupData->wValue & 0xff) != 1 ) && ((SetupData->wValue & 0xff) != 0 )) {
				Error = 1;
				break;
			}

			UsbLocalPtr->CurrentConfig = SetupData->wValue & 0xff;


			/* Call the application specific configuration function to
			 * apply the configuration with the given configuration index.
			 */
			XUsbPs_SetConfiguration(InstancePtr,
						UsbLocalPtr->CurrentConfig);

			if (InstancePtr->AppData != NULL) {
				XUsbPs_SetConfigurationApp(InstancePtr, SetupData);
			}

			/* There is no data phase so ack the transaction by sending a
			 * zero length packet.
			 */
			XUsbPs_EpBufferSend(InstancePtr, 0, NULL, 0);
			break;


		case XUSBPS_REQ_GET_CONFIGURATION:

				XUsbPs_EpBufferSend(InstancePtr, 0,
						    &UsbLocalPtr->CurrentConfig, 1);
			break;


		case XUSBPS_REQ_CLEAR_FEATURE:
			switch (SetupData->bmRequestType & XUSBPS_STATUS_MASK) {
				case XUSBPS_STATUS_ENDPOINT:
					if (SetupData->wValue == XUSBPS_ENDPOINT_HALT) {
						int EpNum = SetupData->wIndex;

						if (EpNum & 0x80) {	/* In ep */
							XUsbPs_ClrBits(InstancePtr,
								       XUSBPS_EPCRn_OFFSET(EpNum & 0xF),
								       XUSBPS_EPCR_TXS_MASK);
						} else { /* Out ep */
							XUsbPs_ClrBits(InstancePtr,
								       XUSBPS_EPCRn_OFFSET(EpNum),
								       XUSBPS_EPCR_RXS_MASK);
						}
					}
					/* Ack the host ? */
					XUsbPs_EpBufferSend(InstancePtr, 0, NULL, 0);
					break;

				default:
					Error = 1;
					break;
			}

			break;

		case XUSBPS_REQ_SET_FEATURE:
			switch (SetupData->bmRequestType & XUSBPS_STATUS_MASK) {
				case XUSBPS_STATUS_ENDPOINT:
					if (SetupData->wValue == XUSBPS_ENDPOINT_HALT) {
						int EpNum = SetupData->wIndex;

						if (EpNum & 0x80) {	/* In ep */
							XUsbPs_SetBits(InstancePtr,
								       XUSBPS_EPCRn_OFFSET(EpNum & 0xF),
								       XUSBPS_EPCR_TXS_MASK);

						} else { /* Out ep */
							XUsbPs_SetBits(InstancePtr,
								       XUSBPS_EPCRn_OFFSET(EpNum),
								       XUSBPS_EPCR_RXS_MASK);
						}
					}
					/* Ack the host ? */
					XUsbPs_EpBufferSend(InstancePtr, 0, NULL, 0);

					break;
				case XUSBPS_STATUS_DEVICE:
					if (SetupData->wValue == XUSBPS_TEST_MODE) {
						int TestSel = (SetupData->wIndex >> 8) & 0xFF;

						/* Ack the host, the transition must happen
							after status stage and < 3ms */
						XUsbPs_EpBufferSend(InstancePtr, 0, NULL, 0);
						usleep(1000);

						switch (TestSel) {
							case XUSBPS_TEST_J:
							case XUSBPS_TEST_K:
							case XUSBPS_TEST_SE0_NAK:
							case XUSBPS_TEST_PACKET:
							case XUSBPS_TEST_FORCE_ENABLE:
								XUsbPs_SetBits(InstancePtr, \
									       XUSBPS_PORTSCR1_OFFSET, \
									       TestSel << 16);
								break;
							default:
								/* Unsupported test selector */
								break;
						}
						break;
					}

				default:
					Error = 1;
					break;
			}

			break;


		/* For set interface, check the alt setting host wants */
		case XUSBPS_REQ_SET_INTERFACE:

			LOG("set interface %d/%d\n", SetupData->wValue, SetupData->wIndex);
			/* Only ISO supported */
			if (InstancePtr->AppData != NULL)
				XUsbPs_SetInterfaceHandler(
					(XUsbPs *)InstancePtr, SetupData);

			/* Ack the host after device finishes the operation */
			Error = XUsbPs_EpBufferSend(InstancePtr, 0, NULL, 0);
			if (Error) {
				LOG("EpBufferSend failed %d\n", Error);
			}
			break;
		case XUSBPS_REQ_SET_SEL:
			LOG("SET SEL \r\n\r");

			Status = XUsbPs_EpBufferReceive((XUsbPs *)InstancePtr,
							0, &TempPtr, &TmpBufferLen, &Handler);
			if (XST_SUCCESS == Status) {
				/* Return the buffer. */
				XUsbPs_EpBufferRelease(Handler);
			}

			break;

		case XUSBPS_REQ_SET_ISOCH_DELAY:
			LOG("SET ISOCH DELAY \r\n\r");
			break;

		default:
			Error = 1;
			break;
	}

	/* Set the send stall bit if there was an error */
	if (Error) {
		LOG("std dev req %d/%d error, stall 0 in out\n",
		       SetupData->bRequest, (SetupData->wValue >> 8) & 0xff);
		XUsbPs_EpStall(InstancePtr, 0, XUSBPS_EP_DIRECTION_IN |
			       XUSBPS_EP_DIRECTION_OUT);
	}
}

/*****************************************************************************/
/**
* This function handles a vendor request.
*
* @param	InstancePtr is a pointer to XUsbPs instance of the controller.
* @param	SetupData is a pointer to the data structure containing the
*		setup request.
*
* @return
*		- XST_SUCCESS if successful.
*		- XST_FAILURE if an Error occurred.
*
* @note
*		This function is a template to handle vendor request for control
*		IN and control OUT endpoints. The control OUT endpoint can
*		receive only 64 bytes of data per dTD. For receiving more than
*		64 bytes of vendor data on control OUT endpoint, change the
*		buffer size of the control OUT endpoint. Otherwise the results
*		are unexpected.
*
******************************************************************************/
int XUsbPs_HandleVendorReq(XUsbPs *InstancePtr, XUsbPs_SetupData *SetupData)
{
	u8      *BufferPtr;
	u32     BufferLen;
	u32     Handle;
	u32	Reg;
#ifdef __ICCARM__
#pragma data_alignment = 32
	const static u8	Reply[8] = {0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17};
#else
	const static u8	Reply[8] ALIGNMENT_CACHELINE =
	{0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17};
#endif
	u8	EpNum = 0;
	int 	Status;
	int 	Direction;
	int 	Timeout;

	/* Check the direction, USB 2.0 section 9.3 */
	Direction = SetupData->bmRequestType & (1 << 7);

	if (!Direction) {
		/* Control OUT vendor request */
		if (SetupData->wLength > 0) {
			/* Re-Prime the endpoint to receive Setup DATA */
			XUsbPs_EpPrime(InstancePtr, 0, XUSBPS_EP_DIRECTION_OUT);

			/* Check whether EP prime is successful or not */
			Timeout = XUSBPS_TIMEOUT_COUNTER;
			do {
				Reg = XUsbPs_ReadReg(InstancePtr->Config.BaseAddress,
						     XUSBPS_EPPRIME_OFFSET);
			} while (((Reg & (1 << EpNum)) == 1) && --Timeout);

			if (!Timeout) {
				return XST_FAILURE;
			}

			/* Get the Setup DATA, don't wait for the interrupt */
			Timeout = XUSBPS_TIMEOUT_COUNTER;
			do {
				Status = XUsbPs_EpBufferReceive(InstancePtr,
								EpNum, &BufferPtr, &BufferLen, &Handle);
			} while ((Status != XST_SUCCESS) && --Timeout);

			if (!Timeout) {
				return XST_FAILURE;
			}

			Xil_DCacheInvalidateRange((unsigned int)BufferPtr,
						  BufferLen);
			int 	Len;
			LOG("Vendor data:\r\n");
			for (Len = 0; Len < BufferLen; Len++) {
				LOG("%02x ", BufferPtr[Len]);
			}

			if (Status == XST_SUCCESS) {
				/* Zero length ACK */
				Status = XUsbPs_EpBufferSend(InstancePtr, EpNum,
							     NULL, 0);
				if (Status != XST_SUCCESS) {
					return XST_FAILURE;
				}
			}
		}
	} else {
		if (SetupData->wLength > 0) {
			/* Control IN vendor request */
			Status = XUsbPs_EpBufferSend(InstancePtr, EpNum, Reply,
						     SetupData->wLength);
			if (Status != XST_SUCCESS) {
				return XST_FAILURE;
			}
		}
	}
	return XST_SUCCESS;
}

/****************************************************************************/
/**
 * Set the Config state
 *
 * @param	InstancePtr is a private member of Usb_DevData instance.
 * @param	Flag is the config value.
 *
 * @return	None.
 *
 * @note		None.
 *
 *****************************************************************************/
void XUsbPs_SetConfigDone(void *InstancePtr, u8 Flag)
{
	((XUsbPs *)InstancePtr)->IsConfigDone = Flag;
}

/****************************************************************************/
/**
 * Get the Config state
 *
 * @param	InstancePtr is a private member of Usb_DevData instance.
 *
 * @return	Current configuration value
 *
 * @note		None.
 *
 *****************************************************************************/
u8 XUsbPs_GetConfigDone(void *InstancePtr)
{
	return (((XUsbPs *)InstancePtr)->IsConfigDone);
}
