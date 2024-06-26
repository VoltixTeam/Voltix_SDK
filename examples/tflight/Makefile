VOLTIX_SDK_ROOT ?= ../..
GNU_INSTALL_ROOT ?=
PRJ_ROOT := .
OUTPUT_DIR := _build

ifndef VOLTIX_SDK_ROOT
  $(error VOLTIX_SDK_ROOT is not set)
endif

SRC_FILES = \
  $(PRJ_ROOT)/src/hello_world_float_model_data.cpp \
  $(PRJ_ROOT)/src/hello_world_int8_model_data.cpp \
  $(PRJ_ROOT)/src/main.cpp

INC_DIRS = \
  $(PRJ_ROOT)/include

LIB_DIRS = $(VOLTIX_SDK_ROOT)/external/tflm-cmsis

LIB_FILES = -ltensorflow-microlite

CFLAGS += -DTF_LITE_STATIC_MEMORY

include $(VOLTIX_SDK_ROOT)/Makefile