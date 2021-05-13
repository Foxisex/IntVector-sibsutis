#include "heap.h"

struct heap *heap_create(int maxsize)
{
	struct heap *h;
	h = malloc(sizeof(*h));
	if (h != NULL) {
		h->maxsize = maxsize;
		h->nnodes = 0;
		h->helper = malloc(sizeof(int) * (maxsize + 1));
		h->nodes = malloc(sizeof(*h->nodes) * (maxsize + 1));
		if (h->nodes == NULL) {
			free(h);
			return NULL;
		}
	}
	return h;
}

void heap_free(struct heap *h)
{
	free(h->nodes);
	free(h->helper);
	free(h);
}

void heap_swap(struct heapnode *a, struct heapnode *b, struct heap *q)
{
	struct heapnode temp = *a;

	*a = *b;
	*b = temp;


	int tmp = q->helper[a->value];
	q->helper[a->value] = q->helper[b->value];
	q->helper[b->value] = tmp;
}

struct heapnode *heap_min(struct heap *h)
{
	if (h->nnodes == 0)
		return NULL;
	return &h->nodes[1];
}

int heap_insert(struct heap *h, int key, int value)
{
	if (h->nnodes >= h->maxsize)
		return -1;

	h->nnodes++;
	h->nodes[h->nnodes].key = key;
	h->nodes[h->nnodes].value = value;
	h->helper[value] = h->nnodes;

	/* HeapifyUp */
	for (int i = h->nnodes; i > 1 && h->nodes[i].key < h->nodes[i / 2].key; i = i / 2) {
		heap_swap(&h->nodes[i], &h->nodes[i / 2], h);
	}
	return 0;
}

struct heapnode heap_extract_min(struct heap *h)
{
	if (h->nnodes == 0)
		return (struct heapnode) {0, 0};


	struct heapnode maxnode = h->nodes[1];
	h->nodes[1] = h->nodes[h->nnodes];
	h->helper[h->nodes[h->nnodes].value] = 1;
	h->nnodes--;
	heap_heapify(h, 1);

	return maxnode;
}

void heap_heapify (struct heap *h, int index)
{
	while (1) {
		int left = 2 * index;
		int right = 2 * index + 1;
		int largest = index;
		if (left <= h->nnodes && h->nodes[left].key < h->nodes[largest].key)
			largest = left;
		if (right <= h->nnodes && h->nodes[right].key < h->nodes[largest].key)
			largest = right;
		if (largest == index)
			break;
		heap_swap(&h->nodes[index], &h->nodes[largest], h);
		index = largest;
	}
}

int heap_decrease_key(struct heap *h, int index, int newkey)
{
	index = h->helper[index];
	
	if (h->nodes[index].key <= newkey)
		return -1;


	h->nodes[index].key = newkey;
	while (index > 1 && h->nodes[index].key < h->nodes[index / 2].key) {
		heap_swap(&h->nodes[index], &h->nodes[index / 2], h);
		index /= 2;
	}
	return index;
}

// void helper_swap(int* helper, int **i, int **j)
// {
// 	int *tmp = helper[*i];
// 	helper[*i+1] = helper[*j];
// 	helper[*j+1] = *tmp;
// }
