EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	1750 4500 1750 4550
Wire Wire Line
	1750 4550 1800 4550
Wire Wire Line
	1850 4550 1850 4500
Wire Wire Line
	1800 4550 1800 4600
Connection ~ 1800 4550
Wire Wire Line
	1800 4550 1850 4550
$Comp
L power:+5V #PWR07
U 1 1 5FA67628
P 1950 2400
F 0 "#PWR07" H 1950 2250 50  0001 C CNN
F 1 "+5V" H 1965 2573 50  0000 C CNN
F 2 "" H 1950 2400 50  0001 C CNN
F 3 "" H 1950 2400 50  0001 C CNN
	1    1950 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1950 2400 1950 2500
$Comp
L power:+12V #PWR05
U 1 1 5FA6990A
P 1650 2400
F 0 "#PWR05" H 1650 2250 50  0001 C CNN
F 1 "+12V" H 1665 2573 50  0000 C CNN
F 2 "" H 1650 2400 50  0001 C CNN
F 3 "" H 1650 2400 50  0001 C CNN
	1    1650 2400
	1    0    0    -1  
$EndComp
NoConn ~ 1250 2900
NoConn ~ 1250 3000
Text Label 800  3200 0    50   ~ 0
INT
Text Label 2600 4000 2    50   ~ 0
I2C_CLK
Text Label 2600 3900 2    50   ~ 0
I2C_DAT
Wire Wire Line
	2600 3900 2250 3900
Wire Wire Line
	2250 4000 2600 4000
NoConn ~ 1850 2500
NoConn ~ 2250 2900
NoConn ~ 2250 3000
NoConn ~ 2250 3300
Text Label 800  3100 0    50   ~ 0
E_STOP
Wire Wire Line
	800  3200 1250 3200
Wire Wire Line
	1250 3100 800  3100
$Comp
L BREAD_Slice-rescue:10uF_t-OCI_UPL_2_Capacitors C1
U 1 1 5FA94020
P 1600 1350
F 0 "C1" H 1715 1396 50  0000 L CNN
F 1 "10uF_t" H 1715 1305 50  0000 L CNN
F 2 "OCI_UPL_FOOTPRINTS:C_2312" H 1600 1100 30  0001 C CNN
F 3 "https://www.digikey.com/short/qcd8n7" H 1600 1550 30  0001 C CNN
F 4 "T491C106K025AT" H 1600 1600 30  0001 C CNN "Part #"
F 5 "2.021" H 1600 1150 30  0001 C CNN "UPL #"
	1    1600 1350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR04
U 1 1 5FA94026
P 1600 1550
F 0 "#PWR04" H 1600 1300 50  0001 C CNN
F 1 "GND" H 1605 1377 50  0000 C CNN
F 2 "" H 1600 1550 50  0001 C CNN
F 3 "" H 1600 1550 50  0001 C CNN
	1    1600 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1600 1200 1600 1150
Wire Wire Line
	1600 1550 1600 1500
$Comp
L Mechanical:MountingHole H1
U 1 1 5FAB1765
P 1100 4900
F 0 "H1" H 1200 4946 50  0000 L CNN
F 1 "MountingHole" H 1200 4855 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_DIN965_Pad" H 1100 4900 50  0001 C CNN
F 3 "~" H 1100 4900 50  0001 C CNN
	1    1100 4900
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H3
U 1 1 5FAB1B3E
P 1850 4900
F 0 "H3" H 1950 4946 50  0000 L CNN
F 1 "MountingHole" H 1950 4855 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_DIN965_Pad" H 1850 4900 50  0001 C CNN
F 3 "~" H 1850 4900 50  0001 C CNN
	1    1850 4900
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H2
U 1 1 5FAB217D
P 1100 5100
F 0 "H2" H 1200 5146 50  0000 L CNN
F 1 "MountingHole" H 1200 5055 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_DIN965_Pad" H 1100 5100 50  0001 C CNN
F 3 "~" H 1100 5100 50  0001 C CNN
	1    1100 5100
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H4
U 1 1 5FAB25F7
P 1850 5100
F 0 "H4" H 1950 5146 50  0000 L CNN
F 1 "MountingHole" H 1950 5055 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_DIN965_Pad" H 1850 5100 50  0001 C CNN
F 3 "~" H 1850 5100 50  0001 C CNN
	1    1850 5100
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x10_Female J1
U 1 1 5FE6B3C7
P 1400 1450
F 0 "J1" H 1428 1380 50  0000 L CNN
F 1 "Conn_01x10_Female" H 1428 1335 50  0001 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x10_P2.54mm_Horizontal" H 1400 1450 50  0001 C CNN
F 3 "~" H 1400 1450 50  0001 C CNN
	1    1400 1450
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR01
U 1 1 5FE6D224
P 1100 1000
F 0 "#PWR01" H 1100 850 50  0001 C CNN
F 1 "+12V" H 1115 1173 50  0000 C CNN
F 2 "" H 1100 1000 50  0001 C CNN
F 3 "" H 1100 1000 50  0001 C CNN
	1    1100 1000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 5FE6E4CA
