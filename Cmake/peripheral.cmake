﻿SET ( USE_SDIO0 1 ) # 0:unused  1:use
SET ( USE_SDIO1 0 ) # 0:unused  1:use
SET ( SDIO0_SPEED 400000 )
SET ( SDIO1_SPEED 400000 )

SET ( USE_I2S 0 ) # 0:unused  1:GPIO16,17,18,19

SET ( USE_ETH 1 ) # 0:unused  1:GPIO36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52
SET ( MDIO_SPEED 2500000 )

SET ( USE_USB 0 ) # 0:unused  1:GPIO60,61,62,63,64,65,66,67,68,69,70,71

SET ( USE_SPI0 0 ) # 0,1:unused  2:GPIO00,01,02,03  3:GPIO04,05,06,07
SET ( USE_SPI1 0 ) # 0,1:unused  2:GPIO08,09,10,11  3:GPIO12,13,14,15
SET ( USE_SPI2 0 ) # 0,1:unused  2:GPIO16,17,18,19  3:GPIO20,21,22,23
SET ( USE_SPI3 0 ) # 0,1:unused  2:GPIO24,25,26,27  3:GPIO28,29,30,31
SET ( USE_SPI4 0 ) # 0,1:unused  2:GPIO32,33,34,35  3:GPIO36,37,38,39
SET ( USE_SPI5 0 ) # 0,1:unused  2:GPIO40,41,42,43  3:GPIO44,45,46,47
SET ( USE_SPI6 0 ) # 0,1:unused  2:GPIO48,49,50,51  3:GPIO52,53,54,55
SET ( USE_SPI7 0 ) # 0,1:unused  2:GPIO56,57,58,59  3:GPIO60,61,62,63
SET ( USE_SPI8 3 ) # 0,1:unused  2:GPIO64,65,66,67  3:GPIO68,69,70,71
SET ( SPI0_SPEED 1500000 )
SET ( SPI0_BIT 24 )
SET ( SPI0_LSB 1 ) # 0:MSB   1:LSB
SET ( SPI1_SPEED 1000000 )
SET ( SPI1_BIT 8 )
SET ( SPI1_LSB 0 )
SET ( SPI2_SPEED 1000000 )
SET ( SPI2_BIT 8 )
SET ( SPI2_LSB 0 )
SET ( SPI3_SPEED 1000000 )
SET ( SPI3_BIT 8 )
SET ( SPI3_LSB 0 )
SET ( SPI4_SPEED 1000000 )
SET ( SPI4_BIT 8 )
SET ( SPI4_LSB 0 )
SET ( SPI5_SPEED 1000000 )
SET ( SPI5_BIT 8 )
SET ( SPI5_LSB 0 )
SET ( SPI6_SPEED 1000000 )
SET ( SPI6_BIT 8 )
SET ( SPI6_LSB 0 )
SET ( SPI7_SPEED 1000000 )
SET ( SPI7_BIT 8 )
SET ( SPI7_LSB 0 )
SET ( SPI8_SPEED 1000000 )
SET ( SPI8_BIT 8 )
SET ( SPI8_LSB 0 )

SET ( USE_I2C0 3 ) # 0,1:unused  2:GPIO06,07  3:GPIO02,03
SET ( USE_I2C1 0 ) # 0,1:unused  2:GPIO14,15  3:GPIO10,11
SET ( USE_I2C2 2 ) # 0,1:unused  2:GPIO22,23  3:GPIO18,19
SET ( USE_I2C3 0 ) # 0,1:unused  2:GPIO30,31  3:GPIO26,27
SET ( USE_I2C4 0 ) # 0,1:unused  2:GPIO38,39  3:GPIO34,35
SET ( USE_I2C5 0 ) # 0,1:unused  2:GPIO46,47  3:GPIO42,53
SET ( USE_I2C6 0 ) # 0,1:unused  2:GPIO54,55  3:GPIO50,51
SET ( USE_I2C7 3 ) # 0,1:unused  2:GPIO62,63  3:GPIO58,59
SET ( USE_I2C8 3 ) # 0,1:unused  2:GPIO70,71  3:GPIO66,67
SET ( I2C0_SPEED 400000 )
SET ( I2C1_SPEED 400000 )
SET ( I2C2_SPEED 400000 )
SET ( I2C3_SPEED 400000 )
SET ( I2C4_SPEED 400000 )
SET ( I2C5_SPEED 400000 )
SET ( I2C6_SPEED 400000 )
SET ( I2C7_SPEED 400000 )
SET ( I2C8_SPEED 400000 )

