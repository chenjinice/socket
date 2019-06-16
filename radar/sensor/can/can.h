#ifndef __CAN_H__
#define __CAN_H__


#include <linux/can.h>


class Can
{
public:
    Can();
    ~Can();
    bool can_open(char *dev);
    int  can_write(struct can_frame *pFrame);
    int  can_read(struct can_frame *pFrame);

private:
    int  m_fd;
    bool m_ready;
};



#endif