P 1150 2000
F 0 "#PWR02" H 1150 1750 50  0001 C CNN
F 1 "GND" H 1155 1827 50  0000 C CNN
F 2 "" H 1150 2000 50  0001 C CNN
F 3 "" H 1150 2000 50  0001 C CNN
	1    1150 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	1150 2000 1150 1950
Wire Wire Line
	1150 1050 1200 1050
Wire Wire Line
	1200 1950 1150 1950
Connection ~ 1150 1950
Wire Wire Line
	1100 1000 1100 1150
Wire Wire Line
	1100 1150 1200 1150
Wire Wire Line
	1200 1850 1100 1850
Wire Wire Line
	1100 1850 1100 1150
Connection ~ 1100 1150
Wire Wire Line
	1200 1450 1150 1450
Connection ~ 1150 1450
Wire Wire Line
	1150 1450 1150 1050
Text Label 750  1250 0    50   ~ 0
I2C_CLK
Text Label 750  1350 0    50   ~ 0
I2C_DAT
Text Label 750  1550 0    50   ~ 0
E_STOP
Text Label 750  1650 0    50   ~ 0
INT
Text Label 750  1750 0    50   ~ 0
SYNC
Wire Wire Line
	1200 1250 750  1250
Wire Wire Line
	750  1350 1200 1350
Wire Wire Line
	1150 1950 1150 1450
Wire Wire Line
	1200 1550 750  1550
Wire Wire Line
	750  1650 1200 1650
Wire Wire Line
	750  1750 1200 1750
$Comp
L power:+12V #PWR03
U 1 1 5FE73FEC
P 1600 1150
F 0 "#PWR03" H 1600 1000 50  0001 C CNN
F 1 "+12V" H 1615 1323 50  0000 C CNN
F 2 "" H 1600 1150 50  0001 C CNN
F 3 "" H 1600 1150 50  0001 C CNN
	1    1600 1150
	1    0    0    -1  
$EndComp
Wire Wire Line
	1650 2400 1650 2500
$Comp
L BREAD_Slice-rescue:10uF_t-OCI_UPL_2_Capacitors C2
U 1 1 5FE84189
P 2100 1350
F 0 "C2" H 2215 1396 50  0000 L CNN
F 1 "10uF_t" H 2215 1305 50  0000 L CNN
F 2 "OCI_UPL_FOOTPRINTS:C_2312" H 2100 1100 30  0001 C CNN
F 3 "https://www.digikey.com/short/qcd8n7" H 2100 1550 30  0001 C CNN
F 4 "T491C106K025AT" H 2100 1600 30  0001 C CNN "Part #"
F 5 "2.021" H 2100 1150 30  0001 C CNN "UPL #"
	1    2100 1350
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR09
U 1 1 5FE8418F
P 2100 1550
F 0 "#PWR09" H 2100 1300 50  0001 C CNN
F 1 "GND" H 2105 1377 50  0000 C CNN
F 2 "" H 2100 1550 50  0001 C CNN
F 3 "" H 2100 1550 50  0001 C CNN
	1    2100 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 1200 2100 1150
Wire Wire Line
	2100 1550 2100 1500
$Comp
L power:+5V #PWR08
U 1 1 5FE8466D
P 2100 1150
F 0 "#PWR08" H 2100 1000 50  0001 C CNN
F 1 "+5V" H 2115 1323 50  0000 C CNN
F 2 "" H 2100 1150 50  0001 C CNN
F 3 "" H 2100 1150 50  0001 C CNN
	1    2100 1150
	1    0    0    -1  
$EndComp
Wire Notes Line
	700  5250 2650 5250
Wire Notes Line
	2650 750  700  750 
Wire Notes Line
	650  5300 2700 5300
Wire Notes Line
	2700 600  650  600 
Wire Notes Line
	650  600  650  5300
