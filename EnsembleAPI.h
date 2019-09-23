#ifndef ENSEMBLEAPI_H
#define ENSEMBLEAPI_H

#include "ErrorType.h"
#include "EnsembleCommon.h"
#include <string>

//[0] Connect
int EnsembleConnect(const char* ip);
void EnsembleDisconnect(void);
int EnsembleIsOnline(void);

//[1]Source
std::string EnsembleGetSourceList(void);
int EnsembleSetSource(const std::string source);


//[2] Get Image Stream
int EnsembleGetImage(const int option, const int type_option, const int width, const int height, unsigned char** data) ;
int EnsembleGetImage(const int option, const int type_option, unsigned char** data, int* out_width, int* out_height) ;


//[3] Job Management
int Ensemble_Task_Get_Run_Option(const std::string id) ;
int Ensemble_Task_Get_View_Option(const std::string id) ;
int Ensemble_Task_Set_Run_Option(const std::string id, const bool run) ;
int Ensemble_Task_Set_View_Option(const std::string id, const bool view) ;
int Ensemble_Task_File_Save(void) ;		//save all
int Ensemble_Task_File_Load(void) ;	//load all



//Project
int Ensemble_Project_Add_New(const std::string name="") ;
int Ensemble_Project_Del(const std::string proj_id="") ;
std::string Ensemble_Project_Get_List(void) ;
std::string Ensemble_Project_Get_Name(const std::string project_id) ;
int Ensemble_Project_Set_Name(const std::string project_id, const std::string name) ;




//Job
int Ensemble_Job_Add_New(const std::string project_id, const int type, const std::string name="") ;
std::string Ensemble_Job_Get_TypeName(const int job_type) ;
std::string Ensemble_Job_Type_Get_List_Xml(void) ;
int Ensemble_Job_Del(const std::string id) ;
std::string Ensemble_Job_Get_Name(const std::string id) ;
int Ensemble_Job_Set_Name(const std::string id, const std::string name) ;
int Ensemble_Job_Get_Image(const std::string id,const int type_option,  const int width, const int height, unsigned char** data) ;
int Ensemble_Job_Get_Image(const std::string id, const int type_option, unsigned char** data, int* out_width, int* out_height) ;
int Ensemble_Job_Get_ObjectImage(const std::string id,const int type_option,  const int width, const int height, unsigned char** data) ;
int Ensemble_Job_Get_ObjectImage(const std::string id, const int type_option, unsigned char** data, int* out_width, int* out_height) ;
int Ensemble_Job_Set_Image(const std::string id) ;
int Ensemble_Job_Set_DetectArea(const std::string id, const float x, const float y, const float width, const float height) ;
int Ensemble_Job_Set_Zoom(const std::string id, const float x, const float y, const float width, const float height) ;
int Ensemble_Job_Set_MaskArea(const std::string id, float x, float y, float w, float h, bool inverse);
int Ensemble_Job_Undo_MaskArea(const std::string id);
int Ensemble_Job_Del_MaskArea(const std::string id);
int Ensemble_Job_Get_FeatureLevel(const std::string id);
int Ensemble_Job_Set_FeatureLevel(const std::string id, const int level);
int Ensemble_Job_Set_SelectObject(const std::string id, const float x, const float y, const float width, const float height) ;
int Ensemble_Job_Del_SelectObject(const std::string id) ;
int Ensemble_Job_Set_DetectOption(const std::string id, const int option, const float value) ;
float Ensemble_Job_Get_DetectOption(const std::string id, const int option) ;
int Ensemble_Job_Get_ResultImage(const std::string id, const int type_option, const int width, const int height, unsigned char** data) ;
int Ensemble_Job_Get_ResultImage(const std::string id, const int type_option, unsigned char** data, int* out_width, int* out_height) ;


//Tool
int Ensemble_Tool_Add_New(const std::string parent_id, const int tool_type) ;
int EnsembleToolInsert(const std::string parent_id, const int index, const int tool_type) ;
int EnsembleToolMove(const std::string parent_id, const int from_index, const int target_index) ;
int EnsembleToolDel(const std::string tool_id) ;

