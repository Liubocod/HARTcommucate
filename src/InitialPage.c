/**************************************************************************/

/**************************************************************************/

/****** CONNETECH Electronics Ltd(BeijingRuiDaYiBiaoYouXianGongSi)  ****************/

/**************************************************************************/

/**************************************************************************/

/* Declaration:        */

/*  We (CONNETECH Electronics Ltd��BeijingRuiDaYiBiaoYouXianGongSi)  has the copyright of the following software  */

/*  all the copyright, patent, trademark, trade secret or any other intellectual property infringement of following software belong to CONNETECH Electronics Ltd��BeijingRuiDaYiBiaoYouXianGongSi */

/*  all the copyright, patent, trademark, trade secret or any other intellectual property infringement of following software are the top secret of CONNETECH Electronics Ltd(BeijingRuiDaYiBiaoYouXianGongSi) */

/*  All the behaviors to read, use, copy, change, publish the software are illegal. And all rights reserved */

#include "InitialPage.h"
bool8 G_IsInitVariable = FALSE;
uchar G_PV_UnitTemp[UCHAR] = {0};
//����PDS 5ϵ�ߵͶ�΢�������ж�
#define IS_CY_PDS6_PATCH_UST       (MENU_CurrentPageNumGet() == CY_PAGE_INDEX_14)\
     &&(MENU_CurrentPageTypeGet() == MENU_BAR)&&(MENU_GetMenuTreeIndex() == CHUAN_YI)
//����PDS 8ϵ�ߵͶ�΢�������ж�
#define IS_CY_PDS7_PATCH_UST       (MENU_CurrentPageNumGet() == CY7_PAGE_INDEX_41)\
     &&(MENU_CurrentPageTypeGet() == MENU_BAR)&&(MENU_GetMenuTreeIndex() == CY_HART7_PDS)

