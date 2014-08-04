Agni
====

Agni aims to be a multi-thread http requester. It's sole purpose is to learn how to stress web applications.


Requirements
=====

 * [libcurl](http://curl.haxx.se/libcurl)
 * [openmp](http://openmp.org/wp/)


Ubuntu users
=====

Installing dependencies

    sudo apt-get install -y libcurl4-openssl-dev lib64gomp1

To compile just run gcc with -fopenmp and -lcurl flags.





