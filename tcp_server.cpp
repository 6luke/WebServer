#include "tcp_server.h"

namespace server{

	TcpServer::TcpServer(TcpServerConf conf) {
		m_conf = conf;
		m_socket = socket(m_conf.protocal_family, SOCK_STREAM, 0);

		switch (m_conf.protocal_family)
		{
		case TcpServerConf::IP4:
			sockaddr_in sai; 
			sai.sin_family = m_conf.protocal_family;
			sai.sin_port = m_conf.port;
			int inet_pton_result = inet_pton(m_conf.protocal_family, m_conf.ip, &(sai.sin_addr.s_addr));
			int bind_result = bind(m_socket, reinterpret_cast<sockaddr*>(&sai), sizeof(sai));
			break;
		case TcpServerConf::IP6:
			sockaddr_in6 sai6;
			sai6.sin6_family = m_conf.protocal_family;
			sai6.sin6_port = m_conf.port;
			sai6.sin6_flowinfo = 0;
			int inet_pton_result6 = inet_pton(m_conf.protocal_family, m_conf.ip, sai6.sin6_addr.s6_addr);
			int bind_result6 = bind(m_socket, reinterpret_cast<sockaddr*>(&sai6), sizeof(sai6));
			break;
		case TcpServerConf::UN:
			break;
		default:
			break;
		}

	}

	int TcpServer::start() {
		int listen_result = listen(m_socket, m_conf.backlog);

		sockaddr* client_addr;
		socklen_t* clinet_addr_len;

		while (true) {
			int client_socket = accept(m_socket, client_addr, clinet_addr_len);
			if (client_socket > 0) {
				proc(client_socket);
				close(client_socket);
			}
		}
	}

}