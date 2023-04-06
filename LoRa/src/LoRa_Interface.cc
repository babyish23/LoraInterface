// Lora.cc
#include <cstdio>
#include <iostream>
#include <LoraInterface.h>

#define SPI_CHANNEL 0
#define SS_PIN      10 //Dimit: Wpi pin
#define DIO0_PIN    3
#define RST_PIN     2

LoraInterface::LoraInterface()
	:LoRa lora(SPI_CHANNEL, SS_PIN, DIO0_PIN, RST_PIN)
{}

LoraInterface::~LoraInterface()
{

}

std::string LoraInterface::Setting(int TxPower , freq_t Frequency, bw_t Bandwidth, sf_t SpreadFactor, hm_t HeaderMode, cr_t CodingRate, uint8_t SyncWord)
{
	//Dimit: Set Setting
	lora.setFrequency(Frequency)
		->setTXPower(TxPower)
		->setSpreadFactor(Bandwidth)
		->setBandwidth(SpreadFactor)
		->setCodingRate(CodingRate)
		->setSyncWord(SyncWord)
		->setHeaderMode(HeaderMode)
		->enableCRC();


	//Dimit: Print Setting
	printf("LoRa setup successful: chipset version 0x%02x\n", lora.version());
	printf("Configuring radio\n");
	printf("  TX power     : %d dB\n", lora.getTXPower());
	printf("  Frequency    : %d Hz\n", lora.getFrequency());
	printf("  Spread factor: %d\n", lora.getSpreadFactor());
	printf("  Bandwidth    : %d Hz\n", lora.bw[lora.getBandwidth()]);
	printf("  Coding Rate  : 4/%d\n", lora.getCodingRate() + 4);
	printf("  Sync word    : 0x%02x\n", lora.getSyncWord());
	printf("  Header mode  : %s\n\n", lora.getHeaderMode() == LoRa::HM_IMPLICIT ? "Implicit" : "Explicit");
}


//Lora start
void LoraInterface::Start()
{
	lora.begin();
}


//client send Message
void LoraInterface::Send(char* Message)
{
	LoRaPacket p((unsigned char *)message, strlen(message));
	printf("Transmitting packet\n");
	size_t bytes = lora.transmitPacket(&p);
	printf("  %d bytes transmitted\n", bytes);
}


//server receive Message
void LoraInterface::Receive(char* Message)
{
	while(true)
	{
		LoRaPacket p = lora.receivePacket();
		printf("Received packet\n");
		printf("  Bytes   : %d\n", p.payloadLength());
		printf("  RSSI    : %d dBm\n", p.getPacketRSSI());
		printf("  SNR     : %.1f dB\n", p.getSNR());
		printf("  Freq err: %d Hz\n", p.getFreqErr());
		printf("  Payload : \n%s\n", p.getPayload());
		//std::cout << p.getPayload() << std::endl;
		//std::cout << (int)p.getPayload() << std::endl << std::endl;
	}
}