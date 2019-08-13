from .kmer import Kmer
from .suffix_array import SuffixArray
from .suffix_trie import SuffixTrie
from .suffix_tree import SuffixTree
from .bwt import BurrowsWheeler


def read_fasta(filepath):
    text = []
    with open(filepath, "r") as fh:
        for l in fh:
            if l.startswith(">"):
                continue
            text.append(l.rstrip())
    return "".join(text)