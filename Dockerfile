ARG IMAGE=ubuntu:20.04
FROM ${IMAGE}
ARG IMAGE
RUN echo ${IMAGE}

ENV DEBIAN_FRONTEND="noninteractive"

# be able to source files
RUN rm /bin/sh && ln -s /bin/bash /bin/sh

RUN apt-get update -yqq
RUN apt-get upgrade -yqq
RUN apt-get install -yqq apt-utils

RUN apt-get install -yqq qtbase5-dev libsdl-image1.2-dev libsdl-ttf2.0-dev

ENV DEST=/other/install
RUN mkdir $DEST -p

RUN apt-get install -yqq cmake
RUN apt-get install -yqq build-essential
RUN apt-get install -yqq libxv-dev

RUN apt-get install -yqq python2
RUN apt-get install -yqq python-is-python2
RUN python --version

ENV PATH=$PATH:$DEST/bin
WORKDIR /other

SHELL ["/bin/bash", "-c"]
