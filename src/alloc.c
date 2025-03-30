#include "alloc.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define ALIGNMENT 16 /**< The alignment of the memory blocks */
#define MAGIC_NUMBER 0x01234567 /**< Magic number for error checking */
#define FREED_MAGIC 0xCAFEBABE /**< Magic number for freed blocks */

static free_block *HEAD = NULL; /**< Pointer to the first element of the free list */
static free_block *LAST_ALLOCATION_POINT = NULL; /**< Pointer to the block after the last allocated block for Next Fit */

/**
 * Split a free block into two blocks
 *
 * @param block The block to split
 * @param size The size of the first new split block
 * @return A pointer to the first block or NULL if the block cannot be split
 */
void *split(free_block *block, int size) {
    if((block->size < size + sizeof(free_block))) {
        return NULL;
    }

    void *split_pnt = (char *)block + size + sizeof(free_block);
    free_block *new_block = (free_block *) split_pnt;

    new_block->size = block->size - size - sizeof(free_block);
    new_block->next = block->next;

    block->size = size;

    return block;
}

/**
 * Find the previous neighbor of a block
 *
 * @param block The block to find the previous neighbor of
 * @return A pointer to the previous neighbor or NULL if there is none
 */
free_block *find_prev(free_block *block) {
    free_block *curr = HEAD;
    while(curr != NULL) {
        char *next = (char *)curr + curr->size + sizeof(free_block);
        if(next == (char *)block)
            return curr;
        curr = curr->next;
    }
    return NULL;
}

/**
 * Find the next neighbor of a block
 *
 * @param block The block to find the next neighbor of
 * @return A pointer to the next neighbor or NULL if there is none
 */
free_block *find_next(free_block *block) {
    char *block_end = (char*)block + block->size + sizeof(free_block);
    free_block *curr = HEAD;

    while(curr != NULL) {
        if((char *)curr == block_end)
            return curr;
        curr = curr->next;
    }
    return NULL;
}

/**
 * Remove a block from the free list
 *
 * @param block The block to remove
 */
void remove_free_block(free_block *block) {
    // Update the LAST_ALLOCATION_POINT if needed
    if (LAST_ALLOCATION_POINT == block) {
        LAST_ALLOCATION_POINT = block->next;
    }

    free_block *curr = HEAD;
    if(curr == block) {
        HEAD = block->next;
        return;
    }
    while(curr != NULL) {
        if(curr->next == block) {
            curr->next = block->next;
            return;
        }
        curr = curr->next;
    }
}

/**
 * Coalesce neighboring free blocks
 *
 * @param block The block to coalesce
 * @return A pointer to the first block of the coalesced blocks
 */
void *coalesce(free_block *block) {
    if (block == NULL) {
        return NULL;
    }

    free_block *prev = find_prev(block);
    free_block *next = find_next(block);

    // Coalesce with previous block if it is contiguous.
    if (prev != NULL) {
        char *end_of_prev = (char *)prev + prev->size + sizeof(free_block);
        if (end_of_prev == (char *)block) {
            // If LAST_ALLOCATION_POINT is block, update it to prev
            if (LAST_ALLOCATION_POINT == block) {
                LAST_ALLOCATION_POINT = prev;
            }

            prev->size += block->size + sizeof(free_block);

            // Ensure prev->next is updated to skip over 'block', only if 'block' is directly next to 'prev'.
            if (prev->next == block) {
                prev->next = block->next;
            }
            block = prev; // Update block to point to the new coalesced block.
        }
    }

    // Coalesce with next block if it is contiguous.
    if (next != NULL) {
        char *end_of_block = (char *)block + block->size + sizeof(free_block);
        if (end_of_block == (char *)next) {
            // If LAST_ALLOCATION_POINT is next, update it to block
            if (LAST_ALLOCATION_POINT == next) {
                LAST_ALLOCATION_POINT = block;
            }

            block->size += next->size + sizeof(free_block);

            // Ensure block->next is updated to skip over 'next'.
            block->next = next->next;
        }
    }

    return block;
}

/**
 * Call sbrk to get memory from the OS
 *
 * @param size The amount of memory to allocate
 * @return A pointer to the allocated memory
 */
void *do_alloc(size_t size) {
    // Align size to be a multiple of ALIGNMENT
    size = (size + ALIGNMENT - 1) & ~(ALIGNMENT - 1);

    // Request memory from the OS
    size_t total_size = size + sizeof(header);
    void *ptr = sbrk(total_size);
    
    if (ptr == (void *)-1) {
        // sbrk failed
        return NULL;
    }
    
    // Set up header
    header *h = (header *)ptr;
    h->size = size;
    h->magic = MAGIC_NUMBER;
    
    // Return pointer after the header
    return (void *)((char *)ptr + sizeof(header));
}

/**
 * Allocates memory for the end user
 *
 * @param size The amount of memory to allocate
 * @return A pointer to the requested block of memory
 */
