/*************************************************************************/
// iec104.h                                        Version 1.00
//
// 本文件是DTU2.0通讯网关装置的IEC60870-5-104规约处理程序
// 编写人  :R&N
// email		  :R&N
//  日	   期:2015.04.17
//  注	   释:
/*************************************************************************/
#ifndef    _IEC104_H
#define    _IEC104_H


#define IEC104CONFFILE				"/config/guiyue104.conf"
#define IEC104LOGFFILE				"/config/log104.txt"
#define IEC104SOELOG                "/config/SOE104.txt"
#define IEC104SOEFILE               "/config/soefile.txt"



#define IEC104FRAMEERR         		    1
#define IEC104FRAMESEQERR      		    2
#define IECFRAMENEEDACK        		    3
#define IEC104FRAMEOK          		    0
#define IEC104FRAME_I          			0x10
#define IEC104FRAME_S          			0x11
#define IEC104FRAME_U         		 	0x13
#define IEC104BUFDOWNNUMBER		        4	//分配6个缓冲 6*256
#define IEC104BUFDOWNLENGTH		        256
#define IEC104BUFUPLENGTH			    4
#define IEC104YXINFONUMBER		        32	//分配4个缓冲
#define IEC104SOENUMBER		            32	//分配4个缓冲


#define FORMAT_I                		0
#define FORMAT_S                		1
#define FORMAT_U                		3

#define IEC104_M_SP_NA_1        		1
#define IEC104_M_ME_NA_1        		9	//测量值，归一化值
#define IEC104_M_ME_NC_1			    13  //测量值，短浮点数
#define IEC104_M_IT_NA_1        		15
#define IEC104_M_SP_TB_1        		30
#define IEC104_M_ME_TD_1        		34
#define IEC104_M_IT_TB_1        		37
#define IEC104_C_DC_NA_1        		46
#define IEC104_C_SC_NA_1        		45
#define IEC104_C_SC_TA_1        		58
#define IEC104_C_IC_NA_1        		100
#define IEC104_C_CI_NA_1        		101
#define IEC104_C_RD             		102
#define IEC104_C_CS_NA_1        		103
#define IEC104_C_RP_NA_1        		105
#define IEC104_DC_NA_1    			    0X2E
#define IEC104_CAUSE_N_BIT              0x40

#define IEC104_CAUSE_SPONT                3
#define IEC104_CAUSE_REQ                  5
#define IEC104_CAUSE_ACT                  6
#define IEC104_CAUSE_ACTCON               7
#define IEC104_CAUSE_DEACT                8
#define IEC104_CAUSE_DEACTCON             9
#define IEC104_CAUSE_ACTTERM              10
#define IEC104_CAUSE_INTROGEN             20
#define IEC104_CAUSE_UNKNOWNTYPE          44
#define IEC104_CAUSE_UNKNOWNCAUSE         45
#define IEC104_CAUSE_UNKNOWNCOMMADDR      46
#define IEC104_CAUSE_UNKNOWNINFOADDR      47

#define IEC104WAITIDLETIME      		  50

//define SIQ_BIT
#define IEC104_SIQ_IV_BIT    			0x80
#define IEC104_SIQ_NT_BIT    		    0x40
#define IEC104_SIQ_SB_BIT    			0x20
#define IEC104_SIQ_BL_BIT    			0x10
#define IEC104_SIQ_OV_BIT   			0x01

//define QOI
#define IEC104_QOI_INTROGEN  		    0x14
#define IEC104_QOI_INTRO1    		    0x15
#define IEC104_QOI_INTRO2    		    0x16
#define IEC104_QOI_INTRO3    		    0x17
#define IEC104_QOI_INTRO4    		    0x18
#define IEC104_QOI_INTRO5    		    0x19
#define IEC104_QOI_INTRO6    		    0x1A
#define IEC104_QOI_INTRO7    		    0x1B
#define IEC104_QOI_INTRO8    		    0x1C
#define IEC104_QOI_INTRO9    		    0x1D
#define IEC104_QOI_INTRO10   		    0x1E
#define IEC104_QOI_INTRO11   		    0x1F
#define IEC104_QOI_INTRO12   		    0x20
#define IEC104_QOI_INTRO13   		    0x21
#define IEC104_QOI_INTRO14   		    0x22
#define IEC104_QOI_INTRO15   		    0x23
#define IEC104_QOI_INTRO16   		    0x24

//define RTU_VSQ_BIT
#define IEC104_VSQ_SQ_BIT    		0x80   //检测是否是测试
#define IEC104_VSQ_PN_BIT    		0x40   //检测是否是连续

