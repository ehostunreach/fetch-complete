lib_LTLIBRARIES = libutils.la libcomplete.la

libutils_la_SOURCES = utils/u_log.c		\
					  utils/u_alloc.c	\
					  utils/u_string.c	\
					  utils/u_array.c	\
					  utils/u_dict.c	\
					  utils/u_misc.c
include_HEADERS = utils/u_log.h			\
				  utils/u_alloc.h		\
				  utils/u_string.h		\
				  utils/u_array.h		\
				  utils/u_dict.h		\
				  utils/u_misc.h		\
				  utils/utils.h			\
				  complete/complete.h

libutils_la_CFLAGS = $(glib_CFLAGS) -DUTILS_COMPILATION
libutils_la_LDFLAGS = $(glib_LIBS)

libcomplete_la_SOURCES = complete/cc_chunk.c		\
					  complete/cc_result.c		\
					  complete/cc_request.c		\
					  complete/complete.c

libcomplete_la_CFLAGS = $(json_glib_CFLAGS) $(CLANG_CFLAGS) -I ./utils
libcomplete_la_LDFLAGS = $(json_glib_LIBS) $(CLANG_LDFLAGS)
libcomplete_la_LIBADD = libutils.la

bin_PROGRAMS = server
server_SOURCES = server.c request.c
server_CFLAGS = $(libsoup_CFLAGS) $(json_glib_CFLAGS) $(CLANG_CFLAGS) -I ./utils -I ./complete
server_LDFLAGS = $(libsoup_LIBS) $(json_glib_LIBS) $(CLANG_LDFLAGS)
server_LDADD = libutils.la libcomplete.la

