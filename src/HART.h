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

#ifndef HART_H
#define HART_H

#define INFO_BUFF_SIZE                   25
#define SLAVE_ADDR_BUFF_SIZE             6
#define HART_FRAME_BUFF_SIZE             150
#define SEND_DATA_BUFF_SIZE              28
#define POLLING_MAX                      15
#define RESPON_BUFF_SIZE                 2
#define MAX_FRAME_LENGTH                 150
#define COMMAND_BUFF_SIZE                50

//������ID
#define SIEMENS_MANUFACTURER_ID         0x2a
#define CHUAN_YI_MANUFACTURER_ID        0xd4
#define RADAR_MANUFACTURER_ID           0xfd//�ɰ汾
#define EJA_MANUFACTURER_ID             0X37
#define LM_MANUFACTURER_ID              0X26
#define HW_MANUFACTURER_ID              0X17
#define RAYDAR_MANUFACTURER_ID              0XE5


#define INIT_ADDR_BYTE_NUMBER            1
#define NORMAL_ADDR_BYTE_NUMBER          5
//#define VARIABLE_BUFF_SIZE               12
#define LEAD_CODE_VAL                   0xFF

#define SHOW_DATA_BUF_SIZE 10
#define VARIABLE_GROUP_SIZE             30

#define SOFTWARE_ERR                    0xff
//#define SAVE_MAMORY//û����ﴨ�ǣ�ֻ��������Ʒ
//#define SAVE_MAMORY_1//û��������Ʒ��ֻ����ﴨ��

//HART����ʶ��
typedef enum
{
  IDENTIFY = 0x00,              //�������ʶ��
  PV = 0x01,                    //��������
  PV_CURRENT_PERCENT = 0x02,    //�������������Ͱٷֱ�
  SECOND_VARIABLE = 0x03,       //�ڶ�������
  UAL009 = 9,                   //ͨ������9
  READ_MESSAGE = 0x0C,          //����Ϣ
  DESCRIPTION = 0x0D,           //����ǩTag,������Description������Date
  PV_SENSOR_INFO = 0x0e,        //����������������Ϣ
  PV_OUTPUT_INFO = 0x0f,        //�������������Ϣ
  READ_FINAL_ASMBLY_NUM = 0X10,  //������װ���
  WRITE_MESSAGE = 0X11,          //д��Ϣ
  WRITE_TAG_DES_DATE = 0x12,      //д��ǩ��������������
  WRITE_FINAL_ASMBLY_NUM = 0X13,  //д����װ���
  WRITE_PV_DAMP = 0x22,           //д����������ֵ
  WRITE_PV_RANGE = 0x23,          //д���������������޼���λ����
  SET_LUL = 0x24,                 //������������������
  SET_LSL = 0x25,                 //������������������
  FLD_LEVEL = 0x28,              // �̶�����������ֵ
  PERFORMING_SELFTEST = 0x29,    //�������Լ�-------�������ͱ�������Ϊ0����Ӧ֡������
  PerformDeviceReset = 42,      //ִ���豸���� 0x2A
  PV_ZERO_SET = 0x2b,            //������0������------�������ͱ�������Ϊ0����Ӧ֡������
  WRITE_PV_UNIT = 0x2c,          //д��������λ
  AO_MINIMUM = 0x2d,            //����������AO�����
  AO_MAX = 0x2e,                //����������AO����
  WRITE_XFER_FNCTN = 0x2f,      //д���书����
  ReadAdditionalDeviceStatus = 48,//��ȡ�����豸״̬ 0x30
  
  SIEMENS_READ_SPECIAL_128 = 0x80,      //���������ⶨ��128��ȡ״̬����
  SIEMENS_WRITE_UP_SNSR_TRIM = 0x82,    //���������ⶨ��130д������������������
  SIEMENS_WRITE_LO_SNSR_TRIM = 0x83,    //���������ⶨ��131д������������������
  SIEMENS_WRITE_PTOTECT_SET = 0x8c,     //������д��������
  SIEMENS_WRITE_ROOTING = 0x96,         //������дRooting
  SIEMENS_WRITE_ROOTING_VALUE = 0x97,   //������дRootingֵ
  
  READ_LONG_TAG = 0x14,             //���ǳ���ʶ
  CHUAN_YI_VARIABLE_DIS_MODE = 150,    //���Ǳ�����ʾģʽ
  CHUAN_YI_CUTOFF_PT_SHOW = 152,  //
  CHUAN_YI_TRANSMITTER_TYPE = 153, //���Ǵ�������
  CHUAN_YI_INP_CAL_ZERO = 131,   //����У��0
  CHUAN_YI_INP_CAL_HIGH = 130,   //����У�����ֵ
  
  CY_PDS7_SquawkWrite = 132,    //Squawk����
  CY_PDS7_SquawkRead = 135,     //Squawk��ȡ
  CHUAN_YI_WRITE_PRO_SET = 140,   //д��������
  CHUAN_YI_WRITE_PRO_CANCEL = 142,  //д����ȡ��
  CHUAN_YI_CUTOFF_PT_SET = 151, //
  CHUAN_YI_VARIABLE_DIS_MODE_SET = 155,//HART6 ������ʾģʽ����
  CHUAN_YI_AO_ALARM_TYPE_SET = 141, //����������������
  CHUAN_YI_DISPLAY_PRESS_TYPE = 154,   //��ʾѹ������
  CHUAN_YI_DISPLAY_PRESS_TYPE_SET = 156,//��ʾѹ����������
  
  
  CY_PDS7ReadTransmitterDisplayVariable = 145,//Read   Transmitter Display Variable
  CY_PDS7SetTransmitterDisplayVariable = 148,//Set Transmitter Display Variable

  CY_PDS7ReadZeroValue = 155,//Read   Zero Value
  CY_PDS7ReadBoardCode = 162,//Read the Board Code
  
  CY_PDS7ReadErrorLog = 166,//��ȡ������־��
  CY_PDS7ClearErrorLog = 167,//���������־��
  CY_PDS7ReadBidirMode = 169,   //read Bi-dir mode
  CY_PDS7WriteBidirMode = 170,   //write Bi-dir mode
  
  CY_PDS7ReadResponseMode = 180,   //Read response mode
  CY_PDS7WriteResponseMode = 171,   //Write response mode
  
  CY_PDS7ReadAO_UplowValue = 172,   //Read AO upper/lower limit value
  CY_PDS7WriteAO_UplowValue = 173,   //write AO upper/lower limit value
  
  CY_PDS7ReadPresAlertValue = 174,      //read pressure High/Low Alert Value 
  CY_PDS7WritePresAlertValue = 175,     //write pressure High/Low Alert Value 

  CY_PDS7ReadTempAlertMode = 176,   //read temperature alert mode
  CY_PDS7WriteTempAlertMode = 177,   //write temperature alert mode

  CY_PDS7ReadTempAlertValue = 178,      //read temperature High/Low Alert Value
  CY_PDS7WriteTempAlertValue = 179,     //Write temperature High/Low Alert Value
  
  CY_PDS7ReadBarIndicator = 181,      //read bar indicator display selection
  CY_PDS7WriteBarIndicator = 182,     //write bar indicator display selection
  
  CY_PDS7ReadAdditionalInfo = 184,   //read additional device information
  
  CY_PDS7EnterExitSimulateMode = 185,   //������˳�ģ��ģʽ
  CY_PDS7Simulate = 187,//ģ�����
  
  CY_PDS7ReadPressureResolution = 189,      //read Display Pressure % Resolution 
  CY_PDS7WritePressureResolution = 190,     //write Display Pressure % Resolution
  
  POLLING_ADDRESS_SET = 6, //polling��ַ����
  POLLING_ADDRESS_READ = 7, //��ȡpolling��ַ����
  WRITE_LONG_TAG = 22, //д����ʶ
  WriteNumOfRespPreams = 59,//���ôӻ���������ǰ��������
  //����TTS���
  CY_SNSR_INFO_READ = 0X82,//��ȡ�����������Ϣ
  CY_SNSR_PARAM_WRITE = 0X83,//���ô�������ز���
  CY_ALARM_AO_READ = 0XA2,//��ȡ�����������ֵ
  CY_ALARM_AO_WRITE = 0XA3,//���ñ����������ֵ
  CY_DISPLAYCODE_READ = 0XA4,//��ȡ��ʾ����
  CY_DISPLAYCODE_WRITE = 0XA5,//д����ʾ����
  CY_WRITE_PRO_SET = 0xA9,   //д��������


  //���
  RADAR_CURRENT_4MA = 71,//4��������
  RADAR_CABLE_LENGTH_WRITE = 0xf8,//�����³�
  RADAR_CABLE_LENGTH_READ = 0xf7,//���³�
  RADAR_CURVE_RANGE = 188,//������ʾ��Χ��ȡ
  RADAR_FAKE_RANGE = 189,//������ٻز�
  RADAR_CURVE_POINT1 = 190,//��ȡ�ز����ߵ���
  RADAR_CURVE_POINT2 = 191,//��ȡ��ٻز�����

  RADAR_CURVE_POINT5 = 194,//���߶���5
  RADAR_PULSE_CURVE = 0xba,//��λ���߽����ֵ��ȡ
  RADAR_GUIDED_WAVES_CURVE = 0xbb,//�������߱���ֵ��ʾ��ȡ
  RADAR_BASIC_INFO = 0x50,//�״������Ϣ��ȡ
  
  RADAR_DIELECTRIC_WRITE = 0xFA,//���ý�糣��
  RADAR_DZ_SET = 0xD8,//ä����������
  RADAR_FEI = 0x52,//��ٻز�����
  RADAR_LEVEL_SPEED_SET = 0x51,//��λ�ٶ�����
  RADAR_ECHO_JUDGE_READ = 0x55,//�ز��о���Ϣ��ȡ
  RADAR_ECHO_JUDGE_SET = 0x58,//�ز��о���Ϣ�趨
  RADAR_DIST_PARAM_READ = 0x95,//���������ȡ
  RADAR_DIST_CORRECT_READ = 0x99,//����У׼ϵ����ȡ
  RADAR_DIST_CORRECT_SET = 0x9a,//�ز��о���Ϣ��ȡ
  RADAR_ELO_READ = 0x53,//ʧ��������ȡ
  RADAR_JUMP_READ = 0x54,//������Ϣ��ȡ
  RADAR_JUMP_SET = 0x57,//������Ϣ����
  RADAR_CURRENT_INFO_READ = 0x46,//������Ϣ��ȡ
  RADAR_CURRENT_INFO_SET = 0x49,//������Ϣ����
  RADAR_PARA_PROTECT = 0x59,//��������
  RADAR_DATE_READ = 0xfb,//���ڶ�ȡ
  RADAR_SERIAL_READ = 0xfc,//���кŶ�ȡ
  RADAR_VERSION_READ = 0xfe,//�汾�Ŷ�ȡ
  RADAR_DATE_SET = 0xf2,//��������
  RADAR_SERIAL_SET = 0xf3,//���к�����
  RADAR_PART_NO_SET = 0xf4,//��Ʒ�ͺ�����
  RADAR_ELO_SET = 0x56,//ʧ��������ȡ
  RADAR_PART_NO_READ = 0xfd,//��Ʒ�ͺŶ�ȡ
  RADAR_POLL_MODE = 0x05,//ͨ�ŷ�ʽ
  RADAR_POLL_INFO = 0x5a,//ͨ����Ϣ
  
  //EJA430A
  EJA_LOW_CUT_R = 0x96,
  EJA_LOW_CUT_W = 0x97,
  EJA_CUT_MODE_W = 0x98,
  EJA_BI_DIR_R = 0x99,
  EJA_BI_DIR_W = 0X9A,
  EJA_DISPLAY_MODE_R = 0x9b,
  EJA_DISPLAY_MODE_W = 0x9c,
  EJA_ENGR_INFO_R = 0x9d,
  EJA_ENGR_INFO_W = 0x9e,

  EJA_UNKNOW_R1 = 0xa0,
  EJA_FIELD_INFO_R = 0xa1,
  EJA_FIELD_INFO_W = 0xa2,
  EJA_UP_LO_TRM_PT_R = 0xa3,
  EJA_EXT_SM_R = 0xa4,
  EJA_EXT_SM_W = 0xa5,
  EJA_MODEL_R = 0xa6,
  EJA_SENSOR_UNIT_R = 0xa7,
  EJA_SENSOR_UNIT_W = 0xa8,
  EJA_SERIAL_NO_R = 0xa9,

  EJA_H20_UNIT_R = 0xb0,
  EJA_H20_UNIT_W = 0xb1,
  EJA_SI_OPTION_R = 0xb4,
  EJA_SI_OPTION_W = 0xb5,

  EJA_UNKNOW_R2 = 0xf8,
  EJA_WRT_PWD_R = 0xf9,
  EJA_WRT_SET = 0xfa,
  EJA_NEW_PWD_SET = 0xfb,
  
  //EJA530E
  EJA530_ENGR_UNIT_R = 0X80,
  EJA530_LOW_CUT_R = 0X82,
  EJA530_LOW_CUT_W = 0X83,
  EJA530_DISP_INFO_R = 0X98,
  EJA530_DISP_INFO_W = 0X99,
  EJA530_ENGR_INFO_R = 0X9A,
  EJA530_ENGR_INFO_W = 0X9B,
  EJA530_ENGR_UNIT_W = 0X9C,
  
  
  LM_FIELD_INFO_R = 0X80,
  LM_FIELD_INFO_W = 0X81,
  LM_CM_SETUP_R = 0X87,
  LM_CM_SETUP_W = 0X88,
  LM_RECALL_FACTORY_TRM_W = 0X8A,
  LM_SNSR_TRIM_CAL_TYPE_R = 0X8B,
  LM_SNSR_TRIM_CAL_TYPE_W = 0X8C,
  LM_ALARM_SAT_LEVEL_R = 0X8D,  
  
  DISP_INFO_W = 0Xca,
  LCD_DISP_W = 0Xcd,
  DISP_INFO_R = 0Xce,
  LCD_DISP_R = 0Xd1,
  
//HVP
  //Write Status bf
  WriteAdditionalDeviceStatus = 159,
  //Read AFCT A0
  ReadAFCT = 160,
  //Write AFCT A1
  WriteAFCT = 161,
  //Read SFCT A2
  ReadSFCT = 162,
  //Write SFCT A3
  WriteSFCT = 163,
  //Read YFCT, SDIR, YDIR	A4
  ReadYFCT_SDIR_YDIR = 164,
  //Write YFCT, SDIR, YDIR	A5
  WriteYFCT_SDIR_YDIR = 165,
  //Read MA4 and MA20 CA
  ReadMA4andMA20 = 202,
  //Write MA4 and MA20 CB
  WriteMA4andMA20 = 203,
  //Read DEBA, SPRA, SPRE, SCUE, SCUE 	B7
  ReadDEBA_SPRA_SPRE_SCUA_SCUE = 183,
  //Write DEBA, SPRA, SPRE, SCUE, SCUE 		B8
  WriteDEBA_SPRA_SPRE_SCUA_SCUE = 184,
  //Read SHUT			CC
  ReadSHUT = 204,
  //Write SHUT			CD
  WriteSHUT = 205,
  //Read YCLS			CE
  ReadYCLS = 206,
  //Write YCLS			CF
  WriteYCLS = 207,
  //Read PID parameters		C6
  ReadPIDparameters = 198,
  //Write PID parameters	C7
  WritePIDparameters = 199,
  //Read Free points SL0, SL1, SL2, SL3, SL4, SL5	B9
  ReadFreepointsSL0 = 185,
  //Write Free points SL0, SL1, SL2, SL3, SL4, SL5	BA
  WriteFreePointsSL0 = 186,
  //Read Free points SL6��SL7��SL8��SL9��SL10	BB
  ReadFreePointsSL6 = 187,
  //Write Free points SL6��SL7��SL8��SL9��SL10	BC
  WriteFreePointsSL6 = 188,
  //Read Free points SL11��SL12��SL13��SL14��SL15	BF
  ReadFreePointsSL11 = 191,
  //Write Free points SL11��SL12��SL13��SL14��SL15	C0
  WriteFreePointsSL11 = 192,
  //Read Free points SL16��SL17��SL18��SL19��SL20	C1
  ReadFreePointsSL16 = 193,
  //Write Free points SL16��SL17��SL18��SL19��SL20	C2
  WriteFreePointsSL16 = 194,
  //Read Self calibrate	BD
  ReadSelfCalibrate = 189,
  //Write Self calibrate	BE
  WriteSelfCalibrate = 190,
  //Read alarm status		A6
  ReadAlarmStatus = 166,
  //Hvp Write Protect		A7
  HvpWriteProtect = 167,
  //Fix control mode		DC
  FixControlMode = 220,
  //control mode		DC
  ControlMode = 220,
  //Read PST		D0
  ReadPSTfunction = 208,
  //Write PST		D1
  WritePSTfunction = 209,
  //Read Diagnostic function-Running time		D4
  ReadDiagnosticFunctionRunningTime = 212,
  //Read Diagnostic function-Temperature  D2
  ReadDiagnosticFunctionTemperature = 210,
  //Read Diagnostic function-Valve information	D6
  ReadDiagnosticFunctionValveInformation = 214,
  //Diagnostic data reset	D9
  DiagnosticDataReset = 217,
  IDENTIFIER	= 0,	//���ʶ��
  READ_PV	= 1,	//����������Ϣ
  LCPOR	= 2,	//����·�����Ͱٷֱ�
  DVLC	= 3,	//��̬��������·����
  WRITE_PLD	= 6,	//д��ѵ��ַ
  READ_PLD	= 7,	//����ѵ��ַ
  READ_DV_CLSF	= 8,	//��ȡ��̬��������
  READ_DV_STATUS	= 9,	//��ȡ��̬����״̬
  READ_IDENTIFIER_TAG	= 11,	//TAGʶ��
  READ_TDD	= 13,	//��Tag, Descriptor, Date
  READ_PVTI	= 14,	//Read Primary Variable Transducer Information
  READ_DEVICE_INF	= 15,	//Read Device Information
  READ_FAN	= 16,	//Read Final Assembly Number
  WRITE_TDD	= 18,	//Write Tag, Descriptor, Date
  WRITE_FAN	= 19,	//Write Final Assembly Number
  READ_LTAG	= 20,	//Read Long Tag
  READ_IDENTIFIER_LTAG	= 21,	//Read Unique Identifier Associated With Long Tag
  WRITE_LTAG	= 22,	//Write Long Tag
  WRITE_PVDV	= 34,	//Write Primary Variable Damping Value
  WRITE_PVRV	= 35,	//Write Primary Variable Range Values
  RESET_CCF	= 38,	//Reset Configuration Changed Flag
  EE_FCM	= 40,	//Enter/Exit Fixed Current Mode
  WRITE_PVU	= 44,	//Write Primary Variable Units
  TRIM_LCZ	= 45,	//Trim Loop Current Zero
  TRIM_LCG	= 46,	//Trim Loop Current Gain
  READ_ADS	= 48,	//Read Additional Device Status
  WRITE_PVTSN	= 49,	//Write Primary Variable Transducer Serial Number
  RAYDAR80G_CMD128	= 128,	//����λ�ٶȣ���ٻز���ֵ����糣��
  RAYDAR80G_CMD129	= 129,	//д��糣��
  RAYDAR80G_CMD130	= 130,	//д��λ�ٶ�
  RAYDAR80G_CMD131	= 131,	//д��ٻز���ֵ
  RAYDAR80G_CMD132	= 132,	//���øߵ�λä��
  RAYDAR80G_CMD133	= 133,	//��ȡ�����ж���Ϣ
  RAYDAR80G_CMD134	= 134,	//д�����ж���Ϣ
  RAYDAR80G_CMD135	= 135,	//��ʧ����Ϣ
  RAYDAR80G_CMD136	= 136,	//дʧ����Ϣ
  RAYDAR80G_CMD137	= 137,	//������������Ϣ
  RAYDAR80G_CMD138	= 138,	//д����������Ϣ
  RAYDAR80G_CMD139	= 139,	//�����������Ϣ
  RAYDAR80G_CMD140	= 140,	//д���������Ϣ
  RAYDAR80G_CMD141	= 141,	//������˳�д����
  RAYDAR80G_CMD142	= 142,	//������������
  RAYDAR80G_CMD143	= 143,	//������У׼
  RAYDAR80G_CMD144	= 144,	//д����У׼
  RAYDAR80G_CMD145	= 145,	//���ַ�����չ����
  RAYDAR80G_CMD146	= 146,	//д�ַ�����չ����
  RAYDAR80G_CMD147	= 147,	//����������չ����
  RAYDAR80G_CMD148	= 148,	//д��������չ����
  RAYDAR80G_CMD190	= 190,	//����������չ����
  RAYDAR80G_CMD191	= 191,	//д��������չ����
}CommandDef;
typedef enum
{
  NOMEANS,
  EJA_TYPE1,
  LM_TYPE1,
  HW_TYPE1,
  EJA530_TYPE1,
  SIEMENS_TYPE1,
  CHUAN_YI_TYPE2,//tts
  CHUAN_YI_HVPID,//HVP
  RADAR_TYPE1,
  CHUAN_YI_TYPE1,//pds
  CY_PDS7,//pds HART7
  RAYDAR_80G,//����Ǳ�����֤�汾
}ProductTypeAndID_Def;

