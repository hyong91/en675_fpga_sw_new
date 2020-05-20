#ifndef __DEV_FUNCTIONS_H__
#define __DEV_FUNCTIONS_H__

//#define EN675_HEVC_TEST
#if 1//defined(EN675_HEVC_TEST)
extern BYTE test_isp_codec_flag;
extern BYTE test_isp_codec_done;
extern BYTE test_isp_update_flag;
extern BYTE test_isp_done_flag;

extern UINT BIT_STREAM_LOCK;
extern UINT BIT_STREAM_ADDR;
extern UINT BIT_STREAM_SIZE;
extern UINT BIT_STREAM_TYPE;
extern UINT BIT_STREAM_FRNUM;
extern UINT BIT_STREAM_RECNUM;
extern ULONG CodecENCTimeStart;
extern ULONG CodecENConlyTimeStart;
#endif
//******************************************************************************
// x. Function
//------------------------------------------------------------------------------

// irq.c ///////////////////////////////////////////////////////////////////////
extern UINT enx_externalirq_is_enable(UINT cpuid, eIRQ_GROUP_INDEX perlIdx, uint64 type);
extern void enx_externalirq_perl(eIRQ_GROUP_INDEX perlIdx, uint64 onoff, uint64 type);
extern void enx_timerirq_next(void);
extern void enx_timerirq_init(void);
extern void enx_exirq_view(void);
extern void enx_externalirq_init(void);
extern void enx_externalirq_init_cpu0(void);
extern void enx_externalirq_init_cpu1(void);
extern void enx_externalirq_init_cpu2(void);
extern void enx_externalirq_init_cpu3(void);
extern void enx_wake_cpu(int cpu_id);
extern void enx_wake_message_to_cpu0(UINT flag);
extern void enx_wake_message_to_cpu1(UINT flag);
extern void enx_wake_message_to_cpu2(UINT flag);
extern void enx_wake_message_to_cpu3(UINT flag);


// Device driver ///////////////////////////////////////////////////////////////

extern void DdrTest(void); // ddr.c
extern ENX_OKFAIL DdrInit(BYTE bCH, BYTE Sel, UINT nWrltc); // ddr.c

extern void SflsInit(void);
extern void SflsSetClkdiv(UINT Clkdiv);
extern UINT SflsGetClkdiv(void);
extern void SflsSetClk(UINT Speed_Hz);
extern UINT SflsGetClk(void);
extern UINT SflsGetinfo(void);
extern UINT SflsGetSize(void);
extern void SflsWriteEnable(void);
extern void SflsSectErase(UINT addr, ENX_YN sync);
extern void Sfls32KErase(UINT addr, ENX_YN sync);
extern void Sfls64KErase(UINT addr, ENX_YN sync);
extern void SflsChipErase(ENX_YN sync);
extern UINT SflsGetUsrreq(void);
extern void SflsSingleCommand(BYTE cmd, UINT CMD_MODE);
extern void SflsWriteStatus(BYTE status);
extern BYTE SflsReadStatus(void);
extern void SflsWriteReg(BYTE wrdata, BYTE len, BYTE iomode);
extern UINT SflsReadReg(BYTE cmd, BYTE iomode, BYTE gap);
extern void SflsEnter4B(void);
extern void SflsExit4B(void);
extern void SflsEnterQPI(void);
extern void SflsExitQPI(void);
extern void SflsEnterQE(void);
extern void SflsExitQE(void);
extern void SflsEnterProtection(void);
extern void SflsExitProtection(void);
extern void SflsReadSFDP(BYTE *sfdp_bin);
extern void SflsViewerSFDP(BYTE *sfdp_bin);
extern SFLScontrol *SflsEn25qh128a_GetControl(void);
extern SFLScontrol *SflsEn25qh256_GetControl(void);
extern SFLScontrol *SflsGd25q128c_GetControl(void);
extern SFLScontrol *SflsIs25lp064_GetControl(void);
extern SFLScontrol *SflsIs25lp128_GetControl(void);
extern SFLScontrol *SflsIs25lp256_GetControl(void);
extern SFLScontrol *SflsMx25u12832f_GetControl(void);
extern SFLScontrol *SflsMx25l12835f_GetControl(void);
extern SFLScontrol *SflsN25q128a_GetControl(void);
extern SFLScontrol *SflsW25q256jvq_GetControl(void);
extern SFLScontrol *SflsW25q64jviq_GetControl(void);
extern void SflsRegShow(ENX_YN isDetail);

