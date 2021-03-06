/* Base class for source and target thread
   Copyright (C) 2018-2020 Adam Leszczynski (aleszczynski@bersler.com)

This file is part of OpenLogReplicator.

OpenLogReplicator is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License as published
by the Free Software Foundation; either version 3, or (at your option)
any later version.

OpenLogReplicator is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
Public License for more details.

You should have received a copy of the GNU General Public License
along with OpenLogReplicator; see the file LICENSE;  If not see
<http://www.gnu.org/licenses/>.  */

#include <iostream>

#include "OracleColumn.h"
#include "OracleObject.h"
#include "RedoLogRecord.h"
#include "Thread.h"

using namespace std;

namespace OpenLogReplicator {

    Thread::Thread(const string alias) :
        shutdown(false),
        started(false),
        pthread(0),
        alias(alias) {
    }

    Thread::~Thread() {
    }

    void *Thread::runStatic(void *context){
        ((Thread *) context)->started = true;
        void *ret = ((Thread *) context)->run();
        return ret;
    }

    void Thread::stop(void) {
        shutdown = true;
    }
}
