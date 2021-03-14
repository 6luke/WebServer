#include "tcp_server.h"

namespace server {
	class HttpServer : public TcpServer {
	public:
		HttpServer();
		virtual ~HttpServer();
		int proc(int client_socket);
		int error();
		int success();
	};
}