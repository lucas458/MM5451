# Driver para o MM5451 usando Arduino
A placa que usei possiu:
* 1x MM5451V
* 6x Botões
* 6x LEDs
* 5x Displays 7 Segmentos **Anodo comum**


![Placa](https://github.com/lucas458/MM5451/blob/main/image/placa.jpg?raw=true "Placa")



## Datasheets
* [Driver do Display - MM5451](https://github.com/lucas458/MM5451/blob/main/datasheet/MM5451V.PDF)
* [Display 7 Segmentos - TDSO5150](https://github.com/lucas458/MM5451/blob/main/datasheet/tdsx51x0.pdf)
* [Transistor PNP - BC856-3F](https://github.com/lucas458/MM5451/blob/main/datasheet/BC856.PDF)


#### O display é multiplexado com dois transistores **PNP** ligados no bit1 e bit2.

| Bit1 | Bit2 | Descrição |
| :-: | :-: | :- |
| 0 | 0 | Desligado |
| 0 | 1 | Controla o display 1 e os LEDs |
| 1 | 0 | Controla os displays 2 ao 5 |
| 1 | 1 | **Ilegal** |

### Quando o **bit1** = `1`

| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 | 20 | 21 | 22 | 23 | 24 | 25 | 26 | 27 | 28 | 29 | 30 | 31 | 32 | 33 | 34 | 35
| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |:-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |:-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| _1_ | _0_ | - | D5-A | D5-B | D5-C | D5-D | D5-E | D5-F | D5-G | D5-dp | D4-A | D4-B | D4-C | D4-D | D4-E | D4-F | D4-G| D4-dp | D3-A | D3-B | D3-C | D3-D | D3-E | D3-F | D3-G | D3-dp | D2-A | D2-B | D2-C | D2-D | D2-E | D2-F | D2-G | D2-dp





### Quando o **bit2** = `1`

| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 | 20 | 21 | 22 | 23 | 24 | 25 | 26 | 27 | 28 | 29 | 30 | 31 | 32 | 33 | 34 | 35
| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |:-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |:-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| _0_ | _1_ | - | D1-A | D1-B | D1-C | D1-D | D1-E | D1-F | D1-G | D1-dp | LED-1 | LED-2 | LED-3 | LED-4 | LED-5 | LED-6 | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - |
  
