static LIST(readyQueue);
static TLS* volatile* const TLSPtr = (TLS**)TLS_PTR;

static inline void switch_to(Thread* thread)
{
    if (thread->process->PD != read_cr3())
        write_cr3(thread->process->PD);

    *TLSPtr = (TLS*)USER_TLS + thread->localTid;
    set_kernel_stack(&thread->context + 1);
    set_context(&thread->context);
}

void schedule(void)
{
  retry:
    if (list_empty(&readyQueue))
        ERROR("No more threads to schedule.");

    Thread* new = list_item(list_pop(&readyQueue), Thread, queueLink);
    if (new->state == DYING)
    {
        unmap(new);
        goto retry;
    }

    list_append(&readyQueue, &new->queueLink);
    switch_to(scheduler_current());
}

void scheduler_init(void)
{
    map((void*)TLSPtr, NULL, PAGE_WRITE | PAGE_USER | PAGE_GLOBAL);

    irq_register(0, schedule);
}
