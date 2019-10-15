Design: Our implementation makes use of a struct that is responsible for storing:
- inUse: Whether or not the block it is managing is in use
- isManaging: The number of bytes the metadata is managing
- prev: pointer to the previous meta block
- next: pointer to the next meta block
- c: character that is responsible for decoding the first time mymalloc is called.

mymalloc:
When mymalloc is called it will check to see if it is the first time it has been called by grabbing the front of the block and seeing if c is set to ‘#’. If not we know it is the first time and set up two metadata structs. One for what the call asked for and another for what’s left of the block. In order to break off chunks of the block we have a function that will create a struct that is in charge of all the memory that the call does not need. In normal cases when the mymalloc function is called it will iterate through the meta data looking for a block that can fit what the user asks for. If it finds a place it will return that block and break off extra if there is any. If not the function returns null.

free:
**JC PART**
When free is called, first we must check to see whether the pointer given to us is even valid. In order to make sure that its a pointer we compared the sizeof("pointer") to the size of an actual void*. Furthermore, we have to check to make sure that the pointer is somewhere in our valid malloc. As a last check we also have to make sure that the pointer is actually pointing to some valid metadatablock and not some random piece of data. In order to accomplish this, we must see if our pointer->c has the value of our hashtag. If it doe sthen we are ready to free our pointer. As one last edge case we make sure that the pointer is in use and not in use or else we would be freeing already freed memory. Now for the freeing process we change the value of pointer->isUsed to 0 to indicate it has been freed and if there is a node to the right that is also free then we merge the two nodes together into one. If all goes well we just return our 0 else we return -1.
Average Run Times:
Implement this in memgrind

Findings:
Fill in any