extern void GpioInit(void);
extern void GpioSetEdge(UINT nCH, GPIO_EDGE edge);
extern UINT GpioGetEdge(UINT nCH);
extern void GpioSetDir(UINT nCH, GPIO_DIR dir);
extern GPIO_DIR GpioGetDir(UINT nCH);
extern void GpioSetOut(UINT nCH, GPIO_OUT out);
extern GPIO_OUT GpioGetOut(UINT nCH);
extern void GpioFuncPin(UINT nCH, UINT nSel);
extern void GpioFuncPinOff(UINT nCH);
extern UINT GpioGetFuncPin(UINT nCH);
extern UINT GpioGetPin(UINT nCH);
extern void GpioIrqCallback(UINT nCH, irq_fn irqfn, void *arg);
extern void GpioSetIrqEn(UINT nCH, ENX_SWITCH sw);
extern ENX_SWITCH GpioGetIrqEn(UINT nCH);
extern void GpioIrqClear(UINT nCH);
extern UINT GpioIsIrq(UINT nCH);
extern void IrqGpio(UINT nCH);

extern void UartInit(UINT nCH, UINT Speed_Hz);
extern void UartDeinit(UINT nCH);
extern void UartSetClkdiv(UINT nCH, UINT Clkdiv);
extern UINT UartGetClkdiv(UINT nCH);
extern void UartSetClk(UINT nCH, UINT Speed_Hz);
extern UINT UartGetClk(UINT nCH);
extern void UartSetTxType(UINT nCH, UINT Type);
extern UINT UartGetTxType(UINT nCH);
extern void UartSetStopbit(UINT nCH, UINT Stopbit);
extern UINT UartGetStopbit(UINT nCH);
extern void UartSetParityMode(UINT nCH, UART_PARITY_MODE mode);
extern UART_PARITY_MODE UartGetParityMode(UINT nCH);
extern void UartTx(UINT nCH, char data);
extern void UartTxSetByte(UINT nCH, char data);
extern UINT UartTxIsEmpty(UINT nCH);
extern UINT UartTxIsFull(UINT nCH);
extern void UartTxIrqCallback(UINT nCH, irq_fn irqfn, void *arg);
extern void UartTxSetIrqEn(UINT nCH, ENX_SWITCH sw);
extern ENX_SWITCH UartTxGetIrqEn(UINT nCH);
extern void UartTxIrqClear(UINT nCH);
extern UINT UartTxIsIrq(UINT nCH);
extern UINT UartRx(UINT nCH);
extern UINT UartRxGetByte(UINT nCH);
extern UINT UartRxIsEmpty(UINT nCH);
extern UINT UartRxIsFull(UINT nCH);
extern void UartRxIrqCallback(UINT nCH, irq_fn irqfn, void *arg);
extern void UartRxSetIrqEn(UINT nCH, ENX_SWITCH sw);
extern ENX_SWITCH UartRxGetIrqEn(UINT nCH);
extern void UartRxIrqClear(UINT nCH);
extern UINT UartRxIsIrq(UINT nCH);
extern void IrqUart(UINT nCH);

extern void I2cInit(UINT nCH, UINT Speed_Hz);
extern void I2cDeInit(UINT nCH);
extern void I2cSetClkdiv(UINT nCH, UINT Clkdiv);
extern UINT I2cGetClkdiv(UINT nCH);
extern void I2cSetClk(UINT nCH, UINT Speed_Hz);
extern UINT I2cGetClk(UINT nCH);
extern void I2cSetMode(UINT nCH, I2C_MODE mode);
extern I2C_MODE I2cGetMode(UINT nCH);
extern void I2cSetBitmode(UINT nCH, I2C_BITMODE bitmode);
extern I2C_BITMODE I2cGetBitmode(UINT nCH);
extern UINT I2cGetACT(UINT nCH);
extern UINT I2cGetMstCol(UINT nCH);
extern UINT I2cGetMstAck(UINT nCH);
extern UINT I2cWrite(UINT nCH, BYTE dat, BYTE last, BYTE repeat);
extern UINT I2cRead(UINT nCH, BYTE last, BYTE repeat);
extern ENX_OKFAIL I2cCheck(UINT nCH, BYTE addr);
extern void I2cChCheck(UINT nCH);
extern void I2cSlvTest(UINT nCH);
extern void I2cSetSlvAddr(UINT nCH, UINT nAddr);
extern UINT I2cGetSlvAddr(UINT nCH);
extern UINT I2cGetSlvSDA(UINT nCH);
extern UINT I2cGetSlvSCL(UINT nCH);
extern UINT I2cGetSlvAckIn(UINT nCH);
extern void I2cIrqCallback(UINT nCH, irq_fn irqfn, void *arg);
extern void I2cSetIrqEn(UINT nCH, ENX_SWITCH sw);
extern ENX_SWITCH I2cGetIrqEn(UINT nCH);
extern void I2cIrqClear(UINT nCH);
extern UINT I2cIsIrq(UINT nCH);
extern void IrqI2c(UINT nCH);