#define	IEC104_MAX_K			    12  //发送状态变量的最大不同的接收序号
#define	IEC104_MAX_W			    8    //接收w个I格式APDUs之后的最后的认可



#define TYPE_GUIYI                  9
#define TYPE_FLOAT                  11

/**************************系统需要的链表结构体******************************/
struct _BufStruct
{
	unsigned short usStatus;
	unsigned short usLength;
	unsigned char * buf;
	struct _BufStruct * next;
};
typedef struct _BufStruct BufStruct;

struct _IEC104Struct
{
	unsigned short  usRecvNum;  //已经接收到的帧
	unsigned short  usSendNum;  //已经发送出的帧
	unsigned short  usServRecvNum; //服务器接收到的帧
	unsigned short  usServSendNum; //服务器已发送的帧
	unsigned short  usAckNum;   //已经认可的帧

	unsigned char	 mode;			//mode=1#模式:不平衡(0),平衡(1)
	unsigned char  linkaddr;		//linkaddr=2#链路地址
	unsigned char  linkaddrlen;		//linkaddrlen=2#链路地址长度
	unsigned char  conaddrlen;		//conaddrlen=2#公共地址长度
	unsigned char  COTlen;			//COTlen=2#传送原因长度
	unsigned char  infoaddlen;		//infoaddlen=2#信息体地址长度
	unsigned char  yctype;			//yctype=9#遥测类型:规一值(9),标度值(11),无品质规一值(21)
	unsigned char  dir;				//dir=1#平衡模式DIR位(0或1,缺省0)

	unsigned char   ucSendCountOverturn_Flag;  //发送计数翻转标志

	unsigned char   ucTimeOut_t0;  //连接建立超时皱邋�,单位s 60
	unsigned char   ucTimeOut_t1;  //APDU的发送或测试的超时时间,s60
	unsigned char   ucTimeOut_t2;  //无数据报文t2<t1情况下认可的超时时间,s20
	unsigned char   ucTimeOut_t3;  //茌长时间Idle状态t3>t1情况下发送S-帧的超时时间,s40

	unsigned char   k;            		 //发送I格式应用规约数据单元的未认可帧数 最大差别接收序号来发送状态变量
	unsigned char   w;            		 //接收I格式应用规约数据单元的帧数 接受到w I格式的APDU后的最新确认


	unsigned char   ucDataSend_Flag;   //是否允许发送标志

//	unsigned char   ucIdleCount_Flag;//是否允许t2计数
//	unsigned char   ucIdleCount;        //t2计数
//
//	unsigned char   ucWaitServConCount_Flag;//是否t1计数
//	unsigned char   ucWaitServConCount; //t1计数
//
//	unsigned char   ucNoRecvCount; //t0计数
//
	unsigned char ucYK_Limit_Time;
	unsigned char ucYK_TimeCount_Flag;
	unsigned char ucYK_TimeCount;

	unsigned char * pSendBuf;
	unsigned char ucInterro_First;
	int			logfd;
    
    int         logsoEfd;
    int         soEfile;

};
typedef	struct _IEC104Struct IEC104Struct;
struct _IEC104_ASDU_Struct
{
	unsigned char ucType;
	unsigned char ucRep_Num;      //可变结构限定词
	unsigned char ucCauseL;        //传送原因
	unsigned char ucCauseH;        //传送原因
	unsigned char ucCommonAddrL;   //公共地址
	unsigned char ucCommonAddrH;   //公共地址
	unsigned char ucInfoUnit[243];//信息体单元,length=249-6
};
typedef struct _IEC104_ASDU_Struct IEC104_ASDU_Frame;



/**********************extern function**********************************/
extern IEC104Struct  	* pIEC104_Struct;

extern void Init_Iec104_Logfile( void );
extern void  *Network_Thread( void * data  );
extern void  *Iec104_Thread( void * data  );
extern int  IEC104_Free_Buf(void);
extern int  IEC104_Init_Buf(void);
extern void IEC104_Process_Message(UInt32 cmd, UInt32 data, UInt32 buf);
extern void IEC104_Senddata2pc(int fd, char *tmp_buf, UInt8 len);
extern void SOE104_Senddata2pc(int fd, char *tmp_buf, UInt8 len);

extern void PC_Send_YC(UInt8* buf,UInt8 len);
extern void PC_Send_YX(UInt8* buf,UInt8 len);
extern void Send_Soe_Data(int fd);
extern void Get_Soe_From_Line(char * line);
extern unsigned long file_wc(int file);  
extern void sig_handler(int signo);
extern void set_timer();
extern void uninit_time();

#endif

