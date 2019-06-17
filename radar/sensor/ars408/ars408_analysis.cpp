#include <stdio.h>
#include "ars408_analysis.h"
#include "ars408_protocol.h"


void ars408_analysis(can_frame *pFrame)
{
    int cmd = ars408_get_cmd(pFrame->can_id);
//    printf("id ==== 0x%X,num = %d,cmd = 0x%X\n",pFrame->can_id,pFrame->can_dlc,cmd);

    switch (cmd) {
    case ARS408_CMD_OBJECT_LIST:
        ars408_get_objectNum(pFrame);
        break;
    case ARS408_CMD_OBJECT_INFO:
        ars408_get_objectInfo(pFrame);
        break;
    case ARS408_CMD_OBJECT_QUALITY:
        break;
    case ARS408_CMD_OBJECT_EXTEND:
        break;
    case ARS408_CMD_VERSION:
//        ars408_get_version(pFrame);
        break;
    default:
        break;
    }
}
