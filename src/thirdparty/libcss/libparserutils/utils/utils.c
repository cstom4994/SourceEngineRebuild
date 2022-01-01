/*
 * This file is part of LibParserUtils.
 * Licensed under the MIT License,
 *                http://www.opensource.org/licenses/mit-license.php
 * Copyright 2008 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include <string.h>

#include <thirdparty/libcss/libparserutils/utils/buffer.h>

#define DEFAULT_SIZE (4096)

 /**
  * Create a memory buffer
  *
  * \param buffer  Pointer to location to receive memory buffer
  * \return PARSERUTILS_OK on success,
  *         PARSERUTILS_BADPARM on bad parameters,
  *         PARSERUTILS_NOMEM on memory exhausion
  */
parserutils_error parserutils_buffer_create(parserutils_buffer** buffer)
{
    parserutils_buffer* b;

    if (buffer == NULL)
        return PARSERUTILS_BADPARM;

    b = malloc(sizeof(parserutils_buffer));
    if (b == NULL)
        return PARSERUTILS_NOMEM;

    b->data = malloc(DEFAULT_SIZE);
    if (b->data == NULL) {
        free(b);
        return PARSERUTILS_NOMEM;
    }

    b->length = 0;
    b->allocated = DEFAULT_SIZE;

    *buffer = b;

    return PARSERUTILS_OK;
}

/**
 * Destroy a memory buffer
 *
 * \param buffer  The buffer to destroy
 * \return PARSERUTILS_OK on success, appropriate error otherwise
 */
parserutils_error parserutils_buffer_destroy(parserutils_buffer* buffer)
{
    if (buffer == NULL)
        return PARSERUTILS_BADPARM;

    free(buffer->data);
    free(buffer);

    return PARSERUTILS_OK;
}

/**
 * Append data to a memory buffer
 *
 * \param buffer  The buffer to append to
 * \param data    The data to append
 * \param len     The length, in bytes, of the data to append
 * \return PARSERUTILS_OK on success, appropriate error otherwise.
 */
parserutils_error parserutils_buffer_append(parserutils_buffer* buffer,
    const uint8_t* data, size_t len)
{
    while (len >= buffer->allocated - buffer->length) {
        parserutils_error error = parserutils_buffer_grow(buffer);
        if (error != PARSERUTILS_OK)
            return error;
    }

    memcpy(buffer->data + buffer->length, data, len);

    buffer->length += len;

    return PARSERUTILS_OK;
}

/**
 * Insert data into a memory buffer
 *
 * \param buffer  The buffer to insert into
 * \param offset  The offset into the buffer to insert at
 * \param data    The data to insert
 * \param len     The length, in bytes, of the data to insert
 * \return PARSERUTILS_OK on success, appropriate error otherwise
 */
parserutils_error parserutils_buffer_insert(parserutils_buffer* buffer,
    size_t offset, const uint8_t* data, size_t len)
{
    if (offset > buffer->length)
        return PARSERUTILS_BADPARM;

    if (offset == buffer->length)
        return parserutils_buffer_append(buffer, data, len);

    while (len >= buffer->allocated - buffer->length) {
        parserutils_error error = parserutils_buffer_grow(buffer);
        if (error != PARSERUTILS_OK)
            return error;
    }

    memmove(buffer->data + offset + len,
        buffer->data + offset, buffer->length - offset);

    memcpy(buffer->data + offset, data, len);

    buffer->length += len;

    return PARSERUTILS_OK;
}

/**
 * Discard a section of a memory buffer
 *
 * \param buffer  The buffer to discard data from
 * \param offset  The offset into the buffer of the start of the section
 * \param len     The number of bytes to discard
 * \return PARSERUTILS_OK on success, appropriate error otherwise.
 */
