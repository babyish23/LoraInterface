#include <cstdio>
#include "lora.h"
#include "packet.h"
#include <LoraInterface.h>

LoraInterface Lora();

int main() {

	//LoRa fundamental setting  這邊的基本設定先預設好 之後可以做更改
	Lora.Setting(17,  FREQ_868,  BW_250k,  SF_12,  "HM_EXPLICIT",  CR_48, 0x12);

	//Lora start
	Lora.Start();
	
	//client send Message
	char* message = "Hello World !";
	Lora.Send(char* Message);

	//server receive Message
	Lora.Receive(char* Message);

}