import unittest
from distance import HammingDistance, LevenshteinDistance, ShortestDetour


class DistanceTest(unittest.TestCase):

    def test_hamming_distance(self):
        dis = HammingDistance("AAATAATCCGAG", "AAATAATCCGAG")
        self.assertEqual(dis.score, 0)
        self.assertEqual(len(dis.matrix), 13)
        self.assertEqual(len(dis.matrix[0]), 13)
        dis = HammingDistance("AAATAATGCGAG", "AAATAATCCGAG")
        self.assertEqual(dis.score, 1)

        with self.assertRaises(ValueError):
            dis = HammingDistance("AAATAATGCGAG", "AAATAATCGAG")
        
        dis = HammingDistance("AAATAATCGAGA", "AAATAATCCGAG")
        self.assertEqual(dis.score, 4)
    
    def test_levenshtein_distance(self):
        dis = LevenshteinDistance("AAATAATCCGAG", "AAATAATCCGAG")
        self.assertEqual(dis.score, 0)

        dis = LevenshteinDistance("AAATAATGCGAG", "AAATAATCCGAG")
        self.assertEqual(dis.score, 1)

        dis = LevenshteinDistance("AAATAATCGAG", "AAATAATCCGAG")
        self.assertEqual(dis.score, 1)

        dis = LevenshteinDistance("AAATAATCCGAG", "AAATAATCGAG")
        self.assertEqual(dis.score, 1)

    def test_shortest_detour(self):
        dis = ShortestDetour("AAATAATCCGAG", "AAATAATCCGAG", 5)
        self.assertEqual(dis.score, 0)

        dis = ShortestDetour("AAATAATGCGAG", "AAATAATCCGAG", 5)
        self.assertEqual(dis.score, 1)

        dis = ShortestDetour("AAATAATCGAG", "AAATAATCCGAG", 5)
        self.assertEqual(dis.score, 1)

        with self.assertRaises(ValueError):
            dis = ShortestDetour("AAATAATCCGAG", "AAATAATGAG", 5)
        
        with self.assertRaises(ValueError):
            dis = ShortestDetour("AAATAATCCGAG", "AAATAATCCGAGTCGAGC", 5)
        