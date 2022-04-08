void MergeSort( int* a, int aLen ) {
if( aLen <= 1 ) {
return;
}
int firstLen = aLen / 2;
int secondLen = aLen – firstLen;
MergeSort( a, firstLen );
MergeSort( a + firstLen, secondLen );
int* c = new int[aLen];
Merge( a, firstLen, a + firstLen, secondLen, c );
memcpy( a, c, sizeof( int ) * aLen );
delete[] c;
}
