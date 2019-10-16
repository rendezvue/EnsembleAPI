#include "EnsembleAPI.h"
#include "InterfaceControl.h"

CInterfaceControl g_cls_interface_control;

int Ensemble_Network_Connect(const char* ip)
{
    return g_cls_interface_control.CreateSocket(ip, NETWORK_PORT_CON);
}

void Ensemble_Network_Disconnect()
{
	g_cls_interface_control.DeleteSocket();
}

int Ensemble_Network_IsOnline(void)
{
    int ret = 0 ;

    //qDebug("Ensemble_Network_IsOnline") ;

    int net_ctrl = g_cls_interface_control.IsOnline();      //ENSEMBLE_ERROR_ALREADY_CONNECT

   // qDebug("Ensemble_Network_IsOnline : net_ctrl = %d", net_ctrl) ;

    if( net_ctrl == 8370 )
    {
        ret = 1 ;
    }

    return ret ;
}

std::string Ensemble_Source_Get_List(void)
{
	return g_cls_interface_control.GetSourceList();
}

int Ensemble_Source_Set(const std::string source)
{
	return g_cls_interface_control.SetSource(source);
}


int Ensemble_Source_Get_Image(const int option, std::string id, const int type_option, const int width, const int height, unsigned char** data)
{
    int fixed_width = width ;
    int fixed_height = height ;

    return g_cls_interface_control.GetImage(option, id, type_option, fixed_width, fixed_height, data);
}

int Ensemble_Source_Get_Image(const int option, std::string id, const int type_option, unsigned char** data, int* out_width, int* out_height)
{
    int get_width = -1 ;
    int get_height = -2 ;

    int ret = g_cls_interface_control.GetImage(option, id, type_option, get_width, get_height, data);

    if( out_width != NULL ) (*out_width) = get_width ;
    if( out_height != NULL ) (*out_height) = get_height ;

    return ret ;
}

int Ensemble_Job_Get_ResultImage(const std::string id, const int type_option, const int width, const int height, unsigned char** data)
{
	 int fixed_width = width ;
    int fixed_height = height ;

    return g_cls_interface_control.GetResultImage(id, type_option, fixed_width, fixed_height, data);
}

int Ensemble_Job_Get_ResultImage(const std::string id, const int type_option, unsigned char** data, int* out_width, int* out_height) 
{
	int get_width = -1 ;
    int get_height = -2 ;

	if( out_width != NULL ) get_width = (*out_width) ;
	if( out_height != NULL ) get_height = (*out_height) ;

    int ret = g_cls_interface_control.GetResultImage(id, type_option, get_width, get_height, data);

    if( out_width != NULL ) (*out_width) = get_width ;
    if( out_height != NULL ) (*out_height) = get_height ;

    return ret ;
}

int Ensemble_Task_Get_Run_Option(const std::string id)
{
	return g_cls_interface_control.Get_Run_Option(id);
}

int Ensemble_Task_Get_View_Option(const std::string id)
{
	return g_cls_interface_control.Get_View_Option(id);
}

int Ensemble_Task_Set_Run_Option(const std::string id, const bool run)
{
	return g_cls_interface_control.Base_Set_Run_Option(id, run);
}

int Ensemble_Task_Set_View_Option(const std::string id, const bool view)
{
	return g_cls_interface_control.Base_Set_View_Option(id, view);
}

int Ensemble_Task_File_Save(void) 		//save all
{
	return g_cls_interface_control.Task_Save();
}

int Ensemble_Task_File_Load(void) //load all
{
	return g_cls_interface_control.Task_Load();
}

int Ensemble_Project_Add_New(const std::string name)
{
	return g_cls_interface_control.Project_Add_New(name);
}

int Ensemble_Project_Del(const std::string proj_id)
{
	return g_cls_interface_control.Project_Del(proj_id);
}

std::string Ensemble_Project_Get_Name(const std::string project_id)
{
	return g_cls_interface_control.Project_Get_Name(project_id);
}

int Ensemble_Project_Set_Name(const std::string project_id, const std::string name)
{
	return g_cls_interface_control.Project_Set_Name(project_id, name);
}

int Ensemble_Job_Add_New(const std::string project_id, const int type, const std::string name)
{
	return g_cls_interface_control.Job_Add_New(project_id, type, name);
}

