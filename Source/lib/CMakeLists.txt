﻿# About this project
# ------------------------------------------------------------------------------
PROJECT(EN675_LIB)

# 출력 디렉토리
SET ( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${CMAKE_BUILD_TYPE} )
SET ( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${CMAKE_BUILD_TYPE}/lib )
SET ( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/${CMAKE_BUILD_TYPE}/lib )

# Add subdirectory
# ------------------------------------------------------------------------------
ADD_SUBDIRECTORY(EnxISP)

IF (USE_WF_SD8782)
	ADD_SUBDIRECTORY(wifi_sd8782)
ENDIF (USE_WF_SD8782)

IF (USE_NETWORK)
	ADD_SUBDIRECTORY(lwIP)
ENDIF (USE_NETWORK)

IF (USE_FIESYSTEM)
	ADD_SUBDIRECTORY(FatFs)
ENDIF (USE_FIESYSTEM)

#IF (USE_FREERTOS)
	ADD_SUBDIRECTORY(FreeRTOS)
#ENDIF (USE_FREERTOS)
