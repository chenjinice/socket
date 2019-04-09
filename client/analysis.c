#include <stdio.h>
#include <sys/time.h>
#include "analysis.h"
#include "vision.pb-c.h"


static void crowd_fun(uint8_t *buffer,int length)
{
	int i;
	Crowd *c = crowd__unpack(NULL,length,buffer);
	if(c == NULL){
		printf("vclient : crowd unpack failed \n");
		return;
	}
	printf("vclient : [%d crowd]\n",c->n_pedestrian);

	for(i=0;i<c->n_pedestrian;i++){
		Pedestrian * p = c->pedestrian[i];
		printf("vclient : pedestrian[%d],type=%d,camera=%d,x=%d,y=%d\n",i,p->object_type,p->camera,p->x,p->y);
	}
	crowd__free_unpacked(c,NULL);
}


static void obstacles_fun(uint8_t *buffer,int length)
{
	int i;
	Obstacles *obs = obstacles__unpack(NULL,length,buffer);
	if(obs == NULL){
		printf("vclient : obstacles unpack failed \n");
		return;
	}
	printf("vclient : [%d  obstacles]\n",obs->n_obstacle);

	for(i=0;i<obs->n_obstacle;i++){
		Obstacle * p = obs->obstacle[i];
		printf("vclient : obstacle[%d],id=%d,lane_id=%d,camera=%d,x=%d,y=%d\n",i,p->object_id,p->lane_id,p->camera,p->x,p->y);
	}
	obstacles__free_unpacked(obs,NULL);
}


static void availableAreas_fun(uint8_t *buffer,int length)
{
	int i;
	AvailableAreas *area = available_areas__unpack(NULL,length,buffer);
	if(area == NULL){
		printf("vclient : available areas unpack failed \n");
		return;
	}
	printf("vclient : [%d  available areas]\n",area->n_area);

	for(i=0;i<area->n_area;i++){
		AvailableArea *p = area->area[i];
		printf("vclient : area[%d],camera=%d,x1=%d,y1=%d,x2=%d,y2=%d\n",i,p->camera,p->x1,p->y1,p->x2,p->y2);
	}
	available_areas__free_unpacked(area,NULL);
}


void analysis(uint8_t *buffer,int len)
{
	ID	id =  -1;
	Base *base = base__unpack(NULL,len,buffer);
	if(base == NULL){
		printf("vclient : base unpack failed,len = %d \n",len);
		return;
	}
	id = base->id;
	base__free_unpacked(base,NULL);

	switch(id)
	{
	case ID__PEDESTRIAN_D:
		crowd_fun(buffer,len);
		break;
	case ID__ILLEGAL_V1:
		break;
	case ID__CAMERA_CAL:
		break;
	case ID__ROCKFALL_D:
		break;
	case ID__SEEING_D:
		break;
	case ID__AVAILABLE_AREA:
		availableAreas_fun(buffer,len);
		break;
	case ID__OBSTACLE_D:
		obstacles_fun(buffer,len);
		break;
	default:
		break;
	}

}


