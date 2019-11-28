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

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    unsigned int command = ENSEMBLE_COMMAND_NETWORK_IS_ONLINE;

    //qDebug("ENSEMBLE_COMMAND_NETWORK_IS_ONLINE send ") ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, std::string(), NULL) ;

    //qDebug("ENSEMBLE_COMMAND_NETWORK_IS_ONLINE redeive") ;
    std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

    //qDebug("ENSEMBLE_COMMAND_NETWORK_IS_ONLINE redeive = %d", ret) ;

    if( vec_receive_data.size() == 1 )
    {
        ret = vec_receive_data[0] ;
    }

    return ret ;
}

std::string CInterfaceControl::Task_Get_Parent_Tree(const std::string id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	std::string str_ret ;
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return str_ret;
    }

    unsigned int command = ENSEMBLE_TASK_GET_PARENT_TREE;
		
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


int CInterfaceControl::Get_Run_Option(const std::string id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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

int CInterfaceControl::JobGetImage(const std::string id, const int type_option, int& width, int& height, unsigned char** out_data, int *out_type_option)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
    int image_buf_size= p_cls_ethernet_control_data->ReceiveImage(p_socket, command, width, height, out_data, out_type_option) ;
		
    return image_buf_size;
}

int CInterfaceControl::OptionGetImage(const std::string option_id, const int type_option, int& width, int& height, unsigned char** out_data, int* out_type_option)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
    int image_buf_size= p_cls_ethernet_control_data->ReceiveImage(p_socket, command, width, height, out_data, out_type_option) ;
	
    return image_buf_size;
}

int CInterfaceControl::Tool_Option_InspectColor_Histogram_GetImage(const std::string option_id, const int color_num, const int type_option, int& width, int& height, unsigned char** out_data, int* out_type_option)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
    int image_buf_size= p_cls_ethernet_control_data->ReceiveImage(p_socket, command, width, height, out_data, out_type_option) ;
	
    return image_buf_size;
}

int CInterfaceControl::Tool_Option_InspectColor_Set_Histogram_UseElement(const std::string option_id, const int color_elem)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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

int CInterfaceControl::ToolGetImage(const std::string tool_id, const int type_option, int& width, int& height, unsigned char** out_data, int* out_type_option)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);


    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
    int image_buf_size= p_cls_ethernet_control_data->ReceiveImage(p_socket, command, width, height, out_data, out_type_option) ;
	
    return image_buf_size;
}

int CInterfaceControl::JobGetObjectImage(const std::string id, const int type_option, int& width, int& height, unsigned char** out_data, int *out_type_option)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
    int image_buf_size = p_cls_ethernet_control_data->ReceiveImage(p_socket, command, width, height, out_data, out_type_option) ;
	
    return image_buf_size;
}

int CInterfaceControl::ToolGetObjectImage(const std::string tool_id, const int type_option, int& width, int& height, unsigned char** out_data, int* out_type_option)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
    int image_buf_size= p_cls_ethernet_control_data->ReceiveImage(p_socket, command, width, height, out_data, out_type_option) ;
	
    return image_buf_size;
}


int CInterfaceControl::JobSetImage(const std::string id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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

int CInterfaceControl::JobSetRefPoint(const std::string id, const float x, const float y)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

	//printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_JOB_SET_REF_POINT;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(x) ;
	vec_send_data.push_back(y) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	return ret;
}

int CInterfaceControl::JobDelRefPoint(const std::string id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

	//printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_JOB_DEL_REF_POINT;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	return ret;
}

int CInterfaceControl::JobSelectObject(const std::string id, const float x, const float y, const float width, const float height)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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

int CInterfaceControl::Tool_Detect_Line_Set_SelectObject(const std::string tool_id, const float line1_x, const float line1_y, const float line2_x, const float line2_y, const float left_top_x, const float left_top_y, const float right_top_x, const float right_top_y, const float right_bottom_x, const float right_bottom_y, const float left_bottom_x, const float left_bottom_y)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

	//printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_TOOL_DETECT_LINE_SELECT_ROTATED_OBJECT;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(line1_x) ;
	vec_send_data.push_back(line1_y) ;
	vec_send_data.push_back(line2_x) ;
	vec_send_data.push_back(line2_y) ;
	vec_send_data.push_back(left_top_x) ;
	vec_send_data.push_back(left_top_y) ;
	vec_send_data.push_back(right_top_x) ;
	vec_send_data.push_back(right_top_y) ;
	vec_send_data.push_back(right_bottom_x) ;
	vec_send_data.push_back(right_bottom_y) ;
	vec_send_data.push_back(left_bottom_x) ;
	vec_send_data.push_back(left_bottom_y) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, tool_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;
	
	return ret;
}

