#---------------------------------------------------------------------------------------------------------------------
# TARGET is the name of the output.
# BUILD is the directory where object files & intermediate files will be placed.
# LIBBUTANO is the main directory of butano library (https://github.com/GValiente/butano).
# PYTHON is the path to the python interpreter.
# SOURCES is a list of directories containing source code.
# INCLUDES is a list of directories containing extra header files.
# DATA is a list of directories containing binary data.
# GRAPHICS is a list of directories containing files to be processed by grit.
# AUDIO is a list of directories containing files to be processed by mmutil.
# DMGAUDIO is a list of directories containing files to be processed by mod2gbt and s3m2gbt.
# ROMTITLE is a uppercase ASCII, max 12 characters text string containing the output ROM title.
# ROMCODE is a uppercase ASCII, max 4 characters text string containing the output ROM code.
# USERFLAGS is a list of additional compiler flags:
#     Pass -flto to enable link-time optimization.
#     Pass -O0 or -Og to try to make debugging work.
# USERASFLAGS is a list of additional assembler flags.
# USERLDFLAGS is a list of additional linker flags:
#     Pass -flto=<number_of_cpu_cores> to enable parallel link-time optimization.
# USERLIBDIRS is a list of additional directories containing libraries.
#     Each libraries directory must contains include and lib subdirectories.
# USERLIBS is a list of additional libraries to link with the project.
# DEFAULTLIBS links standard system libraries when it is not empty.
# USERBUILD is a list of additional directories to remove when cleaning the project.
# EXTTOOL is an optional command executed before processing audio, graphics and code files.
#
# All directories are specified relative to the project directory where the makefile is found.
#---------------------------------------------------------------------------------------------------------------------
TARGET      :=  $(notdir $(CURDIR))
BUILD       :=  build
LIBBUTANO   :=  ../../opt/butano/butano
PYTHON      :=  python
SOURCES     :=  src $(wildcard src/*)
INCLUDES    :=  include $(wildcard include/*)
DATA        :=
GRAPHICS    :=  $(wildcard graphics/*)
AUDIO       :=  $(wildcard audio/*)
DMGAUDIO    :=  $(wildcard dmg_audio/*)
ROMTITLE    :=  MJAM TMPL
ROMCODE     :=  TMPL
USERFLAGS   :=  -DBN_CFG_AUDIO_MIXING_RATE=BN_AUDIO_MIXING_RATE_21_KHZ -DBN_CFG_AUDIO_MAX_MUSIC_CHANNELS=20
USERASFLAGS :=  
USERLDFLAGS	:=  
USERLIBDIRS :=  
USERLIBS    :=  
DEFAULTLIBS :=  
USERBUILD   :=  
EXTTOOL     :=  

#---------------------------------------------------------------------------------------------------------------------
# Export absolute butano path:
#---------------------------------------------------------------------------------------------------------------------
ifndef LIBBUTANOABS
	export LIBBUTANOABS	:=	$(realpath $(LIBBUTANO))
endif

# Allowing for skipping of intro
# TODO: Allow for testing of a specific game
BUILD ?= release
ifeq ($(BUILD),debug)
  USERFLAGS += -DMJ_SKIP_INITIAL_TITLE=1
  USERFLAGS += -DMAX_GAME_SECS=1000
endif

#---------------------------------------------------------------------------------------------------------------------
# Include main makefile:
#---------------------------------------------------------------------------------------------------------------------
include $(LIBBUTANOABS)/butano.mak

#---------------------------------------------------------------------------------------------------------------------
# Include hint to website of where the ROM is located:
#---------------------------------------------------------------------------------------------------------------------
rom.json:
	@echo '{ "rom": "$(TARGET).gba" }' > $@

all: rom.json