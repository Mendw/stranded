from typing import Generator, Any

def get_points(start: int, pivot: int, end: int):
    def _get_points(start: int, pivot: int, end: int) -> Generator[tuple[int, int, int], Any, None]:
        yield pivot
        
        left_pivot = int((start + pivot) / 2)
        if left_pivot != start:
            yield from _get_points(start, left_pivot, pivot)

        right_pivot = int((pivot + end) / 2)
        if right_pivot != pivot:
            yield from _get_points(pivot, right_pivot, end)
    
    yield from _get_points(start, pivot, end)
    yield start
        

if __name__ == '__main__':
    word_set: set[str] = set()
    with open('words.txt', 'r') as input:
        for _word in input.readlines():
            word = _word.lower().strip()
            
            if len(word) <= 3 or len(word) > 20 or not word.isalpha():
                continue
            word_set.add(word)
    
    with open('output.txt', 'w') as output:
        set_size = len(word_set)
        half_point = int(set_size / 2)
        
        word_list = list(sorted(word_set))
        for word_index in get_points(0, half_point, set_size):
            output.write(word_list[word_index] + '\n')
        