int CInterfaceControl::ToolSelectObject(const std::string tool_id, const float x, const float y, const float width, const float height, const int margin)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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

int CInterfaceControl::ToolSetRefPoint(const std::string id, const float x, const float y)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

	//printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_TOOL_SET_REF_POINT;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(x) ;
	vec_send_data.push_back(y) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	return ret;
}

int CInterfaceControl::ToolDelRefPoint(const std::string id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

	//printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_TOOL_DEL_REF_POINT;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	return ret;
}

int CInterfaceControl::JobSetDetectOption(const std::string id, const int option, const float value)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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

int CInterfaceControl::Job_Set_Erase(const std::string id, const float x, const float y, const float width, const float height)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

	//printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_JOB_SET_ERASE;

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

int CInterfaceControl::Job_Del_Erase(const std::string id)
{
	
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
	tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
	CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

	if( p_socket == NULL )
	{
		printf("Network Error : NULL Socket\n");
		return ENSEMBLE_ERROR_SOCKET_CONNECT;
	}

	//printf("id - %d\n", id);

	unsigned int command = ENSEMBLE_JOB_DEL_ERASE;

	std::vector<float> vec_send_data ;
	int ret = p_cls_ethernet_control_data->Send(p_socket, command, id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
	ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;
}

int CInterfaceControl::JobSetMaskArea(const std::string id, float x, float y, float w, float h, bool inverse)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
		
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
		
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
		
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
		
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
		
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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

int CInterfaceControl::JobGetUseCustomFeatureOption(const std::string id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
		
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }
	//printf("id - %d\n", id);

	unsigned int command = ENSEMBLE_JOB_GET_USE_CUSTOM_FEATURE_OPTION;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	int use = 0 ;
	if( vec_receive_data.size() == 1 )
	{
		use = vec_receive_data[0] ;
	}

	ret = use ;
	
    return ret;
}

int CInterfaceControl::JobSetUseCustomFeatureOption(const std::string id, const bool b_use)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
		
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }
	//printf("id - %d\n", id);

	unsigned int command = ENSEMBLE_JOB_SET_USE_CUSTOM_FEATURE_OPTION;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(b_use) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	return ret;
}

int CInterfaceControl::Job_Get_Feature_Option(const std::string id, int* out_param1, int* out_param2, int* out_param3, int* out_param4)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }
	//printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_JOB_GET_FEATURE_OPTION;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	if( vec_receive_data.size() == 4 )
	{
		if( out_param1 != NULL ) (*out_param1) = vec_receive_data[0] ;
		if( out_param2 != NULL ) (*out_param2) = vec_receive_data[1] ;
		if( out_param3 != NULL ) (*out_param3) = vec_receive_data[2] ;
		if( out_param4 != NULL ) (*out_param4) = vec_receive_data[3] ;
	}

	return ret ;
}

int CInterfaceControl::Job_Set_Feature_Option(const std::string id, const int param1, const int param2, const int param3, const int param4)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }
	//printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_JOB_SET_FEATURE_OPTION;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(param1) ;
	vec_send_data.push_back(param2) ;
	vec_send_data.push_back(param3) ;
	vec_send_data.push_back(param4) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	return ret ;
}

	
int CInterfaceControl::DelTool(const std::string tool_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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

int CInterfaceControl::ToolSetMaskArea(const std::string tool_id, float x, float y, float w, float h, bool inverse)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
		
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

	//printf("id - %d\n", id);

	unsigned int command = ENSEMBLE_TOOL_SET_MASK;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(x) ;
	vec_send_data.push_back(y) ;
	vec_send_data.push_back(w) ;
	vec_send_data.push_back(h) ;
	vec_send_data.push_back(inverse) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, tool_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	return ret;

}

