#include "EnsembleAPI.h"

CEnsembleAPI::CEnsembleAPI(const std::string str_ip, const int port)
{
	m_str_ip_addr = str_ip ;
	m_port = port ;
}

CEnsembleAPI::~CEnsembleAPI(void)
{
}	

int CEnsembleAPI::Ensemble_Network_Connect(const char* ip, const int port)
{
	m_str_ip_addr = ip ;
	m_port = port ;

	m_cls_interface_control.CreateSocket(ip, port);
	
    return m_cls_interface_control.SetNetworkIp(ip);
	
    //return m_cls_interface_control.CreateSocket(ip, port);
}

void CEnsembleAPI::Ensemble_Network_Disconnect()
{
	m_cls_interface_control.DeleteSocket();
}

int CEnsembleAPI::Ensemble_Network_IsOnline(void)
{
    int ret = 0 ;

    //qDebug("CEnsembleAPI::Ensemble_Network_IsOnline") ;

    int net_ctrl = m_cls_interface_control.IsOnline();      //ENSEMBLE_ERROR_ALREADY_CONNECT

   // qDebug("CEnsembleAPI::Ensemble_Network_IsOnline : net_ctrl = %d", net_ctrl) ;

    if( net_ctrl == 8370 )
    {
        ret = 1 ;
    }

    return ret ;
}

int CEnsembleAPI::Ensemble_Network_GetInfo(std::string* out_str_ip, int* out_port)
{
	if( out_str_ip ) (*out_str_ip) = m_str_ip_addr ;
	if( out_port ) (*out_port) = m_port ;

	return 1 ;
}

std::string CEnsembleAPI::Ensemble_Source_Get_List(void)
{
	return m_cls_interface_control.GetSourceList();
}

int CEnsembleAPI::Ensemble_Source_Set(const std::string source)
{
	return m_cls_interface_control.SetSource(source);
}

std::string CEnsembleAPI::Ensemble_DB_Get_List(void)
{
    return m_cls_interface_control.DB_Get_List();
}

int CEnsembleAPI::Ensemble_Source_Get_Image(const int type_option, const int width, const int height, ImageBuf* p_buf)
{
    int fixed_width = width ;
    int fixed_height = height ;

    return m_cls_interface_control.GetImage(GET_IMAGE_INPUT, std::string(), type_option, fixed_width, fixed_height, p_buf);
}

int CEnsembleAPI::Ensemble_Source_Get_Image(const int type_option, ImageBuf* p_buf)
{
    int get_width = -1 ;
    int get_height = -2 ;

    int ret = m_cls_interface_control.GetImage(GET_IMAGE_INPUT, std::string(), type_option, get_width, get_height, p_buf);

    if( p_buf != NULL )
	{
		(*p_buf).image_width = get_width ;
    	(*p_buf).image_height = get_height ;
    }

    return ret ;
}

int CEnsembleAPI::Ensemble_Job_Calibration_Get_Source_Calibration_Feature_Image(const std::string id, const int type_option, const int width, const int height, ImageBuf* p_buf)
{
	int fixed_width = width ;
    int fixed_height = height ;

    return m_cls_interface_control.GetImage(GET_IMAGE_CALIBRATION_FEATURE, id, type_option, fixed_width, fixed_height, p_buf);
}

int CEnsembleAPI::Ensemble_Job_Calibration_Get_Source_Calibration_Feature_Image(const std::string id, const int type_option, ImageBuf* p_buf)
{
	int get_width = -1 ;
    int get_height = -2 ;

    int ret = m_cls_interface_control.GetImage(GET_IMAGE_CALIBRATION_FEATURE, id, type_option, get_width, get_height, p_buf);

    if( p_buf != NULL )
	{
		(*p_buf).image_width = get_width ;
    	(*p_buf).image_height = get_height ;
    }

    return ret ;
}

int CEnsembleAPI::Ensemble_DeviceIcon_Get_Image(ImageBuf* p_buf)
{
	int get_width = -1 ;
    int get_height = -2 ;

    int ret = m_cls_interface_control.GetImage(GET_IMAGE_DEVICE_ICON, std::string(), 0, get_width, get_height, p_buf);

    if( p_buf != NULL )
	{
		(*p_buf).image_width = get_width ;
    	(*p_buf).image_height = get_height ;
    }

    return ret ;
}


int CEnsembleAPI::Ensemble_Task_Result_Get_Image(const std::string id, const int type_option, const int width, const int height, ImageBuf* p_buf)
{
	int fixed_width = width ;
    int fixed_height = height ;

    return m_cls_interface_control.GetResultImage(id, type_option, fixed_width, fixed_height, p_buf);
}

int CEnsembleAPI::Ensemble_Task_Result_Get_Image(const std::string id, const int type_option, ImageBuf* p_buf)
{
	int get_width = -1 ;
    int get_height = -2 ;

	if( p_buf != NULL )
	{
        if( (*p_buf).image_width > 0 ) get_width = (*p_buf).image_width ;
        if( (*p_buf).image_height > 0 )  get_height = (*p_buf).image_height ;
	}

    int ret = m_cls_interface_control.GetResultImage(id, type_option, get_width, get_height, p_buf);

	if( p_buf != NULL )
	{
        (*p_buf).image_width = get_width ;
        (*p_buf).image_height = get_height ;
	}

    return ret ;
}

int CEnsembleAPI::Ensemble_Job_Get_ResultImage(const std::string id, const int type_option, const int width, const int height, ImageBuf* p_buf)
{
	 int fixed_width = width ;
    int fixed_height = height ;

    return m_cls_interface_control.Job_GetResultImage(id, type_option, fixed_width, fixed_height, p_buf);
}

int CEnsembleAPI::Ensemble_Job_Get_ResultImage(const std::string id, const int type_option, ImageBuf* p_buf)
{
	int get_width = -1 ;
    int get_height = -2 ;

	if( p_buf != NULL )
	{
        if( (*p_buf).image_width > 0 ) get_width = (*p_buf).image_width ;
        if( (*p_buf).image_height > 0 )  get_height = (*p_buf).image_height ;
	}

    int ret = m_cls_interface_control.Job_GetResultImage(id, type_option, get_width, get_height, p_buf);

    if( p_buf != NULL )
	{
        (*p_buf).image_width = get_width ;
        (*p_buf).image_height = get_height ;
	}

    return ret ;
}

std::string CEnsembleAPI::Ensemble_Task_Get_Parent_Tree(const std::string id)
{
	return m_cls_interface_control.Task_Get_Parent_Tree(id);
}


int CEnsembleAPI::Ensemble_Task_Get_Run_Option(const std::string id)
{
	return m_cls_interface_control.Get_Run_Option(id);
}

int CEnsembleAPI::Ensemble_Task_Get_View_Option(const std::string id)
{
	return m_cls_interface_control.Get_View_Option(id);
}

int CEnsembleAPI::Ensemble_Task_Set_Run_Option(const std::string id, const bool run)
{
	return m_cls_interface_control.Base_Set_Run_Option(id, run);
}

