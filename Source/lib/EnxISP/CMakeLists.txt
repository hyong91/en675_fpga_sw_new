﻿# 최소한의 Cmake 버전을 설정
CMAKE_MINIMUM_REQUIRED ( VERSION 3.13.2 )

# 프로젝트 이름 설정
PROJECT ( EN675_LIB_EnxISP )

# 소스 코드
SET ( ENXISP_HDRS
	isp_lib_main.h
)

SET ( ENXISP_SRCS
	EN675_SENS_IMX291.c
	EN675_SENS_IMX323.c
	EN675_SENS_IMX225.c
	EN675_SENS_IMX335.c
	EN675_SENS_IMX274.c
	EN675_SENS_IMX415.c
	EN675_SENS_OV2718.c
	EN675_SENS_OV4689.c
	EN675_SENS_OS08A10.c
	isp_lib_main.c
	isp_lib_ae_adv.c
	isp_lib_awb.c
	isp_lib_defog.c
	isp_lib_imd.c
)

# 라이브러리 생성
ADD_LIBRARY ( enxisp STATIC ${ENXISP_SRCS} ${ENXISP_HDRS} )
