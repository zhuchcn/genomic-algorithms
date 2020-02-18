class SuffixTrie():
    root = {}
    
    def __init__(self, text):
        text += "$"
        for i in range(len(text)):
            cur = self.root
            for nucleotide in text[i:]:
                if nucleotide not in cur:
                    cur[nucleotide] = i if nucleotide == "$" else {}
                cur = cur[nucleotide]
    
    def follow_path(self, string):
        cur = self.root
        for char in string:
            if char not in cur:
                return None
            cur = cur[char]
        return cur
    
    def has_substring(self, string):
        return self.follow_path(string) is not None
    
    def has_suffix(self, string):
        nodes = self.follow_path(string)
        if not nodes:
            return False
        return "$" in nodes

    def query(self, x):
        cur = self.follow_path(x)
        if not cur:
            return -1

        def recursive(trie):
            offsets = []
            for key in trie.keys():
                if key == "$":
                    offsets.append(trie[key])
                else:
                    offsets += recursive(trie[key])
            return offsets

        return recursive(cur)
    