int CEnsembleAPI::Ensemble_Task_Set_View_Option(const std::string id, const bool view)
{
	return m_cls_interface_control.Base_Set_View_Option(id, view);
}

int CEnsembleAPI::Ensemble_Task_File_Save(const bool b_overwrite) 		//save all
{
	return m_cls_interface_control.Task_Save(b_overwrite);
}

int CEnsembleAPI::Ensemble_Task_File_Load(void)
{
	std::vector<std::string> vec_str_db_id ;
	return Ensemble_Task_File_Load(vec_str_db_id) ; 
}

int CEnsembleAPI::Ensemble_Task_File_Load(std::vector<std::string> vec_str_db_id) //load all
{
	return m_cls_interface_control.Task_Load(vec_str_db_id);
}

int CEnsembleAPI::Ensemble_Task_Clear(void)
{
	return m_cls_interface_control.Task_Clear();
}

int CEnsembleAPI::Ensemble_Project_Add_New(const std::string name)
{
	return m_cls_interface_control.Project_Add_New(name);
}

int CEnsembleAPI::Ensemble_Project_Del(const std::string proj_id)
{
	return m_cls_interface_control.Project_Del(proj_id);
}

std::string CEnsembleAPI::Ensemble_Project_Get_Name(const std::string project_id)
{
	return m_cls_interface_control.Project_Get_Name(project_id);
}

std::string CEnsembleAPI::Ensemble_Project_Get_Has_Job_Info(const std::string project_id)
{
	return m_cls_interface_control.Project_Get_Job_Info(project_id);
}

int CEnsembleAPI::Ensemble_Project_Set_Name(const std::string project_id, const std::string name)
{
	return m_cls_interface_control.Project_Set_Name(project_id, name);
}

int CEnsembleAPI::Ensemble_Poject_Set_Trigger_Run(const std::string id, const bool b_set)
{
	return m_cls_interface_control.Poject_Set_Trigger_Run(id, b_set);
}

int CEnsembleAPI::Ensemble_Poject_Get_Trigger_Run(const std::string id)
{
	return m_cls_interface_control.Poject_Get_Trigger_Run(id);
}

std::string CEnsembleAPI::Ensemble_Poject_Run(const std::string id)
{
	return m_cls_interface_control.Project_Run(id);
}

int CEnsembleAPI::Ensemble_Project_Get_ResultImage(const std::string id, const int type_option, const int width, const int height, ImageBuf* p_buf)
{
	 int fixed_width = width ;
    int fixed_height = height ;

    return m_cls_interface_control.Project_GetResultImage(id, type_option, fixed_width, fixed_height, p_buf);
}

int CEnsembleAPI::Ensemble_Project_Get_ResultImage(const std::string id, const int type_option, ImageBuf* p_buf)
{
	int get_width = -1 ;
    int get_height = -2 ;

    if( p_buf )
    {
        get_width = (*p_buf).image_width ;
        get_height = (*p_buf).image_height ;
    }

    int ret = m_cls_interface_control.Project_GetResultImage(id, type_option, get_width, get_height, p_buf);

    if( p_buf )
    {
        (*p_buf).image_width = get_width ;
        (*p_buf).image_height = get_height ;
    }

    return ret ;
}

int CEnsembleAPI::Ensemble_Job_Add_New(const std::string project_id, const int type, const std::string name)
{
	return m_cls_interface_control.Job_Add_New(project_id, type, name);
}

std::string CEnsembleAPI::Ensemble_Job_Get_TypeName(const int job_type)
{
	return m_cls_interface_control.Job_Get_TypeName(job_type);
}

int CEnsembleAPI::Ensemble_Job_Del(const std::string id)
{	
	return m_cls_interface_control.DelJob(id);
}

std::string CEnsembleAPI::Ensemble_Job_Get_Name(const std::string id)
{
	return m_cls_interface_control.JobGetName(id);
}

int CEnsembleAPI::Ensemble_Job_Set_Name(const std::string id, const std::string name)
{
	return m_cls_interface_control.JobChangeName(id, name);
}

int CEnsembleAPI::Ensemble_Job_Set_Python_Code(const std::string id, const std::string code)
{
	return m_cls_interface_control.Job_Set_Python_Code(id, code) ;
}

std::string CEnsembleAPI::Ensemble_Job_Get_Python_Code(const std::string id)
{
	return m_cls_interface_control.Job_Get_Python_Code(id);
}

int CEnsembleAPI::Ensemble_Job_Run_Python_Code(const std::string id)
{
	return m_cls_interface_control.Job_Run_Python_Code(id);
}

int CEnsembleAPI::Ensemble_Job_Get_Image(const std::string id,const int type_option,  const int width, const int height, ImageBuf* p_buf)
{
	int fixed_width = width ;
    int fixed_height = height ;

    return m_cls_interface_control.JobGetImage(id, type_option, fixed_width, fixed_height, p_buf);
}

int CEnsembleAPI::Ensemble_Job_Get_Image(const std::string id, const int type_option, ImageBuf* p_buf)
{
	int get_width = -1 ;
    int get_height = -2 ;

    int ret = m_cls_interface_control.JobGetImage(id, type_option, get_width, get_height, p_buf);

    if( p_buf )
    {
        (*p_buf).image_width = get_width ;
        (*p_buf).image_height = get_height ;
    }

    return ret ;
}

int CEnsembleAPI::Ensemble_Job_Get_ObjectImage(const std::string id,const int type_option,  const int width, const int height, ImageBuf* p_buf)
{
	int fixed_width = width ;
    int fixed_height = height ;

    return m_cls_interface_control.JobGetObjectImage(id, type_option, fixed_width, fixed_height, p_buf);
}

int CEnsembleAPI::Ensemble_Job_Get_ObjectImage(const std::string id, const int type_option, ImageBuf* p_buf)
{
	int get_width = -1 ;
    int get_height = -2 ;

    int ret = m_cls_interface_control.JobGetObjectImage(id, type_option, get_width, get_height, p_buf);

    if( p_buf )
    {
        (*p_buf).image_width = get_width ;
        (*p_buf).image_height = get_height ;
    }

    return ret ;
}

int CEnsembleAPI::Ensemble_Tool_Get_ObjectImage(const std::string tool_id,const int type_option,  const int width, const int height, ImageBuf* p_buf)
{
	int fixed_width = width ;
    int fixed_height = height ;

    return m_cls_interface_control.ToolGetObjectImage(tool_id, type_option, fixed_width, fixed_height, p_buf);
}

int CEnsembleAPI::Ensemble_Tool_Get_ObjectImage(const std::string tool_id, const int type_option, ImageBuf* p_buf)
{
	int get_width = -1 ;
    int get_height = -2 ;

    int ret = m_cls_interface_control.ToolGetObjectImage(tool_id, type_option, get_width, get_height, p_buf);

    if( p_buf )
    {
        (*p_buf).image_width = get_width ;
        (*p_buf).image_height = get_height ;
    }

    return ret ;
}


int CEnsembleAPI::Ensemble_Job_Set_Image(const std::string id)
{
	return m_cls_interface_control.JobSetImage(id);
}