/*
void HART_SuccessRatioHandle(void )
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
  �ɹ��ʼ��㴦������������������㣬Ȼ������һ�ּ��㡣
*
* �ؼ���ע��
* - 

  
* δ�����:


*/ 
static void HART_SuccessRatioHandle()
{
  G_SuccessNum = 0;
  G_FailureStatistics = 0;
  G_Denominator = 0;
  //�����ɹ��ʼ��㴦����
  G_ComPCT_SWITCH = TRUE;
  MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
  MENU_PageTypeSetHandle(DYNAMIC_PAGE);
  MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_102);
}
/*
static void InitialPageVariableInit();
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
HARTͨ�ű�����ʼ��������
��ͬ��Ʒ��Ҫ���в�ͬ�ı�����ʼ�������Կ�ͨ���������ֱ���д���
*
* �ؼ���ע��
* - 

  
* δ�����:




*/
void InitialPageVariableInit()
{
  uchar i;

  if(IS_CY_PDS6_PATCH_UST || IS_CY_PDS7_PATCH_UST)
  {
    for(i = 0;i < 4;i++)
    {
      G_SIEMENS_UpSnsrTrim[i] = G_PV_USL[i];
      G_SIEMENS_LoSnsrTrim[i] = G_PV_LSL[i];
    }
    G_IsInitVariable = TRUE;
    G_PV_UnitTemp[0] = G_PV_Unit[0];
  }
}
/*
static void InitialPageVariableInit();
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
HARTͨ�ű�����ʼ��������
��ͬ��Ʒ��Ҫ���в�ͬ�ı�����ʼ�������Կ�ͨ���������ֱ���д���
*
* �ؼ���ע��
* - 

  
* δ�����:




*/
bool8 InitialPageRangeCompare()
{
  uchar i;
  for(i = 0;i < 4;i++)
  {
    if((G_SIEMENS_UpSnsrTrim[i] != G_PV_USL[i])
       ||(G_SIEMENS_LoSnsrTrim[i] != G_PV_LSL[i]))
    {
      return FALSE;
    }
  }
  return TRUE;
}
/*
void HART_DeviceTypeHandle()
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
  �豸���ͽ����������������豸Ψһ�룬���־���Ϊ�����豸��
    �汾����ִ����ϣ������豸���ʹ��������в˵����ѡ��
*
* �ؼ���ע��
* - 

  
* δ�����:


*/ 
static void HART_DeviceTypeHandle()
{
  ProductTypeAndID_Def   ProductType;
  ProductType = HART_GetProductTypeAndID();
  switch (ProductType)
  {
      case  SIEMENS_TYPE1:
      if(HART_VersionGet() == HART_VERSION_6)
      {
        MENU_PageIndexSetHandle(SIEMENS);
        MENU_PageTypeSetHandle(WAITING_PAGE);
        MENU_PageNumSetHandle(SMS_PAGE_INDEX_149);
      }
      else
      {
        //��ת����ʼ������ɹ����������
        MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
        MENU_PageTypeSetHandle(WAITING_PAGE);
        MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_108);
      }
      break;
      case  HW_TYPE1:
      if(HART_VersionGet() == HART_VERSION_7)
      {
        MENU_PageIndexSetHandle(HW);
        MENU_PageTypeSetHandle(WAITING_PAGE);
        MENU_PageNumSetHandle(HW_PAGE_INDEX_0);
      }
      else
      {
        //��ת����ʼ������ɹ����������
        MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
        MENU_PageTypeSetHandle(WAITING_PAGE);
        MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_108);
      }
      break;
      case  EJA530_TYPE1:
      if(HART_VersionGet() == HART_VERSION_5)
      {
        MENU_PageIndexSetHandle(EJA530E);
        MENU_PageTypeSetHandle(WAITING_PAGE);
        MENU_PageNumSetHandle(EJA_PAGE_INDEX_0);
      }
      else
      {
        //��ת����ʼ������ɹ����������
        MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
        MENU_PageTypeSetHandle(WAITING_PAGE);
        MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_108);
      }
      break;
      case  EJA_TYPE1:
      if(HART_VersionGet() == HART_VERSION_5)
      {
        MENU_PageIndexSetHandle(EJA);
        MENU_PageTypeSetHandle(WAITING_PAGE);
        MENU_PageNumSetHandle(EA_PAGE_INDEX_0);
      }
      else
      {
        //��ת����ʼ������ɹ����������
        MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
        MENU_PageTypeSetHandle(WAITING_PAGE);
        MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_108);
      }
      break;
      case  LM_TYPE1:
      if(HART_VersionGet() == HART_VERSION_5)
      {
        MENU_PageIndexSetHandle(LM);
        MENU_PageTypeSetHandle(WAITING_PAGE);
        MENU_PageNumSetHandle(LM_PAGE_INDEX_0);
      }
      else
      {
        //��ת����ʼ������ɹ����������
        MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
        MENU_PageTypeSetHandle(WAITING_PAGE);
        MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_108);
      }
      break;
      case  CHUAN_YI_TYPE1://����PDS
      if(HART_VersionGet() == HART_VERSION_6)
      {
        MENU_PageIndexSetHandle(CHUAN_YI);
        MENU_PageTypeSetHandle(WAITING_PAGE);
        MENU_PageNumSetHandle(CY_PAGE_INDEX_109);
      }
      else if(HART_VersionGet() == HART_VERSION_7)
      {
        //���ԣ������޸�
        MENU_PageIndexSetHandle(CY_HART7_PDS);
        MENU_PageTypeSetHandle(WAITING_PAGE);
        MENU_PageNumSetHandle(CY7_PAGE_INDEX_171);
      }
      else
      {
        //��ת����ʼ������ɹ����������
        MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
        MENU_PageTypeSetHandle(WAITING_PAGE);
        MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_108);
      }
      break;
      case  RADAR_TYPE1:
      if(HART_VersionGet() == HART_VERSION_5)
      {
        MENU_PageIndexSetHandle(RADAR);
        MENU_PageTypeSetHandle(WAITING_PAGE);
        MENU_PageNumSetHandle(RADAR_PAGE_INDEX_85);
      }
      else
      {
        //��ת����ʼ������ɹ����������
        MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
        MENU_PageTypeSetHandle(WAITING_PAGE);
        MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_108);
      }
      break;