std::string Ensemble_Job_Get_TypeName(const int job_type)
{
	return g_cls_interface_control.Job_Get_TypeName(job_type);
}

int Ensemble_Job_Del(const std::string id)
{	
	return g_cls_interface_control.DelJob(id);
}

std::string Ensemble_Job_Get_Name(const std::string id)
{
	return g_cls_interface_control.JobGetName(id);
}

int Ensemble_Job_Set_Name(const std::string id, const std::string name)
{
	return g_cls_interface_control.JobChangeName(id, name);
}

int Ensemble_Job_Get_Image(const std::string id,const int type_option,  const int width, const int height, unsigned char** data) 
{
	int fixed_width = width ;
    int fixed_height = height ;

    return g_cls_interface_control.JobGetImage(id, type_option, fixed_width, fixed_height, data);
}

int Ensemble_Job_Get_Image(const std::string id, const int type_option, unsigned char** data, int* out_width, int* out_height) 
{
	int get_width = -1 ;
    int get_height = -2 ;

    int ret = g_cls_interface_control.JobGetImage(id, type_option, get_width, get_height, data);

    if( out_width != NULL ) (*out_width) = get_width ;
    if( out_height != NULL ) (*out_height) = get_height ;

    return ret ;
}

int Ensemble_Job_Get_ObjectImage(const std::string id,const int type_option,  const int width, const int height, unsigned char** data)
{
	int fixed_width = width ;
    int fixed_height = height ;

    return g_cls_interface_control.JobGetObjectImage(id, type_option, fixed_width, fixed_height, data);
}

int Ensemble_Job_Get_ObjectImage(const std::string id, const int type_option, unsigned char** data, int* out_width, int* out_height)
{
	int get_width = -1 ;
    int get_height = -2 ;

    int ret = g_cls_interface_control.JobGetObjectImage(id, type_option, get_width, get_height, data);

    if( out_width != NULL ) (*out_width) = get_width ;
    if( out_height != NULL ) (*out_height) = get_height ;

    return ret ;
}

int Ensemble_Tool_Get_ObjectImage(const std::string tool_id,const int type_option,  const int width, const int height, unsigned char** data)
{
	int fixed_width = width ;
    int fixed_height = height ;

    return g_cls_interface_control.ToolGetObjectImage(tool_id, type_option, fixed_width, fixed_height, data);
}

int Ensemble_Tool_Get_ObjectImage(const std::string tool_id, const int type_option, unsigned char** data, int* out_width, int* out_height) 
{
	int get_width = -1 ;
    int get_height = -2 ;

    int ret = g_cls_interface_control.ToolGetObjectImage(tool_id, type_option, get_width, get_height, data);

    if( out_width != NULL ) (*out_width) = get_width ;
    if( out_height != NULL ) (*out_height) = get_height ;

    return ret ;
}


int Ensemble_Job_Set_Image(const std::string id)
{
	return g_cls_interface_control.JobSetImage(id);
}

int Ensemble_Job_Set_DetectArea(const std::string id, const float x, const float y, const float width, const float height)
{	
	return g_cls_interface_control.JobSetDetectArea(id, x, y, width, height);
}

int Ensemble_Job_Set_Zoom(const std::string id, const float x, const float y, const float width, const float height) 
{
	return g_cls_interface_control.JobSetZoom(id, x, y, width, height);

}

int Ensemble_Job_Set_SelectObject(const std::string id, const float x, const float y, const float width, const float height)
{
	return g_cls_interface_control.JobSelectObject(id, x, y, width, height);
}

int Ensemble_Job_Set_Ref_Point(const std::string id, const float x, const float y) 
{
	return g_cls_interface_control.JobSetRefPoint(id, x, y);
}

int Ensemble_Job_Del_Ref_Point(const std::string id)
{
	return g_cls_interface_control.JobDelRefPoint(id);
}

int Ensemble_Tool_Set_Ref_Point(const std::string id, const float x, const float y)
{
	return g_cls_interface_control.ToolSetRefPoint(id, x, y);
}

int Ensemble_Tool_Del_Ref_Point(const std::string id)
{
	return g_cls_interface_control.ToolDelRefPoint(id);
}

