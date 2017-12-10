# INCLUDES veriable stores header path for compiler required by module
set (INCLUDES ${CMAKE_CURRENT_SOURCE_DIR})

#use list command to append paths to INCLUDES variable
#list (APPEND INCLUDES ${MB_SDK_DI}/Utils/ErrorClass/ ${MB_SDK_DI}/Utils/AVParam/ ${MB_SDK_HISILICON}/pub/include ${MB_SDK_HISILICON}sample/common )
include_directories(${INCLUDES})

#library name and sources
add_library(dvbsections STATIC dvb_section.cpp dvb_section.hpp )
