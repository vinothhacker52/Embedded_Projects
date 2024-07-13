; LPC2129 Startup File
; Vector table and startup code

; Vector table
AREA RESET, CODE, READONLY
EXPORT __Vectors
__Vectors
    LDR     PC, Reset_Addr         ; Reset Handler
    LDR     PC, Undefined_Addr
    LDR     PC, SWI_Addr
    LDR     PC, Prefetch_Abort_Addr
    LDR     PC, Data_Abort_Addr
    NOP                             ; Reserved
    LDR     PC, IRQ_Addr            ; IRQ Handler
    LDR     PC, FIQ_Addr            ; FIQ Handler

Reset_Addr                  DCD     Reset_Handler
Undefined_Addr              DCD     Undefined_Handler
SWI_Addr                    DCD     SWI_Handler
Prefetch_Abort_Addr         DCD     Prefetch_Abort_Handler
Data_Abort_Addr             DCD     Data_Abort_Handler
IRQ_Addr                    DCD     IRQ_Handler
FIQ_Addr                    DCD     FIQ_Handler

; Reset Handler
Reset_Handler
    LDR     R0, =0xE002C010         ; GPIO PINSEL1
    LDR     R1, =0x00000000         ; P0.10 is GPIO
    STR     R1, [R0]

    LDR     R0, =0xE002C020         ; GPIO IO0PIN
    LDR     R1, =0x00000400         ; P0.10 is output high
    STR     R1, [R0]

    LDR     R0, =0xE002C014         ; GPIO IO0DIR
    LDR     R1, =0x00000400         ; P0.10 is output
    STR     R1, [R0]

    B       LED_Init                ; Jump to LED initialization

; LED Toggle with 75% duty cycle and 2Hz frequency
LED_Toggle
    LDR     R0, =0xE002C020         ; GPIO IO0PIN
    LDR     R1, [R0]
    EOR     R1, R1, #0x00000400     ; Toggle P0.10
    STR     R1, [R0]

    LDR     R0, =0xE002C020         ; GPIO IO0PIN
    LDR     R1, =0x00000400         ; P0.10 is output high
    STR     R1, [R0]

    LDR     R0, =0x2DC6C0            ; Delay value for 2Hz (adjust this value based on your clock configuration)
Delay_Loop
    SUBS    R0, R0, #1              ; Decrement R0
    BNE     Delay_Loop              ; Loop until R0 is zero

    B       LED_Toggle              ; Toggle LED again

; Configure LED GPIO pin
LED_Init
    LDR     R0, =0xE002C014         ; GPIO IO0DIR
    LDR     R1, =0x00000400         ; P0.10 is output
    STR     R1, [R0]

; End of startup code

; Handlers for unused interrupts
Undefined_Handler
    B       Undefined_Handler

SWI_Handler
    B       SWI_Handler

Prefetch_Abort_Handler
    B       Prefetch_Abort_Handler

Data_Abort_Handler
    B       Data_Abort_Handler

IRQ_Handler
    B       IRQ_Handler

FIQ_Handler
    B       FIQ_Handler

; End of startup.s
