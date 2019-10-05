#include "InterfaceControl.h"
#include "ErrorType.h"

CInterfaceControl::CInterfaceControl(void)
{
    //initial : make calss instance
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;
}

CInterfaceControl::~CInterfaceControl(void)
{
}

int CInterfaceControl::IsOnline(void)
{
    boost::unique_lock<boost::mutex> scoped_lock(mutex);

    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return ENSEMBLE_ERROR_INVALID_MEMORY;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    unsigned int command = ENSEMBLE_COMMAND_NETWORK_IS_ONLINE;

    int ret = p_cls_ethernet_control_data->Send(p_socket, command, std::string(), NULL) ;
    std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

    if( vec_receive_data.size() == 1 )
    {
        ret = vec_receive_data[0] ;
    }

    return ret ;
}


int CInterfaceControl::Get_Run_Option(const std::string id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return ENSEMBLE_ERROR_INVALID_MEMORY;
	}

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

	unsigned int command = ENSEMBLE_TASK_GET_RUN_OPTION;

    int ret = p_cls_ethernet_control_data->Send(p_socket, command, id, NULL) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	if( vec_receive_data.size() == 1 )
	{
		ret = vec_receive_data[0] ;
	}

	return ret ;
}

int CInterfaceControl::Get_View_Option(const std::string id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return ENSEMBLE_ERROR_INVALID_MEMORY;
	}

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

	//printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_TASK_GET_VIEW_OPTION;

    int ret = p_cls_ethernet_control_data->Send(p_socket, command, id, NULL) ;
	std::vector<float> vec_receive_data; 
    ret += p_cls_ethernet_control_data->Receive(p_socket, command,&vec_receive_data) ;

	if( vec_receive_data.size() == 1 )
	{
		ret = vec_receive_data[0] ;
	}

	return ret ;
}

int CInterfaceControl::Base_Set_Run_Option(const std::string id, const bool run)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return ENSEMBLE_ERROR_INVALID_MEMORY;
	}

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

	unsigned int command = ENSEMBLE_TASK_SET_RUN_OPTION;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(run) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	return ret ;
}

int CInterfaceControl::Base_Set_View_Option(const std::string id, const bool view) 
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return ENSEMBLE_ERROR_INVALID_MEMORY;
	}

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    unsigned int command = ENSEMBLE_TASK_SET_VIEW_OPTION;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(view) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	return ret ;
}

int CInterfaceControl::Task_Save(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return ENSEMBLE_ERROR_INVALID_MEMORY;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_TASK_SAVE;

    int ret = p_cls_ethernet_control_data->Send(p_socket, command, std::string(), NULL) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	return ret ;
}

int CInterfaceControl::Task_Load(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return ENSEMBLE_ERROR_INVALID_MEMORY;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    unsigned int command = ENSEMBLE_TASK_LOAD;

    int ret = p_cls_ethernet_control_data->Send(p_socket, command, std::string(), NULL) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	return ret ;
}

int CInterfaceControl::Project_Add_New(const std::string name)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return ENSEMBLE_ERROR_INVALID_MEMORY;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    std::vector<float> vec_send_data ;
    if( !name.empty() )
    {
        int data_size = name.size() ;
        for( int i=0 ; i<data_size ; i++ )
        {
            float data = name[i] ;
            vec_send_data.push_back(data) ;
        }
    }

    unsigned int command = ENSEMBLE_PRJ_NEW;

    int ret = p_cls_ethernet_control_data->Send(p_socket, command, std::string(), &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	return ret ;
}

int CInterfaceControl::Project_Del(const std::string id)
{
    boost::unique_lock<boost::mutex> scoped_lock(mutex);

    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return ENSEMBLE_ERROR_INVALID_MEMORY;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    unsigned int command = ENSEMBLE_PRJ_DEL;

    int ret = p_cls_ethernet_control_data->Send(p_socket, command, id, NULL) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	return ret ;
}


int CInterfaceControl::Job_Add_New(const std::string project_id, const int type, const std::string name)
{
    boost::unique_lock<boost::mutex> scoped_lock(mutex);

    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return ENSEMBLE_ERROR_INVALID_MEMORY;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    unsigned int command = ENSEMBLE_JOB_NEW;

    std::vector<float> vec_send_data ;
	vec_send_data.push_back(type) ;
	if( !name.empty() )
	{
		int data_size = name.size() ;
		for( int i=0 ; i<data_size ; i++ )
		{
			float data = name[i] ;
            vec_send_data.push_back(data) ;
		}
	}
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, project_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	return ret ;
}

std::string CInterfaceControl::Job_Get_TypeName(const int job_type)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	std::string str_ret ;
	
    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return str_ret;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return str_ret;
    }

    unsigned int command = ENSEMBLE_JOB_GET_TYPE_NAME;
		
	std::vector<float> vec_send_data ;
	vec_send_data.push_back(job_type) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, std::string(), &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	int receive_size = vec_receive_data.size() ;
	if( receive_size > 0 )
	{
		str_ret.resize(receive_size);

		for( int i=0 ; i<receive_size ; i++ )
		{
			str_ret[i] = (char)vec_receive_data[i] ;
		}
	}
    return str_ret;
}


int CInterfaceControl::DelJob(const std::string id)
{
    boost::unique_lock<boost::mutex> scoped_lock(mutex);

    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return ENSEMBLE_ERROR_INVALID_MEMORY;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_JOB_DEL;

    std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

    return ret;
}

std::string CInterfaceControl::JobGetName(const std::string id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	std::string str_ret ;
	
	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return str_ret;
	}

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return str_ret;
    }
	//printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_JOB_GET_NAME;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	int receive_size = vec_receive_data.size() ;
	if( receive_size > 0 )
	{
		str_ret.resize(receive_size);

		for( int i=0 ; i<receive_size ; i++ )
		{
			str_ret[i] = (char)vec_receive_data[i] ;
		}
	}

    return str_ret;
}

