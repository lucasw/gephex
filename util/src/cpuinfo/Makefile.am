EXTRA_DIST = cpuinfo.vcproj cpuinfo.vcproj cpuinfo.dsp cpuinfo.mak cpuinfo.dep

noinst_LIBRARIES = libcpuinfo.a

libcpuinfo_a_SOURCES = cpuinfo.c

noinst_HEADERS = cpuinfo.h

INCLUDES = 	-I @srcdir@/.. \
		-I @srcdir@/../../include

TESTS=cputest

check_PROGRAMS = cputest

cputest_SOURCES = cputest.c

cputest_LDADD = -lcpuinfo -L@builddir@



