ENTRY(_start)
SECTIONS
{
    . = 0x0;
    .text : { *(.init) *(.text) }
    .rodata : { *(.rodata) }
    .data : { *(.data) }
}
