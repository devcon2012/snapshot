#ifndef SERVER_HTTPS_HPP
#define SERVER_HTTPS_HPP

#include "server_http.hpp"

#ifdef USE_STANDALONE_ASIO
#include <asio/ssl.hpp>
#else
#include <boost/asio/ssl.hpp>
#include <boost/asio/ssl/rfc2818_verification.hpp>
#endif

#include <algorithm>
#include <sstream>
#include <openssl/ssl.h>

#include "../common/BaseCertificate.hpp"

namespace SimpleWeb {
  using HTTPS = asio::ssl::stream<asio::ip::tcp::socket>;

  class client_verification 
    {
  public:
      explicit client_verification() : cert_(NULL) {}
      bool operator()(bool preverified, boost::asio::ssl::verify_context& ctx) ;
      const X509 * client_cert() const { return cert_; } ;
      const std::string client_subject() const { return sSubject; } ;
  protected:
      X509 * cert_ ;
      static std::string sSubject ;
    } ;
  
  template <>
  class Server<HTTPS> : public ServerBase<HTTPS> {
    std::string session_id_context;
    bool set_session_id_context = false;

  public:
    Server(const std::string &cert_file, const std::string &private_key_file, const std::string &verify_file = std::string())
        : ServerBase<HTTPS>::ServerBase(443), context(asio::ssl::context::tlsv12) {
      context.use_certificate_chain_file(cert_file);
      context.use_private_key_file(private_key_file, asio::ssl::context::pem);

      if(verify_file.size() > 0) {
        context.load_verify_file(verify_file);
        context.set_verify_mode(asio::ssl::verify_peer | asio::ssl::verify_fail_if_no_peer_cert | asio::ssl::verify_client_once);
        context.set_verify_callback( verificator ) ;
        set_session_id_context = true;
      }
    }

    const X509 * client_cert() { return verificator.client_cert() ; }
    std::string client_subject() { return verificator.client_subject() ; }

    void start() override {
      if(set_session_id_context) {
        // Creating session_id_context from address:port but reversed due to small SSL_MAX_SSL_SESSION_ID_LENGTH
        session_id_context = std::to_string(config.port) + ':';
        session_id_context.append(config.address.rbegin(), config.address.rend());
        SSL_CTX_set_session_id_context(context.native_handle(), reinterpret_cast<const unsigned char *>(session_id_context.data()),
                                       std::min<std::size_t>(session_id_context.size(), SSL_MAX_SSL_SESSION_ID_LENGTH));
      }
      ServerBase::start();
    }

  protected:
    asio::ssl::context context ;
    client_verification verificator ;

    void accept() override {
      auto connection = create_connection(*io_service, context);

      acceptor->async_accept(connection->socket->lowest_layer(), [this, connection](const error_code &ec) {
        auto lock = connection->handler_runner->continue_lock();
        if(!lock)
          return;

        if(ec != asio::error::operation_aborted)
          this->accept();

        auto session = std::make_shared<Session>(config.max_request_streambuf_size, connection);
        if(!ec) {
          asio::ip::tcp::no_delay option(true);
          error_code ec;
          session->connection->socket->lowest_layer().set_option(option, ec);

          session->connection->set_timeout(config.timeout_request);
          session->connection->socket->async_handshake(asio::ssl::stream_base::server, [this, session](const error_code &ec) {

            session->request->owner = client_subject() ;
            session->owner = client_subject() ;
            session->connection->cancel_timeout();

            auto lock = session->connection->handler_runner->continue_lock();
            if(!lock)
              return;
            if(!ec)
              this->read(session);
            else if(this->on_error)
              this->on_error(session->request, ec);
          });
        }
        else if(this->on_error)
          this->on_error(session->request, ec);
      });
    }
  };
} // namespace SimpleWeb

#endif /* SERVER_HTTPS_HPP */
