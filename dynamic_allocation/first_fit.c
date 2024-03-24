#include <stdio.h>

void worstfit(int blocks, int processes, int blockSize[], int processSize[])
{
    int allocated_block[processes];

    int na = 0;
    int allocated = 0;

    for (int i = 0; i < processes; i++)
    {
        for (int j = 0; j < blocks; j++)
        {
            // Check for space with sufficient amount of memory space left
            if (processSize[i] < blockSize[j])
            {
                allocated = 1;
                blockSize[j] = blockSize[j] - processSize[j];

                allocated_block[i] = j + 1;
                break;
            }

            if (allocated = 0)
            {
                allocated_block[i] = -1;
            }
        }

        // reset variables
        allocated = 0;
    }

    printf("Process_no  Process_size  Block\n");
    for (int i = 0; i < processes; i++)
    {
        printf("%d   %d   %d\n", i + 1, processSize[i], allocated_block[i]);
    }
}

int main()
{
    int blockSize[] = {30, 5, 10};
    int processSize[] = {10, 6, 9};
    int blocks = sizeof(blockSize) / sizeof(blockSize[0]);
    int processes = sizeof(processSize) / sizeof(processSize[0]);

    worstfit(blocks, processes, blockSize, processSize);
}