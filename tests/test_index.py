import unittest
from indexes import read_fasta, Kmer, SuffixArray, SuffixTrie, SuffixTree,\
                    BurrowsWheeler
import os


cwd = os.path.dirname(os.path.realpath(__file__))
filepath = os.path.join(cwd, "chr1.GRCh38.excerpt.fasta")
chr1 = read_fasta(filepath)


class TestIndex(unittest.TestCase):

    def test_kmer(self):
        km = Kmer(5, chr1)
        self.assertEqual(km.k, 5)
        hits = km.query("TTAGTTTGTA")
        for hit in hits:
            self.assertEqual(km.text[hit:hit+len("TTAGTTTGTA")], "TTAGTTTGTA")

    def test_suffix_array(self):
        sa = SuffixArray(chr1)
        hits = sa.query("TTAGTTTGTA")
        for hit in hits:
            self.assertEqual(sa.text[hit:hit+len("TTAGTTTGTA")], "TTAGTTTGTA")
    
    def test_suffix_trie(self):
        st = SuffixTrie(chr1[:1000])
        hits = st.query("AGAAAGCTAT")
        self.assertEqual(hits, [37])
        
        hits = st.query("AGA")
        self.assertTrue(len(hits) > 1)
        self.assertTrue(37 in hits)
    
    def test_suffix_tree(self):
        st = SuffixTree(chr1[:1000])
        hits = st.query("AGAAAGCTAT")
        self.assertEqual(hits, [37])
        
        hits = st.query("AGA")
        self.assertTrue(len(hits) > 1)
        self.assertTrue(37 in hits)
    
    def test_burrows_wheeler(self):
        bw = BurrowsWheeler(chr1[:1000])
        hits = bw.query("AGAAAGCTAT")
        self.assertEqual(hits, [37])
        
        hits = bw.query("AGAAACGCTAT")
        self.assertEqual(hits, [-1])
