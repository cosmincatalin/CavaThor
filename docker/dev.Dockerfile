FROM mcr.microsoft.com/devcontainers/cpp:ubuntu

RUN sudo apt update
RUN sudo apt remove -y cmake
RUN sudo apt install -y \
    python3-pip \
    g++-10 \
    clang-format \
    uncrustify \
    clang-tidy
RUN pip install \
    cmake==3.25.0 \
    pre-commit==2.20.0 \
    cpplint==1.6.1
env PROTOC_VERSION=21.9
env PROTOC_ZIP=protoc-${PROTOC_VERSION}-linux-x86_64.zip
RUN wget https://github.com/protocolbuffers/protobuf/releases/download/v${PROTOC_VERSION}/${PROTOC_ZIP} && \
    sudo unzip -o $PROTOC_ZIP -d /usr/local bin/protoc && \
    sudo unzip -o $PROTOC_ZIP -d /usr/local 'include/*' && \
    rm -f $PROTOC_ZIP
RUN git config --global --add safe.directory /workspace
