/* kernel/src/linker.ld */
OUTPUT_FORMAT("") /* you need to paste elf32-i386, pei-i386 or something other, it depends on your device and architecture */
ENTRY(_start)
SECTIONS
{
  . = 0x400000;
  .text : { *(.text) }
  .data : { *(.data) }
  .bss  : { *(.bss) }
}
