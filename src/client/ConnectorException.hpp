/* 
 * File:   ConnectorException.hpp
 * Author: klaus
 *
 * Created on 3. Januar 2019, 15:47
 */

#ifndef CONNECTOREXCEPTION_HPP
#define CONNECTOREXCEPTION_HPP

#include "../common/GenericException.hpp"

class ConnectorException : public GenericException 
    {
    public:
        ConnectorException() noexcept ;
        ConnectorException(const char* sWhat, const char* sWhere, const char * sFunction, 
                    const char * sFile, int nLine) noexcept ;
        ConnectorException(const std::string &sWhat, const std::string &sWhere, const char * sFunction, 
                    const char * sFile, int nLine) noexcept ;
        ConnectorException(const ConnectorException& orig) noexcept ;
        virtual ~ConnectorException() noexcept ;
        ConnectorException& operator= (const ConnectorException &) noexcept ;
        virtual const char* what() const noexcept ;

    protected:
        std::string m_sOp ;
} ;


#endif /* CONNECTOREXCEPTION_HPP */