int CInterfaceControl::JobChangeName(const std::string id, const std::string name)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return ENSEMBLE_ERROR_INVALID_MEMORY;
	}

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

	//printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_JOB_SET_NAME;

	std::vector<float> vec_send_data ;
	if( !name.empty() )
	{
		int data_size = name.size() ;
		for( int i=0 ; i<data_size ; i++ )
		{
			float data = name[i] ;
            vec_send_data.push_back(data) ;
		}
	}
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;
	
	return ret;
}

int CInterfaceControl::JobGetImage(const std::string id, const int type_option, int& width, int& height, unsigned char** out_data)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return ENSEMBLE_ERROR_INVALID_MEMORY;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    unsigned int command = ENSEMBLE_JOB_GET_IMAGE;

	qDebug("JobGetImage : type_option = %d", (unsigned int)type_option) ;
	qDebug("JobGetImage : width = %d", width) ;
	qDebug("JobGetImage : height = %d", height) ;
	
	std::vector<float> vec_send_data ;
    vec_send_data.push_back(type_option) ;
	vec_send_data.push_back(width) ;
	vec_send_data.push_back(height) ;
	
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->ReceiveImage(p_socket, command, width, height, out_data) ;
		
    return ret;
}

int CInterfaceControl::OptionGetImage(const std::string option_id, const int type_option, int& width, int& height, unsigned char** out_data)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return ENSEMBLE_ERROR_INVALID_MEMORY;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    unsigned int command = ENSEMBLE_TOOL_OPTION_GET_IMAGE;

	std::vector<float> vec_send_data ;
    vec_send_data.push_back(type_option) ;
	vec_send_data.push_back(width) ;
	vec_send_data.push_back(height) ;
	
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, option_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->ReceiveImage(p_socket, command, width, height, out_data) ;
	
    return ret;
}

int CInterfaceControl::Tool_Option_InspectColor_Histogram_GetImage(const std::string option_id, const int color_num, const int type_option, int& width, int& height, unsigned char** out_data)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return ENSEMBLE_ERROR_INVALID_MEMORY;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    unsigned int command = ENSEMBLE_TOOL_OPTION_INSPECT_COLOR_GET_HISTOGRAM_IMAGE;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(color_num) ;
    vec_send_data.push_back(type_option) ;
	vec_send_data.push_back(width) ;
	vec_send_data.push_back(height) ;
	
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, option_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->ReceiveImage(p_socket, command, width, height, out_data) ;
	
    return ret;
}

int CInterfaceControl::Tool_Option_InspectColor_Set_Histogram_UseElement(const std::string option_id, const int color_elem)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return ENSEMBLE_ERROR_INVALID_MEMORY;
	}

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    unsigned int command = ENSEMBLE_TOOL_OPTION_INSPECT_COLOR_SET_HISTOGRAM_USE_ELEMENT;

	std::vector<float> vec_send_data ;
    vec_send_data.push_back(color_elem) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, option_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	return ret;
}

int CInterfaceControl::Tool_Option_InspectColor_Get_Histogram_UseElement(const std::string option_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return ENSEMBLE_ERROR_INVALID_MEMORY;
	}

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

	//printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_TOOL_OPTION_INSPECT_COLOR_GET_HISTOGRAM_USE_ELEMENT;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, option_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	int value = 0 ;
	if( vec_receive_data.size()  > 0 ) value = vec_receive_data[0] ;
	
	return value ;
}

int CInterfaceControl::Tool_Option_InspectColor_Set_Histogram_Range(const std::string option_id, const int color_elem, const float min, const float max)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return ENSEMBLE_ERROR_INVALID_MEMORY;
	}

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    unsigned int command = ENSEMBLE_TOOL_OPTION_INSPECT_COLOR_SET_HISTOGRAM_RANGE;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(color_elem) ;
    vec_send_data.push_back(min) ;
	vec_send_data.push_back(max) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, option_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	return ret;
}

int CInterfaceControl::Tool_Option_InspectColor_Get_Histogram_Range(const std::string option_id, const int color_elem, int* out_min, int* out_max)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return ENSEMBLE_ERROR_INVALID_MEMORY;
	}

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

	//printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_TOOL_OPTION_INSPECT_COLOR_GET_HISTOGRAM_RANGE;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(color_elem) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, option_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;
	if( vec_receive_data.size() == 2 )
	{
		if( out_min != NULL ) (*out_min) = vec_receive_data[0] ;
		if( out_max != NULL ) (*out_max) = vec_receive_data[1] ;
	}
	
	return ret ;
}

int CInterfaceControl::Tool_Option_InspectColor_Get_Base_Pixel_Count(const std::string option_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return ENSEMBLE_ERROR_INVALID_MEMORY;
	}

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

	//printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_TOOL_OPTION_INSPECT_COLOR_GET_BASE_PIXEL_COUNT;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, option_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	int base_count = -1 ;
	if( vec_receive_data.size() == 1 )
	{
		base_count = vec_receive_data[0] ;
	}

	return base_count ;
}

int CInterfaceControl::Tool_Option_InspectColor_Get_Tolerance(const std::string option_id, int* out_min, int* out_max)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return ENSEMBLE_ERROR_INVALID_MEMORY;
	}

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

	//printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_TOOL_OPTION_INSPECT_COLOR_GET_TOLERANCE;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, option_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;
	if( vec_receive_data.size() == 2 )
	{
		if( out_min != NULL ) (*out_min) = vec_receive_data[0] ;
		if( out_max != NULL ) (*out_max) = vec_receive_data[1] ;
	}

	return ret ;
}

int CInterfaceControl::Tool_Option_InspectColor_Set_Tolerance(const std::string option_id, const int min, const int max)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return ENSEMBLE_ERROR_INVALID_MEMORY;
	}

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    unsigned int command = ENSEMBLE_TOOL_OPTION_INSPECT_COLOR_SET_TOLERANCE;
	
	std::vector<float> vec_send_data ;
	vec_send_data.push_back(min) ;
	vec_send_data.push_back(max) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, option_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	return ret;
}

