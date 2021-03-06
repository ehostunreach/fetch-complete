#include <clang-c/Index.h>
#include <json-glib/json-glib.h>
#include <utils/utils.h>
#include "cc_chunk.h"
#include "cc_result.h"

char *
cursor_kind_str(enum CXCursorKind cx_kind)
{
    char *str = NULL;

    switch (cx_kind) {
        case CXCursor_UnexposedDecl:
        /* case CXCursor_FirstDecl: */
            str = "UnexposedDecl";
            break;
        case CXCursor_StructDecl:
            str = "StructDecl";
            break;
        case CXCursor_UnionDecl:
            str = "UnionDecl";
            break;
        case CXCursor_ClassDecl:
            str = "ClassDecl";
            break;
        case CXCursor_EnumDecl:
            str = "EnumDecl";
            break;
        case CXCursor_FieldDecl:
            str = "FieldDecl";
            break;
        case CXCursor_EnumConstantDecl:
            str = "EnumConstantDecl";
            break;
        case CXCursor_FunctionDecl:
            str = "FunctionDecl";
            break;
        case CXCursor_VarDecl:
            str = "VarDecl";
            break;
        case CXCursor_ParmDecl:
            str = "ParmDecl";
            break;
        case CXCursor_ObjCInterfaceDecl:
            str = "ObjCInterfaceDecl";
            break;
        case CXCursor_ObjCCategoryDecl:
            str = "ObjCCategoryDecl";
            break;
        case CXCursor_ObjCProtocolDecl:
            str = "ObjCProtocolDecl";
            break;
        case CXCursor_ObjCPropertyDecl:
            str = "ObjCPropertyDecl";
            break;
        case CXCursor_ObjCIvarDecl:
            str = "ObjCIvarDecl";
            break;
        case CXCursor_ObjCInstanceMethodDecl:
            str = "ObjCInstanceMethodDecl";
            break;
        case CXCursor_ObjCClassMethodDecl:
            str = "ObjCClassMethodDecl";
            break;
        case CXCursor_ObjCImplementationDecl:
            str = "ObjCImplementationDecl";
            break;
        case CXCursor_ObjCCategoryImplDecl:
            str = "ObjCCategoryImplDecl";
            break;
        case CXCursor_TypedefDecl:
            str = "TypedefDecl";
            break;
        case CXCursor_CXXMethod:
            str = "CXXMethod";
            break;
        case CXCursor_Namespace:
            str = "Namespace";
            break;
        case CXCursor_LinkageSpec:
            str = "LinkageSpec";
            break;
        case CXCursor_Constructor:
            str = "Constructor";
            break;
        case CXCursor_Destructor:
            str = "Destructor";
            break;
        case CXCursor_ConversionFunction:
            str = "ConversionFunction";
            break;
        case CXCursor_TemplateTypeParameter:
            str = "TemplateTypeParameter";
            break;
        case CXCursor_NonTypeTemplateParameter:
            str = "NonTypeTemplateParameter";
            break;
        case CXCursor_TemplateTemplateParameter:
            str = "TemplateTemplateParameter";
            break;
        case CXCursor_FunctionTemplate:
            str = "FunctionTemplate";
            break;
        case CXCursor_ClassTemplate:
            str = "ClassTemplate";
            break;
        case CXCursor_ClassTemplatePartialSpecialization:
            str = "ClassTemplatePartialSpecialization";
            break;
        case CXCursor_NamespaceAlias:
            str = "NamespaceAlias";
            break;
        case CXCursor_UsingDirective:
            str = "UsingDirective";
            break;
        case CXCursor_UsingDeclaration:
            str = "UsingDeclaration";
            break;
        case CXCursor_TypeAliasDecl:
            str = "TypeAliasDecl";
            break;
        case CXCursor_ObjCSynthesizeDecl:
            str = "ObjCSynthesizeDecl";
            break;
        case CXCursor_ObjCDynamicDecl:
            str = "ObjCDynamicDecl";
            break;
        case CXCursor_CXXAccessSpecifier:
        /* case CXCursor_LastDecl: */
            str = "CXXAccessSpecifier";
            break;

        case CXCursor_ObjCSuperClassRef:
        /* case CXCursor_FirstRef: */
            str = "ObjCSuperClassRef";
            break;
        case CXCursor_ObjCProtocolRef:
            str = "ObjCProtocolRef";
            break;
        case CXCursor_ObjCClassRef:
            str = "ObjCClassRef";
            break;
        case CXCursor_TypeRef:
            str = "TypeRef";
            break;
        case CXCursor_CXXBaseSpecifier:
            str = "CXXBaseSpecifier";
            break;
        case CXCursor_TemplateRef:
            str = "TemplateRef";
            break;
        case CXCursor_NamespaceRef:
            str = "NamespaceRef";
            break;
        case CXCursor_MemberRef:
            str = "MemberRef";
            break;
        case CXCursor_LabelRef:
            str = "LabelRef";
            break;
        case CXCursor_OverloadedDeclRef:
            str = "OverloadedDeclRef";
            break;
        case CXCursor_VariableRef:
        /* case CXCursor_LastRef: */
            str = "VariableRef";
            break;

        case CXCursor_InvalidFile:
        /* case CXCursor_FirstInvalid: */
            str = "InvalidFile";
            break;
        case CXCursor_NoDeclFound:
            str = "NoDeclFound";
            break;
        case CXCursor_NotImplemented:
            str = "NotImplemented";
            break;
        case CXCursor_InvalidCode:
        /* case CXCursor_LastInvalid: */
            str = "InvalidCode";
            break;

        case CXCursor_UnexposedExpr:
        /* case CXCursor_FirstExpr: */
            str = "UnexposedExpr";
            break;
        case CXCursor_DeclRefExpr:
            str = "DeclRefExpr";
            break;
        case CXCursor_MemberRefExpr:
            str = "MemberRefExpr";
            break;
        case CXCursor_CallExpr:
            str = "CallExpr";
            break;
        case CXCursor_ObjCMessageExpr:
            str = "ObjCMessageExpr";
            break;
        case CXCursor_BlockExpr:
            str = "BlockExpr";
            break;
        case CXCursor_IntegerLiteral:
            str = "IntegerLiteral";
            break;
        case CXCursor_FloatingLiteral:
            str = "FloatingLiteral";
            break;
        case CXCursor_ImaginaryLiteral:
            str = "ImaginaryLiteral";
            break;
        case CXCursor_StringLiteral:
            str = "StringLiteral";
            break;
        case CXCursor_CharacterLiteral:
            str = "CharacterLiteral";
            break;
        case CXCursor_ParenExpr:
            str = "ParenExpr";
            break;
        case CXCursor_UnaryOperator:
            str = "UnaryOperator";
            break;
        case CXCursor_ArraySubscriptExpr:
            str = "ArraySubscriptExpr";
            break;
        case CXCursor_BinaryOperator:
            str = "BinaryOperator";
            break;
        case CXCursor_CompoundAssignOperator:
            str = "CompoundAssignOperator";
            break;
        case CXCursor_ConditionalOperator:
            str = "ConditionalOperator";
            break;
        case CXCursor_CStyleCastExpr:
            str = "CStyleCastExpr";
            break;
        case CXCursor_CompoundLiteralExpr:
            str = "CompoundLiteralExpr";
            break;
        case CXCursor_InitListExpr:
            str = "InitListExpr";
            break;
        case CXCursor_AddrLabelExpr:
            str = "AddrLabelExpr";
            break;
        case CXCursor_StmtExpr:
            str = "StmtExpr";
            break;
        case CXCursor_GenericSelectionExpr:
            str = "GenericSelectionExpr";
            break;
        case CXCursor_GNUNullExpr:
            str = "GNUNullExpr";
            break;
        case CXCursor_CXXStaticCastExpr:
            str = "CXXStaticCastExpr";
            break;
        case CXCursor_CXXDynamicCastExpr:
            str = "CXXDynamicCastExpr";
            break;
        case CXCursor_CXXReinterpretCastExpr:
            str = "CXXReinterpretCastExpr";
            break;
        case CXCursor_CXXConstCastExpr:
            str = "CXXConstCastExpr";
            break;
        case CXCursor_CXXFunctionalCastExpr:
            str = "CXXFunctionalCastExpr";
            break;
        case CXCursor_CXXTypeidExpr:
            str = "CXXTypeidExpr";
            break;
        case CXCursor_CXXBoolLiteralExpr:
            str = "CXXBoolLiteralExpr";
            break;
        case CXCursor_CXXNullPtrLiteralExpr:
            str = "CXXNullPtrLiteralExpr";
            break;
        case CXCursor_CXXThisExpr:
            str = "CXXThisExpr";
            break;
        case CXCursor_CXXThrowExpr:
            str = "CXXThrowExpr";
            break;
        case CXCursor_CXXNewExpr:
            str = "CXXNewExpr";
            break;
        case CXCursor_CXXDeleteExpr:
            str = "CXXDeleteExpr";
            break;
        case CXCursor_UnaryExpr:
            str = "UnaryExpr";
            break;
        case CXCursor_ObjCStringLiteral:
            str = "ObjCStringLiteral";
            break;
        case CXCursor_ObjCEncodeExpr:
            str = "ObjCEncodeExpr";
            break;
        case CXCursor_ObjCSelectorExpr:
            str = "ObjCSelectorExpr";
            break;
        case CXCursor_ObjCProtocolExpr:
            str = "ObjCProtocolExpr";
            break;
        case CXCursor_ObjCBridgedCastExpr:
            str = "ObjCBridgedCastExpr";
            break;
        case CXCursor_PackExpansionExpr:
            str = "PackExpansionExpr";
            break;
        case CXCursor_SizeOfPackExpr:
            str = "SizeOfPackExpr";
            break;
        case CXCursor_LambdaExpr:
            str = "LambdaExpr";
            break;
        case CXCursor_ObjCBoolLiteralExpr:
            str = "ObjCBoolLiteralExpr";
            break;
        case CXCursor_ObjCSelfExpr:
        /* case CXCursor_LastExpr: */
            str = "ObjCSelfExpr";
            break;

        case CXCursor_UnexposedStmt:
        /* case CXCursor_FirstStmt: */
            str = "UnexposedStmt";
            break;
        case CXCursor_LabelStmt:
            str = "LabelStmt";
            break;
        case CXCursor_CompoundStmt:
            str = "CompoundStmt";
            break;
        case CXCursor_CaseStmt:
            str = "CaseStmt";
            break;
        case CXCursor_DefaultStmt:
            str = "DefaultStmt";
            break;
        case CXCursor_IfStmt:
            str = "IfStmt";
            break;
        case CXCursor_SwitchStmt:
            str = "SwitchStmt";
            break;
        case CXCursor_WhileStmt:
            str = "WhileStmt";
            break;
        case CXCursor_DoStmt:
            str = "DoStmt";
            break;
        case CXCursor_ForStmt:
            str = "ForStmt";
            break;
        case CXCursor_GotoStmt:
            str = "GotoStmt";
            break;
        case CXCursor_IndirectGotoStmt:
            str = "IndirectGotoStmt";
            break;
        case CXCursor_ContinueStmt:
            str = "ContinueStmt";
            break;
        case CXCursor_BreakStmt:
            str = "BreakStmt";
            break;
        case CXCursor_ReturnStmt:
            str = "ReturnStmt";
            break;
        case CXCursor_AsmStmt:
        /* case CXCursor_GCCAsmStmt: */
            str = "AsmStmt";
            break;
        case CXCursor_ObjCAtTryStmt:
            str = "ObjCAtTryStmt";
            break;
        case CXCursor_ObjCAtCatchStmt:
            str = "ObjCAtCatchStmt";
            break;
        case CXCursor_ObjCAtFinallyStmt:
            str = "ObjCAtFinallyStmt";
            break;
        case CXCursor_ObjCAtThrowStmt:
            str = "ObjCAtThrowStmt";
            break;
        case CXCursor_ObjCAtSynchronizedStmt:
            str = "ObjCAtSynchronizedStmt";
            break;
        case CXCursor_ObjCAutoreleasePoolStmt:
            str = "ObjCAutoreleasePoolStmt";
            break;
        case CXCursor_ObjCForCollectionStmt:
            str = "ObjCForCollectionStmt";
            break;
        case CXCursor_CXXCatchStmt:
            str = "CXXCatchStmt";
            break;
        case CXCursor_CXXTryStmt:
            str = "CXXTryStmt";
            break;
        case CXCursor_CXXForRangeStmt:
            str = "CXXForRangeStmt";
            break;
        case CXCursor_SEHTryStmt:
            str = "SEHTryStmt";
            break;
        case CXCursor_SEHExceptStmt:
            str = "SEHExceptStmt";
            break;
        case CXCursor_SEHFinallyStmt:
            str = "SEHFinallyStmt";
            break;
        case CXCursor_MSAsmStmt:
            str = "MSAsmStmt";
            break;
        case CXCursor_NullStmt:
            str = "NullStmt";
            break;
        case CXCursor_DeclStmt:
        /* case CXCursor_LastStmt: */
            str = "DeclStmt";
            break;

        case CXCursor_TranslationUnit:
            str = "TranslationUnit";
            break;

        case CXCursor_UnexposedAttr:
        /* case CXCursor_FirstAttr: */
            str = "UnexposedAttr";
            break;
        case CXCursor_IBActionAttr:
            str = "IBActionAttr";
            break;
        case CXCursor_IBOutletAttr:
            str = "IBOutletAttr";
            break;
        case CXCursor_IBOutletCollectionAttr:
            str = "IBOutletCollectionAttr";
            break;
        case CXCursor_CXXFinalAttr:
            str = "CXXFinalAttr";
            break;
        case CXCursor_CXXOverrideAttr:
            str = "CXXOverrideAttr";
            break;
        case CXCursor_AnnotateAttr:
            str = "AnnotateAttr";
            break;
        case CXCursor_AsmLabelAttr:
        /* case CXCursor_LastAttr: */
            str = "AsmLabelAttr";
            break;

        case CXCursor_PreprocessingDirective:
        /* case CXCursor_FirstPreprocessing: */
            str = "PreprocessingDirective";
            break;
        case CXCursor_MacroDefinition:
            str = "MacroDefinition";
            break;
        case CXCursor_MacroExpansion:
        /* case CXCursor_MacroInstantiation: */
            str = "MacroExpansionInstantiation";
            break;
        case CXCursor_InclusionDirective:
        /* case CXCursor_LastPreprocessing: */
            str = "InclusionDirective";
            break;

        case CXCursor_ModuleImportDecl:
        /* case CXCursor_FirstExtraDecl:
           case CXCursor_LastExtraDecl: */
            str = "ModuleImportDecl";
            break;

        default:
            u_warn("Unknown cursor kind: %d\n", cx_kind);
            break;
    }

    return u_strdup(str);
}

