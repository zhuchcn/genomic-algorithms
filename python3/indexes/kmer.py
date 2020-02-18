class Kmer():
    k = None
    text = None
    index = {}

    def __init__(self, k, text):
        self.k = k
        self._index(text)

    def _index(self, text):
        self.text = text
        k = self.k
        for i in range(len(text) - k + 1):
            if text[i:i+k] in self.index.keys():
                self.index[text[i:i+k]].append(i)
            else:
                self.index[text[i:i+k]] = [i]
    
    def query(self, pattern):
        k = self.k
        offsets = []
        for i in self.index[pattern[:k]]:
            if pattern[k:] == self.text[i+k:i+len(pattern)]:
                offsets.append(i)
        return offsets