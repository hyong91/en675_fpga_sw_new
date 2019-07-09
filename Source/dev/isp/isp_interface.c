#include "dev.h"


//	OnOff			->	0 : Off, 1 : On
//	IsMipi			->	0 : LVDS, 1 : Mipi
//	MipiClkPhase	->	Select Mipi 1/4 Clock Phase 0, 1, 2, 3
void Isp_SDesPowerOn(BOOL OnOff, BOOL IsMipi, BYTE MipiClkPhase)
{
	if(OnOff) {
		SDES_PDw(0x00);
		if(IsMipi)	{	RDES_CK_SELw(1);	MIPI_RXONw(1);	LSYNCM_SELw(MipiClkPhase);	LVDS_RXONw(0);	}
		else		{	RDES_CK_SELw(0);	LVDS_RXONw(1);	MIPI_RXONw(0);	}
		CH_DSELw(0);
		CH_HSSELw(0);
		CH_VSSELw(0);
		LCK_SONw(1);
		LBUF_ONw(1);
	}
	else {
		SDES_PDw(0x1f);
		MIPI_RXONw(0);
		LVDS_RXONw(0);
		CH_DSELw(1);
		CH_HSSELw(1);
		CH_VSSELw(1);
		LCK_SONw(0);
		LBUF_ONw(0);
	}
}

void Isp_SDesDelay(BYTE Lck, BYTE Ldi0, BYTE Ldi1, BYTE Ldi2, BYTE Ldi3)
{
	LCK_DLYw(Lck);	LDIDLY0w(Ldi0);		LDIDLY1w(Ldi1);		LDIDLY2w(Ldi2);		LDIDLY3w(Ldi3);
}

//void Isp_SdesTimingAlign(BYTE Res)
//{
//	UINT i,j;
//	UINT XRes, YRes;
//
//	switch(Res)
//	{
//		case	RES_720_25P	:	{XRes = 3959;	YRes = 749;		}	break;
//		case	RES_720_30P	:   {XRes = 3299;	YRes = 749;		}   break;
//		case	RES_720_50P	:   {XRes = 1979;	YRes = 749;		}   break;
//		case	RES_720_60P	:   {XRes = 1649;	YRes = 749;		}   break;
//		case	RES_1080_25P:   {XRes = 2639;	YRes = 1124;	}   break;
//		case	RES_1080_30P:   {XRes = 2199;	YRes = 1124;	}   break;
//		case	RES_1080_50P:   {XRes = 2639;	YRes = 1124;	}   break;
//		case	RES_1080_60P:   {XRes = 2199;	YRes = 1124;	}   break;
////		case	RES_4M_25P	:   {XRes = 		}
////		case	RES_4M_30P	:   {XRes = 		}
////		case	RES_4K_15P	:   {XRes = 		}
//		default				:	{XRes = 2639;	YRes = 1124;	}   break;
//
//	}
//
//	for(i=0;i<8;i++)
//	{
//		LCK_DLYw(i);
//		for(
//	}
//
//}

void Isp_SDesPosition(UINT LvdsHRpos, UINT LvdsVRpos, UINT LvdsHw, UINT LvdsVw)
{
	RDES_RPOSw(LvdsHRpos);		// Lvds/Mipi internal buffer���� image�� read�ϴ� horizontal position�� �����Ѵ�.
	RDES_RVPOSw(LvdsVRpos);		// Lvds/Mipi internal buffer���� image�� read�ϴ� vertical position�� �����Ѵ�.
	RDES_VWw(LvdsVw);			// Lvds/Mipi internal buffer���� image�� read�ϴ� vertical width�� �����Ѵ�. �� ���� margin�� �����Ͽ� ���� vertical active pixel���� ũ�� �����Ѵ�.
	MERGE_HWw(LvdsHw>>2);		// Lvds/Mipi internal buffer���� image�� read�ϴ� horizontal width�� �����Ѵ�. �� ���� margin�� �����Ͽ� ���� horizontal active pixel���� ũ�� �����Ѵ�. '>>2'�����Ͽ� ����
}

