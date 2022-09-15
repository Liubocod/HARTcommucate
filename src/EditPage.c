/**************************************************************************/

/**************************************************************************/

/****** CONNETECH Electronics Ltd(BeijingRuiDaYiBiaoYouXianGongSi)  ****************/

/**************************************************************************/

/**************************************************************************/

/* Declaration:        */

/*  We (CONNETECH Electronics Ltd，BeijingRuiDaYiBiaoYouXianGongSi)  has the copyright of the following software  */

/*  all the copyright, patent, trademark, trade secret or any other intellectual property infringement of following software belong to CONNETECH Electronics Ltd，BeijingRuiDaYiBiaoYouXianGongSi */

/*  all the copyright, patent, trademark, trade secret or any other intellectual property infringement of following software are the top secret of CONNETECH Electronics Ltd(BeijingRuiDaYiBiaoYouXianGongSi) */

/*  All the behaviors to read, use, copy, change, publish the software are illegal. And all rights reserved */
#include "EditPage.h"
//特殊数据类型判决处理条件
#define IS_SPECIAL_DATA_TYPE_HANDLE (DataType == CURVE_START_T)||(DataType == FLOAT_T)\
  ||(DataType == FLOAT1_T)||(DataType == CURVE_END_T)||(DataType == FAKE_RANGE_T)||(DataType == FAKE_AMP_T)\
                        ||(DataType == PVL_T)||(DataType == PVU_T)||(DataType == MAX_ZOON_T)||(DataType == MIN_ZOON_T)\
                                ||(DataType == LEVEL_SPD_T)||(DataType == SUPRITY_T)||(DataType == MIN_RESOL_T)
//主变量电流值判决处理条件
#define IS_FIXED_CURRENT_HANDLE (PagePtr->ContentStrIndex == STR_INDEX_105)||(PagePtr->ContentStrIndex == STR_INDEX_99)\
                                  ||(PagePtr->ContentStrIndex == STR_INDEX_902)

#define IS_EDIT_PAGE_INPUT_SPECIAL_DISPLAY      ((PagePtr->ContentStrIndex == STR_INDEX_324)||(PagePtr->ContentStrIndex == STR_INDEX_325)\
                ||(PagePtr->ContentStrIndex == STR_INDEX_364)||(PagePtr->ContentStrIndex == STR_INDEX_365)\
                    ||(PagePtr->ContentStrIndex == STR_INDEX_105))&&(G_EditPageInputSpecialShowFlag == TRUE)
#define IS_CY_PDS6_PATCH_1 (PagePtr->ContentStrIndex == STR_INDEX_590)\
                ||(PagePtr->ContentStrIndex == STR_INDEX_370)
#define IS_SPECIAL_RANGE (DataType == CURVE_START_T)||(DataType == CURVE_END_T)||(DataType == FAKE_RANGE_T)\
          ||(DataType == FAKE_AMP_T)||(DataType == PVL_T)||(DataType == PVU_T)||(DataType == HANDRED_T)||(DataType == BYTE_VALUE_T)\
                   ||(DataType == MAX_ZOON_T)||(DataType == MIN_ZOON_T)||(DataType == LEVEL_SPD_T)||(DataType == SUPRITY_T)||(DataType == MIN_RESOL_T)||(DataType == INT_VALUE_T)

static uchar EditPageVariableValueGet(AdditionalInfoDef AdditionFlog,KeyValueDef CharPositionSelectFlag,KeyValueDef KeyValue);
static uchar EditPageCharValueGet(KeyValueDef CharPositionSelectFlag,KeyValueDef KeyValue);
static uchar EditPageKeyCharIndexGet(KeyValueDef KeyValue);
static DataTypeDef EditVariableRangeConfirm(uchar *ShowData,
                              DataTypeDef DataType,const PageDef *CurrentPage);
static void EditInvalidInputReset(void);
static uchar EditDateDisplay(DataLengthDef DataLength,uchar ShowLineTemp);
static uchar EditTagDisplay(DataLengthDef ReceiveDataLength,DataLengthDef DataLength,uchar *ShowData,uchar ShowLineIndex);
static uchar EditSpecialDataTypeHandle(DataTypeDef DataType,uchar ShowLineIndex,uchar *ShowData,DataLengthDef ReceiveDataLength,uchar *UnitStartPosition);
static uchar EditLongIntDataHandle(uchar *ShowData,DataTypeDef DataType,
        DataLengthDef ReceiveDataLength,DataLengthDef DataLength,
                        uchar ShowLineIndex,uchar *UnitStartPosition);
static uchar EditIntDataHandle(uchar *ShowData,
        DataTypeDef DataType,DataLengthDef DataLength,
          uchar ShowLineIndex,uchar *UnitStartPosition);
static void EditFunctionCodeHandle(uint VariableIndex,DataTypeDef DataType,uchar *ShowData,LanguageTypeDef Language,uchar ShowLineIndex);
static void EditUnitDisplay(uint VariableIndex,uchar ShowLineIndex,const PageDef *const PagePtr,uchar UnitStartPosition);

//第20个字节原来为0x00
uchar G_ShowData[ASCII_42] = 
{
  0x20,0x20,0x20,0x20,0x20,0x20,
  0x20,0x20,0x20,0x20,0x20,0x20,
  0x20,0x20,0x20,0x20,0x20,0x20,
  0x20,0x20,0x20,0x20,0x20,0x20,
  0x20,0x20,0x20,0x20,0x20,0x20,
  0x20,0x20,0x20,0x20,0x20,0x20,
  0x20,0x20,0x20,0x20,0x20,0x20,
};

uchar G_VariableArrIndex = 0;
//编辑界面输入特殊显示状态标志。
bool8 G_EditPageInputSpecialShowFlag = TRUE;
/*


typedef struct 
{
  KeyValueDef KeyValue;
  uchar UpValue;
  uchar LeftValue;
  uchar RightValue;
  uchar NumberValue;
}KeyCharDef;


*/ 


