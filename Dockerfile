FROM alpine as builder

WORKDIR /tmp

RUN apk add --no-cache git gcc g++ make cmake

COPY . .

RUN cmake . -DCMAKE_BUILD_TYPE=Release && \
    make -j$(($(nproc)+1))


FROM alpine

WORKDIR /cuberite

RUN apk add --no-cache py-pip py-setuptools && \
    pip install --no-cache-dir wheel && \
    pip install --no-cache-dir mcstatus

COPY --from=builder /tmp/Server/Cuberite /usr/local/bin/cuberite
COPY --from=builder /tmp/Server/ /cuberite/
RUN rm -f /cuberite/Cuberite

VOLUME /cuberite

HEALTHCHECK --timeout=3s CMD mcstatus localhost status || exit 1

ENTRYPOINT ["cuberite"]
