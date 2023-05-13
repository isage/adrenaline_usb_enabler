cmake_minimum_required(VERSION 3.2)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

project(adrenaline_usb_enabler)
include("${VITASDK}/share/vita.cmake" REQUIRED)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wl,-q -Wall -O3 -nostartfiles -nostdlib -fno-lto")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -fno-exceptions")

add_executable(adrenaline_usb_enabler
  main.c
)

target_link_libraries(adrenaline_usb_enabler
  taihen_stub
#  c
#  m
  SceLibKernel_stub
  SceKernelModulemgr_stub
)

vita_create_self(adrenaline_usb_enabler.suprx adrenaline_usb_enabler CONFIG exports.yml UNSAFE)
