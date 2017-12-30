/* 
 * File:   SnapshotData.cpp
 * Author: klaus
 * 
 * Created on 25. Dezember 2017, 21:07
 */

#include "SnapshotData.hpp"
#include "../common/SnapshotException.hpp"

/// Create a SnapshotData Object containing configuration data
/// and file system state

SnapshotData::SnapshotData()
    {
    }

SnapshotData::SnapshotData(const SnapshotData& orig)
    {
    }

SnapshotData::~SnapshotData()
    {
    m_xServers.clear();
    }

/// Add a server we can connect to
void SnapshotData::AddServer(const char * server)
    {
    m_xServers.push_back(server);
    }

/// Get server numbered n (default 0)
std::string SnapshotData::GetServer(int n /* = 0 */)
    {
    if ( ( n>=0 ) && (n<m_xServers.size()) )
        return m_xServers[n];
    
    }

/// How many servers?    
size_t SnapshotData::GetServerCount()
    {
    return m_xServers.size() ;
    }