extern void SpiInit(UINT nCH, UINT Speed_Hz, BYTE nBIT, BYTE isLSB);
extern void SpiDeinit(UINT nCH);
extern void SpiSetEn(UINT nCH, ENX_SWITCH sw);
extern ENX_SWITCH SpiGetEn(UINT nCH);
extern void SpiSetClkdiv(UINT nCH, UINT Clkdiv);
extern UINT SpiGetClkdiv(UINT nCH);
extern void SpiSetClk(UINT nCH, UINT Speed_Hz);
extern UINT SpiGetClk(UINT nCH);
extern void SpiSetBitmode(UINT nCH, SPI_BITMODE bitmode);
extern SPI_BITMODE SpiGetBitmode(UINT nCH);
extern void SpiSetOnebitmode(UINT nCH, SPI_ONEBITMODE onebitmode);
extern SPI_ONEBITMODE SpiGetOneBitmode(UINT nCH);
extern void SpiSetClkmode(UINT nCH, SPI_CLKDIR_MODE clkmode);
extern SPI_CLKDIR_MODE SpiGetClkmode(UINT nCH);
extern void SpiSetWs(UINT nCH, SPI_WORD_SIZE wdsize);
extern SPI_WORD_SIZE SpiGetWs(UINT nCH);
extern void SpiSetCs(UINT nCH, SPI_CSMODE cs);
extern SPI_CSMODE SpiGetCs(UINT nCH);
extern void SpiWrite(UINT nCH, BYTE *dat);
extern void SpiRead(UINT nCH, BYTE *dat);
extern void SpiRW(UINT nCH, BYTE *WrDat, BYTE *RdDat);
extern void SpiIrqCallback(UINT nCH, irq_fn irqfn, void *arg);
extern void SpiSetIrqEn(UINT nCH, ENX_SWITCH sw);
extern ENX_SWITCH SpiGetIrqEn(UINT nCH);
extern void SpiIrqClear(UINT nCH);
extern UINT SpiIsIrq(UINT nCH);
extern void IrqSpi(UINT nCH);

extern UINT BDmaRegGetControl(UINT nCH);
extern UINT BDmaRegGetFull(UINT nCH);
extern UINT BDmaRegGetDoneVal(UINT nCH);
extern UINT BDmaRegGetDonePtr(UINT nCH);
extern UINT BDmaRegGetJobPtr(UINT nCH);
extern UINT BDmaRegGetIrq(UINT nCH);
extern UINT BDmaRegGetIrqEn(UINT nCH);
extern UINT BDmaRegGetIrqClr(UINT nCH);
extern UINT BDmaRegGetValue(UINT nCH);
extern UINT BDmaRegGetMode(UINT nCH);
extern UINT BDmaRegGetGo(UINT nCH);
extern UINT BDmaRegGetSrc(UINT nCH);
extern UINT BDmaRegGetDst(UINT nCH);
extern UINT BDmaRegGetLen(UINT nCH);
extern void BDmaInit(void);
extern void BDmaMemCpy_isr(UINT nCH, BYTE *apbDst, BYTE *apbSrc, UINT anNum);
extern UINT BDmaMemCpy_isr_async(UINT nCH, BYTE *apbDst, BYTE *apbSrc, UINT anNum);
extern void BDmaMemCpy_rtos(UINT nCH, BYTE *apbDst, BYTE *apbSrc, UINT anNum);
extern UINT BDmaMemCpy_rtos_async(UINT nCH, BYTE *apbDst, BYTE *apbSrc, UINT anNum);
extern void BDmaMemCpy_rtos_flush(UINT nCH, BYTE *apbDst, BYTE *apbSrc, UINT anNum);
extern void BDmaMemCpy_rtos_discard_flush(UINT nCH, BYTE *apbDst, BYTE *apbSrc, UINT anNum);
extern void BDmaMemSet_isr(UINT nCH, BYTE *apbDst, BYTE abVal, UINT anNum);
extern UINT BDmaMemSet_isr_async(UINT nCH, BYTE *apbDst, BYTE abVal, UINT anNum);
extern void BDmaMemSet_rtos(UINT nCH, BYTE *apbDst, BYTE abVal, UINT anNum);
extern UINT BDmaMemSet_rtos_async(UINT nCH, BYTE *apbDst, BYTE abVal, UINT anNum);
extern void BDmaIrqCallback(UINT nCH, irq_fn irqfn, void *arg);
extern void BDmaSetIrqEn(UINT nCH, ENX_SWITCH sw);
extern ENX_SWITCH BDmaGetIrqEn(UINT nCH);
extern void BDmaIrqClear(UINT nCH);
extern UINT BDmaIsIrq(UINT nCH);
extern void IrqBDma(UINT nCH);

