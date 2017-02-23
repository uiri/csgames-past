#!/usr/bin/env bash

export PYTHONPATH=${PWD}/src

cd ./test
python3 -m unittest discover
