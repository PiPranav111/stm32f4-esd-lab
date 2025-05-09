# 🚀 STM32F446RE Embedded Systems Lab – Baremetal & HAL Projects

Welcome to my final-semester academic project portfolio!  
This repository contains hands-on embedded systems experiments developed on the **STM32F446RE Nucleo board** as part of the **Embedded System Design Lab [404196]** at PICT, Pune.

Each experiment is implemented using **both**:
- 🛠️ **Baremetal (Register-Level) Programming**
- 🔧 **HAL (Hardware Abstraction Layer) Libraries**

---

## 📚 About the Lab

> The objective of this lab was to build a strong foundation in embedded systems programming, including real-time control, peripheral interfacing, and multitasking.

- 🔌 GPIO, Timers, UART, ADC, and LCD Interfacing
- ⚙️ Hands-on with low-level ARM Cortex-M4 registers
- 🌐 UART communication with external devices
- ⏱️ FreeRTOS basics for task scheduling
- 🔁 Delay, Interrupt, and Polling mechanisms

---

## 🧪 Experiments Included

| No. | Title | Baremetal | HAL |
|-----|-------------------------------|:---------:|:----:|
| 1   | LED Toggle using Delay        | ✅        | ✅   |
| 2   | LED Chase using Delay         | ✅        | ✅   |
| 3   | Switch-controlled LED         | ✅        | ✅   |
| 4   | Switch-controlled LED Chase   | ✅        | ✅   |
| 5   | LCD: "WELCOME" & "PICT"       | ✅        | ✅   |
| 6   | LCD: "PICT" & "ESD"           | ✅        | ✅   |
| 7   | UART TxRx: "SPPU"             | ✅        | ✅   |
| 8   | UART TxRx: "Hello"            | ✅        | ✅   |
| 9   | LED Toggle with Timer         | ✅        | ✅   |
| 10  | Timer-based LED Blink         | ✅        | ✅   |
| 11  | ADC Read using HAL            | ✅        | ✅   |
| 12  | ADC Read (Alternate)          | ✅        | ✅   |
| 13  | FreeRTOS Task Switching       | ❌        | ✅   |
| 14  | FreeRTOS Delay Tasks          | ❌        | ✅   |

> 🔁 Some experiments are intentionally repeated with variations in logic or approach.

---

## 📁 Repository Structure

```bash
stm32_workspace/
├── Exp01_LED_Toggle_Delay/
│   ├── baremetal/
│   └── hal/
│       └── .ioc, Core/, Drivers/
├── Exp02_LED_Chasing/
├── ...
└── Exp14_FreeRTOS_Tasks/