//HART_�������Ͷ���
//ASCII
typedef enum
{
  UCHAR = 1,
  UINT = 2,
  THREE_BYTES = 3,
  LONG_UINT = 4,
  FLOAT = 4,
  ASCII_5 = 5,
  ASCII_6 = 6,
  ASCII_7 = 7,
  ASCII_8 = 8,
  ASCII_9 = 9,
  ASCII_10 = 10,
  ASCII_11 = 11,
  ASCII_12 = 12,
  ASCII_13 = 13,
  ASCII_14 = 14,
  ASCII_15 = 15,
  ASCII_16 = 16,
  ASCII_20 = 20,
  MESSAGE_BOUNDARY = 21,
  ASCII_24 = 24,
  ASCII_32 = 32,
  ASCII_33 = 33,
  ASCII_42 = 42,
  ASCII_100 = 100,
}DataLengthDef;
typedef enum
{
VariableTableIndex0,
VariableTableIndex1,
VariableTableIndex2,
VariableTableIndex3,
VariableTableIndex4,
VariableTableIndex5,
VariableTableIndex6,
VariableTableIndex7,
VariableTableIndex8,
VariableTableIndex9,
VariableTableIndex10,
VariableTableIndex11,
VariableTableIndex12,
VariableTableIndex13,
VariableTableIndex14,
VariableTableIndex15,
VariableTableIndex16,
VariableTableIndex17,
VariableTableIndex18,
VariableTableIndex19,
VariableTableIndex20,
VariableTableIndex21,
VariableTableIndex22,
VariableTableIndex23,
VariableTableIndex24,
VariableTableIndex25,
VariableTableIndex26,
VariableTableIndex27,
VariableTableIndex28,
VariableTableIndex29,
VariableTableIndex30,
VariableTableIndex31,
VariableTableIndex32,
VariableTableIndex33,
VariableTableIndex34,
VariableTableIndex35,
VariableTableIndex36,
VariableTableIndex37,
VariableTableIndex38,
VariableTableIndex39,
VariableTableIndex40,
VariableTableIndex41,
VariableTableIndex42,
VariableTableIndex43,
VariableTableIndex44,
VariableTableIndex45,
VariableTableIndex46,
VariableTableIndex47,
VariableTableIndex48,
VariableTableIndex49,
VariableTableIndex50,
VariableTableIndex51,
VariableTableIndex52,
VariableTableIndex53,
VariableTableIndex54,
VariableTableIndex55,
VariableTableIndex56,
VariableTableIndex57,
VariableTableIndex58,
VariableTableIndex59,
VariableTableIndex60,
VariableTableIndex61,
VariableTableIndex62,
VariableTableIndex63,
VariableTableIndex64,
VariableTableIndex65,
VariableTableIndex66,
VariableTableIndex67,
VariableTableIndex68,
VariableTableIndex69,
VariableTableIndex70,
VariableTableIndex71,
VariableTableIndex72,
VariableTableIndex73,
VariableTableIndex74,
VariableTableIndex75,
VariableTableIndex76,
VariableTableIndex77,
VariableTableIndex78,
VariableTableIndex79,
VariableTableIndex80,
VariableTableIndex81,
VariableTableIndex82,
VariableTableIndex83,
VariableTableIndex84,
VariableTableIndex85,
VariableTableIndex86,
VariableTableIndex87,
VariableTableIndex88,
VariableTableIndex89,
VariableTableIndex90,
VariableTableIndex91,
VariableTableIndex92,
VariableTableIndex93,
VariableTableIndex94,
VariableTableIndex95,
VariableTableIndex96,
VariableTableIndex97,
VariableTableIndex98,
VariableTableIndex99,
VariableTableIndex100,
VariableTableIndex101,
VariableTableIndex102,
VariableTableIndex103,
VariableTableIndex104,
VariableTableIndex105,
VariableTableIndex106,
VariableTableIndex107,
VariableTableIndex108,
VariableTableIndex109,
VariableTableIndex110,
VariableTableIndex111,
VariableTableIndex112,
VariableTableIndex113,
VariableTableIndex114,
VariableTableIndex115,
VariableTableIndex116,
VariableTableIndex117,
VariableTableIndex118,
VariableTableIndex119,
VariableTableIndex120,
VariableTableIndex121,
VariableTableIndex122,
VariableTableIndex123,
VariableTableIndex124,
VariableTableIndex125,
VariableTableIndex126,
VariableTableIndex127,
VariableTableIndex128,
VariableTableIndex129,
VariableTableIndex130,
VariableTableIndex131,
VariableTableIndex132,
VariableTableIndex133,
VariableTableIndex134,
VariableTableIndex135,
VariableTableIndex136,
VariableTableIndex137,
VariableTableIndex138,
VariableTableIndex139,
VariableTableIndex140,
VariableTableIndex141,
VariableTableIndex142,
VariableTableIndex143,
VariableTableIndex144,
VariableTableIndex145,
VariableTableIndex146,
VariableTableIndex147,
VariableTableIndex148,
VariableTableIndex149,
VariableTableIndex150,
VariableTableIndex151,
VariableTableIndex152,
VariableTableIndex153,
VariableTableIndex154,
VariableTableIndex155,
VariableTableIndex156,
VariableTableIndex157,
VariableTableIndex158,
VariableTableIndex159,
VariableTableIndex160,
VariableTableIndex161,
VariableTableIndex162,
VariableTableIndex163,
VariableTableIndex164,
VariableTableIndex165,
VariableTableIndex166,
VariableTableIndex167,
VariableTableIndex168,
VariableTableIndex169,
VariableTableIndex170,
VariableTableIndex171,
VariableTableIndex172,
VariableTableIndex173,
VariableTableIndex174,
VariableTableIndex175,
VariableTableIndex176,
VariableTableIndex177,
VariableTableIndex178,
VariableTableIndex179,
VariableTableIndex180,
VariableTableIndex181,
VariableTableIndex182,
VariableTableIndex183,
VariableTableIndex184,
VariableTableIndex185,
VariableTableIndex186,
VariableTableIndex187,
VariableTableIndex188,
VariableTableIndex189,
VariableTableIndex190,
VariableTableIndex191,
VariableTableIndex192,
VariableTableIndex193,
VariableTableIndex194,
VariableTableIndex195,
VariableTableIndex196,
VariableTableIndex197,
VariableTableIndex198,
VariableTableIndex199,
VariableTableIndex200,
VariableTableIndex201,
VariableTableIndex202,
VariableTableIndex203,
VariableTableIndex204,
VariableTableIndex205,
VariableTableIndex206,
VariableTableIndex207,
VariableTableIndex208,
VariableTableIndex209,
VariableTableIndex210,
VariableTableIndex211,
VariableTableIndex212,
VariableTableIndex213,
VariableTableIndex214,
VariableTableIndex215,
VariableTableIndex216,
VariableTableIndex217,
VariableTableIndex218,
VariableTableIndex219,
VariableTableIndex220,
VariableTableIndex221,
VariableTableIndex222,
VariableTableIndex223,
VariableTableIndex224,
VariableTableIndex225,
VariableTableIndex226,
VariableTableIndex227,
VariableTableIndex228,
VariableTableIndex229,
VariableTableIndex230,
VariableTableIndex231,
VariableTableIndex232,
VariableTableIndex233,
VariableTableIndex234,
VariableTableIndex235,
VariableTableIndex236,
VariableTableIndex237,
VariableTableIndex238,
VariableTableIndex239,
VariableTableIndex240,
VariableTableIndex241,
VariableTableIndex242,
VariableTableIndex243,
VariableTableIndex244,
VariableTableIndex245,
VariableTableIndex246,
VariableTableIndex247,
VariableTableIndex248,
VariableTableIndex249,
VariableTableIndex250,
VariableTableIndex251,
VariableTableIndex252,
VariableTableIndex253,
VariableTableIndex254,
VariableTableIndex255,
VariableTableIndex256,
VariableTableIndex257,
VariableTableIndex258,
VariableTableIndex259,
VariableTableIndex260,
VariableTableIndex261,
VariableTableIndex262,
VariableTableIndex263,
VariableTableIndex264,
VariableTableIndex265,
VariableTableIndex266,
VariableTableIndex267,
VariableTableIndex268,
VariableTableIndex269,
VariableTableIndex270,
VariableTableIndex271,
VariableTableIndex272,
VariableTableIndex273,
VariableTableIndex274,
VariableTableIndex275,
VariableTableIndex276,
VariableTableIndex277,
VariableTableIndex278,
VariableTableIndex279,
VariableTableIndex280,
VariableTableIndex281,
VariableTableIndex282,
VariableTableIndex283,
VariableTableIndex284,
VariableTableIndex285,
VariableTableIndex286,
VariableTableIndex287,
VariableTableIndex288,
VariableTableIndex289,
VariableTableIndex290,
VariableTableIndex291,
VariableTableIndex292,
VariableTableIndex293,
VariableTableIndex294,
VariableTableIndex295,
VariableTableIndex296,
VariableTableIndex297,
VariableTableIndex298,
VariableTableIndex299,
VariableTableIndex300,
VariableTableIndex301,
VariableTableIndex302,
VariableTableIndex303,
VariableTableIndex304,
VariableTableIndex305,
VariableTableIndex306,
VariableTableIndex307,
VariableTableIndex308,
VariableTableIndex309,
VariableTableIndex310,
VariableTableIndex311,
VariableTableIndex312,
VariableTableIndex313,
VariableTableIndex314,
VariableTableIndex315,
VariableTableIndex316,
VariableTableIndex317,
VariableTableIndex318,
VariableTableIndex319,
VariableTableIndex320,
VariableTableIndex321,
VariableTableIndex322,
VariableTableIndex323,
VariableTableIndex324,
VariableTableIndex325,
VariableTableIndex326,
VariableTableIndex327,
VariableTableIndex328,
VariableTableIndex329,
VariableTableIndex330,
VariableTableIndex331,
VariableTableIndex332,
VariableTableIndex333,
VariableTableIndex334,
VariableTableIndex335,
VariableTableIndex336,
VariableTableIndex337,
VariableTableIndex338,
VariableTableIndex339,
VariableTableIndex340,
VariableTableIndex341,
VariableTableIndex342,
VariableTableIndex343,
VariableTableIndex344,
VariableTableIndex345,
VariableTableIndex346,
VariableTableIndex347,
VariableTableIndex348,
VariableTableIndex349,
VariableTableIndex350,
VariableTableIndex351,
VariableTableIndex352,
VariableTableIndex353,
VariableTableIndex354,
VariableTableIndex355,
VariableTableIndex356,
VariableTableIndex357,
VariableTableIndex358,
VariableTableIndex359,
VariableTableIndex360,
VariableTableIndex361,
VariableTableIndex362,
VariableTableIndex363,
VariableTableIndex364,
VariableTableIndex365,
VariableTableIndex366,
VariableTableIndex367,
VariableTableIndex368,
VariableTableIndex369,
VariableTableIndex370,
VariableTableIndex371,
VariableTableIndex372,
VariableTableIndex373,
VariableTableIndex374,
VariableTableIndex375,
VariableTableIndex376,
VariableTableIndex377,
VariableTableIndex378,
VariableTableIndex379,
VariableTableIndex380,
VariableTableIndex381,
VariableTableIndex382,
VariableTableIndex383,
VariableTableIndex384,
VariableTableIndex385,
VariableTableIndex386,
VariableTableIndex387,
VariableTableIndex388,
VariableTableIndex389,
VariableTableIndex390,
VariableTableIndex391,
VariableTableIndex392,
VariableTableIndex393,
VariableTableIndex394,
VariableTableIndex395,
VariableTableIndex396,
VariableTableIndex397,
VariableTableIndex398,
VariableTableIndex399,
VariableTableIndex400,
VariableTableIndex401,
VariableTableIndex402,
VariableTableIndex403,
VariableTableIndex404,
VariableTableIndex405,
VariableTableIndex406,
VariableTableIndex407,
VariableTableIndex408,
VariableTableIndex409,
VariableTableIndex410,
VariableTableIndex411,
VariableTableIndex412,
VariableTableIndex413,
VariableTableIndex414,
VariableTableIndex415,
VariableTableIndex416,
VariableTableIndex417,
VariableTableIndex418,
VariableTableIndex419,
VariableTableIndex420,
VariableTableIndex421,
VariableTableIndex422,
VariableTableIndex423,
VariableTableIndex424,
VariableTableIndex425,
VariableTableIndex426,
VariableTableIndex427,
VariableTableIndex428,
VariableTableIndex429,
VariableTableIndex430,
VariableTableIndex431,
VariableTableIndex432,
VariableTableIndex433,
VariableTableIndex434,
VariableTableIndex435,
VariableTableIndex436,
VariableTableIndex437,
VariableTableIndex438,
VariableTableIndex439,
VariableTableIndex440,
VariableTableIndex441,
VariableTableIndex442,
VariableTableIndex443,
VariableTableIndex444,
VariableTableIndex445,
VariableTableIndex446,
VariableTableIndex447,
VariableTableIndex448,
VariableTableIndex449,
VariableTableIndex450,
VariableTableIndex451,
VariableTableIndex452,
VariableTableIndex453,
VariableTableIndex454,
VariableTableIndex455,
VariableTableIndex456,
VariableTableIndex457,
VariableTableIndex458,
VariableTableIndex459,
VariableTableIndex460,
VariableTableIndex461,
VariableTableIndex462,
VariableTableIndex463,
VariableTableIndex464,
VariableTableIndex465,
VariableTableIndex466,
VariableTableIndex467,
VariableTableIndex468,
VariableTableIndex469,
VariableTableIndex470,
VariableTableIndex471,
VariableTableIndex472,
VariableTableIndex473,
VariableTableIndex474,
VariableTableIndex475,
VariableTableIndex476,
VariableTableIndex477,
VariableTableIndex478,
VariableTableIndex479,
VariableTableIndex480,
VariableTableIndex481,
VariableTableIndex482,
VariableTableIndex483,
VariableTableIndex484,
VariableTableIndex485,
VariableTableIndex486,
VariableTableIndex487,
VariableTableIndex488,
VariableTableIndex489,
VariableTableIndex490,
VariableTableIndex491,
VariableTableIndex492,
VariableTableIndex493,
VariableTableIndex494,
VariableTableIndex495,
VariableTableIndex496,
VariableTableIndex497,
VariableTableIndex498,
VariableTableIndex499,
VariableTableIndex500,
VariableTableIndex501,
VariableTableIndex502,
VariableTableIndex503,
VariableTableIndex504,
VariableTableIndex505,
VariableTableIndex506,
VariableTableIndex507,
VariableTableIndex508,
VariableTableIndex509,
VariableTableIndex510,
VariableTableIndex511,
VariableTableIndex512,
VariableTableIndex513,
VariableTableIndex514,
VariableTableIndex515,
VariableTableIndex516,
VariableTableIndex517,
VariableTableIndex518,
VariableTableIndex519,
VariableTableIndex520,
VariableTableIndex521,
VariableTableIndex522,
VariableTableIndex523,
VariableTableIndex524,
VariableTableIndex525,
VariableTableIndex526,
VariableTableIndex527,
VariableTableIndex528,
VariableTableIndex529,
VariableTableIndex530,
VariableTableIndex531,
VariableTableIndex532,
VariableTableIndex533,
VariableTableIndex534,
VariableTableIndex535,
VariableTableIndex536,
VariableTableIndex537,
VariableTableIndex538,
VariableTableIndex539,
VariableTableIndex540,
}VariableTableIndexDef;