int Ensemble_Tool_Set_SelectObject(const std::string tool_id, const float x, const float y, const float width, const float height, const int margin) 
{
	return g_cls_interface_control.ToolSelectObject(tool_id, x, y, width, height, margin);
}

int Ensemble_Tool_Set_SelectObject(const std::string tool_id, const float left_top_x, const float left_top_y, const float right_top_x, const float right_top_y, const float right_bottom_x, const float right_bottom_y, const float left_bottom_x, const float left_bottom_y, const int margin) 
{
	return g_cls_interface_control.ToolSelectObject(tool_id, left_top_x, left_top_y, right_top_x, right_top_y, right_bottom_x, right_bottom_y, left_bottom_x, left_bottom_y, margin)  ;
}


int Ensemble_Job_Set_DetectOption(const std::string id, const int option, const float value) 
{
	return g_cls_interface_control.JobSetDetectOption(id, option, value);
}

float Ensemble_Job_Get_DetectOption(const std::string id, const int option)
{
	return g_cls_interface_control.JobGetDetectOption(id, option);
}

int Ensemble_Tool_Set_DetectOption(const std::string tool_id,const int option, const float value)
{
	return g_cls_interface_control.ToolSetDetectOption(tool_id, option, value);
}

float Ensemble_Tool_Get_DetectOption(const std::string tool_id,const int option)
{
	return g_cls_interface_control.ToolGetDetectOption(tool_id, option);
}

float Ensemble_Tool_Distance_Get_CalcDistance(const std::string tool_id)
{
	return Ensemble_Tool_Get_DetectOption(tool_id, DetectOption::DETECT_OPTION_CALC_DISTANCE) ;
}

int Ensemble_Tool_Distance_Set_BaseDistance(const std::string tool_id, const float base_distance)
{
    return Ensemble_Tool_Set_DetectOption(tool_id, DetectOption::DETECT_OPTION_BASE_DISTANCE, base_distance) ;
}

float Ensemble_Tool_Distance_Get_BaseDistance(const std::string tool_id)
{
	return Ensemble_Tool_Get_DetectOption(tool_id, DetectOption::DETECT_OPTION_BASE_DISTANCE) ;
}

float Ensemble_Tool_Angle_Get_CalcAngle(const std::string tool_id)
{
	return Ensemble_Tool_Get_DetectOption(tool_id, DetectOption::DETECT_OPTION_CALC_ANGLE) ;
}

int Ensemble_Job_Del_SelectObject(const std::string id)
{
	return g_cls_interface_control.JobResetObject(id);
}

int Ensemble_Job_Set_MaskArea(const std::string id, float x, float y, float w, float h, bool inverse)
{
	return g_cls_interface_control.JobSetMaskArea(id, x, y, w, h, inverse);
}

int Ensemble_Job_Undo_MaskArea(const std::string id)
{
	return g_cls_interface_control.JobUndoMaskArea(id);
}

int Ensemble_Job_Del_MaskArea(const std::string id)
{
	return g_cls_interface_control.JobDelMaskArea(id);
}

int Ensemble_Job_Get_FeatureLevel(const std::string id)
{
	return g_cls_interface_control.JobGetFeatureLevel(id);
}

int Ensemble_Job_Set_FeatureLevel(const std::string id, const int level)
{
	return g_cls_interface_control.JobSetFeatureLevel(id, level);
}

int Ensemble_Job_Get_UseCustomFeatureOption(const std::string id)
{
	return g_cls_interface_control.JobGetUseCustomFeatureOption(id) ;
}

int Ensemble_Job_Set_UseCustomFeatureOption(const std::string id, const bool b_use)
{
	return g_cls_interface_control.JobSetUseCustomFeatureOption(id, b_use) ;
}

int Ensemble_Job_Get_Feature_Option(const std::string id, int* out_param1, int* out_param2, int* out_param3, int* out_param4)
{
	return g_cls_interface_control.Job_Get_Feature_Option(id, out_param1, out_param2, out_param3, out_param4) ;
}

int Ensemble_Job_Set_Feature_Option(const std::string id, const int param1, const int param2, const int param3, const int param4)
{
	return g_cls_interface_control.Job_Set_Feature_Option(id, param1, param2, param3, param4) ;
}