int CInterfaceControl::Tool_Option_InspectDistance_Get_Tolerance(const std::string option_id, float* out_min, float* out_max)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return ENSEMBLE_ERROR_INVALID_MEMORY;
	}

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

	//printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_TOOL_OPTION_INSPECT_DISTANCE_GET_TOLERANCE;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, option_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;
	if( vec_receive_data.size() == 2 )
	{
		if( out_min != NULL ) (*out_min) = vec_receive_data[0] ;
		if( out_max != NULL ) (*out_max) = vec_receive_data[1] ;
	}

	return ret ;
}

int CInterfaceControl::Tool_Option_InspectDistance_Set_Tolerance(const std::string option_id, const float min, const float max)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return ENSEMBLE_ERROR_INVALID_MEMORY;
	}

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    unsigned int command = ENSEMBLE_TOOL_OPTION_INSPECT_DISTANCE_SET_TOLERANCE;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(min) ;
	vec_send_data.push_back(max) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, option_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	return ret;
}	

std::string CInterfaceControl::Tool_Option_InspectDistance_Get_ID_Info_Base(const std::string option_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	std::string str_ret ;
	
	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return str_ret;
	}

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return str_ret;
    }

    unsigned int command = ENSEMBLE_TOOL_OPTION_INSPECT_DISTANCE_GET_ID_INFO_BASE;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, option_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;
	
	int receive_size = vec_receive_data.size() ;
	if( receive_size > 0 )
	{
		str_ret.resize(receive_size);

		for( int i=0 ; i<receive_size ; i++ )
		{
			str_ret[i] = (char)vec_receive_data[i] ;
		}
	}

    return str_ret;
}

std::string CInterfaceControl::Tool_Option_InspectDistance_Get_ID_Info_Target(const std::string option_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	std::string str_ret ;
	
	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return str_ret;
	}

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return str_ret;
    }

    unsigned int command = ENSEMBLE_TOOL_OPTION_INSPECT_DISTANCE_GET_ID_INFO_TARGET;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, option_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;
	
	int receive_size = vec_receive_data.size() ;
	if( receive_size > 0 )
	{
		str_ret.resize(receive_size);

		for( int i=0 ; i<receive_size ; i++ )
		{
			str_ret[i] = (char)vec_receive_data[i] ;
		}
	}

    return str_ret;
}

int CInterfaceControl::Tool_Option_InspectAngle_Get_Tolerance(const std::string option_id, float* out_min, float* out_max)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return ENSEMBLE_ERROR_INVALID_MEMORY;
	}

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

	//printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_TOOL_OPTION_INSPECT_ANGLE_GET_TOLERANCE;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, option_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;
	if( vec_receive_data.size() == 2 )
	{
		if( out_min != NULL ) (*out_min) = vec_receive_data[0] ;
		if( out_max != NULL ) (*out_max) = vec_receive_data[1] ;
	}
	
	return ret ;
}

int CInterfaceControl::Tool_Option_InspectAngle_Set_Tolerance(const std::string option_id, const float min, const float max)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return ENSEMBLE_ERROR_INVALID_MEMORY;
	}

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }


    unsigned int command = ENSEMBLE_TOOL_OPTION_INSPECT_ANGLE_SET_TOLERANCE;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(min) ;
	vec_send_data.push_back(max) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, option_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	return ret;
}	

std::string CInterfaceControl::Tool_Option_InspectAngle_Get_ID_Info_Base(const std::string option_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	std::string str_ret ;
	
	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return str_ret;
	}

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return str_ret;
    }
	//printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_TOOL_OPTION_INSPECT_ANGLE_GET_ID_INFO_BASE;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, option_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;
	
	int receive_size = vec_receive_data.size() ;
	if( receive_size > 0 )
	{
		str_ret.resize(receive_size);

		for( int i=0 ; i<receive_size ; i++ )
		{
			str_ret[i] = (char)vec_receive_data[i] ;
		}
	}

    return str_ret;
}

std::string CInterfaceControl::Tool_Option_InspectAngle_Get_ID_Info_Target(const std::string option_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	std::string str_ret ;
	
	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return str_ret;
	}

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return str_ret;
    }

	//printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_TOOL_OPTION_INSPECT_ANGLE_GET_ID_INFO_TARGET;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, option_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;
	
	int receive_size = vec_receive_data.size() ;
	if( receive_size > 0 )
	{
		str_ret.resize(receive_size);

		for( int i=0 ; i<receive_size ; i++ )
		{
			str_ret[i] = (char)vec_receive_data[i] ;
		}
	}

    return str_ret;
}

float CInterfaceControl::Tool_Circle_Get_CalcDiameter(const std::string tool_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return ENSEMBLE_ERROR_INVALID_MEMORY;
	}

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

	//printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_TOOL_CIRCLE_GET_CALC_DIAMETER;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, tool_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	float ret_value = -1 ;
	if( vec_receive_data.size() == 1 ) ret_value = vec_receive_data[0] ;
	
	return ret_value ;
}

int CInterfaceControl::Tool_Option_InspectDiameter_Get_Tolerance(const std::string option_id, float* out_min, float* out_max)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return ENSEMBLE_ERROR_INVALID_MEMORY;
	}

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

	//printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_TOOL_OPTION_INSPECT_DIAMETER_GET_TOLERANCE;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, option_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;
	if( vec_receive_data.size() == 2 )
	{
		if( out_min != NULL ) (*out_min) = vec_receive_data[0] ;
		if( out_max != NULL ) (*out_max) = vec_receive_data[1] ;
	}
	return ret ;
}

int CInterfaceControl::Tool_Option_InspectDiameter_Set_Tolerance(const std::string option_id, const float min, const float max)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return ENSEMBLE_ERROR_INVALID_MEMORY;
	}

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    unsigned int command = ENSEMBLE_TOOL_OPTION_INSPECT_DIAMETER_SET_TOLERANCE;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(min) ;
	vec_send_data.push_back(max) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, option_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	return ret;
}

