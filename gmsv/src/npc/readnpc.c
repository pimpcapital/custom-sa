#include <stdio.h>

#include "common.h"
#include "npctemplate.h"
#include "npccreate.h"

int NPC_readNPCSettingFiles(char *topdirectory, int templatesize, int createsize) {
  print("\n");
  if(NPC_readNPCTemplateFiles(topdirectory, templatesize) == FALSE)
    return FALSE;

  if(NPC_readNPCCreateFiles(topdirectory, createsize) == FALSE)
    return FALSE;

  return TRUE;
}
