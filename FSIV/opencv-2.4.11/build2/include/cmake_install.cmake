# Install script for directory: /home/ruben/Documentos/3IngInformatica/FSIV/opencv-2.4.11/include

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Debug")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv" TYPE FILE FILES
    "/home/ruben/Documentos/3IngInformatica/FSIV/opencv-2.4.11/include/opencv/cvwimage.h"
    "/home/ruben/Documentos/3IngInformatica/FSIV/opencv-2.4.11/include/opencv/cv.hpp"
    "/home/ruben/Documentos/3IngInformatica/FSIV/opencv-2.4.11/include/opencv/highgui.h"
    "/home/ruben/Documentos/3IngInformatica/FSIV/opencv-2.4.11/include/opencv/cv.h"
    "/home/ruben/Documentos/3IngInformatica/FSIV/opencv-2.4.11/include/opencv/cvaux.h"
    "/home/ruben/Documentos/3IngInformatica/FSIV/opencv-2.4.11/include/opencv/cxcore.h"
    "/home/ruben/Documentos/3IngInformatica/FSIV/opencv-2.4.11/include/opencv/cxeigen.hpp"
    "/home/ruben/Documentos/3IngInformatica/FSIV/opencv-2.4.11/include/opencv/cvaux.hpp"
    "/home/ruben/Documentos/3IngInformatica/FSIV/opencv-2.4.11/include/opencv/cxmisc.h"
    "/home/ruben/Documentos/3IngInformatica/FSIV/opencv-2.4.11/include/opencv/cxcore.hpp"
    "/home/ruben/Documentos/3IngInformatica/FSIV/opencv-2.4.11/include/opencv/ml.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/opencv2" TYPE FILE FILES "/home/ruben/Documentos/3IngInformatica/FSIV/opencv-2.4.11/include/opencv2/opencv.hpp")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")

