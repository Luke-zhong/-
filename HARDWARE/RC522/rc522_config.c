
#include "rc522_config.h"
//#include "stm32f10x.h"
#include "stm32f1xx.h"
#include "sys.h"

static void             RC522_SPI_Config             ( void );

/**
  * @brief  RC522_Init
  * @param  ��
  * @retval ��
  */
void RC522_Init ( void )
{
	RC522_SPI_Config ();	
	RC522_Reset_Disable();	
	RC522_CS_Disable();
}

//SPI_HandleTypeDef SPI2_Handler;  //SPI1���
/**
  * @brief  R522 SPI����
  * @param  ��
  * @retval ��
  */
static void RC522_SPI_Config ( void )
{
#if 0		
	 GPIO_InitTypeDef GPIO_Initure;


	 __HAL_RCC_GPIOE_CLK_ENABLE();           	//����GPIOEʱ��
		
	 GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  	//�������
	 GPIO_Initure.Pull=GPIO_NOPULL;          	//����
	 GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;    //����

	 GPIO_Initure.Pin=GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_6; 				
	 HAL_GPIO_Init(GPIOE,&GPIO_Initure);
	
	SPI2_Handler.Instance=SPI2;                         //SPI2
    SPI2_Handler.Init.Mode=SPI_MODE_MASTER;             //����SPI����ģʽ������Ϊ��ģʽ
    SPI2_Handler.Init.Direction=SPI_DIRECTION_2LINES;   //����SPI�������˫�������ģʽ:SPI����Ϊ˫��ģʽ
    SPI2_Handler.Init.DataSize=SPI_DATASIZE_8BIT;       //����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
    SPI2_Handler.Init.CLKPolarity=SPI_POLARITY_HIGH;    //����ͬ��ʱ�ӵĿ���״̬Ϊ�ߵ�ƽ
    SPI2_Handler.Init.CLKPhase=SPI_PHASE_2EDGE;         //����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����
    SPI2_Handler.Init.NSS=SPI_NSS_SOFT;                 //NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
    SPI2_Handler.Init.BaudRatePrescaler=SPI_BAUDRATEPRESCALER_256;//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ256
    SPI2_Handler.Init.FirstBit=SPI_FIRSTBIT_MSB;        //ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
    SPI2_Handler.Init.TIMode=SPI_TIMODE_DISABLE;        //�ر�TIģʽ
    SPI2_Handler.Init.CRCCalculation=SPI_CRCCALCULATION_DISABLE;//�ر�Ӳ��CRCУ��
    SPI2_Handler.Init.CRCPolynomial=7;                  //CRCֵ����Ķ���ʽ
    HAL_SPI_Init(&SPI2_Handler);//��ʼ��
    
    __HAL_SPI_ENABLE(&SPI2_Handler);                    //ʹ��SPI2
#endif

#if 1
 GPIO_InitTypeDef GPIO_Initure;

    __HAL_RCC_GPIOF_CLK_ENABLE();           	//����GPIOBʱ��
	//__HAL_RCC_GPIOE_CLK_ENABLE();           	//����GPIOEʱ��
	
    GPIO_Initure.Pin=GPIO_PIN_1; 				//PB13
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  	//�������
    GPIO_Initure.Pull=GPIO_NOPULL;          	//��������
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;    //����
    HAL_GPIO_Init(GPIOF,&GPIO_Initure);

	
	GPIO_Initure.Pin=GPIO_PIN_3; 				//PB15
	HAL_GPIO_Init(GPIOF,&GPIO_Initure);
	
	GPIO_Initure.Pin=GPIO_PIN_7; 				//PE6
	HAL_GPIO_Init(GPIOF,&GPIO_Initure);
	
	GPIO_Initure.Pin=GPIO_PIN_9; 				//PE1
	HAL_GPIO_Init(GPIOF,&GPIO_Initure);
	
	GPIO_Initure.Pin=GPIO_PIN_5; 				//PB14
    GPIO_Initure.Mode=GPIO_MODE_INPUT;  	//��������
    HAL_GPIO_Init(GPIOF,&GPIO_Initure);


#endif
   // SPI2_ReadWriteByte(0Xff);                           //��������
	
//  /* SPI_InitTypeDef  SPI_InitStructure */
//  GPIO_InitTypeDef GPIO_InitStructure;
//  
//	/*!< Configure SPI_RC522_SPI pins: CS */
//	RC522_GPIO_CS_CLK_FUN ( RC522_GPIO_CS_CLK, ENABLE );
//  GPIO_InitStructure.GPIO_Pin = RC522_GPIO_CS_PIN;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = RC522_GPIO_CS_Mode;
//  GPIO_Init(RC522_GPIO_CS_PORT, &GPIO_InitStructure);
//	
//  /*!< Configure SPI_RC522_SPI pins: SCK */
//	RC522_GPIO_SCK_CLK_FUN ( RC522_GPIO_SCK_CLK, ENABLE );
//  GPIO_InitStructure.GPIO_Pin = RC522_GPIO_SCK_PIN;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = RC522_GPIO_SCK_Mode;
//  GPIO_Init(RC522_GPIO_SCK_PORT, &GPIO_InitStructure);
//	
//  /*!< Configure SPI_RC522_SPI pins: MOSI */
//	RC522_GPIO_MOSI_CLK_FUN ( RC522_GPIO_MOSI_CLK, ENABLE );
//  GPIO_InitStructure.GPIO_Pin = RC522_GPIO_MOSI_PIN;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = RC522_GPIO_MOSI_Mode;
//  GPIO_Init(RC522_GPIO_MOSI_PORT, &GPIO_InitStructure);

//  /*!< Configure SPI_RC522_SPI pins: MISO */
//	RC522_GPIO_MISO_CLK_FUN ( RC522_GPIO_MISO_CLK, ENABLE );
//  GPIO_InitStructure.GPIO_Pin = RC522_GPIO_MISO_PIN;
//  GPIO_InitStructure.GPIO_Mode = RC522_GPIO_MISO_Mode;
//  GPIO_Init(RC522_GPIO_MISO_PORT, &GPIO_InitStructure);	
//		
//  /*!< Configure SPI_RC522_SPI pins: RST */
//	RC522_GPIO_RST_CLK_FUN ( RC522_GPIO_RST_CLK, ENABLE );
//  GPIO_InitStructure.GPIO_Pin = RC522_GPIO_RST_PIN;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = RC522_GPIO_RST_Mode;
//  GPIO_Init(RC522_GPIO_RST_PORT, &GPIO_InitStructure);
	
}