SET ( USE_UART0 0 ) # 0,1:unused  2:GPIO04,05  3:GPIO00,01
SET ( USE_UART1 0 ) # 0,1:unused  2:GPIO12,13  3:GPIO08,09
SET ( USE_UART2 0 ) # 0,1:unused  2:GPIO20,21  3:GPIO16,17
SET ( USE_UART3 0 ) # 0,1:unused  2:GPIO28,28  3:GPIO24,25
SET ( USE_UART4 0 ) # 0,1:unused  2:GPIO36,37  3:GPIO32,33
SET ( USE_UART5 0 ) # 0,1:unused  2:GPIO44,45  3:GPIO40,41
SET ( USE_UART6 0 ) # 0,1:unused  2:GPIO52,53  3:GPIO48,49
SET ( USE_UART7 3 ) # 0,1:unused  2:GPIO60,61  3:GPIO56,57
SET ( USE_UART8 3 ) # 0,1:unused  2:GPIO68,69  3:GPIO64,65
SET ( UART0_SPEED 115200)
SET ( UART1_SPEED 115200)
SET ( UART2_SPEED 115200)
SET ( UART3_SPEED 115200)
SET ( UART4_SPEED 115200)
SET ( UART5_SPEED 115200)
SET ( UART6_SPEED 115200)
SET ( UART7_SPEED 115200)
SET ( UART8_SPEED 115200)

SET ( USE_TIMER0 1 ) # 0:unused  1:GPIO00
SET ( USE_TIMER1 1 ) # 0:unused  1:GPIO01
SET ( USE_TIMER2 1 ) # 0:unused  1:GPIO02
SET ( USE_TIMER3 1 ) # 0:unused  1:GPIO03
SET ( USE_TIMER4 1 ) # 0:unused  1:GPIO04
SET ( USE_TIMER5 1 ) # 0:unused  1:GPIO05
SET ( USE_TIMER6 1 ) # 0:unused  1:GPIO06
SET ( USE_TIMER7 1 ) # 0:unused  1:GPIO07
SET ( USE_TIMER8 1 ) # 0:unused  1:GPIO08
SET ( USE_TIMER9 1 ) # 0:unused  1:GPIO09
SET ( USE_TIMER10 1 ) # 0:unused  1:GPIO10
SET ( USE_TIMER11 1 ) # 0:unused  1:GPIO11
SET ( USE_TIMER12 1 ) # 0:unused  1:GPIO12
SET ( USE_TIMER13 1 ) # 0:unused  1:GPIO13
SET ( USE_TIMER14 1 ) # 0:unused  1:GPIO14
SET ( USE_TIMER15 1 ) # 0:unused  1:GPIO15
SET ( USE_TIMER16 1 ) # 0:unused  1:GPIO20
SET ( USE_TIMER17 1 ) # 0:unused  1:GPIO21
SET ( USE_TIMER18 1 ) # 0:unused  1:GPIO22
SET ( USE_TIMER19 1 ) # 0:unused  1:GPIO23
SET ( USE_TIMER20 1 ) # 0:unused  1:GPIO24
SET ( USE_TIMER21 1 ) # 0:unused  1:GPIO25
SET ( USE_TIMER22 1 ) # 0:unused  1:GPIO26
SET ( USE_TIMER23 1 ) # 0:unused  1:GPIO27
SET ( USE_TIMER24 1 ) # 0:unused  1:GPIO28
SET ( USE_TIMER25 1 ) # 0:unused  1:GPIO29
SET ( USE_TIMER26 1 ) # 0:unused  1:GPIO30
SET ( USE_TIMER27 1 ) # 0:unused  1:GPIO31
SET ( USE_TIMER28 1 ) # 0:unused  1:GPIO32
SET ( USE_TIMER29 1 ) # 0:unused  1:GPIO33
SET ( USE_TIMER30 1 ) # 0:unused  1:GPIO34
SET ( USE_TIMER31 1 ) # 0:unused  1:GPIO35
SET ( USE_TIMER32 1 ) # 0:unused  1:GPIO53
SET ( USE_TIMER33 1 ) # 0:unused  1:GPIO54
SET ( USE_TIMER34 1 ) # 0:unused  1:GPIO55
SET ( USE_TIMER35 1 ) # 0:unused  1:GPIO56
SET ( USE_TIMER36 1 ) # 0:unused  1:GPIO57
SET ( USE_TIMER37 1 ) # 0:unused  1:GPIO58
SET ( USE_TIMER38 1 ) # 0:unused  1:GPIO59