int CInterfaceControl::ToolUndoMaskArea(const std::string tool_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
		
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }
	//printf("id - %d\n", id);

	unsigned int command = ENSEMBLE_TOOL_UNDO_MASK;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, tool_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	return ret;
}

int CInterfaceControl::ToolDelMaskArea(const std::string tool_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
		
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }
	//printf("id - %d\n", id);

	unsigned int command = ENSEMBLE_TOOL_DEL_MASK;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, tool_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	return ret;
}


int CInterfaceControl::ToolGetFeatureLevel(const std::string tool_id) 
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
		
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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

int CInterfaceControl::ToolGetUseCustomFeatureOption(const std::string id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
		
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }
	//printf("id - %d\n", id);

	unsigned int command = ENSEMBLE_TOOL_GET_USE_CUSTOM_FEATURE_OPTION;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	int use = 0 ;
	if( vec_receive_data.size() == 1 )
	{
		use = vec_receive_data[0] ;
	}

	ret = use ;
	
    return ret;
}

int CInterfaceControl::ToolSetUseCustomFeatureOption(const std::string id, const bool b_use)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
		
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }
	//printf("id - %d\n", id);

	unsigned int command = ENSEMBLE_TOOL_SET_USE_CUSTOM_FEATURE_OPTION;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(b_use) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	return ret;
}

int CInterfaceControl::Tool_Get_Feature_Option(const std::string id, int* out_param1, int* out_param2, int* out_param3, int* out_param4)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }
	//printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_TOOL_GET_FEATURE_OPTION;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	if( vec_receive_data.size() == 4 )
	{
		if( out_param1 != NULL ) (*out_param1) = vec_receive_data[0] ;
		if( out_param2 != NULL ) (*out_param2) = vec_receive_data[1] ;
		if( out_param3 != NULL ) (*out_param3) = vec_receive_data[2] ;
		if( out_param4 != NULL ) (*out_param4) = vec_receive_data[3] ;
	}

	return ret ;
}

int CInterfaceControl::Tool_Set_Feature_Option(const std::string id, const int param1, const int param2, const int param3, const int param4)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }
	//printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_TOOL_SET_FEATURE_OPTION;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(param1) ;
	vec_send_data.push_back(param2) ;
	vec_send_data.push_back(param3) ;
	vec_send_data.push_back(param4) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	return ret ;
}


int CInterfaceControl::Tool_Option_Crack_GetInspectLevel(const std::string option_id) 
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
		
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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

int CInterfaceControl::Tool_Detect_Object_Get_Inspection_Tolerance_Info(const std::string tool_id, float* out_score_threshold)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

	//printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_TOOL_DETECT_OBJCT_GET_INSPECT_TOLERANCE_INFO;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, tool_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;
	
	if( vec_receive_data.size() == 1 )
	{
		if( out_score_threshold ) (*out_score_threshold) = vec_receive_data[0] ;
	}

	return ret ;
}

int CInterfaceControl::Tool_Detect_Object_Set_Inspection_Tolerance_Info(const std::string tool_id, const float score_threshold)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

	//printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_TOOL_DETECT_OBJCT_SET_INSPECT_TOLERANCE_INFO;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(score_threshold) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, tool_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;
	
	return ret ;
}

