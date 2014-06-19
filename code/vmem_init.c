void vmem_init(void)
{
  PEntry* physPD = frame_alloc();
  memset(physPD, 0, PAGE_SIZE);

  physPD[0]    = (PEntry)0x000000 | PAGE_PRESENT | PAGE_WRITE | PAGE_4MB | PAGE_GLOBAL;
  physPD[1023] = (PEntry)physPD   | PAGE_PRESENT | PAGE_WRITE;

  interrupt_register(14, page_fault);
  enable_paging(physPD);
}