int Ensemble_Tool_Del(const std::string tool_id)
{
	return g_cls_interface_control.DelTool(tool_id);
}

std::string Ensemble_Project_Get_List(void)
{
	return g_cls_interface_control.Project_Get_List();
}

std::string Ensemble_Info_Type_Get_Job_List_Xml(void)
{
	return g_cls_interface_control.Job_Type_Get_List_Xml();
}

std::string Ensemble_Info_Type_Get_Tool_List_Xml(void) 
{
	return g_cls_interface_control.GetToolList();
}

std::string Ensemble_Info_Get_ToolTypeName(const int type)
{
    return g_cls_interface_control.GetToolTypeName(type);
}


int Ensemble_Tool_Add_New(const std::string parent_id, const int tool_type)
{
	return g_cls_interface_control.AddTool(parent_id, tool_type);
}

int Ensemble_Tool_Insert(const std::string parent_id, const int index, const int tool_type)
{
	return g_cls_interface_control.InsertTool(parent_id, index, tool_type);
}

int Ensemble_Tool_Move(const std::string parent_id, const int cur_index, const int target_index)
{
	return g_cls_interface_control.MoveTool(parent_id, cur_index, target_index);
}

//TOOL
std::string Ensemble_Tool_Get_Name(const std::string tool_id)
{
	return g_cls_interface_control.ToolGetName(tool_id);
}	

int Ensemble_Tool_Set_Name(const std::string tool_id, const std::string name) 
{
	return g_cls_interface_control.ToolSetName(tool_id, name);
}

int Ensemble_Tool_Get_Image(const std::string tool_id, const int type_option,  const int width, const int height, unsigned char** data) 
{
	int fixed_width = width ;
    int fixed_height = height ;

    return g_cls_interface_control.ToolGetImage(tool_id, type_option, fixed_width, fixed_height, data);
}

int Ensemble_Tool_Get_Image(const std::string tool_id, const int type_option, unsigned char** data, int* out_width, int* out_height)
{
	int get_width = -1 ;
    int get_height = -2 ;

    int ret = g_cls_interface_control.ToolGetImage(tool_id, type_option, get_width, get_height, data);

    if( out_width != NULL ) (*out_width) = get_width ;
    if( out_height != NULL ) (*out_height) = get_height ;

    return ret ;
}

//Option
int Ensemble_Tool_Option_GetImage(const std::string option_id, const int type_option,  const int width, const int height, unsigned char** data)
{
	int fixed_width = width ;
    int fixed_height = height ;

    return g_cls_interface_control.OptionGetImage(option_id, type_option, fixed_width, fixed_height, data);
}

int Ensemble_Tool_Option_GetImage(const std::string option_id, const int type_option, unsigned char** data, int* out_width, int* out_height)
{
	int get_width = -1 ;
    int get_height = -2 ;

    int ret = g_cls_interface_control.OptionGetImage(option_id, type_option, get_width, get_height, data);

    if( out_width != NULL ) (*out_width) = get_width ;
    if( out_height != NULL ) (*out_height) = get_height ;

    return ret ;
}

int Ensemble_Tool_Option_InspectColor_Histogram_GetImage(const std::string option_id, const int color_num, const int type_option,  const int width, const int height, unsigned char** data)
{
	int fixed_width = width ;
    int fixed_height = height ;

    return g_cls_interface_control.Tool_Option_InspectColor_Histogram_GetImage(option_id, color_num, type_option, fixed_width, fixed_height, data);
}

int Ensemble_Tool_Option_InspectColor_Histogram_GetImage(const std::string option_id, const int color_num, const int type_option, unsigned char** data, int* out_width, int* out_height)
{
	int get_width = -1 ;
    int get_height = -2 ;

    int ret = g_cls_interface_control.Tool_Option_InspectColor_Histogram_GetImage(option_id, color_num, type_option, get_width, get_height, data);

    if( out_width != NULL ) (*out_width) = get_width ;
    if( out_height != NULL ) (*out_height) = get_height ;

    return ret ;
}

int Ensemble_Tool_Option_InspectColor_Set_Histogram_UseElement(const std::string option_id, const int color_elem)
{
	return g_cls_interface_control.Tool_Option_InspectColor_Set_Histogram_UseElement(option_id, color_elem);
}

