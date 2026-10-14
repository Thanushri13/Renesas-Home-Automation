# Renesas Home Automation

A bare-metal embedded systems project developed for the **Renesas RA6E2 BGK board**, demonstrating hardware-level clock configuration, GPT timer operation, GPIO control, and staircase lighting logic using direct register access in C.

## 📌 Project Overview

This project explores low-level peripheral configuration on the Renesas RA6E2 microcontroller without relying on high-level driver APIs for the main application logic. It uses direct memory-mapped register access to configure system clocks, control GPIO pins, and implement timer-based and switch-controlled LED operations.

## 🎯 Objectives

- Configure the High-Speed On-Chip Oscillator (HOCO).
- Configure clock dividers and system clock selection.
- Control GPIO peripherals through direct register access.
- Generate periodic timer events using General PWM Timer (GPT0).
- Implement staircase lighting logic using two switches and an LED.
- Understand bare-metal embedded C programming and peripheral registers.

## 🛠️ Hardware and Software Requirements

| Component | Description |
|---|---|
| Microcontroller board | Renesas RA6E2 BGK |
| Programming language | Embedded C |
| Development environment | Renesas QC Studio |
| Hardware peripherals | GPIO, GPT0, HOCO |
| Programming approach | Bare-metal register-level programming |
| Header dependency | `hal_data.h` |

## 📂 Project Structure

```text
Renesas-Home-Automation/
├── BGK-RA6E2 clock configuration.c
├── Staircase implementation using baremetal.c
└── README.md
```

## ⚙️ Implementation Details

### 1. Clock Configuration and Timer-Based LED Control

**File:** `BGK-RA6E2 clock configuration.c`

This program configures the microcontroller's clock system and uses GPT0 to generate periodic timer events.

**Key features:**
- Enables and configures the HOCO clock source.
- Configures the system clock selection and clock dividers.
- Enables the GPT0 peripheral module.
- Configures the timer period and prescaler.
- Uses the GPT0 status flag to detect timer events.
- Toggles the LED through direct GPIO register access.

**Timer configuration:**

| Parameter | Value |
|---|---:|
| PCLKD frequency | 16 MHz |
| Prescaler | 32 |
| Timer clock | 500 kHz |
| Timer period register | 499,999 |
| Intended timer interval | 1 second |

The program counts timer events and toggles the LED after 60 events. With the intended one-second timer interval, the LED changes state approximately every 60 seconds.

### 2. Staircase Lighting Using Bare-Metal GPIO

**File:** `Staircase implementation using baremetal.c`

This program implements staircase lighting logic using two switches and one LED. It reads the switch inputs, evaluates their logical XOR, and controls the LED accordingly.

**Key features:**
- Configures the HOCO clock and system clock settings.
- Configures GPIO pin functions and directions.
- Reads the two switch inputs using the GPIO input register.
- Evaluates the logical XOR operation.
- Controls the LED using direct GPIO output register access.
- Continuously monitors switch states without using high-level GPIO APIs.

**GPIO configuration:**

| Signal | Pin | Function |
|---|---|---|
| SW1 | P105 | Switch input |
| LED | P104 | LED output |
| SW2 | P103 | Switch input |

**Logic table:**

| SW1 | SW2 | LED |
|---:|---:|---|
| 0 | 0 | OFF |
| 0 | 1 | ON |
| 1 | 0 | ON |
| 1 | 1 | OFF |

The LED turns ON when exactly one switch is active and turns OFF when both switches have the same logical state. This demonstrates XOR-based staircase lighting control.

*Note: The code interprets a low electrical input as an active switch. Actual switch behavior depends on the board wiring and input circuitry.*

## 🔬 Concepts Demonstrated

- Bare-metal embedded programming
- Memory-mapped I/O
- Microcontroller clock configuration
- HOCO oscillator operation
- GPT timer configuration
- GPIO input and output control
- Register-level peripheral access
- Bitwise operations and logical XOR
- Embedded C programming

## 🚀 Getting Started

1. Clone or download this repository.
2. Open the project in the compatible Renesas development environment.
3. Ensure the RA6E2 device configuration and `hal_data.h` are available.
4. Verify the target board's clock settings, peripheral configuration, and pin assignments.
5. Build the project and flash the firmware to the RA6E2 BGK board.
6. Test the timer-based LED behavior and staircase switch logic on the hardware.

📈 Learning Outcomes
This project provides practical experience with direct register manipulation, timer-based event handling, GPIO interfacing, and implementing simple automation logic on a Renesas RA6E2 microcontroller.

👩‍💻 Author
Thanushri13

Developed as an embedded systems learning project using bare-metal C on the Renesas RA6E2 platform.

GitHub: @Thanushri13

Developed as an embedded systems learning project using bare-metal C on the Renesas RA6E2 platform.
