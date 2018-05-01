// Compute the sum of a file full of binary 16-bit integer data,
// parallel version.

// TODO: parallelize this program!

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

struct mmap_region {
	int fd;
	void *addr;
	size_t size;
};

struct arg_pass {
	size_t num_elements;
	size_t startIndex;
	uint64_t sum;
	uint16_t* data;
};

size_t get_file_size(const char *filename);
void map_file_region(const char *filename, size_t size, struct mmap_region *region);
void unmap_file_region(struct mmap_region *region);
void *sum_data(void* args);
struct arg_pass* new_args(size_t num_elements, size_t startIndex, uint64_t sum,	uint16_t* data);

void *sum_data(void* args){
	// size_t i;
	printf("yo\n");
	struct arg_pass* stuff = (struct arg_pass*)args;
	for (stuff->startIndex = 0; stuff->startIndex < stuff->num_elements; stuff->startIndex++) {
		stuff->sum += stuff->data[stuff->startIndex];
	}
	return NULL;
}

int main(int argc, char **argv)
{
	uint16_t *data;
	size_t size, num_elements;
	uint64_t sum;
	struct mmap_region region;
	//uint64_t sums[2];
	// pthread_t *threads[2];
	pthread_t *firstThread = NULL;
	pthread_t *secondThread = NULL;

	if (argc != 2) {
		fprintf(stderr, "Usage: sumu16 <input file>\n");
		exit(1);
	}

	// Find out how large the file is.
	size = get_file_size(argv[1]);
	printf("File is %lu bytes in size\n", size);

	// Each element (datum) is 16 bits.
	// Find out how many elements there are overall.
	num_elements = size / sizeof(uint16_t);

	// Map the file data into memory
	map_file_region(argv[1], size, &region);
	data = region.addr;

	// Compute the sum
	// sum = 0ULL;
	// for (i = 0; i < num_elements; i++) {
	// 	sum += data[i];
	// }
	struct arg_pass *firstSum = new_args(num_elements / 2, 0, 0ULL, data);
	// firstSum = (*arg_pass){.num_elements = num_elements / 2, .startIndex = 0, .sum = 0ULL, .data = region.addr};
	struct arg_pass *secondSum  = new_args(num_elements, num_elements / 2, 0ULL, data);
	// secondSum = (*arg_pass){.num_elements = num_elements, .startIndex = num_elements / 2, .sum = 0ULL, .data = region.addr};
	//printf("%ld\n", firstSum->);
	pthread_create(firstThread, NULL, sum_data, firstSum);
	pthread_create(secondThread, NULL, sum_data, secondSum);
	//long unsigne(d int blah = 0;
	pthread_join((int) *firstThread, NULL);
	pthread_join((int) *secondThread, NULL);
	sum = firstSum->sum + secondSum->sum;

	printf("Sum is %lu\n", sum);

	unmap_file_region(&region);

	return 0;
}

size_t get_file_size(const char *filename)
{
	struct stat file_info;

	if (stat(filename, &file_info) < 0) {
		fprintf(stderr, "Could not stat %s: %s\n", filename, strerror(errno));
		exit(1);
	}
	return (size_t)file_info.st_size;
}

void map_file_region(const char *filename, size_t size, struct mmap_region *region)
{
	region->size = size;

	// Open the file
	region->fd = open(filename, O_RDONLY);
	if (region->fd < 0) {
		fprintf(stderr, "Could not open %s: %s\n", filename, strerror(errno));
		exit(1);
	}

	// Map the file into memory.
	region->addr = mmap(NULL, (size_t)size, PROT_READ, MAP_PRIVATE, region->fd, (off_t)0);
	if (region->addr == MAP_FAILED) {
		fprintf(stderr, "Could not map %s: %s\n", filename, strerror(errno));
		exit(1);
	}
}

void unmap_file_region(struct mmap_region *region)
{
	munmap(region->addr, region->size);
	close(region->fd);
}

struct arg_pass* new_args(size_t num_elements, size_t startIndex, uint64_t sum,	uint16_t* data){
	struct arg_pass* new_argStruct = (struct arg_pass*) malloc(sizeof(struct arg_pass));
	new_argStruct->num_elements = num_elements;
	new_argStruct->startIndex = startIndex;
	new_argStruct->sum = sum;
	new_argStruct->data = data;
	return new_argStruct;
} 


