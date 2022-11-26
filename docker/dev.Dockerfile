FROM mcr.microsoft.com/devcontainers/cpp:ubuntu

RUN sudo apt update
RUN sudo apt remove -y cmake
RUN sudo apt install -y \
    python3-pip \
    g++-10 \
    protobuf-compiler
RUN pip install \
    cmake \
    pre-commit