#!/usr/bin/bash

apt install ./antlr-python-tool-linux-amd64.deb -y

wget https://www.antlr.org/download/antlr-4.13.1-complete.jar -O /tmp/antlr-4.13.1-complete.jar
mv /tmp/antlr-4.13.1-complete.jar /usr/local/lib/antlr-4.13.1-complete.jar