//	LvdsBit		->	LVDS_10BIT		0
//             	 	LVDS_12BIT		1
//              	LVDS_16BIT		2
//
//	LvdsLane	->	LVDS_2LANE		0
//					LVDS_4LANE      1
//
//	IsLsbFirst	->	0 : Msb First, 1 : Lsb First
//
//	PNSel		->	0 : Negative Start, 1 : Positive Start
void Isp_Lvds_Config(BYTE LvdsBit, BYTE LvdsLane, BOOL IsLsbFirst, BOOL PNSel)
{
	RDES_BITw(LvdsBit);
	RDES_CH_MODw(LvdsLane);
	LVDS_LSBw(IsLsbFirst);
	RDES_PNSELw(PNSel);
}

//	MipiBit		->	MIPI_10BIT		0
//             	 	MIPI_12BIT		1
//	MipiLane	->	MIPI_1LANE		0
//					MIPI_2LANE      1
//					MIPI_4LANE      2
void Isp_Mipi_Config(BYTE MipiBit, BYTE MipiLane, BOOL IsLsbFirst, BOOL PNSel, BOOL UseEcc, BOOL UseWcl, BOOL UseWcf, BOOL UseWcfe, BYTE MipiImgPhase)
{
	if(MipiBit==1)		{	OMOD_BITw(0);	}			//	12 Bit
	else				{	OMOD_BITw(1);	}			//	10 Bit

	RDES_BITw(MipiBit);
	RDES_CH_MODw(MipiLane);
	LVDS_LSBw(IsLsbFirst);
	RDES_PNSELw(PNSel);
	MIPI_ECC_ONw(UseEcc);
	MIPI_WCCHK_LONw(UseWcl);
	MIPI_WCCHK_FONw(UseWcf);
	MIPI_WCCHK_FEONw(UseWcfe);
	MIPI_IMG_MCNTw(MipiImgPhase);
//	LSYNCM_SELw(MipiClkPhase);
}


//	ClkSel	->	Select Sensor Operation Clock
//	SENS_148M	0 : 148.5 MHz
//	SENS_74M	1 : 74.25 MHz
//	SENS_37M	2 : 37.125 MHz
//	SENS_18M	3 : 18.5625 MHz
//	SENS_27M	4 : 27 MHz	(CLK Input Clock)
//	SENS_13M	5 : 13.5 MHz (CLK Input Clock / 2)
void Isp_SensorPowerOn(BOOL OnOff, BYTE ClkSel)
{
	PCKO_CK_PDw(0);
	PCKO_PDw(0);
	PCKO_SELw(ClkSel);
	PCKO_CK_PDw(1);
	PCKO_PDw(1);
	PCKO_OENw(0);

	if(OnOff)		PCKO_OENw(0);
	else			PCKO_OENw(1);
}

//	BOOL OnOff			->	0 : Parallel Interface Off, 1 : Parallel Interface On,
//	BOOL IsSlave		->	ISP_MASTER (0)
//							ISP_SLAVE (1)
//	BOOL IsUseExtClk	->	PARA_EXTER_CLK (0)
//							PARA_INTER_CLK (1)
//	BOOL IsClkDdr		->	PARA_CLK_SDR (0)
//							PARA_CLK_DDR (1)
//	BOOL HSyncPol		->	SYNC_FALL (0)
//							SYNC_RISE (1)
//	BOOL SyncMode		->	SAME_EDGE (0)
//							DIFF_EDGE (1)
//	BOOL IsUseAsync		->	NO_USE_AUTOSYNC (0)
//						->	USE_AUTOSYNC 	(1)
void Isp_Parallel_Config(BOOL OnOff, BOOL IsSlave, BOOL IsUseExtClk, BOOL IsClkDdr, BYTE ClkDly, BOOL HSyncPol, BOOL VSyncPol, BOOL SyncMode, BOOL IsUseAsync)
{

	PCLK_PDw(OnOff);

	if(OnOff)	{	CH_DSELw(1);	CH_HSSELw(1);	CH_VSSELw(1);								}
	else		{	CH_DSELw(0);	CH_HSSELw(0);	CH_VSSELw(0);	IBT_PCK_PDw(0);	BT_PCK_PDw(0);	IDDR_ONw(0);	ISDR_OPw(0);	return;	}

	if(IsSlave)		SLVw(3);
	else			SLVw(0);

	IBT_PCK_SET(0);

	if(IsUseExtClk==PARA_EXTER_CLK)	{	BT_PCK_SET(3);	}			//	External Sensor Pixel Clock
	else							{	BT_PCK_SET(2);	}			//	Internal 74.25 MHz

	if(IsClkDdr==PARA_CLK_SDR)		{	IDDR_ONw(1);	ISDR_OPw(1);	}
	else							{	IDDR_ONw(1);	ISDR_OPw(0);	}

	POL_HSIw(HSyncPol);
	POL_VSIw(VSyncPol);

	VSYN_NAONw(SyncMode);
	ASYNC_ONw(IsUseAsync);

	PCLK_DLYw(ClkDly);
}

