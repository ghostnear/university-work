module main

#include <stdio.h>

fn main()
{
	nr1 := 0
	nr2 := 2
	arr := [&nr1, &nr2]
	C.printf("\n nr1 = [%d]".str, nr1)
	C.printf("\n nr2 = [%d]".str, nr2)
	C.printf("\n arr[0] = [%p]".str, arr[0])
	C.printf("\n arr[1] = [%p]".str, arr[1])
	C.printf("\n val of arr[0] = [%d]".str, *arr[0])
	C.printf("\n val of arr[1] = [%d]".str, *arr[1])
}