Text Notes 750  750  0    100  ~ 0
Core Slice Components
$Comp
L Graphic:Logo_Open_Hardware_Small Logo1
U 1 1 5FE4A934
P 10950 6850
F 0 "Logo1" H 10950 7125 50  0001 C CNN
F 1 "Logo_Open_Hardware_Small" H 10950 6625 50  0001 C CNN
F 2 "Symbol:OSHW-Symbol_6.7x6mm_SilkScreen" H 10950 6850 50  0001 C CNN
F 3 "~" H 10950 6850 50  0001 C CNN
	1    10950 6850
	1    0    0    -1  
$EndComp
$Comp
L Driver_Motor:Pololu_Breakout_A4988 A2
U 1 1 6090DC30
P 6100 1650
F 0 "A2" H 6200 500 50  0000 C CNN
F 1 "Pololu_Breakout_A4988" H 6150 600 50  0000 C CNN
F 2 "Module:Pololu_Breakout-16_15.2x20.3mm" H 6375 900 50  0001 L CNN
F 3 "https://www.pololu.com/product/2980/pictures" H 6200 1350 50  0001 C CNN
	1    6100 1650
	1    0    0    -1  
$EndComp
$Comp
L Driver_Motor:Pololu_Breakout_A4988 A3
U 1 1 6090E205
P 7850 1650
F 0 "A3" H 7950 500 50  0000 C CNN
F 1 "Pololu_Breakout_A4988" H 7900 600 50  0000 C CNN
F 2 "Module:Pololu_Breakout-16_15.2x20.3mm" H 8125 900 50  0001 L CNN
F 3 "https://www.pololu.com/product/2980/pictures" H 7950 1350 50  0001 C CNN
	1    7850 1650
	1    0    0    -1  
$EndComp
$Comp
L Driver_Motor:Pololu_Breakout_A4988 A4
U 1 1 6090EAD3
P 9700 1650
F 0 "A4" H 9800 500 50  0000 C CNN
F 1 "Pololu_Breakout_A4988" H 9750 600 50  0000 C CNN
F 2 "Module:Pololu_Breakout-16_15.2x20.3mm" H 9975 900 50  0001 L CNN
F 3 "https://www.pololu.com/product/2980/pictures" H 9800 1350 50  0001 C CNN
	1    9700 1650
	1    0    0    -1  
$EndComp
Text Label 3700 1650 2    50   ~ 0
ST_1
Text Label 3700 1750 2    50   ~ 0
DR_1
Text Label 5500 1650 2    50   ~ 0
ST_2
Text Label 5500 1750 2    50   ~ 0
DR_2
Text Label 7200 1650 2    50   ~ 0
ST_3
Text Label 7200 1750 2    50   ~ 0
DR_3
Text Label 9100 1650 2    50   ~ 0
ST_4
Text Label 9100 1750 2    50   ~ 0
DR_4
Wire Wire Line
	3900 1650 3700 1650
Wire Wire Line
	3900 1750 3700 1750
Wire Wire Line
	5700 1650 5500 1650
Wire Wire Line
	5700 1750 5500 1750
Wire Wire Line
	7450 1650 7200 1650
Wire Wire Line
	7450 1750 7200 1750
Wire Wire Line
	9300 1650 9100 1650
Wire Wire Line
	9300 1750 9100 1750
Wire Wire Line
	3900 1350 3900 1250
Wire Wire Line
	5700 1350 5700 1250
Wire Wire Line
	7450 1350 7450 1250
Wire Wire Line
	9300 1350 9300 1250
$Comp
L power:GND #PWR0101
U 1 1 6095DB78
P 4400 2550
F 0 "#PWR0101" H 4400 2300 50  0001 C CNN
F 1 "GND" H 4750 2600 50  0000 C CNN
F 2 "" H 4400 2550 50  0001 C CNN
F 3 "" H 4400 2550 50  0001 C CNN
	1    4400 2550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 60961D77
P 6200 2550
F 0 "#PWR0102" H 6200 2300 50  0001 C CNN
F 1 "GND" H 6550 2600 50  0000 C CNN
F 2 "" H 6200 2550 50  0001 C CNN
F 3 "" H 6200 2550 50  0001 C CNN
	1    6200 2550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 60962457
P 7950 2550
F 0 "#PWR0103" H 7950 2300 50  0001 C CNN
F 1 "GND" H 8300 2600 50  0000 C CNN
F 2 "" H 7950 2550 50  0001 C CNN
F 3 "" H 7950 2550 50  0001 C CNN
	1    7950 2550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0104
U 1 1 60962A90
P 9800 2550
F 0 "#PWR0104" H 9800 2300 50  0001 C CNN
F 1 "GND" H 10150 2600 50  0000 C CNN
F 2 "" H 9800 2550 50  0001 C CNN
F 3 "" H 9800 2550 50  0001 C CNN
	1    9800 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 2450 4400 2450
