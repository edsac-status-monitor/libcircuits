AM_CFLAGS = -Wall -pedantic -std=c99
AM_LDFLAGS = 
LDADD = 

lib_LTLIBRARIES = libcircuit.la

libcircuit_la_SOURCES = circuit.c circuit.h \
						vector.c vector.h
libcircuit_la_LDFLAGS = -version-info 0:0:0 $(LDADD)

#bin_PROGRAMS = test_program
#test_program_SOURCES = main.c
#test_program_LDADD = $(lib_LIBRARIES) $(LDADD)

