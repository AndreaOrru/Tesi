void map(void* vAddr, void* pAddr, uint16_t flags)
{
  PEntry* pdEntry = PD_ENTRY(vAddr);
  PEntry* ptEntry = PT_ENTRY(vAddr);

  if (! *pdEntry)
  {
    *pdEntry = (PEntry)frame_alloc() | flags | PAGE_PRESENT | PAGE_WRITE | PAGE_USER;
    invlpg(ptEntry);

    memset(PAGE_BASE(ptEntry), 0, PAGE_SIZE);
  }

  if (pAddr == NULL)
  {
    if (*ptEntry & PAGE_ALLOCATED)
      *ptEntry = (*ptEntry & ~0xFFF)   | flags | PAGE_PRESENT | PAGE_ALLOCATED;
    else
      *ptEntry = (PEntry)frame_alloc() | flags | PAGE_PRESENT | PAGE_ALLOCATED;
  }
  else
  {
    if (*ptEntry & PAGE_ALLOCATED)
      frame_free((void*) *ptEntry);

    *ptEntry = (PEntry)PAGE_BASE(pAddr) | flags | PAGE_PRESENT;
  }

  invlpg(vAddr);
}