extern UINT CDmaRegGetControl(UINT nCH);
extern UINT CDmaRegGetFull(UINT nCH);
extern UINT CDmaRegGetDoneVal(UINT nCH);
extern UINT CDmaRegGetDonePtr(UINT nCH);
extern UINT CDmaRegGetJobPtr(UINT nCH);
extern UINT CDmaRegGetIrq(UINT nCH);
extern UINT CDmaRegGetIrqEn(UINT nCH);
extern UINT CDmaRegGetIrqClr(UINT nCH);
extern UINT CDmaRegGetValue(UINT nCH);
extern UINT CDmaRegGetMode(UINT nCH);
extern UINT CDmaRegGetGo(UINT nCH);
extern UINT CDmaRegGetSrc(UINT nCH);
extern UINT CDmaRegGetDst(UINT nCH);
extern UINT CDmaRegGetLen(UINT nCH);
extern void CDmaInit(void);
extern void CDmaMemCpy_isr(UINT nCH, BYTE *apbDst, BYTE *apbSrc, UINT anNum);
extern UINT CDmaMemCpy_isr_async(UINT nCH, BYTE *apbDst, BYTE *apbSrc, UINT anNum);
extern void CDmaMemCpy_rtos(UINT nCH, BYTE *apbDst, BYTE *apbSrc, UINT anNum);
extern UINT CDmaMemCpy_rtos_async(UINT nCH, BYTE *apbDst, BYTE *apbSrc, UINT anNum);
extern void CDmaMemSet_isr(UINT nCH, BYTE *apbDst, BYTE abVal, UINT anNum);
extern UINT CDmaMemSet_isr_async(UINT nCH, BYTE *apbDst, BYTE abVal, UINT anNum);
extern void CDmaMemSet_rtos(UINT nCH, BYTE *apbDst, BYTE abVal, UINT anNum);
extern UINT CDmaMemSet_rtos_async(UINT nCH, BYTE *apbDst, BYTE abVal, UINT anNum);
extern void CDmaIrqCallback(UINT nCH, irq_fn irqfn, void *arg);
extern void CDmaSetIrqEn(UINT nCH, ENX_SWITCH sw);
extern ENX_SWITCH CDmaGetIrqEn(UINT nCH);
extern void CDmaIrqClear(UINT nCH);
extern UINT CDmaIsIrq(UINT nCH);
extern void IrqCDma(UINT nCH);

extern void TimerInit(UINT nCH);
extern void TimerDeInit(UINT nCH);
extern void TimerSetFreq(UINT nCH, UINT nDiv, UINT nLmt, UINT nTrig);
extern void TimerStart(UINT nCH);
extern void TimerStop(UINT nCH);
extern void TimerSetEn(UINT nCH, ENX_SWITCH sw);
extern ENX_SWITCH TimerGetEn(UINT nCH);
extern void TimerSetCken(UINT nCH, ENX_SWITCH sw);
extern ENX_SWITCH TimerGetCken(UINT nCH);
extern void TimerSetPWMEn(UINT nCH, ENX_SWITCH sw);
extern ENX_SWITCH TimerGetPWMEn(UINT nCH);
extern void TimerSetDiv(UINT nCH, UINT nDiv);
extern UINT TimerGetDiv(UINT nCH);
extern void TimerSetLmt(UINT nCH, UINT nLmt);
extern UINT TimerGetLmt(UINT nCH);
extern void TimerSetTrig(UINT nCH, UINT nTrig);
extern UINT TimerGetTrig(UINT nCH);
extern UINT TimerGetCount(UINT nCH);
extern void TimerIrqCallback(UINT nCH, irq_fn irqfn, void *arg);
extern void TimerSetIrqEn(UINT nCH, ENX_SWITCH sw);
extern ENX_SWITCH TimerGetIrqEn(UINT nCH);
extern void TimerIrqClear(UINT nCH);
extern UINT TimerIsIrq(UINT nCH);
extern void IrqTimer(UINT nCH);

extern void MdioInit(UINT Speed_Hz);
extern void MdioRead(BYTE PhyAdr, BYTE RegAdr, WORD *RdDat);
extern void MdioWrite(BYTE PhyAdr, BYTE RegAdr, WORD WrDat);
extern void MdioSetClklmt(UINT Clklmt);
extern UINT MdioGetClklmt(void);
extern void MdioSetClk(UINT Speed_Hz);
extern UINT MdioGetClk(void);

