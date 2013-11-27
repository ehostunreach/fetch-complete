lib_LTLIBRARIES = libutils.la
libutils_la_SOURCES = utils/u_log.c		\
					  utils/u_alloc.c	\
					  utils/u_string.c	\
					  utils/u_array.c	\
					  utils/u_dict.c
include_HEADERS = utils/u_log.h			\
				  utils/u_alloc.h		\
				  utils/u_string.h		\
				  utils/u_array.h		\
				  utils/u_dict.h		\
				  utils/utils.h
libutils_la_CFLAGS = $(glib_CFLAGS) -DUTILS_COMPILATION
libutils_la_LDFLAGS = $(glib_LIBS)

bin_PROGRAMS = server
server_SOURCES = server.c request.c
server_CFLAGS = $(libsoup_CFLAGS) $(json_glib_CFLAGS) -I ./utils
server_LDFLAGS = $(libsoup_LIBS) $(json_glib_LIBS)
server_LDADD = libutils.la

