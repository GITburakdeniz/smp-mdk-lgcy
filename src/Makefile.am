NULL=

sources_h = \
		   Mdk/Object.h \
		   Mdk/Composite.h \
		   Mdk/Component.h \
		   Mdk/EntryPoint.h \
		   Mdk/EventSink.h \
		   Mdk/Aggregate.h \
		   Mdk/Reference.h \
		   Mdk/Management/ManagedObject.h \
		   Mdk/Management/ManagedComponent.h \
		   $(NULL)

sources_c = \
		   Mdk/Object.cpp \
		   Mdk/Composite.cpp \
		   Mdk/Component.cpp \
		   Mdk/Aggregate.cpp \
		   Mdk/Management/ManagedObject.cpp \
		   Mdk/Management/ManagedComponent.cpp \
		   $(NULL)

lib_LTLIBRARIES = libsmpmdk.la

libsmpmdk_la_SOURCES = $(sources_c) $(sources_h)
libsmpmdk_la_LIBADD = @LTLIBOBJS@
libsmpmdk_la_CFLAGS = $(LIBSMPMDK_CFLAGS)
libsmpmdk_la_CXXFLAGS = $(LIBSMPMDK_CXXFLAGS) -std=c++98
libsmpmdk_la_LDFLAGS = -version-info $(LIBSMPMDK_LT_VERSION) -export-dynamic -no-undefined
