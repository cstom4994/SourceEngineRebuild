﻿/* Stuff to export relevant 'expat' entry points from pyexpat to other
 * parser modules, such as cElementTree. */

/* note: you must import expat.h before importing this module! */

#define PyExpat_CAPI_MAGIC  "pyexpat.expat_CAPI 1.0"

struct PyExpat_CAPI {
    char *magic; /* set to PyExpat_CAPI_MAGIC */
    int size; /* set to sizeof(struct PyExpat_CAPI) */
    int MAJOR_VERSION;
    int MINOR_VERSION;
    int MICRO_VERSION;

    /* pointers to selected expat functions.  add new functions at
       the end, if needed */
    const XML_LChar *(*ErrorString)(enum XML_Error code);

    enum XML_Error (*GetErrorCode)(XML_Parser parser);

    XML_Size (*GetErrorColumnNumber)(XML_Parser parser);

    XML_Size (*GetErrorLineNumber)(XML_Parser parser);

    enum XML_Status (*Parse)(
            XML_Parser parser, const char *s, int len, int isFinal);

    XML_Parser (*ParserCreate_MM)(
            const XML_Char *encoding, const XML_Memory_Handling_Suite *memsuite,
            const XML_Char *namespaceSeparator);

    void (*ParserFree)(XML_Parser parser);

    void (*SetCharacterDataHandler)(
            XML_Parser parser, XML_CharacterDataHandler handler);

    void (*SetCommentHandler)(
            XML_Parser parser, XML_CommentHandler handler);

    void (*SetDefaultHandlerExpand)(
            XML_Parser parser, XML_DefaultHandler handler);

    void (*SetElementHandler)(
            XML_Parser parser, XML_StartElementHandler start,
            XML_EndElementHandler end);

    void (*SetNamespaceDeclHandler)(
            XML_Parser parser, XML_StartNamespaceDeclHandler start,
            XML_EndNamespaceDeclHandler end);

    void (*SetProcessingInstructionHandler)(
            XML_Parser parser, XML_ProcessingInstructionHandler handler);

    void (*SetUnknownEncodingHandler)(
            XML_Parser parser, XML_UnknownEncodingHandler handler,
            void *encodingHandlerData);

    void (*SetUserData)(XML_Parser parser, void *userData);
    /* always add new stuff to the end! */
};