Wire Wire Line
	4400 2450 4400 2550
Wire Wire Line
	4500 2450 4400 2450
Connection ~ 4400 2450
Wire Wire Line
	6100 2450 6200 2450
Wire Wire Line
	6200 2450 6200 2550
Wire Wire Line
	6300 2450 6200 2450
Connection ~ 6200 2450
Wire Wire Line
	7850 2450 7950 2450
Wire Wire Line
	7950 2450 7950 2550
Wire Wire Line
	8050 2450 7950 2450
Connection ~ 7950 2450
Wire Wire Line
	9700 2450 9800 2450
Wire Wire Line
	9800 2450 9800 2550
Wire Wire Line
	9900 2450 9800 2450
Connection ~ 9800 2450
$Comp
L power:+5V #PWR0105
U 1 1 609716E4
P 4300 850
F 0 "#PWR0105" H 4300 700 50  0001 C CNN
F 1 "+5V" H 4315 1023 50  0000 C CNN
F 2 "" H 4300 850 50  0001 C CNN
F 3 "" H 4300 850 50  0001 C CNN
	1    4300 850 
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0106
U 1 1 6097EFB7
P 6100 850
F 0 "#PWR0106" H 6100 700 50  0001 C CNN
F 1 "+5V" H 6115 1023 50  0000 C CNN
F 2 "" H 6100 850 50  0001 C CNN
F 3 "" H 6100 850 50  0001 C CNN
	1    6100 850 
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0107
U 1 1 6097F7BB
P 7850 850
F 0 "#PWR0107" H 7850 700 50  0001 C CNN
F 1 "+5V" H 7865 1023 50  0000 C CNN
F 2 "" H 7850 850 50  0001 C CNN
F 3 "" H 7850 850 50  0001 C CNN
	1    7850 850 
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0108
U 1 1 6097FFB3
P 9700 850
F 0 "#PWR0108" H 9700 700 50  0001 C CNN
F 1 "+5V" H 9715 1023 50  0000 C CNN
F 2 "" H 9700 850 50  0001 C CNN
F 3 "" H 9700 850 50  0001 C CNN
	1    9700 850 
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 950  4300 850 
Wire Wire Line
	6100 950  6100 850 
Wire Wire Line
	7850 950  7850 850 
Wire Wire Line
	9700 950  9700 850 
$Comp
L MCU_Module:Arduino_Nano_v3.x G1
U 1 1 5FCAD89B
P 1750 3500
F 0 "G1" H 1600 2400 50  0000 C CNN
F 1 "Arduino_Nano_v3.x" H 2250 2550 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 1750 3500 50  0001 C CIN
F 3 "http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf" H 1750 3500 50  0001 C CNN
	1    1750 3500
	1    0    0    -1  
$EndComp
Text Label 2400 3500 0    50   ~ 0
AG_1
Text Label 2400 3600 0    50   ~ 0
AG_2
Text Label 2400 3700 0    50   ~ 0
AG_3
Text Label 2400 3800 0    50   ~ 0
AG_4
Wire Wire Line
	2250 3500 2400 3500
Wire Wire Line
	2250 3600 2400 3600
Wire Wire Line
	2250 3700 2400 3700
Wire Wire Line
	2250 3800 2400 3800
Text Label 1100 4000 2    50   ~ 0
ST_4
Text Label 1100 4100 2    50   ~ 0
DR_4
Text Label 1100 3900 2    50   ~ 0
DR_3
Text Label 1100 3800 2    50   ~ 0
ST_3
Text Label 1100 3700 2    50   ~ 0
DR_2
Text Label 1100 3600 2    50   ~ 0
ST_2
Text Label 1100 3500 2    50   ~ 0
DR_1
Text Label 1100 3400 2    50   ~ 0
ST_1
Wire Notes Line
	2650 750  2650 5250
Text Label 800  3300 0    50   ~ 0
SYNC
Wire Wire Line
	800  3300 1250 3300
$Comp
L Driver_Motor:Pololu_Breakout_A4988 A1
U 1 1 60909470
P 4300 1650
F 0 "A1" H 4350 450 50  0000 C CNN
F 1 "Pololu_Breakout_A4988" H 4350 600 50  0000 C CNN
F 2 "Module:Pololu_Breakout-16_15.2x20.3mm" H 4575 900 50  0001 L CNN
F 3 "https://www.pololu.com/product/2980/pictures" H 4400 1350 50  0001 C CNN
	1    4300 1650
	1    0    0    -1  
$EndComp
NoConn ~ 5700 1550
NoConn ~ 3900 1550
NoConn ~ 7450 1550
NoConn ~ 9300 1550
Wire Wire Line
	1250 3400 1100 3400