int CInterfaceControl::ToolGetImage(const std::string tool_id, const int type_option, int& width, int& height, unsigned char** out_data)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return ENSEMBLE_ERROR_INVALID_MEMORY;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    unsigned int command = ENSEMBLE_TOOL_GET_IMAGE;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(type_option) ;
	vec_send_data.push_back(width) ;
	vec_send_data.push_back(height) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, tool_id, &vec_send_data) ;
    ret += p_cls_ethernet_control_data->ReceiveImage(p_socket, command, width, height, out_data) ;
	
    return ret;
}

int CInterfaceControl::JobGetObjectImage(const std::string id, const int type_option, int& width, int& height, unsigned char** out_data)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return ENSEMBLE_ERROR_INVALID_MEMORY;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    unsigned int command = ENSEMBLE_JOB_GET_OBJECT_IMAGE;
		
	std::vector<float> vec_send_data ;
	vec_send_data.push_back(type_option) ;
	vec_send_data.push_back(width) ;
	vec_send_data.push_back(height) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, id, &vec_send_data) ;
    ret += p_cls_ethernet_control_data->ReceiveImage(p_socket, command, width, height, out_data) ;
	
    return ret;
}

int CInterfaceControl::ToolGetObjectImage(const std::string tool_id, const int type_option, int& width, int& height, unsigned char** out_data)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return ENSEMBLE_ERROR_INVALID_MEMORY;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    unsigned int command = ENSEMBLE_TOOL_GET_OBJECT_IMAGE;
		
	std::vector<float> vec_send_data ;
	vec_send_data.push_back(type_option) ;
	vec_send_data.push_back(width) ;
	vec_send_data.push_back(height) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, tool_id, &vec_send_data) ;
    ret += p_cls_ethernet_control_data->ReceiveImage(p_socket, command, width, height, out_data) ;
	
    return ret;
}


int CInterfaceControl::JobSetImage(const std::string id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return ENSEMBLE_ERROR_INVALID_MEMORY;
	}

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

	//printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_JOB_SET_IMAGE;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	return ret;

}

int CInterfaceControl::JobSetDetectArea(const std::string id, const float x, const float y, const float width, const float height)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return ENSEMBLE_ERROR_INVALID_MEMORY;
	}

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

	//printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_JOB_SET_DETECT_AREA;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(x) ;
	vec_send_data.push_back(y) ;
	vec_send_data.push_back(width) ;
	vec_send_data.push_back(height) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	return ret;
}

int CInterfaceControl::JobSetZoom(const std::string id, const float x, const float y, const float width, const float height)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return ENSEMBLE_ERROR_INVALID_MEMORY;
	}

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

	//printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_JOB_SET_ZOOM;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(x) ;
	vec_send_data.push_back(y) ;
	vec_send_data.push_back(width) ;
	vec_send_data.push_back(height) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	return ret;
}

int CInterfaceControl::JobSelectObject(const std::string id, const float x, const float y, const float width, const float height)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return ENSEMBLE_ERROR_INVALID_MEMORY;
	}

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

	//printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_JOB_SELECT_OBJECT;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(x) ;
	vec_send_data.push_back(y) ;
	vec_send_data.push_back(width) ;
	vec_send_data.push_back(height) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	return ret;
}

int CInterfaceControl::ToolSelectObject(const std::string tool_id, const float left_top_x, const float left_top_y, const float right_top_x, const float right_top_y, const float right_bottom_x, const float right_bottom_y, const float left_bottom_x, const float left_bottom_y, const int margin) 
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return ENSEMBLE_ERROR_INVALID_MEMORY;
	}

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

	//printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_TOOL_SELECT_ROTATED_OBJECT;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(left_top_x) ;
	vec_send_data.push_back(left_top_y) ;
	vec_send_data.push_back(right_top_x) ;
	vec_send_data.push_back(right_top_y) ;
	vec_send_data.push_back(right_bottom_x) ;
	vec_send_data.push_back(right_bottom_y) ;
	vec_send_data.push_back(left_bottom_x) ;
	vec_send_data.push_back(left_bottom_y) ;
	vec_send_data.push_back(margin) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, tool_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;
	
	return ret;
}

int CInterfaceControl::ToolSelectObject(const std::string tool_id, const float x, const float y, const float width, const float height, const int margin)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return ENSEMBLE_ERROR_INVALID_MEMORY;
	}

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

	//printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_TOOL_SELECT_OBJECT;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(x) ;
	vec_send_data.push_back(y) ;
	vec_send_data.push_back(width) ;
	vec_send_data.push_back(height) ;
	vec_send_data.push_back(margin) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, tool_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	return ret;
}

int CInterfaceControl::JobSetDetectOption(const std::string id, const int option, const float value)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return ENSEMBLE_ERROR_INVALID_MEMORY;
	}

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

	//printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_JOB_SET_DETECT_OPTION;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(option) ;
	vec_send_data.push_back(value) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	return ret;
}

float CInterfaceControl::JobGetDetectOption(const std::string id, const int option)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return ENSEMBLE_ERROR_INVALID_MEMORY;
	}

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }
	//printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_JOB_GET_DETECT_OPTION;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(option) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	float value = 0.0 ;
	if( vec_receive_data.size() == 1 )
	{
		value = vec_receive_data[0] ;
	}

	return value ;
}


int CInterfaceControl::JobResetObject(const std::string id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return ENSEMBLE_ERROR_INVALID_MEMORY;
	}

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

	//printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_JOB_RESET_OBJECT;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	return ret;
}

int CInterfaceControl::JobSetMaskArea(const std::string id, float x, float y, float w, float h, bool inverse)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
		
	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return ENSEMBLE_ERROR_INVALID_MEMORY;
	}

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

	//printf("id - %d\n", id);

	unsigned int command = ENSEMBLE_JOB_SET_MASK;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(x) ;
	vec_send_data.push_back(y) ;
	vec_send_data.push_back(w) ;
	vec_send_data.push_back(h) ;
	vec_send_data.push_back(inverse) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	return ret;

}

int CInterfaceControl::JobUndoMaskArea(const std::string id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
		
	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return ENSEMBLE_ERROR_INVALID_MEMORY;
	}

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }
	//printf("id - %d\n", id);

	unsigned int command = ENSEMBLE_JOB_UNDO_MASK;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	return ret;
}