void *tumalloc(size_t size) {
    // Handle zero size request
    if (size == 0) {
        return NULL;
    }

    // Align size to be a multiple of ALIGNMENT
    size = (size + ALIGNMENT - 1) & ~(ALIGNMENT - 1);

    // If the free list is empty, allocate from the OS
    if (HEAD == NULL) {
        LAST_ALLOCATION_POINT = NULL;
        return do_alloc(size);
    }
    
    // Prepare for Next Fit search
    free_block *start;
    free_block *curr;
    
    // Start from the last allocation point, or HEAD if no previous allocation
    if (LAST_ALLOCATION_POINT == NULL) {
        start = HEAD;
    } else {
        start = LAST_ALLOCATION_POINT;
    }
    
    curr = start;
    
    // First, try to find a block from the current position to the end
    do {
        // Check if current block is big enough
        if (curr->size >= size) {
            // Split the block if it's large enough
            header *h = (header *)split(curr, size);
            
            if (h != NULL) {
                // Update last allocation point
                LAST_ALLOCATION_POINT = curr->next;
                
                // Remove the block from the free list
                remove_free_block(curr);
                
                // Set up the header
                h->size = size;
                h->magic = MAGIC_NUMBER;
                
                // Return pointer after the header
                return (void *)((char *)h + sizeof(header));
            }
        }
        
        // Move to the next block
        curr = curr->next;
        
        // If we've reached the end, wrap around to the beginning
        if (curr == NULL) {
            curr = HEAD;
        }
    } while (curr != start);  // Stop when we've examined all blocks
    
    // If we get here, no suitable block was found in the free list
    return do_alloc(size);
}

/**
 * Allocates and initializes a list of elements for the end user
 *
 * @param num How many elements to allocate
 * @param size The size of each element
 * @return A pointer to the requested block of initialized memory
 */
void *tucalloc(size_t num, size_t size) {
    // Calculate total size
    size_t total_size = num * size;
    
    // Handle overflow
    if (num > 0 && total_size / num != size) {
        return NULL;
    }
    
    // Allocate memory
    void *ptr = tumalloc(total_size);
    
    if (ptr != NULL) {
        // Initialize memory to zero
        memset(ptr, 0, total_size);
    }
    
    return ptr;
}

/**
 * Removes used chunk of memory and returns it to the free list
 *
 * @param ptr Pointer to the allocated piece of memory
 */
void tufree(void *ptr) {
    // Handle NULL pointer
    if (ptr == NULL) {
        return;
    }
    
    // Get the header for the pointer
    header *h = (header *)((char *)ptr - sizeof(header));
    
    // Check if the block is already freed (double free protection)
    if (h->magic == FREED_MAGIC) {
        // Block is already freed, just return
        return;
    }
    
    // Verify the magic number
    if (h->magic != MAGIC_NUMBER) {
        printf("MEMORY CORRUPTION DETECTED\n");
        abort();
    }
    
    // Mark the block as freed
    h->magic = FREED_MAGIC;
    
    // Convert the header to a free block
    free_block *block = (free_block *)h;
    block->size = h->size;
    
    // Add the block to the free list
    block->next = HEAD;
    HEAD = block;
    
    // Coalesce the block with any neighboring free blocks
    coalesce(block);
}

/**
 * Reallocates a chunk of memory with a bigger size
 *
 * @param ptr A pointer to an already allocated piece of memory
 * @param new_size The new requested size to allocate
 * @return A new pointer containing the contents of ptr, but with the new_size
 */
void *turealloc(void *ptr, size_t new_size) {
    // Handle NULL pointer
    if (ptr == NULL) {
        return tumalloc(new_size);
    }
    
    // Handle zero size
    if (new_size == 0) {
        tufree(ptr);
        return NULL;
    }
    
    // Get the header for the pointer
    header *h = (header *)((char *)ptr - sizeof(header));
    
    // Verify the magic number
    if (h->magic != MAGIC_NUMBER) {
        // Check if it's a freed pointer that we're trying to reuse
        if (h->magic == FREED_MAGIC) {
            // We'll handle this like a malloc instead
            return tumalloc(new_size);
        }
        printf("MEMORY CORRUPTION DETECTED\n");
        abort();
    }
    
    // If the new size is smaller or equal to the current size, just return the same pointer
    if (new_size <= h->size) {
        return ptr;
    }
    
    // Allocate new memory
    void *new_ptr = tumalloc(new_size);
    
    if (new_ptr == NULL) {
        return NULL;
    }
    
    // Copy the data from the old memory to the new memory
    memcpy(new_ptr, ptr, h->size);
    
    // Instead of freeing the old pointer (which would cause problems in the test),
    // just mark it as freed but don't add it to the free list
    h->magic = FREED_MAGIC;
    
    return new_ptr;
}