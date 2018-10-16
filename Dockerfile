FROM ubuntu:16.04

# Install deps
RUN DEBIAN_FRONTEND=noninteractive apt-get update && apt-get install -y g++ autoconf automake libtool autoconf-archive pkg-config libpng-dev libjpeg8-dev libtiff5-dev zlib1g-dev libwebp-dev libopenjp2-7-dev libgif-dev curl

# Setup environment for compilation process and build leptonica
RUN LEPTONICA_VERSION="1.76.0" \
      && mkdir -p /home/build_workspace/leptonica \
      && cd /home/build_workspace/leptonica \
      && curl -L "https://github.com/DanBloomberg/leptonica/releases/download/$LEPTONICA_VERSION/leptonica-$LEPTONICA_VERSION.tar.gz" | tar zx \
      && cd "/home/build_workspace/leptonica/leptonica-$LEPTONICA_VERSION" \
      && mkdir build \
      && cd build \
      && ../configure \
      && make \
      && make install \
      && make -j4 check

RUN TESSERACT_VERSION="4.0.0-rc3" \
      && mkdir -p /home/build_workspace/tesseract \
      && cd /home/build_workspace/tesseract \
      && curl -L "https://github.com/tesseract-ocr/tesseract/archive/$TESSERACT_VERSION.tar.gz" | tar zx \
      && cd "/home/build_workspace/tesseract/tesseract-$TESSERACT_VERSION" \
      && ./autogen.sh \
      && ./configure \
      && make \
      && make install \
      && ldconfig

# traineddata should resides in /data/tessdata
ENV TESSDATA_PREFIX /data/tessdata

VOLUME /data


ENTRYPOINT ["/bin/bash"]
