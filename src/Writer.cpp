/* Base class for target writer
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

#include "OutputBuffer.h"
#include "OracleAnalyser.h"
#include "OracleColumn.h"
#include "OracleObject.h"
#include "RedoLogRecord.h"
#include "Writer.h"

using namespace std;

namespace OpenLogReplicator {

    Writer::Writer(const string alias, OracleAnalyser *oracleAnalyser, uint64_t stream, uint64_t singleDml,
            uint64_t showColumns, uint64_t test, uint64_t timestampFormat, uint64_t charFormat, uint64_t maxMessageMb) :
        Thread(alias),
        outputBuffer(oracleAnalyser->outputBuffer),
        oracleAnalyser(oracleAnalyser),
        stream(stream),
        singleDml(singleDml),
        showColumns(showColumns),
        test(test),
        timestampFormat(timestampFormat),
        charFormat(charFormat),
        maxMessageMb(maxMessageMb) {
    }

    Writer::~Writer() {
    }
}
