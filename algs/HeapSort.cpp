void HeapSort( int* a, int n ) {
	int heapSize = n;
	BuildHeap( a, heapSize );
	while ( heapSize > 1 ) {
// Немного переписанный ExtractMax.
		swap( a[0], a[heapSize - 1] );
		--heapSize;
		SiftDown( a, heapSize, 0 );
	}
}