int Ensemble_Tool_Option_InspectColor_Get_Histogram_UseElement(const std::string option_id) 
{
	return g_cls_interface_control.Tool_Option_InspectColor_Get_Histogram_UseElement(option_id);
}

int Ensemble_Tool_Option_InspectColor_Set_Histogram_Range(const std::string option_id, const int color_elem, const float min, const float max)
{
	return g_cls_interface_control.Tool_Option_InspectColor_Set_Histogram_Range(option_id, color_elem, min, max);
}

int Ensemble_Tool_Option_InspectColor_Get_Histogram_Range(const std::string option_id, const int color_elem, int* out_min, int* out_max)
{
	return g_cls_interface_control.Tool_Option_InspectColor_Get_Histogram_Range(option_id, color_elem, out_min, out_max);
}

int Ensemble_Tool_Option_InspectColor_Get_Base_Pixel_Count(const std::string option_id)
{
	return g_cls_interface_control.Tool_Option_InspectColor_Get_Base_Pixel_Count(option_id);
}

int Ensemble_Tool_Option_InspectColor_Get_Tolerance(const std::string option_id, int* out_min, int* out_max)
{
	return g_cls_interface_control.Tool_Option_InspectColor_Get_Tolerance(option_id, out_min, out_max) ;
}

int Ensemble_Tool_Option_InspectColor_Set_Tolerance(const std::string option_id, const int min, const int max)
{
	return g_cls_interface_control.Tool_Option_InspectColor_Set_Tolerance(option_id, min, max) ;
}

int Ensemble_Tool_Option_InspectDistance_Get_Tolerance(const std::string option_id, float* out_min, float* out_max)
{
	return g_cls_interface_control.Tool_Option_InspectDistance_Get_Tolerance(option_id, out_min, out_max) ;
}

int Ensemble_Tool_Option_InspectDistance_Set_Tolerance(const std::string option_id, const float min, const float max)
{
	return g_cls_interface_control.Tool_Option_InspectDistance_Set_Tolerance(option_id, min, max) ;
}

std::string Ensemble_Tool_Option_InspectDistance_Get_ID_Info_Base(const std::string option_id)
{
	return g_cls_interface_control.Tool_Option_InspectDistance_Get_ID_Info_Base(option_id) ;
}

std::string Ensemble_Tool_Option_InspectDistance_Get_ID_Info_Target(const std::string option_id)
{
	return g_cls_interface_control.Tool_Option_InspectDistance_Get_ID_Info_Target(option_id) ;
}

int Ensemble_Tool_Option_InspectAngle_Get_Tolerance(const std::string option_id, float* out_min, float* out_max)
{
	return g_cls_interface_control.Tool_Option_InspectAngle_Get_Tolerance(option_id, out_min, out_max) ;
}

int Ensemble_Tool_Option_InspectAngle_Set_Tolerance(const std::string option_id, const float min, const float max)
{
	return g_cls_interface_control.Tool_Option_InspectAngle_Set_Tolerance(option_id, min, max) ;
}

std::string Ensemble_Tool_Option_InspectAngle_Get_ID_Info_Base(const std::string option_id)
{
	return g_cls_interface_control.Tool_Option_InspectAngle_Get_ID_Info_Base(option_id) ;
}

std::string Ensemble_Tool_Option_InspectAngle_Get_ID_Info_Target(const std::string option_id)
{
	return g_cls_interface_control.Tool_Option_InspectAngle_Get_ID_Info_Target(option_id) ;
}

float Ensemble_Tool_Circle_Get_CalcDiameter(const std::string tool_id)
{
    return g_cls_interface_control.Tool_Circle_Get_CalcDiameter(tool_id) ;
}

int Ensemble_Tool_Option_InspectDiameter_Get_Tolerance(const std::string option_id, float* out_min, float* out_max)
{
    return g_cls_interface_control.Tool_Option_InspectDiameter_Get_Tolerance(option_id, out_min, out_max) ;
}

int Ensemble_Tool_Option_InspectDiameter_Set_Tolerance(const std::string option_id, const float min, const float max)
{
    return g_cls_interface_control.Tool_Option_InspectDiameter_Set_Tolerance(option_id, min, max) ;
}

