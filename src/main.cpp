#include <iostream>
#include <vector>
#include <algorithm>

template <typename T, typename It, typename Comp=std::less<T>>
void quicksort (std::vector<T>& out,
				It begin, It end,
				const Comp& compare = Comp())
{
	if (begin != end)
	{
		T pivot = *begin++;
		
		It mid =
			std::partition(begin, end,
				[&] (T val)
				{
					return compare(val, pivot);
				});
		
		/*
		qsort p:xs =
			qsort(l) ++ [p] ++ qsort(u)
			where
				(l, u) = partition (< p) xs
		qsort [] = []
		*/
		
		quicksort(out, begin, mid, compare);
		out.push_back(pivot);
		quicksort(out, mid, end, compare);
	}
}

template <typename T, typename Comp=std::less<T>>
void quicksort (std::vector<T>& out,
				std::vector<T>&& in,
				const Comp& compare = Comp())
{
	quicksort(out, in.begin(), in.end(), compare);
}


int main (int argc, char** argv)
{
	std::vector<int> sorted;
	quicksort(sorted, { 5, 2, 9, 1, 3, 6, 4 });
	
	for (int n : sorted)
		std::cout << n << " ";
	
	std::cout << std::endl;
}