typedef enum
{
VARIABLE_ARR_0,
VARIABLE_ARR_1,
VARIABLE_ARR_2,
VARIABLE_ARR_3,
VARIABLE_ARR_4,
VARIABLE_ARR_5,
VARIABLE_ARR_6,
VARIABLE_ARR_7,
VARIABLE_ARR_8,
VARIABLE_ARR_9,
VARIABLE_ARR_10,
VARIABLE_ARR_11,
VARIABLE_ARR_12,
VARIABLE_ARR_13,
VARIABLE_ARR_14,
VARIABLE_ARR_15,
VARIABLE_ARR_16,
VARIABLE_ARR_17,
VARIABLE_ARR_18,
VARIABLE_ARR_19,
VARIABLE_ARR_20,
VARIABLE_ARR_21,
VARIABLE_ARR_22,
VARIABLE_ARR_23,
VARIABLE_ARR_24,
VARIABLE_ARR_25,
VARIABLE_ARR_26,
VARIABLE_ARR_27,
VARIABLE_ARR_28,
VARIABLE_ARR_29,
VARIABLE_ARR_30,
VARIABLE_ARR_31,
VARIABLE_ARR_32,
VARIABLE_ARR_33,
VARIABLE_ARR_34,
VARIABLE_ARR_35,
VARIABLE_ARR_36,
VARIABLE_ARR_37,
VARIABLE_ARR_38,
VARIABLE_ARR_39,
VARIABLE_ARR_40,
VARIABLE_ARR_41,
VARIABLE_ARR_42,
VARIABLE_ARR_43,
VARIABLE_ARR_44,
VARIABLE_ARR_45,
VARIABLE_ARR_46,
VARIABLE_ARR_47,
VARIABLE_ARR_48,
VARIABLE_ARR_49,
VARIABLE_ARR_50,
VARIABLE_ARR_51,
VARIABLE_ARR_52,
VARIABLE_ARR_53,
VARIABLE_ARR_54,
VARIABLE_ARR_55,
VARIABLE_ARR_56,
VARIABLE_ARR_57,
VARIABLE_ARR_58,
VARIABLE_ARR_59,
VARIABLE_ARR_60,
VARIABLE_ARR_61,
VARIABLE_ARR_62,
VARIABLE_ARR_63,
VARIABLE_ARR_64,
VARIABLE_ARR_65,
VARIABLE_ARR_66,
VARIABLE_ARR_67,
VARIABLE_ARR_68,
VARIABLE_ARR_69,
VARIABLE_ARR_70,
VARIABLE_ARR_71,
VARIABLE_ARR_72,
VARIABLE_ARR_73,
VARIABLE_ARR_74,
VARIABLE_ARR_75,
VARIABLE_ARR_76,
VARIABLE_ARR_77,
VARIABLE_ARR_78,
VARIABLE_ARR_79,
VARIABLE_ARR_80,
VARIABLE_ARR_81,
VARIABLE_ARR_82,
VARIABLE_ARR_83,
VARIABLE_ARR_84,
VARIABLE_ARR_85,
VARIABLE_ARR_86,
VARIABLE_ARR_87,
VARIABLE_ARR_88,
VARIABLE_ARR_89,
VARIABLE_ARR_90,
VARIABLE_ARR_91,
VARIABLE_ARR_92,
VARIABLE_ARR_93,
VARIABLE_ARR_94,
VARIABLE_ARR_95,
VARIABLE_ARR_96,
VARIABLE_ARR_97,
VARIABLE_ARR_98,
VARIABLE_ARR_99,
VARIABLE_ARR_100,
VARIABLE_ARR_101,
VARIABLE_ARR_102,
VARIABLE_ARR_103,
VARIABLE_ARR_104,
VARIABLE_ARR_105,
VARIABLE_ARR_106,
VARIABLE_ARR_107,
VARIABLE_ARR_108,
VARIABLE_ARR_109,
VARIABLE_ARR_110,
VARIABLE_ARR_111,
VARIABLE_ARR_112,
VARIABLE_ARR_113,
VARIABLE_ARR_114,
VARIABLE_ARR_115,
VARIABLE_ARR_116,
VARIABLE_ARR_117,
VARIABLE_ARR_118,
VARIABLE_ARR_119,
VARIABLE_ARR_120,
VARIABLE_ARR_121,
VARIABLE_ARR_122,
VARIABLE_ARR_123,
VARIABLE_ARR_124,
VARIABLE_ARR_125,
VARIABLE_ARR_126,
VARIABLE_ARR_127,
VARIABLE_ARR_128,
VARIABLE_ARR_129,
VARIABLE_ARR_130,
VARIABLE_ARR_131,
VARIABLE_ARR_132,
VARIABLE_ARR_133,
VARIABLE_ARR_134,
VARIABLE_ARR_135,
VARIABLE_ARR_136,
VARIABLE_ARR_137,
VARIABLE_ARR_138,
VARIABLE_ARR_139,
VARIABLE_ARR_140,
VARIABLE_ARR_141,
VARIABLE_ARR_142,
VARIABLE_ARR_143,
VARIABLE_ARR_144,
VARIABLE_ARR_145,
VARIABLE_ARR_146,
VARIABLE_ARR_147,
VARIABLE_ARR_148,
VARIABLE_ARR_149,
VARIABLE_ARR_150,
VARIABLE_ARR_151,
VARIABLE_ARR_152,
VARIABLE_ARR_153,
VARIABLE_ARR_154,
VARIABLE_ARR_155,
VARIABLE_ARR_156,
VARIABLE_ARR_157,
VARIABLE_ARR_158,
VARIABLE_ARR_159,
VARIABLE_ARR_160,
VARIABLE_ARR_161,
VARIABLE_ARR_162,
VARIABLE_ARR_163,
VARIABLE_ARR_164,
VARIABLE_ARR_165,
VARIABLE_ARR_166,
VARIABLE_ARR_167,
VARIABLE_ARR_168,
VARIABLE_ARR_169,
VARIABLE_ARR_170,
VARIABLE_ARR_171,
VARIABLE_ARR_172,
VARIABLE_ARR_173,
VARIABLE_ARR_174,
VARIABLE_ARR_175,
VARIABLE_ARR_176,
VARIABLE_ARR_177,
VARIABLE_ARR_178,
VARIABLE_ARR_179,
VARIABLE_ARR_180,
VARIABLE_ARR_181,
VARIABLE_ARR_182,
VARIABLE_ARR_183,
VARIABLE_ARR_184,
VARIABLE_ARR_185,
VARIABLE_ARR_186,
VARIABLE_ARR_187,
VARIABLE_ARR_188,
VARIABLE_ARR_189,
VARIABLE_ARR_190,
VARIABLE_ARR_191,
VARIABLE_ARR_192,
VARIABLE_ARR_193,
VARIABLE_ARR_194,
VARIABLE_ARR_195,
VARIABLE_ARR_196,
VARIABLE_ARR_197,
VARIABLE_ARR_198,
VARIABLE_ARR_199,
VARIABLE_ARR_200,
VARIABLE_ARR_201,
VARIABLE_ARR_202,
VARIABLE_ARR_203,
VARIABLE_ARR_204,
VARIABLE_ARR_205,
VARIABLE_ARR_206,
VARIABLE_ARR_207,
VARIABLE_ARR_208,
VARIABLE_ARR_209,
VARIABLE_ARR_210,
VARIABLE_ARR_211,
VARIABLE_ARR_212,
VARIABLE_ARR_213,
VARIABLE_ARR_214,
VARIABLE_ARR_215,
VARIABLE_ARR_216,
VARIABLE_ARR_217,
VARIABLE_ARR_218,
VARIABLE_ARR_219,
VARIABLE_ARR_220,
VARIABLE_ARR_221,
VARIABLE_ARR_222,
VARIABLE_ARR_223,
VARIABLE_ARR_224,
VARIABLE_ARR_225,
VARIABLE_ARR_226,
VARIABLE_ARR_227,
VARIABLE_ARR_228,
VARIABLE_ARR_229,
VARIABLE_ARR_230,
VARIABLE_ARR_231,
VARIABLE_ARR_232,
VARIABLE_ARR_233,
VARIABLE_ARR_234,
VARIABLE_ARR_235,
VARIABLE_ARR_236,
VARIABLE_ARR_237,
VARIABLE_ARR_238,
VARIABLE_ARR_239,
VARIABLE_ARR_240,
VARIABLE_ARR_241,
VARIABLE_ARR_242,
VARIABLE_ARR_243,
VARIABLE_ARR_244,
VARIABLE_ARR_245,
VARIABLE_ARR_246,
VARIABLE_ARR_247,
VARIABLE_ARR_248,
VARIABLE_ARR_249,
VARIABLE_ARR_250,
VARIABLE_ARR_251,
VARIABLE_ARR_252,
VARIABLE_ARR_253,
VARIABLE_ARR_254,
VARIABLE_ARR_255,
VARIABLE_ARR_256,
VARIABLE_ARR_257,
VARIABLE_ARR_258,
VARIABLE_ARR_259,
VARIABLE_ARR_260,
VARIABLE_ARR_261,
VARIABLE_ARR_262,
VARIABLE_ARR_263,
VARIABLE_ARR_264,
VARIABLE_ARR_265,
VARIABLE_ARR_266,
VARIABLE_ARR_267,
VARIABLE_ARR_268,
VARIABLE_ARR_269,
VARIABLE_ARR_270,
VARIABLE_ARR_271,
VARIABLE_ARR_272,
VARIABLE_ARR_273,
VARIABLE_ARR_274,
VARIABLE_ARR_275,
VARIABLE_ARR_276,
VARIABLE_ARR_277,
VARIABLE_ARR_278,
VARIABLE_ARR_279,
VARIABLE_ARR_280,
VARIABLE_ARR_281,
VARIABLE_ARR_282,
VARIABLE_ARR_283,
VARIABLE_ARR_284,
VARIABLE_ARR_285,
VARIABLE_ARR_286,
VARIABLE_ARR_287,
VARIABLE_ARR_288,
VARIABLE_ARR_289,
VARIABLE_ARR_290,
VARIABLE_ARR_291,
VARIABLE_ARR_292,
VARIABLE_ARR_293,
VARIABLE_ARR_294,
VARIABLE_ARR_295,
VARIABLE_ARR_296,
VARIABLE_ARR_297,
VARIABLE_ARR_298,
VARIABLE_ARR_299,
VARIABLE_ARR_300,
VARIABLE_ARR_301,
VARIABLE_ARR_302,
VARIABLE_ARR_303,
VARIABLE_ARR_304,
VARIABLE_ARR_305,
VARIABLE_ARR_306,
VARIABLE_ARR_307,
VARIABLE_ARR_308,
VARIABLE_ARR_309,
VARIABLE_ARR_310,
VARIABLE_ARR_311,
VARIABLE_ARR_312,
VARIABLE_ARR_313,
VARIABLE_ARR_314,
VARIABLE_ARR_315,
VARIABLE_ARR_316,
VARIABLE_ARR_317,
VARIABLE_ARR_318,
VARIABLE_ARR_319,
VARIABLE_ARR_320,
VARIABLE_ARR_321,
VARIABLE_ARR_322,
VARIABLE_ARR_323,
VARIABLE_ARR_324,
VARIABLE_ARR_325,
VARIABLE_ARR_326,
VARIABLE_ARR_327,
VARIABLE_ARR_328,
VARIABLE_ARR_329,
VARIABLE_ARR_330,
VARIABLE_ARR_331,
VARIABLE_ARR_332,
VARIABLE_ARR_333,
VARIABLE_ARR_334,
VARIABLE_ARR_335,
VARIABLE_ARR_336,
VARIABLE_ARR_337,
VARIABLE_ARR_338,
VARIABLE_ARR_339,
VARIABLE_ARR_340,
VARIABLE_ARR_341,
VARIABLE_ARR_342,
VARIABLE_ARR_343,
VARIABLE_ARR_344,
VARIABLE_ARR_345,
VARIABLE_ARR_346,
VARIABLE_ARR_347,
VARIABLE_ARR_348,
VARIABLE_ARR_349,
VARIABLE_ARR_350,
VARIABLE_ARR_351,
VARIABLE_ARR_352,
VARIABLE_ARR_353,
VARIABLE_ARR_354,
VARIABLE_ARR_355,
VARIABLE_ARR_356,
VARIABLE_ARR_357,
VARIABLE_ARR_358,
VARIABLE_ARR_359,
VARIABLE_ARR_360,
VARIABLE_ARR_361,
VARIABLE_ARR_362,
VARIABLE_ARR_363,
VARIABLE_ARR_364,
VARIABLE_ARR_365,
VARIABLE_ARR_366,
VARIABLE_ARR_367,
VARIABLE_ARR_368,
VARIABLE_ARR_369,
VARIABLE_ARR_370,
VARIABLE_ARR_371,
VARIABLE_ARR_372,
VARIABLE_ARR_373,
VARIABLE_ARR_374,
VARIABLE_ARR_375,
VARIABLE_ARR_376,
VARIABLE_ARR_377,
VARIABLE_ARR_378,
VARIABLE_ARR_379,
VARIABLE_ARR_380,
VARIABLE_ARR_381,
VARIABLE_ARR_382,
VARIABLE_ARR_383,
VARIABLE_ARR_384,
VARIABLE_ARR_385,
VARIABLE_ARR_386,
VARIABLE_ARR_387,
VARIABLE_ARR_388,
VARIABLE_ARR_389,
VARIABLE_ARR_390,
VARIABLE_ARR_391,
VARIABLE_ARR_392,
VARIABLE_ARR_393,
VARIABLE_ARR_394,
VARIABLE_ARR_395,
VARIABLE_ARR_396,
VARIABLE_ARR_397,
VARIABLE_ARR_398,
VARIABLE_ARR_399,
VARIABLE_ARR_400,
VARIABLE_ARR_401,
VARIABLE_ARR_402,
VARIABLE_ARR_403,
VARIABLE_ARR_404,
VARIABLE_ARR_405,
VARIABLE_ARR_406,
VARIABLE_ARR_407,
VARIABLE_ARR_408,
VARIABLE_ARR_409,
VARIABLE_ARR_410,
VARIABLE_ARR_411,
VARIABLE_ARR_412,
VARIABLE_ARR_413,
VARIABLE_ARR_414,
VARIABLE_ARR_415,
VARIABLE_ARR_416,
VARIABLE_ARR_417,
VARIABLE_ARR_418,
VARIABLE_ARR_419,
VARIABLE_ARR_420,
VARIABLE_ARR_421,
VARIABLE_ARR_422,
VARIABLE_ARR_423,
VARIABLE_ARR_424,
VARIABLE_ARR_425,
VARIABLE_ARR_426,
VARIABLE_ARR_427,
VARIABLE_ARR_428,
VARIABLE_ARR_429,
VARIABLE_ARR_430,
VARIABLE_ARR_431,
VARIABLE_ARR_432,
VARIABLE_ARR_433,
VARIABLE_ARR_434,
VARIABLE_ARR_435,
VARIABLE_ARR_436,
VARIABLE_ARR_437,
VARIABLE_ARR_438,
VARIABLE_ARR_439,
VARIABLE_ARR_440,
VARIABLE_ARR_441,
VARIABLE_ARR_442,
VARIABLE_ARR_443,
VARIABLE_ARR_444,
VARIABLE_ARR_445,
VARIABLE_ARR_446,
VARIABLE_ARR_447,
VARIABLE_ARR_448,
VARIABLE_ARR_449,
VARIABLE_ARR_450,
VARIABLE_ARR_451,
VARIABLE_ARR_452,
VARIABLE_ARR_453,
VARIABLE_ARR_454,
VARIABLE_ARR_455,
VARIABLE_ARR_456,
VARIABLE_ARR_457,
VARIABLE_ARR_458,
VARIABLE_ARR_459,
VARIABLE_ARR_460,
VARIABLE_ARR_461,
VARIABLE_ARR_462,
VARIABLE_ARR_463,
VARIABLE_ARR_464,
VARIABLE_ARR_465,
VARIABLE_ARR_466,
VARIABLE_ARR_467,
VARIABLE_ARR_468,
VARIABLE_ARR_469,
VARIABLE_ARR_470,
VARIABLE_ARR_471,
VARIABLE_ARR_472,
VARIABLE_ARR_473,
VARIABLE_ARR_474,
VARIABLE_ARR_475,
VARIABLE_ARR_476,
VARIABLE_ARR_477,
VARIABLE_ARR_478,
VARIABLE_ARR_479,
VARIABLE_ARR_480,
VARIABLE_ARR_481,
VARIABLE_ARR_482,
VARIABLE_ARR_483,
VARIABLE_ARR_484,
VARIABLE_ARR_485,
VARIABLE_ARR_486,
VARIABLE_ARR_487,
VARIABLE_ARR_488,
VARIABLE_ARR_489,
VARIABLE_ARR_490,
VARIABLE_ARR_491,
VARIABLE_ARR_492,
VARIABLE_ARR_493,
VARIABLE_ARR_494,
VARIABLE_ARR_495,
VARIABLE_ARR_496,
VARIABLE_ARR_497,
VARIABLE_ARR_498,
VARIABLE_ARR_499,
VARIABLE_ARR_500,
VARIABLE_ARR_501,
VARIABLE_ARR_502,
VARIABLE_ARR_503,
VARIABLE_ARR_504,
VARIABLE_ARR_505,
VARIABLE_ARR_506,
VARIABLE_ARR_507,
VARIABLE_ARR_508,
VARIABLE_ARR_509,
VARIABLE_ARR_510,
VARIABLE_ARR_511,
VARIABLE_ARR_512,
VARIABLE_ARR_513,
VARIABLE_ARR_514,
VARIABLE_ARR_515,
VARIABLE_ARR_516,
VARIABLE_ARR_517,
VARIABLE_ARR_518,
VARIABLE_ARR_519,
VARIABLE_ARR_520,
VARIABLE_ARR_521,
VARIABLE_ARR_522,
VARIABLE_ARR_523,
VARIABLE_ARR_524,
VARIABLE_ARR_525,
VARIABLE_ARR_526,
VARIABLE_ARR_527,
VARIABLE_ARR_528,
VARIABLE_ARR_529,
VARIABLE_ARR_530,
VARIABLE_ARR_531,
VARIABLE_ARR_532,
VARIABLE_ARR_533,
VARIABLE_ARR_534,
VARIABLE_ARR_535,
VARIABLE_ARR_536,
VARIABLE_ARR_537,
VARIABLE_ARR_538,
VARIABLE_ARR_539,
VARIABLE_ARR_540,
}ArrIndexDef;
typedef enum
{
VariablePtrIndex0,
VariablePtrIndex1,
VariablePtrIndex2,
VariablePtrIndex3,
VariablePtrIndex4,
VariablePtrIndex5,
VariablePtrIndex6,
VariablePtrIndex7,
VariablePtrIndex8,
VariablePtrIndex9,
VariablePtrIndex10,
VariablePtrIndex11,
VariablePtrIndex12,
VariablePtrIndex13,
VariablePtrIndex14,
VariablePtrIndex15,
VariablePtrIndex16,
VariablePtrIndex17,
VariablePtrIndex18,
VariablePtrIndex19,
VariablePtrIndex20,
VariablePtrIndex21,
VariablePtrIndex22,
VariablePtrIndex23,
VariablePtrIndex24,
VariablePtrIndex25,
VariablePtrIndex26,
VariablePtrIndex27,
VariablePtrIndex28,
VariablePtrIndex29,
VariablePtrIndex30,
VariablePtrIndex31,
VariablePtrIndex32,
VariablePtrIndex33,
VariablePtrIndex34,
VariablePtrIndex35,
VariablePtrIndex36,
VariablePtrIndex37,
VariablePtrIndex38,
VariablePtrIndex39,
VariablePtrIndex40,
VariablePtrIndex41,
VariablePtrIndex42,
VariablePtrIndex43,
VariablePtrIndex44,
VariablePtrIndex45,
VariablePtrIndex46,
VariablePtrIndex47,
VariablePtrIndex48,
VariablePtrIndex49,
VariablePtrIndex50,
VariablePtrIndex51,
VariablePtrIndex52,
VariablePtrIndex53,
VariablePtrIndex54,
VariablePtrIndex55,
VariablePtrIndex56,
VariablePtrIndex57,
VariablePtrIndex58,
VariablePtrIndex59,
VariablePtrIndex60,
VariablePtrIndex61,
VariablePtrIndex62,
VariablePtrIndex63,
VariablePtrIndex64,
VariablePtrIndex65,
VariablePtrIndex66,
VariablePtrIndex67,
VariablePtrIndex68,
VariablePtrIndex69,
VariablePtrIndex70,
VariablePtrIndex71,
VariablePtrIndex72,
VariablePtrIndex73,
VariablePtrIndex74,
VariablePtrIndex75,
VariablePtrIndex76,
VariablePtrIndex77,
VariablePtrIndex78,
VariablePtrIndex79,
VariablePtrIndex80,
VariablePtrIndex81,
VariablePtrIndex82,
VariablePtrIndex83,
VariablePtrIndex84,
VariablePtrIndex85,
VariablePtrIndex86,
VariablePtrIndex87,
VariablePtrIndex88,
VariablePtrIndex89,
VariablePtrIndex90,
VariablePtrIndex91,
VariablePtrIndex92,
VariablePtrIndex93,
VariablePtrIndex94,
VariablePtrIndex95,
VariablePtrIndex96,
VariablePtrIndex97,
VariablePtrIndex98,
VariablePtrIndex99,
VariablePtrIndex100,
VariablePtrIndex101,
VariablePtrIndex102,
VariablePtrIndex103,
VariablePtrIndex104,
VariablePtrIndex105,
VariablePtrIndex106,
VariablePtrIndex107,
VariablePtrIndex108,
VariablePtrIndex109,
VariablePtrIndex110,
VariablePtrIndex111,
VariablePtrIndex112,
VariablePtrIndex113,
VariablePtrIndex114,
VariablePtrIndex115,
VariablePtrIndex116,
VariablePtrIndex117,
VariablePtrIndex118,
VariablePtrIndex119,
VariablePtrIndex120,
VariablePtrIndex121,
VariablePtrIndex122,
VariablePtrIndex123,
VariablePtrIndex124,
VariablePtrIndex125,
VariablePtrIndex126,
VariablePtrIndex127,
VariablePtrIndex128,
VariablePtrIndex129,
VariablePtrIndex130,
VariablePtrIndex131,
VariablePtrIndex132,
VariablePtrIndex133,
VariablePtrIndex134,
VariablePtrIndex135,
VariablePtrIndex136,
VariablePtrIndex137,
VariablePtrIndex138,
VariablePtrIndex139,
VariablePtrIndex140,
VariablePtrIndex141,
VariablePtrIndex142,
VariablePtrIndex143,
VariablePtrIndex144,
VariablePtrIndex145,
VariablePtrIndex146,
VariablePtrIndex147,
VariablePtrIndex148,
VariablePtrIndex149,
VariablePtrIndex150,
VariablePtrIndex151,
VariablePtrIndex152,
VariablePtrIndex153,
VariablePtrIndex154,
VariablePtrIndex155,
VariablePtrIndex156,
VariablePtrIndex157,
VariablePtrIndex158,
VariablePtrIndex159,
VariablePtrIndex160,
VariablePtrIndex161,
VariablePtrIndex162,
VariablePtrIndex163,
VariablePtrIndex164,
VariablePtrIndex165,
VariablePtrIndex166,
VariablePtrIndex167,
VariablePtrIndex168,
VariablePtrIndex169,
VariablePtrIndex170,
VariablePtrIndex171,
VariablePtrIndex172,
VariablePtrIndex173,
VariablePtrIndex174,
VariablePtrIndex175,
VariablePtrIndex176,
VariablePtrIndex177,
VariablePtrIndex178,
VariablePtrIndex179,
VariablePtrIndex180,
VariablePtrIndex181,
VariablePtrIndex182,
VariablePtrIndex183,
VariablePtrIndex184,
VariablePtrIndex185,
VariablePtrIndex186,
VariablePtrIndex187,
VariablePtrIndex188,
VariablePtrIndex189,
VariablePtrIndex190,
VariablePtrIndex191,
VariablePtrIndex192,
VariablePtrIndex193,
VariablePtrIndex194,
VariablePtrIndex195,
VariablePtrIndex196,
VariablePtrIndex197,
VariablePtrIndex198,
VariablePtrIndex199,
VariablePtrIndex200,
VariablePtrIndex201,
VariablePtrIndex202,
VariablePtrIndex203,
VariablePtrIndex204,
VariablePtrIndex205,
VariablePtrIndex206,
}VariablePtrIndexDef;
typedef enum
{
  UnitTableIndex0,
  UnitTableIndex1,
  UnitTableIndex2,
  UnitTableIndex3,
  UnitTableIndex4,
  UnitTableIndex5,
  UnitTableIndex6,
  UnitTableIndex7,
  UnitTableIndex8,
  UnitTableIndex9,
  UnitTableIndex10,
  UnitTableIndex11,
  UnitTableIndex12,
  UnitTableIndex13,
  UnitTableIndex14,
  UnitTableIndex15,
  UnitTableIndex16,
  UnitTableIndex17,
  UnitTableIndex18,
  UnitTableIndex19,
  UnitTableIndex20,
  UnitTableIndex21,
  UnitTableIndex22,
  UnitTableIndex23,
  UnitTableIndex24,
  UnitTableIndex25,
  UnitTableIndex26,
  UnitTableIndex27,
  UnitTableIndex28,
  UnitTableIndex29,
  UnitTableIndex30,
  UnitTableIndex31,
  UnitTableIndex32,
  UnitTableIndex33,
  UnitTableIndex34,
  UnitTableIndex35,
  UnitTableIndex36,
  UnitTableIndex37,
  UnitTableIndex38,
  UnitTableIndex39,
  UnitTableIndex40,
  UnitTableIndex41,
  UnitTableIndex42,
  UnitTableIndex43,
  UnitTableIndex44,
  UnitTableIndex45,
  UnitTableIndex46,
  UnitTableIndex47,
  UnitTableIndex48,
  UnitTableIndex49,
  UnitTableIndex50,
  UnitTableIndex51,
  UnitTableIndex52,
  UnitTableIndex53,
  UnitTableIndex54,
  UnitTableIndex55,
  UnitTableIndex56,
  UnitTableIndex57,
  UnitTableIndex58,
  UnitTableIndex59,
  UnitTableIndex60,
  UnitTableIndex61,
  UnitTableIndex62,
  UnitTableIndex63,
  UnitTableIndex64,
  UnitTableIndex65,
  UnitTableIndex66,
  UnitTableIndex67,
  UnitTableIndex68,
  UnitTableIndex69,
  UnitTableIndex70,
  UnitTableIndex71,
  UnitTableIndex72,
  UnitTableIndex73,
  UnitTableIndex74,
  UnitTableIndex75,
  UnitTableIndex76,
  UnitTableIndex77,
  UnitTableIndex78,
  UnitTableIndex79,
  UnitTableIndex80,
  UnitTableIndex81,
  UnitTableIndex82,
  UnitTableIndex83,
  UnitTableIndex84,
  UnitTableIndex85,
  UnitTableIndex86,
  UnitTableIndex87,
  UnitTableIndex88,
  UnitTableIndex89,
  UnitTableIndex90,
  UnitTableIndex91,
  UnitTableIndex92,
  UnitTableIndex93,
  UnitTableIndex94,
  UnitTableIndex95,
  UnitTableIndex96,
  UnitTableIndex97,
  UnitTableIndex98,
  UnitTableIndex99,
  UnitTableIndex100,
  UnitTableIndex101,
  UnitTableIndex102,
  UnitTableIndex103,
  UnitTableIndex104,
  UnitTableIndex105,
  UnitTableIndex106,
  UnitTableIndex107,
}UnitTableIndexDef;
//HART��������
typedef enum
{
  UCHAR_T = 1,            //�ַ��ͱ���
  UINT_T = 2,             //�����ͱ���
  FLOAT_T = 4,            //�����ͱ���
  FLOAT1_T,               //1λС���㸡����
  LONG_UINT_T,            //�����ͱ���
  HANDRED_T,              //100���ڵ��ַ�������
  BYTE_VALUE_T,             //255���ڵ���ֵ
  INT_VALUE_T,             //255���ڵ���ֵ
  ASCII_T,                //ASCII���ͱ���
  L_ASCII_T,              //8λASCII
  L_ASCII_1_T,            //8λASCII����1
  FUNC_CODE_T,            //���������ͱ���
  UINT_PERCENTILE_T,     //ǧ�ֱ����ͱ���
  
  CURVE_START_T,        //������㷶Χ������ʶ��0~72
  CURVE_END_T,        //�����յ㷶Χ������ʶ��0.1~72
  FAKE_RANGE_T,//��ٻز���㷶Χ0~70
  FAKE_AMP_T,//��ٻز���ֵ��Χ0~3.3
  PVL_T,//���̵�λ��Χ0.3~70
  PVU_T,//���̸�λ��Χ0~69.7
  MAX_ZOON_T,//��λä�������������ޣ�0.5~70
  MIN_ZOON_T,//��λä�������������ޣ�0~69
  LEVEL_SPD_T,//��λ�ٶȷ�Χ��0.1~70
  SUPRITY_T,//ǰ�����ƣ��ز���ֵ-3~3
  MIN_RESOL_T,//��С�ֱ��ʷ�Χ0~2
}DataTypeDef;
//HART������������ձ�
#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uchar UnitCode;//��λ����
  uchar ArrIndex;//��λ�������
  uint StrIndex; //��λ�ַ������
}HART_UnitDef;
#pragma pack(pop)
//HART��������
#pragma pack(push)
#pragma pack(1)
typedef struct
{
  CommandDef CommandIndex;//��ȡ�ñ�����Ҫ�ṩHARTЭ���������
  DataLengthDef DataLength;//���ݳ���
  DataLengthDef AnalysisLength;//���ս�������
  DataTypeDef DataType;//��������
  VariablePtrIndexDef VariablePtr;//��������ָ��
  UnitTableIndexDef Table;//HART��λ��
}HART_VariableDef;
#pragma pack(pop)


