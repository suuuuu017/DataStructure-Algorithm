#  ===============================================================================  #
#  If you do not understand how docker works, please do not modify the below lines  #
#  ===============================================================================  #
FROM ubuntu:20.04
RUN sed -i 's:^path-exclude=/usr/share/man:#path-exclude=/usr/share/man:' \
        /etc/dpkg/dpkg.cfg.d/excludes
RUN sed -i 's/archive.ubuntu.com/ftp.sjtu.edu.cn/g' /etc/apt/sources.list
RUN ln -snf /usr/share/zoneinfo/$CONTAINER_TIMEZONE /etc/localtime && echo $CONTAINER_TIMEZONE > /etc/timezone
#  ===============================================================================  #
#  If you do not understand how docker works, please do not modify the above lines  #
#  ===============================================================================  #
# Add any package you like here
RUN apt-get update && \
    apt-get install -y \
    g++\
    man \
    manpages-posix\
    vim\
    sudo\
    less\
    git\
    make\
    cmake\
    zsh
# The password for root is: rootpwd
RUN echo "root:rootpwd" | chpasswd
# Our user is called tiij
RUN useradd -rm -d /home/suuuuu017 -s /usr/bin/zsh -g root -G sudo -u 1000 suuuuu017
# The password for tiij is: nobaidu
RUN echo "suuuuu017:sherlock207617" | chpasswd
USER suuuuu017
WORKDIR /home/suuuuu017