const KeyCharDef KeyCharArr[] = 
{
  MINUS,0x3b,0x2a,0x2b,0x2d,
  POINT,0x20,0x3c,0x3e,0x2e,
  ZERO,0x25,0x23,0x26,0x30,
  THREE,0x5a,0x59,0x2f,0x33,
  TWO,0x57,0x56,0x58,0x32,
  ONE,0x54,0x53,0x55,0x31,
  SIX,0x51,0x50,0x52,0x36,
  FIVE,0x4e,0x4d,0x4f,0x35,
  FOUR,0x4b,0x4a,0x4c,0x34,
  NINE,0x48,0x47,0x49,0x39,
  EIGHT,0x45,0x44,0x46,0x38,
  SEVEN,0x42,0x41,0x43,0x37,
};
/*
//函数名称和参量和返回值类型。
KeyValueDef  EditPageCharPositionSelect(AdditionalInfoDef AdditionFlog,KeyValueDef Position)
* 变量范围:
AdditionFlog:页面的附加信息，对一些特殊界面进行说明。
Position：字符位置选择标志，用来选择数字按键上挂载的字符。

* 返回值说明:KeyValueDef 返回数字键挂载字符的位置（左，上，右或无按键）。 
* 功能介绍:   
编辑页面字符位置选择函数，本函数作用是选出数字键挂载的字符所在的位置。

*
* 关键备注：
* - 

  
* 未来提高:

*/ 

KeyValueDef  EditPageCharPositionSelect(AdditionalInfoDef AdditionFlog,KeyValueDef Position)
{
    if(AdditionFlog == CHAR_NUMBER_SHOW)
    {
      return Position;
    }
    return NO_KEY_STATUS;
}
/*
//函数名称和参量和返回值类型。
uchar EditPageKeyCharIndexGet(KeyValueDef KeyValue);
* 变量范围:
KeyValue：数据输入按键值，范围0-9，负号和小数点。


* 返回值说明:uchar 返回按键值字符数组对应按键的序号，可以通过这个序号获得字符的
ASCII码值。
* 功能介绍:   
编辑界面字符键值序号获取函数，本函数作用是根据触发的按键值计算出按键对应
的键值字符数组序号，方便查找到数字键挂载的字符ASCII码值。

*
* 关键备注：
* - 

* 未来提高:

*/ 

uchar EditPageKeyCharIndexGet(KeyValueDef KeyValue)
{
  switch(KeyValue)
  {
    case MINUS:
      return 0;
      break;
    case POINT:
      return 1;
      break;
    case ZERO:
      return 2;
      break;
    case THREE:
      return 3;
      break;
    case TWO:
      return 4;
      break;
    case ONE:
      return 5;
      break;
    case SIX:
      return 6;
      break;
    case FIVE:
      return 7;
      break;
    case FOUR:
      return 8;
      break;
    case NINE:
      return 9;
      break;
    case EIGHT:
      return 10;
      break;
    case SEVEN:
      return 11;
      break;
  default:break;
  }
  //返回错误码
  return 0xff;
}
/*
//函数名称和参量和返回值类型。
uchar EditPageCharValueGet(KeyValueDef CharPositionSelectFlag,KeyValueDef KeyValue)
* 变量范围:
CharPositionSelectFlag:字符位置选择标志，用来选择数字按键上挂载的字符。
KeyValue:被按下的数字按键，可以通过该变量确定是哪一个数字按键被触发，范围是0-9键值以及负号，和小数点。

* 返回值说明:uchar 获取挂载在编辑页面的字符值。 
* 功能介绍:   
编辑页面字符值获取函数，判断当前页面输入到变量中的值是字符型值得时候，通过本
函数获取确定的字符值。

*
* 关键备注：
* - 

  
* 未来提高:

*/ 

uchar EditPageCharValueGet(KeyValueDef CharPositionSelectFlag,KeyValueDef KeyValue)
{
  uchar KeyCharIndex = 0;
  
  KeyCharIndex = EditPageKeyCharIndexGet(KeyValue);
  
  switch(CharPositionSelectFlag)
  {
    case UP_SELECT:
      return KeyCharArr[KeyCharIndex].UpValue;
      break;
    case RIGHT_UP_SELECT:
      return KeyCharArr[KeyCharIndex].RightValue;
      break;
    case LEFT_UP_SELECT:
      return KeyCharArr[KeyCharIndex].LeftValue;
      break;
    case NO_KEY_STATUS:
      return KeyCharArr[KeyCharIndex].NumberValue;
    default :
      break;
  }
  //返回错误码
  return 0xff;
}
/*
//函数名称和参量和返回值类型。
uchar EditPageVariableValueGet(AdditionalInfoDef AdditionFlog,KeyValueDef CharPositionSelectFlag,KeyValueDef KeyValue)
* 变量范围:
AdditionFlog:页面的附加信息，对一些特殊界面进行说明。
CharPositionSelectFlag:字符位置选择标志，用来选择数字按键上挂载的字符。
KeyValue:被按下的数字按键，可以通过该变量确定是哪一个数字按键被触发，范围是0-9键值以及负号，和小数点。

* 返回值说明:uchar，返回的是需要赋给编辑界面绑定变量的数据值。
* 功能介绍:   
编辑页面挂载变量值获取函数，本函数的功能是根据页面附加信息，字符位置变量，以及
触发的按键，计算出要保存在页面挂载变量对应位置行的数据值。

*
* 关键备注：
* - 

  
* 未来提高:
添加特殊数据格式的设计。
*/ 

uchar EditPageVariableValueGet(AdditionalInfoDef AdditionFlog,KeyValueDef CharPositionSelectFlag,KeyValueDef KeyValue)
{
  return EditPageCharValueGet(CharPositionSelectFlag,KeyValue);
}