//��ǰҳ��HART���������ṹ�嶨�壬���а����˵�ǰҳ����ص�HART�����ĸ�����
//�Լ����������ŵ�����ָ��
//ע����������Ƿ񳬹�256��������Ҫ�޸���������
#pragma pack(push)
#pragma pack(1)
//���������������¼��ҳ���ϰ󶨵ı������Ŷ�Ӧ�ı����������ж��ٸ�������
//�Լ�������Щ��������ĵ�ַ������ͨ����ַ��ȡflash�жϱ��������ݡ�
typedef struct
{
  uchar CurrentPageVariableNumber;
  uint CurrentPageVariableBuffIndex;
}HART_VariableIndexDef;
#pragma pack(pop)
//��ǰҳ����ִ��˳���
//�������嵱ǰҳ�������ִ������ṹ
typedef struct
{
  uchar CurrentPageCommandNumber;
  uchar CurrentCommandIndex;
  uchar ResendCounter;
  CommandDef *CurrentPageCommandBuff;
}CommandExecuteBuffDef;

//HARTִ�б�־����
typedef enum
{
  HART_STANDBY,                                 //�ȴ�
  HART_POLLING,                                 //��ѯ
  HART_START_INIT,                              //��ʼ�������ʼ����
  HART_INIT_COMPLETE,                           //��ʼ�����ʼ�����
  HART_INIT_COMMAND_HANDLE,                     //��ʼ���������״̬��
  HART_COMMAND_RESEND,                          //�����ط�
  HART_INIT_ERR,                                //��ʼ������״̬����������������δ�ӵ���Ӧ
  HART_COMMON_ERR,                              //����ͨ�Ŵ���״̬����������������δ�ӵ���Ӧ
  HART_START_COMMON,                //ͨ�ý������ʼ����״̬��
  HART_COMMON_COMMAND_HANDLE,//ͨ�ý��������״̬
  HART_COMMON_COMPLETE,//ͨ�ý�������������
  HART_POLL_ERR,
}HART_HandleFlagDef;

