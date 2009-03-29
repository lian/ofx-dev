#!/bin/sh

#should we run the app based on build
if [ "$2" = "true" ]
then
cd $4/bin
export LD_LIBRARY_PATH=$(pwd)/libs/
./$1 
fi

#should we launch nautilus to this directory on build?
if [ "$3" = "true" ]
then
cd $4
nautilus $(pwd)/bin/
fi

