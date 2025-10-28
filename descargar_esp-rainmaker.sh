#!/bin/sh

git clone --recursive git@github.com:r126401/esp-rainmaker.git -b improve-schedule
git submodule update --init --recursive