char *
completion_chunk_kind_str(enum CXCompletionChunkKind cx_kind)
{
    char *str = NULL;

    switch (cx_kind) {
        case CXCompletionChunk_Optional:
            str = "Optional";
            break;
        case CXCompletionChunk_TypedText:
            str = "TypedText";
            break;
        case CXCompletionChunk_Text:
            str = "Text";
            break;
        case CXCompletionChunk_Placeholder:
            str = "Placeholder";
            break;
        case CXCompletionChunk_Informative:
            str = "Informative";
            break;
        case CXCompletionChunk_CurrentParameter:
            str = "CurrentParameter";
            break;
        case CXCompletionChunk_LeftParen:
            str = "LeftParen";
            break;
        case CXCompletionChunk_RightParen:
            str = "RightParen";
            break;
        case CXCompletionChunk_LeftBracket:
            str = "LeftBracket";
            break;
        case CXCompletionChunk_RightBracket:
            str = "RightBracket";
            break;
        case CXCompletionChunk_LeftBrace:
            str = "LeftBrace";
            break;
        case CXCompletionChunk_RightBrace:
            str = "RightBrace";
            break;
        case CXCompletionChunk_LeftAngle:
            str = "LeftAngle";
            break;
        case CXCompletionChunk_RightAngle:
            str = "RightAngle";
            break;
        case CXCompletionChunk_Comma:
            str = "Comma";
            break;
        case CXCompletionChunk_ResultType:
            str = "ResultType";
            break;
        case CXCompletionChunk_Colon:
            str = "Colon";
            break;
        case CXCompletionChunk_SemiColon:
            str = "SemiColon";
            break;
        case CXCompletionChunk_Equal:
            str = "Equal";
            break;
        case CXCompletionChunk_HorizontalSpace:
            str = "HorizontalSpace";
            break;
        case CXCompletionChunk_VerticalSpace:
            str = "VerticalSpace";
            break;

        default:
            u_warn("Unknown cursor kind: %d\n", cx_kind);
            break;
    }

    return str;
}


