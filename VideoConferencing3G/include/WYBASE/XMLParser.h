/**********************************************************
 * Name: KXMLParser.h
 * Author: zhouxiaochuan@gmail.com
 * KDateTime: 2006-10-09
 **********************************************************/
 
#pragma once

//---------------------------------------------------------------------------------------
// XML解析器错误
 enum XML_ERR
{
    eXMLErrorNone = 0,
    eXMLErrorMissingEndTag,
    eXMLErrorEmpty,
    eXMLErrorFirstNotStartTag,
    eXMLErrorMissingTagName,
    eXMLErrorMissingEndTagName,
    eXMLErrorNoMatchingQuote,
    eXMLErrorUnmatchedEndTag,
    eXMLErrorUnmatchedEndClearTag,
    eXMLErrorUnexpectedToken,
    eXMLErrorInvalidTag,
    eXMLErrorNoElements,
    eXMLErrorFileNotFound,
    eXMLErrorFirstTagNotFound,
    eXMLErrorUnknownEscapeSequence,
    eXMLErrorCharConversionError,
    eXMLErrorCannotOpenWriteFile,
    eXMLErrorCannotWriteFile,

    eXMLErrorBase64DataSizeIsNotMultipleOf4,
    eXMLErrorBase64DecodeIllegalCharacter,
    eXMLErrorBase64DecodeTruncatedData,
    eXMLErrorBase64DecodeBufferTooSmall
};

//---------------------------------------------------------------------------------------
// XML数据管理类型,用于XMLNodeContents
 enum XML_ELEMENTTYPE
{
    eNodeChild=0,
    eNodeAttribute=1,
    eNodeText=2,
    eNodeClear=3,
    eNodeNULL=4
};

//---------------------------------------------------------------------------------------
// 如果XML解析失败获得错误结果
typedef struct _XML_RESULTS
{
    enum XML_ERR error;
    int  nLine,nColumn;
}XML_RESULTS,*PXML_RESULTS;

//---------------------------------------------------------------------------------------
// XML清理Node的结构
typedef struct _XML_CLEAR
{
    const char* lpszValue;
	const char* lpszOpenTag;
	const char* lpszCloseTag;
}XML_CLEAR,*PXML_CLEAR;

//---------------------------------------------------------------------------------------
// XML属性结构
typedef struct _XML_ATTRIB
{
	const char* lpszName;
	const char* lpszValue;
}XML_ATTRIB,*PXML_ATTRIB;

class XMLNode;

//---------------------------------------------------------------------------------------
typedef struct _XML_NODEDATA // to allow shallow copy and "intelligent/smart" pointers (automatic delete):
{
    const char*		lpszName;        // Element name (=NULL if root)
    int				nChild,          // Number of child nodes
					nText,           // Number of text fields
					nClear,          // Number of Clear fields (comments)
					nAttribute;      // Number of attributes
    char			IsDeclaration;   // Whether node is an XML declaration - '<?xml ?>'
    struct _XML_NODEDATA*	pParent;        // Pointer to parent element (=NULL if root)
    XMLNode*		pChild;         // Array of child nodes
    const char**	pText;          // Array of text fields
    PXML_CLEAR		pClear;         // Array of clear fields
    PXML_ATTRIB		pAttribute;     // Array of attributes
    int*			pOrder;         // order of the child_nodes,text_fields,clear_fields 
    int				ref_count;       // for garbage collection (smart pointers)
}XML_NODEDATA,*PXML_NODEDATA;

//---------------------------------------------------------------------------------------
// The variable g_XMLAllClearTags below contains the clearTags recognized by the library
// You can modify the initialization of this variable inside the "xmlParser.cpp" file
// to change the clearTags that are currently recognized.
typedef struct _XML_ALLCLEARTAG
{
    const char* lpszOpen;
	int openTagLen;
	const char* lpszClose;
} XML_ALLCLEARTAG;

extern XML_ALLCLEARTAG g_XMLAllClearTags[];

