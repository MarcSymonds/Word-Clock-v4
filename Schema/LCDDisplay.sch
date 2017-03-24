EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:Word Clock v3-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 3
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L CONN_01X04 P2
U 1 1 558BCD79
P 4550 2950
F 0 "P2" H 4550 3200 50  0000 C CNN
F 1 "LCD Power" H 4550 2650 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04" H 4550 2950 60  0001 C CNN
F 3 "" H 4550 2950 60  0000 C CNN
F 4 "VDD (2)" H 4650 3100 50  0000 L CNN "P1"
F 5 "VSS (1)" H 4650 3000 50  0000 L CNN "P2"
F 6 "LED+ (15)" H 4650 2900 60  0000 L CNN "P3"
F 7 "LED- (16)" H 4650 2800 50  0000 L CNN "P4"
	1    4550 2950
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X08 P3
U 1 1 558BCE47
P 4550 4500
F 0 "P3" H 4550 4950 50  0000 C CNN
F 1 "LCD Control" H 4550 4000 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x08" H 4550 4500 60  0001 C CNN
F 3 "" H 4550 4500 60  0000 C CNN
F 4 "VO (3)" H 4650 4850 50  0000 L CNN "P1"
F 5 "RS (4)" H 4650 4750 50  0000 L CNN "P2"
F 6 "R/W (5)" H 4650 4650 50  0000 L CNN "P3"
F 7 "E (6)" H 4650 4550 50  0000 L CNN "P4"
F 8 "DB4 (11)" H 4650 4450 50  0000 L CNN "P5"
F 9 "DB5 (12)" H 4650 4350 50  0000 L CNN "P6"
F 10 "DB6 (13)" H 4650 4250 50  0000 L CNN "P7"
F 11 "DB7 (14)" H 4650 4150 50  0000 L CNN "P8"
	1    4550 4500
	1    0    0    -1  
$EndComp
$Comp
L POT RV1
U 1 1 558BDAB9
P 3950 3950
F 0 "RV1" H 3950 3850 50  0000 C CNN
F 1 "10K" H 3950 3950 50  0000 C CNN
F 2 "Potentiometers:Potentiometer_VishaySpectrol-Econtrim-Type36T" H 3950 3950 60  0001 C CNN
F 3 "" H 3950 3950 60  0000 C CNN
F 4 "Contrast" H 3800 4050 39  0000 C CNN "Label"
	1    3950 3950
	-1   0    0    1   
$EndComp
Text HLabel 2750 2800 0    60   Input ~ 0
DisplayPwr
Text HLabel 2750 2900 0    60   Input ~ 0
DisplayGND
Text HLabel 2750 3000 0    60   Input ~ 0
LEDPwr
Text HLabel 2750 3100 0    60   Input ~ 0
LEDGND
Text HLabel 2750 4250 0    60   Input ~ 0
RegisterSelect
Text HLabel 2750 4350 0    60   Input ~ 0
Read/Write
Text HLabel 2750 4450 0    60   Input ~ 0
Enable
Text HLabel 2750 4550 0    60   BiDi ~ 0
D0
Text HLabel 2750 4650 0    60   BiDi ~ 0
D1
Text HLabel 2750 4750 0    60   BiDi ~ 0
D2
Text HLabel 2750 4850 0    60   BiDi ~ 0
D3
Wire Wire Line
	2750 2800 3300 2800
Wire Wire Line
	3500 2800 4350 2800
Wire Wire Line
	4350 4850 2750 4850
Wire Wire Line
	4350 4750 2750 4750
Wire Wire Line
	4350 4650 2750 4650
Wire Wire Line
	4350 4550 2750 4550
Wire Wire Line
	4350 4350 2750 4350
Wire Wire Line
	4350 4250 2750 4250
Wire Wire Line
	2750 3000 3300 3000
Wire Wire Line
	2750 3100 4350 3100
Wire Wire Line
	3950 4100 3950 4150
Wire Wire Line
	3950 4150 4350 4150
Wire Wire Line
	2750 2900 4350 2900
Wire Wire Line
	4200 3950 4250 3950
Wire Wire Line
	4250 3950 4250 2900
Connection ~ 4250 2900
Wire Wire Line
	3700 3950 3650 3950
Wire Wire Line
	3650 3950 3650 2800
Connection ~ 3650 2800
Wire Wire Line
	2750 4450 4350 4450
$Comp
L Jumper_NO_Small JP1
U 1 1 559110C4
P 3400 2800
F 0 "JP1" H 3400 2880 50  0000 C CNN
F 1 "Enable LCD" H 3410 2740 39  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 3400 2800 60  0001 C CNN
F 3 "" H 3400 2800 60  0000 C CNN
	1    3400 2800
	1    0    0    -1  
$EndComp
$Comp
L Jumper_NO_Small JP2
U 1 1 559110E3
P 3400 3000
F 0 "JP2" H 3400 3080 50  0000 C CNN
F 1 "Enable LCD BL" H 3410 2940 39  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 3400 3000 60  0001 C CNN
F 3 "" H 3400 3000 60  0000 C CNN
	1    3400 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 3000 3500 3000
Text Label 3800 2800 0    39   ~ 0
DisplayPwrx
Text Label 3850 3000 0    39   ~ 0
LEDPwrx
$EndSCHEMATC
