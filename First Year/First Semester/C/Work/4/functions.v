module main

fn func(val int)
{
	val1 := val + 1
	println("${ val1 } ")
}

fn main()
{
	val := 1
	println("${ val } ")
	func(val)
	println("${ val } ")
	func(val)
}