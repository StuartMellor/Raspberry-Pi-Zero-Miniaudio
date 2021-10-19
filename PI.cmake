# ############################################################################
# # toolchain-raspberry.cmake
# # Copyright (C) 2014  Belledonne Communications, Grenoble France
# #
# ############################################################################
# #
# # This program is free software; you can redistribute it and/or
# # modify it under the terms of the GNU General Public License
# # as published by the Free Software Foundation; either version 2
# # of the License, or (at your option) any later version.
# #
# # This program is distributed in the hope that it will be useful,
# # but WITHOUT ANY WARRANTY; without even the implied warranty of
# # MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# # GNU General Public License for more details.
# #
# # You should have received a copy of the GNU General Public License
# # along with this program; if not, write to the Free Software
# # Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
# #
# ############################################################################

# # Based on:
# # https://gitlab.linphone.org/BC/public/linphone-cmake-builder/blob/master/toolchains/toolchain-raspberry.cmake
# # Updated version:
# # https://github.com/Pro/raspi-toolchain/blob/master/Toolchain-rpi.cmake

# if("$ENV{RASPBERRY_VERSION}" STREQUAL "")
# 	set(RASPBERRY_VERSION 1)
# else()
# 	if($ENV{RASPBERRY_VERSION} VERSION_GREATER 3)
# 		set(RASPBERRY_VERSION 3)
# 	else()
# 		set(RASPBERRY_VERSION $ENV{RASPBERRY_VERSION})
# 	endif()
# endif()

# # RASPBIAN_ROOTFS should point to the local directory which contains all the libraries and includes from the target raspi.
# # Get them with:
# # rsync -vR --progress -rl --delete-after --safe-links pi@192.168.1.PI:/{lib,usr,opt/vc/lib} $HOME/rpi/rootfs
# # Then 
# # set(RASPBIAN_ROOTFS $ENV{$HOME}/cmake-test/rootfs)

# if("$ENV{RASPBIAN_ROOTFS}" STREQUAL "")
# 	message(FATAL_ERROR "Define the RASPBIAN_ROOTFS environment variable to point to the raspbian rootfs.")
# else()
# 	set(SYSROOT_PATH "$ENV{RASPBIAN_ROOTFS}")
# endif()
# set(TOOLCHAIN_HOST "arm-linux-gnueabihf")


# message(STATUS "Using sysroot path: ${SYSROOT_PATH}")
# message(Toolchain host: ${TOOLCHAIN_HOST})

# set(TOOLCHAIN_CC "$ENV{HOME}/cmake-test/tools/cross-pi-gcc-8.3.0-0/bin/${TOOLCHAIN_HOST}-gcc")
# set(TOOLCHAIN_CXX "$ENV{HOME}/cmake-test/tools/cross-pi-gcc-8.3.0-0/bin/${TOOLCHAIN_HOST}-g++")
# set(TOOLCHAIN_LD "$ENV{HOME}/cmake-test/tools/cross-pi-gcc-8.3.0-0/bin/${TOOLCHAIN_HOST}-ld")
# set(TOOLCHAIN_AR "$ENV{HOME}/cmake-test/tools/cross-pi-gcc-8.3.0-0/bin/${TOOLCHAIN_HOST}-ar")
# set(TOOLCHAIN_RANLIB "$ENV{HOME}/cmake-test/tools/cross-pi-gcc-8.3.0-0/bin/${TOOLCHAIN_HOST}-ranlib")
# set(TOOLCHAIN_STRIP "$ENV{HOME}/cmake-test/tools/cross-pi-gcc-8.3.0-0/bin/${TOOLCHAIN_HOST}-strip")
# set(TOOLCHAIN_NM "$ENV{HOME}/cmake-test/tools/cross-pi-gcc-8.3.0-0/bin/${TOOLCHAIN_HOST}-nm")

# set(CMAKE_CROSSCOMPILING TRUE)
# set(CMAKE_SYSROOT "${SYSROOT_PATH}")

# # Define name of the target system
# set(CMAKE_SYSTEM_NAME "Linux")
# if(RASPBERRY_VERSION VERSION_GREATER 1)
# 	set(CMAKE_SYSTEM_PROCESSOR "armv7")
# else()
# 	set(CMAKE_SYSTEM_PROCESSOR "arm")
# endif()

# # Define the compiler
# set(CMAKE_C_COMPILER ${TOOLCHAIN_CC})
# set(CMAKE_CXX_COMPILER ${TOOLCHAIN_CXX})

