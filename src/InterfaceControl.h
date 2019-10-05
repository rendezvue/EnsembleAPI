#ifndef INTERFACE_CONTROL_H
#define INTERFACE_CONTROL_H

#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread.hpp>

#include "EnsembleCommand.h"
#include "Interface.h"
#include "EthernetClient.h"
#include "EthernetClientControlData.h"

#include <qdebug.h>

#define TRANS_IAMGE_WIDTH		640
#define TRANS_IAMGE_HEIGHT		480

class  CInterfaceControl : public CInterface
{
public:
	CInterfaceControl(void);
	~CInterfaceControl(void);

	//-----------------------------
	//Image and Source
    int GetImage(const int option, std::string id, const int type_option, int& width, int& height, unsigned char** out_data);
	int GetResultImage(const std::string id, const int type_option, int& width, int& height, unsigned char** out_data);
	std::string GetSourceList(void) ;
	int SetSource(const std::string source) ;
	//Image and Source
	//-----------------------------
	
	int Get_Run_Option(const std::string id) ;
	int Get_View_Option(const std::string id) ;
	int Base_Set_Run_Option(const std::string id, const bool run) ;
	int Base_Set_View_Option(const std::string id, const bool view) ;
	int Task_Save(void) ;
	int Task_Load(void) ;

	int Project_Add_New(const std::string name) ;
	int Project_Del(const std::string id) ;
	std::string Project_Get_List(void) ;
	std::string Project_Get_Name(const std::string id) ;
	int Project_Set_Name(const std::string id, const std::string name) ;

	std::string Job_Type_Get_List_Xml(void) ;
		
	int Job_Add_New(const std::string project_id, const int type, const std::string name) ;
	std::string Job_Get_TypeName(const int job_type);
	
	int DelJob(const std::string id) ;
	std::string JobGetName(const std::string id) ;
	int JobChangeName(const std::string id, const std::string name) ;
	int JobGetImage(const std::string id, const int type_option, int& width, int& height, unsigned char** out_data) ;
	int JobGetObjectImage(const std::string id, const int type_option, int& width, int& height, unsigned char** out_data) ;
	int JobSetImage(const std::string id) ;
	int JobSetDetectArea(const std::string id, const float x, const float y, const float width, const float height) ;
	int JobSetZoom(const std::string id, const float x, const float y, const float width, const float height) ;
	int JobSelectObject(const std::string id, const float x, const float y, const float width, const float height) ;
	int JobSetDetectOption(const std::string id, const int option, const float value) ;
	float JobGetDetectOption(const std::string id, const int option) ;
	int JobResetObject(const std::string id) ;
	int JobSetMaskArea(const std::string id, float x, float y, float w, float h, bool inverse);
	int JobUndoMaskArea(const std::string id);
	int JobDelMaskArea(const std::string id);
	int JobGetFeatureLevel(const std::string id);
	int JobSetFeatureLevel(const std::string id, const int level);

	int JobRun(const std::string id);

	//Calibration
	int Calibration_Get_Chess_Info(const std::string job_id, int *out_x_num, int *out_y_num, int *out_squre_mm_size) ;
	int Calibration_Set_Chess_Info(const std::string job_id, const int x_num, const int y_num, const int squre_mm_size) ;
	int Calibration_Add(const std::string job_id, float robot_x, float robot_y) ;
	int Calibration_GetCount(const std::string job_id) ;
	int Calibration_GetImage(const std::string job_id, int index, const int type_option, int& width, int& height, unsigned char** out_data) ;
	int Calibration_GetRobotInfo(const std::string job_id, int index, float *out_robot_x, float *out_robot_y);
	int Calibration_Del(const std::string job_id, int index);
	int Calibration_Clear(const std::string job_id);
	int Calibration_Run(const std::string job_id);
	int Calibration_Custom_Center_Point(const std::string job_id, int customnum); 
	int Calibration_GetPoint(const std::string job_id, const float in_px, const float in_py, float* out_rx, float* out_ry);
	int Calibration_GetChessPoint(const std::string job_id, const int index, float* out_rx, float* out_ry);
	int Calibration_isOK(const std::string job_id);
	int Calibration_StandAlone_Run(const std::string job_id);
	int Calibration_StandAlone_Get_Image_Count(const std::string job_id);
	int Calibration_StandAlone_Init(const std::string job_id);
	int Calibration_StandAlone_Get_Feature_Pos(const std::string job_id, int index,float posA[3], float posB[3], float posC[3], float posD[3]);
	int Calibration_StandAlone_Set_Matrix(const std::string job_id, float matrix[12]);
	int Calibration_StandAlone_Get_Matrix(const std::string job_id, float matrix[12]);
	int Calibration_StandAlone_Calc_Calib_Matrix(const std::string job_id, 
															float cposA[3], float cposB[3], float cposC[3], float cposD[3],
															float rposA[3], float rposB[3], float rposC[3], float rposD[3],
															float ret_Matrix[12]);
	int Calibration_StandAlone_Y_Direction(const std::string job_id, int Direction);

	
	std::string GetToolList(void) ;
    std::string GetToolTypeName(const int type) ;
	int AddTool(const std::string parent_id, const int tool_type) ;
	int InsertTool(const std::string parent_id, const int index, const int tool_type) ;
	int MoveTool(const std::string parent_id, const int cur_index, const int target_index) ;
	int DelTool(const std::string tool_id) ;

