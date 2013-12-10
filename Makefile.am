dist_doc_DATA = README
ACLOCAL_AMFLAGS = -I m4

bin_PROGRAMS = fetch-complete

# utils
fetch_complete_SOURCES = \
					src/utils/u_alloc.c		\
					src/utils/u_array.c		\
					src/utils/u_dict.c		\
					src/utils/u_log.c		\
					src/utils/u_misc.c		\
					src/utils/u_string.c

# complete
fetch_complete_SOURCES += \
					src/complete/cc_chunk.c		\
					src/complete/cc_result.c	\
					src/complete/cc_request.c	\
					src/complete/complete.c

# server
fetch_complete_SOURCES += \
					src/request.c	\
					src/server.c


# flags
fetch_complete_CFLAGS = $(DEPS_CFLAGS) $(CLANG_CFLAGS) -DUTILS_COMPILATION -I ./src
fetch_complete_LDFLAGS = $(DEPS_LIBS) $(CLANG_LDFLAGS)
