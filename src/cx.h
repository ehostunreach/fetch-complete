#ifndef CX_H
#define CX_H

char *cx_get_cursor_kind_str(enum CXCursorKind cx_kind);
char *cx_get_completion_chunk_kind_str(enum CXCompletionChunkKind cx_kind);

unsigned cx_get_default_parsing_options(void);

#endif /* CX_H */