/*
//函数名称和参量和返回值类型。
void EditPageHandle(KeyValueDef KeyMode);
* 变量范围:
KeyValueDef KeyMode:按键种类，区分是哪一个按键。
typedef enum
{
  OK,DOWN,UP,BACK,
  ONE,TWO,THREE,FOUR,
  FIVE,SIX,SEVEN,EIGHT,
  NIGHT,ZERO,KEY_IDLE
}KeyValueDef;


* 返回值说明:void 
* 功能介绍:   
  说明页面处理函数，当前显示页面为说明页面时，触发按键或特殊操作时
  通过本函数确定下一个显示页面，或执行什么样的操作，

*
* 关键备注：
* - 
有些说明界面会执行一些特殊操作，所以功能键会绑定一些功能函数指针，
执行什么操作调用什么函数。
  
* 未来提高:
按键齐全后，要进行按键整改
*/ 

void CharPositionSeletFlagReset(KeyValueDef *CharPositionSelectFlag)
{
  *CharPositionSelectFlag = NO_KEY_STATUS;
}
/*
//函数名称和参量和返回值类型。
void EditPageDataInput(uchar G_VariableArrIndex,AdditionalInfoDef AdditionFlog,
                       KeyValueDef CharPositionSelectFlag,KeyValueDef ONE,DataLengthDef ShowDataLength)
* 变量范围:
  uchar VariableArrIndex:显示变量数组的序号。
  AdditionalInfoDef AdditionFlog:页面的附加信息，对一些特殊界面进行说明。
  KeyValueDef CharPositionSelectFlag:字符位置选择标志，用来选择数字按键上挂载的字符。
  KeyValueDef ONE:被按下的数字按键，可以通过该变量确定是哪一个数字按键被触发，范围是0-9键值以及负号，和小数点。
  DataLengthDef ShowDataLength:显示字符串的长度


* 返回值说明:void 
* 功能介绍:
将按键输入的字符保存到编辑页面显示临时变量数组当中。

*
* 关键备注：
* - 

  
* 未来提高:

*/ 
void EditPageDataInput(uchar VariableArrIndex,AdditionalInfoDef AdditionFlog,
                       KeyValueDef CharPositionSelectFlag,KeyValueDef KeyValue,DataLengthDef ShowDataLength)
{
  if((AdditionFlog == SPECIAL_NUMBER_SHOW)
     &&((KeyValue == POINT)||(KeyValue == MINUS)))
  {
    
  }
  else
  {
     G_ShowData[VariableArrIndex] = EditPageVariableValueGet(AdditionFlog,CharPositionSelectFlag,KeyValue);
     G_VariableArrIndex++;
  }
}
/*
//函数名称和参量和返回值类型。
uchar GetPoint(uchar *ShowData,uchar Length)
* 变量范围:
uchar *ShowData显示数据数组指针。
uchar Length：显示数据数组长度。

* 返回值说明:uchar，小数点所在的位置。 
* 功能介绍:   
在显示数据数组中找到小数点的位置，并通过返回值将这个位置返回。

*
* 关键备注：
* - 

  
* 未来提高:

*/ 
uchar GetPoint(uchar *ShowData,uchar Length)
{
  uchar i;
  for(i = 0;i < Length;i++)
  {
    if(ShowData[i] == 0x2e)
      break;
  }
  return i;
}
/*
//函数名称和参量和返回值类型。
void EditPageVariableLoad(uchar *ShowData,DataLengthDef ShowDataLength,
DataTypeDef DataType,DataLengthDef ReceiveDataLength)

* 变量范围:
uchar *ShowData显示数据数组指针。
uchar Length：显示数据数组长度。

* 返回值说明:
* 功能介绍:   
编辑页面挂载变量加载函数，
将编辑页面中的临时缓冲显示数组信息通过数据类型转换，保存到页面挂载变量中。

*
* 关键备注：
* - 

  
* 未来提高:

*/ 
void EditPageVariableLoad(uchar *ShowData,DataLengthDef ShowDataLength,
                          DataTypeDef DataType,DataLengthDef ReceiveDataLength)
{
  uchar i;
  float FloatData = 0.0;
  long uint LongIntData = 0;
  uint IntData = 0;
  
  if(G_VariableArrIndex > ShowDataLength)
  {
    //error
  }
  else if(G_VariableArrIndex != 0)
  {
    if((DataType == FLOAT_T)||(DataType == FLOAT1_T))
    {      
      FloatData = MENU_StrToFloat(GetPoint(G_ShowData,G_VariableArrIndex),G_ShowData,G_VariableArrIndex);
      HART_FloatToData(FloatData,ShowData,FLOAT_T);
    }
    else if(DataType == LONG_UINT_T)
    {
      LongIntData = MENU_StrToInt(G_ShowData,G_VariableArrIndex);
      if(ReceiveDataLength == THREE_BYTES)
      {
        if(LongIntData <= 16777215)
        {
          HART_LongIntToData(LongIntData,ShowData,DataType );
        }
        else
        {
          //
        }
      }
    }
    else if(DataType == L_ASCII_1_T)
    {//特殊ASCII显示，如果遇见空格，需要将空格修改为00码，只在个别产品中这样使用。
      for(i = 0; i < ShowDataLength;i++)
      {
        if(G_ShowData[i] != 0x20)
        {
          *(ShowData+i) = G_ShowData[i];
        }
        else
          *(ShowData+i) = 0;
      }
    }
    else if(DataType == L_ASCII_T)
    {//通用8位ASCII码处理。
      for(i = 0; i < ShowDataLength;i++)
      {
        *(ShowData+i) = G_ShowData[i];
      }
    }
    else if((DataType == UCHAR_T)||(DataType == FUNC_CODE_T))
    {
      *ShowData = MENU_StrToInt(G_ShowData,G_VariableArrIndex);
    }
    else if(DataType == UINT_T)
    {      
      IntData = MENU_StrToInt(G_ShowData,G_VariableArrIndex);
      HART_IntToData(IntData,ShowData,DataType);
    }
    else//test,暂时使用
    {
      for(i = 0; i < ShowDataLength;i++)
      {
        *(ShowData+i) = G_ShowData[i];
      }
    }
  }
}