class XMLNodeContents;

//---------------------------------------------------------------------------------------
class AFX_EXT_CLASS XMLNode
{
  private:
    // protected constructors: use one of these four methods to get your first instance of XMLNode:
    //  - ParseString
    //  - ParseFile
    //  - OpenFile
    //  - CreateXMLTopNode
    XMLNode(PXML_NODEDATA pParent, const char* lpszName, char IsDeclaration);
    XMLNode(PXML_NODEDATA p);

  public:

    // You can create your first instance of XMLNode with these 4 functions:
    // (see complete explanation of parameters below)

    static XMLNode CreateXMLTopNode(const char* lpszName, char IsDeclaration=0);
    static XMLNode ParseString(const char* lpXMLString, const char* tag=NULL, PXML_RESULTS pResults=NULL);
    static XMLNode ParseFile(const char* filename, const char* tag=NULL, PXML_RESULTS pResults=NULL);
    static XMLNode OpenFile(const char* filename, const char* tag=NULL);

    // The tag parameter should be the name of the first tag inside the XML file.
    // If the tag parameter is omitted, the 3 functions return a node that represents
    // the head of the xml document including the declaration term (<? ... ?>).

    // The "OpenFile" reports to the screen all the warnings & errors that occurred during 
    // parsing of the XML file. Since each application has its own way to report and deal with errors, 
    // you should rather use the "ParseFile" function to parse XML files and program yourself thereafter 
    // an "error reporting" tailored to your needs (instead of using the very crude "error reporting" 
    // mechanism included inside the "OpenFile" function). 

    // If the XML document is corrupted:
    //   * The "OpenFile" method will:
    //         - display an error message on the console (or inside a messageBox for windows).
    //         - stop execution (exit).
    //     I suggest that you write your own "OpenFile" method tailored to your needs.
    //   * The 2 other methods will initialize the "pResults" variable with some information that
    //     can be used to trace the error.
    //   * If you still want to parse the file, you can use the APPROXIMATE_PARSING option as
    //     explained inside the note at the beginning of the "xmlParser.cpp" file.
    // You can have a user-friendly explanation of the parsing error with this function:
    static const char* getError(XML_ERR error);

    const char* GetName() const;                                         // name of the node
    const char* GetText(int i=0) const;                                  // return ith text field
    int nText() const;                                               // nbr of text field
    XMLNode GetParentNode() const;                                   // return the parent node
    XMLNode GetChildNode(int i=0) const;                             // return ith child node
    XMLNode GetChildNode(const char* name, int i)  const;                // return ith child node with specific name
                                                                     //     (return an empty node if failing)
    XMLNode GetChildNode(const char* name, int *i=NULL) const;           // return next child node with specific name
                                                                     //     (return an empty node if failing)
    XMLNode GetChildNodeWithAttribute(const char* tagName,               // return child node with specific name/attribute
                                      const char* attributeName,         //     (return an empty node if failing)
                                      const char* attributeValue=NULL,   //
                                      int *i=NULL)  const;           //
    int nChildNode(const char* name) const;                              // return the number of child node with specific name
    int nChildNode() const;                                          // nbr of child node
    XML_ATTRIB GetAttribute(int i=0) const;                        // return ith attribute
    const char* GetAttributeName(int i=0) const;                    // return ith attribute name
    const char* GetAttributeValue(int i=0) const;                   // return ith attribute value
    char  IsAttributeSet(const char* name) const;                        // test if an attribute with a specific name is given
    const char* GetAttribute(const char* name, int i) const;                 // return ith attribute content with specific name
                                                                     //     (return a NULL if failing)
    const char* GetAttribute(const char* name, int *i=NULL) const;           // return next attribute content with specific name
                                                                     //     (return a NULL if failing)
    int nAttribute() const;                                          // nbr of attribute
    XML_CLEAR GetClear(int i=0) const;                                // return ith clear field (comments)
    int nClear() const;                                              // nbr of clear field
    char* CreateXMLString(int nFormat=1, int *pnSize=NULL) const;   // create XML string starting from current XMLNode
                                                                     // if nFormat==0, no formatting is required
                                                                     // otherwise this returns an user friendly XML string from a
                                                                     // given element with appropriate white spaces and carriage returns.
                                                                     // if pnSize is given it returns the size in character of the string.
    XML_ERR WriteToFile(const char* filename, const char *encoding=NULL, char nFormat=1) const;
                                                                     // save the content of an xmlNode inside a file.
                                                                     // the nFormat parameter has the same meaning as in the
                                                                     // CreateXMLString function. If "strictUTF8Parsing=1", the
                                                                     // the encoding parameter is ignored and always set to
                                                                     // "utf-8". If "_XMLUNICODE=1", the encoding parameter is
                                                                     // ignored and always set to "utf-16".
    XMLNodeContents enumContents(int i) const;                       // enumerate all the different contents (attribute,child,text,
                                                                     //     clear) of the current XMLNode. The order is reflecting
                                                                     //     the order of the original file/string. 
                                                                     //     NOTE: 0 <= i < nElement();
    int nElement() const;                                            // nbr of different contents for current node
    bool IsEmpty() const;                                            // is this node Empty?
    char IsDeclaration() const;                                      // is this node a declaration <? .... ?>

// to allow shallow/fast copy:
    ~XMLNode();
    XMLNode(const XMLNode &A);
    XMLNode& operator=( const XMLNode& A );

