/* Encapsulation of Oracle Stament/ResultSet classes
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
#include <sstream>

#include "OracleStatement.h"
#include "RuntimeException.h"

namespace OpenLogReplicator {

    OracleStatement::OracleStatement(
#ifdef ONLINE_MODEIMPL_OCCI
            Connection **conn, Environment *env
#endif /* ONLINE_MODEIMPL_OCCI */
    )
#ifdef ONLINE_MODEIMPL_OCCI
    :
        conn(conn),
        env(env),
        stmt(nullptr),
        rset(nullptr)
#endif /* ONLINE_MODEIMPL_OCCI */
    {
    }

    void OracleStatement::createStatement(string sql) {
#ifdef ONLINE_MODEIMPL_OCCI
        if (stmt != nullptr) {
            if (rset != nullptr) {
                stmt->closeResultSet(rset);
                rset = nullptr;
            }
            if (*conn != nullptr)
                (*conn)->terminateStatement(stmt);
            stmt = nullptr;
        }

        try {
            stmt = (*conn)->createStatement(sql);
        } catch(SQLException &ex) {
            //close dropped connection
            if (ex.getErrorCode() == 3114) {
                if (conn != nullptr) {
                    env->terminateConnection(*conn);
                    *conn = nullptr;
                }
            }

            RUNTIME_FAIL("Oracle: " << ex.getErrorCode() << ": " << ex.getMessage());
        }
#endif /* ONLINE_MODEIMPL_OCCI */
    }

    void OracleStatement::executeQuery(void) {
#ifdef ONLINE_MODEIMPL_OCCI
        rset = stmt->executeQuery();
#endif /* ONLINE_MODEIMPL_OCCI */
    }

    OracleStatement::~OracleStatement() {
#ifdef ONLINE_MODEIMPL_OCCI
        if (stmt != nullptr) {
            if (rset != nullptr) {
                stmt->closeResultSet(rset);
                rset = nullptr;
            }
            if (*conn != nullptr)
                (*conn)->terminateStatement(stmt);
            stmt = nullptr;
        }
#endif /* ONLINE_MODEIMPL_OCCI */
    }
}