//TTS
      case  CHUAN_YI_TYPE2:
      if(HART_VersionGet() == HART_VERSION_6)
      {
        MENU_PageIndexSetHandle(CHUAN_YI_T1);
        MENU_PageTypeSetHandle(WAITING_PAGE);
        MENU_PageNumSetHandle(CY_T1_PAGE_INDEX_109);
      }
      else
      {
        //��ת����ʼ������ɹ����������
        MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
        MENU_PageTypeSetHandle(WAITING_PAGE);
        MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_108);
      }
      break;
//HVP
      case  CHUAN_YI_HVPID:
      if(HART_VersionGet() == HART_VERSION_7)
      {
        MENU_PageIndexSetHandle(CHUAN_YI_HVP);
        MENU_PageTypeSetHandle(WAITING_PAGE);
        MENU_PageNumSetHandle(CY_HVP_PAGE_INDEX_129);
      }
      else if(HART_VersionGet() == HART_VERSION_5)
      {
        MENU_PageIndexSetHandle(CHUAN_YI_HVP5);
        MENU_PageTypeSetHandle(WAITING_PAGE);
        MENU_PageNumSetHandle(CY_HVP5_PAGE_INDEX_129);
      }
      else
      {
        //��ת����ʼ������ɹ����������
        MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
        MENU_PageTypeSetHandle(WAITING_PAGE);
        MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_108);
      }
      break;
//
      case  RAYDAR_80G:
      if(HART_VersionGet() == HART_VERSION_7)
      {
        MENU_PageIndexSetHandle(RAYDAR80G1_0);
        MENU_PageTypeSetHandle(WAITING_PAGE);
        MENU_PageNumSetHandle(RAYDAR80G1_0_PAGE_INDEX_0);
      }
      else
      {
        //��ת����ʼ������ɹ����������
        MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
        MENU_PageTypeSetHandle(WAITING_PAGE);
        MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_108);
      }
      break;
      default:
             //��ת����ʼ������ɹ����������
        MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
        MENU_PageTypeSetHandle(WAITING_PAGE);
        MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_108);
      break;
  }
  
}
/*
void HART_InitialpageHandle(void )
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
��ʼ��ҳ�洦������
�ú��������ǣ�ȷ����ʼ��ҳ���������ӳɹ���ʧ�ܺ�ִ����Щ�����Լ���ʾ��Щҳ�档
*
* �ؼ���ע��
* - 

  
* δ�����:
�����Ӷ�˵��������ܻ�Ҫ������������ת���档
  uint CurrentMenuTreeIndex;
  uint CurrentPageNum;
  PageTypeDef PageType;
  LanguageTypeDef Language;

*/ 
void InitialpageHandle(void )
{
  if(G_HART_HandleFlag == HART_INIT_COMPLETE)     
  {
    //�ɹ��ʽ���ȷ���жϣ�����ǳɹ��ʲ����������ӳɹ������ҳ���л�����
    if((MENU_CurrentPageNumGet() == GENERAL_PAGE_INDEX_101)
       &&(MENU_GetMenuTreeIndex() == GENERAL_MENU_TREE))
    {
      HART_SuccessRatioHandle();
    }
    else if((MENU_CurrentPageNumGet() == GENERAL_PAGE_INDEX_102)
       &&(MENU_GetMenuTreeIndex() == GENERAL_MENU_TREE))
    {
    
    }
    else
    {
      //�رճɹ��ʼ��㴦����
      G_ComPCT_SWITCH = FALSE;
      //�汾����ִ����ϣ������豸���ʹ��������в˵����ѡ��
      HART_DeviceTypeHandle();
    }    
  }//ͨ��δ�����л�����
  else if(G_HART_HandleFlag == HART_INIT_ERR)  
  {
    //��ת����ʼ������ʧ�ܵľ������
    MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
    MENU_PageTypeSetHandle(WARNING_PAGE);
    MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_39);
  }
  MENU_PageShowSwitch(TRUE);
  G_SingleCommandLoad = TRUE;
}