parserutils_error parserutils_buffer_discard(parserutils_buffer* buffer,
    size_t offset, size_t len)
{
    if (offset >= buffer->length || offset + len > buffer->length)
        return PARSERUTILS_BADPARM;

    memmove(buffer->data + offset, buffer->data + offset + len,
        buffer->length - (len + offset));

    buffer->length -= len;

    return PARSERUTILS_OK;
}

/**
 * Extend the amount of space allocated for a memory buffer
 *
 * \param buffer  The buffer to extend
 * \return PARSERUTILS_OK on success, appropriate error otherwise.
 */
parserutils_error parserutils_buffer_grow(parserutils_buffer* buffer)
{
    uint8_t* temp = realloc(buffer->data, buffer->allocated * 2);
    if (temp == NULL)
        return PARSERUTILS_NOMEM;

    buffer->data = temp;
    buffer->allocated *= 2;

    return PARSERUTILS_OK;
}

parserutils_error parserutils_buffer_randomise(parserutils_buffer* buffer)
{
#ifndef NDEBUG
    uint8_t* temp;
#endif

    if (buffer == NULL)
        return PARSERUTILS_BADPARM;

#ifndef NDEBUG
    temp = malloc(buffer->allocated);
    if (temp == NULL)
        return PARSERUTILS_NOMEM;

    memcpy(temp, buffer->data, buffer->length);

    memset(buffer->data, 0xff, buffer->length);

    /* Leak the buffer's current data, so we don't reuse it */
    /* buffer->alloc(buffer->data, 0, buffer->pw); */

    buffer->data = temp;
#endif


    return PARSERUTILS_OK;
}




/*
 * This file is part of LibParserUtils.
 * Licensed under the MIT License,
 *                http://www.opensource.org/licenses/mit-license.php
 * Copyright 2007 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include <string.h>

#include <thirdparty/libcss/libparserutils/errors.h>

 /**
  * Convert a parserutils error code to a string
  *
  * \param error  The error code to convert
  * \return Pointer to string representation of error, or NULL if unknown.
  */
const char* parserutils_error_to_string(parserutils_error error)
{
    const char* result = NULL;

    switch (error) {
    case PARSERUTILS_OK:
        result = "No error";
        break;
    case PARSERUTILS_NOMEM:
        result = "Insufficient memory";
        break;
    case PARSERUTILS_BADPARM:
        result = "Bad parameter";
        break;
    case PARSERUTILS_INVALID:
        result = "Invalid input";
        break;
    case PARSERUTILS_FILENOTFOUND:
        result = "File not found";
        break;
    case PARSERUTILS_NEEDDATA:
        result = "Insufficient data";
        break;
    case PARSERUTILS_BADENCODING:
        result = "Unsupported encoding";
        break;
    case PARSERUTILS_EOF:
        result = "EOF";
        break;
    }

    return result;
}

/**
 * Convert a string representation of an error name to a parserutils error code
 *
 * \param str  String containing error name
 * \param len  Length of string (bytes)
 * \return Error code, or PARSERUTILS_OK if unknown
 */
parserutils_error parserutils_error_from_string(const char* str, size_t len)
{
    if (strncmp(str, "PARSERUTILS_OK", len) == 0) {
        return PARSERUTILS_OK;
    }
    else if (strncmp(str, "PARSERUTILS_NOMEM", len) == 0) {
        return PARSERUTILS_NOMEM;
    }
    else if (strncmp(str, "PARSERUTILS_BADPARM", len) == 0) {
        return PARSERUTILS_BADPARM;
    }
    else if (strncmp(str, "PARSERUTILS_INVALID", len) == 0) {
        return PARSERUTILS_INVALID;
    }
    else if (strncmp(str, "PARSERUTILS_FILENOTFOUND", len) == 0) {
        return PARSERUTILS_FILENOTFOUND;
    }
    else if (strncmp(str, "PARSERUTILS_NEEDDATA", len) == 0) {
        return PARSERUTILS_NEEDDATA;
    }
    else if (strncmp(str, "PARSERUTILS_BADENCODING", len) == 0) {
        return PARSERUTILS_BADENCODING;
    }
    else if (strncmp(str, "PARSERUTILS_EOF", len) == 0) {
        return PARSERUTILS_EOF;
    }

    return PARSERUTILS_OK;
}


