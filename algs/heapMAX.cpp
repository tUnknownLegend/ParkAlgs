// Структура данных двоичная куча
class Heap
{
public:
	Heap()
	explicit Heap( const Array& _arr );
	~Heap();
// Добавить элемент в кучу за
	void Insert( int element );
// Извлечь максимум из кучи за
	int ExtractMax();
// Посмотреть значение максимума в куче за
	int PeekMax() const;
private:
	Array arr; // динамический массив для хранения элементов кучи
	void buildHeap();
	void siftDown( int i );
	void siftUp( int i );
};

// Проталкивание элемента вниз. Array – целочисленный массив.
void Heap::siftDown( int i )
{
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	// Ищем большего сына, если такой есть.
	int largest = i;
	if ( left < arr.Size() && arr[left] > arr[i] )
		largest = left;
	if ( right < arr.Size() && arr[right] > arr[largest] )
		largest = right;

	while (largest != i) {
		// Если больший сын есть, то проталкиваем корень в него.
		std::swap( arr[i], arr[largest] );

		left = 2 * i + 1;
		right = 2 * i + 2;
		// Ищем большего сына, если такой есть.
		if ( left < arr.Size() && arr[left] > arr[i] )
			largest = left;
		if ( right < arr.Size() && arr[right] > arr[largest] )
			largest = right;
	}
}

/*
void Heap::siftDown( int i )
{
	int left = 2 * i + 1;
	int right = 2 * i + 2;
// Ищем большего сына, если такой есть.
	int largest = i;
	if ( left < arr.Size() && arr[left] > arr[i] )
		largest = left;
	if ( right < arr.Size() && arr[right] > arr[largest] )
		largest = right;
// Если больший сын есть, то проталкиваем корень в него.
	if ( largest != i ) {
		std::swap( arr[i], arr[largest] );
		siftDown( largest );
	}
}
*/

// Построение кучи.
void Heap::buildHeap()
{
	for ( int i = arr.Size() / 2 – 1; i >= 0; --i ) {
		siftDown(i);
	}
}

// Проталкивание элемента наверх.
void Heap::siftUp( int index )
{
	while ( index > 0 ) {
		int parent = ( index – 1 ) / 2;
		if ( arr[index] <= arr[parent] )
			return;
		std::swap( arr[index], arr[parent] );
		index = parent;
	}
}

// Добавление элемента.
void Heap::Insert( int element )
{
	arr.Add( element );
	siftUp( arr.Size() - 1 );
}

// Извлечение максимального элемента.
int Heap::ExtractMax()
{
	assert( !arr.IsEmpty() );
// Запоминаем значение корня.
	int result = arr[0];
// Переносим последний элемент в корень.
	arr[0] = arr.Last();
	arr.DeleteLast();
// Вызываем SiftDown для корня.
	if ( !arr.IsEmpty() ) {
		siftDown( 0 );
	}
	return result;
}
