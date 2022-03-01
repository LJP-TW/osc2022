_stack_top = 0x400000;

SECTIONS
{
  . = 0x80000;
  
  .text.boot : {
    *(.text.boot)
  }

  .text : {
    *(.text)
  }

  .rodata : {
    *(.rodata)
  }

  .data : {
    *(.data)
  }

  . = ALIGN(0x8);

  _sbss = .;
  .bss : {
    *(.bss*)
  }
  _ebss = .;
  
  . = _stack_top;
  _sstack = .;
}