/*
 * This file is part of LibParserUtils.
 * Licensed under the MIT License,
 *                http://www.opensource.org/licenses/mit-license.php
 * Copyright 2008 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include <inttypes.h>
#include <string.h>

#include <thirdparty/libcss/libparserutils/utils/vector.h>

 /**
  * Vector object
  */
struct parserutils_vector
{
    size_t item_size;		/**< Size of an item in the vector */
    size_t chunk_size;		/**< Size of a vector chunk */
    size_t items_allocated;		/**< Number of slots allocated */
    int32_t current_item;		/**< Index of current item */
    void* items;			/**< Items in vector */
};

/**
 * Create a vector
 *
 * \param item_size   Length, in bytes, of an item in the vector
 * \param chunk_size  Number of vector slots in a chunk
 * \param vector      Pointer to location to receive vector instance
 * \return PARSERUTILS_OK on success,
 *         PARSERUTILS_BADPARM on bad parameters,
 *         PARSERUTILS_NOMEM on memory exhaustion
 */
parserutils_error parserutils_vector_create(size_t item_size,
    size_t chunk_size, parserutils_vector** vector)
{
    parserutils_vector* v;

    if (item_size == 0 || chunk_size == 0 || vector == NULL)
        return PARSERUTILS_BADPARM;

    v = malloc(sizeof(parserutils_vector));
    if (v == NULL)
        return PARSERUTILS_NOMEM;

    v->items = malloc(item_size * chunk_size);
    if (v->items == NULL) {
        free(v);
        return PARSERUTILS_NOMEM;
    }

    v->item_size = item_size;
    v->chunk_size = chunk_size;
    v->items_allocated = chunk_size;
    v->current_item = -1;

    *vector = v;

    return PARSERUTILS_OK;
}

/**
 * Destroy a vector instance
 *
 * \param vector  The vector to destroy
 * \return PARSERUTILS_OK on success, appropriate error otherwise.
 */
parserutils_error parserutils_vector_destroy(parserutils_vector* vector)
{
    if (vector == NULL)
        return PARSERUTILS_BADPARM;

    free(vector->items);
    free(vector);

    return PARSERUTILS_OK;
}

/**
 * Append an item to the vector
 *
 * \param vector  The vector to append to
 * \param item    The item to append
 * \return PARSERUTILS_OK on success, appropriate error otherwise
 */
parserutils_error parserutils_vector_append(parserutils_vector* vector,
    void* item)
{
    int32_t slot;

    if (vector == NULL || item == NULL)
        return PARSERUTILS_BADPARM;

    /* Ensure we'll get a valid slot */
    if (vector->current_item < -1 || vector->current_item == INT32_MAX)
        return PARSERUTILS_INVALID;

    slot = vector->current_item + 1;

    if ((size_t)slot >= vector->items_allocated) {
        void* temp = realloc(vector->items,
            (vector->items_allocated + vector->chunk_size) *
            vector->item_size);
        if (temp == NULL)
            return PARSERUTILS_NOMEM;

        vector->items = temp;
        vector->items_allocated += vector->chunk_size;
    }

    memcpy((uint8_t*)vector->items + (slot * vector->item_size),
        item, vector->item_size);
    vector->current_item = slot;

    return PARSERUTILS_OK;
}

/**
 * Clear a vector
 *
 * \param vector  The vector to clear
 * \return PARSERUTILS_OK on success, appropriate error otherwise.
 */
parserutils_error parserutils_vector_clear(parserutils_vector* vector)
{
    if (vector == NULL)
        return PARSERUTILS_BADPARM;

    if (vector->current_item < 0)
        return PARSERUTILS_INVALID;

    vector->current_item = -1;

    return PARSERUTILS_OK;
}