extern void EthInit(void);
extern void EthSetTxClockPowerEn(ENX_SWITCH sw);
extern ENX_SWITCH EthGetTxClockPowerEn(void);
extern void EthSetRxClockPowerEn(ENX_SWITCH sw);
extern ENX_SWITCH EthGetRxClockPowerEn(void);
extern void EthRxFilterMacAdr(BYTE *addr);
extern UINT EthRxFilterInsert(BYTE *addr);
extern UINT EthRxFilterDelete(BYTE *addr);
extern void EthRxFilterList(void);
extern void EthRxSetBuffer(BYTE *addr, UINT rx_lmt);
extern void EthRxSetAddrOffset(UINT rx_adrofs);
extern void EthTxPacket(BYTE *addr, UINT Len);
extern void EthSetTxColen(ENX_SWITCH onoff);
extern void EthSetRxTxClockDly(BYTE u8TXe, BYTE u8TXd, BYTE u8RXe, BYTE u8RXd);
extern void EthSetTxDly(BYTE u8TXEN, BYTE u8TXD);
extern void EthRxTxInit(UINT type, UINT speed, UINT duplex);
extern void EthSetRxFilterEn(ENX_SWITCH sw);
extern ENX_SWITCH EthGetRxFilterEn(void);
extern void EthSetRxEn(ENX_SWITCH sw);
extern ENX_SWITCH EthGetRxEn(void);
extern void EthTxIrqCallback(irq_fn irqfn, void *arg);
extern void EthRxIrqCallback(irq_fn irqfn, void *arg);
extern void EthSetTxIrqEn(ENX_SWITCH sw);
extern void EthSetRxIrqEn(ENX_SWITCH sw);
extern ENX_SWITCH EthGetTxIrqEn(void);
extern ENX_SWITCH EthGetRxIrqEn(void);
extern void EthTxIrqClear(void);
extern void EthRxIrqClear(void);
extern UINT EthIsTxIrq(void);
extern UINT EthIsRxIrq(void);
extern void IrqEthTx(void);
extern void IrqEthRx(void);
extern void EthMacAddrCheck(BYTE *addr);

extern void I2sInit(void);
extern void I2sMstInit(UINT freq, UINT byte);
extern void I2sSlvInit(void);
extern void I2sSetTxEdn(UINT txedn);
extern UINT I2sGetTxEdn(void);
extern void I2sSetRxEdn(UINT rxedn);
extern UINT I2sGetRxEdn(void);

extern void I2sTxCfg(UINT tx_mode, UINT tx_cd, UINT tx_dw, UINT rd_byte, UINT rd_dw, UINT rd_len, UINT tx_lr);
extern void I2sSetTxMode(UINT tx_mode);
extern UINT I2sGetTxMode(void);
extern void I2sSetTxCodec(UINT tx_cd);
extern UINT I2sGetTxCodec(void);
extern void I2sSetTxDw(UINT tx_dw);
extern UINT I2sGetTxDw(void);
extern void I2sSetRdByte(UINT rd_byte);
extern UINT I2sGetRdByte(void);
extern void I2sSetRdDw(UINT rd_dw);
extern UINT I2sGetRdDw(void);
extern void I2sSetRdLen(UINT rd_len);
extern UINT I2sGetRdLen(void);
extern void I2sSetTxLr(UINT tx_lr);
extern UINT I2sGetTxLr(void);
extern void I2sTxBaseAddr(BYTE *addr);
extern UINT I2sTxPos(void);
extern void I2sSetTxEn(ENX_SWITCH sw);
extern ENX_SWITCH I2sGetTxEn(void);

extern void I2sRxCfg(UINT rx_mode, UINT rx_cd, UINT rx_dw, UINT wr_byte, UINT wr_dw, UINT wr_len);
extern void I2sSetRxMode(UINT rx_mode);
extern UINT I2sGetRxMode(void);
extern void I2sSetRxCodec(UINT rx_cd);
extern UINT I2sGetRxCodec(void);
extern void I2sSetRxDw(UINT rx_dw);
extern UINT I2sGetRxDw(void);
extern void I2sSetWrByte(UINT wr_byte);
extern UINT I2sGetWrByte(void);
extern void I2sSetWrDw(UINT wr_dw);
extern UINT I2sGetWrDw(void);
extern void I2sSetWrLen(UINT wr_len);
extern UINT I2sGetWrLen(void);
extern void I2sRxBaseAddr(BYTE *addr);
extern UINT I2sRxPos(void);
extern void I2sSetRxEn(ENX_SWITCH sw);
extern ENX_SWITCH I2sGetRxEn(void);