/*
//函数名称和参量和返回值类型。
void EditPageHandle(KeyValueDef KeyMode)

* 变量范围:
KeyValueDef KeyMode：按键名称，用于区分当前触发的按键。
* 返回值说明:
* 功能介绍:   
编辑页面处理函数，
根据编辑页面中触发的按键，实现功能，比如输入显示，页面切换等。

*
* 关键备注：
* - 

  
* 未来提高:

*/ 
void EditPageHandle(KeyValueDef KeyMode)
{
  const ItemDef* CurrentItemH;
  uchar *ShowData;
  DataLengthDef ShowDataLength = UCHAR,ReceiveDataLength = UCHAR;
  DataTypeDef DataType;
  uint VariableIndex;
  AdditionalInfoDef AdditionFlog = ADDITION_STANDBY;
  PageDef *PagePtr = NULL;
  
  static KeyValueDef CharPositionSelectFlag = NO_KEY_STATUS;
  
  
  PagePtr = MENU_GetCurrentMenuPage();
  
  CurrentItemH = MENU_GetHorizontalItem(PagePtr,G_CursorNumH);
  
  AdditionFlog = PagePtr->AdditionalInfo;

  //编辑页面挂载的HART变量一般只有一个，所以是数组0元素
  VariableIndex = MENU_VariableIndexInfoGet(0,G_VariableGroupTable);
  //获取HART变量数组指针
  ShowData = MENU_GetHartVariablePtrIndex(VariableIndex);
  ShowDataLength = MENU_GetHartVariableDataLength(VariableIndex);
  ReceiveDataLength = MENU_GetHartVariableAnalysisLength(VariableIndex);  
  DataType = MENU_GetHartVariableDataType(VariableIndex);
  if(MENU_CurrentPageTypeGet() == EDIT_PAGE)
  {
    //防止输入变量数组访问越界
       switch(KeyMode)
       {
          case LEFT:
              if(G_CursorNumH >= PagePtr->ItemNumberH-1)
              {
                G_CursorNumH = 0;
              }
              else
              {
                G_CursorNumH++;
              }            
            break;
          case RIGHT:
              if(G_CursorNumH == 0)
              {
                G_CursorNumH = PagePtr->ItemNumberH-1;
              }
              else
              {
                G_CursorNumH--;
              }       
            break;
            
          case OK:
            if(G_CursorNumH == HORIZONTAL_RIGHT_FIRST_ITEM)
            {
               //数据有效性检验
               DataType = EditVariableRangeConfirm(ShowData,DataType,PagePtr);
              //如果不是特殊范围变量
              if(G_VariableArrIndex != 0)
              {
                //Tag
                if(DataType == ASCII_T)
                {
                  HART_ASCII_Code(G_ShowData,ReceiveDataLength,ShowDataLength,ShowData);
                }
                //Data
                else if(PagePtr->ContentStrIndex == STR_INDEX_35)
                {
                  HART_DateHandle(G_ShowData);
                }
                else
                {
                   //临时缓冲数组加载到页面挂载变量
                   EditPageVariableLoad(ShowData,ShowDataLength,DataType,ReceiveDataLength);
                }
                //临时缓冲数组清空
                MENU_TemporaryVariableReset(G_ShowData,ASCII_42,0);
                MENU_GeneralItemLinkHandle(CurrentItemH);
              }
              else      
              {  
                //字符型和半字型变量值超限需要进行非法值提示
                if((DataType == INT_VALUE_T)||(DataType == BYTE_VALUE_T))
                {
                  //川仪TTS显示码设定补丁，提示输入值超限，系统均可使用该提示页面
                  MENU_PageIndexSetHandle(GENERAL_MENU_TREE);
                  MENU_PageTypeSetHandle(WARNING_PAGE);
                  MENU_PageNumSetHandle(GENERAL_PAGE_INDEX_113);
                }
                else
                {
                  //页面链接切换
                  MENU_PageLinkHandle(PagePtr);
                }
                //个别变量需要恢复为0值
                G_ParamLoadLock = MENU_ParamReset();
              }
              
              MENU_IS_SingleCommandLoad(FALSE,PagePtr);
              G_VariableArrIndex = 0;
              G_VariableProtect.LoadLock = FALSE;
              FlashReadLockHandle(FALSE);
              G_EditPageInputSpecialShowFlag = TRUE;
            }
            if(G_CursorNumH == HORIZONTAL_RIGHT_SECOND_ITEM)
            {
              //临时缓冲数组清空
              MENU_TemporaryVariableReset(G_ShowData,ASCII_42,0);
              G_VariableArrIndex = 0; 
              //页面链接切换
              MENU_PageLinkHandle(PagePtr);  
              MENU_IS_SingleCommandLoad(FALSE,PagePtr);
              G_VariableProtect.LoadLock = FALSE;
              FlashReadLockHandle(FALSE);
              G_EditPageInputSpecialShowFlag = TRUE;
              if(PagePtr->ContentStrIndex == STR_INDEX_105)
              {
                MENU_ItemParamLoad(CurrentItemH);
              }
            }
            if(G_CursorNumH == HORIZONTAL_RIGHT_THIRD_ITEM)
            {  
              if(G_VariableArrIndex != 0)
              {                
                G_VariableArrIndex--;
              }
              //退格
              G_ShowData[G_VariableArrIndex] = 0x20;
            }
            if(G_CursorNumH == HORIZONTAL_RIGHT_FOURTH_ITEM)
            {
              //临时缓冲数组清空
              MENU_TemporaryVariableReset(G_ShowData,ASCII_42,0);
              G_VariableArrIndex = 0;
            }
            break;
          case UP_SELECT:
            CharPositionSelectFlag = EditPageCharPositionSelect(AdditionFlog,UP_SELECT);        
            break;
          case LEFT_UP_SELECT:
            CharPositionSelectFlag = EditPageCharPositionSelect(AdditionFlog,LEFT_UP_SELECT);
            break;
          case RIGHT_UP_SELECT:
            CharPositionSelectFlag = EditPageCharPositionSelect(AdditionFlog,RIGHT_UP_SELECT);
            break;
          case ONE:
           if(G_VariableArrIndex < ShowDataLength)
           {
              EditPageDataInput(G_VariableArrIndex,AdditionFlog,CharPositionSelectFlag,ONE,ShowDataLength);
           }
           CharPositionSeletFlagReset(&CharPositionSelectFlag);         
           break;
          case TWO:          
           if(G_VariableArrIndex < ShowDataLength)
           {
              EditPageDataInput(G_VariableArrIndex,AdditionFlog,CharPositionSelectFlag,TWO,ShowDataLength);
           }
           CharPositionSeletFlagReset(&CharPositionSelectFlag); 
           break;
          case THREE:
           if(G_VariableArrIndex < ShowDataLength)
           {
              EditPageDataInput(G_VariableArrIndex,AdditionFlog,CharPositionSelectFlag,THREE,ShowDataLength);
           }
           CharPositionSeletFlagReset(&CharPositionSelectFlag);          
           break;
          case FOUR:          
           if(G_VariableArrIndex < ShowDataLength)
           {
              EditPageDataInput(G_VariableArrIndex,AdditionFlog,CharPositionSelectFlag,FOUR,ShowDataLength);
           }
           CharPositionSeletFlagReset(&CharPositionSelectFlag);         
           break;
          case FIVE:           
           if(G_VariableArrIndex < ShowDataLength)
           {
              EditPageDataInput(G_VariableArrIndex,AdditionFlog,CharPositionSelectFlag,FIVE,ShowDataLength);
           }
           CharPositionSeletFlagReset(&CharPositionSelectFlag);         
           break;
          case SIX:           
           if(G_VariableArrIndex < ShowDataLength)
           {
              EditPageDataInput(G_VariableArrIndex,AdditionFlog,CharPositionSelectFlag,SIX,ShowDataLength);
           }
           CharPositionSeletFlagReset(&CharPositionSelectFlag);        
           break;
          case SEVEN:           
           if(G_VariableArrIndex < ShowDataLength)
           {
              EditPageDataInput(G_VariableArrIndex,AdditionFlog,CharPositionSelectFlag,SEVEN,ShowDataLength);
           }
           CharPositionSeletFlagReset(&CharPositionSelectFlag);         
           break;
          case EIGHT:           
           if(G_VariableArrIndex < ShowDataLength)
           {
              EditPageDataInput(G_VariableArrIndex,AdditionFlog,CharPositionSelectFlag,EIGHT,ShowDataLength);
           }
           CharPositionSeletFlagReset(&CharPositionSelectFlag);          
           break;
          case NINE:           
           if(G_VariableArrIndex < ShowDataLength)
           {
              EditPageDataInput(G_VariableArrIndex,AdditionFlog,CharPositionSelectFlag,NINE,ShowDataLength);
           }
           CharPositionSeletFlagReset(&CharPositionSelectFlag);         
           break;
          case ZERO:           
           if(G_VariableArrIndex < ShowDataLength)
           {
              EditPageDataInput(G_VariableArrIndex,AdditionFlog,CharPositionSelectFlag,ZERO,ShowDataLength);
           }
           CharPositionSeletFlagReset(&CharPositionSelectFlag);        
           break;
          case POINT:          
           if(G_VariableArrIndex < ShowDataLength)
           {
              EditPageDataInput(G_VariableArrIndex,AdditionFlog,CharPositionSelectFlag,POINT,ShowDataLength);
           }
           CharPositionSeletFlagReset(&CharPositionSelectFlag);         
           break;
          case MINUS:           
           if(G_VariableArrIndex < ShowDataLength)
           {
              EditPageDataInput(G_VariableArrIndex,AdditionFlog,CharPositionSelectFlag,MINUS,ShowDataLength);
           }
           CharPositionSeletFlagReset(&CharPositionSelectFlag);        
           break;
         default: break;
   
     }
  }
  else
  {
    //Page error
  }
}