Wire Wire Line
	1250 3500 1100 3500
Wire Wire Line
	1250 3600 1100 3600
Wire Wire Line
	1250 3700 1100 3700
Wire Wire Line
	1250 3800 1100 3800
Wire Wire Line
	1250 3900 1100 3900
Wire Wire Line
	1250 4000 1100 4000
Wire Wire Line
	1250 4100 1100 4100
Text Label 2400 4100 0    50   ~ 0
MS1
Text Label 2400 4200 0    50   ~ 0
MS2
Text Label 1100 4200 2    50   ~ 0
MS3
Wire Wire Line
	2250 4100 2400 4100
Wire Wire Line
	2250 4200 2400 4200
Wire Wire Line
	1250 4200 1100 4200
Text Label 3750 1950 2    50   ~ 0
MS1
Text Label 3750 2050 2    50   ~ 0
MS2
Text Label 3750 2150 2    50   ~ 0
MS3
Wire Wire Line
	3750 1950 3900 1950
Wire Wire Line
	3750 2050 3900 2050
Wire Wire Line
	3750 2150 3900 2150
Text Label 5550 1950 2    50   ~ 0
MS1
Text Label 5550 2050 2    50   ~ 0
MS2
Text Label 5550 2150 2    50   ~ 0
MS3
Wire Wire Line
	5550 1950 5700 1950
Wire Wire Line
	5550 2050 5700 2050
Wire Wire Line
	5550 2150 5700 2150
Text Label 7300 1950 2    50   ~ 0
MS1
Text Label 7300 2050 2    50   ~ 0
MS2
Text Label 7300 2150 2    50   ~ 0
MS3
Wire Wire Line
	7300 1950 7450 1950
Wire Wire Line
	7300 2050 7450 2050
Wire Wire Line
	7300 2150 7450 2150
$Comp
L Connector:Screw_Terminal_01x08 J4
U 1 1 60A4BD90
P 10350 4450
F 0 "J4" H 10050 3850 50  0000 R CNN
F 1 "Screw_Terminal_01x08" H 10350 3750 50  0000 R CNN
F 2 "TerminalBlock_TE-Connectivity:TerminalBlock_TE_282834-8_1x08_P2.54mm_Horizontal" H 10350 4450 50  0001 C CNN
F 3 "~" H 10350 4450 50  0001 C CNN
	1    10350 4450
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x08 J3
U 1 1 60A4D391
P 9000 4450
F 0 "J3" H 8800 3850 50  0000 R CNN
F 1 "Screw_Terminal_01x08" H 9150 3750 50  0000 R CNN
F 2 "TerminalBlock_TE-Connectivity:TerminalBlock_TE_282834-8_1x08_P2.54mm_Horizontal" H 9000 4450 50  0001 C CNN
F 3 "~" H 9000 4450 50  0001 C CNN
	1    9000 4450
	1    0    0    -1  
$EndComp
Text Label 4900 1550 0    50   ~ 0
1_1B
Text Label 4900 1650 0    50   ~ 0
1_1A
Text Label 4900 1750 0    50   ~ 0
1_2A
Text Label 4900 1850 0    50   ~ 0
1_2B
Text Label 6700 1550 0    50   ~ 0
2_1B
Text Label 6700 1650 0    50   ~ 0
2_1A
Text Label 6700 1750 0    50   ~ 0
2_2A
Text Label 6700 1850 0    50   ~ 0
2_2B
Text Label 8450 1550 0    50   ~ 0
3_1B
Text Label 8450 1650 0    50   ~ 0
3_1A
Text Label 8450 1750 0    50   ~ 0
3_2A
Text Label 8450 1850 0    50   ~ 0
3_2B
Text Label 10300 1550 0    50   ~ 0
4_1B
Text Label 10300 1650 0    50   ~ 0
4_1A
Text Label 10300 1750 0    50   ~ 0
4_2A
Text Label 10300 1850 0    50   ~ 0
4_2B
Text Label 8650 4550 2    50   ~ 0
1_1B
Text Label 8650 4650 2    50   ~ 0
1_1A
Text Label 8650 4750 2    50   ~ 0
1_2A
Text Label 8650 4850 2    50   ~ 0
1_2B
Text Label 8650 4150 2    50   ~ 0
2_1B
Text Label 8650 4250 2    50   ~ 0
2_1A
Text Label 8650 4350 2    50   ~ 0
2_2A
Text Label 8650 4450 2    50   ~ 0
2_2B
Text Label 10000 4450 2    50   ~ 0
3_1B
Text Label 10000 4350 2    50   ~ 0
3_1A
Text Label 10000 4250 2    50   ~ 0
3_2A
Text Label 10000 4150 2    50   ~ 0
3_2B
Text Label 10000 4850 2    50   ~ 0
4_1B
Text Label 10000 4750 2    50   ~ 0
4_1A
Text Label 10000 4650 2    50   ~ 0
4_2A
Text Label 10000 4550 2    50   ~ 0
4_2B
Wire Wire Line
	10000 4450 10150 4450