int Ensemble_Tool_Get_FeatureLevel(const std::string tool_id)
{
	return g_cls_interface_control.ToolGetFeatureLevel(tool_id);
}

int Ensemble_Tool_Set_FeatureLevel(const std::string tool_id, const int level)
{
	return g_cls_interface_control.ToolSetFeatureLevel(tool_id, level);
}

int Ensemble_Tool_Get_UseCustomFeatureOption(const std::string id)
{
	return g_cls_interface_control.ToolGetUseCustomFeatureOption(id) ;
}

int Ensemble_Tool_Set_UseCustomFeatureOption(const std::string id, const bool b_use)
{
	return g_cls_interface_control.ToolSetUseCustomFeatureOption(id, b_use) ;
}

int Ensemble_Tool_Get_Feature_Option(const std::string id, int* out_param1, int* out_param2, int* out_param3, int* out_param4)
{
	return g_cls_interface_control.Tool_Get_Feature_Option(id, out_param1, out_param2, out_param3, out_param4) ;
}

int Ensemble_Tool_Set_Feature_Option(const std::string id, const int param1, const int param2, const int param3, const int param4)
{
	return g_cls_interface_control.Tool_Set_Feature_Option(id, param1, param2, param3, param4) ;
}

int Ensemble_Tool_Option_Crack_Get_InspectLevel(const std::string option_id)
{
	return g_cls_interface_control.Tool_Option_Crack_GetInspectLevel(option_id);
}

int Ensemble_Tool_Option_Crack_Set_InspectLevel(const std::string option_id, const int level)
{
	return g_cls_interface_control.Tool_Option_Crack_SetInspectLevel(option_id, level);
}


int Ensemble_Job_Run(const std::string id, const float masking_left_top_x, const float masking_left_top_y, const float masking_right_top_x, const float masking_right_top_y, const float masking_right_bottom_x, const float masking_right_bottom_y, const float masking_left_bottom_x, const float masking_left_bottom_y)
{
	return g_cls_interface_control.JobRun(id, masking_left_top_x, masking_left_top_y, masking_right_top_x, masking_right_top_y, masking_right_bottom_x, masking_right_bottom_y, masking_left_bottom_x, masking_left_bottom_y) ;
}

std::string Ensemble_Tool_Get_OptionList(const std::string tool_id)
{
	return g_cls_interface_control.ToolGetOptionList(tool_id) ;
}

std::string Ensemble_Tool_Get_OptionList(const int type)
{
	return g_cls_interface_control.ToolGetOptionList(type) ;
}

int Ensemble_Tool_Get_OptionList_Count(const int type)
{
	return g_cls_interface_control.ToolGetOptionCount(type) ;
}

int Ensemble_Tool_Add_NewOption(const std::string tool_id, const int option_type)
{	
	return g_cls_interface_control.ToolAddNewOption(tool_id, option_type) ;
}

int Ensemble_Tool_Del_Option(const std::string option_id)
{
	return g_cls_interface_control.ToolDelOption(option_id) ;
}

int Ensemble_Job_Calibration_Add(const std::string job_id, float robot_x, float robot_y)
{
	return g_cls_interface_control.Calibration_Add(job_id, robot_x, robot_y);
}

int Ensemble_Job_Calibration_Get_Chess_Info(const std::string job_id, int *out_x_num, int *out_y_num, int *out_squre_mm_size)
{
	return g_cls_interface_control.Calibration_Get_Chess_Info(job_id, out_x_num, out_y_num, out_squre_mm_size) ;
}

int Ensemble_Job_Calibration_Set_Chess_Info(const std::string job_id, const int x_num, const int y_num, const int squre_mm_size)
{
	return g_cls_interface_control.Calibration_Set_Chess_Info(job_id, x_num, y_num, squre_mm_size) ;
}

int Ensemble_Job_Calibration_GetCount(const std::string job_id)
{
	return g_cls_interface_control.Calibration_GetCount(job_id);
}

int Ensemble_Job_Calibration_GetImage(const std::string job_id, const int index, const int type_option, const int width, const int height, unsigned char** data)
{
    int fixed_width = width ;
    int fixed_height = height ;

    return g_cls_interface_control.Calibration_GetImage(job_id, index, type_option, fixed_width, fixed_height, data);
}

