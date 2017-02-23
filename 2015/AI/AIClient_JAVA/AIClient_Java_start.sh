#!/usr/bin/env bash
cd src
javac -d ../class aiclient/Client.java
cd ../class
java aiclient/Client