std::string CInterfaceControl::Tool_Detect_Code_Get_Ref_CodeType(const std::string tool_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return std::string() ; //ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

	//printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_TOOL_DETECT_CODE_GET_CODE_TYPE;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, tool_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	std::string str_ret ;
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

std::string CInterfaceControl::Tool_Detect_Code_Get_Ref_CodeData(const std::string tool_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return std::string() ; //ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

	//printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_TOOL_DETECT_CODE_GET_CODE_DATA;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, tool_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	std::string str_ret ;
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

float CInterfaceControl::Tool_Detect_Code_Get_Padding(const std::string tool_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

	//printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_TOOL_DETECT_CODE_GET_PADDING;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, tool_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	float value = 0.0 ;
	if( vec_receive_data.size() ==1 )
	{
		value = vec_receive_data[0] ;
	}

	return value ;
}

int CInterfaceControl::Tool_Detect_Code_Set_Padding(const std::string tool_id, const float padding_rate)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

	//printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_TOOL_DETECT_CODE_SET_PADDING;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(padding_rate) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, tool_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	return ret ;
}

std::string CInterfaceControl::ToolGetOptionList(const std::string tool_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	std::string str_ret ;

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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

int CInterfaceControl::Tool_Offset_Distance_Set_Direction(const std::string tool_id, const int direction)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	std::string str_ret ;
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    unsigned int command = ENSEMBLE_TOOL_OFFSET_DISTANCE_SET_DIRECTION;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(direction) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, tool_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

    return ret;
}

int CInterfaceControl::Tool_Offset_Distance_Get_Direction(const std::string tool_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	std::string str_ret ;
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    unsigned int command = ENSEMBLE_TOOL_OFFSET_DISTANCE_GET_DIRECTION;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, tool_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	if( vec_receive_data.size() == 1 )
	{
		ret = (int)vec_receive_data[0] ;
	}

    return ret;
}

int CInterfaceControl::Tool_Offset_Distance_Set_Region(const std::string tool_id, const float x, const float y, const float width, const float height)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	std::string str_ret ;
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    unsigned int command = ENSEMBLE_TOOL_OFFSET_DISTANCE_SET_REGION;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(x) ;
	vec_send_data.push_back(y) ;
	vec_send_data.push_back(width) ;
	vec_send_data.push_back(height) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, tool_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

    return ret;
}

int CInterfaceControl::Tool_Offset_Distance_Get_Region(const std::string tool_id, float* out_x, float* out_y, float* out_width, float* out_height)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	std::string str_ret ;
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    unsigned int command = ENSEMBLE_TOOL_OFFSET_DISTANCE_GET_REGION;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, tool_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	if( vec_receive_data.size() == 4 )
	{
		if( out_x ) (*out_x) = vec_receive_data[0] ;
		if( out_y ) (*out_y) = vec_receive_data[1] ;
		if( out_width ) (*out_width) = vec_receive_data[2] ;
		if( out_height ) (*out_height) = vec_receive_data[3] ;
	}

    return ret;
}

int CInterfaceControl::Tool_Offset_Distance_Get_Inspection_Base_Info(const std::string tool_id, float* out_distance, float *out_angle)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	std::string str_ret ;
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    unsigned int command = ENSEMBLE_TOOL_OFFSET_DISTANCE_GET_INSPECT_BASE_INFO;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, tool_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	if( vec_receive_data.size() == 2 )
	{
		if( out_distance ) (*out_distance) = vec_receive_data[0] ;
		if( out_angle ) (*out_angle) = vec_receive_data[1] ;
	}

    return ret;
}

int CInterfaceControl::Tool_Offset_Distance_Get_Inspection_Tolerance_Info(const std::string tool_id, float* out_distance_min, float *out_distance_max, float* out_angle_min, float *out_angle_max) 
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	std::string str_ret ;
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    unsigned int command = ENSEMBLE_TOOL_OFFSET_DISTANCE_GET_INSPECT_TOLERANCE_INFO;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, tool_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	if( vec_receive_data.size() == 4 )
	{
		if( out_distance_min ) (*out_distance_min) = vec_receive_data[0] ;
		if( out_distance_max ) (*out_distance_max) = vec_receive_data[1] ;
		if( out_angle_min ) (*out_angle_min) = vec_receive_data[2] ;
		if( out_angle_max ) (*out_angle_max) = vec_receive_data[3] ;
	}

    return ret;
}

int CInterfaceControl::Tool_Offset_Distance_Set_Inspection_Tolerance_Info(const std::string tool_id, const float distance_min, const float distance_max, const float angle_min, const float angle_max) 
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	std::string str_ret ;
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    unsigned int command = ENSEMBLE_TOOL_OFFSET_DISTANCE_SET_INSPECT_TOLERANCE_INFO;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(distance_min) ;
	vec_send_data.push_back(distance_max) ;
	vec_send_data.push_back(angle_min) ;
	vec_send_data.push_back(angle_max) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, tool_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

    return ret;
}

int CInterfaceControl::ToolDelOption(const std::string option_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	std::string str_ret ;
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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

std::string CInterfaceControl::Project_Get_Job_Info(const std::string id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	std::string str_ret ;
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return str_ret;
    }

	//printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_PRJ_GET_JOB_INFO;

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
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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

int CInterfaceControl::Poject_Set_Trigger_Run(const std::string id, const bool b_set)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

	//printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_PRJ_SET_TRIGGER_RUN;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(b_set) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;
	
	return ret;
}