//��д״̬��־ö�ٶ���
typedef enum 
{
  WRITE,READ
}W_R_FlagDef;
//HART����֡�ṹ����
#pragma pack(push)
#pragma pack(1)
typedef struct
{
  CommandDef Command;           //����
  uchar LeadCodeNumber;         //ǰ�����ֽڸ���
  W_R_FlagDef W_R_Flag;         //��д״̬
  uchar Delimiter;              //�����
  uchar AddrByteNumber;         //��ַ�ֽڸ���
  uchar AddrBuff[SLAVE_ADDR_BUFF_SIZE];//��ַ�����׵�ַָ��
  uchar DataByteNumber;         //�����ֽڸ���
  uchar *DataBuff;              //���������յ�ַ
}HART_SendFrameDef;
#pragma pack(pop)
//HART����֡�ṹ����
#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uchar Delimiter;                      //�����
  CommandDef Command;                        //����
  uchar DataByteNumber;                 //�����ֽڸ���
  uchar *DataBuff;                      //���������յ�ַ
  uchar Checkout;                       //У��
}HART_ReceiveFrameDef;
#pragma pack(pop)
//HART����״̬��־����
typedef enum
{
  //����ģ�����״̬��
  REC_STANDBY = 0x00,
  //����ģ�����״̬��
  REC_COMPLETE = 0X01,
  //����ģ�鲻׼ȷ��
  REC_INCORRECT,
  //��֡�����ꡣ
  SHORT_FRAME = 0x03,
  //��֡������
  LONG_FRAME = 0x07,
  //��Ӧ��˵�����ӻ���Ӧ��Я����Ϣ��Ҫ����������ʾ
  RESPOND_CODE_EXPRESSION,
  //ǰ�������ֱ�Ǻꡣ
  LEAD_CODE = 0x5A,
  //��Ϣ�������ֱ�Ǻꡣ
  INFO_CODE = 0xA5,
  //����ģ�����������־��
  REC_ERR = 0xAA
}HART_ReceiveFlag;