int Ensemble_Job_Calibration_GetImage(const std::string job_id, const int index, const int type_option, unsigned char** data, int* out_width, int* out_height)
{
    int get_width = -1 ;
    int get_height = -2 ;

    int ret = g_cls_interface_control.Calibration_GetImage(job_id, index, type_option, get_width, get_height, data);

    if( out_width != NULL ) (*out_width) = get_width ;
    if( out_height != NULL ) (*out_height) = get_height ;

    return ret ;
}

int Ensemble_Job_Calibration_GetRobotInfo(const std::string job_id, int index, float *out_robot_x, float *out_robot_y)
{
	return g_cls_interface_control.Calibration_GetRobotInfo(job_id, index, out_robot_x, out_robot_y);
}

int Ensemble_Job_Calibration_Del(const std::string job_id, int index)
{
	return g_cls_interface_control.Calibration_Del(job_id, index);
}

int Ensemble_Job_Calibration_Clear(const std::string job_id)
{
	return g_cls_interface_control.Calibration_Clear(job_id);
}

int Ensemble_Job_Calibration_Run(const std::string job_id)
{
	return g_cls_interface_control.Calibration_Run(job_id);
}

int Ensemble_Job_Calibration_StandAlone_Init(const std::string job_id)
{
	return g_cls_interface_control.Calibration_StandAlone_Init(job_id);
}

int Ensemble_Job_Calibration_StandAlone_Run(const std::string job_id)
{
	return g_cls_interface_control.Calibration_StandAlone_Run(job_id);
}

int Ensemble_Job_Calibration_StandAlone_Get_Image_Count(const std::string job_id)
{
	return g_cls_interface_control.Calibration_StandAlone_Get_Image_Count(job_id);
}

int Ensemble_Job_Calibration_StandAlone_Get_Feature_Pos(const std::string job_id, int index, float posA[3], float posB[3], float posC[3], float posD[3])
{
	return g_cls_interface_control.Calibration_StandAlone_Get_Feature_Pos(job_id, index,posA, posB, posC, posD);
}

int Ensemble_Job_Calibration_StandAlone_Set_Matrix(const std::string job_id, float matrix[12])
{
	return g_cls_interface_control.Calibration_StandAlone_Set_Matrix(job_id, matrix);	
}

int Ensemble_Job_Calibration_StandAlone_Get_Matrix(const std::string job_id, float matrix[12])
{
	return g_cls_interface_control.Calibration_StandAlone_Get_Matrix(job_id, matrix);
}


int Ensemble_Job_Calibration_StandAlone_Calc_Calib_Matrix(const std::string job_id, 
	float cposA[3], float cposB[3], float cposC[3], float cposD[3],
	float rposA[3], float rposB[3], float rposC[3], float rposD[3],
	float ret_Matrix[12])
{
	return g_cls_interface_control.Calibration_StandAlone_Calc_Calib_Matrix(job_id, cposA, cposB, cposC, cposD, rposA, rposB, rposC, rposD, ret_Matrix);
}

int Ensemble_Job_Calibration_StandAlone_Y_Direction(const std::string job_id, int Direction)
{
	return g_cls_interface_control.Calibration_StandAlone_Y_Direction(job_id, Direction);
}

int Ensemble_Job_Calibration_Custom_Center_Point(const std::string job_id, int customnum)
{
	return g_cls_interface_control.Calibration_Custom_Center_Point(job_id, customnum);
}

int Ensemble_Job_Calibration_GetPoint(const std::string job_id, const float in_px, const float in_py, float* out_rx, float* out_ry)
{
	return g_cls_interface_control.Calibration_GetPoint(job_id, in_px, in_py, out_rx, out_ry);
}

int Ensemble_Job_Calibration_GetChessPoint(const std::string job_id, const int index, float* out_rx, float* out_ry)
{
	return g_cls_interface_control.Calibration_GetChessPoint(job_id, index, out_rx, out_ry);
}

int Ensemble_Job_Calibration_isOK(const std::string job_id)
{
	return g_cls_interface_control.Calibration_isOK(job_id);
}

