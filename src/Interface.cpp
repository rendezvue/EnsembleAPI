#include "Interface.h"
#include "ErrorType.h"

//#define ENSEMBLE_JAVA_API
CInterface::CInterface(void) :	
	m_cls_eth_client(NULL)
	, m_p_send_data(NULL)
	, m_i_send_data_size(0)
	, m_ip("")
	, m_port(0)
{
	m_i_send_data_size = SEND_DATA_SIZE;
	m_p_send_data = new unsigned char[m_i_send_data_size] ;
}

CInterface::~CInterface(void)
{
	if( m_p_send_data)
	{
		delete m_p_send_data ;
		m_p_send_data = NULL ;
	}

	if(m_cls_eth_client)
	{
		m_cls_eth_client->Close();

		delete m_cls_eth_client;
		m_cls_eth_client = NULL;
	}
}

int CInterface::CreateSocket(const char* ip, const unsigned int port)
{
	m_ip = ip;
	m_port = port ;

	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client)
	{
		//m_cls_eth_client->Close();

		//delete m_cls_eth_client;
		//m_cls_eth_client = NULL;
        return ENSEMBLE_ERROR_ALREADY_CONNECT;
	}

    qDebug("Create Socket 1") ;

	m_cls_eth_client = new CEthernetClient();

	int ret;

	//int sec = 0;

	/*
	while(1){
		ret = m_cls_eth_client->Open(ip, port);
		if(ret == 0)
			break;
		else
		{
			boost::this_thread::sleep(boost::posix_time::millisec(1000));  //1 msec sleep
			sec++;
			if(sec >= 60)
				break;
			continue;
		}
	}
	//return m_cls_eth_client->Open(ip, port);
	*/

    qDebug("Create Socket 2") ;
    ret = m_cls_eth_client->Open(m_ip.c_str(), m_port);

    qDebug("Create Socket 3 ( ret=%d )", ret) ;

	if (ret != 0)
	{
		delete m_cls_eth_client;
		m_cls_eth_client = NULL;
	}

	return ret;
}

void CInterface::DeleteSocket()
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return;
	}

	m_cls_eth_client->Close();
    delete(m_cls_eth_client);
    m_cls_eth_client = NULL;
}