//HARTЭ�鶨�������
typedef enum
{
  LONG_FRAME_REQUEST = 0x82,
  SHORT_FRAME_REQUEST = 0x02,
  LONG_FRAME_RESPOND = 0x86,
  SHORT_FRAME_RESPOND = 0x06
}HART_DelimiterDef;

//HART��������ṹ����
#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uchar ArrIndex;                               //���ͽṹ���������
  CommandDef Command;                           //����
  HART_DelimiterDef Delimiter;	                //�����
  W_R_FlagDef W_R_Flag;                         //��д״̬
  uchar AddrByteNumber;                         //��ַ�ֽڸ���
  uchar VariableByteNumber;                     //�����ֽڸ���
  uchar VariableIndexNumber;    	        //��������
  ArrIndexDef   VariableIndex;                 //�����������      
}HART_SendStructDef;
#pragma pack(pop)
//HART��������ṹ����
#pragma pack(push)
#pragma pack(1)
typedef struct
{
  uchar ArrIndex;                               //���ܽṹ���������
  CommandDef Command;                           //����
  W_R_FlagDef W_R_Flag;                         //��д״̬
  ArrIndexDef   VariableIndex;                 //�����������       
}HART_ReceiveStructDef;
#pragma pack(pop)
//HART�շ�ʹ�ܱ�־����

typedef enum
{
  SEND_START = 0,
  RECEIVE_START = 1
}HART_RS_Flag;



//���������Ͷ���
typedef enum
{
  INTERNAL_VARIABLE,
  EXTERNAL_VARIABLE,
  HART_VARIABLE  
}HART_VariableTypeDef;

//ִ������������� 
//���ܲ��䡣��������
typedef enum 
{
  NO_COMMAND = 0,
  MORE_COMMAND,
  TEST_COMMAND
}PageCommandNumDef;


typedef enum
{
  HART_VERSION_LOW = 4,
  HART_VERSION_5 = 5,
  HART_VERSION_6 = 6,
  HART_VERSION_7 = 7,
}HART_VersionDef;
typedef enum
{
  HART_VERSION_LOW_BM = 0x0c,
  HART_VERSION5_BM = 0x0e,
  HART_VERSION6_BM = 0x13,
  HART_VERSION7_BM = 0x18,
}HART_VersionByteNumDef;
//HART���ݱ����ṹ
typedef struct
{
  DataLengthDef DataLength;//�����������ݳ���
  uchar Buff[ASCII_42];//�����洢����
  uchar *DataPtr;//������������ַָ��
  bool8 LoadLock;//���ݱ�����
}VariableProtectDef;
typedef enum 
{
  WRITE_PROTECT,
  POSSIBLE_VALUE,
  VALUE_SMALL,
  VALUE_LARGE,
  EXC_CORRECTION,
  SPAN_SMALL,
  INVALID_SELECTION,
  INVALID_FUNCTION,
  ABORTING_STATUS,
  NOT_IMPLEMENTED,
  INVALID_TRIM_TYPE,
  UPPER_HIGH,
  UPPER_LOW,
  LOWER_HIGH,
  LOWER_LOW,
  OTHER_ANOMALY,//test
  COMMUNICATION_ERR,
  MULTIDROP_MODE,
  PROCESS_HIGH,
  PROCESS_LOW,
  NEW_LRV_PUSHED,
  ABNORMAL_STANDBY,
}AbnormalStatusDef;

typedef union
{
  HART_VariableDef VariableStructureInfo;
  uchar VariableStructure[sizeof(HART_VariableDef)];
}VariableStructureDef;

typedef union
{
  HART_VariableIndexDef PageVariableInfo;
  uchar PageVariableStructure[sizeof(HART_VariableIndexDef)];
}PageVariableTableDef;

typedef union
{
  HART_ReceiveStructDef ReceiveStructInfo;
  uchar ReceiveStruct[sizeof(HART_ReceiveStructDef)];
}ReceiveStructureDef;

typedef union
{
  HART_SendStructDef SendStructInfo;
  uchar SendStruct[sizeof(HART_SendStructDef)];
}SendStructureDef;

typedef union
{
  uint VariableGroupI[VARIABLE_GROUP_SIZE];
  uchar VariableGroupC[sizeof(uint)*VARIABLE_GROUP_SIZE];
}VariableGroupDef;

CommandExecuteBuffDef G_CurrentPageCommandExecuteStructure;
extern CommandDef G_HART_ReceiveTableRealCommandID;




extern HART_HandleFlagDef G_HART_HandleFlag;
extern const HART_VariableDef G_VariableStructure[];
extern  const uint G_VariableGroupAddress[];

extern uchar G_254[UCHAR];
extern uchar G_ManufacturerID[UCHAR];
extern uchar G_DeviceType[UCHAR];
extern uchar G_NumRegPreams[UCHAR];
extern uchar G_NumRegPreamsSM[UCHAR];

extern uchar G_UniversalRev[UCHAR];
extern uchar G_FldDevRev[UCHAR];
extern uchar G_SoftwareRev[UCHAR];
extern uchar G_HardwareRev[UCHAR];
extern uchar G_DeviceMark[UCHAR];
extern uchar G_DeviceID[THREE_BYTES];
  
extern uchar G_PV_Unit[UCHAR];
extern uchar G_UnitTemp[UCHAR];
extern uchar G_PV[FLOAT];
 
extern uchar G_PV_Current[FLOAT];
extern uchar G_PercentOfPV[FLOAT];
extern uchar G_AO1[UCHAR];
extern uchar G_SV_Unit[UCHAR];
extern uchar G_SV[FLOAT];
extern uchar G_TV_Unit[UCHAR];
extern uchar G_TV[FLOAT];
extern uchar G_QV_Unit[UCHAR];
extern uchar G_QV[FLOAT];
;

extern uchar G_Message[ASCII_24];
  
extern uchar G_Tag[ASCII_6];
extern uchar G_Description[ASCII_12];
extern uchar G_Date[THREE_BYTES];
  
extern uchar G_PV_SnsrSN[THREE_BYTES];
extern uchar G_PV_SnsrUNIT[UCHAR];
extern uchar G_PV_SnsrLSL[FLOAT];
extern uchar G_PV_SnsrUSL[FLOAT];
extern uchar G_PV_MinSpan[FLOAT];

extern uchar G_PV_AlarmSelectCode[UCHAR];
extern uchar G_PV_TransferCode[UCHAR];
extern uchar G_PV_RangeUnit[UCHAR];
extern uchar G_PV_USL[FLOAT];
extern uchar G_PV_LSL[FLOAT];
extern uchar G_PV_DampValue[FLOAT];
extern uchar G_WriteProtect[UCHAR];
extern uchar G_PrivateLabelDistributorCode[UINT];




extern uchar G_AssemblyNum[THREE_BYTES];

extern uchar G_OutputLevel[FLOAT];
extern uchar G_None[LONG_UINT];

extern uchar G_XferFnctn[UCHAR];
extern uchar G_BatteryPercent[UCHAR];

extern const HART_VariableIndexDef G_HART_PageVariableArr[];
extern const HART_ReceiveStructDef G_HART_V5_ReceiveStruct[];

extern const HART_UnitDef G_AddrTable[];

extern HART_VersionDef HART_VersionFlag;
extern uchar G_SlaveAddrBuff[SLAVE_ADDR_BUFF_SIZE];
extern uchar G_MeterValue[ASCII_7];
extern uchar G_DampUnit[UCHAR];
extern VariableProtectDef G_VariableProtect;

extern const HART_UnitDef G_GeneralUnitTable[];
extern const HART_UnitDef G_GeneralFunctionTable[];
extern const HART_UnitDef G_GeneralWriteProtectTable[];
extern const HART_UnitDef G_A0_AlarmTypeTable[];
extern const HART_UnitDef G_CY_TTS_SnsrTypeTable[];
extern const HART_UnitDef G_CY_TTS_SnsrModelTable[];
extern const HART_UnitDef G_CY_TTS_SnsrWiresTable[];
extern const HART_UnitDef G_CY_TTS_SnsrModel_1Table[];
extern const HART_UnitDef G_DisplayPressTypeTable[];
extern const HART_UnitDef G_ManufacturerCodeTable[];
extern const HART_UnitDef G_DeviceTypeTable[];
extern const HART_UnitDef G_CutModeFunctionTable[];
extern const HART_UnitDef G_CutMode530FunctionTable[];
extern const HART_UnitDef G_BiDirModeTable[];
extern const HART_UnitDef G_H20UnitTable[];
extern const HART_UnitDef G_RemoteSealTable[];
extern const HART_UnitDef G_FlangeTypeTable[];
extern const HART_UnitDef G_SealFillFluidTable[];
extern const HART_UnitDef G_NumOfRmtSealTable[];
extern const HART_UnitDef G_ModuleFillFluidTable[];
extern const HART_UnitDef G_DisplayModeTable[];
extern const HART_UnitDef G_EngrDispPointTable[];
extern const HART_UnitDef G_FlangeMaterialTable[];
extern const HART_UnitDef G_SoftwareSealTable[];
extern const HART_UnitDef G_ExtSWTable[];
extern const HART_UnitDef G_Eja530UnitTable[];
extern const HART_UnitDef G_Eja530EngrUnitTable[];
extern const HART_UnitDef G_DispOutTable[];
extern const HART_UnitDef G_ResoTable[];
extern const HART_UnitDef G_EngrExpTable[];
extern const HART_UnitDef G_OringMaterialTable[];
extern const HART_UnitDef G_MeterTypeTable[];
extern const HART_UnitDef G_LocalKeysTable[];
extern const HART_UnitDef G_NoneTable[];
extern const HART_UnitDef G_SngrTrimCalTypeTable[];
extern const HART_UnitDef G_SelDecPtPosTable[];
extern const HART_UnitDef G_LM_FlangeTypeTable[];
extern const HART_UnitDef G_OringMaterialTable[];
extern const HART_UnitDef G_LM_RemoteSealTable[];
extern const HART_UnitDef G_LM_SealFillFluidTable[];
extern const HART_UnitDef G_AlarmSatTable[];
extern const HART_UnitDef G_RADAR_DielTable[];
extern const HART_UnitDef G_RADAR_LogicSelectTable[];
extern const HART_UnitDef G_RadarELOTable[];
extern const HART_UnitDef G_RadarCurrentDirTable[];
extern const HART_UnitDef G_RadarJumpModeTable[];
extern const HART_UnitDef G_RadarCurrentOptTable[];
extern const HART_UnitDef G_RadarPollModeTable[];
extern const HART_UnitDef G_CY_T1_CurrentTable[];
extern const HART_UnitDef G_CY_HVP_YFCT_Table[];
extern const HART_UnitDef G_CY_HVP_SFCT_Table[];
extern const HART_UnitDef G_CY_HVP_AFCT_Table[];
extern const HART_UnitDef G_CY_HVP_YCLS_Table[];

