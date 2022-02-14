Thirdparty dependencies for simulator service
=============================================

Depedencies are temporarily included as source. To be fixed, change to submodules or CMake dependencies.

Prerequisites:

~~~bash
sudo apt-get install libzmq3-dev libboost-all-dev
~~~

For each dependency:

~~~bash
mkdir build
cd build
cmake ..
make && sudo make install
~~~
