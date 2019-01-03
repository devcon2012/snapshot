/* 
 * File:   SnapshotHash.cpp
 * Author: klaus
 * 
 * Created on 3. Januar 2019, 16:18
 * 
 * represent a hash of a file or whatever
 */

#include "SnapshotHash.hpp"
#include "OpenSSLException.hpp"

SnapshotHash::SnapshotHash()
    {
    m_pCTX = EVP_MD_CTX_new();
    }

SnapshotHash::SnapshotHash(const SnapshotHash& orig)
    {
    m_pCTX = EVP_MD_CTX_new();
    }

SnapshotHash::~SnapshotHash()
    {
    if(m_pCTX)
        EVP_MD_CTX_free(m_pCTX) ;
    m_pCTX = NULL ;
    }

std::string SnapshotHash::GetHash(const std::string &sData)
    {
    const EVP_MD * type = EVP_sha1() ;
    
    if ( ! EVP_DigestInit_ex(m_pCTX, type, NULL) )
        {
        throw OpenSSLException("GetHash::Init") ;
        }
    
    if ( ! EVP_DigestUpdate(m_pCTX, sData.c_str(), sData.length() ) )
        {
        throw OpenSSLException("GetHash::DigestUpdate") ;
        }
    
    unsigned int nBytes = EVP_MD_CTX_size( m_pCTX ) ;
              
    unsigned char buf[nBytes] ;
    unsigned int s = nBytes ;
    if ( ! EVP_DigestFinal_ex(m_pCTX, buf, &s) )
        {
        throw OpenSSLException("GetHash::DigestFinal") ;        
        }

    std::string sHash ;
    sHash.assign( (const char *) buf,(size_t) s) ;
    return sHash ;
    }

std::string SnapshotHash::GetHash(std::istream &sData)
    {
    
    return "" ;
    }