extern const HART_UnitDef G_HW_DisplayPointTable[];
extern const HART_UnitDef G_HW_DisplayUnitTable[];
extern const HART_UnitDef G_HW_DisplaySetupTable[];

extern const HART_UnitDef G_AlarmSelectionCodesTable[];
extern const HART_UnitDef G_DispPresResoTable[];
extern const HART_UnitDef G_QuickRespTable[];
extern const HART_UnitDef G_CY_PDS7DispValueTable[];




extern const HART_UnitDef G_SquawkControlCodes[];
extern const HART_UnitDef G_ResponsModeCodes[];


extern uchar G_WriteProtectSet[UCHAR];
extern uchar G_SIEMENS_UpSnsrTrim[FLOAT];
extern uchar G_SIEMENS_LoSnsrTrim[FLOAT];
extern uchar G_SIEMENS_RootingCode[UCHAR];

extern uchar G_SIEMENS_RootingWriteCode[UINT];
extern uchar G_LongTag[ASCII_33];
extern uchar G_CHUAN_YI_VariableDisMode[UINT];
extern uchar G_CHUAN_YI_RootCutoffPt[UINT];
extern uchar G_CHUAN_YI_TransmitterType[UINT];

extern uchar G_WriteProtectCancel[UCHAR];
extern uchar G_CHUAN_YI_AO_AlarmType[UCHAR];
extern uchar G_CHUAN_YI_DisplayPressType[UINT];
extern uchar G_PollingAddress[UCHAR];
extern uchar G_CurrentMode[UCHAR];






//������
extern uchar G_RadarCurveEndP[FLOAT];
extern uchar G_RadarCurvePoint1[ASCII_20];
extern uchar G_RadarCurvePoint2[ASCII_20];
extern uchar G_RadarCurvePoint3[ASCII_20];
extern uchar G_RadarCurvePoint4[ASCII_20];
extern uchar G_RadarCurvePoint5[ASCII_20];





//Public variable float
extern uchar G_PublicVF0[FLOAT];
extern uchar G_PublicVF1[FLOAT];
extern uchar G_PublicVF2[FLOAT];
extern uchar G_PublicVF3[FLOAT];
extern uchar G_PublicVF4[FLOAT];
extern uchar G_PublicVF5[FLOAT];
extern uchar G_PublicVF6[FLOAT];
extern uchar G_PublicVF7[FLOAT];
extern uchar G_PublicVF8[FLOAT];
extern uchar G_PublicVF9[FLOAT];
extern uchar G_PublicVF10[FLOAT];
extern uchar G_PublicVF11[FLOAT];
extern uchar G_PublicVF12[FLOAT];
extern uchar G_PublicVF13[FLOAT];
extern uchar G_PublicVF14[FLOAT];
extern uchar G_PublicVF15[FLOAT];
extern uchar G_PublicVF16[FLOAT];
extern uchar G_PublicVF17[FLOAT];
extern uchar G_PublicVF18[FLOAT];
extern uchar G_PublicVF19[FLOAT];
extern uchar G_PublicVF20[FLOAT];
extern uchar G_PublicVF21[FLOAT];
extern uchar G_PublicVF22[FLOAT];
extern uchar G_PublicVF23[FLOAT];
extern uchar G_PublicVF24[FLOAT];
extern uchar G_PublicVF25[FLOAT];
extern uchar G_PublicVF26[FLOAT];
extern uchar G_PublicVF27[FLOAT];
extern uchar G_PublicVF28[FLOAT];
extern uchar G_PublicVF29[FLOAT];
extern uchar G_PublicVF30[FLOAT];
extern uchar G_PublicVF31[FLOAT];
extern uchar G_PublicVF32[FLOAT];
extern uchar G_PublicVF33[FLOAT];
extern uchar G_PublicVF34[FLOAT];
extern uchar G_PublicVF35[FLOAT];
extern uchar G_PublicVF36[FLOAT];
extern uchar G_PublicVF37[FLOAT];
extern uchar G_PublicVF38[FLOAT];
extern uchar G_PublicVF39[FLOAT];
extern uchar G_PublicVF40[FLOAT];

//Public variable uchar
extern uchar G_PublicVC0[UCHAR];
extern uchar G_PublicVC1[UCHAR];
extern uchar G_PublicVC2[UCHAR];
extern uchar G_PublicVC3[UCHAR];
extern uchar G_PublicVC4[UCHAR];
extern uchar G_PublicVC5[UCHAR];
extern uchar G_PublicVC6[UCHAR];
extern uchar G_PublicVC7[UCHAR];
extern uchar G_PublicVC8[UCHAR];
extern uchar G_PublicVC9[UCHAR];
extern uchar G_PublicVC10[UCHAR];
extern uchar G_PublicVC11[UCHAR];
extern uchar G_PublicVC12[UCHAR];
extern uchar G_PublicVC13[UCHAR];
extern uchar G_PublicVC14[UCHAR];
extern uchar G_PublicVC15[UCHAR];
extern uchar G_PublicVC16[UCHAR];
extern uchar G_PublicVC17[UCHAR];
extern uchar G_PublicVC18[UCHAR];
extern uchar G_PublicVC19[UCHAR];
extern uchar G_PublicVC20[UCHAR];
extern uchar G_PublicVC21[UCHAR];
extern uchar G_PublicVC22[UCHAR];


//public variable uint
extern uchar G_PublicVI0[UINT];
extern uchar G_PublicVI1[UINT];
extern uchar G_PublicVI2[UINT];
extern uchar G_PublicVI3[UINT];
extern uchar G_PublicVI4[UINT];
extern uchar G_PublicVI5[UINT];
extern uchar G_PublicVI6[UINT];
extern uchar G_PublicVI7[UINT];
extern uchar G_PublicVI8[UINT];
extern uchar G_PublicVI9[UINT];
extern uchar G_PublicVI10[UINT];
extern uchar G_PublicVI11[UINT];
extern uchar G_PublicVI12[UINT];
extern uchar G_PublicVI13[UINT];
extern uchar G_PublicVI14[UINT];
extern uchar G_PublicVI15[UINT];
extern uchar G_PublicVI16[UINT];
extern uchar G_PublicVI17[UINT];
extern uchar G_PublicVI18[UINT];
extern uchar G_PublicVI19[UINT];

//public variable long uint
extern uchar G_PublicVLI0[LONG_UINT];
extern uchar G_PublicVLI1[LONG_UINT];
extern uchar G_PublicVLI2[LONG_UINT];
extern uchar G_PublicVLI3[LONG_UINT];
extern uchar G_PublicVLI4[LONG_UINT];
extern uchar G_PublicVLI5[LONG_UINT];
extern uchar G_PublicVLI6[LONG_UINT];
extern uchar G_PublicVLI7[LONG_UINT];
extern uchar G_PublicVLI8[LONG_UINT];
extern uchar G_PublicVLI9[LONG_UINT];
extern uchar G_PublicVLI10[LONG_UINT];
extern uchar G_PublicVLI11[LONG_UINT];
extern uchar G_PublicVLI12[LONG_UINT];
extern uchar G_PublicVLI13[LONG_UINT];
extern uchar G_PublicVLI14[LONG_UINT];
extern uchar G_PublicVLI15[LONG_UINT];
extern uchar G_PublicVLI16[LONG_UINT];
extern uchar G_PublicVLI17[LONG_UINT];
extern uchar G_PublicVLI18[LONG_UINT];



//public variable Unknow
extern uchar G_PublicVUnknowA0[ASCII_16];
extern uchar G_PublicVUnknowA1[ASCII_11];
extern uchar G_PublicVUnknowA2[ASCII_9];
extern uchar G_PublicVUnknowA3[ASCII_16];
extern uchar G_PublicVUnknowA4[ASCII_16];
extern uchar* const G_VariableTablePtr[];
extern const HART_UnitDef* const G_UnitTableIndexPtr[];

extern  HART_ReceiveFlag G_RxFrameVerifyFlag;


extern VariableStructureDef G_VariableStructureInfo;
extern ReceiveStructureDef G_ReceiveStructure;
extern SendStructureDef G_SendStructure;
extern PageVariableTableDef G_PageVariableTable;
extern VariableGroupDef G_VariableGroupTable;


void HART_CommandExecuteArrLoad(CommandDef Command,uchar *CommandIndexCount);
void HART_ResendFlagReset();
uchar HART_ASCII_Decode(uchar *const ASCII_Tag,DataLengthDef ReceiveLength,DataLengthDef ShowDataLength,uchar *const DataRam);
static signed char ModbusFloatToASCIIConvert(float TranFloat,
                                  unsigned char DecimalN,uchar* ShowDataBuffe);
uchar HART_TypeConvert(uchar *const ShowData,uchar *const Temp,DataTypeDef DataType,
                      DataLengthDef DataLength,DataTypeDef ToType);
void HART_ASCII_Code(uchar *const ASCII_Tag,DataLengthDef ReceiveLength,DataLengthDef ShowDataLength,uchar *const DataRam);
bool8 HART_DateHandle(uchar *const DateStr);
bool8 HART_YearHandle(uchar *const Year);
void HART_FloatToData(float FloatData,uchar *ShowData,DataTypeDef Length);
void HART_LongIntToData(long uint LongIntData,uchar *const ShowData,DataTypeDef ShowDataLength);
void HART_IntToData(uint IntData,uchar *const ShowData,DataTypeDef ShowDataLength);
void HART_CharToString(uchar  Data,uchar *const DeviceStr);
void HART_ProtectedVariableGet();
void HART_VariableProtect(uchar *ShowData,DataLengthDef DataLength);
uint HART_UnitShowHandle(const HART_UnitDef *Table,uchar* Variable);
void HART_FloatToChar(float TranFloat,unsigned char DecimalN);
float HART_DataToFloat(uchar *const ShowData,DataTypeDef ShowDataType);
void HART_FrameReceiveHandle();
void HART_CableLengthReset(void);
void HART_DistCalibrateHandle();
void HART_ReceiveSendEN(HART_RS_Flag Flag);
ProductTypeAndID_Def HART_GetProductTypeAndID();
void HART_InfoInit(void);
void HART_AbnormalPageHandle(AbnormalStatusDef ABNORMAL_STANDBY);
void HART_UnitTempLoad(DataTypeDef DataType,bool8 IsVariableHandle,uchar *ShowData);
long uint HART_DataToLongInt(uchar *const ShowData,DataTypeDef ShowDataType );
uchar HART_VersionGet();
#endif
