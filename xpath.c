#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

void print_content(xmlNodeSetPtr nodes, xmlDocPtr doc) {
  xmlNodePtr cur;
  xmlChar *xmlContent;
  char *content = "";
  int size;

  size = (nodes) ? nodes->nodeNr : 0;

  if (size > 0) {
    cur = nodes->nodeTab[0];
    if ((xmlContent = xmlNodeListGetString(doc, cur->xmlChildrenNode, 1)) != NULL) {
      content = (char*) xmlContent;
      xmlFree(xmlContent);
    }
  }
  fprintf(stdout, "%s\t", content);
}

int main(int argc, char **argv) {
  int exitStatus = 0;
  xmlDocPtr doc;
  xmlXPathContextPtr xpathCtx;
  xmlXPathObjectPtr xpathObj;

  LIBXML_TEST_VERSION       // Macro to check API for match with the DLL we are using
  xmlKeepBlanksDefault(0);  // disable blanks

  if (argc < 3) {
    fprintf(stderr, "usage: xpath <file> <xpath>\n");
    exitStatus=-1;
  } else {
    if ((doc = xmlParseFile(argv[1])) == NULL) {
      fprintf(stderr,"Error: unable to parse file \"%s\"\n", argv[1]);
      exitStatus=-1;
    } else {
      if ((xpathCtx = xmlXPathNewContext(doc)) == NULL) {
        fprintf(stderr,"Error: unable to create new XPath context\n");
        exitStatus=-1;
      } else {
        //for(int i=2;i<argc;i++) fprintf(stdout,"%s\t",argv[i]);
        //fprintf(stdout,"\n");

        for(int i=2;i<argc;i++) {
          if ((xpathObj = xmlXPathEvalExpression(BAD_CAST argv[i], xpathCtx)) == NULL) {
            fprintf(stderr,"Error: unable to evaluate xpath expression \"%s\"\n", argv[i]);
            exitStatus=-1;
          } else {
            print_content(xpathObj->nodesetval, doc);
            xmlXPathFreeObject(xpathObj);
          }
        }
        fprintf(stdout,"\n");
        xmlXPathFreeContext(xpathCtx);
      }
      xmlFreeDoc(doc);
    }
  }

  xmlCleanupParser();
  return exitStatus;
}