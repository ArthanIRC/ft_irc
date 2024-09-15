FROM alpine:3.20 AS build
RUN apk update && apk add --no-cache build-base
WORKDIR /irc
COPY /src ./src/
COPY /include ./include/
COPY /make ./make/
COPY Makefile .
RUN make ircserv

FROM alpine:3.20 AS runner
RUN apk update && apk add --no-cache libstdc++
RUN addgroup -S irc && adduser -S irc -G irc
COPY --from=build /irc/ircserv /usr/local/bin/ircserv
COPY ./docker-entrypoint.sh /docker-entrypoint.sh
USER irc
ENTRYPOINT ["/docker-entrypoint.sh"]
CMD ["ircserv"]
