#ifndef __MYCAN_H__
#define __MYCAN_H__


#include <linux/can.h>


class MyCan
{
public:
    MyCan();
    ~MyCan();
    bool can_open(char *dev);
    int  can_write(struct can_frame *pFrame);
    int  can_read(struct can_frame *pFrame);

private:
    int  m_fd;
    bool m_ready;
};



#endif

