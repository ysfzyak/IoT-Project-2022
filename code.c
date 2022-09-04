#include <wiringPi.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>

void mail(){
	system("echo \"Subject: Bilgilendirme \r\n\r\nEvinizde beklenmedik bir ses oluştu! Sesin algılandığı tarih ve saat bilgileri RaspberryPi4 cihazınıza kaydedildi.\" |msmtp --debug --from=default -t rpitau09@gmail.com");
}

void writeoutput(){
	
	time_t t;
	time(&t);
	FILE * fPtr;
	fPtr = fopen("/home/pi/Desktop/GüvenlikKayıt.txt" , "a");
	
	char ary[100];
	strcpy(ary, "Şu tarihte evinizde bir ses oluştu: ");
	strcat(ary, ctime(&t));
	
	fputs(ary, fPtr);
	fclose(fPtr);
	
}

int main(void){
	
	const int sensor = 1;
	
	wiringPiSetup();
	pinMode(sensor, INPUT);
	
	while(1){
		if(digitalRead(sensor) == LOW){
			mail();
			writeoutput();
			delay(500);
		}
	}
	return 0;
}


