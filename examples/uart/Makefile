VOLTIX_SDK_ROOT ?= ../..
GNU_INSTALL_ROOT ?=

PRJ_ROOT := .
OUTPUT_DIR := _build

ifndef VOLTIX_SDK_ROOT
  $(error VOLTIX_SDK_ROOT is not set)
endif

SRC_FILES = \
  $(PRJ_ROOT)/src/main.c

INC_DIRS = \
  $(PRJ_ROOT)/include

include $(VOLTIX_SDK_ROOT)/Makefile