int CInterfaceControl::JobDelMaskArea(const std::string id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
		
	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return ENSEMBLE_ERROR_INVALID_MEMORY;
	}

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }
	//printf("id - %d\n", id);

	unsigned int command = ENSEMBLE_JOB_DEL_MASK;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	return ret;
}

int CInterfaceControl::JobGetFeatureLevel(const std::string id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
		
	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return ENSEMBLE_ERROR_INVALID_MEMORY;
	}

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }
	//printf("id - %d\n", id);

	unsigned int command = ENSEMBLE_JOB_GET_FEATURE_LEVEL;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	int level = -1 ;
	if( vec_receive_data.size() == 1 )
	{
		level = vec_receive_data[0] ;
	}

	ret = level ;
	
    return ret;
}

int CInterfaceControl::JobSetFeatureLevel(const std::string id, const int level)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
		
	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return ENSEMBLE_ERROR_INVALID_MEMORY;
	}

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }
	//printf("id - %d\n", id);

	unsigned int command = ENSEMBLE_JOB_SET_FEATURE_LEVEL;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(level) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	return ret;
}
	
int CInterfaceControl::DelTool(const std::string tool_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return ENSEMBLE_ERROR_INVALID_MEMORY;
	}

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }
	//printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_TOOL_DEL;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, tool_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	return ret;

}

std::string CInterfaceControl::ToolGetName(const std::string tool_id) 
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	std::string str_ret ;
	
	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return str_ret;
	}

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return str_ret;
    }

	//printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_TOOL_GET_NAME;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, tool_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	int receive_size = vec_receive_data.size() ;
	if( receive_size > 0 )
	{
		str_ret.resize(receive_size);

		for( int i=0 ; i<receive_size ; i++ )
		{
			str_ret[i] = (char)vec_receive_data[i] ;
		}
	}
	
    return str_ret;
}

int CInterfaceControl::ToolSetName(const std::string tool_id, const std::string name)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return ENSEMBLE_ERROR_INVALID_MEMORY;
	}

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

	//printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_TOOL_SET_NAME;

	std::vector<float> vec_send_data ;
	if( !name.empty() )
    {
        int data_size = name.size() ;
        for( int i=0 ; i<data_size ; i++ )
        {
            float data = name[i] ;
            vec_send_data.push_back(data) ;
        }
    }
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, tool_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	return ret;
}

int CInterfaceControl::ToolGetFeatureLevel(const std::string tool_id) 
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
		
	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return ENSEMBLE_ERROR_INVALID_MEMORY;
	}

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

	//printf("id - %d\n", id);

	unsigned int command = ENSEMBLE_TOOL_GET_FEATURE_LEVEL;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, tool_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	int level = -1 ;
	if( vec_receive_data.size() == 1 )
	{
		level = vec_receive_data[0] ;
	}

	ret = level ;
	
    return ret;
}

int CInterfaceControl::ToolSetFeatureLevel(const std::string tool_id, const int level) 
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
		
	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return ENSEMBLE_ERROR_INVALID_MEMORY;
	}

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

	//printf("id - %d\n", id);

	unsigned int command = ENSEMBLE_TOOL_SET_FEATURE_LEVEL;

	
	std::vector<float> vec_send_data ;
	vec_send_data.push_back(level) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, tool_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	return ret;
}

int CInterfaceControl::Tool_Option_Crack_GetInspectLevel(const std::string option_id) 
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
		
	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return ENSEMBLE_ERROR_INVALID_MEMORY;
	}

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

	//printf("id - %d\n", id);

	unsigned int command = ENSEMBLE_TOOL_OPTION_INSPECT_CRACK_GET_INSPECT_LEVEL;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, option_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	int level = -1 ;
	if( vec_receive_data.size() == 1 )
	{
		level = vec_receive_data[0] ;
	}

	ret = level ;
	
    return ret;
}

int CInterfaceControl::Tool_Option_Crack_SetInspectLevel(const std::string option_id, const int level) 
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
		
	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return ENSEMBLE_ERROR_INVALID_MEMORY;
	}

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }
	//printf("id - %d\n", id);

	unsigned int command = ENSEMBLE_TOOL_OPTION_INSPECT_CRACK_SET_INSPECT_LEVEL;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(level) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, option_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	return ret;
}

int CInterfaceControl::ToolSetDetectOption(const std::string tool_id, const int option, const float value)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return ENSEMBLE_ERROR_INVALID_MEMORY;
	}

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }
	//printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_TOOL_SET_DETECT_OPTION;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(option) ;
	vec_send_data.push_back(value) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, tool_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;
	
	return ret;
}

float CInterfaceControl::ToolGetDetectOption(const std::string tool_id, const int option)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return ENSEMBLE_ERROR_INVALID_MEMORY;
	}

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

	//printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_TOOL_GET_DETECT_OPTION;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(option) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, tool_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;
	
	float value = 0.0 ;
	if( vec_receive_data.size() == 1 )
	{
		value = vec_receive_data[0] ;
	}

	return value ;
}

std::string CInterfaceControl::ToolGetOptionList(const std::string tool_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	std::string str_ret ;
	
    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return str_ret;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return str_ret;
    }

    unsigned int command = ENSEMBLE_TOOL_OPTION_GET_LIST;
		
	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, tool_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	int receive_size = vec_receive_data.size() ;
	if( receive_size > 0 )
	{
		str_ret.resize(receive_size);

		for( int i=0 ; i<receive_size ; i++ )
		{
			str_ret[i] = (char)vec_receive_data[i] ;
		}
	}
	
    return str_ret;
}

int CInterfaceControl::ToolGetOptionCount(const int tool_type)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	std::string str_ret ;
	
    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return ENSEMBLE_ERROR_INVALID_MEMORY;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    unsigned int command = ENSEMBLE_TOOL_OPTION_GET_LIST_COUNT;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(tool_type) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, std::string(), &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	float value = 0.0 ;
	if( vec_receive_data.size() ==1 )
	{
		value = vec_receive_data[0] ;
	}

	return value ;
}

