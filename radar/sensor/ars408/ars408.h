#ifndef __ARS408_H__
#define __ARS408_H__

class Can;

class ARS408{

public:
    ARS408(char *dev);
    ~ARS408();
    void start();

private:
    Can  *m_can;
    char *m_dev;

    void  run();
    // 友元函数，pthread 创建线程时需要
    friend  void *ars408_read_thread(void *param);
};

#endif

