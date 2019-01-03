/* 
 * File:   SnapshotHash.hpp
 * Author: klaus
 *
 * Created on 3. Januar 2019, 16:18
 */

#ifndef SNAPSHOTHASH_HPP
#define SNAPSHOTHASH_HPP

#include <string>
#include <istream>

#include "openssl/evp.h"

class SnapshotHash {
public:
    SnapshotHash() ;
    SnapshotHash(const SnapshotHash& orig) ;
    virtual ~SnapshotHash() ;
    
    std::string GetHash(const std::string &sData ) ;
    std::string GetHash(std::istream &sData ) ;
protected:
    EVP_MD_CTX     * m_pCTX ;
};

#endif /* SNAPSHOTHASH_HPP */

