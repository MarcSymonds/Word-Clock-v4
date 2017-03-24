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
LIBS:Word Clock v4-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 2
Title "Button Scan"
Date "25 June 2015"
Rev "1"
Comp "Marc Symonds"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L 4017 U2
U 1 1 558BB5EB
P 4300 3200
F 0 "U2" H 4200 3050 60  0000 C CNN
F 1 "4017" H 4200 2900 60  0000 C CNN
F 2 "Housings_DIP:DIP-16_W7.62mm_LongPads" H 4300 3200 60  0001 C CNN
F 3 "" H 4300 3200 60  0000 C CNN
	1    4300 3200
	1    0    0    -1  
$EndComp
$Comp
L CONN_01X05 P1
U 1 1 558BB645
P 6050 2850
F 0 "P1" H 6050 3150 50  0000 C CNN
F 1 "CONN_01X05" H 6050 2500 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x05" H 6050 2850 60  0001 C CNN
F 3 "" H 6050 2850 60  0000 C CNN
F 4 "Mode/Cancel" H 6150 3050 50  0000 L CNN "B1"
F 5 "Setting" H 6150 2950 50  0000 L CNN "B2"
F 6 "Adjust" H 6150 2850 50  0000 L CNN "B3"
F 7 "Brightness" H 6150 2750 50  0000 L CNN "B4"
F 8 "Common" H 6150 2650 50  0000 L CNN "COM"
	1    6050 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 2650 5850 2650
Wire Wire Line
	4850 2750 5850 2750
Wire Wire Line
	4850 2850 5850 2850
Wire Wire Line
	4850 2950 5850 2950
Wire Wire Line
	4850 3050 5200 3050
Wire Wire Line
	5200 3050 5200 4450
Wire Wire Line
	5200 4450 3450 4450
Wire Wire Line
	3450 4450 3450 3050
Wire Wire Line
	3450 3050 3750 3050
$Comp
L GND #PWR025
U 1 1 558BB6C9
P 3150 3200
F 0 "#PWR025" H 3150 2950 50  0001 C CNN
F 1 "GND" H 3150 3050 50  0000 C CNN
F 2 "" H 3150 3200 60  0000 C CNN
F 3 "" H 3150 3200 60  0000 C CNN
	1    3150 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 2750 3150 2750
Text HLabel 5700 3950 3    60   Output ~ 0
ButDetect
Wire Wire Line
	5850 3050 5700 3050
Wire Wire Line
	5700 3050 5700 3950
Text HLabel 2900 2650 0    60   Input ~ 0
ButClock
Wire Wire Line
	3750 2650 2900 2650
NoConn ~ 4850 3150
NoConn ~ 4850 3250
NoConn ~ 4850 3350
NoConn ~ 4850 3450
NoConn ~ 4850 3550
NoConn ~ 4850 3750
$Comp
L GND #PWR026
U 1 1 5590D9C0
P 5450 4200
F 0 "#PWR026" H 5450 3950 50  0001 C CNN
F 1 "GND" H 5450 4050 50  0000 C CNN
F 2 "" H 5450 4200 60  0000 C CNN
F 3 "" H 5450 4200 60  0000 C CNN
	1    5450 4200
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 5590D9D6
P 5450 3900
F 0 "R4" V 5530 3900 50  0000 C CNN
F 1 "10K" V 5450 3900 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 5380 3900 30  0001 C CNN
F 3 "" H 5450 3900 30  0000 C CNN
	1    5450 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 3750 5450 3650
Wire Wire Line
	5450 3650 5700 3650
Connection ~ 5700 3650
Wire Wire Line
	3150 2750 3150 3200
Wire Wire Line
	5450 4050 5450 4200
$Comp
L GND #PWR027
U 1 1 559422E0
P 4300 4200
F 0 "#PWR027" H 4300 3950 50  0001 C CNN
F 1 "GND" H 4300 4050 50  0000 C CNN
F 2 "" H 4300 4200 60  0000 C CNN
F 3 "" H 4300 4200 60  0000 C CNN
	1    4300 4200
	1    0    0    -1  
$EndComp
$Comp
L +5V #PWR028
U 1 1 5594234E
P 4300 2150
F 0 "#PWR028" H 4300 2000 50  0001 C CNN
F 1 "+5V" H 4300 2290 50  0000 C CNN
F 2 "" H 4300 2150 60  0000 C CNN
F 3 "" H 4300 2150 60  0000 C CNN
	1    4300 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 2400 4300 2150
Wire Wire Line
	4300 4000 4300 4200
Text HLabel 5650 2350 1    60   Output ~ 0
ZeroDetect
Wire Wire Line
	5650 2650 5650 2350
Connection ~ 5650 2650
Text Notes 3500 1200 0    59   ~ 0
Possibly need signal diodes between outputs and buttons.\nThe outputs, when low, are sinks, which means that if multiple\nbuttons are pressed at the same time, any non-active output\nsinks some of the current used to detect the button. This\nmeans the micro controller can't detect simultaneous presses.
$EndSCHEMATC
