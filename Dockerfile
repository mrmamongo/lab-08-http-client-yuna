# rusdevops/bootstrap-cpp image
FROM ubuntu:20.04
LABEL maintainer="mrmamongo@gmail.com"
ENV DEBIAN_FRONTEND noninteractive

# tools for the project
RUN apt-get update \
    && apt-get install gcc -y \
    && apt-get install g++ -y \
    && apt-get install cmake -y \
    && apt-get install wget -y

# install boost
RUN cd /home \
    && wget http://downloads.sourceforge.net/project/boost/boost/1.68.0/boost_1_68_0.tar.gz \
    && tar xfz boost_1_68_0.tar.gz \
    && rm boost_1_68_0.tar.gz \
    && cd boost_1_68_0 \
    && ./bootstrap.sh --with-libraries=system \
    && ./b2 install

COPY . /cpp/src/project/
WORKDIR /cpp/src/project/

RUN apt -y update && \
    apt -y install software-properties-common doxygen rpm g++-7 curl llvm g++ lcov gcovr cmake python3-pip clang git && \
    add-apt-repository -y ppa:ubuntu-toolchain-r/test && \
    pip3 install cpplint gitpython requests && \
    apt clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*