Wire Wire Line
	10000 4350 10150 4350
Wire Wire Line
	10000 4250 10150 4250
Wire Wire Line
	10000 4150 10150 4150
Wire Wire Line
	10000 4850 10150 4850
Wire Wire Line
	10000 4750 10150 4750
Wire Wire Line
	10000 4650 10150 4650
Wire Wire Line
	10000 4550 10150 4550
$Comp
L Connector:Screw_Terminal_01x04 J2
U 1 1 60AC48D5
P 7250 4400
F 0 "J2" H 7500 4300 50  0000 L CNN
F 1 "Screw_Terminal_01x04" H 6900 3900 50  0000 L CNN
F 2 "TerminalBlock_TE-Connectivity:TerminalBlock_TE_282834-4_1x04_P2.54mm_Horizontal" H 7250 4400 50  0001 C CNN
F 3 "~" H 7250 4400 50  0001 C CNN
	1    7250 4400
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 60AC6879
P 5100 3500
F 0 "R1" V 4893 3500 50  0000 C CNN
F 1 "1k" V 4984 3500 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 5030 3500 50  0001 C CNN
F 3 "~" H 5100 3500 50  0001 C CNN
	1    5100 3500
	0    1    1    0   
$EndComp
$Comp
L Device:D_Zener D1
U 1 1 60AC7C2F
P 4800 3700
F 0 "D1" V 4754 3780 50  0000 L CNN
F 1 "5V" V 4845 3780 50  0000 L CNN
F 2 "Diode_SMD:D_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 4800 3700 50  0001 C CNN
F 3 "~" H 4800 3700 50  0001 C CNN
	1    4800 3700
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0113
U 1 1 60ACE6FA
P 4800 3950
F 0 "#PWR0113" H 4800 3700 50  0001 C CNN
F 1 "GND" H 5150 4000 50  0000 C CNN
F 2 "" H 4800 3950 50  0001 C CNN
F 3 "" H 4800 3950 50  0001 C CNN
	1    4800 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 3500 4950 3500
Text Label 5500 3500 0    50   ~ 0
A_IN1
Wire Wire Line
	5500 3500 5250 3500
Text Label 4450 3500 2    50   ~ 0
AG_1
Wire Wire Line
	4450 3500 4800 3500
Connection ~ 4800 3500
Wire Wire Line
	4800 3550 4800 3500
Wire Wire Line
	4800 3950 4800 3850
$Comp
L Device:R R2
U 1 1 60AE9158
P 5100 4350
F 0 "R2" V 4893 4350 50  0000 C CNN
F 1 "1k" V 4984 4350 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 5030 4350 50  0001 C CNN
F 3 "~" H 5100 4350 50  0001 C CNN
	1    5100 4350
	0    1    1    0   
$EndComp
$Comp
L Device:D_Zener D2
U 1 1 60AE915E
P 4800 4550
F 0 "D2" V 4754 4630 50  0000 L CNN
F 1 "5V" V 4845 4630 50  0000 L CNN
F 2 "Diode_SMD:D_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 4800 4550 50  0001 C CNN
F 3 "~" H 4800 4550 50  0001 C CNN
	1    4800 4550
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0114
U 1 1 60AE9164
P 4800 4800
F 0 "#PWR0114" H 4800 4550 50  0001 C CNN
F 1 "GND" H 5150 4850 50  0000 C CNN
F 2 "" H 4800 4800 50  0001 C CNN
F 3 "" H 4800 4800 50  0001 C CNN
	1    4800 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 4350 4950 4350
Text Label 5500 4350 0    50   ~ 0
A_IN2
Wire Wire Line
	5500 4350 5250 4350
Text Label 4450 4350 2    50   ~ 0
AG_2
Wire Wire Line
	4450 4350 4800 4350
Connection ~ 4800 4350
Wire Wire Line
	4800 4400 4800 4350
Wire Wire Line
	4800 4800 4800 4700
$Comp
L Device:R R3
U 1 1 60AF1AA7
P 5100 5350
F 0 "R3" V 4893 5350 50  0000 C CNN
F 1 "1k" V 4984 5350 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 5030 5350 50  0001 C CNN
F 3 "~" H 5100 5350 50  0001 C CNN
	1    5100 5350
	0    1    1    0   