struct cc_result *
cc_result_init(void)
{
    struct cc_result *res;

    res = u_malloc(sizeof(struct cc_result));

    res->typed_chunk = u_malloc(sizeof(struct cc_chunk));
    res->chunks = u_array_init();

    return res;
}

void
cc_result_fini(struct cc_result *res)
{
    unsigned i, n;

    u_assert(res && res->typed_chunk && res->chunks);

    n = u_array_length(res->chunks);
    for (i = 0; i < n; i++) {
        struct cc_chunk *chunk;

        chunk = u_array_index(res->chunks, i);
        cc_chunk_fini(chunk);
    }

    cc_chunk_fini(res->typed_chunk);

    u_array_fini(res->chunks);
    u_free(res);
}

static void
cc_result_add_chunk(struct cc_result *res, enum CXCompletionChunkKind ck,
                                           CXString completion_string)
{
    struct cc_chunk *chunk;
    char *kind_str, *text_str;
    const char *c_str;

    kind_str = completion_chunk_kind_str(ck);
    c_str = clang_getCString(completion_string);
    text_str = u_strdup(c_str ? c_str : "");

    chunk = cc_chunk_init(kind_str, text_str);
    u_array_add(res->chunks, chunk);

    if (ck == CXCompletionChunk_TypedText)
        res->typed_chunk->text = u_strdup(chunk->text);
    else
        res->typed_chunk->text = u_strdup("");

    clang_disposeString(completion_string);
}