# # List of library dirs where LD has to look. Pass them directly through gcc. LD_LIBRARY_PATH is not evaluated by arm-*-ld
# set(LIB_DIRS 
# 	"/opt/cross-pi-gcc/arm-linux-gnueabihf/lib"
# 	"/opt/cross-pi-gcc/lib"
# 	"$ENV{HOME}/cmake-test/rootfs/opt/vc/lib"
# 	"$ENV{HOME}/cmake-test/rootfs/lib/${TOOLCHAIN_HOST}"
# 	"$ENV{HOME}/cmake-test/rootfs/usr/local/lib"
# 	"$ENV{HOME}/cmake-test/rootfs/usr/lib/${TOOLCHAIN_HOST}"
# 	"$ENV{HOME}/cmake-test/rootfs/usr/lib"
# 	"$ENV{HOME}/cmake-test/rootfs/usr/lib/${TOOLCHAIN_HOST}/blas"
# 	"$ENV{HOME}/cmake-test/rootfs/usr/lib/${TOOLCHAIN_HOST}/lapack"
# )
# # You can additionally check the linker paths if you add the flags ' -Xlinker --verbose'
# set(COMMON_FLAGS "-I${SYSROOT_PATH}/usr/include ")
# FOREACH(LIB ${LIB_DIRS})
# 	set(COMMON_FLAGS "${COMMON_FLAGS} -L${LIB} -Wl,-rpath-link,${LIB}")
# ENDFOREACH()

# set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};${SYSROOT_PATH}/usr/lib/${TOOLCHAIN_HOST}")

# if(RASPBERRY_VERSION VERSION_GREATER 2)
# 	set(CMAKE_C_FLAGS "-mcpu=cortex-a53 -mfpu=neon-vfpv4 -mfloat-abi=hard ${COMMON_FLAGS}" CACHE STRING "Flags for Raspberry PI 3")
# 	set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS}" CACHE STRING "Flags for Raspberry PI 3")
# elseif(RASPBERRY_VERSION VERSION_GREATER 1)
# 	set(CMAKE_C_FLAGS "-mcpu=cortex-a7 -mfpu=neon-vfpv4 -mfloat-abi=hard ${COMMON_FLAGS}" CACHE STRING "Flags for Raspberry PI 2")
# 	set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS}" CACHE STRING "Flags for Raspberry PI 2")
# else()
# 	set(CMAKE_C_FLAGS "-mcpu=arm1176jzf-s -mfpu=vfp -mfloat-abi=hard ${COMMON_FLAGS}" CACHE STRING "Flags for Raspberry PI 1 B+ Zero")
# 	set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS}" CACHE STRING "Flags for Raspberry PI 1 B+ Zero")
# endif()

# set(CMAKE_FIND_ROOT_PATH "${CMAKE_INSTALL_PREFIX};${CMAKE_PREFIX_PATH};${CMAKE_SYSROOT}")


# # search for programs in the build host directories
# set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# # for libraries and headers in the target directories
# set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
# set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
# set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)





set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(tools $ENV{HOME}/cmake-test/tools/cross-pi-gcc-8.3.0-0) # warning change toolchain path here.
set(rootfs_dir $ENV{HOME}/cmake-test/rootfs)

set(CMAKE_FIND_ROOT_PATH ${rootfs_dir})
set(CMAKE_SYSROOT ${rootfs_dir})

set(CMAKE_LIBRARY_ARCHITECTURE arm-linux-gnueabihf)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fPIC -Wl,-rpath-link,${CMAKE_SYSROOT}/usr/lib/${CMAKE_LIBRARY_ARCHITECTURE} -L${CMAKE_SYSROOT}/usr/lib/${CMAKE_LIBRARY_ARCHITECTURE}")
set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wl,-rpath-link,${CMAKE_SYSROOT}/usr/lib/${CMAKE_LIBRARY_ARCHITECTURE} -L${CMAKE_SYSROOT}/usr/lib/${CMAKE_LIBRARY_ARCHITECTURE}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wl,-rpath-link,${CMAKE_SYSROOT}/usr/lib/${CMAKE_LIBRARY_ARCHITECTURE} -L${CMAKE_SYSROOT}/usr/lib/${CMAKE_LIBRARY_ARCHITECTURE}")

## Compiler Binary 
SET(BIN_PREFIX ${tools}/bin/arm-linux-gnueabihf)

SET (CMAKE_C_COMPILER ${BIN_PREFIX}-gcc)
SET (CMAKE_CXX_COMPILER ${BIN_PREFIX}-g++ )
SET (CMAKE_LINKER ${BIN_PREFIX}-ld 
            CACHE STRING "Set the cross-compiler tool LD" FORCE)
SET (CMAKE_AR ${BIN_PREFIX}-ar 
            CACHE STRING "Set the cross-compiler tool AR" FORCE)
SET (CMAKE_NM {BIN_PREFIX}-nm 
            CACHE STRING "Set the cross-compiler tool NM" FORCE)
SET (CMAKE_OBJCOPY ${BIN_PREFIX}-objcopy 
            CACHE STRING "Set the cross-compiler tool OBJCOPY" FORCE)
SET (CMAKE_OBJDUMP ${BIN_PREFIX}-objdump 
            CACHE STRING "Set the cross-compiler tool OBJDUMP" FORCE)
SET (CMAKE_RANLIB ${BIN_PREFIX}-ranlib 
            CACHE STRING "Set the cross-compiler tool RANLIB" FORCE)
SET (CMAKE_STRIP {BIN_PREFIX}-strip 
            CACHE STRING "Set the cross-compiler tool RANLIB" FORCE)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)