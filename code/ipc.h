typedef struct
{
    struct
    {
        uint16_t pid;
        uint16_t tid;
        uint32_t n;
    } tag;
    uint32_t reg[64];
} __attribute__((packed)) MsgBox;
