/* Header for OpCode class
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

#include <string>
#include "types.h"

#ifndef OPCODE_H_
#define OPCODE_H_

using namespace std;

namespace OpenLogReplicator {

    class OracleAnalyser;
    class RedoLogRecord;

    class OpCode {
    protected:
        OracleAnalyser *oracleAnalyser;
        RedoLogRecord *redoLogRecord;

        void ktbRedo(uint64_t fieldPos, uint64_t fieldLength);
        void kdoOpCode(uint64_t fieldPos, uint64_t fieldLength);
        void kdoOpCodeIRP(uint64_t fieldPos, uint64_t fieldLength);
        void kdoOpCodeDRP(uint64_t fieldPos, uint64_t fieldLength);
        void kdoOpCodeLKR(uint64_t fieldPos, uint64_t fieldLength);
        void kdoOpCodeURP(uint64_t fieldPos, uint64_t fieldLength);
        void kdoOpCodeORP(uint64_t fieldPos, uint64_t fieldLength);
        void kdoOpCodeCFA(uint64_t fieldPos, uint64_t fieldLength);
        void kdoOpCodeSKL(uint64_t fieldPos, uint64_t fieldLength);
        virtual void kdoOpCodeQM(uint64_t fieldPos, uint64_t fieldLength);

        void ktub(uint64_t fieldPos, uint64_t fieldLength);
        virtual const char* getUndoType(void);
        void dumpCols(uint8_t *data, uint64_t colnum, uint16_t fieldLength, uint8_t isNull);
        void dumpColsVector(uint8_t *data, uint64_t colnum, uint16_t fieldLength);
        void dumpRows(uint8_t *data);
        void dumpVal(uint64_t fieldPos, uint64_t fieldLength, string msg);
        void processFbFlags(uint8_t fb, char *fbStr);
        void suppLog(uint64_t &fieldNum, uint64_t &fieldPos, uint16_t &fieldLength);

    public:
        OpCode(OracleAnalyser *oracleAnalyser, RedoLogRecord *redoLogRecord);
        virtual ~OpCode();

        virtual void process(void);
    };
}

#endif