int CEnsembleAPI::Ensemble_Job_Set_DetectArea(const std::string id, const float x, const float y, const float width, const float height)
{	
	return m_cls_interface_control.JobSetDetectArea(id, x, y, width, height);
}

int CEnsembleAPI::Ensemble_Job_Set_Zoom(const std::string id, const float x, const float y, const float width, const float height) 
{
	return m_cls_interface_control.JobSetZoom(id, x, y, width, height);

}

int CEnsembleAPI::Ensemble_Job_Set_SelectObject(const std::string id, const float x, const float y, const float width, const float height)
{
	return m_cls_interface_control.JobSelectObject(id, x, y, width, height);
}

int CEnsembleAPI::Ensemble_Job_Set_Ref_Point(const std::string id, const float x, const float y) 
{
	return m_cls_interface_control.JobSetRefPoint(id, x, y);
}

int CEnsembleAPI::Ensemble_Job_Del_Ref_Point(const std::string id)
{
	return m_cls_interface_control.JobDelRefPoint(id);
}

int CEnsembleAPI::Ensemble_Tool_Set_Ref_Point(const std::string id, const float x, const float y)
{
	return m_cls_interface_control.ToolSetRefPoint(id, x, y);
}

int CEnsembleAPI::Ensemble_Tool_Del_Ref_Point(const std::string id)
{
	return m_cls_interface_control.ToolDelRefPoint(id);
}

int CEnsembleAPI::Ensemble_Tool_Set_SelectObject(const std::string tool_id, const float x, const float y, const float width, const float height, const int margin) 
{
	return m_cls_interface_control.ToolSelectObject(tool_id, x, y, width, height, margin);
}

int CEnsembleAPI::Ensemble_Tool_Set_SelectObject(const std::string tool_id, const float left_top_x, const float left_top_y, const float right_top_x, const float right_top_y, const float right_bottom_x, const float right_bottom_y, const float left_bottom_x, const float left_bottom_y, const int margin) 
{
	return m_cls_interface_control.ToolSelectObject(tool_id, left_top_x, left_top_y, right_top_x, right_top_y, right_bottom_x, right_bottom_y, left_bottom_x, left_bottom_y, margin)  ;
}

int CEnsembleAPI::Ensemble_Tool_Detect_Line_Set_SelectObject(const std::string tool_id, const float line1_x, const float line1_y, const float line2_x, const float line2_y, const float left_top_x, const float left_top_y, const float right_top_x, const float right_top_y, const float right_bottom_x, const float right_bottom_y, const float left_bottom_x, const float left_bottom_y) 
{
	return m_cls_interface_control.Tool_Detect_Line_Set_SelectObject(tool_id, line1_x, line1_y, line2_x, line2_y, left_top_x, left_top_y, right_top_x, right_top_y, right_bottom_x, right_bottom_y, left_bottom_x, left_bottom_y)  ;
}

int CEnsembleAPI::Ensemble_Job_Set_DetectOption(const std::string id, const int option, const float value) 
{
	return m_cls_interface_control.JobSetDetectOption(id, option, value);
}

float CEnsembleAPI::Ensemble_Job_Get_DetectOption(const std::string id, const int option)
{
	return m_cls_interface_control.JobGetDetectOption(id, option);
}

int CEnsembleAPI::Ensemble_Tool_Set_DetectOption(const std::string tool_id,const int option, const float value)
{
	return m_cls_interface_control.ToolSetDetectOption(tool_id, option, value);
}

float CEnsembleAPI::Ensemble_Tool_Get_DetectOption(const std::string tool_id,const int option)
{
	return m_cls_interface_control.ToolGetDetectOption(tool_id, option);
}

std::string CEnsembleAPI::Ensemble_Tool_Detect_Code_Get_Ref_CodeType(const std::string tool_id)
{
	return m_cls_interface_control.Tool_Detect_Code_Get_Ref_CodeType(tool_id) ;
}

std::string CEnsembleAPI::Ensemble_Tool_Detect_Code_Get_Ref_CodeData(const std::string tool_id)
{
	return m_cls_interface_control.Tool_Detect_Code_Get_Ref_CodeData(tool_id) ;
}

float CEnsembleAPI::Ensemble_Tool_Detect_Code_Get_Padding(const std::string tool_id)
{
	return m_cls_interface_control.Tool_Detect_Code_Get_Padding(tool_id) ;
}

int CEnsembleAPI::Ensemble_Tool_Detect_Code_Set_Padding(const std::string tool_id, const float padding_rate)
{
	return m_cls_interface_control.Tool_Detect_Code_Set_Padding(tool_id, padding_rate) ;
}

int CEnsembleAPI::Ensemble_Tool_Detect_Object_Get_Inspection_Tolerance_Info(const std::string tool_id, float* out_score_threshold)
{
	return m_cls_interface_control.Tool_Detect_Object_Get_Inspection_Tolerance_Info(tool_id, out_score_threshold) ;
}

int CEnsembleAPI::Ensemble_Tool_Detect_Object_Set_Inspection_Tolerance_Info(const std::string tool_id, const float score_threshold) 
{
	return m_cls_interface_control.Tool_Detect_Object_Set_Inspection_Tolerance_Info(tool_id, score_threshold) ;
}

int CEnsembleAPI::Ensemble_Tool_Offset_Distance_Set_Direction(const std::string tool_id, const int direction)
{
	return m_cls_interface_control.Tool_Offset_Distance_Set_Direction(tool_id, direction);
}

int CEnsembleAPI::Ensemble_Tool_Offset_Distance_Get_Direction(const std::string tool_id)
{
	return m_cls_interface_control.Tool_Offset_Distance_Get_Direction(tool_id);
}

int CEnsembleAPI::Ensemble_Tool_Offset_Distance_Set_Region(const std::string tool_id, const float x, const float y, const float width, const float height)
{
	return m_cls_interface_control.Tool_Offset_Distance_Set_Region(tool_id, x, y, width, height) ;
}

int CEnsembleAPI::Ensemble_Tool_Offset_Distance_Get_Region(const std::string tool_id, float* out_x, float* out_y, float* out_width, float* out_height)
{
	return m_cls_interface_control.Tool_Offset_Distance_Get_Region(tool_id, out_x, out_y, out_width, out_height) ;
}

int CEnsembleAPI::Ensemble_Tool_Offset_Distance_Get_Inspection_Base_Info(const std::string tool_id, float* out_distance, float *out_angle)
{
	return m_cls_interface_control.Tool_Offset_Distance_Get_Inspection_Base_Info(tool_id, out_distance, out_angle) ;
}

int CEnsembleAPI::Ensemble_Tool_Offset_Distance_Get_Inspection_Tolerance_Info(const std::string tool_id, float* out_distance_min, float *out_distance_max, float* out_angle_min, float *out_angle_max) 
{
	return m_cls_interface_control.Tool_Offset_Distance_Get_Inspection_Tolerance_Info(tool_id, out_distance_min, out_distance_max, out_angle_min, out_angle_max) ;
}

