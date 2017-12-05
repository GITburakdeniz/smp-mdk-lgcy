TESTS = smp_sdk_tests
check_PROGRAMS = smp_sdk_tests
smp_sdk_tests_SOURCES = \
						TestRunner.cpp
smp_sdk_tests_CXXFLAGS = $(CPPUNIT_CFLAGS) -I$(top_srcdir)/src
smp_sdk_tests_LDADD = $(CPPUNIT_LIBS) $(top_builddir)/src/libsmpmdk.la
