module main

fn main()
{
	nr1 := 1
	nr2 := 2
	ptr := &nr1
	println("nr1 value is ${ nr1 } and is at the address ${ &nr1 }")
	println("nr2 value is ${ nr2 } and is at the address ${ &nr2 }")
	println("ptr value is ${ ptr } and is at the address ${ &ptr }")
	println("value at address ptr is ${ *ptr }")	
}