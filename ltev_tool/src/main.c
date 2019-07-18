#include <stdio.h>
#include "MessageFrame.h"
//#include "IA5String.h"


static int ltev_msgcnt = 0;


int main(int argc,char *argv[])
{
	MessageFrame_t *msgframe;
	msgframe= NULL;

	ltev_msgcnt++;
	if(ltev_msgcnt > 127)
		ltev_msgcnt = 0;

	msgframe = (MessageFrame_t*)malloc(sizeof(MessageFrame_t));
	memset(msgframe,0,sizeof(MessageFrame_t));
	msgframe->present = MessageFrame_PR_rsiFrame;
	msgframe->choice.rsiFrame.msgCnt = ltev_msgcnt;
	/*just test*/
	double tmp_lat, tmp_lon;
	tmp_lat = 1234567;
	tmp_lon = 7654321;

	msgframe->choice.rsiFrame.msgCnt = ltev_msgcnt;
	int rsu_id = 1234;
	msgframe->choice.rsiFrame.id.buf = malloc(8);
	memcpy(msgframe->choice.rsiFrame.id.buf,&rsu_id,sizeof(rsu_id));   // rsu_id
	msgframe->choice.rsiFrame.id.size = 8;

	msgframe->choice.rsiFrame.rsiId = 0;
	msgframe->choice.rsiFrame.refPos.lat = tmp_lat * 1e7;
	msgframe->choice.rsiFrame.refPos.Long = tmp_lon * 1e7;

	msgframe->choice.rsiFrame.alertType = 35;	// 前方施工提醒
	msgframe->choice.rsiFrame.description = calloc(sizeof(IA5String_t),1);

	msgframe->choice.rsiFrame.description->buf =(uint8_t*)calloc(1,sizeof(int));

	msgframe->choice.rsiFrame.description->size = sizeof(int);
	msgframe->choice.rsiFrame.alertRadius = 0;

	{
		int i;
		for(i = 0;i<2;i++)
		{
			struct PositionOffsetLLV* ptemp_alertPath;
			ptemp_alertPath  =calloc(sizeof(struct PositionOffsetLLV),1);
			memset(ptemp_alertPath,0,sizeof(struct PositionOffsetLLV));
			ptemp_alertPath->offsetLL.present = PositionOffsetLL_PR_position_LL6;
			ptemp_alertPath->offsetLL.choice.position_LL6.lat = 0;
			ptemp_alertPath->offsetLL.choice.position_LL6.lon = 0;

			ASN_SET_ADD(&msgframe->choice.rsiFrame.alertPath.list,ptemp_alertPath);
		}
	}

	printf("hello world\n");
	return 0;
}