int CInterfaceControl::Poject_Get_Trigger_Run(const std::string id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

	//printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_PRJ_GET_TRIGGER_RUN;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	int b_trigger_run = 0 ;
	if( vec_receive_data.size() == 1 )
	{
		b_trigger_run = vec_receive_data[0] ;
	}
	return b_trigger_run;
}


std::string CInterfaceControl::Project_Run(const std::string id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

	std::string str_ret ;
    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return str_ret;
    }

	//printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_PRJ_RUN;

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

int CInterfaceControl::Project_GetResultImage(const std::string id, const int type_option, int& width, int& height, unsigned char** out_data, int* out_type_option)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    unsigned int command = ENSEMBLE_PRJ_GET_IMAGE_RESULT;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(type_option) ;
	vec_send_data.push_back(width) ;
	vec_send_data.push_back(height) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, id, &vec_send_data) ;
    int image_buf_size= p_cls_ethernet_control_data->ReceiveImage(p_socket, command, width, height, out_data, out_type_option) ;
	
    return image_buf_size;
}

std::string CInterfaceControl::GetToolList(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	std::string str_ret ;

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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

std::string CInterfaceControl::JobRun(const std::string id, const float masking_left_top_x, const float masking_left_top_y, const float masking_right_top_x, const float masking_right_top_y, const float masking_right_bottom_x, const float masking_right_bottom_y, const float masking_left_bottom_x, const float masking_left_bottom_y)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

	std::string str_ret ;
    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return str_ret;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_JOB_RUN;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(masking_left_top_x) ;
	vec_send_data.push_back(masking_left_top_y) ;
	vec_send_data.push_back(masking_right_top_x) ;
	vec_send_data.push_back(masking_right_top_y) ;
	vec_send_data.push_back(masking_right_bottom_x) ;
	vec_send_data.push_back(masking_right_bottom_y) ;
	vec_send_data.push_back(masking_left_bottom_x) ;
	vec_send_data.push_back(masking_left_bottom_y) ;
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

//Calibration

int CInterfaceControl::Calibration_Get_Chess_Info(const std::string job_id, int *out_x_num, int *out_y_num, int *out_squre_mm_size) 
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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

int CInterfaceControl::Calibration_GetImage(const std::string job_id, int index, const int type_option, int& width, int& height, unsigned char** out_data, int* out_type_option)
{
    boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
    int image_buf_size= p_cls_ethernet_control_data->ReceiveImage(p_socket, command, width, height, out_data, out_type_option) ;
	
    return image_buf_size;
}


int CInterfaceControl::Calibration_GetRobotInfo(const std::string job_id, int index, float *out_robot_x, float *out_robot_y)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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

int CInterfaceControl::Calibration_Copy(const std::string job_id, const std::string from_job_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_JOB_CALIBRATION_COPY ;

	std::vector<float> vec_send_data ;
	if( !from_job_id.empty() )
	{
		int data_size = from_job_id.size() ;
		for( int i=0 ; i<data_size ; i++ )
		{
			float data = from_job_id[i] ;
            vec_send_data.push_back(data) ;
		}
	}
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

    return ret;
}

int CInterfaceControl::Calibration_StandAlone_Run(const std::string job_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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

int CInterfaceControl::Camera_Set_Ready(const std::string job_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_CAMERA_SET_READY  ;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;
	
    return ret;		
}

int CInterfaceControl::Camera_Set_Auto_Exposure(const std::string job_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_CAMERA_SET_AUTO_EXPOSURE  ;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;
	
    return ret;		
}

int CInterfaceControl::Camera_Set_Manual_Exposure_Value(const std::string job_id, const int value)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_CAMERA_SET_MANUAL_EXPOSURE_VALUE  ;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(value) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;
	
    return ret;		
}

int CInterfaceControl::Camera_Get_Manual_Exposure_Value(const std::string job_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_CAMERA_GET_MANUAL_EXPOSURE_VALUE  ;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	if( vec_receive_data.size() > 0 )
	{
		ret = vec_receive_data[0] ;
	}
	
    return ret;		
}

int CInterfaceControl::Camera_Get_Min_Exposure_Value(const std::string job_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_CAMERA_GET_MIN_EXPOSURE_VALUE  ;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	if( vec_receive_data.size() > 0 )
	{
		ret = vec_receive_data[0] ;
	}
	
    return ret;		
}

int CInterfaceControl::Camera_Get_Max_Exposure_Value(const std::string job_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_CAMERA_GET_MAX_EXPOSURE_VALUE  ;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	if( vec_receive_data.size() > 0 )
	{
		ret = vec_receive_data[0] ;
	}
	
    return ret;		
}

int CInterfaceControl::Camera_Set_Manual_Gain_Value(const std::string job_id, const int value)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_CAMERA_SET_MANUAL_GAIN_VALUE  ;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(value) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;
	
    return ret;		
}

