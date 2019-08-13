class SuffixTree():
    root = {}

    def __init__(self, text):
        text += "$"
        self.root = self._create_node(None)
        self.root["out"][text[0]] = self._create_node(text)

        for i in range(1, len(text)):
            current_branch = self.root
            j = i
            while j < len(text):
                if text[j] in current_branch["out"]:
                    child = current_branch["out"][text[j]]
                    label = child["lab"]
                    k = j + 1
                    while k-j < len(label) and text[k] == label[k-j]:
                        k += 1
                    if k - j == len(label):
                        current_branch = child
                        j = k
                    else:
                        mid = self._create_node(label[:k-j])
                        mid["out"][text[k]] = self._create_node(text[k:])
                        mid["out"][text[k]]["ind"] = i
                        child["lab"] = label[k-j:]
                        mid["out"][label[k-j]] = child
                        current_branch["out"][text[j]] = mid
                else:
                    current_branch["out"][text[j]] = {
                        "lab": text[j:], "out": {}, "ind": i
                    }
    
    @staticmethod
    def _create_node(text):
        return {"lab": text, "out": {}}

    def follow_path(self, string):
        cur = self.root
        i = 0
        while i < len(string):
            if string[i] not in cur["out"]:
                return None
            child = cur["out"][string[i]]
            label = child["lab"]
            j = i + 1
            while j - i < len(label) and j < len(string) and string[j] == label[j - i]:
                j += 1
            if j-i == len(label):
                cur = child
                i = j
            elif j == len(string):
                return child
            else:
                return None
        return cur
    
    def has_substring(self, string):
        return self.follow_path(string)[0] is not None

    def query(self, string):
        tree = self.follow_path(string)
        if not tree:
            return -1
        
        def recursive(tree):
            offsets = []

            if "ind" in tree:
                offsets.append(tree["ind"])
            if tree["out"]:
                for key in tree["out"]:
                    offsets += recursive(tree["out"][key])
            return offsets
        
        return recursive(tree)

    