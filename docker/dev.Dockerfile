FROM mcr.microsoft.com/devcontainers/cpp:ubuntu

RUN sudo apt update
RUN sudo apt remove -y cmake
RUN sudo apt install -y \
    python3-pip \
    g++-10 \
    protobuf-compiler \
    clang-format \
    uncrustify \
    clang-tidy
RUN pip install \
    cmake \
    pre-commit \
    cpplint