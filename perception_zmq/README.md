编译:
    cd build
    cmake ..
    make -4




proto生成c++文件:
    protoc --cpp_out=. perception.proto


proto生成c文件:
    protoc-c --c_out=. perception.proto



修改 :
    2020.07.20 : server和client都增加filter
    2020.06.28 : server端增加一个ipc发送，去掉 analysis.cc ，替换为设置回调函数的方式，例子写在main.cc，