    XMLNode(): d(NULL){};
    static XMLNode emptyXMLNode;
    static XML_CLEAR emptyXMLClear;
    static XML_ATTRIB emptyXMLAttribute;

    // The following functions allows you to create from scratch (or update) a XMLNode structure
    // Start by creating your top node with the "CreateXMLTopNode" function and then add new nodes with the "AddChild" function.
    // The parameter 'pos' gives the position where the childNode, the text or the XMLClearTag will be inserted.
    // The default value (pos=-1) inserts at the end. The value (pos=0) insert at the beginning (Insertion at the beginning is slower than at the end).
    // REMARK: 0 <= pos < nChild()+nText()+nClear()
    XMLNode AddChild(const char* lpszName, char IsDeclaration=0, int pos=-1);
    PXML_ATTRIB AddAttribute(const char* lpszName, const char* lpszValuev);
    const char* AddText(const char* lpszValue, int pos=-1);
    PXML_CLEAR AddClear(const char* lpszValue, const char* lpszOpen=g_XMLAllClearTags[0].lpszOpen, const char* lpszClose=g_XMLAllClearTags[0].lpszClose, int pos=-1);
    XMLNode AddChild(XMLNode nodeToAdd, int pos=-1);          // If the "nodeToAdd" has some parents, it will be detached
                                                                    // from it's parents before being attached to the current XMLNode
    // Some update functions:
    const char* UpdateName(const char* lpszName);                                                    // change node's name
    PXML_ATTRIB UpdateAttribute(PXML_ATTRIB newAttribute, PXML_ATTRIB oldAttribute);         // if the attribute to update is missing, a new one will be added
    PXML_ATTRIB UpdateAttribute(const char* lpszNewValue, const char* lpszNewName=NULL,int i=0);         // if the attribute to update is missing, a new one will be added
    PXML_ATTRIB UpdateAttribute(const char* lpszNewValue, const char* lpszNewName,const char* lpszOldName);  // set lpszNewName=NULL if you don't want to change the name of the attribute
                                                                                                   // if the attribute to update is missing, a new one will be added
    const char* UpdateText(const char* lpszNewValue, int i=0);                                       // if the text to update is missing, a new one will be added
    const char* UpdateText(const char* lpszNewValue, const char* lpszOldValue);                          // if the text to update is missing, a new one will be added
    PXML_CLEAR UpdateClear(const char* lpszNewContent, int i=0);                                    // if the clearTag to update is missing, a new one will be added
    PXML_CLEAR UpdateClear(XML_CLEAR *newP,XML_CLEAR *oldP);                                      // if the clearTag to update is missing, a new one will be added
    PXML_CLEAR UpdateClear(const char* lpszNewValue, const char* lpszOldValue);                         // if the clearTag to update is missing, a new one will be added

