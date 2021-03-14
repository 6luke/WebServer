#ifndef __TCP_SERVER_H__
#define __TCP_SERVER_H__

#include <memory>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

namespace server {

	struct TcpServerConf {
		enum PF {
			IP4 = PF_INET,
			IP6 = PF_INET6,
			UN = PF_UNIX
		};
		PF protocal_family;	// Э����
		char* ip;	// ip��ַ
		int port;	// �˿ں�
		int backlog;	// ��ȫ����socket����
	};

	class TcpServer {
	public:
		TcpServer(TcpServerConf ptr);

		virtual ~TcpServer();

		int start();

		int proc(int client_socket);

		int stop();

	private:
		int m_socket;

		TcpServerConf m_conf;
	};

}

#endif
