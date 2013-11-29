#include <json-glib/json-glib.h>
#include <clang-c/Index.h>
#include <utils/utils.h>
#include "cc_result.h"
#include "cc_request.h"

static unsigned
default_parsing_options(void)
{
    unsigned opts = CXTranslationUnit_DetailedPreprocessingRecord;

    if (u_getenv("CINDEXTEST_EDITING"))
        opts |= clang_defaultEditingTranslationUnitOptions();
    if (u_getenv("CINDEXTEST_COMPLETION_CACHING"))
        opts |= CXTranslationUnit_CacheCompletionResults;
    if (u_getenv("CINDEXTEST_COMPLETION_NO_CACHING"))
        opts &= ~CXTranslationUnit_CacheCompletionResults;
    if (u_getenv("CINDEXTEST_SKIP_FUNCTION_BODIES"))
        opts |= CXTranslationUnit_SkipFunctionBodies;
    if (u_getenv("CINDEXTEST_COMPLETION_BRIEF_COMMENTS"))
        opts |= CXTranslationUnit_IncludeBriefCommentsInCodeCompletion;

    return opts;
}

struct cc_request *
cc_request_init(const char *fname,
                unsigned line, unsigned column,
                const char *clang_args)
{
    struct cc_request *req;
    unsigned parse_opts, reparse_opts;

    u_assert(fname && clang_args);

    req = u_calloc(1, sizeof(struct cc_request));

    if (u_parse_shell_args(clang_args, &req->cx_argc, &req->cx_argv))
        goto ERR_PARSE_ARGS;

    req->fname = u_strdup(fname);
    req->row = line + 1;
    req->col = column + 1;

    req->cx_idx = clang_createIndex(0, 0);
    if (!req->cx_idx) {
        u_warn("Failed to create clang index!\n");
        goto ERR_CLANG_INDEX;
    }

    parse_opts = default_parsing_options();
    req->cx_tu = clang_parseTranslationUnit(req->cx_idx, 0,
                                            (const char * const *) req->cx_argv,
                                            req->cx_argc,
                                            0, 0, parse_opts);
    if (!req->cx_tu) {
        u_warn("Failed to parse translation unit!\n");
        goto ERR_CLANG_PARSE;
    }

    reparse_opts = clang_defaultReparseOptions(req->cx_tu);
    if (clang_reparseTranslationUnit(req->cx_tu, 0, 0, reparse_opts)) {
        u_warn("Unable to reparse translation unit\n");
        goto ERR_CLANG_REPARSE;
    }

    req->res = u_array_init();
    return req;

ERR_CLANG_REPARSE:
    clang_disposeTranslationUnit(req->cx_idx);
ERR_CLANG_PARSE:
    clang_disposeIndex(req->cx_idx);
ERR_CLANG_INDEX:
    u_free(req->cx_argv);
    u_free(req->fname);
ERR_PARSE_ARGS:
    u_free(req);
    return NULL;
}

void
cc_request_fini(struct cc_request *req)
{
    int i, n;

    u_assert(req);

    for (i = 0; i < req->cx_argc; i++) {
        if (req->cx_argv[i])
            u_free(req->cx_argv[i]);
    }
    if (req->cx_argv)
        u_free(req->cx_argv);

    if (req->fname)
        u_free(req->fname);

    if (req->cx_tu)
        clang_disposeTranslationUnit(req->cx_tu);

    if (req->cx_idx)
        clang_disposeIndex(req->cx_idx);

    if (req->res) {
        n = u_array_length(req->res);

        for (i = 0; i < n; i++) {
            struct cc_result *res;

            res = u_array_index(req->res, i);
            cc_result_fini(res);
        }

        u_array_fini(req->res);
    }

    u_free(req);
}

int
cc_request_run(struct cc_request *req)
{
    struct cc_result *res;
    unsigned compl_opts;
    unsigned i, n;

    compl_opts = clang_defaultCodeCompleteOptions();
    req->cx_res = clang_codeCompleteAt(req->cx_tu,
                                       req->fname,
                                       req->row, req->col,
                                       NULL, 0, compl_opts);
    if (!req->cx_res) {
        u_warn("Code completion failed!\n");
        return 1;
    }

    n = req->cx_res->NumResults;
    for (i = 0; i < n; i++)
    {
        res = cc_result_init();
        cc_result_fill(res, req->cx_res->Results + i);
        u_array_add(req->res, res);
    }

    return 0;
}

void
cc_request_json(JsonBuilder *builder, struct cc_request *req)
{
    int i, n;

    u_assert(bld && req);

    json_builder_begin_object(builder);

        json_builder_set_member_name(builder, "results");
        json_builder_begin_array(builder);

            n = u_array_length(req->res);
            for (i = 0; i < n; i++) {
                struct cc_result *res;

                res = u_array_index(req->res, i);
                cc_result_json(builder, res);
            }

        json_builder_end_array(builder);

    json_builder_end_object(builder);
}