/**
 * Remove the last item from a vector
 *
 * \param vector  The vector to remove from
 * \return PARSERUTILS_OK on success, appropriate error otherwise
 */
parserutils_error parserutils_vector_remove_last(parserutils_vector* vector)
{
    if (vector == NULL)
        return PARSERUTILS_BADPARM;

    if (vector->current_item < 0)
        return PARSERUTILS_INVALID;

    vector->current_item--;

    return PARSERUTILS_OK;
}

/**
 * Acquire the length (in items) of the vector.
 *
 * \param vector  The vector to interrogate.
 * \param length  Pointer to location to receive length information.
 * \return PARSERUTILS_OK on success, appropriate error otherwise
 */
parserutils_error parserutils_vector_get_length(parserutils_vector* vector,
    size_t* length)
{
    if (vector == NULL)
        return PARSERUTILS_BADPARM;

    if (length == NULL)
        return PARSERUTILS_BADPARM;

    *length = vector->current_item + 1;

    return PARSERUTILS_OK;
}

/**
 * Iterate over a vector
 *
 * \param vector  The vector to iterate over
 * \param ctx     Pointer to an integer for the iterator to use as context.
 * \return Pointer to current item, or NULL if no more
 *
 * \note The value pointed to by \a ctx must be zero to begin the iteration.
 */
const void* parserutils_vector_iterate(const parserutils_vector* vector,
    int32_t* ctx)
{
    void* item;

    if (vector == NULL || ctx == NULL || vector->current_item < 0)
        return NULL;

    if ((*ctx) > vector->current_item)
        return NULL;

    item = (uint8_t*)vector->items + ((*ctx) * vector->item_size);

    (*ctx)++;

    return item;
}

/**
 * Peek at an item in a vector
 *
 * \param vector  The vector to iterate over
 * \param ctx     Integer for the iterator to use as context.
 * \return Pointer to item, or NULL if no more
 */
const void* parserutils_vector_peek(const parserutils_vector* vector,
    int32_t ctx)
{
    if (vector == NULL || vector->current_item < 0)
        return NULL;

    if (ctx > vector->current_item)
        return NULL;

    return (uint8_t*)vector->items + (ctx * vector->item_size);
}


#ifndef NDEBUG
#include <stdio.h>

extern void parserutils_vector_dump(parserutils_vector* vector,
    const char* prefix, void (*printer)(void* item));

void parserutils_vector_dump(parserutils_vector* vector, const char* prefix,
    void (*printer)(void* item))
{
    int32_t i;

    if (vector == NULL || printer == NULL)
        return;

    for (i = 0; i <= vector->current_item; i++) {
        printf("%s %d: ", prefix != NULL ? prefix : "", i);
        printer((uint8_t*)vector->items + (i * vector->item_size));
        printf("\n");
    }
}

#endif




/*
 * This file is part of LibParserUtils.
 * Licensed under the MIT License,
 *                http://www.opensource.org/licenses/mit-license.php
 * Copyright 2008 John-Mark Bell <jmb@netsurf-browser.org>
 */

#include <inttypes.h>
#include <string.h>

#include <thirdparty/libcss/libparserutils/utils/stack.h>

/**
 * Stack object
 */
struct parserutils_stack
{
	size_t item_size;		/**< Size of an item in the stack */
	size_t chunk_size;		/**< Size of a stack chunk */
	size_t items_allocated;		/**< Number of slots allocated */
	int32_t current_item;		/**< Index of current item */
	void *items;			/**< Items in stack */
};

/**
 * Create a stack
 *
 * \param item_size   Length, in bytes, of an item in the stack
 * \param chunk_size  Number of stack slots in a chunk
 * \param stack       Pointer to location to receive stack instance
 * \return PARSERUTILS_OK on success,
 *         PARSERUTILS_BADPARM on bad parameters
 *         PARSERUTILS_NOMEM on memory exhaustion
 */