//Option
int Ensemble_Tool_Option_GetImage(const std::string option_id, const int type_option,  const int width, const int height, unsigned char** data) ;
int Ensemble_Tool_Option_GetImage(const std::string option_id, const int type_option, unsigned char** data, int* out_width, int* out_height) ;

//Option Inspect Color
int Ensemble_Tool_Option_InspectColor_Histogram_GetImage(const std::string option_id, const int color_num, const int type_option,  const int width, const int height, unsigned char** data) ;
int Ensemble_Tool_Option_InspectColor_Histogram_GetImage(const std::string option_id, const int color_num, const int type_option, unsigned char** data, int* out_width, int* out_height) ;
int Ensemble_Tool_Option_InspectColor_Set_Histogram_UseElement(const std::string option_id, const int color_elem) ;
int Ensemble_Tool_Option_InspectColor_Get_Histogram_UseElement(const std::string option_id) ;
int Ensemble_Tool_Option_InspectColor_Set_Histogram_Range(const std::string option_id, const int color_elem, const float min, const float max) ;
int Ensemble_Tool_Option_InspectColor_Get_Histogram_Range(const std::string option_id, const int color_elem, int* out_min, int* out_max) ;
int Ensemble_Tool_Option_InspectColor_Get_Base_Pixel_Count(const std::string option_id) ;
int Ensemble_Tool_Option_InspectColor_Get_Tolerance(const std::string option_id, int* out_min, int* out_max) ;
int Ensemble_Tool_Option_InspectColor_Set_Tolerance(const std::string option_id, const int min, const int max) ;


//Tool Image
int EnsembleToolGetImage(const std::string tool_id, const int type_option,  const int width, const int height, unsigned char** data) ;
int EnsembleToolGetImage(const std::string tool_id, const int type_option, unsigned char** data, int* out_width, int* out_height) ;

//Tool Name
std::string EnsembleToolGetName(const std::string tool_id) ;
int EnsembleToolSetName(const std::string tool_id, const std::string name) ;

int EnsembleToolGetFeatureLevel(const std::string tool_id);
int EnsembleToolSetFeatureLevel(const std::string tool_id, const int level);

int EnsembleToolSelectObject(const std::string tool_id, const float x, const float y, const float width, const float height, const int margin=0) ;
int EnsembleToolSelectObject(const std::string tool_id, const float left_top_x, const float left_top_y, const float right_top_x, const float right_top_y, const float right_bottom_x, const float right_bottom_y, const float left_bottom_x, const float left_bottom_y, const int margin=0) ;

int EnsembleToolGetObjectImage(const std::string tool_id,const int type_option,  const int width, const int height, unsigned char** data) ;
int EnsembleToolGetObjectImage(const std::string tool_id, const int type_option, unsigned char** data, int* out_width, int* out_height) ;

//tool option
std::string EnsembleToolGetOptionList(const std::string tool_id) ;
std::string EnsembleToolGetOptionList(const int type) ;
int EnsembleToolGetOptionListCount(const int type) ;
int EnsembleToolAddNewOption(const std::string tool_id, const int option_type) ;
int EnsembleToolDelOption(const std::string option_id) ;


//Detect Tool API
int EnsembleToolSetDetectOption(const std::string tool_id,const int option, const float value) ;
float EnsembleToolGetDetectOption(const std::string tool_id,const int option) ;

//Distance Tool API
float Ensemble_Tool_Distance_Get_CalcDistance(const std::string tool_id) ;
int Ensemble_Tool_Distance_Set_BaseDistance(const std::string tool_id, const float base_distance) ;
float Ensemble_Tool_Distance_Get_BaseDistance(const std::string tool_id) ;
int Ensemble_Tool_Option_InspectDistance_Get_Tolerance(const std::string option_id, float* out_min, float* out_max) ;
int Ensemble_Tool_Option_InspectDistance_Set_Tolerance(const std::string option_id, const float min, const float max) ;
std::string Ensemble_Tool_Option_InspectDistance_Get_ID_Info_Base(const std::string option_id) ;
std::string Ensemble_Tool_Option_InspectDistance_Get_ID_Info_Target(const std::string option_id) ;

