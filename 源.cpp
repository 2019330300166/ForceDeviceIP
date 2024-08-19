#include "../common/common.hpp"
//获取相机参数信息
void DumpParam(void* pHandle, char* pParamName);
int DumpAllParams(void* pHandle);

int main(int argc, char** argv)
{


    MV3D_RGBD_IMAGE_DATA stPointCloudImage;
    //设备版本
    MV3D_RGBD_VERSION_INFO stVersion;
    ASSERT_OK(MV3D_RGBD_GetSDKVersion(&stVersion));
    LOGD("dll version: %d.%d.%d", stVersion.nMajor, stVersion.nMinor, stVersion.nRevision);

    ASSERT_OK(MV3D_RGBD_Initialize());
    //获取设备数量
    unsigned int nDevNum = 0;
    ASSERT_OK(MV3D_RGBD_GetDeviceNumber(DeviceType_Ethernet | DeviceType_USB, &nDevNum));
    LOGD("MV3D_RGBD_GetDeviceNumber success! nDevNum:%d.", nDevNum);
    ASSERT(nDevNum);

    // 查找设备
    std::vector<MV3D_RGBD_DEVICE_INFO> devs(nDevNum);
    void* handle = NULL;
    ASSERT_OK(MV3D_RGBD_GetDeviceList(DeviceType_Ethernet | DeviceType_USB, &devs[0], nDevNum, &nDevNum));
    for (unsigned int i = 0; i < nDevNum; i++)
    {
        if (DeviceType_Ethernet == devs[i].enDeviceType)
        {
            LOG("Index[%d]. SerialNum[%s] IP[%s] name[%s].\r\n", i, devs[i].chSerialNumber, devs[i].SpecialInfo.stNetInfo.chCurrentIp, devs[i].chModelName);
        }
        else if (DeviceType_USB == devs[i].enDeviceType)
        {
            LOG("Index[%d]. SerialNum[%s] UsbProtocol[%d] name[%s].\r\n", i, devs[i].chSerialNumber, devs[i].SpecialInfo.stUsbInfo.enUsbProtocol, devs[i].chModelName);
        }
    }
    

   //打开设备
   // void* handle = NULL;
    unsigned int nIndex = 0;
    ASSERT_OK(MV3D_RGBD_OpenDevice(&handle, &devs[nIndex]));
    LOGD("OpenDevice success.");

    MV3D_RGBD_DEVICE_INFO pst;
    //获取设备详细信息
    ASSERT_OK(MV3D_RGBD_GetDeviceInfo(handle, &pst));
    LOGD("GetDeviceInfo success.");
    LOG("设备厂商：[%s] ,设备型号：[%s] ,设备版本：[%s] ",pst.chManufacturerName,pst.chModelName,pst.chDeviceVersion);

    MV3D_RGBD_CALIB_INFO pstc;
    //获取当前相机标定信息
    ASSERT_OK(MV3D_RGBD_GetCalibInfo(handle,CoordinateType_Depth, &pstc));
    LOGD("GetCalibInfo success.");
    /// 相机内参，3x3 matrix  
/// | fx|  0| cx|
/// |  0| fy| cy|
/// |  0|  0|  1|
    LOGD("\n相机内参: \n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%f\t",pstc.stIntrinsic.fData[i * 3 + j]);
        }
        printf("\n");
    }
    printf("\n相机畸变参数\n");
    //k1,k2,p1,p2,k3,k4,k5,k6,s1,s2,s3,s4
    for (int i = 0; i < 12; i++) {
        printf("%f\t",pstc.stDistortion.fData[i]);
    }
    printf("\n");


    //相机参数获取
    ASSERT_OK(DumpAllParams(handle));




    //开始工作
   ASSERT_OK(MV3D_RGBD_Start(handle));
    LOGD("Start work success.");
   
    MV3D_RGBD_FRAME_DATA stimage = {0};
    MV3D_RGBD_IMAGE_DATA image;
    MV3D_RGBD_IMAGE_DATA image1;
    //帧数据
   int net1=MV3D_RGBD_FetchFrame(handle,&stimage,5000);
   if (net1 == MV3D_RGBD_OK)
       LOGD("fetchframe success.");
   else
       LOGD("ERROR");


   //帧数据转换成点云
   if (MV3D_RGBD_OK == net1)
   {
       for (int i = 0; i < stimage.nImageCount; i++)
       {
           if (ImageType_Depth == stimage.stImageData[i].enImageType)
           {
               int net1 = MV3D_RGBD_MapDepthToPointCloud(handle, &stimage.stImageData[i], &stPointCloudImage);
               if (MV3D_RGBD_OK != net1)
               {
                   break;
                   LOGD("帧数据转点云失败");
               }
               LOGD("_MapDepthToPointCloud() Run Succeed: framenum (%d) height(%d) width(%d)  len (%d)!", stPointCloudImage.nFrameNum,
                   stPointCloudImage.nHeight, stPointCloudImage.nWidth, stPointCloudImage.nDataLen);
               /* RIFrameInfo pointCloud = { 0 };
                pointCloud.enPixelType = (RIPixelType)stPointCloudImage.enImageType;
                pointCloud.nFrameNum = stPointCloudImage.nFrameNum;
                pointCloud.nHeight = stPointCloudImage.nHeight;
                pointCloud.nWidth = stPointCloudImage.nWidth;
                pointCloud.nFrameLength = stPointCloudImage.nDataLen;
                pointCloud.pData = stPointCloudImage.pData;*/


           }
       }

   }




   //深度图 图像保存
   MV3D_RGBD_IMAGE_DATA pstImage= stimage.stImageData[0];
   const char* savepath = "C:\\Users\\Administrator\\Desktop\\depth";
   ASSERT_OK(MV3D_RGBD_SaveImage(handle,&pstImage, FileType_BMP,savepath));
   LOGD("成功保存深度图");

   system("pause");
   //停止工作
   ASSERT_OK(MV3D_RGBD_Stop(handle));
   LOGD("Stop work success.");

   //点云图像保存
   
   const char* savepath1 = "C:\\Users\\Administrator\\Desktop\\poingcloud";
   ASSERT_OK(MV3D_RGBD_SavePointCloudImage(handle, &stPointCloudImage, PointCloudFileType_PLY, savepath1));
   LOGD("成功保存点云图");

    //system("pause");
    ////停止工作
    //ASSERT_OK(MV3D_RGBD_Stop(handle));
    //LOGD("Stop work success.");



    
    ASSERT_OK(MV3D_RGBD_Release());

    LOGD("Main done!");
    system("pause");

    return  0;
}