std::string CInterfaceControl::ToolGetOptionList(const int tool_type)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	std::string str_ret ;
	
    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return str_ret;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return str_ret;
    }

    unsigned int command = ENSEMBLE_TOOL_OPTION_GET_LIST;
		
	std::vector<float> vec_send_data ;
	vec_send_data.push_back(tool_type) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, std::string(), &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	int receive_size = vec_receive_data.size() ;
	if( receive_size > 0 )
	{
		str_ret.resize(receive_size);

		for( int i=0 ; i<receive_size ; i++ )
		{
			str_ret[i] = (char)vec_receive_data[i] ;
		}
	}

    return str_ret;
}

int CInterfaceControl::ToolAddNewOption(const std::string tool_id, const int option_type)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	std::string str_ret ;
	
    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return ENSEMBLE_ERROR_INVALID_MEMORY;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    unsigned int command = ENSEMBLE_TOOL_OPTION_ADD_NEW;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(option_type) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, tool_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

    return ret;
}

int CInterfaceControl::ToolDelOption(const std::string option_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	std::string str_ret ;
	
    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return ENSEMBLE_ERROR_INVALID_MEMORY;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    unsigned int command = ENSEMBLE_TOOL_OPTION_DEL;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, option_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;
	
    return ret;
}


std::string CInterfaceControl::Job_Type_Get_List_Xml(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	std::string str_ret ;
	
    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return str_ret;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return str_ret;
    }

    unsigned int command = ENSEMBLE_JOB_TYPE_GET_LIST;
		
	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, std::string(), &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	int receive_size = vec_receive_data.size() ;
	if( receive_size > 0 )
	{
		str_ret.resize(receive_size);

		for( int i=0 ; i<receive_size ; i++ )
		{
			str_ret[i] = (char)vec_receive_data[i] ;
		}
	}

    return str_ret;
}



std::string CInterfaceControl::Project_Get_List(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	std::string str_ret ;
	
    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return str_ret;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return str_ret;
    }

	qDebug("Project_Get_List") ;
	
    unsigned int command = ENSEMBLE_PRJ_GET_LIST;
		
	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, std::string(), &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	int receive_size = vec_receive_data.size() ;

	qDebug("receive_size = %d", receive_size)  ;
	
	if( receive_size > 0 )
	{
		str_ret.resize(receive_size);

		for( int i=0 ; i<receive_size ; i++ )
		{
			str_ret[i] = (char)vec_receive_data[i] ;
		}
	}

    return str_ret;
}

std::string CInterfaceControl::Project_Get_Name(const std::string id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	std::string str_ret ;
	
	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return str_ret;
	}

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return str_ret;
    }

	//printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_PRJ_GET_NAME;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	int receive_size = vec_receive_data.size() ;
	if( receive_size > 0 )
	{
		str_ret.resize(receive_size);

		for( int i=0 ; i<receive_size ; i++ )
		{
			str_ret[i] = (char)vec_receive_data[i] ;
		}
	}
	
    return str_ret;
}

int CInterfaceControl::Project_Set_Name(const std::string id, const std::string name) 
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
	if (m_cls_eth_client == NULL)
	{
		printf("Before accessing the Ensemble\n");
		return ENSEMBLE_ERROR_INVALID_MEMORY;
	}

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

	//printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_PRJ_SET_NAME;

	std::vector<float> vec_send_data ;
	if( !name.empty() )
    {
        int data_size = name.size() ;
        for( int i=0 ; i<data_size ; i++ )
        {
            float data = name[i] ;
            vec_send_data.push_back(data) ;
        }
    }
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;
	
	return ret;
}

std::string CInterfaceControl::GetToolList(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	std::string str_ret ;
	
    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return str_ret;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return str_ret;
    }

    unsigned int command = ENSEMBLE_GET_TOOL_LIST;
		
	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, std::string(), &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	int receive_size = vec_receive_data.size() ;
	if( receive_size > 0 )
	{
		str_ret.resize(receive_size);

		for( int i=0 ; i<receive_size ; i++ )
		{
			str_ret[i] = (char)vec_receive_data[i] ;
		}
	}
	
    return str_ret;
}

std::string CInterfaceControl::GetToolTypeName(const int type)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	std::string str_ret ;
	
    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return str_ret;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return str_ret;
    }

    unsigned int command = ENSEMBLE_GET_TOOL_TYPE_NAME;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(type) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, std::string(), &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	int receive_size = vec_receive_data.size() ;
	if( receive_size > 0 )
	{
		str_ret.resize(receive_size);

		for( int i=0 ; i<receive_size ; i++ )
		{
			str_ret[i] = (char)vec_receive_data[i] ;
		}
	}
	
    return str_ret;
}

int CInterfaceControl::AddTool(const std::string parent_id, const int tool_type)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return ENSEMBLE_ERROR_INVALID_MEMORY;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_TOOL_ADD;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(tool_type) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, parent_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

    return ret;
}

int CInterfaceControl::InsertTool(const std::string parent_id, const int index, const int tool_type)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return ENSEMBLE_ERROR_INVALID_MEMORY;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_TOOL_INSERT;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(index) ;
	vec_send_data.push_back(tool_type) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, parent_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;
	
    return ret;
}

int CInterfaceControl::MoveTool(const std::string parent_id, const int cur_index, const int target_index)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return ENSEMBLE_ERROR_INVALID_MEMORY;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_TOOL_MOVE;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(cur_index) ;
	vec_send_data.push_back(target_index) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, parent_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;
	
    return ret;
}

int CInterfaceControl::JobRun(const std::string id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return ENSEMBLE_ERROR_INVALID_MEMORY;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_JOB_RUN;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

    return ret;
}

//Calibration