int CEnsembleAPI::Ensemble_Tool_Offset_Distance_Set_Inspection_Tolerance_Info(const std::string tool_id, const float distance_min, const float distance_max, const float angle_min, const float angle_max)
{
	return m_cls_interface_control.Tool_Offset_Distance_Set_Inspection_Tolerance_Info(tool_id, distance_min, distance_max, angle_min, angle_max) ;
}

float CEnsembleAPI::Ensemble_Tool_Distance_Get_CalcDistance(const std::string tool_id)
{
	return CEnsembleAPI::Ensemble_Tool_Get_DetectOption(tool_id, DetectOption::DETECT_OPTION_CALC_DISTANCE) ;
}

int CEnsembleAPI::Ensemble_Tool_Distance_Set_BaseDistance(const std::string tool_id, const float base_distance)
{
    return CEnsembleAPI::Ensemble_Tool_Set_DetectOption(tool_id, DetectOption::DETECT_OPTION_BASE_DISTANCE, base_distance) ;
}

float CEnsembleAPI::Ensemble_Tool_Distance_Get_BaseDistance(const std::string tool_id)
{
	return CEnsembleAPI::Ensemble_Tool_Get_DetectOption(tool_id, DetectOption::DETECT_OPTION_BASE_DISTANCE) ;
}

float CEnsembleAPI::Ensemble_Tool_Angle_Get_CalcAngle(const std::string tool_id)
{
	return CEnsembleAPI::Ensemble_Tool_Get_DetectOption(tool_id, DetectOption::DETECT_OPTION_CALC_ANGLE) ;
}

int CEnsembleAPI::Ensemble_Job_Del_SelectObject(const std::string id)
{
	return m_cls_interface_control.JobResetObject(id);
}

int CEnsembleAPI::Ensemble_Job_Set_Erase(const std::string id, const float x, const float y, const float width, const float height)
{
	return m_cls_interface_control.Job_Set_Erase(id, x, y, width, height) ;
}

int CEnsembleAPI::Ensemble_Job_Del_Erase(const std::string id)
{
	return m_cls_interface_control.Job_Del_Erase(id);
}

int CEnsembleAPI::Ensemble_Job_Set_MaskArea(const std::string id, float x, float y, float w, float h, bool inverse)
{
	return m_cls_interface_control.JobSetMaskArea(id, x, y, w, h, inverse);
}

int CEnsembleAPI::Ensemble_Job_Undo_MaskArea(const std::string id)
{
	return m_cls_interface_control.JobUndoMaskArea(id);
}

int CEnsembleAPI::Ensemble_Job_Del_MaskArea(const std::string id)
{
	return m_cls_interface_control.JobDelMaskArea(id);
}

int CEnsembleAPI::Ensemble_Job_Get_FeatureLevel(const std::string id)
{
	return m_cls_interface_control.JobGetFeatureLevel(id);
}

int CEnsembleAPI::Ensemble_Job_Set_FeatureLevel(const std::string id, const int level)
{
	return m_cls_interface_control.JobSetFeatureLevel(id, level);
}

int CEnsembleAPI::Ensemble_Job_Get_UseCustomFeatureOption(const std::string id)
{
	return m_cls_interface_control.JobGetUseCustomFeatureOption(id) ;
}

int CEnsembleAPI::Ensemble_Job_Set_UseCustomFeatureOption(const std::string id, const bool b_use)
{
	return m_cls_interface_control.JobSetUseCustomFeatureOption(id, b_use) ;
}

int CEnsembleAPI::Ensemble_Job_Get_Feature_Option(const std::string id, int* out_param1, int* out_param2, int* out_param3, int* out_param4)
{
	return m_cls_interface_control.Job_Get_Feature_Option(id, out_param1, out_param2, out_param3, out_param4) ;
}

int CEnsembleAPI::Ensemble_Job_Set_Feature_Option(const std::string id, const int param1, const int param2, const int param3, const int param4)
{
	return m_cls_interface_control.Job_Set_Feature_Option(id, param1, param2, param3, param4) ;
}

int CEnsembleAPI::Ensemble_Tool_Del(const std::string tool_id)
{
	return m_cls_interface_control.DelTool(tool_id);
}

std::string CEnsembleAPI::Ensemble_Project_Get_List(void)
{
	return m_cls_interface_control.Project_Get_List();
}

std::string CEnsembleAPI::Ensemble_Info_Type_Get_Job_List_Xml(void)
{
	return m_cls_interface_control.Job_Type_Get_List_Xml();
}

std::string CEnsembleAPI::Ensemble_Info_Type_Get_Tool_List_Xml(void) 
{
	return m_cls_interface_control.GetToolList();
}

std::string CEnsembleAPI::Ensemble_Info_Get_ToolTypeName(const int type)
{
    return m_cls_interface_control.GetToolTypeName(type);
}

int CEnsembleAPI::Ensemble_Info_Get_Type(const std::string id)
{
	return m_cls_interface_control.Get_Type(id);
}

std::string CEnsembleAPI::Ensemble_Info_Get_Addable_Subjob_List_Xml(const std::string id)
{
	return m_cls_interface_control.Get_Addable_Subjob_List_Xml(id);
}

int CEnsembleAPI::Ensemble_Tool_Add_New(const std::string parent_id, const int tool_type)
{
	return m_cls_interface_control.AddTool(parent_id, tool_type);
}

int CEnsembleAPI::Ensemble_Tool_Insert(const std::string parent_id, const int index, const int tool_type)
{
	return m_cls_interface_control.InsertTool(parent_id, index, tool_type);
}

int CEnsembleAPI::Ensemble_Tool_Move(const std::string parent_id, const int cur_index, const int target_index)
{
	return m_cls_interface_control.MoveTool(parent_id, cur_index, target_index);
}

//TOOL
std::string CEnsembleAPI::Ensemble_Tool_Get_Name(const std::string tool_id)
{
	return m_cls_interface_control.ToolGetName(tool_id);
}	

int CEnsembleAPI::Ensemble_Tool_Set_Name(const std::string tool_id, const std::string name) 
{
	return m_cls_interface_control.ToolSetName(tool_id, name);
}

int CEnsembleAPI::Ensemble_Tool_Get_Image(const std::string tool_id, const int type_option,  const int width, const int height, ImageBuf* p_buf)
{
	int fixed_width = width ;
    int fixed_height = height ;

    return m_cls_interface_control.ToolGetImage(tool_id, type_option, fixed_width, fixed_height, p_buf);
}

int CEnsembleAPI::Ensemble_Tool_Get_Image(const std::string tool_id, const int type_option, ImageBuf* p_buf)
{
	int get_width = -1 ;
    int get_height = -2 ;

    int ret = m_cls_interface_control.ToolGetImage(tool_id, type_option, get_width, get_height, p_buf);

    if( p_buf )
    {
        (*p_buf).image_width = get_width ;
        (*p_buf).image_height = get_height ;
    }

    return ret ;
}

