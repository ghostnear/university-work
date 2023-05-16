module main

fn func(mut num []int, max int)
{
	for i := 0; i < max; i++
	{
		num[i]++
	}
}

fn main()
{
	mut num := []int{}
	for i := 0; i < 3; i++
	{
		num << i
	}
	func(mut num, 3)
	for i := 0; i < num.len; i++
	{
		print("${ num[i] } ")
	}
}