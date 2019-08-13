import unittest
from alignment import NeedlemanWunsch, SmithWaterman, SemiGlobal


class TestAlignment(unittest.TestCase):

    def test_needleman_wunsch(self):
        ali = NeedlemanWunsch("AAGCTCGGTGGCGAAGTC", "AAGCTCGGTGGCGAAGTC")
        self.assertEqual(ali.align_matrix[-1][-1], 18)
        # ali = NeedlemanWunsch("AAGCTCGGTGGCGAAGTC", "AAGCTAGGGGCGACAGTC")
        # print(ali)
    
    def test_smith_watterman(self):
        ali = SmithWaterman("CTCTAAGCTCGGTGGCGAAGTCGTCA", "GTCCCCCCCCAGTAAGCTAGGGGCGACAGTG")
        self.assertEqual(ali.align_matrix[-1][-1], 10)
    
    def test_semi_global(self):
        ali = SemiGlobal("AAGCTAGGGGCGACAGTG", "CTTTGCAAGCTCGGTGGCGAAGTCGTCA")
        