//Option
int CEnsembleAPI::Ensemble_Tool_Option_GetImage(const std::string option_id, const int type_option,  const int width, const int height, ImageBuf* p_buf)
{
	int fixed_width = width ;
    int fixed_height = height ;

    return m_cls_interface_control.OptionGetImage(option_id, type_option, fixed_width, fixed_height, p_buf);
}

int CEnsembleAPI::Ensemble_Tool_Option_GetImage(const std::string option_id, const int type_option, ImageBuf* p_buf)
{
	int get_width = -1 ;
    int get_height = -2 ;

    int ret = m_cls_interface_control.OptionGetImage(option_id, type_option, get_width, get_height, p_buf);

    if( p_buf )
    {
        (*p_buf).image_width = get_width ;
        (*p_buf).image_height = get_height ;
    }

    return ret ;
}

int CEnsembleAPI::Ensemble_Tool_Option_InspectColor_Histogram_GetImage(const std::string option_id, const int color_num, const int type_option,  const int width, const int height, ImageBuf* p_buf)
{
	int fixed_width = width ;
    int fixed_height = height ;

    return m_cls_interface_control.Tool_Option_InspectColor_Histogram_GetImage(option_id, color_num, type_option, fixed_width, fixed_height, p_buf);
}

int CEnsembleAPI::Ensemble_Tool_Option_InspectColor_Histogram_GetImage(const std::string option_id, const int color_num, const int type_option, ImageBuf* p_buf)
{
	int get_width = -1 ;
    int get_height = -2 ;

    int ret = m_cls_interface_control.Tool_Option_InspectColor_Histogram_GetImage(option_id, color_num, type_option, get_width, get_height, p_buf);

    if( p_buf )
    {
        (*p_buf).image_width = get_width ;
        (*p_buf).image_height = get_height ;
    }

    return ret ;
}

int CEnsembleAPI::Ensemble_Tool_Option_InspectColor_Set_Histogram_UseElement(const std::string option_id, const int color_elem)
{
	return m_cls_interface_control.Tool_Option_InspectColor_Set_Histogram_UseElement(option_id, color_elem);
}

int CEnsembleAPI::Ensemble_Tool_Option_InspectColor_Get_Histogram_UseElement(const std::string option_id) 
{
	return m_cls_interface_control.Tool_Option_InspectColor_Get_Histogram_UseElement(option_id);
}

int CEnsembleAPI::Ensemble_Tool_Option_InspectColor_Set_Histogram_Range(const std::string option_id, const int color_elem, const float min, const float max)
{
	return m_cls_interface_control.Tool_Option_InspectColor_Set_Histogram_Range(option_id, color_elem, min, max);
}

int CEnsembleAPI::Ensemble_Tool_Option_InspectColor_Get_Histogram_Range(const std::string option_id, const int color_elem, int* out_min, int* out_max)
{
	return m_cls_interface_control.Tool_Option_InspectColor_Get_Histogram_Range(option_id, color_elem, out_min, out_max);
}

int CEnsembleAPI::Ensemble_Tool_Option_InspectColor_Get_Base_Pixel_Count(const std::string option_id)
{
	return m_cls_interface_control.Tool_Option_InspectColor_Get_Base_Pixel_Count(option_id);
}

int CEnsembleAPI::Ensemble_Tool_Option_InspectColor_Get_Tolerance(const std::string option_id, int* out_min, int* out_max)
{
	return m_cls_interface_control.Tool_Option_InspectColor_Get_Tolerance(option_id, out_min, out_max) ;
}

int CEnsembleAPI::Ensemble_Tool_Option_InspectColor_Set_Tolerance(const std::string option_id, const int min, const int max)
{
	return m_cls_interface_control.Tool_Option_InspectColor_Set_Tolerance(option_id, min, max) ;
}

int CEnsembleAPI::Ensemble_Tool_Option_InspectDistance_Get_Tolerance(const std::string option_id, float* out_min, float* out_max)
{
	return m_cls_interface_control.Tool_Option_InspectDistance_Get_Tolerance(option_id, out_min, out_max) ;
}

int CEnsembleAPI::Ensemble_Tool_Option_InspectDistance_Set_Tolerance(const std::string option_id, const float min, const float max)
{
	return m_cls_interface_control.Tool_Option_InspectDistance_Set_Tolerance(option_id, min, max) ;
}

std::string CEnsembleAPI::Ensemble_Tool_Option_InspectDistance_Get_ID_Info_Base(const std::string option_id)
{
	return m_cls_interface_control.Tool_Option_InspectDistance_Get_ID_Info_Base(option_id) ;
}

std::string CEnsembleAPI::Ensemble_Tool_Option_InspectDistance_Get_ID_Info_Target(const std::string option_id)
{
	return m_cls_interface_control.Tool_Option_InspectDistance_Get_ID_Info_Target(option_id) ;
}

int CEnsembleAPI::Ensemble_Tool_Option_InspectAngle_Get_Tolerance(const std::string option_id, float* out_min, float* out_max)
{
	return m_cls_interface_control.Tool_Option_InspectAngle_Get_Tolerance(option_id, out_min, out_max) ;
}

int CEnsembleAPI::Ensemble_Tool_Option_InspectAngle_Set_Tolerance(const std::string option_id, const float min, const float max)
{
	return m_cls_interface_control.Tool_Option_InspectAngle_Set_Tolerance(option_id, min, max) ;
}

std::string CEnsembleAPI::Ensemble_Tool_Option_InspectAngle_Get_ID_Info_Base(const std::string option_id)
{
	return m_cls_interface_control.Tool_Option_InspectAngle_Get_ID_Info_Base(option_id) ;
}

std::string CEnsembleAPI::Ensemble_Tool_Option_InspectAngle_Get_ID_Info_Target(const std::string option_id)
{
	return m_cls_interface_control.Tool_Option_InspectAngle_Get_ID_Info_Target(option_id) ;
}

float CEnsembleAPI::Ensemble_Tool_Circle_Get_CalcDiameter(const std::string tool_id)
{
    return m_cls_interface_control.Tool_Circle_Get_CalcDiameter(tool_id) ;
}

int CEnsembleAPI::Ensemble_Tool_Option_InspectDiameter_Get_Tolerance(const std::string option_id, float* out_min, float* out_max)
{
    return m_cls_interface_control.Tool_Option_InspectDiameter_Get_Tolerance(option_id, out_min, out_max) ;
}

int CEnsembleAPI::Ensemble_Tool_Option_InspectDiameter_Set_Tolerance(const std::string option_id, const float min, const float max)
{
    return m_cls_interface_control.Tool_Option_InspectDiameter_Set_Tolerance(option_id, min, max) ;
}

int CEnsembleAPI::Ensemble_Tool_Set_MaskArea(const std::string tool_id, float x, float y, float w, float h, bool inverse)
{
	return m_cls_interface_control.ToolSetMaskArea(tool_id, x, y, w, h, inverse);
}

int CEnsembleAPI::Ensemble_Tool_Undo_MaskArea(const std::string tool_id)
{
	return m_cls_interface_control.ToolUndoMaskArea(tool_id);
}