/*
//函数名称和参量和返回值类型。
void EditPageShow()
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
编辑页面显示函数，根据编辑页面的格式以及需要兼容的
页面格式显示将编辑页面显示出来。

*
* 关键备注：
* - 

  
* 未来提高:
需要移至显示文件中。


*/ 
void EditPageShow()
{
  uchar ShowLineIndex = 0,VariableNumber = 0;
  
  DataLengthDef DataLength = UCHAR,ReceiveDataLength = UCHAR;
  DataTypeDef DataType = UCHAR_T;
  uint VariableIndex = {0};
  uchar *ShowData = NULL,UnitStartPosition = 0;
  PageDef *PagePtr = NULL;
  LanguageTypeDef Language = MENU_LanguageTypeGet();
  PagePtr = MENU_GetCurrentMenuPage();
  //加载当前页面的变量表信息以及变量组信息，变量用来显示或发送绑定的HART命令。
  FlashVariableGroupLoad(PagePtr->VariableIndex,&G_PageVariableTable,&G_VariableGroupTable);
  ShowData = MENU_VariableInfoGet(&VariableIndex,&DataType,&DataLength,&ReceiveDataLength);
  if(ShowData == NULL)
  {
    HART_AbnormalPageHandle(COMMUNICATION_ERR); 
    return ;
  }
  //警告界面返回环境保护函数
  MENU_ReturnPageSave(PagePtr);
  //页面停止刷新
  MENU_PageShowSwitch(FALSE);
  MENU_IS_SingleCommandLoad(TRUE,PagePtr);
  ShowLineIndex = MENU_ExplainInfoDisplayHandle(Language,ShowLineIndex,PagePtr);
  //Date显示
  /* 川仪的表是MM-DD-YY */
  if(PagePtr->ContentStrIndex == STR_INDEX_35)
  { 
    ShowLineIndex = EditDateDisplay(DataLength,ShowLineIndex);
    if(ShowLineIndex == SOFTWARE_ERR)
    {
      //后续新增，软件崩溃
      HART_AbnormalPageHandle(COMMUNICATION_ERR); 
      return ;
    }
  }
  else
  {
    if(DataType == ASCII_T)
    {
      //如果是Tag编辑界面，需要进行ASCII解码
      ShowLineIndex = EditTagDisplay(ReceiveDataLength,DataLength,ShowData,ShowLineIndex);
    }
    else if(IS_SPECIAL_DATA_TYPE_HANDLE)
    {
      ShowLineIndex = EditSpecialDataTypeHandle(DataType,ShowLineIndex,ShowData,ReceiveDataLength,&UnitStartPosition);
    }
    else if((DataType == LONG_UINT_T)||(DataType == HANDRED_T)||(DataType == BYTE_VALUE_T))
    {
      ShowLineIndex = EditLongIntDataHandle(ShowData,DataType,ReceiveDataLength,DataLength,ShowLineIndex,&UnitStartPosition);
    }
    else if((DataType == L_ASCII_T)||(DataType == L_ASCII_1_T))
    {
      ShowLineIndex = MENU_VariableShow(DataLength,ShowData,ShowLineIndex,PagePtr,0,NORMAL);
      UnitStartPosition = DataLength;
    }
    else if((DataType == UCHAR_T)||(DataType == UINT_T)||(DataType == INT_VALUE_T))
    {
      ShowLineIndex = EditIntDataHandle(ShowData,DataType,DataLength,ShowLineIndex,&UnitStartPosition);
    }
    else if(DataType == FUNC_CODE_T)
    {
      if(PagePtr->ContentStrIndex == STR_INDEX_337)
      {
        Language = ENGLISH;
      }
      EditFunctionCodeHandle(VariableIndex,DataType,ShowData,Language,ShowLineIndex);
    }
  }
  EditUnitDisplay(VariableNumber,ShowLineIndex,PagePtr,UnitStartPosition);
  PagePtr = MENU_GetCurrentMenuPageTemporary();
  ShowLineIndex = MENU_VariableShow(DataLength,G_ShowData,4,PagePtr,0,NORMAL);
  MENU_HorizontalItemShow(PagePtr,4,MENU_LanguageTypeGet());
  FlashReadLockHandle(TRUE);
}
/*
//函数名称和参量和返回值类型。
DataTypeDef EditVariableRangeConfirm(uchar *ShowData,DataTypeDef DataType);
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
编辑界面变量范围确认函数，
主要针对特殊变量，根据变量规定的范围，进行数值有效性确认。

*
* 关键备注：
* - 

  
* 未来提高:
需要移至显示文件中。


*/ 
DataTypeDef EditVariableRangeConfirm(uchar *ShowData,
                              DataTypeDef DataType,const PageDef *CurrentPage)
{
  float FloatData;
  uchar UcharData;
  uint32 UintData;
  
  //如果是特殊范围变量
  if(IS_SPECIAL_RANGE)
  {
    switch(DataType)
    {
      case CURVE_START_T:
        FloatData = MENU_StrToFloat(GetPoint(G_ShowData,G_VariableArrIndex),G_ShowData,G_VariableArrIndex);
        if((FloatData < 0)||(FloatData > 72))
        {
          EditInvalidInputReset();
        }
        else
        {
          DataType = FLOAT_T;
        }
        break;
      case SUPRITY_T:
        FloatData = MENU_StrToFloat(GetPoint(G_ShowData,G_VariableArrIndex),G_ShowData,G_VariableArrIndex);
        if((FloatData < -3)||(FloatData > 3))
        {
          EditInvalidInputReset();
        }
        else
        {
          DataType = FLOAT_T;
        }
        break;
      case MIN_RESOL_T:
        FloatData = MENU_StrToFloat(GetPoint(G_ShowData,G_VariableArrIndex),G_ShowData,G_VariableArrIndex);
        if((FloatData < 0)||(FloatData > 2))
        {
          EditInvalidInputReset();
        }
        else
        {
          DataType = FLOAT_T;
        }
        break;
      case MAX_ZOON_T:
        FloatData = MENU_StrToFloat(GetPoint(G_ShowData,G_VariableArrIndex),G_ShowData,G_VariableArrIndex);
        if((FloatData < 0.5)||(FloatData > 70))
        {
          EditInvalidInputReset();
        }
        else
        {
          DataType = FLOAT_T;
        }
        break;
      case MIN_ZOON_T:
        FloatData = MENU_StrToFloat(GetPoint(G_ShowData,G_VariableArrIndex),G_ShowData,G_VariableArrIndex);
        if((FloatData < 0)||(FloatData > 69.5))
        {
          EditInvalidInputReset();
        }
        else
        {
          DataType = FLOAT_T;
        }
        break;
      case LEVEL_SPD_T:
        FloatData = MENU_StrToFloat(GetPoint(G_ShowData,G_VariableArrIndex),G_ShowData,G_VariableArrIndex);
        if((FloatData < 0.1)||(FloatData > 70))
        {
          EditInvalidInputReset();
        }
        else
        {
          DataType = FLOAT_T;
        }
        break;
      case CURVE_END_T:
        FloatData = MENU_StrToFloat(GetPoint(G_ShowData,G_VariableArrIndex),G_ShowData,G_VariableArrIndex);
        if((FloatData < 0.1)||(FloatData > 72))
        {
          EditInvalidInputReset();
        }
        else
        {
          DataType = FLOAT_T;
        }
        break;
      case FAKE_RANGE_T:
        FloatData = MENU_StrToFloat(GetPoint(G_ShowData,G_VariableArrIndex),G_ShowData,G_VariableArrIndex);
        if((FloatData < 0)||(FloatData > 70))
        {
          EditInvalidInputReset();
        }
        else
        {
          DataType = FLOAT_T;
        }
        break;
      case FAKE_AMP_T:
        FloatData = MENU_StrToFloat(GetPoint(G_ShowData,G_VariableArrIndex),G_ShowData,G_VariableArrIndex);
        if((FloatData < 0)||(FloatData > 3.3))
        {
          EditInvalidInputReset();
        }
        else
        {
          DataType = FLOAT_T;
        }
        break;
      case PVL_T:
        FloatData = MENU_StrToFloat(GetPoint(G_ShowData,G_VariableArrIndex),G_ShowData,G_VariableArrIndex);
        if((FloatData < 0.3)||(FloatData > 70))
        {
          EditInvalidInputReset();
        }
        else
        {
          DataType = FLOAT_T;
        }
        break;
      case PVU_T:
        FloatData = MENU_StrToFloat(GetPoint(G_ShowData,G_VariableArrIndex),G_ShowData,G_VariableArrIndex);
        if((FloatData < 0)||(FloatData > 69.7))
        {
          EditInvalidInputReset();
        }
        else
        {
          DataType = FLOAT_T;
        }
        break;
      case HANDRED_T:
        //先将显示字符串转换成长整型数据
        UcharData = MENU_StrToInt(G_ShowData,G_VariableArrIndex);
        if(UcharData >= 100)
        {
          EditInvalidInputReset();
        }
        else
        {
          DataType = UCHAR_T;
        }
        break;
      case BYTE_VALUE_T:
        //先将显示字符串转换成长整型数据
        UintData = MENU_StrToInt(G_ShowData,G_VariableArrIndex);
        if(UintData > 255)
        {
          EditInvalidInputReset();
        }
        else
        {
          DataType = UCHAR_T;
        }
        break;
      case INT_VALUE_T:
        //先将显示字符串转换成长整型数据
        UintData = MENU_StrToInt(G_ShowData,G_VariableArrIndex);
        if(UintData > 65535)
        {
          EditInvalidInputReset();
        }
        else
        {
          DataType = UINT_T;
        }
        break;
      default:
        
        break;
    }
  }
  return DataType;
}
/*
//函数名称和参量和返回值类型。
void EditInvalidInputReset(void)
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
非法输入显示数组复原函数

*
* 关键备注：
* - 

  
* 未来提高:
需要移至显示文件中。


*/ 
void EditInvalidInputReset(void)
{
  G_VariableArrIndex = 0;
  //临时缓冲数组清空
  MENU_TemporaryVariableReset(G_ShowData,ASCII_42,0);
}
/*
//函数名称和参量和返回值类型。
static void EditDateDisplay(DataLengthDef DataLength,uchar *ShowLinePtr);
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
编辑日期显示函数。

*
* 关键备注：
* - 

  
* 未来提高:


*/ 
static uchar EditDateDisplay(DataLengthDef DataLength,uchar ShowLineIndex)
{
  uchar DateStrTemp[ASCII_10] = {0};
  StringDef StrStruct[1] = {0};
  uchar StringCodeBuff[1][COMMON_STRING_SIZE];
  PageDef * PagePtr = NULL;
  PagePtr = MENU_GetCurrentMenuPageTemporary();
  MENU_DateShowHandle(DateStrTemp);
  ShowLineIndex = MENU_VariableShow(DataLength,DateStrTemp,ShowLineIndex,PagePtr,0,NORMAL);
  //DD-MM-YY
  StrStruct[0] = MENU_GetStrStruct(STR_INDEX_320);
  FlashStringCodeGet(StrStruct,StringCodeBuff[0],ENGLISH);
  MENU_StaticStringShow(StrStruct,START_X_INDEX,
             START_Y_INDEX+5,ENGLISH,NORMAL,StringCodeBuff[0]);  
  return ShowLineIndex;
}
/*
//函数名称和参量和返回值类型。
static uchar EditTagDisplay(DataLengthDef ReceiveDataLength,DataLengthDef DataLength,
                            uchar *ShowData,uchar ShowLineIndex,const PageDef *const PagePtr);
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
编辑Tag显示函数,解码，数据转换，显示。

*
* 关键备注：
* - 

  
* 未来提高:


*/ 
static uchar EditTagDisplay(DataLengthDef ReceiveDataLength,DataLengthDef DataLength,uchar *ShowData,uchar ShowLineIndex)
{
  uchar j = 0;
  PageDef * PagePtr = NULL;
  PagePtr = MENU_GetCurrentMenuPageTemporary();

  //第20个字节原来为0x00
  uchar Tagline[]  = 
  {
    0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,
    0x20,0x20,0x20,0x20,0x20,0x20,
    0x00,
  };
  j = HART_ASCII_Decode(Tagline,ReceiveDataLength,DataLength,ShowData);
  if(j != 0)
  {
     ShowLineIndex = MENU_VariableShow(DataLength,Tagline,ShowLineIndex,PagePtr,0,NORMAL);
  }
  return ShowLineIndex;
}
/*
//函数名称和参量和返回值类型。
static uchar EditSpecialDataTypeHandle(DataTypeDef DataType,uchar ShowLineIndex,
        uchar *ShowData,DataLengthDef ReceiveDataLength,const PageDef *const PagePtr);
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
编辑界面特殊数据类型处理函数。

*
* 关键备注：
* - 

  
* 未来提高:


*/ 
static uchar EditSpecialDataTypeHandle(DataTypeDef DataType,
  uchar ShowLineIndex,uchar *ShowData,DataLengthDef ReceiveDataLength,uchar *UnitStartPosition)
{
  uchar FloatStrTemp[ASCII_42] = {0};
  uchar Length = 0,j = 0;
  StringDef StrStruct[1] = {0};
  uchar StringCodeBuff[1][COMMON_STRING_SIZE];
  PageDef * PagePtr = NULL;
  PagePtr = MENU_GetCurrentMenuPageTemporary();
  if(IS_FIXED_CURRENT_HANDLE)
  {
    ShowData = G_PV_Current;
  }
  Length = MENU_DataToASCII(ShowData,FloatStrTemp,DataType);
  if(Length < ASCII_42)
  {
    MENU_TemporaryVariableReset(FloatStrTemp,ASCII_42,Length);
    ShowLineIndex = MENU_VariableShow(ReceiveDataLength,FloatStrTemp,ShowLineIndex,PagePtr,0,NORMAL);
    if(IS_EDIT_PAGE_INPUT_SPECIAL_DISPLAY)
    {  
      for(j = 0;j < Length;j++)
      {
        G_ShowData[j] = FloatStrTemp[j];
      }
      //确定特殊编辑界面输入变量字符串长度,变量序号需要用字节个数-1
      G_VariableArrIndex = Length-1;
      G_EditPageInputSpecialShowFlag = FALSE;
    }
    else if(IS_CY_PDS6_PATCH_1)
    {
      //川仪PDS补丁
      StrStruct[0] = MENU_GetStrStruct(STR_INDEX_275);
      FlashStringCodeGet(StrStruct,StringCodeBuff[1],ENGLISH);
      MENU_StaticStringShow(StrStruct,START_X_INDEX+Length*6,
          START_Y_INDEX+(ShowLineIndex-1)*(ITEM_HIGHT),ENGLISH,NORMAL,StringCodeBuff[1]);        
    }
  }
  *UnitStartPosition = Length;
  ShowLineIndex++;
  return ShowLineIndex;
}
/*
//函数名称和参量和返回值类型。
static uchar EditLongIntDataHandle(uchar *ShowData,DataTypeDef DataType,
                DataLengthDef ReceiveDataLength,DataLengthDef DataLength,
                  uchar ShowLineIndex,uchar *UnitStartPosition);
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
编辑界面长整数据类型处理函数。

*
* 关键备注：
* - 

  
* 未来提高:


*/ 
static uchar EditLongIntDataHandle(uchar *ShowData,DataTypeDef DataType,
                DataLengthDef ReceiveDataLength,DataLengthDef DataLength,
                  uchar ShowLineIndex,uchar *UnitStartPosition)
{
  uchar Temp[ASCII_8] = {0};
  PageDef * PagePtr = NULL;
  PagePtr = MENU_GetCurrentMenuPageTemporary();
  *UnitStartPosition = HART_TypeConvert(ShowData,Temp,DataType,ReceiveDataLength,ASCII_T);
  ShowLineIndex = MENU_VariableShow(DataLength,Temp,ShowLineIndex,PagePtr,0,NORMAL);
  return ShowLineIndex;
}
/*
//函数名称和参量和返回值类型。
static uchar EditIntDataHandle(uchar *ShowData,DataType,DataTypeDef DataLength,
       uchar ShowLineIndex,const PageDef *const PagePtr);
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
编辑界面整数据类型处理函数。

*
* 关键备注：
* - 

  
* 未来提高:


*/ 
static uchar EditIntDataHandle(uchar *ShowData,DataTypeDef DataType,
    DataLengthDef DataLength,uchar ShowLineIndex,uchar *UnitStartPosition)
{
  uchar Temp[ASCII_8] = {0};
  PageDef * PagePtr = NULL;
  PagePtr = MENU_GetCurrentMenuPageTemporary();
  *UnitStartPosition = HART_TypeConvert(ShowData,Temp,DataType,DataLength,ASCII_T);
  ShowLineIndex = MENU_VariableShow(DataLength,Temp,ShowLineIndex,PagePtr,0,NORMAL);
  return ShowLineIndex;
}
/*
//函数名称和参量和返回值类型。
static void EditFunctionCodeHandle(uint VariableIndex,
            DataTypeDef DataType,uchar *ShowData,LanguageTypeDef Language,uchar ShowLineIndex);
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
编辑界面功能码显示处理函数。

*
* 关键备注：
* - 

  
* 未来提高:


*/ 
static void EditFunctionCodeHandle(uint VariableIndex,DataTypeDef DataType,uchar *ShowData,LanguageTypeDef Language,uchar ShowLineIndex)
{
  StringDef StrStruct[1] = {0};
  uint StrNum = 0;
  const HART_UnitDef* UnitTable = NULL;
  uchar StringCodeBuff[1][COMMON_STRING_SIZE];

  //获取HART变量功能码对照表数组指针
  UnitTable = MENU_GetHartUnitTable(VariableIndex); 
  if(DataType == FUNC_CODE_T)
  {
    StrNum = HART_UnitShowHandle(UnitTable,ShowData);
    StrStruct[0] = MENU_GetStrStruct(StrNum);
    FlashStringCodeGet(StrStruct,StringCodeBuff[0],Language);
    MENU_StaticStringShow(StrStruct,START_X_INDEX,
            START_Y_INDEX+ShowLineIndex*(ITEM_HIGHT),Language,NORMAL,StringCodeBuff[0]); 
  }
}
/*
//函数名称和参量和返回值类型。
static void EditUnitDisplay(uint VariableIndex,uchar ShowLineIndex,const PageDef *const PagePtr); 
* 变量范围:


* 返回值说明:void 
* 功能介绍:   
编辑界面单位显示处理函数。

*
* 关键备注：
* - 

  
* 未来提高:


*/ 
static void EditUnitDisplay(uint VariableIndex,
          uchar ShowLineIndex,const PageDef *const PagePtr,uchar UnitStartPosition)
{
  uint StrNum = 0;
  const HART_UnitDef* UnitTable = NULL;
  StringDef StrStruct[1] = {0};
  uchar StringCodeBuff[1][COMMON_STRING_SIZE];
  uchar VariableNumber = 0,*ShowData = NULL;
  DataTypeDef DataType;
  //如果挂载两个变量，另一个变量多为单位变量，通过下列方法处理。
  VariableNumber = MENU_PageVariableNumber(G_PageVariableTable);
  if(VariableNumber == 0x02)
  {
    //编辑页面挂载的HART变量一般只有一个，所以是数组0元素
    VariableIndex = MENU_VariableIndexInfoGet(1,G_VariableGroupTable);
    DataType = MENU_GetHartVariableDataType(VariableIndex);
    //获取HART变量数组指针
    ShowData = MENU_GetHartVariablePtrIndex(VariableIndex);
    //获取HART变量功能码对照表数组指针
    UnitTable = MENU_GetHartUnitTable(VariableIndex); 
    if(DataType == FUNC_CODE_T)
    {

      StrNum = HART_UnitShowHandle(UnitTable,ShowData);
      StrStruct[0] = MENU_GetStrStruct(StrNum);
      FlashStringCodeGet(StrStruct,StringCodeBuff[0],ENGLISH);
      MENU_StaticStringShow(StrStruct,START_X_INDEX+UnitStartPosition*6,
              START_Y_INDEX+(ShowLineIndex-2)*(ITEM_HIGHT),ENGLISH,NORMAL,StringCodeBuff[0]); 
    }
  }
}

