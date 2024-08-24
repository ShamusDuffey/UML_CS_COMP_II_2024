#define _CRT_SECURE_NO_WARNINGS
typedef void* QUEUE;
typedef enum status { FAILURE, SUCCESS } STATUS;
QUEUE queueInit(void);
STATUS queueInsert(QUEUE, int input);
STATUS queueService(QUEUE);
STATUS queueDestroy(QUEUE* phQueue);
int getFront(QUEUE);
int getSize(QUEUE);