int CEnsembleAPI::Ensemble_Tool_Del_MaskArea(const std::string tool_id)
{
	return m_cls_interface_control.ToolDelMaskArea(tool_id);
}

int CEnsembleAPI::Ensemble_Tool_Get_FeatureLevel(const std::string tool_id)
{
	return m_cls_interface_control.ToolGetFeatureLevel(tool_id);
}

int CEnsembleAPI::Ensemble_Tool_Set_FeatureLevel(const std::string tool_id, const int level)
{
	return m_cls_interface_control.ToolSetFeatureLevel(tool_id, level);
}

int CEnsembleAPI::Ensemble_Tool_Get_UseCustomFeatureOption(const std::string id)
{
	return m_cls_interface_control.ToolGetUseCustomFeatureOption(id) ;
}

int CEnsembleAPI::Ensemble_Tool_Set_UseCustomFeatureOption(const std::string id, const bool b_use)
{
	return m_cls_interface_control.ToolSetUseCustomFeatureOption(id, b_use) ;
}

int CEnsembleAPI::Ensemble_Tool_Get_Feature_Option(const std::string id, int* out_param1, int* out_param2, int* out_param3, int* out_param4)
{
	return m_cls_interface_control.Tool_Get_Feature_Option(id, out_param1, out_param2, out_param3, out_param4) ;
}

int CEnsembleAPI::Ensemble_Tool_Set_Feature_Option(const std::string id, const int param1, const int param2, const int param3, const int param4)
{
	return m_cls_interface_control.Tool_Set_Feature_Option(id, param1, param2, param3, param4) ;
}

int CEnsembleAPI::Ensemble_Tool_Option_Crack_Get_InspectLevel(const std::string option_id)
{
	return m_cls_interface_control.Tool_Option_Crack_GetInspectLevel(option_id);
}

int CEnsembleAPI::Ensemble_Tool_Option_Crack_Set_InspectLevel(const std::string option_id, const int level)
{
	return m_cls_interface_control.Tool_Option_Crack_SetInspectLevel(option_id, level);
}

int CEnsembleAPI::Ensemble_Tool_Option_ColorCompare_Get_InspectLevel(const std::string option_id)
{
	return m_cls_interface_control.Tool_Option_ColorCompare_GetInspectLevel(option_id);
}

int CEnsembleAPI::Ensemble_Tool_Option_ColorCompare_Set_InspectLevel(const std::string option_id, const int level)
{
	return m_cls_interface_control.Tool_Option_ColorCompare_SetInspectLevel(option_id, level);
}

int CEnsembleAPI::Ensemble_Tool_Option_ColorCompare_Get_Sensitivity(const std::string option_id)
{
	return m_cls_interface_control.Tool_Option_ColorCompare_GetSensitivity(option_id);
}

int CEnsembleAPI::Ensemble_Tool_Option_ColorCompare_Set_Sensitivity(const std::string option_id, const int level)
{
	return m_cls_interface_control.Tool_Option_ColorCompare_SetSensitivity(option_id, level);
}

std::string CEnsembleAPI::Ensemble_Job_Run(const std::string id, const float masking_left_top_x, const float masking_left_top_y, const float masking_right_top_x, const float masking_right_top_y, const float masking_right_bottom_x, const float masking_right_bottom_y, const float masking_left_bottom_x, const float masking_left_bottom_y)
{
	return m_cls_interface_control.JobRun(id, masking_left_top_x, masking_left_top_y, masking_right_top_x, masking_right_top_y, masking_right_bottom_x, masking_right_bottom_y, masking_left_bottom_x, masking_left_bottom_y) ;
}

std::string CEnsembleAPI::Ensemble_Tool_Get_OptionList(const std::string tool_id)
{
	return m_cls_interface_control.ToolGetOptionList(tool_id) ;
}

std::string CEnsembleAPI::Ensemble_Tool_Get_OptionList(const int type)
{
	return m_cls_interface_control.ToolGetOptionList(type) ;
}

int CEnsembleAPI::Ensemble_Tool_Get_OptionList_Count(const int type)
{
	return m_cls_interface_control.ToolGetOptionCount(type) ;
}

int CEnsembleAPI::Ensemble_Tool_Add_NewOption(const std::string tool_id, const int option_type)
{	
	return m_cls_interface_control.ToolAddNewOption(tool_id, option_type) ;
}

int CEnsembleAPI::Ensemble_Tool_Del_Option(const std::string option_id)
{
	return m_cls_interface_control.ToolDelOption(option_id) ;
}

int CEnsembleAPI::Ensemble_Job_Calibration_Add(const std::string job_id, float robot_x, float robot_y)
{
	return m_cls_interface_control.Calibration_Add(job_id, robot_x, robot_y);
}

int CEnsembleAPI::Ensemble_Job_Calibration_Get_Chess_Info(const std::string job_id, int *out_x_num, int *out_y_num, float *out_squre_mm_size)
{
	return m_cls_interface_control.Calibration_Get_Chess_Info(job_id, out_x_num, out_y_num, out_squre_mm_size) ;
}

int CEnsembleAPI::Ensemble_Job_Calibration_Set_Chess_Info(const std::string job_id, const int x_num, const int y_num, const float squre_mm_size)
{
	return m_cls_interface_control.Calibration_Set_Chess_Info(job_id, x_num, y_num, squre_mm_size) ;
}

int CEnsembleAPI::Ensemble_Job_Calibration_GetCount(const std::string job_id)
{
	return m_cls_interface_control.Calibration_GetCount(job_id);
}

int CEnsembleAPI::Ensemble_Job_Calibration_GetImage(const std::string job_id, const int index, const int type_option, const int width, const int height, ImageBuf* p_buf)
{
    int fixed_width = width ;
    int fixed_height = height ;

    return m_cls_interface_control.Calibration_GetImage(job_id, index, type_option, fixed_width, fixed_height, p_buf);
}

int CEnsembleAPI::Ensemble_Job_Calibration_GetImage(const std::string job_id, const int index, const int type_option, ImageBuf* p_buf)
{
    int get_width = -1 ;
    int get_height = -2 ;

    int ret = m_cls_interface_control.Calibration_GetImage(job_id, index, type_option, get_width, get_height, p_buf);

    if( p_buf )
    {
        (*p_buf).image_width = get_width ;
        (*p_buf).image_height = get_height ;
    }

    return ret ;
}

int CEnsembleAPI::Ensemble_Job_Calibration_GetRobotInfo(const std::string job_id, int index, float *out_robot_x, float *out_robot_y)
{
	return m_cls_interface_control.Calibration_GetRobotInfo(job_id, index, out_robot_x, out_robot_y);
}

int CEnsembleAPI::Ensemble_Job_Calibration_Del(const std::string job_id, int index)
{
	return m_cls_interface_control.Calibration_Del(job_id, index);
}

int CEnsembleAPI::Ensemble_Job_Calibration_Clear(const std::string job_id)
{
	return m_cls_interface_control.Calibration_Clear(job_id);
}

int CEnsembleAPI::Ensemble_Job_Calibration_Run(const std::string job_id)
{
	return m_cls_interface_control.Calibration_Run(job_id);
}