/*
void InitialPageShow()
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
��ʼ��ҳ����ʾ������
�ú������������ֲ����ո��ϵ�����ʱ��ʾ��ʼ�����棬һ��ֻ�����豸δ���ӳɹ���
���������豸ʱ����á�
*
* �ؼ���ע��
* - 
���ֲ�����׼��֮ǰ���ú����ǿ��Ը��ݿͻ���Ҫ����ʾ��ʽ���иĶ��ġ�
  
* δ�����:

3.03�汾����ǰ�汾������TTS�����в˵�������������Ǳ�80G��26G��
StringIndex_870
*/ 
void InitialPageShow()
{
  StringDef StrStruct[1] = {0};
  uchar StringCodeBuff[1][COMMON_STRING_SIZE] = {0};
  PageDef *PagePtr = NULL;
  MENU_PageShowSwitch(FALSE);

  //��ȡ�˵������
  PagePtr = MENU_GetCurrentMenuPage();

  G_ConnectWay = PagePtr->ConnectWay;
  //ҳ����������غ���
  MENU_PageCommandGroupLoad(PagePtr);
  //��ʼ����ʾ����ΪӢ�Ľ��棬���������Ҫ�ĳ����ĵģ����Խ��г�������
  StrStruct[0] = MENU_GetStrStruct(STR_INDEX_0);
  FlashStringCodeGet(StrStruct,StringCodeBuff[0],ENGLISH);
  MENU_StaticStringShow(StrStruct,START_X_INDEX,
       START_Y_INDEX,ENGLISH,REVERSE_DISPLAY,StringCodeBuff[0]);
  StrStruct[0]  = MENU_GetStrStruct(STR_INDEX_81);
  FlashStringCodeGet(StrStruct,StringCodeBuff[0],ENGLISH);
  MENU_StaticStringShow(StrStruct,START_X_INDEX,
       START_Y_INDEX+2*(ITEM_HIGHT),ENGLISH,NORMAL,StringCodeBuff[0]); 
  StrStruct[0]  = MENU_GetStrStruct(STR_INDEX_82);  
  FlashStringCodeGet(StrStruct,StringCodeBuff[0],ENGLISH);
  MENU_StaticStringShow(StrStruct,START_X_INDEX+24,
       START_Y_INDEX+4*(ITEM_HIGHT),ENGLISH,NORMAL,StringCodeBuff[0]);
  StrStruct[0]  = MENU_GetStrStruct(STR_INDEX_898); 
  FlashStringCodeGet(StrStruct,StringCodeBuff[0],ENGLISH);
  MENU_StaticStringShow(StrStruct,START_X_INDEX+6,
       START_Y_INDEX+6*(ITEM_HIGHT),ENGLISH,NORMAL,StringCodeBuff[0]); 
  StrStruct[0]  = MENU_GetStrStruct(STR_INDEX_899);
  FlashStringCodeGet(StrStruct,StringCodeBuff[0],ENGLISH);
  MENU_StaticStringShow(StrStruct,START_X_INDEX,
       START_Y_INDEX+7*(ITEM_HIGHT),ENGLISH,REVERSE_DISPLAY,StringCodeBuff[0]);     
}
/*
void InitialPageRangeHandle()
* ������Χ:


* ����ֵ˵��:void 
* ���ܽ���:   
��ʼҳ�淶Χ����ģ�麯������������һЩ���������
*
* �ؼ���ע��
* - 
  
* δ�����:

*/ 
void InitialPageRangeHandle()
{
  if(G_IsInitVariable == FALSE)
  {
    InitialPageVariableInit();
  }
  else
  {
    if((G_PV_UnitTemp[0] != G_PV_Unit[0])
    ||(InitialPageRangeCompare() == FALSE))
    {
      G_IsInitVariable = FALSE;
    }
  }
}

