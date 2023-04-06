#include <cstdio>
#include "lora.h"
#include "packet.h"
#include <iostream>

#define SPI_CHANNEL 0
#define SS_PIN      10
#define DIO0_PIN    3
#define RST_PIN     2

using namespace std;

class LoraInterface
{
public:
	LoraInterface();
	~LoraInterface();

	// 參數設定(電源功率, 傳輸頻率, 傳輸頻寬, 傳播因子, 標頭模式, CRC驗證方式, 同步文字)
	void Setting(int TxPower , freq_t Frequency, bw_t Bandwidth, sf_t SpreadFactor, hm_t HeaderMode, cr_t CodingRate, uint8_t SyncWord ); 

	//Lora start
	void Start();
	
	//client send Message
	void Send(char* Message);

	//server receive Message
	void Receive(char* Message);
	
}
