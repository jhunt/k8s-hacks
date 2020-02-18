FROM ubuntu:18.04 AS stage1

RUN apt-get update \
 && apt-get install -y build-essential

WORKDIR /src
COPY . .
RUN gcc -static pause.c -o /pause

FROM scratch
COPY --from=stage1 /pause /pause
ENTRYPOINT ["/pause"]
