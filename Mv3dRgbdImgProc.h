/***************************************************************************************************
*
* 版权信息：版权所有 (c) 2023, 杭州海康机器人股份有限公司, 保留所有权利

*   @file       Mv3dRgbdImgProc.h
*   @note       HangZhou Hikrobot Co., Ltd. All Right Reserved.
*   @brief      RGBD camera image processing
*
*   @date       2023/03/10
*   @note       V1.2.0 
*   
*   @warning    版权所有
****************************************************************************************************/

#ifndef _MV3D_RGBD_IMG_PROC_H_
#define _MV3D_RGBD_IMG_PROC_H_

#include "Mv3dRgbdDefine.h"

/************************************************************************
 *  @fn     MV3D_RGBD_MapDepthToPointCloud()
 *  @brief  RGBD相机深度图像转换点云图像  
 *  @param  handle                  [IN]            句柄地址
 *  @param  pstDepthImage           [IN]            输入深度图数据
 *  @param  pstPointCloudImage      [OUT]           输出点云图数据
 *  @return 成功，返回MV3D_RGBD_OK；错误，返回错误码 

 *  @fn     MV3D_RGBD_MapDepthToPointCloud()
 *  @brief  depth image convert to pointcloud image
 *  @param  handle                  [IN]            handle address
 *  @param  pstDepthImage           [IN]            In Depth  data
 *  @param  pstPointCloudImage      [OUT]           Out Point Cloud data
 *  @return Success, return MV3D_RGBD_OK. Failure,return error code
************************************************************************/
MV3D_RGBD_API MV3D_RGBD_STATUS  MV3D_RGBD_MapDepthToPointCloud(void* handle, MV3D_RGBD_IMAGE_DATA* pstDepthImage, MV3D_RGBD_IMAGE_DATA* pstPointCloudImage);

/************************************************************************
*  @fn     MV3D_RGBD_SaveImage()
*  @brief  深度图和RGB图存图接口
*  @param  handle                   [IN]            句柄地址
*  @param  pstImage                 [IN]            图像数据
*  @param  enFileType               [IN]            文件类型
*  @param  chFileName               [IN]            文件名称
*  @return 成功，返回MV3D_RGBD_OK；错误，返回错误码 

*  @fn     MV3D_RGBD_SaveImage()
*  @brief  depth and rgb image save image to file
*  @param  handle                   [IN]            handle address
*  @param  pstImage                 [IN]            image data 
*  @param  enFileType               [IN]            file type
*  @param  chFileName               [IN]            file name
*  @return Success, return MV3D_RGBD_OK. Failure, return error code
************************************************************************/
MV3D_RGBD_API MV3D_RGBD_STATUS MV3D_RGBD_SaveImage(void* handle, MV3D_RGBD_IMAGE_DATA* pstImage, Mv3dRgbdFileType enFileType, const char* chFileName);

/************************************************************************
*  @fn     MV3D_RGBD_SavePointCloudImage()
*  @brief  点云图存图接口
*  @param  handle                   [IN]            句柄地址
*  @param  pstImage                 [IN]            图像数据
*  @param  enPointCloudFileType     [IN]            点云图文件类型
*  @param  chFileName               [IN]            文件名称
*  @return 成功，返回MV3D_RGBD_OK；错误，返回错误码 

*  @fn     MV3D_RGBD_SavePointCloudImage()
*  @brief  pointcloud image save image to file
*  @param  handle                   [IN]            handle address
*  @param  pstImage                 [IN]            image data 
*  @param  enPointCloudFileType     [IN]            pointcloud image file type
*  @param  chFileName               [IN]            file name
*  @return Success, return MV3D_RGBD_OK. Failure, return error code
************************************************************************/
MV3D_RGBD_API MV3D_RGBD_STATUS MV3D_RGBD_SavePointCloudImage(void* handle, MV3D_RGBD_IMAGE_DATA* pstImage, Mv3dRgbdPointCloudFileType enPointCloudFileType, const char* chFileName);

/************************************************************************
*  @fn     MV3D_RGBD_DisplayImage()
*  @brief  显示深度和RGB图像接口
*  @param  handle                   [IN]            句柄地址
*  @param  pstImage                 [IN]            图像数据
*  @param  hWnd                     [IN]            窗口句柄
*  @return 成功，返回MV3D_RGBD_OK；错误，返回错误码 

*  @fn     MV3D_RGBD_DisplayImage()
*  @brief  display depth and rgb image api
*  @param  handle                   [IN]            handle address
*  @param  pstImage                 [IN]            image data 
*  @param  hWnd                     [IN]            windows handle
*  @return Success, return MV3D_RGBD_OK. Failure, return error code
************************************************************************/
MV3D_RGBD_API MV3D_RGBD_STATUS MV3D_RGBD_DisplayImage(void* handle, MV3D_RGBD_IMAGE_DATA* pstImage, void* hWnd);

#endif