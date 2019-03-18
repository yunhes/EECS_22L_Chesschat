#ifndef ServerLog
#define ServerLog

#include "UserList.h"
#include "ChatStruct.h"
#include <string.h>
#include <stdlib.h>

void saveLog(ULIST *list);
void loadLog(ULIST *list);
void conversionSpace(char *string);
void conversionSpaceBack(char *string);
void conversionNewline(char *string);
void conversionNewlineBack(char *string);
void spaceRemove(char *removeString);

#endif