int CInterfaceControl::Camera_Get_Manual_Gain_Value(const std::string job_id)
{	
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_CAMERA_GET_MANUAL_GAIN_VALUE  ;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	if( vec_receive_data.size() > 0 )
	{
		ret = vec_receive_data[0] ;
	}
	
    return ret;		
}

int CInterfaceControl::Camera_Get_Min_Gain_Value(const std::string job_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_CAMERA_GET_MIN_GAIN_VALUE  ;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	if( vec_receive_data.size() > 0 )
	{
		ret = vec_receive_data[0] ;
	}
	
    return ret;		
}

int CInterfaceControl::Camera_Get_Max_Gain_Value(const std::string job_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_CAMERA_GET_MAX_GAIN_VALUE  ;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	if( vec_receive_data.size() > 0 )
	{
		ret = vec_receive_data[0] ;
	}
	
    return ret;		
}

int CInterfaceControl::Camera_Set_Auto_Focus(const std::string job_id, const float x, const float y, const float width, const float height)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_CAMERA_SET_AUTO_FOCUS ;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(x) ;
	vec_send_data.push_back(y) ;
	vec_send_data.push_back(width) ;
	vec_send_data.push_back(height) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;
	
    return ret;		
}

int CInterfaceControl::Camera_Get_Auto_Focus_Area(const std::string job_id, float *out_x, float *out_y, float *out_width, float *out_height)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_CAMERA_GET_AUTO_FOCUS_AREA  ;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	if( vec_receive_data.size() == 4 )
	{
		if( out_x ) (*out_x) = vec_receive_data[0] ;
		if( out_y ) (*out_y) = vec_receive_data[1] ;
		if( out_width ) (*out_width) = vec_receive_data[2] ;
		if( out_height ) (*out_height) = vec_receive_data[3] ;
	}
	
    return ret;		
}


int CInterfaceControl::Camera_Set_Manual_Focus_Value(const std::string job_id, const int value)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_CAMERA_SET_MANUAL_FOCUS_VALUE  ;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(value) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;
	
    return ret;		
}

int CInterfaceControl::Camera_Get_Manual_Focus_Value(const std::string job_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_CAMERA_GET_MANUAL_FOCUS_VALUE  ;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	if( vec_receive_data.size() > 0 )
	{
		ret = vec_receive_data[0] ;
	}
	
    return ret;		
}

int CInterfaceControl::Camera_Get_Min_Focus_Value(const std::string job_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_CAMERA_GET_MIN_FOCUS_VALUE  ;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	if( vec_receive_data.size() > 0 )
	{
		ret = vec_receive_data[0] ;
	}
	
    return ret;		
}

int CInterfaceControl::Camera_Get_Max_Focus_Value(const std::string job_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_CAMERA_GET_MAX_FOCUS_VALUE  ;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	if( vec_receive_data.size() > 0 )
	{
		ret = vec_receive_data[0] ;
	}
	
    return ret;		
}


int CInterfaceControl::Camera_Set_Manual_Brightness_Value(const std::string job_id, const int value)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_CAMERA_SET_MANUAL_BRIGHTNESS_VALUE  ;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(value) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;
	
    return ret;		
}

int CInterfaceControl::Camera_Get_Manual_Brightness_Value(const std::string job_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_CAMERA_GET_MANUAL_BRIGHTNESS_VALUE  ;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	if( vec_receive_data.size() > 0 )
	{
		ret = vec_receive_data[0] ;
	}
	
    return ret;		
}

int CInterfaceControl::Camera_Get_Min_Brightness_Value(const std::string job_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_CAMERA_GET_MIN_BRIGHTNESS_VALUE  ;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	if( vec_receive_data.size() > 0 )
	{
		ret = vec_receive_data[0] ;
	}
	
    return ret;		
}

