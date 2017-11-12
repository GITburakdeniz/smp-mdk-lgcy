NULL=

sources_h = \
		   Mdk/Object.h \
		   $(NULL)

sources_c = \
		   Mdk/Object.cpp \
		   $(NULL)

lib_LTLIBRARIES = libsmpmdk.la

libsmpmdk_la_SOURCES = $(sources_c) $(sources_h)
libsmpmdk_la_LIBADD = @LTLIBOBJS@
libsmpmdk_la_CFLAGS = $(LIBSMPMDK_CFLAGS)
libsmpmdk_la_LDFLAGS = -version-info $(LIBSMPMDK_LT_VERSION) -export-dynamic -no-undefined