extern void I2sTxIrqCallback(irq_fn irqfn, void *arg);
extern void I2sRxIrqCallback(irq_fn irqfn, void *arg);
extern void I2sSetTxIrqEn(ENX_SWITCH sw);
extern void I2sSetRxIrqEn(ENX_SWITCH sw);
extern ENX_SWITCH I2sGetTxIrqEn(void);
extern ENX_SWITCH I2sGetRxIrqEn(void);
extern void I2sTxIrqClear(void);
extern void I2sRxIrqClear(void);
extern UINT I2sTxIsIrq(void);
extern UINT I2sRxIsIrq(void);
extern void IrqI2sTx(void);
extern void IrqI2sRx(void);

extern void SdioInit(UINT nCH, UINT Speed_Hz);
extern ENX_OKFAIL SdioCmd(UINT nCH, BYTE Cmd, UINT Arg, UINT *nResp, eCmdRespType cmdType);
extern ENX_OKFAIL SdioCmd_async(UINT nCH, BYTE Cmd, UINT Arg, ENX_ENABLE bEnResp, eCmdRespType cmdType);
extern ENX_OKFAIL SdioCmdResp(UINT nCH, UINT *nResp, eCmdRespType cmdType);
extern void SdioSetDelayfn(UINT nCH, user_delay_fn user_delay);
extern void SdioGetResp(UINT nCH, UINT *nResp, eCmdRespType cmdType);
extern void SdioSetClockDef(UINT nCH);
extern void SdioSetClock(UINT nCH, UINT Speed_Hz);
extern UINT SdioGetClock(UINT nCH);
extern void SdioSetClockDiv(UINT nCH, UINT nClkDiv);
extern UINT SdioGetClockDiv(UINT nCH);
extern void SdioSetClockEn(UINT nCH, ENX_SWITCH sw);
extern ENX_SWITCH SdioGetClockEn(UINT nCH);
extern void SdioClockDivPrint(UINT nCH, char *strBuffer);
extern void SdioSetBitMode(UINT nCH, eSDIO_BIT_MODE bitmode);
extern eSDIO_BIT_MODE SdioGetBitMode(UINT nCH);
extern void SdioSetIoMode(UINT nCH, eSDIO_IO_MODE iomode);
extern eSDIO_IO_MODE SdioGetIoMode(UINT nCH);
extern void SdioSetIoFnvalue(UINT nCH, UINT cmd53fn);
extern void SdioSetIoBmMode(UINT nCH, eSDIO_CMD53_BM cmd53bm);
extern void SdioSetIoOpCode(UINT nCH, eSDIO_CMD53_OP cmd53op);
extern void SdioSetDataBlockByte(UINT nCH, UINT BlkByte);
extern UINT SdioGetDataBlockByte(UINT nCH);
extern UINT SdioIsDataEn(UINT nCH);
extern ENX_OKFAIL SdioDataIO(UINT nCH, eSDIO_DIO_TYPE iotype, ULONG MemAdr, UINT BlkAdr, UINT BlkCnt);
extern ENX_OKFAIL SdioDataIO_async(UINT nCH, eSDIO_DIO_TYPE iotype, ULONG MemAdr, UINT BlkAdr, UINT BlkCnt);
extern ENX_OKFAIL SdioDataIO_resp(UINT nCH, eSDIO_DIO_TYPE iotype);
extern void SdioSetDataCmd(UINT nCH, eSDIO_DIO_TYPE iotype, UINT nCmd);
extern UINT SdioGetDataCmd(UINT nCH, eSDIO_DIO_TYPE iotype);
extern void SdioSetTrg(UINT nCH, int val);
extern void SdioIoIrqCallback(UINT nCH, irq_fn irqfn, void *arg);
extern void SdioCmdIrqCallback(UINT nCH, irq_fn irqfn, void *arg);
extern void SdioDatIrqCallback(UINT nCH, irq_fn irqfn, void *arg);
extern void SdioSetIoIrqEn(UINT nCH, ENX_SWITCH sw);
extern void SdioSetCmdIrqEn(UINT nCH, ENX_SWITCH sw);
extern void SdioSetDatIrqEn(UINT nCH, ENX_SWITCH sw);
extern ENX_SWITCH SdioGetIoIrqEn(UINT nCH);
extern ENX_SWITCH SdioGetCmdIrqEn(UINT nCH);
extern ENX_SWITCH SdioGetDatIrqEn(UINT nCH);
extern void SdioIoIrqClear(UINT nCH);
extern void SdioCmdIrqClear(UINT nCH);
extern void SdioDatIrqClear(UINT nCH);
extern UINT SdioIoIsIrq(UINT nCH);
extern UINT SdioCmdIsIrq(UINT nCH);
extern UINT SdioDatIsIrq(UINT nCH);
extern void IrqSdio(UINT nCH);
extern void SdioRegShow(UINT isDetail);