$EndComp
$Comp
L Device:D_Zener D3
U 1 1 60AF1AAD
P 4800 5550
F 0 "D3" V 4754 5630 50  0000 L CNN
F 1 "5V" V 4845 5630 50  0000 L CNN
F 2 "Diode_SMD:D_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 4800 5550 50  0001 C CNN
F 3 "~" H 4800 5550 50  0001 C CNN
	1    4800 5550
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0115
U 1 1 60AF1AB3
P 4800 5800
F 0 "#PWR0115" H 4800 5550 50  0001 C CNN
F 1 "GND" H 5150 5850 50  0000 C CNN
F 2 "" H 4800 5800 50  0001 C CNN
F 3 "" H 4800 5800 50  0001 C CNN
	1    4800 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 5350 4950 5350
Text Label 5500 5350 0    50   ~ 0
A_IN3
Wire Wire Line
	5500 5350 5250 5350
Text Label 4450 5350 2    50   ~ 0
AG_3
Wire Wire Line
	4450 5350 4800 5350
Connection ~ 4800 5350
Wire Wire Line
	4800 5400 4800 5350
Wire Wire Line
	4800 5800 4800 5700
$Comp
L Device:R R4
U 1 1 60AF5F30
P 5100 6250
F 0 "R4" V 4893 6250 50  0000 C CNN
F 1 "1k" V 4984 6250 50  0000 C CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.30x1.75mm_HandSolder" V 5030 6250 50  0001 C CNN
F 3 "~" H 5100 6250 50  0001 C CNN
	1    5100 6250
	0    1    1    0   
$EndComp
$Comp
L Device:D_Zener D4
U 1 1 60AF5F36
P 4800 6450
F 0 "D4" V 4754 6530 50  0000 L CNN
F 1 "5V" V 4845 6530 50  0000 L CNN
F 2 "Diode_SMD:D_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 4800 6450 50  0001 C CNN
F 3 "~" H 4800 6450 50  0001 C CNN
	1    4800 6450
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0116
U 1 1 60AF5F3C
P 4800 6700
F 0 "#PWR0116" H 4800 6450 50  0001 C CNN
F 1 "GND" H 5150 6750 50  0000 C CNN
F 2 "" H 4800 6700 50  0001 C CNN
F 3 "" H 4800 6700 50  0001 C CNN
	1    4800 6700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 6250 4950 6250
Text Label 5500 6250 0    50   ~ 0
A_IN4
Wire Wire Line
	5500 6250 5250 6250
Text Label 4450 6250 2    50   ~ 0
AG_4
Wire Wire Line
	4450 6250 4800 6250
Connection ~ 4800 6250
Wire Wire Line
	4800 6300 4800 6250
Wire Wire Line
	4800 6700 4800 6600
Text Label 6800 4300 2    50   ~ 0
A_IN1
Text Label 6800 4400 2    50   ~ 0
A_IN2
Text Label 6800 4500 2    50   ~ 0
A_IN3
Text Label 6800 4600 2    50   ~ 0
A_IN4
Wire Wire Line
	6800 4300 7050 4300
Wire Wire Line
	6800 4400 7050 4400
Wire Wire Line
	6800 4500 7050 4500
Wire Wire Line
	6800 4600 7050 4600
$Comp
L power:GND #PWR06
U 1 1 5FA66343
P 1800 4600
F 0 "#PWR06" H 1800 4350 50  0001 C CNN
F 1 "GND" H 2150 4650 50  0000 C CNN
F 2 "" H 1800 4600 50  0001 C CNN
F 3 "" H 1800 4600 50  0001 C CNN
	1    1800 4600
	1    0    0    -1  
$EndComp
Text Label 9150 1950 2    50   ~ 0
MS1
Text Label 9150 2050 2    50   ~ 0
MS2
Text Label 9150 2150 2    50   ~ 0
MS3
Wire Wire Line
	9150 1950 9300 1950
Wire Wire Line
	9150 2050 9300 2050
Wire Wire Line
	9150 2150 9300 2150
Wire Wire Line
	10300 1550 10200 1550
Wire Wire Line
	10300 1650 10200 1650
Wire Wire Line
	10300 1750 10200 1750
Wire Wire Line
	10300 1850 10200 1850
Wire Wire Line
	8450 1550 8350 1550
Wire Wire Line
	8450 1650 8350 1650
Wire Wire Line
	8450 1750 8350 1750
Wire Wire Line
	8450 1850 8350 1850
