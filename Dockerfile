# Pull Ubuntu22.04 image
FROM ubuntu:22.04

# Set environment variable to avoid user interaction during installation (ex : avoid passwords, press y)
ENV DEBIAN_FRONTEND=noninteractive
ENV WORKDIR=/home/brain-spark/

# Install essential packages (git, cmake, build-essential, etc.)
RUN apt-get update && \
    apt-get install -y cmake git build-essential libeigen3-dev \
    python3.10 python3-pip python3-venv \
    tmux vim \
    octovis && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Create working directory
RUN mkdir -p $WORKDIR
WORKDIR $WORKDIR

# Clone repository
RUN cd $WORKDIR && git clone --recurse-submodules https://github.com/SambaranRepo/Octomap.git && \
    cd Octomap && git submodule update --init --recursive && \
    cd OCTOMAP && mkdir build && cd build && cmake .. && make -j${nproc} && make install

RUN cd $WORKDIR && python3 -m venv octomap_venv

# Set default command to bas
CMD ["/bin/bash"]


