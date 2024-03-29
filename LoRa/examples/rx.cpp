#include <iostream>
#include <cstdio>
#include "lora.h"
#include "packet.h"

#define SPI_CHANNEL 0
#define SS_PIN      10  //header pin:24 GPIO:8 wpi:10
#define DIO0_PIN    3	//header pin:15 GPIO:22 wpi:3
#define RST_PIN     2   //header pin:13 GPIO: wpi:2

int main() {
	printf("Setting up LoRa\n");
	LoRa lora(SPI_CHANNEL, SS_PIN, DIO0_PIN, RST_PIN);
	if (lora.begin()) {
		printf("LoRa setup successful: chipset version 0x%02x\n", lora.version());
		printf("Configuring radio\n");
		lora.setFrequency(LoRa::FREQ_868)
			->setTXPower(17)
			->setSpreadFactor(LoRa::SF_12)
			->setBandwidth(LoRa::BW_125k)
			->setCodingRate(LoRa::CR_48)
			->setSyncWord(0x12)
			->setHeaderMode(LoRa::HM_EXPLICIT)
			->enableCRC();
		printf("  TX power     : %d dB\n", lora.getTXPower());
		printf("  Frequency    : %d Hz\n", lora.getFrequency());
		printf("  Spread factor: %d\n", lora.getSpreadFactor());
		printf("  Bandwidth    : %d Hz\n", lora.bw[lora.getBandwidth()]);
		printf("  Coding Rate  : 4/%d\n", lora.getCodingRate() + 4);
		printf("  Sync word    : 0x%02x\n", lora.getSyncWord());
		printf("  Header mode  : %s\n", lora.getHeaderMode() == LoRa::HM_IMPLICIT ? "Implicit" : "Explicit");
		printf("Receiving...\n");
		while (true) {
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
}