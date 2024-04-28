FROM debian:buster-slim
ENV DEBIAN_FRONTEND noninteractive

ENV TZ=America/New_York
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get -y update && apt-get -y install \
	bc \
    build-essential \
    bzip2 \
	bzr \
	cmake \
	cmake-curses-gui \
	cpio \
	device-tree-compiler \
	git \
	imagemagick \
	libncurses5-dev \
	locales \
	make \
	p7zip-full \
	rsync \
	sharutils \
	scons \
	tree \
	unzip \
	vim \
	wget \
	zip \
  && rm -rf /var/lib/apt/lists/*

RUN dpkg --add-architecture armhf
RUN apt -y update
RUN apt-get -y update 
RUN apt -y install libc6:armhf

RUN apt-get -y install libsdl2-dev
RUN apt-get -y install libsdl2-dev:armhf

RUN apt-get -y install libsdl2-ttf-dev
RUN apt-get -y install libsdl2-dev:armhf
RUN apt-get -y install libsdl2-ttf-dev:armhf

RUN export LIBGL_ALWAYS_INDIRECT=1

RUN mkdir -p /root/workspace
WORKDIR /root

COPY test ./test
COPY support .
RUN ./build-toolchain.sh
RUN cat ./setup-env.sh >> .bashrc

VOLUME /root/workspace
WORKDIR /root/workspace

CMD ["/bin/bash"]