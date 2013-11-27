lib_LTLIBRARIES = libutils.la
libutils_la_SOURCES = utils/util.c
libutils_la_CFLAGS = $(glib_CFLAGS)
libutils_la_LDFLAGS = $(glib_LIBS)

bin_PROGRAMS = server
server_SOURCES = server.c request.c
server_CFLAGS = $(libsoup_CFLAGS) $(json_glib_CFLAGS)
server_LDFLAGS = $(libsoup_LIBS) $(json_glib_LIBS)
server_LDADD = libutils.la