//	Clk	->	Select Isp Pre Processor Clock
//	ISP_CLK_PLL			0   //	ISP PLL Output
//	ISP_CLK_148M		1   //	ISP PLL / 2 (148.5 MHz)
//	ISP_CLK_74M			2   //	ISP PLL / 2 (74.5 MHz)
//	ISP_CLK_PCLK		3   //	SS_CKI Input
//	ISP_CLK_PCLK_DIV2	4   //	SS_CKI Input 1/2 Divided Clock
//	ISP_CLK_PLL_DIV0	5	//	ISP PLL Output Adjust CLock 0
void Isp_PreClk_Config(BYTE Clk)
{
	BT_PCK_PDw(0);	FPCK_PDw(0);

	if(Clk==5)		BT_PCK_SELw(7);
	else			BT_PCK_SELw(Clk);

	FPCK_SELw(Clk);

	BT_PCK_PDw(1);	FPCK_PDw(1);
}


//	IsSlave+	->	0 : Master Mode, 1 : Slave Mode
//	Htw			->	Horizontal Total Counter : Real Number
//	Vtw			->	Vertical Total Counter : Real Number
//	HsyncOfs*	->	Horizontal Sync Offset, Hsp ���ڷ� Image ��ġ�� ���� ������ Sync�� ��ġ�� �̵��Ͽ� image ��ġ�� ���ߴµ� ����Ѵ�.
//	VsyncOfs*	->	Vertical Sync Offset, Vsp ���ڷ� Image ��ġ�� ���� ������ Sync�� ��ġ�� �̵��Ͽ� image ��ġ�� ���ߴµ� ����Ѵ�.
//	Hsp*		->	Post module horizontal image start position
//	Vsp*		->	Post module vertical image start position
//	Hw			->	Horizontal Active Width
//	Vw			->	Vertical Active Width
//	IsASync+	->	omni sensor�� ���� Active �̿��� �������� sync�� ������ �ʴ� sensor���� 1�� ����
//	IsNSync+	->	�Է� sync�� H/V ������ ��ġ���� �ʴ� ��Ȳ���� 1�� ����
void Isp_PreSync_Config(BOOL IsSlave, UINT Htw, UINT Vtw, UINT HsyncOfs, UINT VsyncOfs, UINT Hsp, UINT Vsp, UINT Hw, UINT Vw, BOOL IsASync, BOOL IsNSync)
{

	PRS_HZw(1);

	HSPIw(Hsp);		VSPIw(Vsp);		HWIw(Hw);		VWIw(Vw);

	if(IsSlave)		{												SLVw(3);	}
	else			{		HTWIw(Htw-2);		VTWIw(Vtw-1);		SLVw(0);	}


	VLOCKI_POSw(VsyncOfs);
	HLOCKI_POSw(HsyncOfs);

	ASYNC_ONw(IsASync);
	VSYN_NAONw(IsNSync);
	PRS_HZw(0);
}

void Isp_AutoSync_Config()
{


}