extern void SdioCdInit(UINT nCH);
extern UINT SdioCdDet(void);
extern ENX_OKFAIL SdioCdInitProcess(void);
extern void SdioCdClockDown(void);
extern void SdioCdClockSet(WORD Clkdiv);
extern void SdioCdClockRestore(void);

extern UINT SdioCdGetActive(void);
extern UINT SdioCdGetErrCode(void);
extern UINT SdioCdGetAUSize(void);
extern void SdioCdGetName(char *buf);
extern UINT SdioCdGetSectorCnt(void);
extern UINT SdioCdGetSize(void);
extern UINT SdioCdE(UINT start_sctor, UINT end_sctor);
extern ENX_OKFAIL SdioCdRead(const BYTE *buff, UINT sector, UINT count);
extern ENX_OKFAIL SdioCdWrite(const BYTE *buff, UINT sector, UINT count);

extern void AdcInit(UINT Speed_Hz);
extern void AdcOn(void);
extern void AdcOff(void);
extern BYTE AdcIsEnable(void);
extern void AdcSetClkdiv(UINT Clkdiv);
extern UINT AdcGetClkdiv(void);
extern void AdcSetClk(UINT Speed_Hz);
extern UINT AdcGetClk(void);
extern void AdcSetLockCnt(UINT lock_cnt);
extern UINT AdcGetLockCnt(void);
extern void AdcSetCapPos(UINT cappos);
extern UINT AdcGetCapPos(void);
extern void AdcSetCtrlpos(UINT Ctrlpos);
extern UINT AdcGetCtrlpos(void);
extern void AdcSetMode(UINT mode);
extern UINT AdcGetMode(void);
extern void AdcSetIirCoef(UINT nCH, UINT iir_coef);
extern UINT AdcGetIirCoef(UINT nCH);
extern void AdcSetOsel(UINT nCH, UINT osel);
extern UINT AdcGetOsel(UINT nCH);
extern void AdcSetEsel(UINT esel);
extern UINT AdcGetEsel(void);
extern void AdcSetHighf(UINT highf);
extern UINT AdcGetHighf(void);
extern void AdcSetOselIirInv(UINT oseliirinv);
extern UINT AdcGetOselIirInv(void);
extern WORD AdcGet(UINT nCH);

extern void Checksum16_isr_async(BYTE *apbDst, UINT anNum);
extern WORD Checksum16_isr(BYTE *apbDst, UINT anNum);
extern void Checksum16_rtos_async(BYTE *apbDst, UINT anNum);
extern WORD Checksum16_rtos(BYTE *apbDst, UINT anNum);
extern WORD ChksumGetDat(void);
extern void ChksumIrqCallback(irq_fn irqfn, void *arg);
extern void ChksumSetIrqEn(ENX_SWITCH sw);
extern ENX_SWITCH ChksumGetIrqEn(void);
extern void ChksumIrqClear(void);
extern UINT ChksumIsIrq(void);
extern void IrqChksum(void);

extern void AesInit(void);
extern void AesSetKey(BYTE *key, UINT size);
extern void AesSetIv(BYTE *iv);
extern void AesCalc_isr_async(BYTE *apbDst, BYTE *apbSrc, UINT len, AESmode mode);
extern void AesCalc_isr(BYTE *apbDst, BYTE *apbSrc, UINT len, AESmode mode);
extern void AesCalc_rtos_async(BYTE *apbDst, BYTE *apbSrc, UINT len, AESmode mode);
extern void AesCalc_rtos(BYTE *apbDst, BYTE *apbSrc, UINT len, AESmode mode);
extern void AesIrqCallback(irq_fn irqfn, void *arg);
extern void AesSetIrqEn(ENX_SWITCH sw);
extern ENX_SWITCH AesGetIrqEn(void);
extern void AesIrqClear(void);
extern UINT AesIsIrq(void);
extern void IrqAes(void);
#if 0
extern void Aes128Enc(BYTE *apbDst, BYTE *apbSrc, UINT len);
extern void Aes128Dec(BYTE *apbDst, BYTE *apbSrc, UINT len);
extern void Aes256Enc(BYTE *apbDst, BYTE *apbSrc, UINT len);
extern void Aes256Dec(BYTE *apbDst, BYTE *apbSrc, UINT len);
#endif

