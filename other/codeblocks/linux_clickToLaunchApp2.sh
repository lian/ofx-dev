#!/bin/sh

SDIR=`dirname "$0"`
export LD_LIBRARY_PATH=$SDIR/../../../../libs/fmodex/lib/linux:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$SDIR/../../../vendor/ofx-dev/libs/fmodex/lib/linux:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$SDIR/libs/:$SDIR/../../../../libs/libofw/lib:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=$SDIR/../../../vendor/ofx-dev/libs/libofw/lib:$LD_LIBRARY_PATH
echo "exec: $SDIR/applicationName $*"
exec $SDIR/applicationName $*
