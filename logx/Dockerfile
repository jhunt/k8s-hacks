FROM alpine:3 AS build
RUN apk update
RUN apk add musl-dev gcc make
WORKDIR /src
COPY . .
RUN make logx

FROM alpine:3
COPY --from=build /src/logx /logx
ENTRYPOINT ["/logx"]
CMD ["8192"]