int CEnsembleAPI::Ensemble_Job_Calibration_StandAlone_Init(const std::string job_id)
{
	return m_cls_interface_control.Calibration_StandAlone_Init(job_id);
}

int CEnsembleAPI::Ensemble_Job_Calibration_StandAlone_Run(const std::string job_id)
{
	return m_cls_interface_control.Calibration_StandAlone_Run(job_id);
}

int CEnsembleAPI::Ensemble_Job_Calibration_StandAlone_Get_Image_Count(const std::string job_id)
{
	return m_cls_interface_control.Calibration_StandAlone_Get_Image_Count(job_id);
}

int CEnsembleAPI::Ensemble_Job_Calibration_StandAlone_Get_Feature_Pos(const std::string job_id, int index, float posA[3], float posB[3], float posC[3], float posD[3])
{
	return m_cls_interface_control.Calibration_StandAlone_Get_Feature_Pos(job_id, index,posA, posB, posC, posD);
}

int CEnsembleAPI::Ensemble_Job_Calibration_StandAlone_Set_Matrix(const std::string job_id, float matrix[12])
{
	return m_cls_interface_control.Calibration_StandAlone_Set_Matrix(job_id, matrix);	
}

int CEnsembleAPI::Ensemble_Job_Calibration_StandAlone_Get_Matrix(const std::string job_id, float matrix[12])
{
	return m_cls_interface_control.Calibration_StandAlone_Get_Matrix(job_id, matrix);
}


int CEnsembleAPI::Ensemble_Job_Calibration_StandAlone_Calc_Calib_Matrix(const std::string job_id, 
	float cposA[3], float cposB[3], float cposC[3], float cposD[3],
	float rposA[3], float rposB[3], float rposC[3], float rposD[3],
	float ret_Matrix[12])
{
	return m_cls_interface_control.Calibration_StandAlone_Calc_Calib_Matrix(job_id, cposA, cposB, cposC, cposD, rposA, rposB, rposC, rposD, ret_Matrix);
}

int CEnsembleAPI::Ensemble_Job_Calibration_StandAlone_Y_Direction(const std::string job_id, int Direction)
{
	return m_cls_interface_control.Calibration_StandAlone_Y_Direction(job_id, Direction);
}

int CEnsembleAPI::Ensemble_Job_Calibration_Custom_Center_Point(const std::string job_id, int customnum)
{
	return m_cls_interface_control.Calibration_Custom_Center_Point(job_id, customnum);
}

int CEnsembleAPI::Ensemble_Job_Calibration_GetPoint(const std::string job_id, const float in_px, const float in_py, float* out_rx, float* out_ry)
{
	return m_cls_interface_control.Calibration_GetPoint(job_id, in_px, in_py, out_rx, out_ry);
}

int CEnsembleAPI::Ensemble_Job_Calibration_GetChessPoint(const std::string job_id, const int index, float* out_rx, float* out_ry)
{
	return m_cls_interface_control.Calibration_GetChessPoint(job_id, index, out_rx, out_ry);
}

int CEnsembleAPI::Ensemble_Job_Calibration_isOK(const std::string job_id)
{
	return m_cls_interface_control.Calibration_isOK(job_id);
}

int CEnsembleAPI::Ensemble_Job_Calibration_Copy(const std::string job_id, const std::string from_job_id)
{
	return m_cls_interface_control.Calibration_Copy(job_id, from_job_id);
}

int CEnsembleAPI::Ensemble_Camera_Set_Ready(const std::string job_id)
{
	return m_cls_interface_control.Camera_Set_Ready(job_id);
}

int CEnsembleAPI::Ensemble_Camera_Set_Auto_Exposure(const std::string job_id)
{
    return m_cls_interface_control.Camera_Set_Auto_Exposure(job_id);
}

int CEnsembleAPI::Ensemble_Camera_Set_Manual_Exposure_Value(const std::string job_id, const int value)
{
	return m_cls_interface_control.Camera_Set_Manual_Exposure_Value(job_id, value);
}

int CEnsembleAPI::Ensemble_Camera_Get_Manual_Exposure_Value(const std::string job_id)
{
	return m_cls_interface_control.Camera_Get_Manual_Exposure_Value(job_id);
}

int CEnsembleAPI::Ensemble_Camera_Get_Min_Exposure_Value(const std::string job_id)
{
	return m_cls_interface_control.Camera_Get_Min_Exposure_Value(job_id);
}

int CEnsembleAPI::Ensemble_Camera_Get_Max_Exposure_Value(const std::string job_id)
{
	return m_cls_interface_control.Camera_Get_Max_Exposure_Value(job_id);
}

int CEnsembleAPI::Ensemble_Camera_Set_Manual_Gain_Value(const std::string job_id, const int value)
{
	return m_cls_interface_control.Camera_Set_Manual_Gain_Value(job_id, value);
}

int CEnsembleAPI::Ensemble_Camera_Get_Manual_Gain_Value(const std::string job_id)
{
	return m_cls_interface_control.Camera_Get_Manual_Gain_Value(job_id);
}

int CEnsembleAPI::Ensemble_Camera_Get_Min_Gain_Value(const std::string job_id)
{
	return m_cls_interface_control.Camera_Get_Min_Gain_Value(job_id);
}

int CEnsembleAPI::Ensemble_Camera_Get_Max_Gain_Value(const std::string job_id)
{
	return m_cls_interface_control.Camera_Get_Max_Gain_Value(job_id);
}

int CEnsembleAPI::Ensemble_Camera_Set_Auto_Focus(const std::string job_id, const float x, const float y, const float width, const float height)
{
    return m_cls_interface_control.Camera_Set_Auto_Focus(job_id, x, y, width, height);
}

int CEnsembleAPI::Ensemble_Camera_Get_Auto_Focus_Area(const std::string job_id, float *out_x, float *out_y, float *out_width, float *out_height)
{
	return m_cls_interface_control.Camera_Get_Auto_Focus_Area(job_id, out_x, out_y, out_width, out_height) ;
}

int CEnsembleAPI::Ensemble_Camera_Set_Manual_Focus_Value(const std::string job_id, const int value)
{
	return m_cls_interface_control.Camera_Set_Manual_Focus_Value(job_id, value);
}

int CEnsembleAPI::Ensemble_Camera_Get_Manual_Focus_Value(const std::string job_id)
{
	return m_cls_interface_control.Camera_Get_Manual_Focus_Value(job_id);
}

int CEnsembleAPI::Ensemble_Camera_Get_Min_Focus_Value(const std::string job_id)
{
	return m_cls_interface_control.Camera_Get_Min_Focus_Value(job_id);
}

int CEnsembleAPI::Ensemble_Camera_Get_Max_Focus_Value(const std::string job_id)
{
	return m_cls_interface_control.Camera_Get_Max_Focus_Value(job_id);
}

int CEnsembleAPI::Ensemble_Camera_Set_Manual_Brightness_Value(const std::string job_id, const int value)
{
	return m_cls_interface_control.Camera_Set_Manual_Brightness_Value(job_id, value);
}