//void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
//{
//    GPIO_InitTypeDef GPIO_Initure;
//    
//    __HAL_RCC_GPIOB_CLK_ENABLE();       //ʹ��GPIOBʱ��
//    __HAL_RCC_SPI2_CLK_ENABLE();        //ʹ��SPI2ʱ��
//    
//    //PB13,14,15
//    GPIO_Initure.Pin=GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
//    GPIO_Initure.Mode=GPIO_MODE_AF_PP;              //�����������
//    GPIO_Initure.Pull=GPIO_PULLUP;                  //����
//    GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;        //����            
//    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
//}

//SPI�ٶ����ú���
//SPI�ٶ�=fAPB1/��Ƶϵ��
//@ref SPI_BaudRate_Prescaler:SPI_BAUDRATEPRESCALER_2~SPI_BAUDRATEPRESCALER_2 256
//fAPB1ʱ��һ��Ϊ42Mhz��
//void SPI2_SetSpeed(u8 SPI_BaudRatePrescaler)
//{
//    assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));//�ж���Ч��
//    __HAL_SPI_DISABLE(&SPI2_Handler);            //�ر�SPI
//    SPI2_Handler.Instance->CR1&=0XFFC7;          //λ3-5���㣬�������ò�����
//    SPI2_Handler.Instance->CR1|=SPI_BaudRatePrescaler;//����SPI�ٶ�
//    __HAL_SPI_ENABLE(&SPI2_Handler);             //ʹ��SPI
//    
//}

//SPI1 ��дһ���ֽ�
//TxData:Ҫд����ֽ�
//����ֵ:��ȡ�����ֽ�
//u8 SPI2_ReadWriteByte(u8 TxData)
//{
//    u8 Rxdata;
//    HAL_SPI_TransmitReceive(&SPI2_Handler,&TxData,&Rxdata,1, 1000);       
// 	return Rxdata;          		    //�����յ�������		
//}