int CInterfaceControl::Calibration_Get_Chess_Info(const std::string job_id, int *out_x_num, int *out_y_num, int *out_squre_mm_size) 
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return ENSEMBLE_ERROR_INVALID_MEMORY;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_JOB_CALIBRATION_GET_CHESS_INFO;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	if( vec_receive_data.size() == 3 )
	{
		if( out_x_num ) (*out_x_num) = vec_receive_data[0] ;
		if( out_y_num ) (*out_y_num) = vec_receive_data[1] ;
		if( out_squre_mm_size ) (*out_squre_mm_size) = vec_receive_data[2] ;
	}

	return ret ;
}

int CInterfaceControl::Calibration_Set_Chess_Info(const std::string job_id, const int x_num, const int y_num, const int squre_mm_size)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return ENSEMBLE_ERROR_INVALID_MEMORY;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_JOB_CALIBRATION_SET_CHESS_INFO;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(x_num) ;
	vec_send_data.push_back(y_num) ;
	vec_send_data.push_back(squre_mm_size) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;
	
    return ret;
}
	
int CInterfaceControl::Calibration_Add(const std::string job_id, float robot_x, float robot_y)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return ENSEMBLE_ERROR_INVALID_MEMORY;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_JOB_CALIBRATION_ADD;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(robot_x) ;
	vec_send_data.push_back(robot_y) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

    return ret;

}

int CInterfaceControl::Calibration_GetCount(const std::string job_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return ENSEMBLE_ERROR_INVALID_MEMORY;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_JOB_CALIBRATION_GET_COUNT;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	int count = 0 ;
	if( vec_receive_data.size() == 1 )
	{
		count = vec_receive_data[0]  ;
	}

	return count ;
}

int CInterfaceControl::Calibration_GetImage(const std::string job_id, int index, const int type_option, int& width, int& height, unsigned char** out_data)
{
    boost::unique_lock<boost::mutex> scoped_lock(mutex);

    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return ENSEMBLE_ERROR_INVALID_MEMORY;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    unsigned int command = ENSEMBLE_JOB_CALIBRATION_GET_IMAGE;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(index) ;
	vec_send_data.push_back(type_option) ;
	vec_send_data.push_back(width) ;
	vec_send_data.push_back(height) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
    ret += p_cls_ethernet_control_data->ReceiveImage(p_socket, command, width, height, out_data) ;
	
    return ret;
}


int CInterfaceControl::Calibration_GetRobotInfo(const std::string job_id, int index, float *out_robot_x, float *out_robot_y)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return ENSEMBLE_ERROR_INVALID_MEMORY;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_JOB_CALIBRATION_GET_INFO;

   	std::vector<float> vec_send_data ;
	vec_send_data.push_back(index) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;
	
	int i_robot_x = 0;
	int i_robot_y = 0;

	if (vec_receive_data.size() == 2)
	{
		(*out_robot_x) = vec_receive_data[0] ;
		(*out_robot_y) = vec_receive_data[1] ;
	}

	return ret ;
}

int CInterfaceControl::Calibration_Del(const std::string job_id, int index)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return ENSEMBLE_ERROR_INVALID_MEMORY;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_JOB_CALIBRATION_DEL ;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(index) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

    return ret;
}

int CInterfaceControl::Calibration_Clear(const std::string job_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return ENSEMBLE_ERROR_INVALID_MEMORY;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }
    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_JOB_CALIBRATION_CLEAR ;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

    return ret;
}

int CInterfaceControl::Calibration_Run(const std::string job_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return ENSEMBLE_ERROR_INVALID_MEMORY;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }
    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_JOB_CALIBRATION_RUN ;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

    return ret;
}

int CInterfaceControl::Calibration_Custom_Center_Point(const std::string job_id, int customnum)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return ENSEMBLE_ERROR_INVALID_MEMORY;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_JOB_CALIBRATION_SET_CUSTOM_CENTER_POINT ;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(customnum) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;
	
    return ret;
}

int CInterfaceControl::Calibration_GetPoint(const std::string job_id, const float in_px, const float in_py, float* out_rx, float* out_ry)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return ENSEMBLE_ERROR_INVALID_MEMORY;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }
    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_JOB_CALIBRATION_GET_POINT;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(in_px) ;
	vec_send_data.push_back(in_py) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;
	
	if( vec_receive_data.size() == 2 )
	{
		(*out_rx) = vec_receive_data[0] ;
		(*out_ry) = vec_receive_data[1] ;
	}

	return ret ;
}

int CInterfaceControl::Calibration_GetChessPoint(const std::string job_id, const int index, float* out_rx, float* out_ry)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return ENSEMBLE_ERROR_INVALID_MEMORY;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }
    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_JOB_CALIBRATION_GET_CHESSPOINT;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(index) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;
	
    if( vec_receive_data.size() == 2 )
	{
		(*out_rx) = vec_receive_data[0] ;
		(*out_ry) = vec_receive_data[1] ;
	}

	return ret ;
}

int CInterfaceControl::Calibration_isOK(const std::string job_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return ENSEMBLE_ERROR_INVALID_MEMORY;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_JOB_CALIBRATION_IS_OK;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;
	
	int is_ok = 0;
	
	if( vec_receive_data.size() == 1 )
	{
		is_ok = vec_receive_data[0] ;
	}

	return is_ok ;
}

int CInterfaceControl::Calibration_StandAlone_Run(const std::string job_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return ENSEMBLE_ERROR_INVALID_MEMORY;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_JOB_CALIBRATION_STANDALONE_RUN ;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

    return ret;
}

int CInterfaceControl::Calibration_StandAlone_Get_Image_Count(const std::string job_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return ENSEMBLE_ERROR_INVALID_MEMORY;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }
    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_JOB_CALIBRATION_STANDALONE_GET_IMAGE_COUNT;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	int value = 0.0 ;
	if( vec_receive_data.size() == 1 )
	{
		value = vec_receive_data[0]  ;
	}

	return value ;
}

int CInterfaceControl::Calibration_StandAlone_Init(const std::string job_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return ENSEMBLE_ERROR_INVALID_MEMORY;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_JOB_CALIBRATION_STANDALONE_INIT ;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;
	
    return ret;
}