//	OSyncMode	->	0 : External Sync(Slave), 1 : Standalone Sync(Master)
//	ExSyncSel	->	Select External Sync,  0 : Pre Module Sync,  1: External Input Sync (EN675 Pin VSO, HSO Input)
//	Htw			->	Horizontal Total Counter : Real Number
//	Vtw			->	Vertical Total Counter : Real Number
//	HsyncOfs	->	Horizontal Sync Offset, Hsp ���ڷ� image ��ġ�� ���� ������ sync�� ��ġ�� �̵��Ͽ� image ��ġ�� ���ߴµ� ���
//	VsyncOfs	->	Vertical Sync Offset, Vsp ���ڷ� image ��ġ�� ���� ������ sync�� ��ġ�� �̵��Ͽ� image ��ġ�� ���ߴµ� ���
//	Hsp			->	Post module horizontal image start position
//	Vsp			->	Post module vertical image start position
//	Hw			->	Horizontal Active Width
//	Vw			->	Vertical Active Width
//	OCSel*		->	Post module color phase selection
void Isp_PostSync_Config(BOOL OSyncMode, BOOL ExSyncSel, UINT Htw, UINT Vtw, UINT HsyncOfs, UINT VsyncOfs, UINT Hsp, UINT Vsp, UINT Hw, UINT Vw, BYTE OCSel)
{
	POS_HZw(1);

	HSPOw(Hsp);		VSPOw(Vsp);		HWOw(Hw);		VWOw(Vw);

	if(OSyncMode)	{	HTWOw(Htw-2);		VTWOw(Vtw-1);		OSYNC_MODw(1);	}
	else			{											OSYNC_MODw(0);	}

	VLOCKI2_POSw(VsyncOfs);
	HLOCKI2_POSw(HsyncOfs);
	EXVSYNC_SELw(ExSyncSel);
	EXHSYNC_SELw(ExSyncSel);

	OCSELw(OCSel);

	POS_HZw(0);
}

//	ISP_CLK_PLL			0   //	ISP PLL Output
//	ISP_CLK_148M		1   //	ISP PLL / 2 (148.5 MHz)
//	ISP_CLK_74M			2   //	ISP PLL / 2 (74.5 MHz)
//	ISP_CLK_PCLK		3   //	SS_CKI Input
//	ISP_CLK_PCLK_DIV2	4   //	SS_CKI Input 1/2 Divided Clock
//	ISP_CLK_PLL_DIV0	5	//	ISP PLL Output Adjust CLock 0
void Isp_PostClk_Config(BYTE Clk)
{
	PSCK_PDw(0);	PPCK_PDw(0);	PR_CK0_PDw(0);	FN_CK0_PDw(0);

	PSCK_SELw(Clk);
	PPCK_SELw(Clk);
	FN_CK0_SELw(Clk);
	PR_CK0_SELw(Clk);

	PSCK_PDw(1);	PPCK_PDw(1);	PR_CK0_PDw(1);	FN_CK0_PDw(1);
}


void Isp_Gamma_Config(BOOL Y_OnOff, BOOL C_OnOff)
{

	//	Table Setting

	//	On
	YGMA_ONw(Y_OnOff);
	CGMA_ONw(C_OnOff);
}

void Isp_Edge_Config(BOOL OnOff)
{

//	APT_TH3w(0x40);
//	APT_TH2w(0x0c);
//	APT_TH1w(0x08);
//
//	APT_GAIN2_NEGw(0x08);
//	APT_GAIN1_NEGw(0x08);
//	APT_GAIN2_POSw(0x08);
//	APT_GAIN1_POSw(0x08);
//	APT_SLIC3w(0x10);
//	APT_CLIP3w(0x40);
//	APT_GAIN3w(0x80);
//	APT_LPFKw(0xf0);
//	APT_LPFGAw(0x80);
//	APT_LPFTHw(0x08);

	APT_ONw(OnOff);
	APT_GAIN_ONw(OnOff);
}

