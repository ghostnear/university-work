module main

fn quick_sort(mut array []int, left int, right int)
{
	if left < right
	{
		mut aux := array[left]
		middle := left + (right - left) / 2
		array[left] = array[middle]
		array[middle] = aux

		mut i := left
		mut j := right
		d := 0

		for i < j
		{
			if array[i] > array[j]
			{
				aux = array[i]
				array[i] = array[j]
				array[j] = aux
			}

			i += d
			j -= 1 - d

			quick_sort(mut array, left, i - 1)
			quick_sort(mut array, i + 1, right)
		}
	}
}

fn print_array(array []int)
{
	for x in array
	{
		print("${ x } ")
	}
}

fn main()
{
	mut array := [5, 4, 2, 1, 3]
	quick_sort(mut array, 0, array.len - 1)
	print_array(array)
}