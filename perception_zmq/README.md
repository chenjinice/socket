编译:
    cd build
    cmake ..
    make -4




proto生成c++文件:
    protoc --cpp_out=. perception.proto


proto生成c文件:
    protoc-c --c_out=. perception.proto



修改 :
    2020-09-29 :
                1.修改动态配时场景id 和 消息名
                2.修改能见度场景数据内容
                3.增加车流量统计场景数据
    2020.08.01 : 修改协议，添加场景id ，改枚举名字，改序号
    2020.07.20 : server和client都增加filter
    2020.06.28 : server端增加一个ipc发送，去掉 analysis.cc ，替换为设置回调函数的方式，例子写在main.cc，