parserutils_error parserutils_stack_create(size_t item_size, size_t chunk_size,
		parserutils_stack **stack)
{
	parserutils_stack *s;

	if (item_size == 0 || chunk_size == 0 || stack == NULL)
		return PARSERUTILS_BADPARM;

	s = malloc(sizeof(parserutils_stack));
	if (s == NULL)
		return PARSERUTILS_NOMEM;

	s->items = malloc(item_size * chunk_size);
	if (s->items == NULL) {
		free(s);
		return PARSERUTILS_NOMEM;
	}

	s->item_size = item_size;
	s->chunk_size = chunk_size;
	s->items_allocated = chunk_size;
	s->current_item = -1;

	*stack = s;

	return PARSERUTILS_OK;
}

/**
 * Destroy a stack instance
 *
 * \param stack  The stack to destroy
 * \return PARSERUTILS_OK on success, appropriate error otherwise.
 */
parserutils_error parserutils_stack_destroy(parserutils_stack *stack)
{
	if (stack == NULL)
		return PARSERUTILS_BADPARM;

	free(stack->items);
	free(stack);

	return PARSERUTILS_OK;
}

/**
 * Push an item onto the stack
 *
 * \param stack  The stack to push onto
 * \param item   The item to push
 * \return PARSERUTILS_OK on success, appropriate error otherwise
 */
parserutils_error parserutils_stack_push(parserutils_stack *stack, 
		const void *item)
{
	int32_t slot;

	if (stack == NULL || item == NULL)
		return PARSERUTILS_BADPARM;

	/* Ensure we'll get a valid slot */
	if (stack->current_item < -1 || stack->current_item == INT32_MAX)
		return PARSERUTILS_INVALID;

	slot = stack->current_item + 1;

	if ((size_t) slot >= stack->items_allocated) {
		void *temp = realloc(stack->items,
				(stack->items_allocated + stack->chunk_size) *
				stack->item_size);
		if (temp == NULL)
			return PARSERUTILS_NOMEM;

		stack->items = temp;
		stack->items_allocated += stack->chunk_size;
	}

	memcpy((uint8_t *) stack->items + (slot * stack->item_size), 
			item, stack->item_size);
	stack->current_item = slot;

	return PARSERUTILS_OK;
}

/**
 * Pop an item off a stack
 *
 * \param stack  The stack to pop from
 * \param item   Pointer to location to receive popped item, or NULL
 * \return PARSERUTILS_OK on success, appropriate error otherwise.
 */
parserutils_error parserutils_stack_pop(parserutils_stack *stack, void *item)
{
	if (stack == NULL)
		return PARSERUTILS_BADPARM;

	if (stack->current_item < 0)
		return PARSERUTILS_INVALID;

	if (item != NULL) {
		memcpy(item, (uint8_t *) stack->items + 
				(stack->current_item * stack->item_size), 
				stack->item_size);
	}

	stack->current_item -= 1;

	return PARSERUTILS_OK;
}

/**
 * Retrieve a pointer to the current item on the stack
 *
 * \param stack  The stack to inspect
 * \return Pointer to item on stack, or NULL if none
 */
void *parserutils_stack_get_current(parserutils_stack *stack)
{
	if (stack == NULL || stack->current_item < 0)
		return NULL;

	return (uint8_t *) stack->items + 
			(stack->current_item * stack->item_size);
}

#ifndef NDEBUG
#include <stdio.h>

extern void parserutils_stack_dump(parserutils_stack *stack, const char *prefix,
		void (*printer)(void *item));

void parserutils_stack_dump(parserutils_stack *stack, const char *prefix,
		void (*printer)(void *item))
{
	int32_t i;

	if (stack == NULL || printer == NULL)
		return;

	for (i = 0; i <= stack->current_item; i++) {
		printf("%s %d: ", prefix != NULL ? prefix : "", i);
		printer((uint8_t *) stack->items + (i * stack->item_size));
		printf("\n");
	}
}

#endif

