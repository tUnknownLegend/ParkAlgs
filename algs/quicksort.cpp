// Возвращает индекс, на который встанет пивот после разделения.
int Partition( int* a, int n ) {
	if ( n <= 1 ) {
		return 0;
	}
	const int& pivot = a[n - 1];
	int i = 0; j = n – 2;
	while ( i <= j ) {
// Не проверяем, что i < n - 1, т.к. a[n - 1] == pivot.
		for ( ; a[i] < pivot; ++i ) {}
		for ( ; j >= 0 && !( a[j] < pivot ); --j ) {}
		if ( i < j ) {
			swap( a[i++], a[j--] );
		}
	}
	swap( a[i], a[n - 1] );
	return i;
}

void QuickSort( int* a, int n ) {
	int part = Partition( a, n );
	if ( part > 0 ) QuickSort( a, part );
	if ( part + 1 < n ) QuickSort( a + part + 1, n – ( part + 1 ) );
}
