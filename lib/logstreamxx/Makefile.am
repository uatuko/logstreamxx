## [logstreamxx] lib/logstreamxx/

AM_CPPFLAGS                = -I$(top_srcdir)/lib
liblogstreamxxincludedir   = $(includedir)/logstreamxx

lib_LTLIBRARIES            = liblogstreamxx.la
liblogstreamxx_la_LIBADD   =
liblogstreamxx_la_LDFLAGS  = -version-info @LIBLOGSTREAMXX_LT_VERSION@ -no-undefined
liblogstreamxx_la_SOURCES  = \
	logstreambuf.cpp \
	logstream.cpp

liblogstreamxxinclude_HEADERS = \
	priority.h \
	logstreambuf.h \
	logstream.h