int CInterfaceControl::Camera_Get_Max_Brightness_Value(const std::string job_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_CAMERA_GET_MAX_BRIGHTNESS_VALUE  ;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	if( vec_receive_data.size() > 0 )
	{
		ret = vec_receive_data[0] ;
	}
	
    return ret;		
}

int CInterfaceControl::Camera_Set_Manual_Sharpness_Value(const std::string job_id, const int value)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_CAMERA_SET_MANUAL_SHARPNESS_VALUE  ;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(value) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;
	
    return ret;		
}

int CInterfaceControl::Camera_Get_Manual_Sharpness_Value(const std::string job_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_CAMERA_GET_MANUAL_SHARPNESS_VALUE  ;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	if( vec_receive_data.size() > 0 )
	{
		ret = vec_receive_data[0] ;
	}
	
    return ret;		
}

int CInterfaceControl::Camera_Get_Min_Sharpness_Value(const std::string job_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_CAMERA_GET_MIN_SHARPNESS_VALUE  ;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	if( vec_receive_data.size() > 0 )
	{
		ret = vec_receive_data[0] ;
	}
	
    return ret;		
}

int CInterfaceControl::Camera_Get_Max_Sharpness_Value(const std::string job_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_CAMERA_GET_MAX_SHARPNESS_VALUE  ;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	if( vec_receive_data.size() > 0 )
	{
		ret = vec_receive_data[0] ;
	}
	
    return ret;		
}

int CInterfaceControl::Camera_Set_Manual_Contrast_Value(const std::string job_id, const int value)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_CAMERA_SET_MANUAL_CONTRAST_VALUE  ;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(value) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;
	
    return ret;		
}

int CInterfaceControl::Camera_Get_Manual_Contrast_Value(const std::string job_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_CAMERA_GET_MANUAL_CONTRAST_VALUE  ;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	if( vec_receive_data.size() > 0 )
	{
		ret = vec_receive_data[0] ;
	}
	
    return ret;		
}

int CInterfaceControl::Camera_Get_Min_Contrast_Value(const std::string job_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_CAMERA_GET_MIN_CONTRAST_VALUE  ;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	if( vec_receive_data.size() > 0 )
	{
		ret = vec_receive_data[0] ;
	}
	
    return ret;		
}

int CInterfaceControl::Camera_Get_Max_Contrast_Value(const std::string job_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_CAMERA_GET_MAX_CONTRAST_VALUE  ;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	if( vec_receive_data.size() > 0 )
	{
		ret = vec_receive_data[0] ;
	}
	
    return ret;		
}

int CInterfaceControl::Camera_Set_Manual_ISO_Value(const std::string job_id, const int value)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_CAMERA_SET_MANUAL_ISO_VALUE  ;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(value) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;
	
    return ret;		
}

int CInterfaceControl::Camera_Get_Manual_ISO_Value(const std::string job_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_CAMERA_GET_MANUAL_ISO_VALUE  ;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	if( vec_receive_data.size() > 0 )
	{
		ret = vec_receive_data[0] ;
	}
	
    return ret;		
}

int CInterfaceControl::Camera_Get_Min_ISO_Value(const std::string job_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_CAMERA_GET_MIN_ISO_VALUE  ;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	if( vec_receive_data.size() > 0 )
	{
		ret = vec_receive_data[0] ;
	}
	
    return ret;		
}

int CInterfaceControl::Camera_Get_Max_ISO_Value(const std::string job_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_CAMERA_GET_MAX_ISO_VALUE  ;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	if( vec_receive_data.size() > 0 )
	{
		ret = vec_receive_data[0] ;
	}
	
    return ret;		
}

int CInterfaceControl::Camera_Set_Manual_Shutter_Speed_Value(const std::string job_id, const int value)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_CAMERA_SET_MANUAL_SHUTTER_SPEED_VALUE  ;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(value) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;
	
    return ret;		
}

int CInterfaceControl::Camera_Get_Manual_Shutter_Speed_Value(const std::string job_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_CAMERA_GET_MANUAL_SHUTTER_SPEED_VALUE  ;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	if( vec_receive_data.size() > 0 )
	{
		ret = vec_receive_data[0] ;
	}
	
    return ret;		
}