//Angle Tool API
float Ensemble_Tool_Angle_Get_CalcAngle(const std::string tool_id) ;
int Ensemble_Tool_Option_InspectAngle_Get_Tolerance(const std::string option_id, float* out_min, float* out_max) ;
int Ensemble_Tool_Option_InspectAngle_Set_Tolerance(const std::string option_id, const float min, const float max) ;
std::string Ensemble_Tool_Option_InspectAngle_Get_ID_Info_Base(const std::string option_id) ;
std::string Ensemble_Tool_Option_InspectAngle_Get_ID_Info_Target(const std::string option_id) ;

//Circle Tool API
float Ensemble_Tool_Circle_Get_CalcDiameter(const std::string tool_id) ;
int Ensemble_Tool_Option_InspectDiameter_Get_Tolerance(const std::string option_id, float* out_min, float* out_max) ;
int Ensemble_Tool_Option_InspectDiameter_Set_Tolerance(const std::string option_id, const float min, const float max) ;

//Crack Tool API
int Ensemble_Tool_Option_Crack_GetInspectLevel(const std::string option_id);
int Ensemble_Tool_Option_Crack_SetInspectLevel(const std::string option_id, const int level);

//[4] Run
int EnsembleJobRun(const std::string id) ;


std::string EnsembleGetToolList(void) ;
std::string EnsembleGetToolTypeName(const int type) ;

//[5] Calibration
int Ensemble_Job_Calibration_Get_Chess_Info(const std::string job_id, int *out_x_num, int *out_y_num, int *out_squre_mm_size);
int Ensemble_Job_Calibration_Set_Chess_Info(const std::string job_id, const int x_num, const int y_num, const int squre_mm_size);
int Ensemble_Job_Calibration_Add(const std::string job_id, float robot_x, float robot_y);
int Ensemble_Job_Calibration_GetCount(const std::string job_id);
int Ensemble_Job_Calibration_GetImage(const std::string job_id, int index, char** data, int* len);
int Ensemble_Job_Calibration_GetRobotInfo(const std::string job_id, int index, float *out_robot_x, float *out_robot_y);
int Ensemble_Job_Calibration_Del(const std::string job_id, int index);
int Ensemble_Job_Calibration_Clear(const std::string job_id);
int Ensemble_Job_Calibration_Run(const std::string job_id);
int Ensemble_Job_Calibration_StandAlone_Init(const std::string job_id);
int Ensemble_Job_Calibration_StandAlone_Run(const std::string job_id);
int Ensemble_Job_Calibration_StandAlone_Get_Image_Count(const std::string job_id);
int Ensemble_Job_Calibration_StandAlone_Get_Feature_Pos(const std::string job_id, int index, float posA[3], float posB[3], float posC[3], float posD[3]);
int Ensemble_Job_Calibration_StandAlone_Set_Matrix(const std::string job_id, float matrix[12]);
int Ensemble_Job_Calibration_StandAlone_Get_Matrix(const std::string job_id, float matrix[12]);
int Ensemble_Job_Calibration_StandAlone_Calc_Calib_Matrix(const std::string job_id, 
																			float cposA[3], float cposB[3], float cposC[3], float cposD[3],
																			float rposA[3], float rposB[3], float rposC[3], float rposD[3],
																			float ret_Matrix[12]);
int Ensemble_Job_Calibration_StandAlone_Y_Direction(const std::string job_id, int Direction);
int Ensemble_Job_Calibration_Custom_Center_Point(const std::string job_id, int customnum);
int Ensemble_Job_Calibration_GetPoint(const std::string job_id, const float in_px, const float in_py, float* out_rx, float* out_ry);
int Ensemble_Job_Calibration_GetChessPoint(const std::string job_id, const int index, float* out_rx, float* out_ry);
int Ensemble_Job_Calibration_isOK(const std::string job_id);



#endif