Wire Wire Line
	6700 1550 6600 1550
Wire Wire Line
	6700 1650 6600 1650
Wire Wire Line
	6700 1750 6600 1750
Wire Wire Line
	6700 1850 6600 1850
Wire Wire Line
	4900 1550 4800 1550
Wire Wire Line
	4900 1650 4800 1650
Wire Wire Line
	4900 1750 4800 1750
Wire Wire Line
	4900 1850 4800 1850
$Comp
L BREAD_Slice-rescue:10uF_t-OCI_UPL_2_Capacitors C3
U 1 1 60978411
P 2450 5700
F 0 "C3" V 2650 5450 50  0000 L CNN
F 1 "10uF_t" V 2550 5350 50  0000 L CNN
F 2 "OCI_UPL_FOOTPRINTS:C_2312" H 2450 5450 30  0001 C CNN
F 3 "https://www.digikey.com/short/qcd8n7" H 2450 5900 30  0001 C CNN
F 4 "T491C106K025AT" H 2450 5950 30  0001 C CNN "Part #"
F 5 "2.021" H 2450 5500 30  0001 C CNN "UPL #"
	1    2450 5700
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J6
U 1 1 6097C6EF
P 2400 5950
F 0 "J6" V 2500 5300 50  0000 R CNN
F 1 "Screw_Terminal_01x02" V 2350 5600 50  0000 R CNN
F 2 "TerminalBlock_TE-Connectivity:TerminalBlock_TE_282834-2_1x02_P2.54mm_Horizontal" H 2400 5950 50  0001 C CNN
F 3 "~" H 2400 5950 50  0001 C CNN
	1    2400 5950
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0109
U 1 1 6097FF86
P 2500 6250
F 0 "#PWR0109" H 2500 6000 50  0001 C CNN
F 1 "GND" H 2650 6250 50  0000 C CNN
F 2 "" H 2500 6250 50  0001 C CNN
F 3 "" H 2500 6250 50  0001 C CNN
	1    2500 6250
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x03_Male J5
U 1 1 60980F5B
P 2200 6450
F 0 "J5" V 1900 6450 50  0000 C CNN
F 1 "Conn_01x03_Male" V 2050 6450 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x03_P2.54mm_Vertical" H 2200 6450 50  0001 C CNN
F 3 "~" H 2200 6450 50  0001 C CNN
	1    2200 6450
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 6150 2500 6250
Wire Wire Line
	2400 6150 2400 6350
$Comp
L power:+12V #PWR0110
U 1 1 6099BAB9
P 2700 6450
F 0 "#PWR0110" H 2700 6300 50  0001 C CNN
F 1 "+12V" H 2715 6623 50  0000 C CNN
F 2 "" H 2700 6450 50  0001 C CNN
F 3 "" H 2700 6450 50  0001 C CNN
	1    2700 6450
	0    1    1    0   
$EndComp
Wire Wire Line
	2400 6450 2700 6450
Text Label 2400 6700 3    50   ~ 0
M_POWER
Wire Wire Line
	2400 6550 2400 6700
Wire Wire Line
	2300 5700 2200 5700
Wire Wire Line
	2200 5700 2200 6150
Wire Wire Line
	2200 6150 2400 6150
Connection ~ 2400 6150
Wire Wire Line
	2600 5700 2700 5700
Wire Wire Line
	2700 5700 2700 6150
Wire Wire Line
	2700 6150 2500 6150
Connection ~ 2500 6150
Text Label 4650 800  0    50   ~ 0
M_POWER
Text Label 6450 800  0    50   ~ 0
M_POWER
Text Label 8250 800  0    50   ~ 0
M_POWER
Text Label 10100 800  0    50   ~ 0
M_POWER
Wire Wire Line
	10100 800  9900 800 
Wire Wire Line
	9900 800  9900 950 
Wire Wire Line
	8250 800  8050 800 
Wire Wire Line
	8050 800  8050 950 
Wire Wire Line
	6450 800  6300 800 
Wire Wire Line
	6300 800  6300 950 
Wire Wire Line
	4650 800  4500 800 
Wire Wire Line
	4500 800  4500 950 
Wire Wire Line
	8800 4150 8650 4150
Wire Wire Line
	8800 4250 8650 4250
Wire Wire Line
	8800 4350 8650 4350
Wire Wire Line
	8800 4450 8650 4450
Wire Wire Line
	8800 4550 8650 4550
Wire Wire Line
	8800 4650 8650 4650
Wire Wire Line
	8800 4750 8650 4750
Wire Wire Line
	8800 4850 8650 4850
$EndSCHEMATC
