typedef union
{
    struct
    {
        uint16_t tid;
        uint16_t localTid;
        Link queueLink;

        State state;
        uint16_t waitingFor;
        uint8_t waitingIrq;
        List waitingList;

        Process* process;
        Link processLink;
    };
    struct
    {
        uint8_t kernelStack[PAGE_SIZE - sizeof(Context)];
        Context context;
    };
} Thread;