#if EN675_SINGLE
extern void ShaGetDigest(BYTE *data, SHAmode mode);
extern void ShaChopCalc_isr_async(SHAChopitem *item, UINT len);
extern void ShaChopCalc_isr(SHAChopitem *item, UINT len);
extern void ShaChopCalc_rtos_async(SHAChopitem *item, UINT len);
extern void ShaChopCalc_rtos(SHAChopitem *item, UINT len);
extern void ShaChopIrqCallback(irq_fn irqfn, void *arg);
extern void ShaSetChopIrqEn(ENX_SWITCH sw);
extern ENX_SWITCH ShaGetChopIrqEn(void);
extern void ShaChopIrqClear(void);
extern UINT ShaIsChopIrq(void);
extern void IrqShaChop(void);
extern void ShaShotCalc_isr_async(BYTE *apbSrc, UINT len, SHAmode mode);
extern void ShaShotCalc_isr(BYTE *apbSrc, UINT len, SHAmode mode);
extern void ShaShotCalc_rtos_async(BYTE *apbSrc, UINT len, SHAmode mode);
extern void ShaShotCalc_rtos(BYTE *apbSrc, UINT len, SHAmode mode);
extern void ShaShotIrqCallback(irq_fn irqfn, void *arg);
extern void ShaSetShotIrqEn(ENX_SWITCH sw);
extern ENX_SWITCH ShaGetShotIrqEn(void);
extern void ShaShotIrqClear(void);
extern UINT ShaIsShotIrq(void);
extern void IrqShaOneshot(void);
#else
extern void ShaGetDigest(BYTE *data, SHAmode mode);
extern void ShaShotCalc_isr_async(BYTE *apbSrc, UINT len, SHAmode mode);
extern void ShaShotCalc_isr(BYTE *apbSrc, UINT len, SHAmode mode);
extern void ShaShotCalc_rtos_async(BYTE *apbSrc, UINT len, SHAmode mode);
extern void ShaShotCalc_rtos(BYTE *apbSrc, UINT len, SHAmode mode);
extern void ShaShotIrqCallback(irq_fn irqfn, void *arg);
extern void ShaSetShotIrqEn(ENX_SWITCH sw);
extern ENX_SWITCH ShaGetShotIrqEn(void);
extern void ShaShotIrqClear(void);
extern UINT ShaIsShotIrq(void);
extern void IrqSha(void);
#endif

extern void WdtInit(ULONG milsec);
extern void WdtReset(void);
extern void WdtReboot(void);
extern void WdtWaitReboot(ULONG milsec);

extern void AtoBIrqCall(void);
extern void BtoAIrqCall(void);
extern void AtoBIrqCallback(irq_fn irqfn, void *arg);
extern void BtoAIrqCallback(irq_fn irqfn, void *arg);
extern void AtoBSetIrqEn(ENX_SWITCH sw);
extern void BtoASetIrqEn(ENX_SWITCH sw);
extern ENX_SWITCH AtoBGetIrqEn(void);
extern ENX_SWITCH BtoAGetIrqEn(void);
extern void AtoBIrqClear(void);
extern void BtoAIrqClear(void);
extern UINT AtoBIsIrq(void);
extern UINT BtoAIsIrq(void);
extern void IrqAtoB(void);
extern void IrqBtoA(void);

extern void OicInit(void);
extern void OicIrqCallback(irq_fn irqfn, void *arg);
extern void OicSetIrqEn(ENX_SWITCH sw);
extern ENX_SWITCH OicGetIrqEn(void);
extern void OicIrqClear(void);
extern UINT OicIsIrq(void);
extern void IrqOic(void);

extern void IrInit(UINT nAddr);
extern void IrDeInit(void);
extern void IrSetClk(UINT clk);
extern UINT IrGetClk(void);
extern void IrSetEn(ENX_SWITCH sw);
extern UINT IrGetEn(void);
extern void IrSetIrqAddr(UINT nAddr);
extern UINT IrGetIrqAddr(void);
extern void IrSetMargin(UINT nMargin);
extern UINT IrGetMargin(void);
extern void IrSetRepeatMargin(UINT nMargin);
extern UINT IrGetRepeatMargin(void);
extern UINT IrIsRepeat(void);
extern UINT IrGetAddr(void);
extern UINT IrGetDat(void);
extern void IrIrqCallback(irq_fn irqfn, void *arg);
extern void IrSetIrqEn(ENX_SWITCH sw);
extern ENX_SWITCH IrGetIrqEn(void);
extern void IrIrqClear(void);
extern UINT IrIsIrq(void);
extern void IrqIr(void);

#endif
