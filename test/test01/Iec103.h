#ifndef IEC103_H
#define IEC103_H

#include  <sqlite3.h>
#include  <stdbool.h>
#define  CLIENT_NUM				5
#define  SQL_DB_TABLE_NAME_LEN  20  //数据库表名长度
#define  XML_TABLE_NAME_LEN		80  //xml表名长度

#define  MAX_COM_SIZE			10  //点号长度

enum  eMBParity
{
	MB_PAR_NONE=0,              /*!< No parity. */
	MB_PAR_ODD,                 /*!< Odd parity. */
	MB_PAR_EVEN                 /*!< Even parity. */
};
enum  eNETTYPE
{
	NET_SERIAL=0,           /* Ž®¿ÚÍšÐÅ */
	NET_TCP_MASTER,         /* TCPÍšÐÅÐ­Òé */
	NET_TCP_CLIENT,         /* TCPÍšÐÅÐ­Òé */
	NET_UDP_MASTER,         /* UDPÍšÐÅÐ­Òé */
	NET_UDP_CLIENT			/* UDPÍšÐÅÐ­Òé */
};

typedef struct iec103_conf
{
	enum  eNETTYPE	eNetType;
	enum  eMBParity	eParity;//ÆæÅŒÐ£Ñé
	char			cLibType[CLIENT_NUM];
    char   			SerialPort[20];//¶Ë¿ÚºÅ
    unsigned long 	ulBaudRate;//²šÌØÂÊ
    unsigned char   ucDataBit;//ÊýŸÝÎ»bit
    unsigned char   ucStopBit;//Í£Ö¹Î»

	/**********************************************/
	char			RemoteIp[20];//Ô¶¶ËIPµØÖ·
	ushort			RemotePort;

	char			LocalIp[20];//±ŸµØIPµØÖ·
	ushort			LocalPort;
	ushort			UdpLocalPort;
	/*********************************************/
	sqlite3    	    *pdb;//ÊýŸÝ¿âÎÄŒþÃèÊö·û
	char  	 		ProtocolXmlName[XML_TABLE_NAME_LEN];//Ð­Òé±í
    char  			TableName[SQL_DB_TABLE_NAME_LEN];//ÊýŸÝ¿â±íÃû
}nrComIEC103Master_Conf;

int  Init103Master(nrComIEC103Master_Conf x);

#endif
