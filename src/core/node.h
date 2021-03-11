
#ifndef _NODE_H_
#define _NODE_H_

typedef enum {
    DOM_ELEMENT_NODE        = 1,
    DOM_ATTRIBUTE_NODE      = 2,
    DOM_TEXT_NODE           = 3,
    DOM_CDATA_SECTION_NODE      = 4,
    DOM_ENTITY_REFERENCE_NODE   = 5,
    DOM_ENTITY_NODE         = 6,
    DOM_PROCESSING_INSTRUCTION_NODE = 7,
    DOM_COMMENT_NODE        = 8,
    DOM_DOCUMENT_NODE       = 9,
    DOM_DOCUMENT_TYPE_NODE      = 10,
    DOM_DOCUMENT_FRAGMENT_NODE  = 11,
    DOM_NOTATION_NODE       = 12,

    /* And a count of the number of node types */
    DOM_NODE_TYPE_COUNT
} DomNodeType;

typedef struct DomNode_ {
    struct DomNode_ *parent;  /**< Parent node */
    struct DomNode_ *first_child; /**< First child node */
    struct DomNode_ *last_child;  /**< Last child node */
    struct DomNode_ *previous;    /**< Previous sibling */
    struct DomNode_ *next;        /**< Next sibling */

    void *attach;

    char *name;
    char *value;
    DomNodeType domType;

    char *id;
    char **classes;
    int classesCount;
    char *inlineStyle;

    char *runnerType;
} DomNode;

#endif // _NODE_H_
