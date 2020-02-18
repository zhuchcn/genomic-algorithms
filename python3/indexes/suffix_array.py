class SuffixArray():
    text = None
    index = None
    
    def __init__(self, text):
        self.text = text
        self._index()
    
    @property
    def suffixes(self):
        return [self.text[i:] for i in self.index]

    def _index(self):
        for i in reversed(range(len(self.text))):
            suffix = self.text[i:]
            if not self.index:
                self.index = [i]
                continue
            self.index.insert(self._search_nearest(suffix) + 1, i)
    
    def _search_nearest(self, suffix):
        left = 0
        right = len(self.index) - 1

        while True:
            mid = int(left + (right - left)/2)
            current_suffix = self.text[self.index[mid]:]

            if mid == 0 and current_suffix > suffix:
                return -1
            if mid == len(self.index) - 1 and current_suffix < suffix:
                return mid

            next_suffix = self.text[self.index[mid + 1]:]
            if current_suffix < suffix and next_suffix > suffix:
                return mid

            if current_suffix > suffix:
                right = mid - 1
            else:
                left = mid + 1
    
    def query(self, x):
        left = 0
        right = len(self.index) - 1
        mid = int(left + (right - left)/2)

        while right > left:
            current_suffix = self.text[self.index[mid]:]
            if current_suffix > x:
                right = mid
            else:
                left = mid + 1
            mid = int(left + (right - left)/2)
        
        offsets = []
        while True:
            current_suffix = self.text[self.index[mid]:]
            if current_suffix[:len(x)] != x:
                break
            offsets.append(self.index[mid])
            mid += 1
        offsets.sort()
        return offsets