#!/usr/bin/env bash

cd ServerRoot
node GameServer.js &
 
cd ../GameClient
./GameClient_start.sh