	//Tool Option
	int OptionGetImage(const std::string option_id, const int type_option, int& width, int& height, unsigned char** out_data) ;

	//Tool Option : Inspect Color
	int Tool_Option_InspectColor_Histogram_GetImage(const std::string option_id, const int color_num, const int type_option, int& width, int& height, unsigned char** out_data) ;
	int Tool_Option_InspectColor_Set_Histogram_UseElement(const std::string option_id, const int color_elem) ;
	int Tool_Option_InspectColor_Get_Histogram_UseElement(const std::string option_id) ;
	int Tool_Option_InspectColor_Set_Histogram_Range(const std::string option_id, const int color_elem, const float min, const float max) ;
	int Tool_Option_InspectColor_Get_Histogram_Range(const std::string option_id, const int color_elem, int* out_min, int* out_max) ;
	int Tool_Option_InspectColor_Get_Base_Pixel_Count(const std::string option_id) ;
	int Tool_Option_InspectColor_Get_Tolerance(const std::string option_id, int* out_min, int* out_max) ;
	int Tool_Option_InspectColor_Set_Tolerance(const std::string option_id, const int min, const int max) ;

	//Tool Option : Inspect Distance
	int Tool_Option_InspectDistance_Get_Tolerance(const std::string option_id, float* out_min, float* out_max) ;
	int Tool_Option_InspectDistance_Set_Tolerance(const std::string option_id, const float min, const float max) ;
	std::string Tool_Option_InspectDistance_Get_ID_Info_Base(const std::string option_id) ;
	std::string Tool_Option_InspectDistance_Get_ID_Info_Target(const std::string option_id) ;

	//Tool Option : Inspect Angle
	int Tool_Option_InspectAngle_Get_Tolerance(const std::string option_id, float* out_min, float* out_max) ;
	int Tool_Option_InspectAngle_Set_Tolerance(const std::string option_id, const float min, const float max) ;
	std::string Tool_Option_InspectAngle_Get_ID_Info_Base(const std::string option_id) ;
	std::string Tool_Option_InspectAngle_Get_ID_Info_Target(const std::string option_id) ;

	//Tool Option : Inspect Diameter
	float Tool_Circle_Get_CalcDiameter(const std::string tool_id) ;
	int Tool_Option_InspectDiameter_Get_Tolerance(const std::string option_id, float* out_min, float* out_max) ;
	int Tool_Option_InspectDiameter_Set_Tolerance(const std::string option_id, const float min, const float max) ;
	
	////
	int ToolGetImage(const std::string tool_id, const int type_option, int& width, int& height, unsigned char** out_data) ;
	std::string ToolGetName(const std::string tool_id) ;
	int ToolSetName(const std::string tool_id, const std::string name) ;

	int ToolGetFeatureLevel(const std::string tool_id) ;
	int ToolSetFeatureLevel(const std::string tool_id, const int level) ;

	//crack
	int Tool_Option_Crack_GetInspectLevel(const std::string option_id) ;
	int Tool_Option_Crack_SetInspectLevel(const std::string option_id, const int level) ;

	//object
	int ToolSelectObject(const std::string tool_id, const float x, const float y, const float width, const float height, const int margin=0) ;
	int ToolSelectObject(const std::string tool_id, const float left_top_x, const float left_top_y, const float right_top_x, const float right_top_y, const float right_bottom_x, const float right_bottom_y, const float left_bottom_x, const float left_bottom_y, const int margin=0)  ;
	int ToolGetObjectImage(const std::string tool_id, const int type_option, int& width, int& height, unsigned char** out_data) ;

	//object detct
	int ToolSetDetectOption(const std::string tool_id, const int option, const float value) ;
	float ToolGetDetectOption(const std::string tool_id, const int option) ;

	std::string ToolGetOptionList(const std::string tool_id) ;
	std::string ToolGetOptionList(const int tool_type) ;
	int ToolGetOptionCount(const int tool_type) ;
	int ToolAddNewOption(const std::string tool_id, const int option_type) ;
	int ToolDelOption(const std::string option_id) ;
		
	//////////////////
 };

#endif
