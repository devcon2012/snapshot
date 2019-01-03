/* 
 * File:   ConnectorException.cpp
 * Author: klaus
 * 
 * Created on 3. Januar 2019, 15:47
 */

#include "ConnectorException.hpp" 
#include <sstream>

ConnectorException::ConnectorException() noexcept
    {
    }

ConnectorException::ConnectorException(const char* sWhat, const char* sOp, const char * sFunction, 
            const char * sFile, int nLine) noexcept :
                    GenericException(sWhat, sFunction, sFile, nLine)
    {
    m_sOp = sOp ;
    }

ConnectorException::ConnectorException(const std::string &sWhat, const std::string &sOp, const char * sFunction, 
            const char * sFile, int nLine) noexcept :
                    GenericException(sWhat.c_str(), sFunction, sFile, nLine)
    {
    m_sOp = sOp ;
    }

ConnectorException::ConnectorException(const ConnectorException& orig) noexcept
    {
    }

ConnectorException::~ConnectorException() noexcept
    {
    }

ConnectorException& ConnectorException::operator= (const ConnectorException &src) noexcept 
    {
    m_sWhat         = src.m_sWhat ;
    m_sOp           = src.m_sOp ;
    m_sFunction     = src.m_sFunction ;
    m_sFile         = src.m_sFile ;
    m_nLine         = src.m_nLine ;
    
    return *this;
    }

const char* ConnectorException::what() const noexcept 
    {
    static std::ostringstream buf ;
    buf.clear() ; buf.str("") ;
    buf << "Connector error for Operation " << m_sOp << ": \n" ;
    buf << m_sWhat << ": " << m_sFunction << "@" << m_sFile << ":" << m_nLine ;
    return buf.str().c_str() ;
    }