    // Some deletion functions:
    void DeleteNodeContent(char force=0);  // delete the content of this XMLNode and the subtree. 
                                           // if force=0, while (references to this node still exist), no memory free occurs
                                           // if force=1, always delete the content of this XMLNode and the subtree and free associated memory
    void DeleteAttribute(const char* lpszName);
    void DeleteAttribute(int i=0);
    void DeleteAttribute(PXML_ATTRIB anAttribute);
    void DeleteText(int i=0);
    void DeleteText(const char* lpszValue);
    void DeleteClear(int i=0);
    void DeleteClear(PXML_CLEAR p);
    void DeleteClear(const char* lpszValue);

    // The strings given as parameters for the following add and update methods (all these methods have
    // a name with the postfix "_WOSD" that means "WithOut String Duplication" ) will be free'd by the
    // XMLNode class. For example, it means that this is incorrect:
    //    xNode.AddText_WOSD("foo");
    //    xNode.UpdateAttribute_WOSD("#newcolor" ,NULL,"color");
    // In opposition, this is correct:
    //    xNode.AddText("foo");
    //    xNode.AddText_WOSD(StringDup("foo"));
    //    xNode.UpdateAttribute("#newcolor" ,NULL,"color");
    //    xNode.UpdateAttribute_WOSD(StringDup("#newcolor"),NULL,"color");
    // Typically, you will never do:
    //    char *b=(char*)malloc(...);
    //    xNode.AddText(b);
    //    free(b);
    // ... but rather:
    //    char *b=(char*)malloc(...);
    //    xNode.AddText_WOSD(b);
    //    ('free(b)' is performed by the XMLNode class)

    static XMLNode CreateXMLTopNode_WOSD(const char* lpszName, char IsDeclaration=0);
    XMLNode AddChild_WOSD(const char* lpszName, char IsDeclaration=0, int pos=-1);
    PXML_ATTRIB AddAttribute_WOSD(const char* lpszName, const char* lpszValue);
    const char* AddText_WOSD(const char* lpszValue, int pos=-1);
    PXML_CLEAR AddClear_WOSD(const char* lpszValue, const char* lpszOpen=g_XMLAllClearTags[0].lpszOpen, const char* lpszClose=g_XMLAllClearTags[0].lpszClose, int pos=-1);

    const char* UpdateName_WOSD(const char* lpszName);
    PXML_ATTRIB UpdateAttribute_WOSD(PXML_ATTRIB newAttribute, PXML_ATTRIB oldAttribute);
    PXML_ATTRIB UpdateAttribute_WOSD(const char* lpszNewValue, const char* lpszNewName=NULL,int i=0);
    PXML_ATTRIB UpdateAttribute_WOSD(const char* lpszNewValue, const char* lpszNewName,const char* lpszOldName);
    const char* UpdateText_WOSD(const char* lpszNewValue, int i=0);
    const char* UpdateText_WOSD(const char* lpszNewValue, const char* lpszOldValue);
    PXML_CLEAR UpdateClear_WOSD(const char* lpszNewContent, int i=0);
    PXML_CLEAR UpdateClear_WOSD(PXML_CLEAR newP,PXML_CLEAR oldP);
    PXML_CLEAR UpdateClear_WOSD(const char* lpszNewValue, const char* lpszOldValue);

    // These are some useful functions when you want to insert a childNode, a text or a XMLClearTag in the
    // middle (at a specified position) of a XMLNode tree already constructed. The return value of these
    // methods is to be used as last parameter (parameter 'pos') of AddChild, AddText or AddClear.
    int PositionOfText(int i=0) const;
    int PositionOfText(const char* lpszValue) const;
    int PositionOfClear(int i=0) const;
    int PositionOfClear(const char* lpszValue) const;
    int PositionOfClear(PXML_CLEAR a) const;
    int PositionOfChildNode(int i=0) const;
    int PositionOfChildNode(XMLNode x) const;
    int PositionOfChildNode(const char* name, int i=0) const; // return the position of the ith childNode with the specified name
                                                          // if (name==NULL) return the position of the ith childNode