int CInterfaceControl::Camera_Get_Min_Shutter_Speed_Value(const std::string job_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_CAMERA_GET_MIN_SHUTTER_SPEED_VALUE  ;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	if( vec_receive_data.size() > 0 )
	{
		ret = vec_receive_data[0] ;
	}
	
    return ret;		
}

int CInterfaceControl::Camera_Get_Max_Shutter_Speed_Value(const std::string job_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_CAMERA_GET_MAX_SHUTTER_SPEED_VALUE  ;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	if( vec_receive_data.size() > 0 )
	{
		ret = vec_receive_data[0] ;
	}
	
    return ret;		
}

int CInterfaceControl::Camera_Set_Flip_V(const std::string job_id, const bool flip)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_CAMERA_SET_FLIP_V  ;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(flip) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;
	
    return ret;		
}

int CInterfaceControl::Camera_Get_Flip_V(const std::string job_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_CAMERA_GET_FLIP_V  ;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	ret = false ;
	if( vec_receive_data.size() > 0 )
	{
		ret = vec_receive_data[0] ;
	}
	
    return ret;		
}

int CInterfaceControl::Camera_Set_Flip_H(const std::string job_id, const bool flip)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_CAMERA_SET_FLIP_H  ;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(flip) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;
	
    return ret;		
}

int CInterfaceControl::Camera_Get_Flip_H(const std::string job_id) 
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_CAMERA_GET_FLIP_H  ;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;

	ret = false ;
	if( vec_receive_data.size() > 0 )
	{
		ret = vec_receive_data[0] ;
	}
	
    return ret;		
}

int CInterfaceControl::Camera_Set_Factory_Reset(const std::string job_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_CAMERA_SET_FACTORY_RESET  ;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;
	
    return ret;		
}

int CInterfaceControl::Camera_Set_Config_Run(const std::string job_id)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    //printf("id - %d\n", id);

    unsigned int command = ENSEMBLE_CAMERA_SET_CONFIG_RUN  ;

	std::vector<float> vec_send_data ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, job_id, &vec_send_data) ;
	std::vector<float> vec_receive_data ;
    ret += p_cls_ethernet_control_data->Receive(p_socket, command, &vec_receive_data) ;
	
    return ret;		
}

int CInterfaceControl::GetImage(const int option, std::string id, const int type_option, int& width, int& height, unsigned char** out_data, int *out_type_option)
{
    boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
    int image_buf_size= p_cls_ethernet_control_data->ReceiveImage(p_socket, command, width, height, out_data, out_type_option) ;
	
    return image_buf_size;
}

int CInterfaceControl::GetResultImage(const std::string id, const int type_option, int& width, int& height, unsigned char** out_data, int *out_type_option)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
    CEthernetClientControlData* p_cls_ethernet_control_data = CEthernetClientControlData::getInstance() ;

    if( p_socket == NULL )
    {
        printf("Network Error : NULL Socket\n");
        return ENSEMBLE_ERROR_SOCKET_CONNECT;
    }

    unsigned int command = ENSEMBLE_GET_IMAGE_RESULT;

	std::vector<float> vec_send_data ;
	vec_send_data.push_back(type_option) ;
	vec_send_data.push_back(width) ;
	vec_send_data.push_back(height) ;
    int ret = p_cls_ethernet_control_data->Send(p_socket, command, id, &vec_send_data) ;
    int image_buf_size= p_cls_ethernet_control_data->ReceiveImage(p_socket, command, width, height, out_data, out_type_option) ;
	
    return image_buf_size;
}

int CInterfaceControl::Job_GetResultImage(const std::string id, const int type_option, int& width, int& height, unsigned char** out_data, int *out_type_option)
{
    boost::unique_lock<boost::mutex> scoped_lock(mutex);

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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
    int image_buf_size= p_cls_ethernet_control_data->ReceiveImage(p_socket, command, width, height, out_data, out_type_option) ;
	
    return image_buf_size;
}


std::string CInterfaceControl::GetSourceList(void)
{
	boost::unique_lock<boost::mutex> scoped_lock(mutex);

	std::string str_ret ;
	
    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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

    tcp::socket *p_socket = m_cls_eth_client.GetSocketPointer() ;
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



