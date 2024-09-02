#!/bin/sh

set -e
if [ $1 == "ircserv" ]; then
    password=${PASSWORD}
fi

exec "$@" $password