//	OnOff	->	FN_ON, FN_OFF
//	DnrFk	->	3D dnr ���� �� feedback�Ǵ� image�� ������ �����Ѵ�.
//	DnrTh	->	���� �̹����� �� �̹����� difference�� �� threshold ������ ���� �������� 3d dnr�� �����ϰ� �ȴ�.
//	DnrGain	->	Gain���� Dnrth�� ���� 3D dnr ���ۿ� �� ū ������ �ش�. ���� 0x20���� ����Ѵ�.
void Isp_Dnr3d_Config(BOOL OnOff, BYTE DnrFk, BYTE DnrTh, BYTE DnrGain)
{

	DNR3D_FKw(DnrFk);
	DNR3D_THw(DnrTh);
	DNR3D_GAw(DnrGain);

	if(OnOff)	{	DNR3D_RCH_ENw(1);
					if(FPCK_SELr==4)		{	YCR_CK4_SET(7);         }
					else if(FPCK_SELr==5)	{	YCR_CK4_SET(11);        }
					else					{	YCR_CK4_SET(FPCK_SELr);	}
					DNR3D_ONw(1);
				}
	else		{	DNR3D_RCH_ENw(0);	DNR3D_ONw(0);	YCR_CK4_PDw(0);	}

}

//	OnOff				->	FN_ON, FN_OFF
//	GsumCnt, RBSumCnt	->	DF_SUM_4 : 4 pixel
//							DF_SUM_6 : 6 pixel
//	GWgt, RBWgt			->	DF_WGT_CASEA : Based pixel count method.
//	                        DF_WGT_CASEB : Based weight method				:	GWgt  -> Use this method normally. RBWgt -> Use this method normally.
//	                        DF_WGT_CASEC : Based multiplex weight method
//	DfSlope				->	DF_SLOPE_NOR : Use this value
//	GThres				->	DF_RBTHRES : Use this value normally
//	RBThres				->	DF_GTHRES : Use this value normally
void Isp_Defect_Config(BOOL OnOff, BOOL GsumCnt, BOOL RBSumCnt, BYTE GWgt, BYTE RBWgt, BYTE DfSlope, UINT GThres, UINT RBThres, UINT DfMax, UINT DfMin, BYTE DfCsel)
{

	DF_GSUM_SELw(GsumCnt);
	DF_RBSUM_SELw(RBSumCnt);
	DF_GWGT_SELw(GWgt);
	DF_RBWGT_SELw(RBWgt);
	DF_SLOPEw(DfSlope);
	DF_SUM_GTHw(GThres);
	DF_SUM_RBTHw(RBThres);
	DF_MINw(DfMin);
	DF_MAXw(DfMax);
	DFS_ICSELw(DfCsel);
	DF_OFSw(0);

	DF_COR_ONw(OnOff);
}

//	OnOff		->	FN_ON, FN_OFF
//	Dnr2dMode	->	DNR2D_DTH_MOD (0) : Dnr2dDth �� ������ ������ �ֺ� difference�� ���� pixel�� ���Ͽ� reference�� ����Ͽ� 2d�� �����Ѵ�.
//					DNR2D_SUM_MOD (1) : Dnr2dCnt �� ������ pixel ���� ��ŭ reference�� ����Ͽ� 2d dnr�� �����Ѵ�.
//	Dnr2dCnt	->	Dnr reference pixel count
//					DNR2D_CNT8 : Default 8 pixel
//	Dnr2dDth	->	'center pixel - near pixel' difference threshold
//	Dnr2dGain	->	2d dnr gain
void Isp_Dnr2d_Config(BOOL OnOff, BOOL Dnr2dMode, BYTE Dnr2dCnt, BYTE Dnr2dDth, BYTE Dnr2dGain)
{
	DNR2D_CNTw(Dnr2dCnt);
	DNR2D_DTHw(Dnr2dDth);
	DNR2D_GAINw(Dnr2dGain);
	DNR2D_MODw(Dnr2dMode);

	DNR2D_ONw(OnOff);
}

//	SD_MODw : 0 -> FRC 2 Page (Adr2, Adr3, Adr4 Don't care)
//			  1 -> FRC 3 Page (Adr3, Adr4 Don't care)
//			  4 -> FRC 5 Page
void Isp_Frc_Adr_Config(UINT Adr0, UINT Adr1, UINT Adr2, UINT Adr3, UINT Adr4)
{
	FRC_ADR0w(DDR_BASE_ISP+Adr0);
	FRC_ADR1w(DDR_BASE_ISP+Adr1);
	FRC_ADR2w(DDR_BASE_ISP+Adr2);
	FRC_ADR3w(DDR_BASE_ISP+Adr3);
	FRC_ADR4w(DDR_BASE_ISP+Adr4);
}



