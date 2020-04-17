#include "dev.h"
#include "test_nonos.h"

void main_1(int cpu_id)
{
	SYS_REG0 = 0xf;
	while(SYS_REG0 == 0xf) {} // Wait for CPU0 to be ready.

	enx_externalirq_init_cpu1();

#if model_TgtBd == 2	// CPU 2core
	enx_externalirq_perl(eigiISP, ENX_ON, 0);							// Enable ISP Interrupts
	enx_externalirq_perl(eigiVCODEC, ENX_ON, 0);						// Enable Codec Interrupts

	Init_Visp(); INIT_STR("Init_Visp...");	// ISP initial
	Init_Vcap(); INIT_STR("Init_Vcap...");	// Video path set
	Init_Vout(); INIT_STR("Init_Vout...");	// Digital/Analog Output set
	Init_Virq(); INIT_STR("Init_Virq...");	// Video interrupt enable

	INIT_STR("--------- Main Loop Start ---------");

	while (1)
	{
		Visp();
		Vcap();
		//Venc();
		//Vdec();
	}
#else
	while (1) {
#if TEST_CPU1
		testloop1();
#else
		if (SYS_REG0 == 0xA) {
#ifdef __USE_LED1__
			GpioSetOut(GPIO_LED1, GPIO_OUT_HI);
#endif
			//_printf("%d:%lu\r\n", cpu_id, *mtime);
			WaitXms(100);
			SYS_REG0 = 0xB;
		}
#endif
	}
#endif
}