void
cc_result_fill(struct cc_result *cc_res, CXCompletionResult *cx_res)
{
    unsigned i, n;

    u_assert(cc_res && cx_res);

    cc_res->typed_chunk->kind = cursor_kind_str(cx_res->CursorKind);

    n = clang_getNumCompletionChunks(cx_res->CompletionString);
    for (i = 0; i < n; i++) {
        enum CXCompletionChunkKind ck;

        ck = clang_getCompletionChunkKind(cx_res->CompletionString, i);
        if (ck == CXCompletionChunk_Optional) {
            u_warn("Ignoring optional completion chunk.\n");
            continue;
        }

        cc_result_add_chunk(cc_res, ck,
                clang_getCompletionChunkText(cx_res->CompletionString, i));
    }
}

void
cc_result_json(JsonBuilder *builder, struct cc_result *res)
{
    struct cc_chunk *chunk;
    int i, n;

    u_assert(builder && res);

    json_builder_begin_object(builder);

        json_builder_set_member_name(builder, "typed");
        cc_chunk_json(builder, res->typed_chunk);

        json_builder_set_member_name(builder, "chunks");
        json_builder_begin_array(builder);

            n = u_array_length(res->chunks);
            for (i = 0; i < n; i++) {
                chunk = u_array_index(res->chunks, i);
                cc_chunk_json(builder, chunk);
            }

        json_builder_end_array(builder);

    json_builder_end_object(builder);
}