    // The SetGlobalOptions function allows you to change two global parameters that affect string&file
    // parsing. First of all, you most-probably will never have to change these 2 global parameters.
    // About the "guessUnicodeChars" parameter:
    //     If "guessUnicodeChars=1" and if this library is compiled in UNICODE mode, then the
    //     "ParseFile" and "OpenFile" functions will test if the file contains ASCII
    //     characters. If this is the case, then the file will be loaded and converted in memory to
    //     UNICODE before being parsed. If "guessUnicodeChars=0", no conversion will
    //     be performed.
    //
    //     If "guessUnicodeChars=1" and if this library is compiled in ASCII/UTF8 mode, then the
    //     "ParseFile" and "OpenFile" functions will test if the file contains UNICODE
    //     characters. If this is the case, then the file will be loaded and converted in memory to
    //     ASCII/UTF8 before being parsed. If "guessUnicodeChars=0", no conversion will
    //     be performed
    //
    //     Sometime, it's useful to set "guessUnicodeChars=0" to disable any conversion
    //     because the test to detect the file-type (ASCII/UTF8 or UNICODE) may fail (rarely).
    //
    // About the "strictUTF8Parsing" parameter:
    //     If "strictUTF8Parsing=0" then we assume that all characters have the same length of 1 byte.
    //     If "strictUTF8Parsing=1" then the characters have different lengths (from 1 byte to 4 bytes)
    //     depending on the content of the first byte of the character.

    static void SetGlobalOptions(char guessUnicodeChars=1, char strictUTF8Parsing=1);

    // The next function try to guess if the character encoding is UTF-8. You most-probably will never 
    // have to use this function. It then returns the appropriate value of the global parameter 
    // "strictUTF8Parsing" described above. The guess is based on the content of a buffer of length 
    // "bufLen" bytes that contains the first bytes (minimum 25 bytes; 200 bytes is a good value) of the 
    // file to be parsed. The "OpenFile" function is using this function to automatically compute 
    // the value of the "strictUTF8Parsing" global parameter. There are several heuristics used to do the 
    // guess. One of the heuristic is based on the "encoding" attribute. The original XML specifications 
    // forbids to use this attribute to do the guess but you can still use it if you set 
    // "useXMLEncodingAttribute" to 1 (this is the default behavior and the behavior of most parsers).

    static char GuessUTF8ParsingParameterValue(void *buffer, int bufLen, char useXMLEncodingAttribute=1);

  private:

// these are functions and structures used internally by the XMLNode class (don't bother about them):

      PXML_NODEDATA d;

      int ParseClearTag(void *pXML, void *pClear);
      int ParseXMLElement(void *pXML);
      void *AddToOrder(int *_pos, int nc, void *p, int size, XML_ELEMENTTYPE xtype);
      int IndexText(const char* lpszValue) const;
      int IndexClear(const char* lpszValue) const;
      static inline int FindPosition(PXML_NODEDATA d, int index, XML_ELEMENTTYPE xtype);
      static int CreateXMLStringR(PXML_NODEDATA pEntry, char* lpszMarker, int nFormat);
      static int RemoveOrderElement(PXML_NODEDATA d, XML_ELEMENTTYPE t, int index);
      static void ExactMemory(PXML_NODEDATA d);      
      static int DetachFromParent(PXML_NODEDATA d);
};

//---------------------------------------------------------------------------------------
// This structure is given by the function "enumContents".
class AFX_EXT_CLASS XMLNodeContents
{
public:
	// This dictates what's the content of the XMLNodeContent
    enum XML_ELEMENTTYPE type;
    // should be an union to access the appropriate data.
    // compiler does not allow union of object with constructor... too bad.
    XMLNode child;
    XML_ATTRIB attrib;
    const char* text;
    XML_CLEAR clear;
};

