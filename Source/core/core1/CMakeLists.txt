﻿# 최소한의 Cmake 버전을 설정
CMAKE_MINIMUM_REQUIRED ( VERSION 3.13.2 )

# 프로젝트 이름 설정
PROJECT ( EN675_LIB_CORE1 )

# 소스 코드
SET ( CORE1_HDRS
)

SET ( CORE1_SRCS
	main1.c
)

# 라이브러리 생성
ADD_LIBRARY ( core1 STATIC ${CORE1_SRCS} ${CORE1_HDRS} )