int CInterfaceControl::Calibration_StandAlone_Get_Feature_Pos(const std::string job_id, int index,float posA[3], float posB[3], float posC[3], float posD[3])
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return ENSEMBLE_ERROR_INVALID_MEMORY;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_JOB_CALIBRATION_STANDALONE_GET_FEATURE_POSE;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(index) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;
	
	if ( vec_receive_data.size() == 12 )
	{
		float posAll[12];
		for (int i = 0; i < 12; i++)
		{
			posAll[i] = vec_receive_data[i] ;
		}
		
		//i_robot_x
		posA[0] = posAll[0] ;
		posA[1] = posAll[1] ;
		posA[2] = posAll[2] ;

		posB[0] = posAll[3] ;
		posB[1] = posAll[4] ;
		posB[2] = posAll[5] ;

		posC[0] = posAll[6] ;
		posC[1] = posAll[7] ;
		posC[2] = posAll[8] ;

		posD[0] = posAll[9] ;
		posD[1] = posAll[10];
		posD[2] = posAll[11];
	}

    return ret ;
}


int CInterfaceControl::Calibration_StandAlone_Set_Matrix(const std::string job_id, float matrix[12])
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return ENSEMBLE_ERROR_INVALID_MEMORY;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_JOB_CALIBRATION_STANDALONE_SET_CALIB_MAT  ;

	std::vector<float> vec_send_data ;
	for (int i = 0; i < 12; i++)
	{
		vec_send_data.push_back(matrix[i]) ;
	}
	
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;
	

    return ret;
}

int CInterfaceControl::Calibration_StandAlone_Get_Matrix(const std::string job_id, float matrix[12])
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return ENSEMBLE_ERROR_INVALID_MEMORY;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_JOB_CALIBRATION_STANDALONE_GET_CALIB_MAT;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

    if ( vec_receive_data.size() == 12 )
	{
		for (int i = 0; i < 12; i++)
		{
			matrix[i] = vec_receive_data[i];
		}
	}

    return ret ;
}

int CInterfaceControl::Calibration_StandAlone_Calc_Calib_Matrix(const std::string job_id, 
															float cposA[3], float cposB[3], float cposC[3], float cposD[3],
															float rposA[3], float rposB[3], float rposC[3], float rposD[3],
															float ret_Matrix[12])
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return ENSEMBLE_ERROR_INVALID_MEMORY;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_JOB_CALIBRATION_STANDALONE_CALC_CALIB_MAT;

	std::vector<float> vec_send_data ;
	float cpos[12], rpos[12];
	memcpy(&cpos[0], cposA, sizeof(float) * 3);
	memcpy(&cpos[3], cposB, sizeof(float) * 3);
	memcpy(&cpos[6], cposC, sizeof(float) * 3);
	memcpy(&cpos[9], cposD, sizeof(float) * 3);

	memcpy(&rpos[0], rposA, sizeof(float) * 3);
	memcpy(&rpos[3], rposB, sizeof(float) * 3);
	memcpy(&rpos[6], rposC, sizeof(float) * 3);
	memcpy(&rpos[9], rposD, sizeof(float) * 3);

	for (int i = 0; i < 12; i++)
	{
		vec_send_data.push_back(cpos[i]) ;
	}

	for (int i = 0; i < 12; i++)
	{
		vec_send_data.push_back(rpos[i]) ;
	}
	
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	if ( vec_receive_data.size() == 12 )
	{
		for (int i = 0; i < 12; i++)
		{
			ret_Matrix[i] = vec_receive_data[i];
		}
	}

    return ret ;
}

int CInterfaceControl::Calibration_StandAlone_Y_Direction(const std::string job_id, int Direction)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return ENSEMBLE_ERROR_INVALID_MEMORY;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_JOB_CALIBRATION_STANDALONE_SET_DIRECTION  ;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(Direction) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;
	
    return ret;
}

int CInterfaceControl::GetImage(const int option, std::string id, const int type_option, int& width, int& height, unsigned char** out_data)
{
    boost::unique_lock<boost::mutex> scoped_lock(mutex);

    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return ENSEMBLE_ERROR_INVALID_MEMORY;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    unsigned int command = ENSEMBLE_GET_IMAGE;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(option) ;
	vec_send_data.push_back(type_option) ;
	vec_send_data.push_back(width) ;
	vec_send_data.push_back(height) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, id, &vec_send_data) ;
    ret += p_cls_ethernet_control_data->ReceiveImage(p_socket, command, width, height, out_data) ;
	
    return ret;
}

int CInterfaceControl::GetResultImage(const std::string id, const int type_option, int& width, int& height, unsigned char** out_data)
{
    boost::unique_lock<boost::mutex> scoped_lock(mutex);

    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return ENSEMBLE_ERROR_INVALID_MEMORY;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    unsigned int command = ENSEMBLE_JOB_GET_IMAGE_RESULT;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(type_option) ;
	vec_send_data.push_back(width) ;
	vec_send_data.push_back(height) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, id, &vec_send_data) ;
    ret += p_cls_ethernet_control_data->ReceiveImage(p_socket, command, width, height, out_data) ;
	
    return ret;
}


std::string CInterfaceControl::GetSourceList(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	std::string str_ret ;
	
    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return str_ret;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return str_ret;
    }

    unsigned int command = ENSEMBLE_GET_SOURCE_LIST;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, std::string(), &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	int receive_size = vec_receive_data.size() ;
	if( receive_size > 0 )
	{
		str_ret.resize(receive_size) ;

		for( int i=0 ; i<receive_size ; i++ )
		{
			str_ret[i] = vec_receive_data[i];
		}
	}

    return str_ret;
}

int CInterfaceControl::SetSource(const std::string source)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    if (m_cls_eth_client == NULL)
    {
        printf("Before accessing the Ensemble\n");
        return ENSEMBLE_ERROR_INVALID_MEMORY;
    }

    tcp::socket *p_socket = m_cls_eth_client->GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_SET_SOURCE;

    int ret = p_cls_ethernet_control_data->SendString(p_socket, command, std::string(), source) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

    return ret;
}