void DumpParam(void* pHandle, char* pParamName)
{
    MV3D_RGBD_PARAM pstValue;
    int nRet = MV3D_RGBD_OK;
    memset(&pstValue, 0, sizeof(MV3D_RGBD_PARAM));
    nRet = MV3D_RGBD_GetParam(pHandle, pParamName, &pstValue);
    if (MV3D_RGBD_OK != nRet)
    {
        return ;
    }

    if (ParamType_Int == pstValue.enParamType)
    {
        LOG("ParamName : %s, Current Value: %I64d ,Max Value: %I64d ,Min Value: %I64d \r\n",
            pParamName, pstValue.ParamInfo.stIntParam.nCurValue, pstValue.ParamInfo.stIntParam.nMax,
            pstValue.ParamInfo.stIntParam.nMin);
    }
    else if (ParamType_Float == pstValue.enParamType)
    {
        LOG("ParamName : %s, Current Value: %f ,Max Value: %f ,Min Value: %f \r\n",
            pParamName, pstValue.ParamInfo.stFloatParam.fCurValue, pstValue.ParamInfo.stFloatParam.fMax,
            pstValue.ParamInfo.stFloatParam.fMin);
    }
    else if (ParamType_Enum == pstValue.enParamType)
    {
        LOG("ParamName : %s, Current Value: %d ,Supported Number: %d \r\n",
            pParamName, pstValue.ParamInfo.stEnumParam.nCurValue, pstValue.ParamInfo.stEnumParam.nSupportedNum);

        LOG("            %s Enum options :\r\n", pParamName);
        for (int i = 0; i < pstValue.ParamInfo.stEnumParam.nSupportedNum; i++)
        {
            LOG("            Support Value is [%d] \r\n", pstValue.ParamInfo.stEnumParam.nSupportValue[i]);
        }
    }
    else if (ParamType_Bool == pstValue.enParamType)
    {
        LOG("ParamName : %s, Current BoolValue: %d \r\n", pParamName, pstValue.ParamInfo.bBoolParam);
    }
    else if (ParamType_String == pstValue.enParamType)
    {
        LOG("ParamName : %s, Current String MaxLength: %d,Current String Value: %s\r\n", pParamName, pstValue.ParamInfo.stStringParam.nMaxLength,
            pstValue.ParamInfo.stStringParam.chCurValue);
    }
}

int DumpAllParams(void* pHandle)
{
    DumpParam(pHandle, MV3D_RGBD_INT_WIDTH);
    DumpParam(pHandle, MV3D_RGBD_INT_HEIGHT);
    DumpParam(pHandle, MV3D_RGBD_ENUM_WORKINGMODE);
    DumpParam(pHandle, MV3D_RGBD_ENUM_PIXELFORMAT);
    DumpParam(pHandle, MV3D_RGBD_ENUM_IMAGEMODE);
    DumpParam(pHandle, MV3D_RGBD_FLOAT_GAIN);
    DumpParam(pHandle, MV3D_RGBD_FLOAT_EXPOSURETIME);
    DumpParam(pHandle, MV3D_RGBD_FLOAT_FRAMERATE);
    DumpParam(pHandle, MV3D_RGBD_ENUM_TRIGGERSELECTOR);
    DumpParam(pHandle, MV3D_RGBD_ENUM_TRIGGERMODE);
    DumpParam(pHandle, MV3D_RGBD_ENUM_TRIGGERSOURCE);
    DumpParam(pHandle, MV3D_RGBD_FLOAT_TRIGGERDELAY);
    DumpParam(pHandle, MV3D_RGBD_INT_IMAGEALIGN);

    return MV3D_RGBD_OK;
}