//---------------------------------------------------------------------------------------
// Duplicate (copy in a new allocated buffer) the source string. This is
// a very handy function when used with all the "XMLNode::*_WOSD" functions.
// (If (cbData!=0) then cbData is the number of chars to duplicate)
AFX_EXT_CLASS char* StringDup(const char* source, int cbData=0);

//---------------------------------------------------------------------------------------
// The 3 following functions are processing strings so that all the characters
// &,",',<,> are replaced by their XML equivalent: &amp;, &quot;, &apos;, &lt;, &gt;.
// These 3 functions are useful when creating from scratch an XML file using the
// "printf", "fprintf", "cout",... functions. If you are creating from scratch an
// XML file using the provided XMLNode class you cannot use these functions (the
// XMLNode class does the processing job for you during rendering). The second
// function ("ToXMLStringFast") allows you to re-use the same output buffer
// for all the conversions so that only a few memory allocations are performed.
// If the output buffer is too small to contain the resulting string, it will
// be enlarged.
AFX_EXT_CLASS char* ToXMLString(const char* source);
AFX_EXT_CLASS char* ToXMLStringFast(char* *destBuffer,int *destSz, const char* source);

//---------------------------------------------------------------------------------------
// you should not use this one (there is a possibility of "destination-buffer-overflow"):
AFX_EXT_CLASS char* ToXMLString(char* dest,const char* source);

//---------------------------------------------------------------------------------------
// Below is a class that allows you to include any binary data (images, sounds,...)
// into an XML document using "Base64 encoding". This class is completely
// separated from the rest of the xmlParser library and can be removed without any problem.
// To include some binary data into an XML file, you must convert the binary data into
// standard text (using "Encode"). To retrieve the original binary data from the
// b64-encoded text included inside the XML file use "Decode". Alternatively, these
// functions can also be used to "encrypt/decrypt" some critical data contained inside
// the XML.
class AFX_EXT_CLASS KXMLParserBase64Tool
{
public:
    KXMLParserBase64Tool(): buf(NULL),buflen(0){}
    ~KXMLParserBase64Tool();

    void FreeBuffer();

    // returns the length of the base64 string that encodes a data buffer of size inBufLen bytes.
    // If "formatted" parameter is true, some space will be reserved for a carriage-return every 72 chars.
    static int EncodeLength(int inBufLen, char formatted=0);

    // The "base64Encode" function returns a string containing the base64 encoding of "inByteLen" bytes 
    // from "inByteBuf". If "formatted" parameter is true, then there will be a carriage-return every 72 chars.
    // The string will be free'd when the KXMLParserBase64Tool object is deleted.
    // All returned strings are sharing the same memory space.
    char* Encode(unsigned char *inByteBuf, unsigned int inByteLen, char formatted=0);

    // returns the number of bytes which will be decoded from "inString".
    static unsigned int DecodeSize(const char* inString, XML_ERR *xe=NULL);

    // returns a pointer to a buffer containing the binary data decoded from "inString"
    // If "inString" is malformed NULL will be returned
    // The output buffer will be free'd when the KXMLParserBase64Tool object is deleted.
    // All output buffer are sharing the same memory space.
    unsigned char* Decode(const char* inString, int *outByteLen=NULL, XML_ERR *xe=NULL);

    // The next function is deprecated.
    // decodes data from "inString" to "outByteBuf". You need to provide the size (in byte) of "outByteBuf" 
    // in "inMaxByteOutBuflen". If "outByteBuf" is not large enough or if data is malformed, then "0"
    // will be returned; otherwise "1".
    static unsigned char Decode(const char* inString, unsigned char *outByteBuf, int inMaxByteOutBuflen, XML_ERR *xe=NULL);

private:
    void *buf;
    int buflen;
    void alloc(int newsize);
};