int CEnsembleAPI::Ensemble_Camera_Get_Manual_Brightness_Value(const std::string job_id)
{
	return m_cls_interface_control.Camera_Get_Manual_Brightness_Value(job_id);
}

int CEnsembleAPI::Ensemble_Camera_Get_Min_Brightness_Value(const std::string job_id)
{
	return m_cls_interface_control.Camera_Get_Min_Brightness_Value(job_id);
}

int CEnsembleAPI::Ensemble_Camera_Get_Max_Brightness_Value(const std::string job_id)
{
	return m_cls_interface_control.Camera_Get_Max_Brightness_Value(job_id);
}

int CEnsembleAPI::Ensemble_Camera_Set_Manual_Sharpness_Value(const std::string job_id, const int value)
{
	return m_cls_interface_control.Camera_Set_Manual_Sharpness_Value(job_id, value);
}

int CEnsembleAPI::Ensemble_Camera_Get_Manual_Sharpness_Value(const std::string job_id)
{
	return m_cls_interface_control.Camera_Get_Manual_Sharpness_Value(job_id);
}

int CEnsembleAPI::Ensemble_Camera_Get_Min_Sharpness_Value(const std::string job_id)
{
	return m_cls_interface_control.Camera_Get_Min_Sharpness_Value(job_id);
}

int CEnsembleAPI::Ensemble_Camera_Get_Max_Sharpness_Value(const std::string job_id)
{
	return m_cls_interface_control.Camera_Get_Max_Sharpness_Value(job_id);
}

int CEnsembleAPI::Ensemble_Camera_Set_Manual_Contrast_Value(const std::string job_id, const int value)
{
	return m_cls_interface_control.Camera_Set_Manual_Contrast_Value(job_id, value);
}

int CEnsembleAPI::Ensemble_Camera_Get_Manual_Contrast_Value(const std::string job_id)
{
	return m_cls_interface_control.Camera_Get_Manual_Contrast_Value(job_id);
}

int CEnsembleAPI::Ensemble_Camera_Get_Min_Contrast_Value(const std::string job_id)
{
	return m_cls_interface_control.Camera_Get_Min_Contrast_Value(job_id);
}

int CEnsembleAPI::Ensemble_Camera_Get_Max_Contrast_Value(const std::string job_id)
{
	return m_cls_interface_control.Camera_Get_Max_Contrast_Value(job_id);
}

int CEnsembleAPI::Ensemble_Camera_Set_Manual_ISO_Value(const std::string job_id, const int value)
{
	return m_cls_interface_control.Camera_Set_Manual_ISO_Value(job_id, value);
}

int CEnsembleAPI::Ensemble_Camera_Get_Manual_ISO_Value(const std::string job_id)
{
	return m_cls_interface_control.Camera_Get_Manual_ISO_Value(job_id);
}

int CEnsembleAPI::Ensemble_Camera_Get_Min_ISO_Value(const std::string job_id)
{
	return m_cls_interface_control.Camera_Get_Min_ISO_Value(job_id);
}

int CEnsembleAPI::Ensemble_Camera_Get_Max_ISO_Value(const std::string job_id)
{
	return m_cls_interface_control.Camera_Get_Max_ISO_Value(job_id);
}

int CEnsembleAPI::Ensemble_Camera_Set_Manual_Shutter_Speed_Value(const std::string job_id, const int value)
{
	return m_cls_interface_control.Camera_Set_Manual_Shutter_Speed_Value(job_id, value);
}

int CEnsembleAPI::Ensemble_Camera_Get_Manual_Shutter_Speed_Value(const std::string job_id)
{
	return m_cls_interface_control.Camera_Get_Manual_Shutter_Speed_Value(job_id);
}

int CEnsembleAPI::Ensemble_Camera_Get_Min_Shutter_Speed_Value(const std::string job_id)
{
	return m_cls_interface_control.Camera_Get_Min_Shutter_Speed_Value(job_id);
}

int CEnsembleAPI::Ensemble_Camera_Get_Max_Shutter_Speed_Value(const std::string job_id)
{
	return m_cls_interface_control.Camera_Get_Max_Shutter_Speed_Value(job_id);
}

int CEnsembleAPI::Ensemble_Camera_Set_Flip_V(const std::string job_id, const bool flip)
{
	return m_cls_interface_control.Camera_Set_Flip_V(job_id, flip);
}

int CEnsembleAPI::Ensemble_Camera_Get_Flip_V(const std::string job_id)
{
	return m_cls_interface_control.Camera_Get_Flip_V(job_id);
}

int CEnsembleAPI::Ensemble_Camera_Set_Flip_H(const std::string job_id, const bool flip)
{
	return m_cls_interface_control.Camera_Set_Flip_H(job_id, flip);
}

int CEnsembleAPI::Ensemble_Camera_Get_Flip_H(const std::string job_id)
{
	return m_cls_interface_control.Camera_Get_Flip_H(job_id);
}

int CEnsembleAPI::Ensemble_Camera_Set_Factory_Reset(const std::string job_id)
{
	return m_cls_interface_control.Camera_Set_Factory_Reset(job_id);
}

int CEnsembleAPI::Ensemble_Camera_Set_Config_Run(const std::string job_id)
{
	return m_cls_interface_control.Camera_Set_Config_Run(job_id);
}

int CEnsembleAPI::Ensemble_Camera_Capture_SW_Trigger(void)
{
    return m_cls_interface_control.Camera_Capture_SW_Trigger();
}

int CEnsembleAPI::Ensemble_Camera_Capture_HW_Trigger(void)
{
	return m_cls_interface_control.Camera_Capture_HW_Trigger();
}

int CEnsembleAPI::Ensemble_Digital_IO_GetIn(void)
{
    return m_cls_interface_control.Digital_IO_GetIn();
}

int CEnsembleAPI::Ensemble_Digital_IO_SetOut(int pin_num, int pin_val)
{
    return m_cls_interface_control.Digital_IO_SetOut(pin_num, pin_val);
}

std::string CEnsembleAPI::Ensemble_Update_Get_Version_List(void)
{
    return m_cls_interface_control.Update_Get_Version_List();
}

std::string CEnsembleAPI::Ensemble_Update_Get_Current_Version(void)
{
    return m_cls_interface_control.Update_Get_Current_Version();
}

int CEnsembleAPI::Ensemble_Update_Set_Version(std::string version_string)
{
    return m_cls_interface_control.Update_Set_Version(version_string);
}
int CEnsembleAPI::Ensemble_Camera_Get_Frame_Count()
{
	return m_cls_interface_control.Camera_Get_Frame_Count();
}
int CEnsembleAPI::Ensemble_Camera_Set_Camera_Image_To_Past_Frame(int FrameNum)
{
	return m_cls_interface_control.Camera_Set_Camera_Image_To_Past_Frame(FrameNum);
}
int CEnsembleAPI::Ensemble_Camera_Save_Image_To_Device_Local(const std::string file_name)
{
    return m_cls_interface_control.Camera_Save_Image_To_Device_Local(file_name);
}
