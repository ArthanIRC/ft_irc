FROM alpine:3.20 AS build
RUN apk update && apk add --no-cache build-base
WORKDIR /irc
COPY /src ./src/
COPY /include ./include/
COPY /make ./make/
COPY Makefile .
RUN make

FROM alpine:3.20 AS runner
RUN apk update && apk add --no-cache libstdc++
RUN addgroup -S irc && adduser -S irc -G irc
COPY --from=build /irc/ircserv /usr/local/bin/ircserv
USER irc
CMD exec ircserv $PASSWORD