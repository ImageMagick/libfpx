FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get install -y autoconf gcc g++ git libtool locales make pkg-config && \
    locale-gen en_US.UTF-8

ENV CFLAGS='-Wall -Wextra -Werror -Wno-error=deprecated-copy -Wno-error=class-memaccess'
ENV CXXFLAGS='-Wall -Wextra -Werror -Wno-error=deprecated-copy -Wno-error=class-memaccess'
